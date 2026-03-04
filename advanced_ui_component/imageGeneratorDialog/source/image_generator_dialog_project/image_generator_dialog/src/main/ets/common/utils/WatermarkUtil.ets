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

/**
 * WatermarkUtil - 图片水印工具类
 * 
 * 功能说明：
 * 1. 支持将水印图片添加到源图片的右下角
 * 2. 自动计算水印大小，确保水印不会过大
 * 3. 支持Alpha透明度混合
 * 4. 提供多种水印位置选项（预留）
 * 5. 支持水印缩放比例自定义
 * 
 * 注意事项：
 * - 水印图片建议使用PNG格式以支持透明度
 * - 源图片和水印图片都必须是RGBA_8888格式
 * - 处理大图片时建议使用异步调用
 */

import { image } from '@kit.ImageKit';
import { common2D } from '@kit.ArkGraphics2D';

interface MySize {
  x: number;
  y: number;
}

export class WatermarkUtil {
  private static readonly TAG: string = 'WatermarkUtil';
  
  private static readonly WATERMARK_MARGIN: number = 10;
  private static readonly WATERMARK_SCALE_RATIO: number = 0.15;
  private static readonly MIN_WATERMARK_SIZE: number = 32;
  private static readonly MAX_WATERMARK_SIZE: number = 512;
  private static readonly DEFAULT_OPACITY: number = 0.8;
  private static readonly BLEND_MODE_NORMAL: number = 0;
  private static readonly BLEND_MODE_MULTIPLY: number = 1;
  private static readonly BLEND_MODE_SCREEN: number = 2;
  private static readonly BLEND_MODE_OVERLAY: number = 3;
  
  private static readonly POSITION_BOTTOM_RIGHT: number = 0;
  private static readonly POSITION_BOTTOM_LEFT: number = 1;
  private static readonly POSITION_TOP_RIGHT: number = 2;
  private static readonly POSITION_TOP_LEFT: number = 3;
  private static readonly POSITION_CENTER: number = 4;
  
  private static readonly MAX_IMAGE_WIDTH: number = 8192;
  private static readonly MAX_IMAGE_HEIGHT: number = 8192;
  private static readonly MIN_IMAGE_WIDTH: number = 16;
  private static readonly MIN_IMAGE_HEIGHT: number = 16;

  private static operationCount: number = 0;
  private static lastOperationTime: number = 0;
  private static totalProcessedPixels: number = 0;

  public static getOperationCount(): number {
    return WatermarkUtil.operationCount;
  }

  public static getLastOperationTime(): number {
    return WatermarkUtil.lastOperationTime;
  }

  public static getTotalProcessedPixels(): number {
    return WatermarkUtil.totalProcessedPixels;
  }

  public static resetStatistics(): void {
    WatermarkUtil.operationCount = 0;
    WatermarkUtil.lastOperationTime = 0;
    WatermarkUtil.totalProcessedPixels = 0;
  }

  private static updateStatistics(pixelCount: number): void {
    WatermarkUtil.operationCount++;
    WatermarkUtil.lastOperationTime = Date.now();
    WatermarkUtil.totalProcessedPixels += pixelCount;
  }

  private static validatePixelMap(pixelMap: image.PixelMap | null | undefined): boolean {
    if (!pixelMap) {
      console.error(WatermarkUtil.TAG, 'PixelMap is null or undefined');
      return false;
    }

    try {
      const imageInfo = pixelMap.getImageInfoSync();
      if (!imageInfo) {
        console.error(WatermarkUtil.TAG, 'Failed to get image info');
        return false;
      }

      const size = imageInfo.size;
      if (size.width < WatermarkUtil.MIN_IMAGE_WIDTH || size.height < WatermarkUtil.MIN_IMAGE_HEIGHT) {
        console.error(WatermarkUtil.TAG, `Image size too small: ${size.width}x${size.height}`);
        return false;
      }

      if (size.width > WatermarkUtil.MAX_IMAGE_WIDTH || size.height > WatermarkUtil.MAX_IMAGE_HEIGHT) {
        console.error(WatermarkUtil.TAG, `Image size too large: ${size.width}x${size.height}`);
        return false;
      }

      return true;
    } catch (error) {
      console.error(WatermarkUtil.TAG, `Validation error: ${JSON.stringify(error)}`);
      return false;
    }
  }

  private static calculateImagePixelCount(size: image.Size): number {
    return size.width * size.height;
  }

