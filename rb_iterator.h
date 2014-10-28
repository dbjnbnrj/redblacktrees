#ifndef RB_ITERATOR
#define RB_ITERATOR

#include <iterator>
#include "rb_node.h"
using std::iterator ;
using std::bidirectional_iterator_tag ;

template< typename T >
class rb_iterator:public std::iterator<	bidirectional_iterator_tag,typename T::value_type>
{
protected:
		T * Iterator ;	// a pointer to a rb_node
public:
//Type definitions
	typedef typename T::value_type *			pointer ;			 
	typedef typename T::value_type const *		const_pointer ;		
	typedef typename T::value_type &			reference ;			
	typedef typename T::value_type const &		const_reference ;	

// Constructors:
	explicit rb_iterator( void ): iterator(), Iterator(NULL) { } ;
	rb_iterator( T * ptr ): Iterator( ptr ) { }
	rb_iterator( const rb_iterator & that ): Iterator( that.Iterator ) { }

//Operators
	rb_iterator operator++( void ) {
		Iterator = Iterator->successor() ;
		return *this ;
	}
	rb_iterator operator++( int ) {
		T * temp = Iterator ;
		operator++();
		return rb_iterator( temp ) ;
	}

	rb_iterator operator--( void ) {
		Iterator = Iterator->predecessor() ;
		return ( *this ) ;
	}

	rb_iterator operator--( int ) {
		T * temp = Iterator ;
		operator--();
		return rb_iterator( temp ) ;
	}

	rb_iterator & operator=( const_reference that ) {
		Iterator->value = that ;
		return ( *this );
	}

	bool operator==( const rb_iterator & that ) const	{	return ( Iterator == that.Iterator ) ;	}
	bool operator!=( const rb_iterator & that ) const	{	return ( Iterator != that.Iterator ) ;	}
	operator T&()				{	return *Iterator ;	}
	operator const T&() const	{	return *Iterator ;	}
	reference operator* ( void )	{	return Iterator->value ;		}
	T * operator->( void )		{	return Iterator ;	}
} ;

#endif