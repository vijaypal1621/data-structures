
#include<cstring>
#include<iostream>

using namespace std;

// cretaing a class which is a sort of linkedlist node
template <typename V>

class mapNode
{
public:
	string key;
	V value;
	mapNode<V>* next;

	// constructor
	mapNode(string key, V value)
	{
		this->key = key;
		this->value = value;
		next = NULL;
	}

	// destructor
	~mapNode()
	{
		delete next;  // first delete next address nodes
	}

};




// we have to define template before ech class
template <typename V>
class hashmap
{
private:
	// an array which stores the addresses of the head of mapnode
	mapNode<V>** bucketarray;
	int count; // size of the linkedlist(mapNode)
	int numbucket; // size of the bucket array
public:
	hashmap()
	{
		bucketarray = new mapNode<V> * [20];
		// here bucketarray is initialised with garbage value which is dangerous
		for (int i = 0; i < 20; i++)
			bucketarray[i] = NULL;

		numbucket = 20;
		count = 0;
	}

	~hashmap()
	{
		for (int i = 0; i < 20; i++)
			delete bucketarray[i];
		delete[] bucketarray;
	}

public:

	int size()
	{
		return count;
	}

private:
	// basically a hash function which gives you index where the key and value is going to be stored
	int getBucketIndex(string key)
	{
		// this has 2 parts hash code and hash compression
		int hashcode = 0;
		// we are using the concept of some number form (base p) where p is prime no.
		int coeff = 1; // p raises to 0 is 1

		for (int i = key.length() - 1; i >= 0; i--)
		{
			hashcode += key[i] * coeff;
			hashcode = hashcode % numbucket;

			coeff *= 37;  // here we have to confirm that it should not overshoot the range of int
			coeff = coeff % numbucket;
		}

		return hashcode % numbucket;  // hash compression
	}
private:
	void rehash()
	{
		mapNode<V>** temp = bucketarray;
		bucketarray = new mapNode<V> * [2 * numbucket]; // here it is initialised with garbage value
		for (int i = 0; i < 2 * numbucket; i++)
			bucketarray[i] = NULL;

		int oldbucketsize = numbucket;
		numbucket = 2 * numbucket;
		count = 0;

		for (int i = 0; i < oldbucketsize; i++)
		{
			mapNode<V>* head = temp[i];
			while (head != NULL)
			{
				string key = head->key;
				V value = head->value;
				insert(key, value);  // we have to one by one insert each element of the linked list
				head = head->next;

			}

		}
		// deleting the old bucketarray
		for (int i = 0; i < oldbucketsize; i++)
		{
			mapNode<V>* head = temp[i];
			delete head;
		}
		delete[] temp;

	}


public:
	void insert(string key, V value)
	{
		int index = getBucketIndex(key);
		// first i have to confirm that key is not already exist and if yes then i have to update it only
		mapNode<V>* head = bucketarray[index];
		mapNode<V>* temp = head;  // just to traverse

		while (temp != NULL)
		{
			if (temp->key == key)
			{
				temp->value = value;//updation
				return;
			}

			temp = temp->next;
		}
		// if control reaches here that means key is not already exist
		 // creting a new MapNode
		mapNode<V>* newnode = new mapNode<V>(key, value);
		newnode->next = head;// inserting in front
		bucketarray[index] = newnode;  // updaing the head of that bucket array index
		count++; // updaing the count of linked nodes
		// creating a load factor to check the condition for rehash
		double loadfactor = (1.0 * count) / numbucket;
		if (loadfactor >= 0.7)  // if its value is greater than 0.7 rehashed it
			rehash();

		return;


	}

	double getloadfactor()
	{
		return (1.0 * count) / numbucket;
	}


	V remove(string key)
	{
		V ans;  // value to be returned

		int index = getBucketIndex(key);
		mapNode<V>* head = bucketarray[index];
		mapNode<V>* temp = head;
		mapNode<V>* pretemp = NULL;
		while (temp != NULL)
		{
			// if first node is to be deleted
			if (temp->key == key && pretemp == NULL)
			{
				ans = temp->value;
				head = temp->next;// shifting head to the next position
				temp->next = NULL;
				delete temp;
				return ans;
			}
			// if control reaches here that means it is not fist node
			pretemp = temp;
			if (temp->key == key)
			{
				ans = temp->value;
				pretemp->next = temp->next;
				temp->next = NULL;
				delete temp;
				return ans;
			}
			temp = temp->next;

		}

		// if control reaches here that means key is not found
		return -1;

	}

	V search(string key)
	{
		int index = getBucketIndex(key);
		mapNode<V>* head = bucketarray[index];
		while (head != NULL)
		{
			if (head->key == key)
				return head->value;

			head = head->next;
		}
		// if control reaches here that means key is not found
		return -1;

	}


};


// main class

int main()
{


	hashmap<int> ourmap;

	string str = "abc";

	for (int i = 1; i <50; i++)
	{
		char ch = 'i' + '0';
		str = str + ch;
		ourmap.insert(str, i);
		cout << "loadfactor: " << ourmap.getloadfactor() << endl;
	}






}
