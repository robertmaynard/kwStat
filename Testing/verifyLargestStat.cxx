
#include "../kwStat.h"
#include <assert.h>

#include <iostream>


int main(int argc, char **argv)
{
  kwStat ks;

  //basically this should confirm that we are using the largest
  //stat that is aviable
  assert(sizeof(ks.st_size)==8);

  std::cout << __SIZEOF_LONG_LONG__ << std::endl;

  return 0;
}


