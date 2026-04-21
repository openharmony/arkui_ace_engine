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
 * BackgroundUtil - 图片背景色工具类
 *
 * 功能说明：
 * 1. 根据图片主色调自动计算对比度背景色
 * 2. 支持多种背景色选择策略
 * 3. 使用WCAG 2.1标准计算对比度
 * 4. 自动计算图片平均颜色
 * 5. 支持自定义边距和对比度阈值
 *
 * 使用场景：
 * - 图片展示时增强视觉效果
 * - 为透明背景图片添加底色
 * - 提升图片在不同背景下的可读性
 * - 生成缩略图时统一背景
 */

import { image } from '@kit.ImageKit';

interface MySize {
  width: number;
  height: number;
}

export class BackgroundUtil {
  private static readonly TAG: string = 'BackgroundUtil';
  private static readonly MIN_CONTRAST_RATIO: number = 1.5;
  private static readonly BACKGROUND_PADDING: number = 20;
  private static readonly MIN_PADDING: number = 5;
  private static readonly MAX_PADDING: number = 100;
  private static readonly DEFAULT_SAMPLE_RATE: number = 10000;
  private static readonly MAX_SAMPLE_RATE: number = 50000;
  private static readonly MIN_VALID_PIXELS: number = 100;
  private static readonly LUMINANCE_RED: number = 0.2126;
  private static readonly LUMINANCE_GREEN: number = 0.7152;
  private static readonly LUMINANCE_BLUE: number = 0.0722;
  private static readonly GAMMA_THRESHOLD: number = 0.03928;
  private static readonly GAMMA_DIVISOR: number = 12.92;
  private static readonly GAMMA_EXPONENT: number = 2.4;
  private static readonly GAMMA_OFFSET: number = 0.055;
  private static readonly GAMMA_DIVISOR_OFFSET: number = 1.055;
  private static readonly CONTRAST_OFFSET: number = 0.05;
  private static readonly MAX_IMAGE_DIMENSION: number = 16384;
  private static readonly MIN_IMAGE_DIMENSION: number = 8;
  private static readonly MAX_TOTAL_PIXELS: number = 268435456;
  private static readonly COLOR_WHITE: number[] = [255, 255, 255, 255];
  private static readonly COLOR_BLACK: number[] = [0, 0, 0, 255];
  private static readonly COLOR_LIGHT_GRAY: number[] = [240, 240, 240, 255];
  private static readonly COLOR_DARK_GRAY: number[] = [20, 20, 20, 255];
  private static readonly COLOR_OFF_WHITE: number[] = [245, 245, 250, 255];
  private static readonly COLOR_OFF_BLACK: number[] = [30, 30, 35, 255];
  private static readonly COLOR_PURE_WHITE: number[] = [250, 250, 250, 255];
  private static readonly COLOR_CHARCOAL: number[] = [40, 40, 40, 255];
  private static readonly STRATEGY_AUTO: number = 0;
  private static readonly STRATEGY_LIGHT: number = 1;
  private static readonly STRATEGY_DARK: number = 2;
  private static readonly STRATEGY_CUSTOM: number = 3;
  private static operationCount: number = 0;
  private static lastOperationTime: number = 0;
  private static totalProcessedPixels: number = 0;
  private static averageContrastRatio: number = 0;

  public static getOperationCount(): number {
    return BackgroundUtil.operationCount;
  }

  public static getLastOperationTime(): number {
    return BackgroundUtil.lastOperationTime;
  }

  public static getTotalProcessedPixels(): number {
    return BackgroundUtil.totalProcessedPixels;
  }

  public static getAverageContrastRatio(): number {
    return BackgroundUtil.averageContrastRatio;
  }

  public static resetStatistics(): void {
    BackgroundUtil.operationCount = 0;
    BackgroundUtil.lastOperationTime = 0;
    BackgroundUtil.totalProcessedPixels = 0;
    BackgroundUtil.averageContrastRatio = 0;
  }

  private static updateStatistics(pixelCount: number, contrastRatio: number): void {
    BackgroundUtil.operationCount++;
    BackgroundUtil.lastOperationTime = Date.now();
    BackgroundUtil.totalProcessedPixels += pixelCount;

    if (BackgroundUtil.operationCount === 1) {
      BackgroundUtil.averageContrastRatio = contrastRatio;
    } else {
      BackgroundUtil.averageContrastRatio =
        (BackgroundUtil.averageContrastRatio * (BackgroundUtil.operationCount - 1) + contrastRatio)
          / BackgroundUtil.operationCount;
    }
  }

