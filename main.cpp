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

vector<double> input_numbers(size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }
    return result;
}
vector <size_t> make_histogram(const vector<double>& numbers, size_t bin_count)
{
    double min;
    double max;
    vector <size_t> bins(bin_count);
    find_minmax(numbers, min, max);
    for (double number : numbers)
    {
        size_t bin = (size_t)((number - min) / (max - min) * bin_count);
        if (bin == bin_count)
        {
            bin--;
        }
        bins[bin]++;
    }
    return bins;
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
    double IMAGE_WIDTH;
    size_t  number_count;
    cerr <<  "Enter number count: ";
    cin >>  number_count;
    const auto numbers = input_numbers(number_count);
    size_t  bin_count;
    cerr <<  "Enter bin_count: ";
    cin >>  bin_count;
    //vector <size_t> bins (bin_count);
    const auto bins = make_histogram(numbers, bin_count);
    //show_histogram_text(bins, MAX_ASTERISK);
    string stroke;
    string fill;
    show_histogram_svg(bins, MAX_ASTERISK, number_count,stroke,fill);
    return 0;
}
