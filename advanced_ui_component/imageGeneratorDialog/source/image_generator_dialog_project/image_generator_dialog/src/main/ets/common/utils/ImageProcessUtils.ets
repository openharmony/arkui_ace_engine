/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import {
  CompressionPlan,
  HistogramChannel,
  HistogramResult,
  HsvColor,
  ImagePlane,
  RgbaColor,
  Size2D
} from './ImageTypes';
import { ImageGeometryUtils } from './ImageGeometryUtils';

interface GeneratedTypeLiteralInterface_1 {
  min: number;
  max: number;
  mean: number;
  std: number;
}

export class ImageProcessUtils {
  static createImage(width: number, height: number, fill?: RgbaColor): ImagePlane {
    let w = Math.max(1, Math.floor(width));
    let h = Math.max(1, Math.floor(height));
    let data = new Uint8Array(w * h * 4);
    let image: ImagePlane = { width: w, height: h, data };

    if (fill) {
      ImageProcessUtils.fill(image, fill);
    }

    return image;
  }

  static cloneImage(image: ImagePlane): ImagePlane {
    return {
      width: image.width,
      height: image.height,
      data: new Uint8Array(image.data)
    };
  }

  static isValidImage(image: ImagePlane | undefined): boolean {
    if (!image) {
      return false;
    }
    return image.width > 0 && image.height > 0 && image.data.length === image.width * image.height * 4;
  }

  static assertValidImage(image: ImagePlane): void {
    if (!ImageProcessUtils.isValidImage(image)) {
      throw new Error('Invalid image plane data.');
    }
  }

  static bytesPerImage(width: number, height: number, channels: number = 4): number {
    return Math.max(0, Math.floor(width)) * Math.max(0, Math.floor(height)) * Math.max(1, channels);
  }

  static indexOf(image: ImagePlane, x: number, y: number): number {
    let xx = ImageGeometryUtils.clamp(Math.floor(x), 0, image.width - 1);
    let yy = ImageGeometryUtils.clamp(Math.floor(y), 0, image.height - 1);
    return (yy * image.width + xx) * 4;
  }

  static getPixel(image: ImagePlane, x: number, y: number): RgbaColor {
    let idx = ImageProcessUtils.indexOf(image, x, y);
    return {
      r: image.data[idx],
      g: image.data[idx + 1],
      b: image.data[idx + 2],
      a: image.data[idx + 3]
    };
  }

  static setPixel(image: ImagePlane, x: number, y: number, color: RgbaColor): void {
    if (x < 0 || y < 0 || x >= image.width || y >= image.height) {
      return;
    }
    let idx = (Math.floor(y) * image.width + Math.floor(x)) * 4;
    image.data[idx] = ImageGeometryUtils.clamp(Math.round(color.r), 0, 255);
    image.data[idx + 1] = ImageGeometryUtils.clamp(Math.round(color.g), 0, 255);
    image.data[idx + 2] = ImageGeometryUtils.clamp(Math.round(color.b), 0, 255);
    image.data[idx + 3] = ImageGeometryUtils.clamp(Math.round(color.a), 0, 255);
  }

  static fill(image: ImagePlane, color: RgbaColor): void {
    let r = ImageGeometryUtils.clamp(Math.round(color.r), 0, 255);
    let g = ImageGeometryUtils.clamp(Math.round(color.g), 0, 255);
    let b = ImageGeometryUtils.clamp(Math.round(color.b), 0, 255);
    let a = ImageGeometryUtils.clamp(Math.round(color.a), 0, 255);

    for (let i = 0; i < image.data.length; i += 4) {
      image.data[i] = r;
      image.data[i + 1] = g;
      image.data[i + 2] = b;
      image.data[i + 3] = a;
    }
  }

  static clear(image: ImagePlane): void {
    image.data.fill(0);
  }

  static copyRegion(
    src: ImagePlane,
    srcX: number,
    srcY: number,
    width: number,
    height: number,
    dst: ImagePlane,
    dstX: number,
    dstY: number
  ): void {
    let w = Math.max(0, Math.floor(width));
    let h = Math.max(0, Math.floor(height));

    for (let y = 0; y < h; y++) {
      for (let x = 0; x < w; x++) {
        let sx = srcX + x;
        let sy = srcY + y;
        let dx = dstX + x;
        let dy = dstY + y;

        if (sx < 0 || sy < 0 || sx >= src.width || sy >= src.height) {
          continue;
        }
        if (dx < 0 || dy < 0 || dx >= dst.width || dy >= dst.height) {
          continue;
        }

        let srcIdx = (sy * src.width + sx) * 4;
        let dstIdx = (dy * dst.width + dx) * 4;
        dst.data[dstIdx] = src.data[srcIdx];
        dst.data[dstIdx + 1] = src.data[srcIdx + 1];
        dst.data[dstIdx + 2] = src.data[srcIdx + 2];
        dst.data[dstIdx + 3] = src.data[srcIdx + 3];
      }
    }
  }

