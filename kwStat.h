/*============================================================================
  KWStat
  Copyright 2011 Kitware, Inc.

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/

#if defined(__GNUC__)
//a great read on 64bit file support for Linux is:
//www.gnu.org/s/libc/manual/html_node/Feature-Test-Macros.html

#if  defined(_LARGEFILE64_SOURCE) && \
   (defined(_FILE_OFFSET_BITS) && _FILE_OFFSET_BITS < 64)
//we always want to use the 64bit supported stat if it exists.
//On 32Bit linux we need to see if LargeFile support has been enabled.
//if it has been enabled and _FILE_OFFSET_BITS is set to 32 we call stat64
//if _FILE_OFFSET_BITS is equal to 64 than stat is stat64
#  define KW_USE_GNUC_STAT_64
# endif

//end Linux

#elif defined(_WIN64) || defined (_M_IA64) || defined (_M_X64)
//windows 64bit

#if defined(_MSC_VER)
//MS Visual Studio
# define KW_USE_MS_STAT_64
#endif

#elif defined(_WIN32) || defined (_M_IX86)
//windows 32bit

#if defined(_MSC_VER)
//MS Visual Studio
# define KW_USE_MS_STAT_I64
#endif

#elif defined(__APPLE__)
// Mac OSX

//on OSX SDK 10.5 stat64 needs to be used if using 64bits.
//on OSX SDK 10.6 you need to check the _DARWIN_FEATURE_64_BIT_INODE
//stat should be used, as stat64 is deprecated!
#if !defined(_DARWIN_FEATURE_64_BIT_INODE)
# define KW_USE_GNUC_STAT_64
# endif

#endif


//now that we know what we want include stat

#include <sys/types.h>
#include <sys/stat.h>


//setup kwStat
#if defined(KW_USE_GNUC_STAT_64)

typedef struct stat64 kwStat;

extern int kw_stat(const char* fn, kwStat *ks)
  {
  return stat64(fn,ks);
  }

#elif defined(KW_USE_MS_STAT_64)

typedef struct _stat64 kwStat;

extern int kw_stat(const char* fn, kwStat *ks)
  {
  return _stat64(fn,ks);
  }

#elif defined(KW_USE_MS_STAT_I64)

typedef struct _stat32i64 kwStat;

extern int kw_stat(const char* fn, kwStat *ks)
  {
  return _stat32i64(fn,ks);
  }

#else

typedef struct stat kwStat;

extern int kw_stat(const char* fn, kwStat *ks)
  {
  return stat(fn,ks);
  }
#endif

namespace kw
{

bool file_exists(const char* fn)
  {
  kwStat ks;
  return static_cast<bool>(kw_stat(fn,&ks));
  }

int64_t file_length(const char* fn)
  {
  kwStat ks;
  int ret = kw_stat(fn,&ks);
  if(ret==0)
    {
    return ks.st_size;
    }
  else
    {
    return -1;
    }
  }

}//end namespace

