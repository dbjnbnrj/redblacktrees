Introduction

A red–black tree is a type of self-balancing binary search tree, a data structure used in computer science. It is complex, but has good worst-case running time for its operations and is efficient in practice: it can search, insert, and delete in O(log n) time, where n is the total number of elements in the tree. A red–black tree is a binary search tree that inserts and deletes in such a way that the tree is always reasonably balanced. It has the following requirements-

Root node must always be black
The children of a red node must never be red
The black height (height between the root and the leaves) must be a constant.

In this assignment I have attempted to implement a generic type-safe red-black tree as a container type. I have defined my own node, iterator and container in header files rb_node.h, rb_iterator.h and rb_tree.h for realizing the same.

Function Definition

In header rb_node.h
Name
 class rb_node 
Synopsis
 class rb_node
{ 
value_type value;
rb_node * parent;
rb_node * left;
rb_node *right;
bool color;
}; 
Members
value- data of  same as type as the data-type(primitive/user-defined) used to instantiate the object.
parent- pointer to parent of the current node
left- pointer to left child
 right- pointer to right child
color- bool variable instantiated by enum where RED-0, BLACK-1

Functions
rb_node * max( void )- Returns maximum value of subtree
rb_node * min( void )- Returns minimum value of subtree
rb_node * sibling( void )- Returns sibling node (needed to find uncle)
rb_node * successor( void )- Returns successor of a given node
rb_node * predecessor( void )- Returns previous tree node
void print()- utility function used to print node details
const bool is_a_left_son( void )- checks if node is left son
const bool is_a_right_son(void )- checks if node is a right son 



Description
This class represents one node in the tree and links left and right to nodes with lower and higher value of order criterion. Each tree is built from one type of items defined by user. User can decide to include node structure inside item representation or rb_tree can create node structures for each inserted item.


In header rb_iterator.h
Name
 class rb_iterator 
Synopsis

class rb_iterator:public std::iterator<bidirectional_iterator_tag>
{

		node_type * Iterator ;
}

Description
This class represents an implementation of an STL iterator for red black search trees.


In header rb_tree.h
Name
 class rb_tree
Synopsis
 class rb_tree
{
	node_type * root;
	unsigned long size;
}
Members
root- pointer to root node of tree
size- number of nodes in tree

Functions
	iterator max( void )  - returns iterator to maximum element of tree
	iterator min( void )  - returns iterator to minimum element of tree
	iterator begin( void ) – returns iterator to minimum element of tree
	iterator end( void) – returns default iterator(marking tree end)
	bool empty( void )- checks whether tree is empty


	Insertion functions for rb_tree
	iterator insert( value_type value )- by value
iterator insert( iterator & current, value_type &value )- by iterator
void insert( Iterator_ begin, Iterator_ end )- inserting a range
node_type * insert( node_type * node )- inserting a node

void print()- visually displaying trees
void inorder_print()- printing nodes inorder
int height()- returns tree height

Special functions (protected):

List of functions unique to rb_tree
	void rb_adjust(node_type *node)- adjusts tree based on rb-tree criteria (see Introduction)
	void left_rotate(node_type *node)- rotate node left
	void right_rotate( node_type * node )- rotate node right


Description
This class is an implementation of a red-black balanced binary search tree. This class implements an STL-compatible container.	














Usage
Typical usage case is as follows-
#include<iostream>
#include<fstream>
#include<algorithm>
#include"rb_tree.h"
#include"conio.h"
#include<vector>
using namespace std;
int main()
{
	system("color fc");
	rb_tree<int> t1,t2;
	ifstream sample;
	int test_array[10]={0,1,2,3,4,5,6,7,8,9}, test_array_copy[10]; 
	
	cout<<endl<<"Reading from sample"<<endl;
	sample.open("C:\\C++\\sample.txt");
	if(sample.is_open())
	{
		while(!sample.eof()){
			t1.insert(sample.get());
		}
	}
	sample.close();
	t1.print();

	cout<<endl<<"Reading from test array"<<endl;
	t2.insert(&test_array[0],&test_array[10]);
	cout<<"Printing tree:"<<endl;
	t2.print();
	cout<<"Printing nodes:"<<endl;
	t2.inorder_print(t2.root);


	cout<<endl<<"Illustrating find:"<<endl;
	cout<<"Enter search value:";
	int key;
	cin>>key;
	rb_tree<int>::iterator it=find(t2.begin(),t2.end(),key);
	if(it==t2.end())
		cout<<endl<<"Not found"<<endl;
	else
	{cout<<"Element has been found"<<endl;it->print();}
	
	cout<<"Illustrating copy"<<endl;
	copy(t2.begin(),t2.end(),&test_array_copy[0]);
	cout<<"Printing array after copy"<<endl;
	for (int i=0; i<10; i++)
		cout<<test_array_copy[i]<<" ";
	cout<<endl;

	cout<<"Illustrating replace"<<endl;
	cout<<"Original tree"<<endl;
	t2.print();
	replace(t2.begin(),t2.end(),0, -4);
	cout<<"After replace"<<endl;
	t2.print();
	_getch();
}