  static crop(image: ImagePlane, left: number, top: number, width: number, height: number, padColor?: RgbaColor): ImagePlane {
    let w = Math.max(1, Math.floor(width));
    let h = Math.max(1, Math.floor(height));
    let out = ImageProcessUtils.createImage(w, h, padColor ?? { r: 0, g: 0, b: 0, a: 0 });

    for (let y = 0; y < h; y++) {
      for (let x = 0; x < w; x++) {
        let sx = Math.floor(left + x);
        let sy = Math.floor(top + y);
        if (sx < 0 || sy < 0 || sx >= image.width || sy >= image.height) {
          continue;
        }
        let srcIdx = (sy * image.width + sx) * 4;
        let dstIdx = (y * w + x) * 4;
        out.data[dstIdx] = image.data[srcIdx];
        out.data[dstIdx + 1] = image.data[srcIdx + 1];
        out.data[dstIdx + 2] = image.data[srcIdx + 2];
        out.data[dstIdx + 3] = image.data[srcIdx + 3];
      }
    }

    return out;
  }

  static pad(image: ImagePlane, left: number, top: number, right: number, bottom: number, color: RgbaColor): ImagePlane {
    let outWidth = image.width + Math.max(0, left) + Math.max(0, right);
    let outHeight = image.height + Math.max(0, top) + Math.max(0, bottom);
    let out = ImageProcessUtils.createImage(outWidth, outHeight, color);
    ImageProcessUtils.copyRegion(image, 0, 0, image.width, image.height, out, Math.max(0, left), Math.max(0, top));
    return out;
  }

  static flipHorizontal(image: ImagePlane): ImagePlane {
    let out = ImageProcessUtils.createImage(image.width, image.height);

    for (let y = 0; y < image.height; y++) {
      for (let x = 0; x < image.width; x++) {
        let srcIdx = (y * image.width + x) * 4;
        let dstIdx = (y * out.width + (out.width - 1 - x)) * 4;
        out.data[dstIdx] = image.data[srcIdx];
        out.data[dstIdx + 1] = image.data[srcIdx + 1];
        out.data[dstIdx + 2] = image.data[srcIdx + 2];
        out.data[dstIdx + 3] = image.data[srcIdx + 3];
      }
    }

    return out;
  }

  static flipVertical(image: ImagePlane): ImagePlane {
    let out = ImageProcessUtils.createImage(image.width, image.height);

    for (let y = 0; y < image.height; y++) {
      for (let x = 0; x < image.width; x++) {
        let srcIdx = (y * image.width + x) * 4;
        let dstIdx = ((out.height - 1 - y) * out.width + x) * 4;
        out.data[dstIdx] = image.data[srcIdx];
        out.data[dstIdx + 1] = image.data[srcIdx + 1];
        out.data[dstIdx + 2] = image.data[srcIdx + 2];
        out.data[dstIdx + 3] = image.data[srcIdx + 3];
      }
    }

    return out;
  }

  static rotate90CW(image: ImagePlane): ImagePlane {
    let out = ImageProcessUtils.createImage(image.height, image.width);

    for (let y = 0; y < image.height; y++) {
      for (let x = 0; x < image.width; x++) {
        let srcIdx = (y * image.width + x) * 4;
        let dx = image.height - 1 - y;
        let dy = x;
        let dstIdx = (dy * out.width + dx) * 4;
        out.data[dstIdx] = image.data[srcIdx];
        out.data[dstIdx + 1] = image.data[srcIdx + 1];
        out.data[dstIdx + 2] = image.data[srcIdx + 2];
        out.data[dstIdx + 3] = image.data[srcIdx + 3];
      }
    }

    return out;
  }

  static rotate90CCW(image: ImagePlane): ImagePlane {
    let out = ImageProcessUtils.createImage(image.height, image.width);

    for (let y = 0; y < image.height; y++) {
      for (let x = 0; x < image.width; x++) {
        let srcIdx = (y * image.width + x) * 4;
        let dx = y;
        let dy = image.width - 1 - x;
        let dstIdx = (dy * out.width + dx) * 4;
        out.data[dstIdx] = image.data[srcIdx];
        out.data[dstIdx + 1] = image.data[srcIdx + 1];
        out.data[dstIdx + 2] = image.data[srcIdx + 2];
        out.data[dstIdx + 3] = image.data[srcIdx + 3];
      }
    }

    return out;
  }

  static rotate180(image: ImagePlane): ImagePlane {
    return ImageProcessUtils.flipVertical(ImageProcessUtils.flipHorizontal(image));
  }