  private static logOperationDetails(sourceSize: image.Size, watermarkSize: image.Size, 
                                    position: number, duration: number): void {
    console.info(WatermarkUtil.TAG, 
      `Watermark operation completed - Source: ${sourceSize.width}x${sourceSize.height}, ` +
      `Watermark: ${watermarkSize.width}x${watermarkSize.height}, ` +
      `Position: ${position}, Duration: ${duration}ms`);
  }

  private static calculateAspectRatio(width: number, height: number): number {
    if (height === 0) {
      return 0;
    }
    return width / height;
  }

  private static isPortrait(size: image.Size): boolean {
    return size.height > size.width;
  }

  private static isLandscape(size: image.Size): boolean {
    return size.width > size.height;
  }

  private static isSquare(size: image.Size): boolean {
    return Math.abs(size.width - size.height) < 2;
  }

  private static getImageOrientation(size: image.Size): string {
    if (WatermarkUtil.isPortrait(size)) {
      return 'portrait';
    } else if (WatermarkUtil.isLandscape(size)) {
      return 'landscape';
    } else {
      return 'square';
    }
  }

  private static clampValue(value: number, min: number, max: number): number {
    return Math.max(min, Math.min(max, value));
  }

  private static normalizeOpacity(opacity: number): number {
    return WatermarkUtil.clampValue(opacity, 0.0, 1.0);
  }

  public static async addWatermark(sourcePixelMap: image.PixelMap, 
                                    watermarkPixelMap: image.PixelMap,
                                    position: number = WatermarkUtil.POSITION_BOTTOM_RIGHT,
                                    opacity: number = WatermarkUtil.DEFAULT_OPACITY): Promise<image.PixelMap | undefined> {
    const startTime = Date.now();
    
    if (!WatermarkUtil.validatePixelMap(sourcePixelMap) || 
        !WatermarkUtil.validatePixelMap(watermarkPixelMap)) {
      console.error(WatermarkUtil.TAG, 'Invalid source or watermark pixelMap');
      return undefined;
    }

    try {
      const sourceInfo = sourcePixelMap.getImageInfoSync();
      const watermarkInfo = watermarkPixelMap.getImageInfoSync();

      if (!sourceInfo || !watermarkInfo) {
        console.error(WatermarkUtil.TAG, 'Failed to get image info');
        return undefined;
      }

      const sourceSize = sourceInfo.size;
      const watermarkSize = watermarkInfo.size;

      console.info(WatermarkUtil.TAG, 
        `Processing watermark - Source: ${sourceSize.width}x${sourceSize.height}, ` +
        `Watermark: ${watermarkSize.width}x${watermarkSize.height}, ` +
        `Orientation: ${WatermarkUtil.getImageOrientation(sourceSize)}`);

      const normalizedOpacity = WatermarkUtil.normalizeOpacity(opacity);
      const scaledWatermarkSize = WatermarkUtil.calculateWatermarkSize(sourceSize, watermarkSize);
      
      console.debug(WatermarkUtil.TAG, 
        `Scaling watermark from ${watermarkSize.width}x${watermarkSize.height} ` +
        `to ${scaledWatermarkSize.width}x${scaledWatermarkSize.height}`);

      const scaledWatermark = await WatermarkUtil.scaleWatermark(watermarkPixelMap, scaledWatermarkSize);
      
      if (!scaledWatermark) {
        console.error(WatermarkUtil.TAG, 'Failed to scale watermark');
        return undefined;
      }

      const resultPixelMap = await WatermarkUtil.combineImages(
        sourcePixelMap, 
        scaledWatermark, 
        sourceSize, 
        scaledWatermarkSize,
        position,
        normalizedOpacity
      );
      
      scaledWatermark.release();
      
      if (resultPixelMap) {
        const duration = Date.now() - startTime;
        WatermarkUtil.updateStatistics(WatermarkUtil.calculateImagePixelCount(sourceSize));
        WatermarkUtil.logOperationDetails(sourceSize, scaledWatermarkSize, position, duration);
      }
      
      return resultPixelMap;
    } catch (error) {
      console.error(WatermarkUtil.TAG, `addWatermark error: ${error.message}`);
      return undefined;
    }
  }

