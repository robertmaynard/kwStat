
#include "../kwStat.h"
#include <assert.h>

int main(int argc, char **argv)
{
  const char* fname = "test.txt";
  kwStat ks;

  //this needs to be configured to properly
  //check 32bit vs 64bit

  // check that off_t can hold 2^64 - 1
  off_t temp = (((off_t)1 << 62) + (((off_t)1<<62) -1));
  assert(temp==(((off_t)1 << 62) + (((off_t)1<<62) -1)));

  // check that the st_size can hold the temp
  ks.st_size = temp;
  assert(ks.st_size == temp);

  return 0;
}