  static toGrayscale(image: ImagePlane): ImagePlane {
    let out = ImageProcessUtils.cloneImage(image);

    for (let i = 0; i < out.data.length; i += 4) {
      let r = out.data[i];
      let g = out.data[i + 1];
      let b = out.data[i + 2];
      let y = Math.round(0.299 * r + 0.587 * g + 0.114 * b);
      out.data[i] = y;
      out.data[i + 1] = y;
      out.data[i + 2] = y;
    }

    return out;
  }

  static invert(image: ImagePlane): ImagePlane {
    let out = ImageProcessUtils.cloneImage(image);
    for (let i = 0; i < out.data.length; i += 4) {
      out.data[i] = 255 - out.data[i];
      out.data[i + 1] = 255 - out.data[i + 1];
      out.data[i + 2] = 255 - out.data[i + 2];
    }
    return out;
  }
  static adjustBrightness(image: ImagePlane, delta: number): ImagePlane {
    let out = ImageProcessUtils.cloneImage(image);
    let diff = Math.round(delta * 255);

    for (let i = 0; i < out.data.length; i += 4) {
      out.data[i] = ImageGeometryUtils.clamp(out.data[i] + diff, 0, 255);
      out.data[i + 1] = ImageGeometryUtils.clamp(out.data[i + 1] + diff, 0, 255);
      out.data[i + 2] = ImageGeometryUtils.clamp(out.data[i + 2] + diff, 0, 255);
    }

    return out;
  }

  static adjustContrast(image: ImagePlane, factor: number): ImagePlane {
    let out = ImageProcessUtils.cloneImage(image);
    let f = Math.max(0, factor);

    for (let i = 0; i < out.data.length; i += 4) {
      out.data[i] = ImageGeometryUtils.clamp(Math.round((out.data[i] - 128) * f + 128), 0, 255);
      out.data[i + 1] = ImageGeometryUtils.clamp(Math.round((out.data[i + 1] - 128) * f + 128), 0, 255);
      out.data[i + 2] = ImageGeometryUtils.clamp(Math.round((out.data[i + 2] - 128) * f + 128), 0, 255);
    }

    return out;
  }

  static adjustGamma(image: ImagePlane, gamma: number): ImagePlane {
    let out = ImageProcessUtils.cloneImage(image);
    let g = Math.max(0.01, gamma);
    let inv = 1 / g;

    let lut: number[] = [];
    for (let i = 0; i <= 255; i++) {
      lut.push(ImageGeometryUtils.clamp(Math.round(Math.pow(i / 255, inv) * 255), 0, 255));
    }

    for (let i = 0; i < out.data.length; i += 4) {
      out.data[i] = lut[out.data[i]];
      out.data[i + 1] = lut[out.data[i + 1]];
      out.data[i + 2] = lut[out.data[i + 2]];
    }

    return out;
  }

  static adjustSaturation(image: ImagePlane, factor: number): ImagePlane {
    let out = ImageProcessUtils.cloneImage(image);

    for (let i = 0; i < out.data.length; i += 4) {
      let r = out.data[i];
      let g = out.data[i + 1];
      let b = out.data[i + 2];

      let gray = 0.299 * r + 0.587 * g + 0.114 * b;
      out.data[i] = ImageGeometryUtils.clamp(Math.round(gray + (r - gray) * factor), 0, 255);
      out.data[i + 1] = ImageGeometryUtils.clamp(Math.round(gray + (g - gray) * factor), 0, 255);
      out.data[i + 2] = ImageGeometryUtils.clamp(Math.round(gray + (b - gray) * factor), 0, 255);
    }

    return out;
  }

  static applyColorMatrix(image: ImagePlane, matrix4x5: number[]): ImagePlane {
    let out = ImageProcessUtils.cloneImage(image);
    if (matrix4x5.length !== 20) {
      return out;
    }

    for (let i = 0; i < out.data.length; i += 4) {
      let r = out.data[i];
      let g = out.data[i + 1];
      let b = out.data[i + 2];
      let a = out.data[i + 3];

      let nr = r * matrix4x5[0] + g * matrix4x5[1] + b * matrix4x5[2] + a * matrix4x5[3] + matrix4x5[4];
      let ng = r * matrix4x5[5] + g * matrix4x5[6] + b * matrix4x5[7] + a * matrix4x5[8] + matrix4x5[9];
      let nb = r * matrix4x5[10] + g * matrix4x5[11] + b * matrix4x5[12] + a * matrix4x5[13] + matrix4x5[14];
      let na = r * matrix4x5[15] + g * matrix4x5[16] + b * matrix4x5[17] + a * matrix4x5[18] + matrix4x5[19];

      out.data[i] = ImageGeometryUtils.clamp(Math.round(nr), 0, 255);
      out.data[i + 1] = ImageGeometryUtils.clamp(Math.round(ng), 0, 255);
      out.data[i + 2] = ImageGeometryUtils.clamp(Math.round(nb), 0, 255);
      out.data[i + 3] = ImageGeometryUtils.clamp(Math.round(na), 0, 255);
    }

    return out;
  }

