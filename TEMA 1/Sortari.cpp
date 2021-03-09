#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;

ifstream f("teste.in");

        // DECLARARE VARIABILE //

unsigned long long int nr_teste, nr_elemente, nr_max;

bool verificare(vector<unsigned> v, int n)
{
    for(int i = 0; i < n - 1; i++)
        if(v[i] > v[i+1])
            return false;
    return true;
}

        // BUBBLE SORT //

void bubble_sort(vector<unsigned> &v)
{
    bool ok = 0;
    while(ok == 0)
    {
        ok = 1;
        for(unsigned long long int i = 0; i < v.size(); i++ )
            if(v[i] > v[i+1])
                {
                    swap(v[i], v[i + 1]);
                    ok = 0;
                }
    }
}

        // BUBBLE SORT //

        // COUNT SORT //

void count_sort(vector<unsigned> &v)
{
    vector<unsigned> auxiliar;

    auxiliar.resize(nr_max);

    for(unsigned long long int i : v)
        auxiliar[i]++;

    int index = 0;

    for(unsigned long long int i = 0; i < auxiliar.size(); i++)
        if(auxiliar[i] != 0)
            for(unsigned long long int j = 1; j <= auxiliar[i]; j++)
                v[index++] = i;
}

        // COUNT SORT //

        // RADIX SORT //

void radix_count_sort(vector<unsigned> &t, int n, int exp)
{
    vector<unsigned> auxiliar;

    auxiliar.resize(nr_max);

    int i;
    int counting[10] = {0};

    for(i = 0; i < n; i ++)
        counting[(t[i] / exp) % 10] ++;

    for(i = 1; i < 10; i ++)
        counting[i] += counting[i - 1];

    for(i = n - 1; i >= 0; i --)
    {
        auxiliar[counting[(t[i] / exp) % 10] - 1] = t[i];
        counting[(t[i] / exp) % 10] --;
    }

    for(i = 0; i < n; i++)
        t[i] = auxiliar[i];

}

void radix_sort(vector<unsigned> &v, int n)
{
        int maxim = v[0];

        for(int i = 1; i < n; i ++)
            if(v[i] > maxim)
                maxim = v[i];

        for(int exp = 1; maxim / exp > 0; exp *= 10)
            radix_count_sort(v, n, exp);
}

        // RADIX SORT //

        // MERGE SORT //

void merge_(vector<unsigned> &t, unsigned long long int starting, unsigned long long int middle, unsigned long long int ending)
{
    unsigned long long int nr_elemente_stanga = middle - starting + 1;
    unsigned long long int nr_elemente_dreapta = ending - middle;

    vector<unsigned> stanga;
    vector<unsigned> dreapta;

    stanga.resize(nr_elemente_stanga);
    dreapta.resize(nr_elemente_dreapta);

    for(unsigned long long int i = 0; i < nr_elemente_stanga; i++)
        stanga[i] = t[starting + i];
    for(unsigned long long int j = 0; j < nr_elemente_dreapta; j++)
        dreapta[j] = t[middle + 1 + j];

    unsigned long long int indice_stanga = 0, indice_dreapta = 0, indice_sortat = starting;

    while(indice_stanga < nr_elemente_stanga && indice_dreapta < nr_elemente_dreapta)
    {
        if(stanga[indice_stanga] <= dreapta[indice_dreapta])
        {
            t[indice_sortat] = stanga[indice_stanga];
            indice_stanga++;
        }
        else
        {
            t[indice_sortat] = dreapta[indice_dreapta];
            indice_dreapta++;
        }
        indice_sortat++;
    }

    while(indice_stanga < nr_elemente_stanga)
    {
        t[indice_sortat] = stanga[indice_stanga];
        indice_stanga++;
        indice_sortat++;
    }

    while(indice_dreapta < nr_elemente_dreapta)
    {
        t[indice_sortat] = dreapta[indice_dreapta];
        indice_dreapta++;
        indice_sortat++;
    }
}


