#include <bits/stdc++.h>
#include <chrono>

using namespace std;

ifstream fin( "input.in" );
ofstream fout( "output.out" );

/// 1. HEAPSORT ( alocare dinamica a memoriei cu vector )
/// 2. QUICKSORT + INSERTION SORT'
/// 3. BUCKETSORT + HEAPSORT
/// 4. BUCKETSORT + QUICKSORT + INSERTION SORT
/// 5. EASTER EGG

class heap {
    private:
        vector <int> v;

        void Upheap( int pos ) {
            while( pos > 0 && v[(pos - 1) >> 1] > v[pos] ) {
                swap( v[pos], v[(pos - 1) >> 1] );
                Upheap( ( pos - 1 ) >> 1 );
            }
        }

        void Downheap( int pos ) {
            if( (pos << 1) + 1 < v.size() ) {
                long long val1 = v[(pos << 1) + 1];
                long long val2;

                ( ( pos << 1 ) + 2 < v.size() ) ? val2 = v[(pos << 1) + 2] : val2 = 4000000000;

                if( val1 >= v[pos] && val2 >= v[pos] ) return;
                if( val1 < val2 ) {
                    swap( v[pos], v[(pos << 1) + 1] );
                    Downheap( (pos << 1) + 1 );
                }
                else {
                    swap( v[pos], v[(pos << 1) + 2] );
                    Downheap( (pos << 1) + 2 );
                }
            }
        }

    public:
        void push( int x ) {
            v.push_back( x );
            Upheap( v.size() - 1 );
        }
        int top() {
            if( v.empty() ) return -1;
            return v[0];
        }
        void pop() {
            if( v.empty() ) return;

            v[0] = v.back();
            v.pop_back();

            Downheap( 0 );
        }
        int hsize() {
            return v.size();
        }
};

void HeapSort( vector <int> & v, int lf, int rg ) {
    heap A;

    for( int i = lf; i <= rg; ++i ) {
        A.push( v[i] );
    }
    while( A.hsize() > 0 ) {
        v[lf++] = A.top();
        A.pop();
    }
}

void InsertionSort( vector<int> & v, int lf, int rg ) {
    for( int i = lf; i <= rg; ++i ) {
        int p = i;

        for( int j = i - 1; j >= lf; --j )
            if( v[j] > v[i] )
                p = j;

        if( p == i ) continue;
        else {
            int tmp = v[i];

            for( int j = i; j > p; --j )
                v[j] = v[j - 1];
            v[p] = tmp;
        }
    }
}

int Pivot( vector <int> & v, int lf, int rg ) {
    /// Pivotul este ales aleatoriu

    srand( time(0) );
    int rand_p = int( (double)rand() / ((double)RAND_MAX + 1.0) * 2000000001 ) % ( rg - lf + 1);

    swap( v[rg], v[lf + rand_p] );

    int steplf = 1, steprg = 0;

    while( lf < rg ) {
        if( v[lf] > v[rg] ) {
            swap( v[lf], v[rg] );
            swap( steplf, steprg );
        }
        lf += steplf;
        rg -= steprg;
    }
    return lf;
}

void QuickSort( vector <int> & v, int lf, int rg ) {
    if( lf > rg ) return;
    if( rg - lf + 1 <= 16 ) {
        InsertionSort( v, lf, rg );
        return;
    }

    int p = Pivot( v, lf, rg );

    QuickSort( v, lf, p - 1 );
    QuickSort( v, p + 1, rg );
}

void BucketSort( vector<int> & v, int lf, int rg ) {
    vector<int> H[30520];

    for( int i = 0; i < v.size(); ++i )
        H[ v[i] >> 16].push_back( v[i] );

    for( int i = 0; i < 30520; ++i )
        HeapSort( H[i], 0, H[i].size() - 1 );

    v.clear();
    for( int i = 0; i < 30520; ++i )
        for( int j = 0; j < H[i].size(); ++j )
            v[lf++] = H[i][j];
}

void BucketSort2( vector<int> & v, int lf, int rg ) {
    vector<int> H[30520];

    for( int i = 0; i < v.size(); ++i )
        H[ v[i] >> 16 ].push_back( v[i] );

    for( int i = 0; i < 30520; ++i )
        QuickSort( H[i], 0, H[i].size() - 1 );

    for( int i = 0; i < 30520; ++i )
        for( int j = 0; j < H[i].size(); ++j )
            v[lf++] = H[i][j];
}

void STALIN_SORT( vector<int> & v ) {
    vector <int> v2;

    v2.push_back( v[0] );

    for( int i = 1; i < v.size(); ++i )
        if( v[i - 1] <= v[i] ) v2.push_back( v[i] );

    v = v2;
}

