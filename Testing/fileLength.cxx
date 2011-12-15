#include "../kwStat.h"
#include <iostream>

int main(int argc, char **argv)
{
  const char* fname = "test.txt";
  kwStat ks;
  int ret = kw_stat(fname,&ks);
  if (!ret)
    {
    std::cout << "failed to open file" << std::endl;
    }
  else
    {
    off_t size = ks.st_size;
    std::cout << "File test.txt has a length of " << size << std::endl;
    }
  return ret;
}

