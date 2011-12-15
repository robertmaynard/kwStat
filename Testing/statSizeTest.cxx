
#include "../kwStat.h"
#include <assert.h>

int main(int argc, char **argv)
{
  kwStat ks;

  //basically this should confirm that we are using the right stat version
  //based on the off_t size
  assert(sizeof(off_t)==sizeof(ks.st_size));

  off_t temp;
  if(sizeof(off_t)==4)
    {
    // check that off_t can hold 2^32 - 1
    temp = (((off_t)1 << 32) + (((off_t)1<<32) -1));
    assert(temp==(((off_t)1 << 32) + (((off_t)1<<32) -1)));
    }
  else
    {
    // check that off_t can hold 2^64 - 1
    temp = (((off_t)1 << 62) + (((off_t)1<<62) -1));
    assert(temp==(((off_t)1 << 62) + (((off_t)1<<62) -1)));
    }

  // check that the st_size can hold the temp
  ks.st_size = temp;
  assert(ks.st_size == temp);

  return 0;
}

