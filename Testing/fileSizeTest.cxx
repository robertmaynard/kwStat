#include "../kwStat.h"
#include <assert.h>

int main(int argc, char **argv)
{
 
  const char* fname = "test.txt";
  kw::stat s(fname);
  assert(s.fileExists()==true);
  assert(s.fileLength()==0);
  return 0;
}


