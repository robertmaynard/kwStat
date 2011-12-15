#include "../kwStat.h"
#include <assert.h>

int main(int argc, char **argv)
{
  const char* fname = "test.txt";
  kwStat ks;
  int ret = kw_stat(fname,&ks);
  assert(ret==0);

  //make sure the st_size is a valid number
  assert(ks.st_size==0);

  return ret;
}


