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

import { picker } from '@kit.CoreFileKit';

/**
 * Filter effect types
 */
enum FilterType {
  NONE = 'none',
  GRAYSCALE = 'grayscale',
  SEPIA = 'sepia',
  BLUR = 'blur',
  BRIGHTNESS = 'brightness',
  CONTRAST = 'contrast'
}

/**
 * Animation effect types
 */
enum AnimationType {
  NONE = 'none',
  FADE_IN = 'fadeIn',
  SLIDE_IN = 'slideIn',
  SCALE_IN = 'scaleIn'
}

/**
 * Sticker data model
 */
interface StickerItem {
  id: string;
  imageSrc: string | number;
  x: number;
  y: number;
  width: number;
  height: number;
  rotation: number;
  scale: number;
  isSelected: boolean;
  opacity?: number;
  zIndex?: number;
  filter?: FilterType;
}

@Entry
@Component
struct Index {
  @State private stickerList: StickerItem[] = [];
  @State private selectedStickerId: string = '';
  @State private canvasWidth: number = 360;
  @State private canvasHeight: number = 600;
  @State private maxStickers: number = 50;

  addSticker(imageSrc: string | number) {
    if (this.stickerList.length >= this.maxStickers) {
      console.warn(`Maximum ${this.maxStickers} stickers allowed`);
      return;
    }

    const newSticker: StickerItem = {
      id: Date.now().toString(),
      imageSrc: imageSrc,
      x: this.canvasWidth / 2 - 50,
      y: this.canvasHeight / 2 - 50,
      width: 100,
      height: 100,
      rotation: 0,
      scale: 1,
      isSelected: false,
      opacity: 1,
      zIndex: this.stickerList.length,
      filter: FilterType.NONE
    };
    this.stickerList = [...this.stickerList, newSticker];
    this.selectSticker(newSticker.id);
  }

  selectSticker(id: string) {
    this.stickerList = this.stickerList.map(sticker => ({
      ...sticker,
      isSelected: sticker.id === id
    }));
    this.selectedStickerId = id;
  }

  deleteSelectedSticker() {
    if (this.selectedStickerId) {
      this.stickerList = this.stickerList.filter(s => s.id !== this.selectedStickerId);
      this.selectedStickerId = '';
    }
  }

  clearAllStickers() {
    this.stickerList = [];
    this.selectedStickerId = '';
  }

  updateSticker(id: string, x: number, y: number, scale: number, rotation: number) {
    this.stickerList = this.stickerList.map(sticker => {
      if (sticker.id === id) {
        return { ...sticker, x: x, y: y, scale: scale, rotation: rotation };
      }
      return sticker;
    });
  }

  duplicateSticker(id: string) {
    const sticker = this.stickerList.find(s => s.id === id);
    if (!sticker || this.stickerList.length >= this.maxStickers) return;

    const duplicatedSticker: StickerItem = {
      ...sticker,
      id: Date.now().toString(),
      x: sticker.x + 20,
      y: sticker.y + 20,
      isSelected: false,
      zIndex: this.stickerList.length
    };
    this.stickerList = [...this.stickerList, duplicatedSticker];
    this.selectSticker(duplicatedSticker.id);
  }

  getSelectedSticker(): StickerItem | undefined {
    return this.stickerList.find(s => s.id === this.selectedStickerId);
  }

  updateStickerOpacity(id: string, opacity: number) {
    const clampedOpacity = Math.max(0, Math.min(1, opacity));
    this.stickerList = this.stickerList.map(s => {
      if (s.id === id) {
        return { ...s, opacity: clampedOpacity };
      }
      return s;
    });
  }

  bringToFront(id: string) {
    const maxZ = Math.max(...this.stickerList.map(s => s.zIndex || 0));
    this.stickerList = this.stickerList.map(s => {
      if (s.id === id) {
        return { ...s, zIndex: maxZ + 1 };
      }
      return s;
    });
  }

