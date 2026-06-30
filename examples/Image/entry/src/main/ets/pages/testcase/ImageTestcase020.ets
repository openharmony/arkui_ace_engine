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
 * 测试Image组件copyOption属性
 * 验证不同复制选项下的图片行为
 */

@Entry
@Component
struct ImageCopyOptionTestCase020 {
  @State currentCopyOption: CopyOptions = CopyOptions.None
  @State currentOptionIndex: number = 0
  @State isDraggable: boolean = false

  private readonly COPY_OPTIONS: Array<{ option: CopyOptions; label: string }> = [
    { option: CopyOptions.None, label: 'None' },
    { option: CopyOptions.InApp, label: 'InApp' },
    { option: CopyOptions.LocalDevice, label: 'LocalDevice' },
    { option: CopyOptions.CrossDevice, label: 'CrossDevice' }
  ]

  build() {
    Column() {
      Text('Image copyOption属性测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      Row() {
        Column() {
          Text('copyOption测试图片')
            .fontSize(14)
            .margin({ bottom: 8 })
          Image($r('app.media.startIcon'))
            .width(120)
            .height(120)
            .copyOption(this.currentCopyOption)
            .draggable(this.isDraggable)
            .border({ width: 2, color: Color.Blue })
            .borderRadius(8)
        }

        Column() {
          Text('当前配置')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
            .margin({ bottom: 12 })

          Text(`copyOption: ${this.COPY_OPTIONS[this.currentOptionIndex].label}`)
            .fontSize(12)
            .margin({ bottom: 4 })

          Text(`draggable: ${this.isDraggable}`)
            .fontSize(12)
            .fontColor(this.isDraggable ? Color.Green : Color.Gray)
        }
        .margin({ left: 16 })
      }
      .margin({ bottom: 16 })

      Divider()

      Text('copyOption选项')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .margin({ top: 16, bottom: 8 })

      Grid() {
        ForEach(this.COPY_OPTIONS, (config: { option: CopyOptions; label: string }, index: number) => {
          GridItem() {
            Column() {
              Text(config.label)
                .fontSize(14)
                .fontWeight(index === this.currentOptionIndex ? FontWeight.Bold : FontWeight.Normal)
                .fontColor(index === this.currentOptionIndex ? Color.Blue : Color.Gray)
            }
            .padding(12)
            .backgroundColor(index === this.currentOptionIndex ? '#E3F2FD' : '#FAFAFA')
            .borderRadius(6)
            .onClick(() => {
              this.currentOptionIndex = index
              this.currentCopyOption = config.option
            })
          }
        })
      }
      .columnsTemplate('repeat(4, 1fr)')
      .rowsGap(8)
      .columnsGap(8)

      Row({ space: 12 }) {
        Button(`切换draggable: ${this.isDraggable}`)
          .onClick(() => {
            this.isDraggable = !this.isDraggable
          })
          .margin({ top: 16 })
      }
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}
