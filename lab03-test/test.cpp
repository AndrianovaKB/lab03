#include "histogram.h"
#include "svg.h"
#include <cassert>
#include <math.h>
#include <sstream>
#include <string>
#include <iostream>
void
test_positive()
{
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}
void
test_negative()
{
    double min = 0;
    double max = 0;
    find_minmax({-1,-2, -3}, min, max);
    assert(min == -3);
    assert(max == -1);
}
void
test_similar()
{
    double min = 0;
    double max = 0;
    find_minmax({3, 3, 3}, min, max);
    assert(min == 3);
    assert(max == 3);
}
void
test_single()
{
    double min = 0;
    double max = 0;
    find_minmax({1}, min, max);
    assert(min == 1);
    assert(max == 1);
}
void
test_empty()
{
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min == 0);
    assert(max == 0);
}
//модульные тесты
void
test ()
{
    //double IMAGE_WIDTH=400;
    stringstream iw ("400");
    double res = image_width (5, 10, iw);
    assert(res == 400);
}
void
test1 ()
{
    //double IMAGE_WIDTH = 1000;
    stringstream iw ("1000");
    double res = image_width (5, 10, iw);
    stringstream im ("500");
    res = image_width (5, 10, im);
    assert(res == 500);

}
void
test2 ()
{
    //double IMAGE_WIDTH = 30;
    stringstream iw ("30");
    double res = image_width (5, 10, iw);
    assert(res == 30);
}
int
main ()
{
    double IMAGE_WIDTH;
    test_positive();
    test_negative();
    test_single();
    test_empty();
    test();
    test1();
    test2();
}
