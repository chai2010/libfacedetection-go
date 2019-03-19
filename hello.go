// Copyright 2019 <chaishushan{AT}gmail.com>. All rights reserved.
// Use of this source code is governed by a Apache-style
// license that can be found in the LICENSE file.

// +build ignore

package main

import (
	"fmt"
	"image"
	"image/color"
	"image/draw"
	_ "image/jpeg"
	"image/png"
	"log"
	"os"

	"github.com/chai2010/libfacedetection-go"
)

func main() {
	m := GetImage("./libfacedetection/images/keliamoniz2.jpg")
	rgb, w, h := libfacedetection.NewRGBImageFrom(m)

	faces := libfacedetection.DetectFaceRGB(rgb, w, h, w*3)
	fmt.Printf("%#v\n", faces)

	if len(faces) > 0 {
		b := m.Bounds()
		m2 := image.NewRGBA(b)

		for y := b.Min.Y; y < b.Max.Y; y++ {
			for x := b.Min.X; x < b.Max.X; x++ {
				m2.Set(x, y, m.At(x, y))
			}
		}

		x1 := faces[0].X
		y1 := faces[0].Y
		x2 := faces[0].W + x1
		y2 := faces[0].H + y1

		DrawRect(m2, x1, y1, x2, y2)
		SaveImage(m2, "a.out.png")
	}
}

func GetImage(path string) image.Image {
	r, err := os.Open(path)
	if err != nil {
		log.Fatal(err)
	}
	defer r.Close()

	m, _, err := image.Decode(r)
	if err != nil {
		log.Fatal(err)
	}
	return m
}

func SaveImage(m image.Image, path string) {
	f, err := os.Create(path)
	if err != nil {
		log.Fatal(err)
	}
	defer f.Close()

	err = png.Encode(f, m)
	if err != nil {
		log.Fatal(err)
	}
}

// DrawHLine draws a horizontal line
func DrawHLine(m draw.Image, x1, y, x2 int) {
	for ; x1 <= x2; x1++ {
		m.Set(x1, y, color.RGBA{0, 0, 255, 255})
	}
}

// DrawVLine draws a veritcal line
func DrawVLine(m draw.Image, x, y1, y2 int) {
	for ; y1 <= y2; y1++ {
		m.Set(x, y1, color.RGBA{0, 0, 255, 255})
	}
}

// DrawRect draws a rectangle utilizing HLine() and VLine()
func DrawRect(m draw.Image, x1, y1, x2, y2 int) {
	DrawHLine(m, x1, y1, x2)
	DrawHLine(m, x1, y2, x2)
	DrawVLine(m, x1, y1, y2)
	DrawVLine(m, x2, y1, y2)
}
