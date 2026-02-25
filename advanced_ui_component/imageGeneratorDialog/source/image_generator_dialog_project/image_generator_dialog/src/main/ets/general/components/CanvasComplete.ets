/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { ImageGenerateState } from '../types/Declaration'
import { image } from '@kit.ImageKit';

/**
 * ResultImageShowArea - Result image display area with zoom and pan support
 * Supports: pinch to zoom, single finger drag, double-tap to zoom in/out
 */
@ComponentV2
export struct ResultImageShowArea {
  @Param pixelMap?: image.PixelMap | undefined = undefined;
  // Scale-related states
  @Local imageScale: number = 1.0;
  private minScale: number = 1.0;
  private maxScale: number = 4.0;
  // Position-related states
  @Local offsetX: number = 0;
  @Local offsetY: number = 0;
  // Gesture initial states
  @Local initialScale: number = 1.0;
  @Local initialOffsetX: number = 0;
  @Local initialOffsetY: number = 0;
  @Local isPinching: boolean = false;
  // Focus zoom-related states
  @Local focusX: number = 0;
  @Local focusY: number = 0;
  @Local focalPointX: number = 0;
  @Local focalPointY: number = 0;
  // Image and container dimensions
  @Local imageWidth: number = 386;
  @Local imageHeight: number = 386;
  @Local containerWidth: number = 386;
  @Local containerHeight: number = 386;
  @Local imageAspectRatio: number = 1.0;

  aboutToAppear(): void {
    // Initialize container dimensions (same as DoodleBoardArea)
    this.containerWidth = 386;
    this.containerHeight = 386;
  }

  // Snap scale value back to valid range
  snapScaleToBounds(): void {
    if (this.imageScale < this.minScale) {
      this.imageScale = this.minScale;
    } else if (this.imageScale > this.maxScale) {
      this.imageScale = this.maxScale;
    }
  }

  // Snap offset values back within bounds
  snapOffsetToBounds(): void {
    // If image is smaller than container, don't allow dragging (center display)
    if (this.imageWidth * this.imageScale < this.containerWidth) {
      this.offsetX = 0;
    } else {
      // Calculate and limit maximum allowed offset
      let maxOffsetX = Math.max(0, (this.imageWidth * this.imageScale) / 2 - this.containerWidth / 2);
      if (this.offsetX > maxOffsetX) {
        this.offsetX = maxOffsetX;
      } else if (this.offsetX < -maxOffsetX) {
        this.offsetX = -maxOffsetX;
      }
    }

    if (this.imageHeight * this.imageScale < this.containerHeight) {
      this.offsetY = 0;
    } else {
      // Calculate and limit maximum allowed offset
      let maxOffsetY = Math.max(0, (this.imageHeight * this.imageScale) / 2 - this.containerHeight / 2);
      if (this.offsetY > maxOffsetY) {
        this.offsetY = maxOffsetY;
      } else if (this.offsetY < -maxOffsetY) {
        this.offsetY = -maxOffsetY;
      }
    }
  }

  build() {
    Stack() {
      Column() {
        Image(this.pixelMap)
          .objectFit(ImageFit.Contain)
          .scale({ x: this.imageScale, y: this.imageScale })
          .translate({ x: this.offsetX, y: this.offsetY })
          .gesture(
            // Double-tap gesture
            TapGesture({ count: 2 })
              .onAction((event: GestureEvent) => {
                if (event.fingerList && event.fingerList.length > 0) {
                  // Get tap position relative to container center
                  let tapX = event.fingerList[0].localX - this.containerWidth / 2;
                  let tapY = event.fingerList[0].localY - this.containerHeight / 2;

                  if (this.imageScale === this.minScale) {
                    // Currently at original scale, zoom to 2x
                    let oldOffsetX = this.offsetX;
                    let oldOffsetY = this.offsetY;
                    let oldScale = this.imageScale;
                    let scaleRatio = 2.0 / oldScale;

                    this.imageScale = 2.0;
                    this.offsetX = tapX - (tapX - oldOffsetX) * scaleRatio;
                    this.offsetY = tapY - (tapY - oldOffsetY) * scaleRatio;

                    // Check and correct bounds
                    this.snapOffsetToBounds();
                  } else {
                    // Currently zoomed, return to original scale
                    this.imageScale = this.minScale;
                    this.offsetX = 0;
                    this.offsetY = 0;
                  }
                }
              })
          )
          .gesture(
            // Pinch gesture (zoom with focus as center)
            PinchGesture()
              .onActionStart((event: GestureEvent) => {
                // Mark that zooming is in progress
                this.isPinching = true;
                // Record initial scale value
                this.initialScale = this.imageScale;
                // Record initial offset
                this.initialOffsetX = this.offsetX;
                this.initialOffsetY = this.offsetY;
                // Calculate two-finger center point as focus
                if (event.fingerList && event.fingerList.length >= 2) {
                  let centerX = (event.fingerList[0].localX + event.fingerList[1].localX) / 2;
                  let centerY = (event.fingerList[0].localY + event.fingerList[1].localY) / 2;
                  // Focus offset relative to container center
                  this.focusX = centerX - this.containerWidth / 2;
                  this.focusY = centerY - this.containerHeight / 2;
                  // Calculate focus position in image coordinate system
                  this.focalPointX = (this.focusX - this.initialOffsetX) / this.initialScale;
                  this.focalPointY = (this.focusY - this.initialOffsetY) / this.initialScale;
                }
              })
              .onActionUpdate((event: GestureEvent) => {
                if (event.scale) {
                  // Calculate new scale value
                  let newScale = this.initialScale * event.scale;
                  this.imageScale = newScale;
                  // Use focus position in image coordinate system to calculate new offset
                  this.offsetX = this.focusX - this.focalPointX * this.imageScale;
                  this.offsetY = this.focusY - this.focalPointY * this.imageScale;
                }
              })
              .onActionEnd(() => {
                // Mark zooming as ended
                this.isPinching = false;
                // Snap back to limit range
                this.snapScaleToBounds();
                // Check offset bounds after zooming
                this.snapOffsetToBounds();
                // Reset drag initial offset
                this.initialOffsetX = this.offsetX;
                this.initialOffsetY = this.offsetY;
              })
          )
          .gesture(
            // Single-finger drag gesture
            PanGesture({ direction: PanDirection.All })
              .onActionStart(() => {
                // Only respond to drag when not zooming
                if (!this.isPinching) {
                  // Record finger position and current offset when drag starts
                  this.initialOffsetX = this.offsetX;
                  this.initialOffsetY = this.offsetY;
                }
              })
              .onActionUpdate((event: GestureEvent) => {
                // Only respond to drag when not zooming
                if (!this.isPinching && event.offsetX !== undefined && event.offsetY !== undefined) {
                  // Apply offset directly
                  let adjustedOffsetX = event.offsetX * this.imageScale;
                  let adjustedOffsetY = event.offsetY * this.imageScale;
                  this.offsetX = this.initialOffsetX + adjustedOffsetX;
                  this.offsetY = this.initialOffsetY + adjustedOffsetY;
                }
              })
              .onActionEnd(() => {
                // Only snap back when not zooming
                if (!this.isPinching) {
                  // Snap back within bounds
                  this.snapOffsetToBounds();
                }
              })
          )
      }
      .width('100%')
      .height('100%')
      .justifyContent(FlexAlign.Center)
      .alignItems(HorizontalAlign.Center)
      .backgroundColor('#FFFFFF')
      .borderRadius(24)
    }
    .width(this.containerWidth)
    .height(this.containerHeight)
    .borderRadius(24)
    .clip(true)
  }
}

