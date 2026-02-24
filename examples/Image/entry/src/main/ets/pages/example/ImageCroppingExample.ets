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

/**
 * 图片裁剪示例 - 展示各种裁剪方式和效果
 */
@Entry
@Component
struct ImageCropping {
  @State cropMode: string = '中心';
  @State cropRatio: string = '1:1';
  @State cropWidth: number = 200;
  @State cropHeight: number = 200;
  @State rotation: number = 0;

  private cropModes: string[] = ['中心', '左上', '右上', '左下', '右下', '自定义'];
  private cropRatios: string[] = ['1:1', '4:3', '3:4', '16:9', '9:16', '自由'];

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('图片裁剪示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.Black)
          .margin({ top: 20, bottom: 10 })

        // 裁剪预览
        Column({ space: 15 }) {
          Text('裁剪预览 - ' + this.cropMode)
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Stack() {
            // 原图
            Image($r('app.media.app_icon'))
              .width(320)
              .height(320)
              .objectFit(ImageFit.Cover)
              .borderRadius(10)

            // 裁剪框
            Rectangle()
              .width(this.cropWidth)
              .height(this.cropHeight)
              .fill(Color.Transparent)
              .border({ width: 3, color: Color.White, radius: 0 })
              .position(this.getCropPosition())
              .rotate(this.rotation)
              .shadow({ radius: 10, color: '#80000000' })

            // 裁剪框辅助线
            if (this.cropMode !== '自定义') {
              Line()
                .width(this.cropWidth)
                .height(1)
                .stroke(Color.White)
                .position(this.getCropPosition())
                .offset({ x: 0, y: this.cropHeight / 2 })

              Line()
                .width(1)
                .height(this.cropHeight)
                .stroke(Color.White)
                .position(this.getCropPosition())
                .offset({ x: this.cropWidth / 2, y: 0 })
            }
          }
          .width(340)
          .height(340)
          .backgroundColor('#F0F0F0')
          .borderRadius(15)
          .shadow({ radius: 15, color: '#20000000' })

          // 裁剪信息
          Text('裁剪尺寸: ' + this.cropWidth + ' x ' + this.cropHeight + ' px')
            .fontSize(14)
            .fontColor(Color.Gray)
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F8F8FF')
        .borderRadius(15)

        Divider().strokeWidth(2).color('#E0E0E0')

        // 裁剪模式选择
        Column({ space: 15 }) {
          Text('裁剪位置:')
            .fontSize(16)
            .fontColor(Color.Gray)

          Row({ space: 10 }) {
            ForEach(this.cropModes, (mode: string) => {
              Button(mode)
                .fontSize(14)
                .backgroundColor(this.cropMode === mode ? Color.Blue : Color.Gray)
                .onClick(() => {
                  this.cropMode = mode;
                })
            })
          }
          .width('100%')
          .justifyContent(FlexAlign.SpaceEvenly)
          .flexWrap(FlexWrap.Wrap)
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F5F5F5')
        .borderRadius(10)

        // 裁剪比例选择
        Column({ space: 15 }) {
          Text('裁剪比例:')
            .fontSize(16)
            .fontColor(Color.Gray)

          Row({ space: 10 }) {
            ForEach(this.cropRatios, (ratio: string) => {
              Button(ratio)
                .fontSize(14)
                .backgroundColor(this.cropRatio === ratio ? Color.Green : Color.Gray)
                .onClick(() => {
                  this.cropRatio = ratio;
                  this.applyCropRatio(ratio);
                })
            })
          }
          .width('100%')
          .justifyContent(FlexAlign.SpaceEvenly)
          .flexWrap(FlexWrap.Wrap)
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F5F5F5')
        .borderRadius(10)

        // 自定义尺寸
        if (this.cropRatio === '自由') {
          Column({ space: 10 }) {
            Text('自定义宽度: ' + this.cropWidth + 'px')
              .fontSize(14)
              .fontColor(Color.Gray)
            Slider({
              value: this.cropWidth,
              min: 50,
              max: 300,
              step: 10
            })
              .width('100%')
              .onChange((value: number) => {
                this.cropWidth = value;
              })

            Text('自定义高度: ' + this.cropHeight + 'px')
              .fontSize(14)
              .fontColor(Color.Gray)
            Slider({
              value: this.cropHeight,
              min: 50,
              max: 300,
              step: 10
            })
              .width('100%')
              .onChange((value: number) => {
                this.cropHeight = value;
              })
          }
          .width('100%')
          .padding(15)
          .backgroundColor('#F5F5F5')
          .borderRadius(10)
        }

        // 旋转角度
        Column({ space: 10 }) {
          Text('裁剪框旋转: ' + this.rotation + '°')
            .fontSize(16)
            .fontColor(Color.Gray)

          Slider({
            value: this.rotation,
            min: -45,
            max: 45,
            step: 5
          })
            .width('100%')
            .onChange((value: number) => {
              this.rotation = value;
            })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F5F5F5')
        .borderRadius(10)

        Divider().strokeWidth(2).color('#E0E0E0')

        // 裁剪预设模板
        Column({ space: 15 }) {
          Text('裁剪预设模板:')
            .fontSize(18)
          .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Grid() {
            GridItem() {
              this.CropPreset('头像', '1:1', 200, 200)
            }
            GridItem() {
              this.CropPreset('横屏', '16:9', 280, 158)
            }
            GridItem() {
              this.CropPreset('竖屏', '9:16', 158, 280)
            }
            GridItem() {
              this.CropPreset('照片', '4:3', 240, 180)
            }
            GridItem() {
              this.CropPreset('封面', '3:4', 180, 240)
            }
            GridItem() {
              this.CropPreset('全景', '21:9', 300, 129)
            }
          }
          .columnsTemplate('1fr 1fr 1fr')
          .rowsGap(15)
          .columnsGap(15)
          .width('100%')
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#FFE4B5')
        .borderRadius(10)

        // 操作按钮
        Row({ space: 15 }) {
          Button('重置')
            .fontSize(14)
            .backgroundColor(Color.Gray)
            .onClick(() => {
              this.resetCrop();
            })

          Button('确认裁剪')
            .fontSize(14)
            .backgroundColor(Color.Green)
            .onClick(() => {
              // 执行裁剪
            })

          Button('保存')
            .fontSize(14)
            .backgroundColor(Color.Blue)
            .onClick(() => {
              // 保存裁剪结果
            })
        }
        .width('100%')
        .justifyContent(FlexAlign.Center)

        Text('裁剪可用于调整图片尺寸和构图')
          .fontSize(12)
          .fontColor(Color.Blue)
          .margin({ top: 10, bottom: 20 })
      }
      .width('100%')
      .padding({ left: 20, right: 20 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(Color.White)
  }

  @Builder
  CropPreset(name: string, ratio: string, width: number, height: number) {
    Column({ space: 8 }) {
      Text(name)
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
      Text(ratio)
        .fontSize(12)
        .fontColor(Color.Gray)
      Button('应用')
        .fontSize(12)
        .backgroundColor(Color.Orange)
        .onClick(() => {
          this.cropRatio = ratio;
          this.cropWidth = width;
          this.cropHeight = height;
        })
    }
  }

  getCropPosition(): Record<string, number> {
    const containerSize = 320;
    switch (this.cropMode) {
      case '左上':
        return { x: 10, y: 10 };
      case '右上':
        return { x: containerSize - this.cropWidth - 10, y: 10 };
      case '左下':
        return { x: 10, y: containerSize - this.cropHeight - 10 };
      case '右下':
        return { x: containerSize - this.cropWidth - 10, y: containerSize - this.cropHeight - 10 };
      case '中心':
      default:
        return { x: (containerSize - this.cropWidth) / 2, y: (containerSize - this.cropHeight) / 2 };
      case '自定义':
        return { x: 60, y: 60 };
    }
  }

  applyCropRatio(ratio: string): void {
    const baseSize = 200;
    switch (ratio) {
      case '1:1':
        this.cropWidth = baseSize;
        this.cropHeight = baseSize;
        break;
      case '4:3':
        this.cropWidth = baseSize;
        this.cropHeight = Math.round(baseSize * 3 / 4);
        break;
      case '3:4':
        this.cropWidth = Math.round(baseSize * 3 / 4);
        this.cropHeight = baseSize;
        break;
      case '16:9':
        this.cropWidth = baseSize;
        this.cropHeight = Math.round(baseSize * 9 / 16);
        break;
      case '9:16':
        this.cropWidth = Math.round(baseSize * 9 / 16);
        this.cropHeight = baseSize;
        break;
      case '自由':
        // 保持当前尺寸
        break;
    }
  }

  resetCrop(): void {
    this.cropMode = '中心';
    this.cropRatio = '1:1';
    this.cropWidth = 200;
    this.cropHeight = 200;
    this.rotation = 0;
  }
}
