#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include "histogram.h"
#include "histogram.cpp"
#include "svg.h"

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;
using namespace std;

vector<double>
input_numbers(istream& in, size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
    return result;
}
Input
read_input(istream& in) {
    Input data;

    cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;

    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    cerr << "Enter bin count: ";
    in >> data.bin_count;
    return data;
}
vector <size_t> make_histogram(const Input& data)
{
    double min;
    double max;
    vector <size_t> result(data.bin_count);
    find_minmax(data.numbers, min, max);
    for (double number : data.numbers)
    {
        size_t bin = (size_t)((number - min) / (max - min) * data.bin_count);
        if (bin == data.bin_count)
        {
            bin--;
        }
        result[bin]++;
    }
    return result;
}
void show_histogram_text(vector <size_t> bins, const size_t MAX_ASTERISK)
{
    size_t bin_count = bins.size();
    size_t  Max = bins[0];
    for (size_t  j=1; j<bin_count; j++)
    {
        if (bins[j]>Max)
            Max = bins[j];
    }
    for (size_t  j=0; j<bin_count; j++)
    {
        if(bins[j]>=100)
            cout<<bins[j];
        if (bins[j]<10)
            cout <<"  "<< bins[j];
        else if (bins[j]<100)
            cout<< " "<< bins[j] ;
        cout << "|";
        if(Max>MAX_ASTERISK)
        {
            size_t  height = MAX_ASTERISK * (static_cast<double>(bins[j]) / Max);
            for (size_t  a=0; a<height; a++)
            {
                cout << "*";
            }
        }
        else
            for(size_t a=0; a<bins[j]; a++)
                cout << "*";
        cout << endl;
    }
}
int main()
{
    Input input;
    size_t  number_count;
    input = read_input(cin);
    size_t  bin_count;
    const auto bins = make_histogram(input);
    //show_histogram_text(bins, MAX_ASTERISK);
    string stroke;
    string fill;
    show_histogram_svg(bins, MAX_ASTERISK, number_count,stroke,fill);
    return 0;
}
