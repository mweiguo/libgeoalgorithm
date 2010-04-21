#ifndef _INDEX_SORTER_H_
#define _INDEX_SORTER_H_

#include <vector>
#include <algorithm>

using namespace std;

// if _NEED_STATISTIC_ is defined, the interface 'statistic' will be ready for using.
template < class Vec >
class IndexVecSort
{
public:
    IndexVecSort (vector<int>& indices, vector<Vec>& vecs, int axis) : 
        _indices(indices), _vecs(vecs), _axis(axis) {
#ifdef _NEED_STATISTIC_
        _swapcnt = 0;    
        _comparecnt = 0;
        _assignmentcnt = 0;
        _addsubcnt = 0;
#endif
    }
    // [left, right)
    void sort (int istart, int iend)
    {
        while ( iend > (istart+1) ) {
            int pivotIndex = _partition ( istart, iend, medianof3(istart, iend-1, istart+(iend-istart)/2 ) );
            // int pivotIndex = _partition ( istart, iend, istart );
            if ( (pivotIndex-istart) >= (iend-pivotIndex) ) {
                sort ( pivotIndex+1, iend );
                iend = pivotIndex;
            } else {
                sort ( istart, pivotIndex );
                istart = pivotIndex+1;
            }
#ifdef _NEED_STATISTIC_
            _assignmentcnt += 2;
            _comparecnt ++;
            _addsubcnt += 4;
#endif
        }
    }
#ifdef _NEED_STATISTIC_
    string statistic () {
#include <sstream>
        stringstream ss;
        ss << "\tswap count       = " << _swapcnt << endl;
        ss << "\tcompare count    = " << _comparecnt << endl;
        ss << "\tassignment count = " << _comparecnt << endl;
        ss << "\taddsub count     = " << _addsubcnt << endl;

        return ss.str();
    }
#endif
private:
    int medianof3 ( int idx1, int idx2, int idx3 ) {
#ifdef _NEED_STATISTIC_
        _comparecnt += 2;
        _assignmentcnt += 3;
        _addsubcnt += 9;
#endif
        float v1 = _vecs[_indices[idx1]][_axis];
        float v2 = _vecs[_indices[idx2]][_axis];
        float v3 = _vecs[_indices[idx3]][_axis];
        if ( v1 <= v2 ) {
            if ( v3 <= v1 ) { // v3 v1 v2
                return idx1;
            } else if ( v2 <= v3 ) { // v1 v2 v3
                return idx2;
            } else { // v1 v3 v2
                return idx3;
            }            
        } else { // v2 < v1
            if ( v3 <= v2 ) { // v3 v2 v1
                return idx2;
            } else if ( v1 <= v3 ) { // v2 v1 v3
                return idx1;
            } else { // v2 v3 v1
                return idx3;
            }            
        }
    }
    // [left, right)
    int _partition (int left, int right, int pivotIndex )
    {
#ifdef _NEED_STATISTIC_
        _assignmentcnt += 5;
        _swapcnt++;
        _addsubcnt += 6;
#endif

        right = right - 1;
        int* pPivot = &_indices[pivotIndex];
        float pivotValue = _vecs[*pPivot][_axis];
        int *pStoreIndex = &_indices[left];
        int *pEnd = &_indices[right];
        // move pivot to end
        swap ( *pPivot, *pEnd );
        // move all less node in the front of pivot
        for ( int* pp=pStoreIndex; pp!=pEnd; ++pp ) {
            if ( _vecs[*pp][_axis] < pivotValue ) {
                // if ( i != storeIndex ) {
                swap (*pp, *pStoreIndex );
                // }
                ++pStoreIndex;
#ifdef _NEED_STATISTIC_
                _swapcnt ++;
                _addsubcnt ++;
#endif
            }
#ifdef _NEED_STATISTIC_
            _addsubcnt += 3;
            _comparecnt ++;            
#endif
        }
        // move pivot to it's real position
        // if ( storeIndex != right ) {
        swap ( *pStoreIndex, *pEnd );
        // }

        return pStoreIndex-&_indices[0];
    }
private:
    vector<int>& _indices;
    vector<Vec>& _vecs;
    int _axis;
#ifdef _NEED_STATISTIC_
    int _swapcnt, _comparecnt, _assignmentcnt, _addsubcnt;
#endif
};

#endif
