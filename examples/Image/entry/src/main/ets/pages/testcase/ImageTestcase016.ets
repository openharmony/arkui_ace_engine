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
 * 测试Image组件sourceSize属性
 * 验证不同sourceSize配置下的图片解码尺寸
 */

@Entry
@Component
struct ImageSourceSizeTestCase016 {
  @State sourceSizeWidth: number = 100
  @State sourceSizeHeight: number = 100
  @State currentSizeIndex: number = 0

  private readonly SIZE_CONFIGS: Array<{ width: number; height: number; label: string }> = [
    { width: 50, height: 50, label: '50x50' },
    { width: 100, height: 100, label: '100x100' },
    { width: 200, height: 200, label: '200x200' },
    { width: 300, height: 300, label: '300x300' },
    { width: 400, height: 400, label: '400x400' },
    { width: 50, height: 200, label: '50x200' },
    { width: 200, height: 50, label: '200x50' },
    { width: 0, height: 0, label: '0x0' },
    { width: 1000, height: 1000, label: '1000x1000' },
    { width: 1, height: 1, label: '1x1' }
  ]

  build() {
    Column() {
      Text('Image sourceSize属性测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      Row() {
        Image($r('app.media.startIcon'))
          .width(150)
          .height(150)
          .sourceSize({ width: this.sourceSizeWidth, height: this.sourceSizeHeight })
          .objectFit(ImageFit.Contain)
          .border({ width: 2, color: Color.Blue })
          .borderRadius(8)

        Column() {
          Text(`当前尺寸: ${this.sourceSizeWidth}x${this.sourceSizeHeight}`)
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
            .margin({ bottom: 8 })
          Text(`索引: ${this.currentSizeIndex}`)
            .fontSize(12)
            .fontColor(Color.Gray)
        }
        .margin({ left: 16 })
      }
      .margin({ bottom: 16 })

      Grid() {
        ForEach(this.SIZE_CONFIGS, (config: { width: number; height: number; label: string }, index: number) => {
          GridItem() {
            Column() {
              Text(config.label)
                .fontSize(12)
                .fontWeight(index === this.currentSizeIndex ? FontWeight.Bold : FontWeight.Normal)
                .fontColor(index === this.currentSizeIndex ? Color.Blue : Color.Gray)
            }
            .padding(8)
            .backgroundColor(index === this.currentSizeIndex ? '#E3F2FD' : '#FAFAFA')
            .borderRadius(4)
            .onClick(() => {
              this.currentSizeIndex = index
              this.sourceSizeWidth = config.width
              this.sourceSizeHeight = config.height
            })
          }
        })
      }
      .columnsTemplate('repeat(5, 1fr)')
      .rowsGap(8)
      .columnsGap(8)
      .padding(16)
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}