  private static calculateWatermarkSize(sourceSize: image.Size, watermarkSize: image.Size): image.Size {
    const maxWatermarkWidth = sourceSize.width * WatermarkUtil.WATERMARK_SCALE_RATIO;
    const maxWatermarkHeight = sourceSize.height * WatermarkUtil.WATERMARK_SCALE_RATIO;

    let scaleWidth = maxWatermarkWidth / watermarkSize.width;
    let scaleHeight = maxWatermarkHeight / watermarkSize.height;
    const scale = Math.min(scaleWidth, scaleHeight);

    let resultWidth = Math.floor(watermarkSize.width * scale);
    let resultHeight = Math.floor(watermarkSize.height * scale);

    resultWidth = WatermarkUtil.clampValue(resultWidth, WatermarkUtil.MIN_WATERMARK_SIZE, WatermarkUtil.MAX_WATERMARK_SIZE);
    resultHeight = WatermarkUtil.clampValue(resultHeight, WatermarkUtil.MIN_WATERMARK_SIZE, WatermarkUtil.MAX_WATERMARK_SIZE);

    return {
      width: resultWidth,
      height: resultHeight
    };
  }

  private static async scaleWatermark(watermarkPixelMap: image.PixelMap, targetSize: image.Size): Promise<image.PixelMap | undefined> {
    try {
      const sourceInfo = watermarkPixelMap.getImageInfoSync();
      const sourceSize = sourceInfo.size;
      
      const sourceBuffer = new ArrayBuffer(sourceSize.width * sourceSize.height * 4);
      watermarkPixelMap.readPixelsToBufferSync(sourceBuffer);
      const sourceArray = new Uint8Array(sourceBuffer);
      
      const targetBuffer = new ArrayBuffer(targetSize.width * targetSize.height * 4);
      const targetArray = new Uint8Array(targetBuffer);
      
      const scaleX = sourceSize.width / targetSize.width;
      const scaleY = sourceSize.height / targetSize.height;
      
      for (let y = 0; y < targetSize.height; y++) {
        for (let x = 0; x < targetSize.width; x++) {
          const sourceX = Math.floor(x * scaleX);
          const sourceY = Math.floor(y * scaleY);
          
          const sourceIndex = (sourceY * sourceSize.width + sourceX) * 4;
          const targetIndex = (y * targetSize.width + x) * 4;
          
          targetArray[targetIndex] = sourceArray[sourceIndex];
          targetArray[targetIndex + 1] = sourceArray[sourceIndex + 1];
          targetArray[targetIndex + 2] = sourceArray[sourceIndex + 2];
          targetArray[targetIndex + 3] = sourceArray[sourceIndex + 3];
        }
      }
      
      const scaledPixelMap = await image.createPixelMap(targetBuffer, {
        size: targetSize,
        editable: true
      });
      return scaledPixelMap;
    } catch (error) {
      console.error(WatermarkUtil.TAG, `scaleWatermark error: ${error.message}`);
      return undefined;
    }
  }

  private static calculateWatermarkPosition(sourceSize: image.Size, 
                                          watermarkSize: image.Size,
                                          position: number): MySize {
    let x: number = 0;
    let y: number = 0;

    switch (position) {
      case WatermarkUtil.POSITION_BOTTOM_RIGHT:
        x = sourceSize.width - watermarkSize.width - WatermarkUtil.WATERMARK_MARGIN;
        y = sourceSize.height - watermarkSize.height - WatermarkUtil.WATERMARK_MARGIN;
        break;
      case WatermarkUtil.POSITION_BOTTOM_LEFT:
        x = WatermarkUtil.WATERMARK_MARGIN;
        y = sourceSize.height - watermarkSize.height - WatermarkUtil.WATERMARK_MARGIN;
        break;
      case WatermarkUtil.POSITION_TOP_RIGHT:
        x = sourceSize.width - watermarkSize.width - WatermarkUtil.WATERMARK_MARGIN;
        y = WatermarkUtil.WATERMARK_MARGIN;
        break;
      case WatermarkUtil.POSITION_TOP_LEFT:
        x = WatermarkUtil.WATERMARK_MARGIN;
        y = WatermarkUtil.WATERMARK_MARGIN;
        break;
      case WatermarkUtil.POSITION_CENTER:
        x = Math.floor((sourceSize.width - watermarkSize.width) / 2);
        y = Math.floor((sourceSize.height - watermarkSize.height) / 2);
        break;
      default:
        x = sourceSize.width - watermarkSize.width - WatermarkUtil.WATERMARK_MARGIN;
        y = sourceSize.height - watermarkSize.height - WatermarkUtil.WATERMARK_MARGIN;
        break;
    }

    return { x, y };
  }

