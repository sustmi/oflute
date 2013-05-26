/**
 * @file dropShadow.cpp
 * 
 * @author José Tomás Tocino García
 * @date 2010
 *
 * Copyright (C) 2010 José Tomás Tocino García <theom3ga@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include "dropShadow.h"
#include "log.h"

// Taken from:
// http://stackoverflow.com/questions/7622/shift-operator-in-c/2463888#2463888
int lRS(int x, int n) {
    return (x >> n) & ~( ( (x >> (sizeof(int) << 3) - 1) << (sizeof(int) << 3) - 1) ) >> (n - 1);
}

// Adapted from Java example:
// http://www.curious-creature.org/2005/07/06/non-rectangular-shadow/
// and
// http://www.curious-creature.org/2005/07/07/fast-or-good-drop-shadows/
Gosu::Bitmap applyShadow(Gosu::Image & image, int shadowSize, float shadowOpacity) {
    int dstWidth = image.width();
    int dstHeight = image.height();

    Gosu::Bitmap sourceBitmap = image.getData().toBitmap();
    Gosu::Bitmap targetBitmap;
    targetBitmap.resize(dstWidth + shadowSize * 2, dstHeight + shadowSize * 2);

    for(int i = 0; i < dstWidth; ++i){
	for(int j = 0; j < dstHeight; ++j){
	    targetBitmap.setPixel(i + shadowSize, j + shadowSize, sourceBitmap.getPixel(i,j));
	}
    }

    int * dataBuffer = (int *)targetBitmap.data();
    dstWidth = targetBitmap.width();
    dstHeight = targetBitmap.height();

    //*******************************

    int left = (shadowSize - 1) >> 1;
    int right = shadowSize - left;
    int xStart = left;
    int xStop = dstWidth - right;
    int yStart = left;
    int yStop = dstHeight - right;
    
    int shadowRgb = 0x00000000;
    
    int * aHistory = new int[shadowSize];
    int historyIdx = 0;
    
    int aSum;
    
    int lastPixelOffset = right * dstWidth;
    float sumDivider = shadowOpacity / (float)shadowSize;

    //******************************
    // horizontal pass

    for (int y = 0, bufferOffset = 0; y < dstHeight; y++, bufferOffset = y * dstWidth) {
	aSum = 0;
	historyIdx = 0;
	for (int x = 0; x < shadowSize; x++, bufferOffset++) {
	    int a = lRS(dataBuffer[bufferOffset], 24);
	    aHistory[x] = a;
	    aSum += a;
	}

	bufferOffset -= right;

	for (int x = xStart; x < xStop; x++, bufferOffset++) {
	    int a = (int) (aSum * sumDivider);
	    dataBuffer[bufferOffset] = a << 24 | shadowRgb;
//	    cout << (a << 24 | shadowRgb) << endl;
	    // substract the oldest pixel from the sum
	    aSum -= aHistory[historyIdx];

	    // get the lastest pixel
	    a = lRS(dataBuffer[bufferOffset + right], 24);
	    aHistory[historyIdx] = a;
	    aSum += a;

	    if (++historyIdx >= shadowSize) {
		historyIdx -= shadowSize;
	    }
	}
    }

    
    // vertical pass
    for (int x = 0, bufferOffset = 0; x < dstWidth; x++, bufferOffset = x) {
	aSum = 0;
	historyIdx = 0;
	for (int y = 0; y < shadowSize; y++, bufferOffset += dstWidth) {
	    int a = lRS(dataBuffer[bufferOffset], 24);
	    aHistory[y] = a;
	    aSum += a;
	}

	bufferOffset -= lastPixelOffset;

	for (int y = yStart; y < yStop; y++, bufferOffset += dstWidth) {
	    int a = (int) (aSum * sumDivider);
	    dataBuffer[bufferOffset] = a << 24 | shadowRgb;

	    // substract the oldest pixel from the sum
	    aSum -= aHistory[historyIdx];

	    // get the lastest pixel
	    a = lRS(dataBuffer[bufferOffset + lastPixelOffset], 24);
	    aHistory[historyIdx] = a;
	    aSum += a;

	    if (++historyIdx >= shadowSize) {
		historyIdx -= shadowSize;
	    }
	}
    }//*/

    // ********************
    return targetBitmap;
}