vector <int> rand_vect( int lg ) {
    vector <int> v;

    srand( time(0) );
    for( int i = 1; i <= lg; ++i )
        v.push_back( (double)rand() / ((double)RAND_MAX + 1.0) * (double)2000000001 );

    return v;
}

///  p - ce procent din vector sa fie amestecat p = [ 0, 100 ]

vector <int> almost_sorted( int lg, int p ) {
    vector <int> v;

    srand( time(0) );
    v.push_back( 1 );
    for( int i = 1; i <= lg; ++i )
        v.push_back( v.back() + 1 + rand() % 5 );

    int nr_shuffles = lg * ( (double)p / 100 );

    for( int i = 1; i <= nr_shuffles; ++i ) {
        int x = (double)rand() / ((double)RAND_MAX + 1.0) * lg;
        int y = (double)rand() / ((double)RAND_MAX + 1.0) * lg;

        swap( v[x], v[y] );
    }
    return v;
}

vector <int> rev_vect( vector<int> & V ) {
    vector <int> v;

    for( int i = V.size() - 1; i >= 0; --i )
        v.push_back( V[i] );
    return v;
}

vector<int> mountain( int lg ) {
    vector <int> v( lg );
    int lf = 0, rg = lg - 1;
    int nr = 1;

    while( nr < lg ) {
        v[lf] = nr++;
        v[rg] = nr++;

        ++lf;
        --rg;
    }
    if( lg % 2 ) v[lg >> 1] = lg;
    return v;
}

bool Check( vector<int> &v, vector<int> &v2 ) {
    if( v.size() != v2.size() ) return false;

    for( int i = 0; i < v.size(); ++i )
        if( v[i] != v2[i] )
            return false;
    return true;
}

void TEST_IT( vector <int> v ) {
    vector<int> V = v;
    auto start = chrono::high_resolution_clock::now();
    HeapSort( V, 0, V.size() - 1 );
    auto stop = chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    fout << "HeapSort:                             " << duration.count() << " ms\n";

    V = v;
    start = chrono::high_resolution_clock::now();
    QuickSort( V, 0, V.size() - 1 );
    stop = chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    fout << "QuickSort:                            " << duration.count() << " ms\n";

    V = v;
    start = chrono::high_resolution_clock::now();
    BucketSort( V, 0, V.size() - 1 );
    stop = chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    fout << "BucketSort:                           " << duration.count() << " ms\n";

    V = v;
    start = chrono::high_resolution_clock::now();
    BucketSort2( V, 0, V.size() - 1 );
    stop = chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    fout << "BucketSort2:                          " << duration.count() << " ms\n";
    fout << "\n";
}

int main()
{
    vector <int> V_rand = rand_vect( 1000000 );
    vector <int> V_asc1 = almost_sorted( 1000000, 0 );
    vector <int> V_asc2 = almost_sorted( 1000000, 25 );
    vector <int> V_asc3 = almost_sorted( 1000000, 50 );
    vector <int> V_desc1 = rev_vect( V_asc1 );
    vector <int> V_desc2 = rev_vect( V_asc2 );
    vector <int> V_desc3 = rev_vect( V_asc3 );
    vector <int> V_mtn = mountain( 1000000 );
    vector <int> V;

    fout << "                   Vector aleator\n";
    TEST_IT( V_rand );
    fout << "                   Vector sortat\n";
    TEST_IT( V_asc1 );
    fout << "                   Vector sortat in proportie de 75%\n";
    TEST_IT( V_asc2 );
    fout << "                   Vector sortat in proportie de 50%\n";
    TEST_IT( V_asc3 );
    fout << "                   Vector sortat descrescator \n";
    TEST_IT( V_desc1 );
    fout << "                   Vector sortat descrescator in proportie de 75%\n";
    TEST_IT( V_desc2 );
    fout << "                   Vector sortat descrescator in proportie de 50%\n";
    TEST_IT( V_desc3 );
    fout << "                   Vector de tip 'munte'\n";
    TEST_IT( V_mtn );

    fout << "\n\n\nBONUS\n\n";
    fout << "STALINSORT este un algoritm sovietic de sortare,\n";
    fout << "care garanteaza sortarea in O(n), indiferent de input\n";
    fout << "eliminand din vector elementele care nu corespund\n\n";


    V = V_rand;
    auto start = chrono::high_resolution_clock::now();
    STALIN_SORT( V );
    auto stop = chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    fout << "STALINSORT:                           " << duration.count() << " ms\n";


    return 0;
}