  private static async combineImages(sourcePixelMap: image.PixelMap, 
                                    watermarkPixelMap: image.PixelMap,
                                    sourceSize: image.Size,
                                    watermarkSize: image.Size,
                                    position: number,
                                    opacity: number): Promise<image.PixelMap | undefined> {
    try {
      const imageInfo = sourcePixelMap.getImageInfoSync();
      const pixelMapCapacity = sourceSize.width * sourceSize.height;
      const bufferData = new ArrayBuffer(pixelMapCapacity * 4);
      
      const resultPixelMap = await image.createPixelMap(bufferData, {
        size: sourceSize,
        editable: true
      });

      const sourceBuffer = new ArrayBuffer(pixelMapCapacity * 4);
      sourcePixelMap.readPixelsToBufferSync(sourceBuffer);
      const sourceArray = new Uint8Array(sourceBuffer);
      
      const watermarkBuffer = new ArrayBuffer(watermarkSize.width * watermarkSize.height * 4);
      watermarkPixelMap.readPixelsToBufferSync(watermarkBuffer);
      const watermarkArray = new Uint8Array(watermarkBuffer);
      
      const resultData = new Uint8Array(bufferData);

      const watermarkPos = WatermarkUtil.calculateWatermarkPosition(sourceSize, watermarkSize, position);

      for (let y = 0; y < sourceSize.height; y++) {
        for (let x = 0; x < sourceSize.width; x++) {
          const sourceIndex = (y * sourceSize.width + x) * 4;
          const resultIndex = sourceIndex;

          const isInWatermarkArea = x >= watermarkPos.x && x < watermarkPos.x + watermarkSize.width &&
                                   y >= watermarkPos.y && y < watermarkPos.y + watermarkSize.height;

          if (isInWatermarkArea) {
            const watermarkXLocal = x - watermarkPos.x;
            const watermarkYLocal = y - watermarkPos.y;
            const watermarkIndex = (watermarkYLocal * watermarkSize.width + watermarkXLocal) * 4;

            const watermarkAlpha = (watermarkArray[watermarkIndex + 3] / 255) * opacity;
            const sourceAlpha = sourceArray[sourceIndex + 3] / 255;

            const blendedAlpha = watermarkAlpha + sourceAlpha * (1 - watermarkAlpha);
            
            if (blendedAlpha > 0) {
              const r = (watermarkArray[watermarkIndex] * watermarkAlpha + 
                        sourceArray[sourceIndex] * sourceAlpha * (1 - watermarkAlpha)) / blendedAlpha;
              const g = (watermarkArray[watermarkIndex + 1] * watermarkAlpha + 
                        sourceArray[sourceIndex + 1] * sourceAlpha * (1 - watermarkAlpha)) / blendedAlpha;
              const b = (watermarkArray[watermarkIndex + 2] * watermarkAlpha + 
                        sourceArray[sourceIndex + 2] * sourceAlpha * (1 - watermarkAlpha)) / blendedAlpha;

              resultData[resultIndex] = WatermarkUtil.clampValue(Math.round(r), 0, 255);
              resultData[resultIndex + 1] = WatermarkUtil.clampValue(Math.round(g), 0, 255);
              resultData[resultIndex + 2] = WatermarkUtil.clampValue(Math.round(b), 0, 255);
              resultData[resultIndex + 3] = WatermarkUtil.clampValue(Math.round(blendedAlpha * 255), 0, 255);
            } else {
              resultData[resultIndex] = sourceArray[sourceIndex];
              resultData[resultIndex + 1] = sourceArray[sourceIndex + 1];
              resultData[resultIndex + 2] = sourceArray[sourceIndex + 2];
              resultData[resultIndex + 3] = sourceArray[sourceIndex + 3];
            }
          } else {
            resultData[resultIndex] = sourceArray[sourceIndex];
            resultData[resultIndex + 1] = sourceArray[sourceIndex + 1];
            resultData[resultIndex + 2] = sourceArray[sourceIndex + 2];
            resultData[resultIndex + 3] = sourceArray[sourceIndex + 3];
          }
        }
      }

      await resultPixelMap.writeBufferToPixels(bufferData);
      return resultPixelMap;
    } catch (error) {
      console.error(WatermarkUtil.TAG, `combineImages error: ${error.message}`);
      return undefined;
    }
  }
}