  private static validatePixelMap(pixelMap: image.PixelMap | null | undefined): boolean {
    if (!pixelMap) {
      console.error(BackgroundUtil.TAG, 'PixelMap is null or undefined');
      return false;
    }

    try {
      const imageInfo = pixelMap.getImageInfoSync();
      if (!imageInfo) {
        console.error(BackgroundUtil.TAG, 'Failed to get image info');
        return false;
      }

      const size = imageInfo.size;
      if (size.width < BackgroundUtil.MIN_IMAGE_DIMENSION ||
        size.height < BackgroundUtil.MIN_IMAGE_DIMENSION) {
        console.error(BackgroundUtil.TAG, `Image size too small: ${size.width}x${size.height}`);
        return false;
      }

      if (size.width > BackgroundUtil.MAX_IMAGE_DIMENSION ||
        size.height > BackgroundUtil.MAX_IMAGE_DIMENSION) {
        console.error(BackgroundUtil.TAG, `Image size too large: ${size.width}x${size.height}`);
        return false;
      }

      const totalPixels = size.width * size.height;
      if (totalPixels > BackgroundUtil.MAX_TOTAL_PIXELS) {
        console.error(BackgroundUtil.TAG, `Total pixels exceed limit: ${totalPixels}`);
        return false;
      }

      return true;
    } catch (error) {
      console.error(BackgroundUtil.TAG, `Validation error: ${error.message}`);
      return false;
    }
  }

  private static validatePadding(padding: number): number {
    return Math.max(BackgroundUtil.MIN_PADDING,
      Math.min(BackgroundUtil.MAX_PADDING, padding));
  }

  private static clampValue(value: number, min: number, max: number): number {
    return Math.max(min, Math.min(max, value));
  }

  private static roundSafe(number: number): number {
    return Math.round(BackgroundUtil.clampValue(number, 0, 255));
  }

  private static calculateTotalPixels(size: image.Size): number {
    return size.width * size.height;
  }

  private static calculateImageAspectRatio(width: number, height: number): number {
    if (height === 0) {
      return 0;
    }
    return width / height;
  }

  private static logOperationDetails(sourceSize: image.Size, backgroundColor: number[],
    contrastRatio: number, duration: number): void {
    console.info(BackgroundUtil.TAG,
      `Background operation completed - Source: ${sourceSize.width}x${sourceSize.height}, ` +
        `Background: RGB(${backgroundColor[0]}, ${backgroundColor[1]}, ${backgroundColor[2]}), ` +
        `Contrast: ${contrastRatio.toFixed(2)}, Duration: ${duration}ms`);
  }

  public static async addBackground(sourcePixelMap: image.PixelMap,
    padding: number = BackgroundUtil.BACKGROUND_PADDING,
    strategy: number = BackgroundUtil.STRATEGY_AUTO): Promise<image.PixelMap | undefined> {
    const startTime = Date.now();

    if (!BackgroundUtil.validatePixelMap(sourcePixelMap)) {
      console.error(BackgroundUtil.TAG, 'Invalid source pixelMap');
      return undefined;
    }

    try {
      const imageInfo = sourcePixelMap.getImageInfoSync();
      if (!imageInfo) {
        console.error(BackgroundUtil.TAG, 'Failed to get image info');
        return undefined;
      }

      const sourceSize = imageInfo.size;
      const validPadding = BackgroundUtil.validatePadding(padding);

      console.info(BackgroundUtil.TAG,
        `Processing background - Source: ${sourceSize.width}x${sourceSize.height}, ` +
          `Padding: ${validPadding}, Strategy: ${strategy}`);

      const averageColor = BackgroundUtil.calculateAverageColor(sourcePixelMap, sourceSize);
      const backgroundColor = BackgroundUtil.calculateContrastBackgroundColor(averageColor, strategy);

      const backgroundSize: MySize = {
        width: sourceSize.width + validPadding * 2,
        height: sourceSize.height + validPadding * 2
      };

      const contrastRatio = BackgroundUtil.calculateContrastRatio(averageColor, backgroundColor);

      console.debug(BackgroundUtil.TAG,
        `Selected background color - RGB(${backgroundColor[0]}, ${backgroundColor[1]}, ${backgroundColor[2]}), ` +
          `Contrast ratio: ${contrastRatio.toFixed(2)}`);

      const resultPixelMap = await BackgroundUtil.createBackgroundWithImage(
        sourcePixelMap,
        backgroundColor,
        sourceSize,
        backgroundSize,
        validPadding
      );

      if (resultPixelMap) {
        const duration = Date.now() - startTime;
        BackgroundUtil.updateStatistics(BackgroundUtil.calculateTotalPixels(sourceSize), contrastRatio);
        BackgroundUtil.logOperationDetails(sourceSize, backgroundColor, contrastRatio, duration);
      }

      return resultPixelMap;
    } catch (error) {
      console.error(BackgroundUtil.TAG, `addBackground error: ${error.message}`);
      return undefined;
    }
  }