  sendToBack(id: string) {
    const minZ = Math.min(...this.stickerList.map(s => s.zIndex || 0));
    this.stickerList = this.stickerList.map(s => {
      if (s.id === id) {
        return { ...s, zIndex: minZ - 1 };
      }
      return s;
    });
  }

  applyFilter(filterType: FilterType) {
    if (!this.selectedStickerId) return;
    this.stickerList = this.stickerList.map(s => {
      if (s.id === this.selectedStickerId) {
        return { ...s, filter: filterType };
      }
      return s;
    });
  }

  getFilterValue(filter: FilterType): string {
    switch (filter) {
      case FilterType.GRAYSCALE: return 'grayscale(100%)';
      case FilterType.SEPIA: return 'sepia(100%)';
      case FilterType.BLUR: return 'blur(3px)';
      case FilterType.BRIGHTNESS: return 'brightness(1.3)';
      case FilterType.CONTRAST: return 'contrast(1.5)';
      default: return 'none';
    }
  }

  async selectImageFromGallery() {
    try {
      const photoSelectOptions = new picker.PhotoSelectOptions();
      photoSelectOptions.MIMEType = picker.PhotoViewMIMETypes.IMAGE_TYPE;
      photoSelectOptions.maxSelectNumber = 1;

      const photoViewPicker = new picker.PhotoViewPicker();
      const result = await photoViewPicker.select(photoSelectOptions);

      if (result.photoUris && result.photoUris.length > 0) {
        this.addSticker(result.photoUris[0]);
      }
    } catch (err) {
      console.error('Failed to select image:', JSON.stringify(err));
    }
  }

  resetSticker(id: string) {
    this.stickerList = this.stickerList.map(s => {
      if (s.id === id) {
        return { ...s, rotation: 0, scale: 1, opacity: 1, filter: FilterType.NONE };
      }
      return s;
    });
  }

  centerSticker(id: string) {
    this.stickerList = this.stickerList.map(s => {
      if (s.id === id) {
        return {
          ...s,
          x: (this.canvasWidth - s.width * s.scale) / 2,
          y: (this.canvasHeight - s.height * s.scale) / 2
        };
      }
      return s;
    });
  }

