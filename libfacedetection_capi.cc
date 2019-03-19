// Copyright 2019 <chaishushan{AT}gmail.com>. All rights reserved.
// Use of this source code is governed by a Apache-style
// license that can be found in the LICENSE file.

extern "C" {
	#include "libfacedetection_capi.h"
}

#include "./libfacedetection/src/facedetectcnn.h"

#include <string>

// define the buffer size. Do not change the size!
#define DETECT_BUFFER_SIZE 0x20000

const libfacedetection_capi_result_t* libfacedetection_capi_facedetect_rgb(
	uint8_t * rgb, int width, int height, int step
) {
	std::string sBuffer;
	sBuffer.resize(DETECT_BUFFER_SIZE);

	unsigned char* pBuffer = (unsigned char *)sBuffer.data();
	int* pResults = facedetect_cnn(pBuffer, rgb, width, height, step);
	return (libfacedetection_capi_result_t*)(pResults);
}

const libfacedetection_capi_result_t* libfacedetection_capi_facedetect_rgba(
	uint8_t* rgba, int width, int height, int step
) {
	std::string rgbBuffer;
	rgbBuffer.resize(width*height*3);

	uint8_t* rgb = (uint8_t*)rgbBuffer.data();
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			*rgb++ = *rgba++; // r
			*rgb++ = *rgba++; // g
			*rgb++ = *rgba++; // b
			rgba++;           // a
		}
	}

	std::string sBuffer;
	sBuffer.resize(DETECT_BUFFER_SIZE);

	unsigned char* pBuffer = (unsigned char *)sBuffer.data();
	int* pResults = facedetect_cnn(pBuffer, rgb, width, height, step);
	return (libfacedetection_capi_result_t*)(pResults);
}

int libfacedetection_capi_result_len(libfacedetection_capi_result_t* self) {
	int* pResults = (int*)(self);
	return pResults? *pResults: 0;
}

libfacedetection_capi_bool_t libfacedetection_capi_result_get(
	libfacedetection_capi_result_t* self, int i,
	libfacedetection_capi_face_t* face
) {
	int* pResults = (int*)(self);
	int n = pResults? *pResults: 0;

	if(i < 0 || i >= n) return 0;

	short * p = ((short*)(pResults+1))+142*i;
	face->x = p[0];
	face->y = p[1];
	face->w = p[2];
	face->h = p[3];
	face->neighbors = p[4];
	face->angle = p[5];

	return 1;
}
