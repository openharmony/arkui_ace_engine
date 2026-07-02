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
 * 测试Image组件resizable属性
 * 验证九宫格拉伸在不同slice配置下的效果
 */

@Entry
@Component
struct ImageResizableTestCase022 {
  @State currentSliceIndex: number = 0
  @State resizableEnabled: boolean = true

  private readonly SLICE_CONFIGS: Array<ResizableOptions> = [
    { slice: { left: '0', right: '0', top: '0', bottom: '0' } },
    { slice: { left: '10', right: '10', top: '10', bottom: '10' } },
    { slice: { left: '20', right: '20', top: '20', bottom: '20' } },
    { slice: { left: '50', right: '50', top: '50', bottom: '50' } },
    { slice: { left: '5', right: '5', top: '50', bottom: '50' } },
    { slice: { left: '50', right: '50', top: '5', bottom: '5' } }
  ]

  build() {
    Column() {
      Text('Image resizable属性测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      Row() {
        Column() {
          Text('resizable启用')
            .fontSize(14)
            .margin({ bottom: 8 })
          Image($r('app.media.startIcon'))
            .width(200)
            .height(200)
            .resizable(this.resizableEnabled ? this.SLICE_CONFIGS[this.currentSliceIndex] : undefined)
            .objectFit(ImageFit.Fill)
            .border({ width: 2, color: Color.Blue })
            .borderRadius(8)
        }
        .margin({ right: 16 })

        Column() {
          Text('resizable禁用')
            .fontSize(14)
            .margin({ bottom: 8 })
          Image($r('app.media.startIcon'))
            .width(200)
            .height(200)
            .objectFit(ImageFit.Fill)
            .border({ width: 2, color: Color.Gray })
            .borderRadius(8)
        }
      }
      .margin({ bottom: 16 })

      Text(`当前slice配置: ${JSON.stringify(this.SLICE_CONFIGS[this.currentSliceIndex].slice)}`)
        .fontSize(12)
        .fontColor(Color.Gray)
        .margin({ bottom: 8 })

      Grid() {
        ForEach(this.SLICE_CONFIGS, (_: ResizableOptions, index: number) => {
          GridItem() {
            Column() {
              Text(`Slice ${index + 1}`)
                .fontSize(12)
                .fontWeight(index === this.currentSliceIndex ? FontWeight.Bold : FontWeight.Normal)
                .fontColor(index === this.currentSliceIndex ? Color.Blue : Color.Gray)
            }
            .padding(10)
            .backgroundColor(index === this.currentSliceIndex ? '#E3F2FD' : '#FAFAFA')
            .borderRadius(4)
            .onClick(() => {
              this.currentSliceIndex = index
            })
          }
        })
      }
      .columnsTemplate('repeat(3, 1fr)')
      .rowsGap(8)
      .columnsGap(8)
      .padding(16)

      Button(`resizable: ${this.resizableEnabled ? '开启' : '关闭'}`)
        .onClick(() => {
          this.resizableEnabled = !this.resizableEnabled
        })
        .margin({ top: 16 })
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}
