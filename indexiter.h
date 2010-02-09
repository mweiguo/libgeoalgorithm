#ifndef _INDEX_ITER_H_
#define _INDEX_ITER_H_

template < class ValueType >
class IndexIterator
{
public:
  typedef IndexIterator self;
  typedef IndexIterator& reference;
  typedef const IndexIterator& const_reference;
  typedef IndexIterator* pointer;
  typedef ValueType value_type;
  IndexIterator ( vector<ValueType>* data, int index ) : pData(data), idx(index) { }
  reference operator ++ ();
  self operator ++ (int);
  ValueType operator* ();
  ValueType* operator-> ();
  int index() { return idx; }
  bool operator== ( const_reference ref );
  bool operator!= ( const_reference ref );
private:
  vector<ValueType>* pData;
  int idx;
};

template < class ValueType >
IndexIterator<ValueType>& IndexIterator<ValueType>::operator ++ ()
{ 
  ++idx; 
  return *this; 
}

template < class ValueType >
IndexIterator<ValueType> IndexIterator<ValueType>::operator ++ (int)
{
  self tmp = *this;
  ++idx;
  return tmp;
}

template < class ValueType >
ValueType IndexIterator<ValueType>::operator* ()
{
  return *(operator-> ());
}

template < class ValueType >
ValueType* IndexIterator<ValueType>::operator-> ()
{
  return &((*pData)[idx]);
}

template < class ValueType >
bool IndexIterator<ValueType>::operator== ( typename IndexIterator<ValueType>::const_reference ref )
{
  return ((pData==ref.pData) && (idx==ref.idx));
}

template < class ValueType >
bool IndexIterator<ValueType>::operator!= ( typename IndexIterator<ValueType>::const_reference ref )
{
  return !(operator==(ref));
}

#endif
