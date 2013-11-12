
#pragma once
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "zlib.h"
#include <stdint.h>



#define CHUNK 16384

namespace carbonite{
	namespace dedupexperiment{
		class CompressionZutil
		{
		public:
			CompressionZutil(void);
			~CompressionZutil(void);
			static int def(FILE *source, FILE *dest, int level);
			static uint64_t defFromMemory(unsigned char *first,uint64_t size, int level);
			static int inf(FILE *source, FILE *dest);
			static void zerr(int ret);
			static uint64_t prepareCompressZUTIL(unsigned char *first,uint64_t size);
			static uint64_t prepareCompressZUTILInBlocksOf13M(unsigned char *first,uint64_t size);
			static uint64_t prepareCompressZUTILInBlocksOf256K(unsigned char *first,uint64_t size);
		};
	}
}

