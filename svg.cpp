#include "svg.h"
#include <string>
#include <sstream>
#include <windows.h>

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;
void
svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}
void
svg_text(double left, double baseline, string text)
{
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>";
}
void svg_rect(double x, double y, double width, double height,string stroke, string fill)
{
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height <<"' stroke='"<<stroke<<"' fill='"<< fill<<"'/>";
}
void
svg_end()
{
    cout << "</svg>\n";
}
/*double input_image_width(size_t number_count, double BLOCK_WIDTH, double& IMAGE_WIDTH,istream& in)
{
    //double IMAGE_WIDTH;
    cerr << "Enter IMAGE_WIDTH:";
    in >> IMAGE_WIDTH;
    image_width (number_count, BLOCK_WIDTH, IMAGE_WIDTH, cin);
    return IMAGE_WIDTH;
}*/
double image_width (size_t number_count, double BLOCK_WIDTH,  istream& in)
{
    int image_width;
    in >> image_width;
    while(image_width < 70 || image_width > 800 || image_width < 1/3*(number_count*BLOCK_WIDTH))
    {
        cerr << "invalid input, please enter again" << endl;
        cerr << "Enter SCREEN_WIDTH:";
        in >> image_width;
    }

    return image_width;
}
string
make_info_text() {
    stringstream buffer;

    DWORD info = GetVersion();
    DWORD mask = 0x0000ffff;
    DWORD mask_2 = 0x000000ff;
    DWORD platform = info >> 16;
    DWORD version = info & mask;
    if ((info & 0x80000000) == 0)
    {
        DWORD version_major = version & mask_2;
        DWORD version_minor = version >> 8;
        DWORD build = platform;
        buffer << "Windows v" << version_major << "." << version_minor << " (build " << build << ") \n ";
    }

    DWORD size = MAX_COMPUTERNAME_LENGTH+1;
    char computer_name[size];
    GetComputerNameA(computer_name, &size);
    buffer << "Computer name: " << computer_name;

    return buffer.str();
}

void show_histogram_svg(const vector <size_t>& bins, double bin_count, size_t  number_count, string& stroke, string& fill)
{
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    double IMAGE_WIDTH = image_width(number_count, BLOCK_WIDTH,  cin);
    cerr << "IMAGE_WIDTH=" << IMAGE_WIDTH;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    size_t  Max = bins[0];
    for (size_t  j=1; j<bin_count; j++)
    {
        cerr <<"bins["<<j<<"]="<<bins[j]<<endl;
        if (bins[j]>Max)
            Max = bins[j];
    }
    const bool scaling_up = (Max*BLOCK_WIDTH) > (IMAGE_WIDTH-TEXT_WIDTH);
    if (scaling_up)
    {
        const double scaling = (double)(IMAGE_WIDTH-TEXT_WIDTH) / (Max*BLOCK_WIDTH);
        cerr << "scaling="<<scaling;
        cerr << "MAX_ASTERISK="<<MAX_ASTERISK;
        cerr << "Max="<<Max;
        for (size_t bin : bins)
        {
            cerr <<"bin="<<bin<<"\n";
            auto  height = (size_t)(bin * scaling);
            cerr << "height=" << height<<"\n";
            const double bin_width = BLOCK_WIDTH * height;
            cerr << "bin_width=" << bin_width<<"\n";
            svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
            svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "blue", "#ffeeee");
            top += BIN_HEIGHT;
        }
    }
    else
    {
        for (size_t bin : bins)
        {
            const double bin_width = BLOCK_WIDTH * bin;
            //cerr << "bin_width=" << bin_width;
            svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
            svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "blue", "#ffeeee");//stroke, fill);
            top += BIN_HEIGHT;
        }
    }
    svg_text(0, top + TEXT_BASELINE, make_info_text());
    svg_end();
}