  static thresholdLuma(image: ImagePlane, threshold: number): ImagePlane {
    let out = ImageProcessUtils.cloneImage(image);
    let th = ImageGeometryUtils.clamp(Math.round(threshold), 0, 255);

    for (let i = 0; i < out.data.length; i += 4) {
      let y = Math.round(0.299 * out.data[i] + 0.587 * out.data[i + 1] + 0.114 * out.data[i + 2]);
      let value = y >= th ? 255 : 0;
      out.data[i] = value;
      out.data[i + 1] = value;
      out.data[i + 2] = value;
    }

    return out;
  }

  static levels(image: ImagePlane, inBlack: number, inWhite: number, gamma: number, outBlack: number, outWhite: number): ImagePlane {
    let out = ImageProcessUtils.cloneImage(image);

    let inB = ImageGeometryUtils.clamp(inBlack, 0, 255);
    let inW = ImageGeometryUtils.clamp(inWhite, 0, 255);
    let outB = ImageGeometryUtils.clamp(outBlack, 0, 255);
    let outW = ImageGeometryUtils.clamp(outWhite, 0, 255);
    let g = Math.max(0.01, gamma);

    let rangeIn = Math.max(1, inW - inB);
    let rangeOut = Math.max(1, outW - outB);

    for (let i = 0; i < out.data.length; i += 4) {
      for (let c = 0; c < 3; c++) {
        let v = out.data[i + c];
        let n = ImageGeometryUtils.clamp((v - inB) / rangeIn, 0, 1);
        let corrected = Math.pow(n, 1 / g);
        out.data[i + c] = ImageGeometryUtils.clamp(Math.round(outB + corrected * rangeOut), 0, 255);
      }
    }

    return out;
  }

  private static channelStats(bins: number[]): HistogramChannel {
    let min = 0;
    let max = 255;

    while (min < 255 && bins[min] === 0) {
      min++;
    }

    while (max > 0 && bins[max] === 0) {
      max--;
    }

    let sum = 0;
    let total = 0;
    for (let i = 0; i < 256; i++) {
      sum += i * bins[i];
      total += bins[i];
    }

    return {
      bins,
      min,
      max,
      mean: total > 0 ? sum / total : 0
    };
  }

  static meanColor(image: ImagePlane): RgbaColor {
    if (image.data.length === 0) {
      return { r: 0, g: 0, b: 0, a: 0 };
    }

    let sumR = 0;
    let sumG = 0;
    let sumB = 0;
    let sumA = 0;
    let count = image.width * image.height;

    for (let i = 0; i < image.data.length; i += 4) {
      sumR += image.data[i];
      sumG += image.data[i + 1];
      sumB += image.data[i + 2];
      sumA += image.data[i + 3];
    }

    return {
      r: sumR / count,
      g: sumG / count,
      b: sumB / count,
      a: sumA / count
    };
  }

  static lumaStats(image: ImagePlane): GeneratedTypeLiteralInterface_1 {
    if (image.data.length === 0) {
      return { min: 0, max: 0, mean: 0, std: 0 };
    }

    let min = 255;
    let max = 0;
    let sum = 0;
    let sumSq = 0;
    let count = image.width * image.height;

    for (let i = 0; i < image.data.length; i += 4) {
      let y = 0.299 * image.data[i] + 0.587 * image.data[i + 1] + 0.114 * image.data[i + 2];
      min = Math.min(min, y);
      max = Math.max(max, y);
      sum += y;
      sumSq += y * y;
    }

    let mean = sum / count;
    let variance = Math.max(0, sumSq / count - mean * mean);
    return {
      min,
      max,
      mean,
      std: Math.sqrt(variance)
    };
  }

  static premultiplyAlpha(image: ImagePlane): ImagePlane {
    let out = ImageProcessUtils.cloneImage(image);
    for (let i = 0; i < out.data.length; i += 4) {
      let alpha = out.data[i + 3] / 255;
      out.data[i] = Math.round(out.data[i] * alpha);
      out.data[i + 1] = Math.round(out.data[i + 1] * alpha);
      out.data[i + 2] = Math.round(out.data[i + 2] * alpha);
    }
    return out;
  }