  build() {
    Column() {
      // Title bar
      Row() {
        Text($r('app.string.sticker_title'))
          .fontSize(18)
          .fontWeight(FontWeight.Bold)
          .layoutWeight(1)
          .textAlign(TextAlign.Center)

        Button('Clear')
          .fontSize(12)
          .backgroundColor('#F44336')
          .fontColor(Color.White)
          .height(32)
          .margin({ left: 10 })
          .onClick(() => {
            this.clearAllStickers();
          })
      }
      .width('100%')
      .padding(12)
      .backgroundColor(Color.White)

      // Canvas area
      Stack() {
        Column()
          .width(this.canvasWidth)
          .height(this.canvasHeight)
          .backgroundColor($r('app.color.sticker_canvas_bg'))
          .border({ width: 2, color: $r('app.color.sticker_border') })

        ForEach(
          [...this.stickerList].sort((a, b) => (a.zIndex || 0) - (b.zIndex || 0)),
          (sticker: StickerItem) => {
            this.StickerComponent({
              sticker: sticker,
              onSelect: (id: string) => this.selectSticker(id),
              onUpdate: (id: string, x: number, y: number, scale: number, rotation: number) => {
                this.updateSticker(id, x, y, scale, rotation);
              },
              onDelete: (id: string) => {
                this.stickerList = this.stickerList.filter(s => s.id !== id);
                if (this.selectedStickerId === id) {
                  this.selectedStickerId = '';
                }
              }
            })
          },
          (sticker: StickerItem) => sticker.id
        )

        if (this.stickerList.length === 0) {
          Column() {
            Text('No stickers yet')
              .fontSize(16)
              .fontColor(Color.Gray)
              .margin({ top: 20 })
            Text('Add stickers from bottom panel')
              .fontSize(14)
              .fontColor(Color.LightGray)
              .margin({ top: 10 })
          }
          .width('100%')
          .height('100%')
          .justifyContent(FlexAlign.Center)
        }
      }
      .width('100%')
      .layoutWeight(1)
      .margin(10)

      // Status bar
      Row() {
        Text(`Stickers: ${this.stickerList.length}/${this.maxStickers}`)
          .fontSize(14)
          .fontColor('#666666')

        Blank()

        if (this.selectedStickerId) {
          Text('✓ Selected')
            .fontSize(14)
            .fontColor('#4CAF50')
        } else {
          Text('No Selection')
            .fontSize(14)
            .fontColor('#999999')
        }
      }
      .width('100%')
      .padding({ left: 16, right: 16, top: 8, bottom: 8 })
      .backgroundColor('#F5F5F5')

      // Control panel
      Column() {
        Button('Add Image')
          .width('90%')
          .height(40)
          .fontSize(16)
          .backgroundColor($r('app.color.sticker_primary'))
          .fontColor(Color.White)
          .margin({ top: 5, bottom: 10 })
          .onClick(() => {
            this.selectImageFromGallery();
          })

        Row() {
          Text('Sample Stickers:')
            .fontSize(14)
            .margin({ left: 20 })

          ForEach([0xFF6B6B, 0x4ECDC4, 0x45B7D1], (color: number, index: number) => {
            Button(`${index + 1}`)
              .width(50)
              .height(50)
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
              .fontColor(Color.White)
              .margin({ left: 10 })
              .backgroundColor(color)
              .onClick(() => {
                this.addSticker(color);
              })
          })
        }
        .width('100%')
        .margin({ bottom: 10 })

        if (this.selectedStickerId) {
          Column() {
            Row() {
              Button('Duplicate')
                .fontSize(14)
                .backgroundColor('#2196F3')
                .fontColor(Color.White)
                .onClick(() => {
                  this.duplicateSticker(this.selectedStickerId);
                })

              Button('Center')
                .fontSize(14)
                .backgroundColor('#4CAF50')
                .fontColor(Color.White)
                .margin({ left: 10 })
                .onClick(() => {
                  this.centerSticker(this.selectedStickerId);
                })

              Button('Reset')
                .fontSize(14)
                .backgroundColor('#FF9800')
                .fontColor(Color.White)
                .margin({ left: 10 })
                .onClick(() => {
                  this.resetSticker(this.selectedStickerId);
                })
            }
            .width('100%')
            .margin({ bottom: 10 })

            Row() {
              Button('Front')
                .fontSize(12)
                .backgroundColor(Color.Green)
                .onClick(() => this.bringToFront(this.selectedStickerId))

              Button('Back')
                .fontSize(12)
                .backgroundColor(Color.Orange)
                .margin({ left: 10 })
                .onClick(() => this.sendToBack(this.selectedStickerId))

              ForEach([FilterType.GRAYSCALE, FilterType.SEPIA, FilterType.BLUR], (filter: FilterType) => {
                Button(filter.slice(0, 4))
                  .fontSize(11)
                  .backgroundColor('#9E9E9E')
                  .fontColor(Color.White)
                  .margin({ left: 5 })
                  .onClick(() => this.applyFilter(filter))
              })
            }
            .width('100%')
            .margin({ bottom: 10 })

            Row() {
              Text('Opacity:')
                .fontSize(14)
                .margin({ left: 20 })

              Slider({ value: (this.getSelectedSticker()?.opacity || 1) * 100 })
                .width('60%')
                .block(true)
                .trackColor('#FF9800')
                .trackThickness(3)
                .onChange((value: number) => {
                  this.updateStickerOpacity(this.selectedStickerId, value / 100);
                })
                .colorStart(Color.Red)
                .colorEnd(Color.Green)
            }
            .width('100%')
            .margin({ bottom: 10 })

            Row() {
              Button('Delete')
                .fontSize(14)
                .backgroundColor('#F44336')
                .fontColor(Color.White)
                .onClick(() => {
                  this.deleteSelectedSticker();
                })
            }
          }
          .width('100%')
          .padding({ left: 20, right: 20, bottom: 20 })
        }
      }
      .width('100%')
      .backgroundColor(Color.White)
      .border({ width: { top: 1 }, color: $r('app.color.sticker_border') })
    }
    .width('100%')
    .height('100%')
    .backgroundColor($r('app.color.sticker_bg'))
  }