  private static calculateAverageColor(pixelMap: image.PixelMap, size: image.Size): number[] {
    try {
      const bufferSize = size.width * size.height * 4;
      let bufferData = new ArrayBuffer(bufferSize);
      pixelMap.readPixelsToBufferSync(bufferData);
      const dataArray = new Uint8Array(bufferData);

      let totalR = 0;
      let totalG = 0;
      let totalB = 0;
      let totalA = 0;
      let validPixels = 0;

      const totalPixels = size.width * size.height;
      const sampleStep = Math.max(1, Math.floor(totalPixels / BackgroundUtil.DEFAULT_SAMPLE_RATE));
      const clampedSampleStep = Math.min(sampleStep, BackgroundUtil.MAX_SAMPLE_RATE);

      for (let i = 0; i < dataArray.length; i += 4 * clampedSampleStep) {
        const alpha = dataArray[i + 3];
        if (alpha > 0) {
          totalR += dataArray[i];
          totalG += dataArray[i + 1];
          totalB += dataArray[i + 2];
          totalA += alpha;
          validPixels++;
        }
      }

      if (validPixels >= BackgroundUtil.MIN_VALID_PIXELS) {
        const avgR = BackgroundUtil.roundSafe(totalR / validPixels);
        const avgG = BackgroundUtil.roundSafe(totalG / validPixels);
        const avgB = BackgroundUtil.roundSafe(totalB / validPixels);
        const avgA = BackgroundUtil.roundSafe(totalA / validPixels);

        console.debug(BackgroundUtil.TAG,
          `Average color calculated - RGB(${avgR}, ${avgG}, ${avgB}), ` +
            `Alpha: ${avgA}, Valid pixels: ${validPixels}`);

        return [avgR, avgG, avgB, avgA];
      }

      console.warn(BackgroundUtil.TAG,
        `Insufficient valid pixels: ${validPixels}, using default white color`);
      return [...BackgroundUtil.COLOR_WHITE];
    } catch (error) {
      console.error(BackgroundUtil.TAG, `calculateAverageColor error: ${error.message}`);
      return [...BackgroundUtil.COLOR_WHITE];
    }
  }

  private static calculateContrastBackgroundColor(averageColor: number[],
    strategy: number): number[] {
    const avgR = averageColor[0];
    const avgG = averageColor[1];
    const avgB = averageColor[2];
    const avgA = averageColor[3];

    const brightness = (avgR * 0.299 + avgG * 0.587 + avgB * 0.114) / 255;

    console.debug(BackgroundUtil.TAG,
      `Source brightness: ${brightness.toFixed(3)}, Alpha: ${(avgA / 255).toFixed(3)}`);

    const contrastColors = [
      BackgroundUtil.COLOR_WHITE,
      BackgroundUtil.COLOR_BLACK,
      BackgroundUtil.COLOR_LIGHT_GRAY,
      BackgroundUtil.COLOR_DARK_GRAY,
      BackgroundUtil.COLOR_OFF_WHITE,
      BackgroundUtil.COLOR_OFF_BLACK,
      BackgroundUtil.COLOR_PURE_WHITE,
      BackgroundUtil.COLOR_CHARCOAL
    ];

    let bestColor = contrastColors[0];
    let maxContrast = 0;

    if (strategy === BackgroundUtil.STRATEGY_LIGHT) {
      bestColor = BackgroundUtil.COLOR_BLACK;
    } else if (strategy === BackgroundUtil.STRATEGY_DARK) {
      bestColor = BackgroundUtil.COLOR_WHITE;
    } else {
      for (const color of contrastColors) {
        const contrast = BackgroundUtil.calculateContrastRatio(averageColor, color);
        if (contrast > maxContrast) {
          maxContrast = contrast;
          bestColor = color;
        }
      }
    }

    console.debug(BackgroundUtil.TAG,
      `Best background color - RGB(${bestColor[0]}, ${bestColor[1]}, ${bestColor[2]}), ` +
        `Contrast: ${maxContrast.toFixed(2)}`);

    return bestColor;
  }

  private static calculateContrastRatio(color1: number[], color2: number[]): number {
    const luminance1 = BackgroundUtil.calculateLuminance(color1);
    const luminance2 = BackgroundUtil.calculateLuminance(color2);

    const lighter = Math.max(luminance1, luminance2);
    const darker = Math.min(luminance1, luminance2);

    return (lighter + BackgroundUtil.CONTRAST_OFFSET) / (darker + BackgroundUtil.CONTRAST_OFFSET);
  }

  private static calculateLuminance(color: number[]): number {
    const r = BackgroundUtil.normalizeColorComponent(color[0]);
    const g = BackgroundUtil.normalizeColorComponent(color[1]);
    const b = BackgroundUtil.normalizeColorComponent(color[2]);

    return (BackgroundUtil.LUMINANCE_RED * r +
      BackgroundUtil.LUMINANCE_GREEN * g +
      BackgroundUtil.LUMINANCE_BLUE * b);
  }