void merge_sort(vector<unsigned> &v, unsigned long long int starting, unsigned long long int ending)
{
    if(starting >= ending)
        return;

    int middle = starting + (ending - starting)/2;
    merge_sort(v, starting, middle);
    merge_sort(v, middle + 1, ending);
    merge_(v, starting, middle, ending);
}

        // MERGE SORT //

        // QUICK SORT //


void quick_sort(vector<unsigned> &v, int starting, int ending)
{
	if(starting < ending)
	{
		int middle = (starting + ending) / 2;
		int aux = v[starting];
		v[starting] = v[middle];
		v[middle] = aux;
		int i = starting, j = ending, d = 0;
		while(i < j)
		{
			if(v[i] > v[j])
			{
				aux = v[i];
				v[i] = v[j];
				v[j] = aux;
				d = 1 - d;
			}
			i += d;
			j -= 1 - d;
		}
		quick_sort(v, starting, i - 1);
		quick_sort(v, i + 1, ending);
	}
}

        // QUICK SORT //

int main()
{
    vector<unsigned> vect;                                          // VECTORUL IN CARE VOM STOCA ELEMENTELE
    std::mt19937 generare(time(NULL));                              // FUNCTIE CARE GENEREAZA NUMERE DIN INTERVALUL [0 , 10 ^ 32]

    f >> nr_teste;

    cout<<"Numarul de teste : "<<nr_teste;

    for(unsigned long long int i = 1; i <= nr_teste; i++)
    {
        f>>nr_elemente>>nr_max;

        vect.resize(nr_elemente);                                   // ALOCAM SPATIU VECTORULUI

        cout<<"\n\nTestul : "<<i;
        cout<<"\n\nNumarul de elemente : "<<nr_elemente;
        cout<<"\nNumarul maxim din vector : "<<nr_max;

        for(unsigned long long int j = 0; j < nr_elemente; j++)
                    vect[j] = generare() % (nr_max+1);              // GENERAM RANDOM ELEMENTE DIN INTERVALUL [0, NR_MAX + 1]

        // BUBBLE SORT

        if(nr_elemente > 10000)
            cout<<"\n\nNumarul de elemente este prea mare pentru bubble_sort().";
        else
        {
            if(nr_max > 18446744073709551614)
                cout<<"\n\nNumarul maxim este prea mare pentru bubble_sort().";
            else
            {
                vector<unsigned> copie;
                copie.resize(nr_elemente);

                for(int j = 0; j < nr_elemente; j++)
                    copie[j] = vect[j];

                auto start = std::chrono::high_resolution_clock::now();

                bubble_sort(copie);

                auto stop = std::chrono::high_resolution_clock::now();

                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

                cout<<"\n\nExecutia functiei bubble_sort() a durat : "<<duration.count()<<" milisecunde.";

                if(verificare(copie, copie.size()) == true)
                    cout<<"\nVectorul este sortat.";
                else
                    cout<<"\nVectorul nu este sortat.";

            }

        }


        // COUNT SORT

        if(nr_elemente >= 100000000)
            cout<<"\n\nNumarul de elemente este prea mare pentru count_sort().";
        else
        {
            if(nr_max > 1000000000)
                cout<<"\n\nNumarul maxim din vector este prea mare pentru count_sort().";
            else
            {
                vector<unsigned> copie;
                copie.resize(nr_elemente);

                for(int j = 0; j < nr_elemente; j++)
                    copie[j] = vect[j];

                auto start = std::chrono::high_resolution_clock::now();

                count_sort(copie);

                auto stop = std::chrono::high_resolution_clock::now();

                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

                cout<<"\n\nExecutia functiei count_sort() a durat : "<<duration.count()<<" milisecunde.";

                if(verificare(copie, copie.size()) == true)
                    cout<<"\nVectorul este sortat.";
                else
                    cout<<"\nVectorul nu este sortat.";
            }
        }


        // RADIX SORT

        if(nr_elemente >= 10000000)
            cout<<"\n\nNumarul de elemente este prea mare pentru radix_sort().";
        else
        {
            if(nr_max > 1000000000)
                cout<<"\n\nNumarul maxim din vector este prea mare pentru radix_sort().";
            else
            {
                vector<unsigned> copie;
                copie.resize(nr_elemente);

                for(int j = 0; j < nr_elemente; j++)
                    copie[j] = vect[j];

                auto start = std::chrono::high_resolution_clock::now();

                radix_sort(copie, copie.size());

                auto stop = std::chrono::high_resolution_clock::now();

                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

                cout<<"\n\nExecutia functiei radix_sort() a durat : "<<duration.count()<<" milisecunde.";

                if(verificare(copie, copie.size()) == true)
                    cout<<"\nVectorul este sortat.";
                else
                    cout<<"\nVectorul nu este sortat.";
            }
        }


        // QUICK SORT

        if(nr_elemente > 10000000)
            cout<<"\n\nNumarul de elemente este prea mare pentru quick_sort().";
        else
        {
            if(nr_max > 18446744073709551614)
                cout<<"\n\nNumarul maxim din vector este prea mare pentru quick_sort().";
            else
            {

            vector<unsigned> copie;
                copie.resize(nr_elemente);

            for(int j = 0; j < nr_elemente; j++)
                copie[j] = vect[j];

            auto start = std::chrono::high_resolution_clock::now();

            quick_sort(copie, 0, copie.size()-1);

            auto stop = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

            cout<<"\n\nExecutia functiei quick_sort() a durat : "<<duration.count()<<" milisecunde.";

            if(verificare(copie, copie.size()) == true)
                cout<<"\nVectorul este sortat.";
            else
                cout<<"\nVectorul nu este sortat.";

            }
        }


        // MERGE SORT

        if(nr_elemente > 10000000)
            cout<<"\n\nNumarul de elemente este prea mare pentru merge_sort().";
        else
        {
            if(nr_max > 18446744073709551614)
                cout<<"\n\nNumarul maxim din vector este prea mare pentru merge_sort().";
            else
            {
                vector<unsigned> copie;
                copie.resize(nr_elemente);

                for(int j = 0; j < nr_elemente; j++)
                    copie[j] = vect[j];

                auto start = std::chrono::high_resolution_clock::now();

                merge_sort(copie, 0, copie.size()-1);

                auto stop = std::chrono::high_resolution_clock::now();

                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

                cout<<"\n\nExecutia functiei merge_sort() a durat : "<<duration.count()<<" milisecunde.";

                if(verificare(copie, copie.size()) == true)
                    cout<<"\nVectorul este sortat.";
                else
                    cout<<"\nVectorul nu este sortat.";
            }
        }

        // C++ SORT

        if(nr_elemente > 100000000)
            cout<<"\n\nNumarul de elemente este prea mare pentru sort().";
        else
        {
            if(nr_max > 18446744073709551614)
                cout<<"\n\nNumarul maxim din vector este prea mare pentru sort().";
            else
            {
                vector<unsigned> copie;
                copie.resize(nr_elemente);

                for(int j = 0; j < nr_elemente; j++)
                    copie[j] = vect[j];

                auto start = std::chrono::high_resolution_clock::now();

                sort(copie.begin(), copie.end());

                auto stop = std::chrono::high_resolution_clock::now();

                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

                cout<<"\n\nExecutia functiei sort() a durat : "<<duration.count()<<" milisecunde.";

                if(verificare(copie, copie.size()) == true)
                    cout<<"\nVectorul este sortat.";
                else
                    cout<<"\nVectorul nu este sortat.";

            }
        }

    }

    return 0;
}

// !!! LIMITELE AU FOST PUSE ASTFEL INCAT EXECUTIA PROGRAMULUI SA NU DUREZE FOARTE MULT !!! //
