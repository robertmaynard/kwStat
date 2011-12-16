/*============================================================================
  KWStat
  Copyright 2011 Kitware, Inc.

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#include <stdint.h>
#include <string>

#if defined(__GNUC__)
//a great read on 64bit file support for Linux is:
//www.gnu.org/s/libc/manual/html_node/Feature-Test-Macros.html
#include <inttypes.h>

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
#include <inttypes.h>

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

namespace kw
{

class stat
  {
  public:
  stat(const char* fn):
    Exists_(false)
    {
    this->init(fn);
    }

  stat(const std::string &fn):
    Exists_(false)
    {
    this->init(fn.c_str());
    }

  //copy constructors
  stat(const stat &other):
    Exists_(other.Exists_),
    Stat_(other.Stat_)
    {
    
    }

  //assignment operator
  stat & operator= (const stat &other)
    {
    if(this!=&other)
      {
      this->Exists_ = other.Exists_;
      this->Stat_ = other.Stat_;
      }
    return *this;
    }

  //destructor
  ~stat(){}

  //check if we have a valid stat object
  bool fileExists( ) const { return Exists_;}

  //return the length of the file
  int64_t fileLength() const
    {
    return this->fileExists() ? this->Stat_.st_size : -1;    
    };

  //return the last modified time of the file
  int64_t modifiedTime() const
    {
    return this->fileExists() ? this->Stat_.st_mtime : -1;
    }

  //return the last status time of the file
  int64_t statusTime() const
    {
    return this->fileExists() ? this->Stat_.st_ctime : -1;
    }

  //return the last access time of the file
  int64_t accessTime() const
    {
    return this->fileExists() ? this->Stat_.st_atime : -1;
    }

  private:
  //setup kwStat
  #if defined(KW_USE_GNUC_STAT_64)
  typedef struct stat64 kwStat;
# define stat_func stat64  
  #elif defined(KW_USE_MS_STAT_64)
  typedef struct _stat64 kwStat;
# define stat_func _stat64
  #elif defined(KW_USE_MS_STAT_I64)
  typedef struct _stat32i64 kwStat;
# define stat_func _stat32i64
  #else
  typedef struct stat kwStat;
# define stat_func stat
  #endif

  bool Exists_;
  kwStat Stat_;

  void init(const char* fn)
    {
    int v = stat_func(fn,&this->Stat_);
    this->Exists_ = (v == 0);
    }
};

}//end namespace

