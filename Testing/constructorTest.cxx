#include "../kwStat.h"
#include <assert.h>

int main(int argc, char **argv)
{
 
  const char* fname = "test.txt";
  kw::stat s(fname);
  assert(s.fileExists()==true);
  assert(s.fileLength()==0);

  kw::stat s2(s);
  assert(s2.fileExists()==s.fileExists());
  assert(s2.fileLength()==s.fileLength());
  assert(s2.modifiedTime()==s.modifiedTime());
  assert(s2.statusTime()==s.statusTime());
  assert(s2.accessTime()==s.accessTime());
  
  kw::stat s3 = s2;
  assert(s3.fileExists()==s2.fileExists());
  assert(s3.fileLength()==s2.fileLength());   
  assert(s3.modifiedTime()==s2.modifiedTime());
  assert(s3.statusTime()==s2.statusTime());
  assert(s3.accessTime()==s2.accessTime());

  return 0;
}


