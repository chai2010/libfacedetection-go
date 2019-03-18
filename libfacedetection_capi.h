// Copyright 2019 <chaishushan{AT}gmail.com>. All rights reserved.
// Use of this source code is governed by a Apache-style
// license that can be found in the LICENSE file.

#ifndef libfacedetection_capi_h_
#define libfacedetection_capi_h_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct libfacedetection_capi_face_t {
	int x;
	int y;
	int w;
	int h;
	int neighbors;
	int angle;
} libfacedetection_capi_face_t;

int libfacedetection_capi_facedetect_rgb(
	uint8_t * rgb, int width, int height, int step,
	libfacedetection_capi_face_t* face_buf,
	int face_buf_len
);

#ifdef __cplusplus
}
#endif
#endif // libfacedetection_capi_h_
