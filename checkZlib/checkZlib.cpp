// checkZlib.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdint.h>
#include <string>  
#include "CompressionZutil.h"
#define nMaxFileSizeToread 1024*1024*1024
#define nBuffer 16*1024*1024
using namespace carbonite::dedupexperiment;

uint64_t getSizeForFile(std::string fileName);
int readContents(std::string fileName,unsigned char* P,uint64_t sizeFile);
int _tmain(int argc, _TCHAR* argv[])
{

	std::string fName="hp_scanDS_9129942834";

	uint64_t sizeFile=getSizeForFile(fName);
	if(sizeFile>0){
		fprintf(stderr, "File Length >0!\n");
		unsigned char* P=new unsigned char[sizeFile];
		if(readContents(fName,P,sizeFile)==0){
			fprintf(stderr, "FileContent read!\n");
			uint64_t sCompressedSizeZUTIL=CompressionZutil::prepareCompressZUTILInBlocksOf13M(P,sizeFile);
			fprintf(stderr, "UnCompressed Size ::%llu!\n",sizeFile);
			fprintf(stderr, "Compressed Size ::%llu!\n",sCompressedSizeZUTIL);
		}
		delete P;
	}
	

	fwprintf(stdout,L"Lets roll");
	return 0;
}
int readContents(std::string fileName,unsigned char* P,uint64_t sizeFile){
	FILE *fp=NULL;
	fp = fopen(fileName.c_str(), "rb");
	if (NULL==fp) {

		fprintf(stderr, "Unable to open file ::%s to get file length!\n",fileName.c_str());
		return 1;
	}
	uint64_t nBytesRead4File=0L;
	//normal read
	//nBytesRead4File = fread(P, 1, sizeFile, fp);
	
	if(sizeFile<=(uint64_t)nMaxFileSizeToread){//read all of file

										//if file size is less than nBuffer
										if(sizeFile<=nBuffer){
											nBytesRead4File = fread(P, 1, sizeFile, fp);
										}else{//if file size is bigger than nBuffer
											//read in loops
											uint64_t nBytesReadInPass=0L;
											while(nBytesRead4File<sizeFile){//read in buffers
												nBytesReadInPass=0L;
												if(nBytesRead4File+nBuffer<sizeFile){//read nBuffer
													nBytesReadInPass = fread(P+nBytesRead4File, 1, nBuffer, fp);
												}else{//read remaining size
													nBytesReadInPass= fread(P+nBytesRead4File, 1, sizeFile-nBytesRead4File, fp);
												}
												nBytesRead4File+=nBytesReadInPass;
											}
										}
									}
	fclose( fp );
	if(nBytesRead4File==sizeFile){
		fprintf(stderr, "Read Success!\n");
		return 0;
	}
	return 1;
}
uint64_t getSizeForFile(std::string fileName){
	uint64_t length=0L;
	FILE *fp=NULL;
	fp = fopen(fileName.c_str(), "rb");
	if (NULL==fp) {

		fprintf(stderr, "Unable to open file ::%s to get file length!\n",fileName.c_str());
		return length;
	}
	/* fseek() to SEEK_END and then ftell() to get position */
	_fseeki64(fp, 0, SEEK_END);
	length=_ftelli64(fp);
	fclose( fp );

	return length;
}