  static unpremultiplyAlpha(image: ImagePlane): ImagePlane {
    let out = ImageProcessUtils.cloneImage(image);
    for (let i = 0; i < out.data.length; i += 4) {
      let alpha = out.data[i + 3];
      if (alpha <= 0) {
        continue;
      }
      let inv = 255 / alpha;
      out.data[i] = ImageGeometryUtils.clamp(Math.round(out.data[i] * inv), 0, 255);
      out.data[i + 1] = ImageGeometryUtils.clamp(Math.round(out.data[i + 1] * inv), 0, 255);
      out.data[i + 2] = ImageGeometryUtils.clamp(Math.round(out.data[i + 2] * inv), 0, 255);
    }
    return out;
  }
  static blendNormal(bottom: ImagePlane, top: ImagePlane, offsetX: number = 0, offsetY: number = 0): ImagePlane {
    let out = ImageProcessUtils.cloneImage(bottom);

    for (let y = 0; y < top.height; y++) {
      for (let x = 0; x < top.width; x++) {
        let dstX = x + offsetX;
        let dstY = y + offsetY;
        if (dstX < 0 || dstY < 0 || dstX >= out.width || dstY >= out.height) {
          continue;
        }

        let topIdx = (y * top.width + x) * 4;
        let bottomIdx = (dstY * out.width + dstX) * 4;

        let sa = top.data[topIdx + 3] / 255;
        let da = out.data[bottomIdx + 3] / 255;
        let outA = sa + da * (1 - sa);
        if (outA < 1e-6) {
          out.data[bottomIdx] = 0;
          out.data[bottomIdx + 1] = 0;
          out.data[bottomIdx + 2] = 0;
          out.data[bottomIdx + 3] = 0;
          continue;
        }

        let sr = top.data[topIdx] / 255;
        let sg = top.data[topIdx + 1] / 255;
        let sb = top.data[topIdx + 2] / 255;

        let dr = out.data[bottomIdx] / 255;
        let dg = out.data[bottomIdx + 1] / 255;
        let db = out.data[bottomIdx + 2] / 255;

        let rr = (sr * sa + dr * da * (1 - sa)) / outA;
        let rg = (sg * sa + dg * da * (1 - sa)) / outA;
        let rb = (sb * sa + db * da * (1 - sa)) / outA;

        out.data[bottomIdx] = ImageGeometryUtils.clamp(Math.round(rr * 255), 0, 255);
        out.data[bottomIdx + 1] = ImageGeometryUtils.clamp(Math.round(rg * 255), 0, 255);
        out.data[bottomIdx + 2] = ImageGeometryUtils.clamp(Math.round(rb * 255), 0, 255);
        out.data[bottomIdx + 3] = ImageGeometryUtils.clamp(Math.round(outA * 255), 0, 255);
      }
    }

    return out;
  }

  static blendMultiply(bottom: ImagePlane, top: ImagePlane, opacity: number = 1): ImagePlane {
    let out = ImageProcessUtils.cloneImage(bottom);
    let width = Math.min(bottom.width, top.width);
    let height = Math.min(bottom.height, top.height);
    let op = ImageGeometryUtils.saturate(opacity);

    for (let y = 0; y < height; y++) {
      for (let x = 0; x < width; x++) {
        let idx = (y * width + x) * 4;
        for (let c = 0; c < 3; c++) {
          let b = out.data[idx + c] / 255;
          let t = top.data[idx + c] / 255;
          let mixed = b * t;
          out.data[idx + c] = ImageGeometryUtils.clamp(Math.round((b * (1 - op) + mixed * op) * 255), 0, 255);
        }
      }
    }

    return out;
  }

  static blendScreen(bottom: ImagePlane, top: ImagePlane, opacity: number = 1): ImagePlane {
    let out = ImageProcessUtils.cloneImage(bottom);
    let width = Math.min(bottom.width, top.width);
    let height = Math.min(bottom.height, top.height);
    let op = ImageGeometryUtils.saturate(opacity);

    for (let y = 0; y < height; y++) {
      for (let x = 0; x < width; x++) {
        let idx = (y * width + x) * 4;
        for (let c = 0; c < 3; c++) {
          let b = out.data[idx + c] / 255;
          let t = top.data[idx + c] / 255;
          let screened = 1 - (1 - b) * (1 - t);
          out.data[idx + c] = ImageGeometryUtils.clamp(Math.round((b * (1 - op) + screened * op) * 255), 0, 255);
        }
      }
    }

    return out;
  }

