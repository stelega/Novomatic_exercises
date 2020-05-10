#include <vector>
#include <array>


// Funkcja ustawiająca indeks elementu wektora weights, dla którego wartość jest najmniejsza, na początek tablicy arr.
inline void mySort( std::array<int, 4> &arr, const std::vector<float> &weights ){
    int i, min = 0;
    // Szukanie indeksu, dla którego wartość w wektorze weights jest najmniejsza.
    for( i=1; i<4; i++ ){
        if( weights[arr[min]] > weights[arr[i]] ){
           min = i;
        }
    }

    // Swapowanie znalezionego indeksu z indeksem na początku tablicy.
    if( min!=0 ){
        int tmp = arr[min];
        arr[min] = arr[0];
        arr[0] = tmp;
    }    
}


// Funkcja zwracająca tablicę 4 indeksów, dla których wartość w wektorze weights jest największa.
std::array<int, 4> pickMorphs(const std::vector<float> &weights){
    // Jeżeli wektor ma mniej niż 4 elementy funkcja zwraca tablicę {-1, -1, -1, -1}
    if(weights.size() < 4)
        return std::array<int, 4>({-1, -1, -1, -1});

    // Przypisanie do tablicy pierwszych 4 indeksów wektora weights i posortowanie ich.
    std::array<int, 4> arr( {0, 1, 2, 3} );
    mySort(arr, weights);

    // Przejście po reszcie tablicy, w celu znalezienia indeksów,
    // dla których wartość wektora weights będzie większa.
    for( int i=4; i<weights.size(); i++ ){
        if( weights[i] > weights[arr[0]] ){
            arr[0] = i;
            mySort(arr, weights);
        }
    }

    return arr;
}
