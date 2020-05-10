#pragma once
#include <iostream>


// Szablon klasy pełniącej rolę bufora cyklicznego
template<typename T>
class MyBuffer{

public:
    // Konstruktor przyjmujący rozmiar bufora. Alokuje pamięć na podaną liczbę elementów typu T.
    // W wypadku podania liczby ujemnej lub zera wyrzuca błąd.
    MyBuffer( long );
    // Destruktor zwalniający pamięć zaalokowaną w konstruktorze.
    ~MyBuffer();

    // Metoda przyjmująca stałą referencję na obiekt typu T. Zapisuje przekazany obiekt w buforze,
    // chyba że bufor jest pełny. W takim wypadku metoda wypisuje informacje o przepełnieniu bufora.
    void AddElement( const T& );
    // Metoda zwracająca i usuwająca pierwszy element bufora.
    const T& GetElement();
    // Metoda zwracająca liczbę elementów znajdujących się w buforze.
    long GetNumberOfElements() const;
    // Metoda zwracająca pojemność bufora.
    long GetCapacity() const;
    // Metoda czyszcząca bufor.
    void ClearBuffer();

private:
    // Wskaźnik na tablicę objektów typu T.
    T* m_buffer;
    // Zmienna przechowująca pojemnośc bufora.
    long m_capacity; 
    // Zmienna przechowująca indeks pierwszego elementu w buforze.
    long m_beg = 0;
    // Zmienna przechowująca liczbę o 1 większą niż indeks ostatniego elementu w buforze.
    long m_end = 0;
    // Zmienna przechowująca aktualny rozmiar bufora.
    long m_size = 0;

    // Metoda inkrementująca wskaźnik w zależności od jego aktualnej wartości.
    void Increment( long& );
};



template <typename T>
MyBuffer<T>::MyBuffer( long capacity ) : m_capacity(capacity){
    if( capacity <1 )
        throw std::range_error("rozmiar bufora musi być większy niż 0");
    else
        m_buffer = new T[capacity];
}


template <typename T>
MyBuffer<T>::~MyBuffer(){
    delete[] m_buffer;
}


template <typename T>
void MyBuffer<T>::AddElement(const T& obj ){
    if( m_size == m_capacity )
        std::cout << "Bufor pełny, nie można dodać elementu." << std::endl;

    else{
        m_buffer[m_end] = obj;
        Increment(m_end);
        m_size++;
    }
}


template <typename T>
const T& MyBuffer<T>::GetElement(){
    if( !m_size )
        throw std::range_error("Brak elementów w buforze, nie usunięto żadnego elementu.");
    
    long tmp = m_beg;
    Increment(m_beg);
    m_size--;

    return m_buffer[tmp];
}


template <typename T>
long MyBuffer<T>::GetNumberOfElements() const{
    return m_size;
}


template <typename T>
long MyBuffer<T>::GetCapacity() const{
    return m_capacity;
}


template <typename T>
void MyBuffer<T>::ClearBuffer(){
    m_beg = 0;
    m_end = 0;
    m_size = 0;
}


template <typename T>
void MyBuffer<T>::Increment(long& x){
    if( x == m_capacity-1 )
        x = 0;
    else
        x++;
}
