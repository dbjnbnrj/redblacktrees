
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
	int ch=1;
	do
	{
		cout<<"Enter value:"<<endl;
		int val=0;
		cin>>val;
		t1.insert(val);
		t1.print();
		t1.inorder_print(t1.root);
		cout<<"Do you want to continue? Y(1)/N(0)";
		cin>>ch;
	}while(ch==1);
#if 0
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
#endif

	_getch();
}