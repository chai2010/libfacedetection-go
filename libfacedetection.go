// Copyright 2019 <chaishushan{AT}gmail.com>. All rights reserved.
// Use of this source code is governed by a Apache-style
// license that can be found in the LICENSE file.

package libfacedetection

//#include "libfacedetection_capi.h"
import "C"
import (
	"image"
)

func init() {
	if false {
		C.libfacedetection_capi_facedetect_rgb(nil, 0, 0, 0, nil, 0)
	}
}

type Face struct {
	X         int
	Y         int
	W         int
	H         int
	Neighbors int
	Angle     int
}

func DetectFace(m *image.RGBA) []Face {
	return nil // todo
}
