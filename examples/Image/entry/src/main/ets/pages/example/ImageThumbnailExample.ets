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
 * 缩略图生成示例 - 展示如何生成不同尺寸的缩略图
 */
@Entry
@Component
struct ImageThumbnail {
  @State selectedSize: string = '小';
  @State customWidth: number = 100;
  @State customHeight: number = 100;
  @State quality: number = 80;

  private sizePresets: string[] = ['极小', '小', '中', '大', '超大'];
  private sizeMap: Map<string, number[]> = new Map([
    ['极小', [50, 50]],
    ['小', [100, 100]],
    ['中', [150, 150]],
    ['大', [200, 200]],
    ['超大', [300, 300]]
  ]);

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('缩略图生成示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.Black)
          .margin({ top: 20, bottom: 10 })

        // 原图预览
        Column({ space: 15 }) {
          Text('原图 (300x300):')
            .fontSize(16)
            .fontColor(Color.Gray)

          Image($r('app.media.app_icon'))
            .width(150)
            .height(150)
            .objectFit(ImageFit.Cover)
            .borderRadius(10)
            .border({ width: 2, color: Color.Blue })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F0F8FF')
        .borderRadius(10)

        Divider().strokeWidth(2).color('#E0E0E0')

        // 尺寸预设选择
        Column({ space: 15 }) {
          Text('选择缩略图尺寸:')
            .fontSize(16)
            .fontColor(Color.Gray)

          Row({ space: 10 }) {
            ForEach(this.sizePresets, (size: string) => {
              Button(size)
                .fontSize(14)
                .backgroundColor(this.selectedSize === size ? Color.Blue : Color.Gray)
                .onClick(() => {
                  this.selectedSize = size;
                  const dims = this.sizeMap.get(size) || [100, 100];
                  this.customWidth = dims[0];
                  this.customHeight = dims[1];
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

        // 缩略图预览
        Column({ space: 15 }) {
          Text('缩略图预览 (' + this.customWidth + 'x' + this.customHeight + '):')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Row({ space: 20 }) {
            // 缩略图
            Column({ space: 10 }) {
              Image($r('app.media.app_icon'))
                .width(this.customWidth / 2)
                .height(this.customHeight / 2)
                .objectFit(ImageFit.Cover)
                .borderRadius(8)
                .border({ width: 2, color: Color.Green })

              Text('缩略图')
                .fontSize(12)
                .fontColor(Color.Gray)
            }

            // 尺寸信息
            Column({ space: 8 }) {
              Text('尺寸信息:')
                .fontSize(14)
                .fontWeight(FontWeight.Medium)
              Text('宽度: ' + this.customWidth + 'px')
                .fontSize(12)
                .fontColor(Color.Gray)
              Text('高度: ' + this.customHeight + 'px')
                .fontSize(12)
                .fontColor(Color.Gray)
              Text('质量: ' + this.quality + '%')
                .fontSize(12)
                .fontColor(Color.Gray)
              Text('压缩比: ' + Math.round((1 - Math.sqrt(this.customWidth * this.customHeight / 90000)) * 100) + '%')
                .fontSize(12)
                .fontColor(Color.Gray)
            }
            .alignItems(HorizontalAlign.Start)
          }
          .width('100%')
          .justifyContent(FlexAlign.Center)
        }
        .width('100%')
        .padding(20)
        .backgroundColor('#F8F8FF')
        .borderRadius(15)

        Divider().strokeWidth(2).color('#E0E0E0')

        // 自定义尺寸
        Column({ space: 10 }) {
          Text('自定义宽度: ' + this.customWidth + 'px')
            .fontSize(14)
            .fontColor(Color.Gray)
          Slider({
            value: this.customWidth,
            min: 50,
            max: 300,
            step: 10
          })
            .width('100%')
            .onChange((value: number) => {
              this.customWidth = value;
            })

          Text('自定义高度: ' + this.customHeight + 'px')
            .fontSize(14)
            .fontColor(Color.Gray)
          Slider({
            value: this.customHeight,
            min: 50,
            max: 300,
            step: 10
          })
            .width('100%')
            .onChange((value: number) => {
              this.customHeight = value;
            })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F5F5F5')
        .borderRadius(10)

        // 质量设置
        Column({ space: 10 }) {
          Text('缩略图质量: ' + this.quality + '%')
            .fontSize(16)
            .fontColor(Color.Gray)

          Slider({
            value: this.quality,
            min: 10,
            max: 100,
            step: 5
          })
            .width('100%')
            .onChange((value: number) => {
              this.quality = value;
            })
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#F5F5F5')
        .borderRadius(10)

        Divider().strokeWidth(2).color('#E0E0E0')

        // 批量生成
        Column({ space: 15 }) {
          Text('批量生成缩略图:')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          Row({ space: 10 }) {
            ForEach(this.sizePresets, (size: string) => {
              const dims = this.sizeMap.get(size) || [100, 100];
              Column({ space: 8 }) {
                Image($r('app.media.app_icon'))
                  .width(dims[0] / 3)
                  .height(dims[1] / 3)
                  .objectFit(ImageFit.Cover)
                  .borderRadius(5)
                Text(size + '\n' + dims[0] + 'x' + dims[1])
                  .fontSize(10)
                  .fontColor(Color.Gray)
                  .textAlign(TextAlign.Center)
              }
            })
          }
          .width('100%')
          .justifyContent(FlexAlign.SpaceEvenly)
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#FFF8DC')
        .borderRadius(10)

        // 使用场景
        Column({ space: 10 }) {
          Text('缩略图使用场景:')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Black)

          this.UsageScenario('图片列表', '极小', '快速浏览大量图片')
          this.UsageScenario('相册网格', '小/中', '平衡清晰度和加载速度')
          this.UsageScenario('详情预览', '大', '查看图片细节')
          this.UsageScenario('全屏展示', '超大', '高质量显示')
        }
        .width('100%')
        .padding(15)
        .backgroundColor('#E6E6FA')
        .borderRadius(10)

        Row({ space: 15 }) {
          Button('生成缩略图')
            .fontSize(14)
            .backgroundColor(Color.Green)
            .onClick(() => {
              // 生成缩略图逻辑
            })

          Button('保存缩略图')
            .fontSize(14)
            .backgroundColor(Color.Blue)
            .onClick(() => {
              // 保存缩略图逻辑
            })
        }
        .width('100%')
        .justifyContent(FlexAlign.Center)

        Text('缩略图可节省存储空间和加载时间')
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
  UsageScenario(scenario: string, size: string, description: string) {
    Row({ space: 10 }) {
      Text(scenario + ':')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .width(80)
      Text(size + ' - ' + description)
        .fontSize(14)
        .fontColor(Color.Gray)
    }
    .width('100%')
  }
}
