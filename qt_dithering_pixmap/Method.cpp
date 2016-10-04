#include "Method.h"
#include <cmath>

double Method::getBitDepth(int depth)
{
   return (pow(2, depth) - 1);
}