  static resizeNearest(image: ImagePlane, width: number, height: number): ImagePlane {
    let outW = Math.max(1, Math.floor(width));
    let outH = Math.max(1, Math.floor(height));
    let out = ImageProcessUtils.createImage(outW, outH);

    let scaleX = image.width / outW;
    let scaleY = image.height / outH;

    for (let y = 0; y < outH; y++) {
      let sy = Math.min(image.height - 1, Math.floor(y * scaleY));
      for (let x = 0; x < outW; x++) {
        let sx = Math.min(image.width - 1, Math.floor(x * scaleX));
        let srcIdx = (sy * image.width + sx) * 4;
        let dstIdx = (y * outW + x) * 4;

        out.data[dstIdx] = image.data[srcIdx];
        out.data[dstIdx + 1] = image.data[srcIdx + 1];
        out.data[dstIdx + 2] = image.data[srcIdx + 2];
        out.data[dstIdx + 3] = image.data[srcIdx + 3];
      }
    }

    return out;
  }

  static resizeBilinear(image: ImagePlane, width: number, height: number): ImagePlane {
    let outW = Math.max(1, Math.floor(width));
    let outH = Math.max(1, Math.floor(height));
    let out = ImageProcessUtils.createImage(outW, outH);

    let xRatio = image.width / outW;
    let yRatio = image.height / outH;

    for (let y = 0; y < outH; y++) {
      let fy = (y + 0.5) * yRatio - 0.5;
      let y0 = ImageGeometryUtils.clamp(Math.floor(fy), 0, image.height - 1);
      let y1 = ImageGeometryUtils.clamp(y0 + 1, 0, image.height - 1);
      let wy = fy - y0;

      for (let x = 0; x < outW; x++) {
        let fx = (x + 0.5) * xRatio - 0.5;
        let x0 = ImageGeometryUtils.clamp(Math.floor(fx), 0, image.width - 1);
        let x1 = ImageGeometryUtils.clamp(x0 + 1, 0, image.width - 1);
        let wx = fx - x0;

        let i00 = (y0 * image.width + x0) * 4;
        let i10 = (y0 * image.width + x1) * 4;
        let i01 = (y1 * image.width + x0) * 4;
        let i11 = (y1 * image.width + x1) * 4;

        let dst = (y * outW + x) * 4;

        for (let c = 0; c < 4; c++) {
          let top = image.data[i00 + c] * (1 - wx) + image.data[i10 + c] * wx;
          let bottom = image.data[i01 + c] * (1 - wx) + image.data[i11 + c] * wx;
          out.data[dst + c] = ImageGeometryUtils.clamp(Math.round(top * (1 - wy) + bottom * wy), 0, 255);
        }
      }
    }

    return out;
  }

  static downsample2x(image: ImagePlane): ImagePlane {
    let outW = Math.max(1, Math.floor(image.width / 2));
    let outH = Math.max(1, Math.floor(image.height / 2));
    let out = ImageProcessUtils.createImage(outW, outH);

    for (let y = 0; y < outH; y++) {
      for (let x = 0; x < outW; x++) {
        let sx = x * 2;
        let sy = y * 2;

        let accum = [0, 0, 0, 0];
        let count = 0;

        for (let oy = 0; oy < 2; oy++) {
          for (let ox = 0; ox < 2; ox++) {
            let px = sx + ox;
            let py = sy + oy;
            if (px >= image.width || py >= image.height) {
              continue;
            }
            let idx = (py * image.width + px) * 4;
            accum[0] += image.data[idx];
            accum[1] += image.data[idx + 1];
            accum[2] += image.data[idx + 2];
            accum[3] += image.data[idx + 3];
            count++;
          }
        }

        let dst = (y * outW + x) * 4;
        out.data[dst] = Math.round(accum[0] / count);
        out.data[dst + 1] = Math.round(accum[1] / count);
        out.data[dst + 2] = Math.round(accum[2] / count);
        out.data[dst + 3] = Math.round(accum[3] / count);
      }
    }

    return out;
  }

  static boxBlur(image: ImagePlane, radius: number): ImagePlane {
    if (radius <= 0) {
      return ImageProcessUtils.cloneImage(image);
    }

    let out = ImageProcessUtils.createImage(image.width, image.height);
    let kernel = radius * 2 + 1;
    let area = kernel * kernel;

    for (let y = 0; y < image.height; y++) {
      for (let x = 0; x < image.width; x++) {
        let sumR = 0;
        let sumG = 0;
        let sumB = 0;
        let sumA = 0;

        for (let ky = -radius; ky <= radius; ky++) {
          for (let kx = -radius; kx <= radius; kx++) {
            let px = ImageGeometryUtils.clamp(x + kx, 0, image.width - 1);
            let py = ImageGeometryUtils.clamp(y + ky, 0, image.height - 1);
            let idx = (py * image.width + px) * 4;
            sumR += image.data[idx];
            sumG += image.data[idx + 1];
            sumB += image.data[idx + 2];
            sumA += image.data[idx + 3];
          }
        }

        let dst = (y * image.width + x) * 4;
        out.data[dst] = Math.round(sumR / area);
        out.data[dst + 1] = Math.round(sumG / area);
        out.data[dst + 2] = Math.round(sumB / area);
        out.data[dst + 3] = Math.round(sumA / area);
      }
    }

    return out;
  }
  static gaussianKernel(radius: number, sigma: number): number[] {
    let kernel: number[] = [];
    let s = Math.max(0.01, sigma);
    let sum = 0;

    for (let i = -radius; i <= radius; i++) {
      let value = Math.exp(-(i * i) / (2 * s * s));
      kernel.push(value);
      sum += value;
    }

    for (let i = 0; i < kernel.length; i++) {
      kernel[i] /= sum;
    }

    return kernel;
  }

