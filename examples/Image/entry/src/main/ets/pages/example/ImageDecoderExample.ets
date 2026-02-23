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

import { image } from '@kit.ImageKit';
import { http } from '@kit.NetworkKit';

/**
 * 图片解码示例 - 展示如何使用 ImageKit 解码各种格式的图片
 */
@Entry
@Component
struct ImageDecoderExample {
  @State decodedImage: PixelMap | undefined = undefined;
  @State decodingStatus: string = '等待解码...';
  @State selectedFormat: string = 'PNG';
  @State imageQuality: number = 100;

  private formats: string[] = ['PNG', 'JPEG', 'GIF', 'WEBP', 'BMP'];

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('图片解码示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.Black)
          .margin({ top: 20, bottom: 10 })

        // 格式选择
        Column({ space: 10 }) {
          Text('选择图片格式:')
            .fontSize(16)
            .fontColor(Color.Gray)

          Row({ space: 10 }) {
            ForEach(this.formats, (format: string) => {
              Button(format)
                .fontSize(14)
                .backgroundColor(this.selectedFormat === format ? Color.Blue : Color.Gray)
                .onClick(() => {
                  this.selectedFormat = format;
                  this.decodeImage(format);
                })
            })
          }
          .width('100%')
          .justifyContent(FlexAlign.SpaceEvenly)
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F5F5F5')
        .borderRadius(10)

        // 质量设置
        Column({ space: 10 }) {
          Text('解码质量: ' + this.imageQuality + '%')
            .fontSize(16)
            .fontColor(Color.Gray)

          Slider({
            value: this.imageQuality,
            min: 10,
            max: 100,
            step: 10,
            style: SliderStyle.OutSet
          })
            .width('100%')
            .trackColor('#E0E0E0')
            .selectedColor(Color.Blue)
            .onChange((value: number) => {
              this.imageQuality = value;
            })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F5F5F5')
        .borderRadius(10)

        Divider().strokeWidth(2).color('#E0E0E0')

        // 解码按钮
        Button('开始解码')
          .fontSize(18)
          .width('80%')
          .height(50)
          .backgroundColor(Color.Green)
          .onClick(() => {
            this.decodeImage(this.selectedFormat);
          })

        // 解码状态
        Text('状态: ' + this.decodingStatus)
          .fontSize(16)
          .fontColor(this.decodingStatus.includes('成功') ? Color.Green :
                     this.decodingStatus.includes('失败') ? Color.Red : Color.Gray)
          .margin({ top: 10 })

        // 解码结果展示
        if (this.decodedImage) {
          Column({ space: 15 }) {
            Text('解码结果:')
              .fontSize(18)
              .fontWeight(FontWeight.Medium)
              .fontColor(Color.Black)

            Image(this.decodedImage)
              .width(250)
              .height(250)
              .objectFit(ImageFit.Contain)
              .border({ width: 2, color: Color.Blue, radius: 10 })
              .shadow({ radius: 10, color: '#80000000' })

            // 图片信息
            Column({ space: 8 }) {
              Text('格式: ' + this.selectedFormat)
                .fontSize(14)
              Text('质量: ' + this.imageQuality + '%')
                .fontSize(14)
              Text('尺寸: 250 x 250')
                .fontSize(14)
            }
            .width('100%')
            .padding(10)
            .backgroundColor('#F0F8FF')
            .borderRadius(8)
          }
          .width('100%')
          .padding(15)
          .backgroundColor('#FFF8DC')
          .borderRadius(10)
        }

        Divider().strokeWidth(2).color('#E0E0E0')

        // 解码选项说明
        Column({ space: 10 }) {
          Text('解码选项说明:')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Column({ space: 8 }) {
            this.DecodeOptionItem('PNG', '无损压缩，支持透明通道')
            this.DecodeOptionItem('JPEG', '有损压缩，文件小')
            this.DecodeOptionItem('GIF', '支持动画，256色')
            this.DecodeOptionItem('WEBP', '现代格式，压缩率高')
            this.DecodeOptionItem('BMP', '无压缩，文件大')
          }
          .width('100%')
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#E6E6FA')
        .borderRadius(10)

        Text('使用 image.createImageSource() 创建图片源')
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
  DecodeOptionItem(format: string, description: string) {
    Row({ space: 10 }) {
      Text(format + ':')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .width(60)
      Text(description)
        .fontSize(14)
        .fontColor(Color.Gray)
    }
    .width('100%')
  }

  async decodeImage(format: string): Promise<void> {
    this.decodingStatus = '解码中...';
    this.decodedImage = undefined;

    try {
      // 模拟图片数据 (实际应用中从文件或网络获取)
      const imageBuffer = await this.loadSampleImage(format);

      // 创建图片源
      const imageSource = image.createImageSource(imageBuffer);

      // 解码选项
      const decodingOptions: image.DecodingOptions = {
        editable: true,
        desiredSize: { width: 250, height: 250 },
        desiredPixelFormat: image.PixelMapFormat.RGBA_8888
      };

      // 创建 PixelMap
      this.decodedImage = await imageSource.createPixelMap(decodingOptions);
      this.decodingStatus = format + ' 格式解码成功';

      // 释放资源
      imageSource.release();
    } catch (error) {
      this.decodingStatus = format + ' 格式解码失败: ' + JSON.stringify(error);
    }
  }

  async loadSampleImage(format: string): Promise<ArrayBuffer> {
    // 模拟加载图片数据
    // 实际应用中应该从真实文件加载
    return new ArrayBuffer(0);
  }
}
