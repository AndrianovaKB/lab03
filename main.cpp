#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <curl/curl.h>
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
read_input(istream& in, bool promt) {
    Input data;

    cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;
    if(promt)
    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);
    if(promt)
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
int main(int argc, char* argv[])
{
    //Input input;
    size_t  number_count;
    cout << "argc=" << argc;
        if (argc > 1)
    {
        cout << argc << endl;
        for(size_t i=0; i<argc; i++)
        cout << argv[i]<<" ";

        curl_global_init(CURL_GLOBAL_ALL);
        CURL *curl = curl_easy_init();
        if(curl)
        {
            CURLcode res;
            curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            if(res)
            {
                cout << curl_easy_strerror(res);
                exit(1);
            }
        }
        return 0;
    }
    const auto input = read_input(cin, true);
    size_t  bin_count;
    const auto bins = make_histogram(input);
    //show_histogram_text(bins, MAX_ASTERISK);
    string stroke;
    string fill;
    show_histogram_svg(bins, MAX_ASTERISK, number_count,stroke,fill);
    return 0;
}
