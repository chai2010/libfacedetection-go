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

int libfacedetection_capi_facedetect_rgb(
	uint8_t* rgb, int width, int height, int step,
	libfacedetection_capi_face_t* face_buf,
	int face_buf_len
) {
	std::string sBuffer;
	sBuffer.resize(DETECT_BUFFER_SIZE);

	unsigned char* pBuffer = (unsigned char *)sBuffer.data();
	int* pResults = facedetect_cnn(pBuffer, rgb, width, height, step);

	int i;
	for(i = 0; i < (pResults ? *pResults: 0) && i < face_buf_len; i++) {
		short * p = ((short*)(pResults+1))+142*i;
		face_buf[i].x = p[0];
		face_buf[i].y = p[1];
		face_buf[i].w = p[2];
		face_buf[i].h = p[3];
		face_buf[i].neighbors = p[4];
		face_buf[i].angle = p[5];
	}
	return i;
}