  private static normalizeColorComponent(component: number): number {
    const normalized = component / 255;

    if (normalized <= BackgroundUtil.GAMMA_THRESHOLD) {
      return normalized / BackgroundUtil.GAMMA_DIVISOR;
    } else {
      const adjusted = (normalized + BackgroundUtil.GAMMA_OFFSET) / BackgroundUtil.GAMMA_DIVISOR_OFFSET;
      return Math.pow(adjusted, BackgroundUtil.GAMMA_EXPONENT);
    }
  }

  private static blendAlphaColors(foreground: number[], background: number[],
    alpha: number): number[] {
    const blendedAlpha = alpha + (background[3] / 255) * (1 - alpha);

    if (blendedAlpha > 0) {
      const r = (foreground[0] * alpha + background[0] * (background[3] / 255) * (1 - alpha)) / blendedAlpha;
      const g = (foreground[1] * alpha + background[1] * (background[3] / 255) * (1 - alpha)) / blendedAlpha;
      const b = (foreground[2] * alpha + background[2] * (background[3] / 255) * (1 - alpha)) / blendedAlpha;

      return [
        BackgroundUtil.roundSafe(r),
        BackgroundUtil.roundSafe(g),
        BackgroundUtil.roundSafe(b),
        BackgroundUtil.roundSafe(blendedAlpha * 255)
      ];
    }

    return [...background];
  }

  private static async createBackgroundWithImage(sourcePixelMap: image.PixelMap,
    backgroundColor: number[],
    sourceSize: image.Size,
    backgroundSize: image.Size,
    padding: number): Promise<image.PixelMap | undefined> {
    try {
      const imageInfoInfo = sourcePixelMap.getImageInfoSync();
      const pixelMapCapacity = backgroundSize.width * backgroundSize.height;
      let bufferData = new ArrayBuffer(pixelMapCapacity * 4);

      const resultPixelMap = await image.createPixelMap(bufferData, {
        size: backgroundSize,
        editable: true
      });

      const sourceBuffer = new ArrayBuffer(sourceSize.width * sourceSize.height * 4);
      sourcePixelMap.readPixelsToBufferSync(sourceBuffer);
      const resultData = new Uint8Array(bufferData);
      const sourceArray = new Uint8Array(sourceBuffer);

      const bgAlpha = backgroundColor[3] / 255;

      for (let y = 0; y < backgroundSize.height; y++) {
        for (let x = 0; x < backgroundSize.width; x++) {
          const resultIndex = (y * backgroundSize.width + x) * 4;

          const isInSourceArea = x >= padding &&
            x < padding + sourceSize.width &&
            y >= padding &&
            y < padding + sourceSize.height;

          if (isInSourceArea) {
            const sourceX = x - padding;
            const sourceY = y - padding;
            const sourceIndex = (sourceY * sourceSize.width + sourceX) * 4;

            const sourceAlpha = sourceArray[sourceIndex + 3] / 255;
            const blendedAlpha = sourceAlpha + bgAlpha * (1 - sourceAlpha);

            if (blendedAlpha > 0) {
              const r = (sourceArray[sourceIndex] * sourceAlpha +
                backgroundColor[0] * bgAlpha * (1 - sourceAlpha)) / blendedAlpha;
              const g = (sourceArray[sourceIndex + 1] * sourceAlpha +
                backgroundColor[1] * bgAlpha * (1 - sourceAlpha)) / blendedAlpha;
              const b = (sourceArray[sourceIndex + 2] * sourceAlpha +
                backgroundColor[2] * bgAlpha * (1 - sourceAlpha)) / blendedAlpha;

              resultData[resultIndex] = BackgroundUtil.roundSafe(r);
              resultData[resultIndex + 1] = BackgroundUtil.roundSafe(g);
              resultData[resultIndex + 2] = BackgroundUtil.roundSafe(b);
              resultData[resultIndex + 3] = BackgroundUtil.roundSafe(blendedAlpha * 255);
            } else {
              resultData[resultIndex] = backgroundColor[0];
              resultData[resultIndex + 1] = backgroundColor[1];
              resultData[resultIndex + 2] = backgroundColor[2];
              resultData[resultIndex + 3] = backgroundColor[3];
            }
          } else {
            resultData[resultIndex] = backgroundColor[0];
            resultData[resultIndex + 1] = backgroundColor[1];
            resultData[resultIndex + 2] = backgroundColor[2];
            resultData[resultIndex + 3] = backgroundColor[3];
          }
        }
      }

      await resultPixelMap.writeBufferToPixels(bufferData);
      return resultPixelMap;
    } catch (error) {
      console.error(BackgroundUtil.TAG, `createBackgroundWithImage error: ${error.message}`);
      return undefined;
    }
  }
}
