#ifndef _QUICKVECTOR_H_
#define _QUICKVECTOR_H_

#include <vector>
using namespace std;

template < class T >
class quickvector
{
public:
  typedef const T& const_reference;
  typedef T& reference;
  typedef typename vector<T>::iterator iterator;
  typedef typename vector<T>::const_iterator const_iterator;

  quickvector () { _currIdx = 0; }
  quickvector (const_reference rhs ) { _data = rhs._data; _currIdx = rhs._currIdx; }
  quickvector& operator= (const_reference rhs){ _data = rhs._data; _currIdx = rhs._currIdx; return *this; }
  void push_back (const T& d) { 
    if ( _currIdx >= _data.size() )
      _data.push_back(d); 
    else
      _data[_currIdx] = d;
    _currIdx++;
  }

  iterator begin () { return _data.begin(); }
  const_iterator begin () const { return _data.begin(); }
  iterator end () { return _data.end(); }
  const_iterator end () const { return _data.end(); }

  void reset() { _currIdx = 0; }
  void clear() { _data.clear(); }
  int size() { return _data.size(); }
private:
  vector<T> _data;
  int _currIdx;
};

#endif