  static gaussianBlur(image: ImagePlane, radius: number, sigma: number = radius * 0.5): ImagePlane {
    if (radius <= 0) {
      return ImageProcessUtils.cloneImage(image);
    }

    let kernel = ImageProcessUtils.gaussianKernel(radius, sigma);
    let temp = ImageProcessUtils.createImage(image.width, image.height);
    let out = ImageProcessUtils.createImage(image.width, image.height);

    for (let y = 0; y < image.height; y++) {
      for (let x = 0; x < image.width; x++) {
        let sum = [0, 0, 0, 0];
        for (let k = -radius; k <= radius; k++) {
          let px = ImageGeometryUtils.clamp(x + k, 0, image.width - 1);
          let idx = (y * image.width + px) * 4;
          let w = kernel[k + radius];
          sum[0] += image.data[idx] * w;
          sum[1] += image.data[idx + 1] * w;
          sum[2] += image.data[idx + 2] * w;
          sum[3] += image.data[idx + 3] * w;
        }

        let dst = (y * temp.width + x) * 4;
        temp.data[dst] = Math.round(sum[0]);
        temp.data[dst + 1] = Math.round(sum[1]);
        temp.data[dst + 2] = Math.round(sum[2]);
        temp.data[dst + 3] = Math.round(sum[3]);
      }
    }

    for (let y = 0; y < temp.height; y++) {
      for (let x = 0; x < temp.width; x++) {
        let sum = [0, 0, 0, 0];
        for (let k = -radius; k <= radius; k++) {
          let py = ImageGeometryUtils.clamp(y + k, 0, temp.height - 1);
          let idx = (py * temp.width + x) * 4;
          let w = kernel[k + radius];
          sum[0] += temp.data[idx] * w;
          sum[1] += temp.data[idx + 1] * w;
          sum[2] += temp.data[idx + 2] * w;
          sum[3] += temp.data[idx + 3] * w;
        }

        let dst = (y * out.width + x) * 4;
        out.data[dst] = Math.round(sum[0]);
        out.data[dst + 1] = Math.round(sum[1]);
        out.data[dst + 2] = Math.round(sum[2]);
        out.data[dst + 3] = Math.round(sum[3]);
      }
    }

    return out;
  }

  static sobelEdge(image: ImagePlane): ImagePlane {
    let gray = ImageProcessUtils.toGrayscale(image);
    let out = ImageProcessUtils.createImage(image.width, image.height, { r: 0, g: 0, b: 0, a: 255 });

    let gxKernel = [
      -1, 0, 1,
      -2, 0, 2,
      -1, 0, 1
    ];
    let gyKernel = [
      -1, -2, -1,
      0, 0, 0,
      1, 2, 1
    ];

    for (let y = 1; y < image.height - 1; y++) {
      for (let x = 1; x < image.width - 1; x++) {
        let gx = 0;
        let gy = 0;

        let k = 0;
        for (let ky = -1; ky <= 1; ky++) {
          for (let kx = -1; kx <= 1; kx++) {
            let idx = ((y + ky) * image.width + (x + kx)) * 4;
            let lum = gray.data[idx];
            gx += lum * gxKernel[k];
            gy += lum * gyKernel[k];
            k++;
          }
        }

        let mag = ImageGeometryUtils.clamp(Math.round(Math.sqrt(gx * gx + gy * gy)), 0, 255);
        let dst = (y * out.width + x) * 4;
        out.data[dst] = mag;
        out.data[dst + 1] = mag;
        out.data[dst + 2] = mag;
      }
    }

    return out;
  }

  static rgbToHsv(color: RgbaColor): HsvColor {
    let r = color.r / 255;
    let g = color.g / 255;
    let b = color.b / 255;

    let max = Math.max(r, g, b);
    let min = Math.min(r, g, b);
    let delta = max - min;

    let h = 0;
    if (delta > 0) {
      if (max === r) {
        h = 60 * (((g - b) / delta) % 6);
      } else if (max === g) {
        h = 60 * ((b - r) / delta + 2);
      } else {
        h = 60 * ((r - g) / delta + 4);
      }
    }
    if (h < 0) {
      h += 360;
    }

    let s = max === 0 ? 0 : delta / max;
    let v = max;

    return {
      h,
      s,
      v,
      a: color.a / 255
    };
  }