  @Builder
  StickerComponent(sticker: StickerItem, onSelect: (id: string) => void,
    onUpdate: (id: string, x: number, y: number, scale: number, rotation: number) => void,
    onDelete: (id: string) => void) {
    Stack() {
      if (typeof sticker.imageSrc === 'string') {
        Image(sticker.imageSrc)
          .width(sticker.width * sticker.scale)
          .height(sticker.height * sticker.scale)
          .rotate({ angle: sticker.rotation })
          .objectFit(ImageFit.Contain)
          .border(sticker.isSelected ? {
            width: 2,
            color: $r('app.color.sticker_primary'),
            style: BorderStyle.Dashed
          } : undefined)
          .filter(this.getFilterValue(sticker.filter || FilterType.NONE))
          .opacity(sticker.opacity || 1)
          .gesture(
            PanGesture({ direction: PanDirection.All })
              .onActionStart(() => {
                onSelect(sticker.id);
              })
              .onActionUpdate((event: GestureEvent) => {
                onUpdate(sticker.id, sticker.x + event.offsetX, sticker.y + event.offsetY, sticker.scale, sticker.rotation);
              })
          )
      } else {
        Column()
          .width(sticker.width * sticker.scale)
          .height(sticker.height * sticker.scale)
          .backgroundColor(sticker.imageSrc as number)
          .rotate({ angle: sticker.rotation })
          .border(sticker.isSelected ? {
            width: 2,
            color: $r('app.color.sticker_primary'),
            style: BorderStyle.Dashed
          } : undefined)
          .filter(this.getFilterValue(sticker.filter || FilterType.NONE))
          .opacity(sticker.opacity || 1)
          .gesture(
            PanGesture({ direction: PanDirection.All })
              .onActionStart(() => {
                onSelect(sticker.id);
              })
              .onActionUpdate((event: GestureEvent) => {
                onUpdate(sticker.id, sticker.x + event.offsetX, sticker.y + event.offsetY, sticker.scale, sticker.rotation);
              })
          )
      }

      if (sticker.isSelected) {
        Text('×')
          .width(24)
          .height(24)
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.White)
          .backgroundColor(Color.Red)
          .borderRadius(12)
          .position({ x: sticker.width * sticker.scale - 12, y: -12 })
          .textAlign(TextAlign.Center)
          .onClick(() => {
            onDelete(sticker.id);
          })

        Circle({ width: 20, height: 20 })
          .fill($r('app.color.sticker_primary'))
          .position({
            x: sticker.width * sticker.scale / 2 - 10,
            y: sticker.height * sticker.scale / 2 - 10
          })
          .gesture(
            PanGesture({ direction: PanDirection.All })
              .onActionUpdate((event: GestureEvent) => {
                const delta = (event.offsetX + event.offsetY) / 2;
                const newScale = Math.max(0.5, sticker.scale + delta / 100);
                onUpdate(sticker.id, sticker.x, sticker.y, newScale, sticker.rotation);
              })
          )

        Circle({ width: 20, height: 20 })
          .fill(Color.Green)
          .position({
            x: sticker.width * sticker.scale / 2 - 10,
            y: -sticker.height * sticker.scale / 2 - 10
          })
          .gesture(
            PanGesture({ direction: PanDirection.All })
              .onActionUpdate((event: GestureEvent) => {
                const angle = Math.atan2(
                  sticker.y + event.offsetY - sticker.y,
                  sticker.x + event.offsetX - sticker.x
                );
                const newRotation = angle * 180 / Math.PI;
                onUpdate(sticker.id, sticker.x, sticker.y, sticker.scale, newRotation);
              })
          )
      }
    }
    .position({ x: sticker.x, y: sticker.y })
    .width(sticker.width * sticker.scale)
    .height(sticker.height * sticker.scale)
    .onClick(() => {
      onSelect(sticker.id);
    })
  }
}
