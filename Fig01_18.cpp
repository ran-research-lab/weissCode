#include <iostream>
using namespace std;

/**
 * Figure 1.18: Implements the big five.
 */
class IntCell
{
  public:
    explicit IntCell( int initialValue = 0 )
      { 
        storedValue = new int{ initialValue }; 
        cout << "Int constructor!\n";
      }
    
    ~IntCell( )
      {
        cout << "Destructor\n"; 
        delete storedValue; 
      }

    IntCell( const IntCell & rhs ) { 
      storedValue = new int{ *rhs.storedValue }; 
      cout << "Class constructor!\n";
    }

    IntCell( IntCell && rhs ) : storedValue{ rhs.storedValue }
      { rhs.storedValue = nullptr; 
      cout << "RValue copy constructor!\n";
      }
    
    IntCell & operator= ( const IntCell & rhs )
    {
        if( this != & rhs )
            *storedValue = *rhs.storedValue; 
        cout << "Assignment operator!\n";
        return *this;
    }
    
    IntCell & operator= ( IntCell && rhs )
    {
        std::swap( storedValue, rhs.storedValue );
        cout << "Move operator!\n";
        return *this;
    }
    
    int read( ) const
      { return *storedValue; }
    void write( int x )
      { *storedValue = x; }
    
  private:
    int *storedValue;
};

void myswap( IntCell & lhs, IntCell & rhs )
{
    IntCell tmp = static_cast<IntCell &&>( lhs );  // std::move
    lhs = static_cast<IntCell &&>( rhs );
    rhs = static_cast<IntCell &&>( tmp );
}

/*
 * Figure 1.15.
 */
int f( )
{
    IntCell a( 2 );
    IntCell b = a;
    IntCell c;

    c = b;
    a.write( 4 );
    myswap( a, b );
    cout << a.read( ) << endl << b.read( ) << endl << c.read( ) << endl;
    
    return 0;
}


int main( )
{
    f( );
    return 0;
}