  static hsvToRgb(color: HsvColor): RgbaColor {
    let h = ((color.h % 360) + 360) % 360;
    let s = ImageGeometryUtils.saturate(color.s);
    let v = ImageGeometryUtils.saturate(color.v);

    let c = v * s;
    let x = c * (1 - Math.abs((h / 60) % 2 - 1));
    let m = v - c;

    let r = 0;
    let g = 0;
    let b = 0;

    if (h < 60) {
      r = c; g = x; b = 0;
    } else if (h < 120) {
      r = x; g = c; b = 0;
    } else if (h < 180) {
      r = 0; g = c; b = x;
    } else if (h < 240) {
      r = 0; g = x; b = c;
    } else if (h < 300) {
      r = x; g = 0; b = c;
    } else {
      r = c; g = 0; b = x;
    }

    return {
      r: Math.round((r + m) * 255),
      g: Math.round((g + m) * 255),
      b: Math.round((b + m) * 255),
      a: Math.round(ImageGeometryUtils.saturate(color.a) * 255)
    };
  }

  static shiftHue(image: ImagePlane, degreeOffset: number): ImagePlane {
    let out = ImageProcessUtils.cloneImage(image);

    for (let i = 0; i < out.data.length; i += 4) {
      let hsv = ImageProcessUtils.rgbToHsv({
        r: out.data[i],
        g: out.data[i + 1],
        b: out.data[i + 2],
        a: out.data[i + 3]
      });
      hsv.h += degreeOffset;
      let rgb = ImageProcessUtils.hsvToRgb(hsv);
      out.data[i] = rgb.r;
      out.data[i + 1] = rgb.g;
      out.data[i + 2] = rgb.b;
    }

    return out;
  }

  static containsTransparency(image: ImagePlane): boolean {
    for (let i = 3; i < image.data.length; i += 4) {
      if (image.data[i] < 255) {
        return true;
      }
    }
    return false;
  }

  static alphaCoverage(image: ImagePlane, alphaThreshold: number = 1): number {
    let covered = 0;
    let total = image.width * image.height;

    for (let i = 3; i < image.data.length; i += 4) {
      if (image.data[i] >= alphaThreshold) {
        covered++;
      }
    }

    return total === 0 ? 0 : covered / total;
  }

  static thumbnailPlan(src: Size2D, maxEdge: number): Size2D {
    if (src.width <= maxEdge && src.height <= maxEdge) {
      return { width: src.width, height: src.height };
    }

    let ratio = src.width / Math.max(src.height, 1e-6);
    if (ratio >= 1) {
      return {
        width: Math.round(maxEdge),
        height: Math.max(1, Math.round(maxEdge / ratio))
      };
    }

    return {
      width: Math.max(1, Math.round(maxEdge * ratio)),
      height: Math.round(maxEdge)
    };
  }

  static suggestCompressionPlan(size: Size2D, hasAlpha: boolean, qualityHint: number = 0.85): CompressionPlan {
    let pixels = Math.max(1, Math.floor(size.width * size.height));

    let quality = ImageGeometryUtils.saturate(qualityHint);
    let level: 'low' | 'medium' | 'high' = 'medium';

    if (pixels > 4000000) {
      quality *= 0.8;
      level = 'low';
    } else if (pixels < 800000) {
      quality = Math.max(quality, 0.9);
      level = 'high';
    }

    let bytesPerPixel = hasAlpha ? 1.25 : 0.9;
    let expectedBytes = Math.round(pixels * bytesPerPixel * (0.4 + 0.6 * quality));

    return {
      quality,
      level,
      expectedBytes
    };
  }

  static estimatePsnr(reference: ImagePlane, test: ImagePlane): number {
    let width = Math.min(reference.width, test.width);
    let height = Math.min(reference.height, test.height);

    if (width <= 0 || height <= 0) {
      return 0;
    }

    let mse = 0;
    let count = width * height * 3;

    for (let y = 0; y < height; y++) {
      for (let x = 0; x < width; x++) {
        let idxRef = (y * reference.width + x) * 4;
        let idxTest = (y * test.width + x) * 4;

        for (let c = 0; c < 3; c++) {
          let diff = reference.data[idxRef + c] - test.data[idxTest + c];
          mse += diff * diff;
        }
      }
    }

    mse /= count;
    if (mse <= 1e-12) {
      return 99;
    }

    return 10 * Math.log10((255 * 255) / mse);
  }
}
