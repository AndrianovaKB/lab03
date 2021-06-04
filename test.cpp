#include "histogram.h"
#include "svg.h"
#include <cassert>
#include <math.h>
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
}
//модульные тесты
void
test ()
{
    double IMAGE_WIDTH=400;
    image_width (5, 10, IMAGE_WIDTH, cin);
}
void
test1 ()
{
    double IMAGE_WIDTH = 1000;
    image_width (5, 10, IMAGE_WIDTH, cin);
}
void
test2 ()
{
    double IMAGE_WIDTH = 30;
    image_width (5, 10, IMAGE_WIDTH, cin);
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
