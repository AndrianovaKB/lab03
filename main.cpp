#include <iostream>
#include <vector>
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
void find_minmax(vector<double> numbers, double& min, double& max) {
    min = numbers[0];
    max = numbers[0];
    for (double number : numbers) {
        if (number < min) {
            min = number;
        }
        if (number > max) {
            max = number;
        }
    }}
void make_histogram()
 for (size_t  i = 0; i < number_count; i++)
    {
        bool  found = false;
        for (size_t j = 0; (j < bin_count - 1) && !found; j++)
        {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;
            if ((lo <= numbers[i]) && (numbers[i] < hi))
            {
                bins[j]++;
                found = true;
            }
        }
        if (!found)
        {
            bins[bin_count - 1]++;
        }
    }

int main()
{
    size_t  number_count;
    cerr <<  "Enter number count: ";
    cin >>  number_count;
    const auto numbers = input_numbers(number_count);
    double min;
    double max;
    find_minmax(numbers, min, max);
    size_t SCREEN_WIDTH;
    cerr << "Enter SCREEN_WIDTH:";
    cin >> SCREEN_WIDTH;
    while(SCREEN_WIDTH < 7 || SCREEN_WIDTH > 80 || SCREEN_WIDTH < 1/3*(number_count))
    {
        cerr << "invalid input, please enter again";
        cerr << "Enter SCREEN_WIDTH:";
        cin >> SCREEN_WIDTH;
    }
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;
    size_t  bin_count;
    cerr <<  "Enter bin_count: ";
    cin >>  bin_count;
    vector <size_t> bins (bin_count);
    double bin_size = (max - min) / bin_count;

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
        if(number_count>MAX_ASTERISK)
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
    return 0;
}
