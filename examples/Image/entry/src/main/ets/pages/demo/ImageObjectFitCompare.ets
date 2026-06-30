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
import { router } from '@kit.ArkUI';

@Entry
@Component
struct ImageObjectFitCompare {
  @State imageSrc: Resource = $r('app.media.startIcon');
  @State altSrc: Resource = $r('app.media.foreground');
  @State containerWidth: number = 200;
  @State containerHeight: number = 150;

  private objectFitList: { name: string; value: ImageFit; desc: string }[] = [
    { name: 'Cover', value: ImageFit.Cover, desc: '等比缩放，填满容器，可能裁剪' },
    { name: 'Contain', value: ImageFit.Contain, desc: '等比缩放，完整显示，可能有留白' },
    { name: 'Fill', value: ImageFit.Fill, desc: '拉伸填满容器，可能变形' },
    { name: 'None', value: ImageFit.None, desc: '保持原始大小，不做缩放' },
    { name: 'ScaleDown', value: ImageFit.ScaleDown, desc: '取None和Contain的较小值' },
  ];

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('Image ObjectFit 对比示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .textAlign(TextAlign.Center)
          .width('100%')
          .margin({ top: 20, bottom: 10 })

        Divider().strokeWidth(1).color(Color.Gray)

        Column({ space: 8 }) {
          Text('参考图片（原始显示）')
            .fontSize(14)
            .fontColor(Color.Gray)

          Image(this.imageSrc)
            .alt(this.altSrc)
            .objectFit(ImageFit.Cover)
            .width(this.containerWidth)
            .height(this.containerHeight)
            .borderRadius(8)
            .border({ width: 2, color: '#2196F3' })
        }
        .padding(15)
        .backgroundColor('#f8f8f8')
        .borderRadius(12)
        .width('100%')
        .alignItems(HorizontalAlign.Center)

        Column({ space: 8 }) {
          Text('容器尺寸调节')
            .fontSize(14)
            .fontColor(Color.Gray)

          Row({ space: 10 }) {
            Text('宽:')
              .fontSize(13)
            Slider({
              value: this.containerWidth,
              min: 100,
              max: 350,
              step: 10,
              style: SliderStyle.OutSet
            })
              .onChange((value: number) => {
                this.containerWidth = value;
              })
              .layoutWeight(1)
            Text(`${this.containerWidth}`)
              .fontSize(13)
              .width(35)
          }
          .width('100%')

          Row({ space: 10 }) {
            Text('高:')
              .fontSize(13)
            Slider({
              value: this.containerHeight,
              min: 80,
              max: 250,
              step: 10,
              style: SliderStyle.OutSet
            })
              .onChange((value: number) => {
                this.containerHeight = value;
              })
              .layoutWeight(1)
            Text(`${this.containerHeight}`)
              .fontSize(13)
              .width(35)
          }
          .width('100%')
        }
        .padding(10)
        .backgroundColor('#fff')
        .borderRadius(8)
        .width('100%')

        ForEach(this.objectFitList, (item: { name: string; value: ImageFit; desc: string }) => {
          Column({ space: 6 }) {
            Row({ space: 8 }) {
              Text(item.name)
                .fontSize(16)
                .fontWeight(FontWeight.Bold)
                .fontColor('#2196F3')
              Text(item.desc)
                .fontSize(12)
                .fontColor(Color.Gray)
                .layoutWeight(1)
            }
            .width('100%')

            Row({ space: 10 }) {
              Stack() {
                Image(this.imageSrc)
                  .alt(this.altSrc)
                  .objectFit(item.value)
                  .width(this.containerWidth)
                  .height(this.containerHeight)
                  .borderRadius(8)
                  .border({ width: 1, color: '#e0e0e0' })
              }
              .backgroundColor('#f0f0f0')
              .borderRadius(8)

              Column({ space: 4 }) {
                Text(`容器: ${this.containerWidth}x${this.containerHeight}`)
                  .fontSize(11)
                  .fontColor(Color.Gray)
                Text(`模式: ${item.name}`)
                  .fontSize(11)
                  .fontColor('#333')
              }
              .alignItems(HorizontalAlign.Start)
            }
            .width('100%')
          }
          .padding(12)
          .backgroundColor('#fff')
          .borderRadius(10)
          .width('100%')
        })

        Button('返回')
          .onClick(() => {
            router.back();
          })
          .width('80%')
          .margin({ bottom: 30 })
      }
      .padding({ left: 15, right: 15 })
    }
    .height('100%')
    .width('100%')
  }
}