@Extend(Text)
function iconFontStyle() {
  .fontFamily("HarmonyHeiTi")
  .fontColor("#000000")
  .fontSize(10)
  .fontWeight(400)
  .lineHeight(12)
  .textAlign(TextAlign.Center)
}

@ComponentV2
export struct ContinueOperateArea {
  @Param currentGenerateState: ImageGenerateState | undefined = undefined;
  @Event changeGenerateState: (state: ImageGenerateState) => void = (state: ImageGenerateState) => {
  };
  private limit: boolean = false;

  build() {
    Column() {
      Row() {
        Column() {
          Image($r('sys.media.reset_light'))
            .width(24)
            .height(24)
            .opacity(this.limit ? 0.3 : 1)
            .margin({
              bottom: 4
            })
          Text('重新编辑')
            .iconFontStyle()
            .fontColor(this.limit ? "#808080" : "#000000")
        }
        .width(123)
        .height(42)
        .alignItems(HorizontalAlign.Center)
        .onClick(() => {
        })

        Column() {
          Image($r('sys.media.creat_light'))
            .width(24)
            .height(24)
            .opacity(this.limit ? 0.3 : 1)
            .margin({
              bottom: 4
            })
          Text('继续创作')
            .iconFontStyle()
            .fontColor(this.limit ? "#808080" : "#000000")
        }
        .width(123)
        .height(42)
        .alignItems(HorizontalAlign.Center)
        .onClick(() => {
        })

        Column() {
          Image($r('sys.media.download_light'))
            .width(24)
            .height(24)
            .margin({
              bottom: 4
            })
          Text('下载')
            .iconFontStyle()
        }
        .width(123)
        .height(42)
        .alignItems(HorizontalAlign.Center)
        .onClick(() => {
        })

        Column() {
          Image($r('sys.media.stickers_light'))
            .width(24)
            .height(24)
            .margin({
              bottom: 4
            })
          Text('添加至贴纸')
            .iconFontStyle()
        }
        .width(123)
        .height(42)
        .alignItems(HorizontalAlign.Center)
        .onClick(() => {
        })

        Column() {
          Image($r('sys.media.add_to_text_light'))
            .width(24)
            .height(24)
            .margin({
              bottom: 4
            })
          Text('插入笔记')
            .iconFontStyle()
        }
        .width(123)
        .height(42)
        .alignItems(HorizontalAlign.Center)
        .onClick(() => {
        })
      }
      .justifyContent(FlexAlign.SpaceBetween)
      .width(618)
      .height(58)
      .margin({
        top: 18
      })
    }.width('100%')
  }
}

@ComponentV2
export struct HistoryArea {
  @Param resultList: string[] = [];
  private selectIndex: number = 0;

  build() {
    Column() {
      Scroll() {
        Column({ space: 12 }) {
          ForEach(this.resultList, (item: string, index: number) => {
            Column() {
              Image(item)
                .id('resultImage' + index)
                .width(56)
                .height(56)
                .borderRadius(10)
            }
            .width(60)
            .height(60)
            .padding(2)
            .borderRadius(11)
            .clip(true)
            .linearGradient(this.selectIndex == index ? {
              angle: 90,
              direction: GradientDirection.Left,
              colors: [['#44D1FF', 0.0], ['#A479FF', 0.52], ['#FF678C', 1.0]],
            } : undefined)
            .onClick(() => {
              this.selectIndex = index;
            })
          })
        }
        .width(79)
      }
      .scrollBar(BarState.Off)
      .scrollable(ScrollDirection.Vertical)
      .width(79)
      .height(386)
    }.width('100%')
  }
}

