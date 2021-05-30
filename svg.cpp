#include "svg.h"
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
double image_width (size_t number_count, double BLOCK_WIDTH)
{
    double IMAGE_WIDTH;
    cerr << "Enter IMAGE_WIDTH:";
    cin >> IMAGE_WIDTH;
    while(IMAGE_WIDTH < 70 || IMAGE_WIDTH > 800 || IMAGE_WIDTH < 1/3*(number_count*BLOCK_WIDTH))
    {
        cerr << "invalid input, please enter again";
        cerr << "Enter SCREEN_WIDTH:";
        cin >> IMAGE_WIDTH;
    }
    return IMAGE_WIDTH;
}
void show_histogram_svg(const vector <size_t>& bins, double bin_count, size_t  number_count, string& stroke, string& fill)
{
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    double IMAGE_WIDTH = image_width(number_count, BLOCK_WIDTH);
    double top = 0;
    size_t  Max = bins[0];
    for (size_t  j=1; j<bin_count; j++)
    {
        if (bins[j]>Max)
            Max = bins[j];
    }
    const bool scaling_up = Max > MAX_ASTERISK;
    if (scaling_up)
    {
        const double scaling = (double)MAX_ASTERISK / Max;
        svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
        for (size_t bin : bins)
        {
            auto  height = (size_t)(bin * scaling);
            const double bin_width = BLOCK_WIDTH * bin;
            svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
            svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT,"blue", "#ffeeee");
            top += BIN_HEIGHT;
        }
    }
    else
    {
        for (size_t bin : bins)
        {
            const double bin_width = BLOCK_WIDTH * bin;
            svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
            svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, stroke, fill);
            top += BIN_HEIGHT;
        }

    }
    svg_end();
}
