#ifndef RB_TREE
#define RB_TREE
#include<functional>
#include<queue>
#include "rb_node.h"
#include "rb_iterator.h"

template< typename T >
class rb_tree
{
public:
	// type definitions:
	typedef typename rb_node< T >	node_type ;
	typedef typename T	value_type ;
	typedef rb_iterator< node_type > iterator ;

	//members
	node_type * root;
	unsigned long size;

	//Constructors
	rb_tree( void ): root( NULL ), size( 0 )	{	}
	
	template<typename Iterator_>
	rb_tree(Iterator_ begin, Iterator_ end){ insert(begin, end);}

	//Utility functions
	iterator max( void )  {	return ( empty() ) ? end() : iterator( root->max() ) ;	}
	iterator min( void )  {	return ( empty() ) ? end() : iterator( root->min() ) ;	}
	iterator begin( void ) 	{	return min() ;	}
	iterator end( void ) 	{	return iterator() ;	}
	bool empty( void ) const		{	return ( root == NULL ) ;	}

	/*Insertion*/
	iterator insert( value_type value ) {
		return iterator( insert( new node_type( value ) ) ) ;
	}

	iterator insert( iterator & current, value_type &value ) {
		return insert( value ) ;
	}

	template< typename Iterator_ >
	void insert( Iterator_ begin, Iterator_ end ) {
	for ( Iterator_ it = begin ; it != end ; ++it )
		{
		value_type v= *it;
		insert( v ) ;
		}
	}



	/*	RED BLACK INSERTION	*/
	node_type * insert( node_type * node ) { 	
		binary_insert(node) ;
		node_type *temp = node;
		rb_adjust(temp);
		return node;
	}

	

	//Display tree
	void print()
	{
		if (empty())
			cout<<"No tree initialized";
		else
			print(root);
	}

	void inorder_print(node_type *ptr)
	{
		if(ptr==NULL)
			return;
		ptr->print();
		inorder_print(ptr->left);
		inorder_print(ptr->right);
	}

	int height()
	{
		return height(root);
	}


	protected:
	
	void print(node_type * node)
	{
		cout<<endl;
		if(node==NULL)
			return;
		int h= height();
		queue<node_type *> currentLevel, nextLevel;
		currentLevel.push(node);
		while (!currentLevel.empty()) {
		node_type *currNode = currentLevel.front();
		currentLevel.pop();
		if (currNode!=NULL) {
			for(int i=(1<< h-1)* 2; i>0; i--)
				cout<<" ";
			cout << currNode->value<<":"<< currNode->color;
			nextLevel.push(currNode->left);
			nextLevel.push(currNode->right);
		}
		if (currentLevel.empty()) {
			cout << endl; h--;
			swap(currentLevel, nextLevel);
		}
	}

	}

	int height(node_type * node){
	if (node == NULL)
		return 0;
	int heightLeft = height(node->left);
	int heightRight = height(node->right);

		if( heightLeft > heightRight )
			return heightLeft +1;
		else
			return heightRight +1;
	}
	
	//Binary Tree Insertion
	node_type * binary_insert( node_type * node ) {
		++size;
		//Root insertion case
		if(empty())
			root=node;
		else
		{
			node_type * current= root;
			do
			{
				if(current->value < node->value)
				{
					if(current->right==NULL)
					{node->parent= current;current->right= node;break;}
					else
					{current=current->right;}
				}
				else if (current->value >= node->value)
				{
					if(current->left==NULL)
					{node->parent= current;current->left= node;break;}
					else
					{current=current->left;}
				}
			}while(true);
		}
		return node;
	}
	
	//Special functions
	void rb_adjust(node_type *node)
		{
			//Case 1: Root node
			if(node==NULL)
				return;
			if(node->parent==NULL)
			{node->color=BLACK;return;}
			
			node_type *p= node->parent;
			//Case 2: Parent is BLACK
			if(p!=NULL && p->color==BLACK)
					return;
			
			//Case 3: Parent and Uncle are RED
			node_type *u= p->sibling();
			if( p->color==RED && (u!=NULL && u->color==RED))
			{
				p->color=BLACK;
				u->color=BLACK;
				p->parent->color=RED;
				rb_adjust(p->parent);
				return;
			}

			//Case 4: Parent is Red and Uncle is Black(Or NULL)
			//If parent is left son
			if(p->is_a_left_son())
			{
				if(node->is_a_right_son())
				{node=p;left_rotate(p);}
				
				p->color=BLACK;
				
				if(p->parent!=NULL)
				{p->parent->color=RED;
				right_rotate(p->parent);}
				return;
			}
			//If parent is right son
			else if (p->is_a_right_son())
			{
				if(node->is_a_left_son())
				{node=p;right_rotate(p);}
				p->color=BLACK;
				if(p->parent!=NULL)
				{p->parent->color=RED;
				left_rotate(p->parent);}
				return;
			}

		}


	// left rotate
	void left_rotate(node_type *node)
	{
		if ( node->right != NULL ) {
			node_type * right_son = node->right ;
			if ( ( node->right = node->right->left ) != NULL )
				node->right->parent = node ;
			if ( node->parent == NULL )
				root = right_son ;
			else if ( node->is_a_left_son() )
				node->parent->left = right_son ;
			else
				node->parent->right = right_son ;	

			// update right_son's parent:
			right_son->parent = node->parent ;
			// the left son of the old right son is this node:
			node->parent = right_son ;
			right_son->left = node ;
		}
	}
	
	//	right rotate	
	void right_rotate( node_type * node ) {
		// check if node has a left son
		if ( node->left != NULL ) {
			node_type * left_son = node->left ;
			if ( ( node->left = node->left->right ) != NULL )
				node->left->parent = node ;
			if ( node->parent == NULL )
				root = left_son ;
			else if ( node->is_a_left_son() )
				node->parent->left = left_son ;
			else
				node->parent->right = left_son ;	
			left_son->parent = node->parent ;
			node->parent = left_son ;
			left_son->right = node ;
		}
	}

} ;


#endif