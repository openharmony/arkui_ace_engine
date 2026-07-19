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
 * 测试Image组件objectRepeat属性
 * 验证不同重复模式在图片显示中的效果
 */

@Entry
@Component
struct ImageRepeatTestCase032 {
  @State currentRepeatIndex: number = 0
  @State containerWidth: number = 300
  @State containerHeight: number = 200

  private readonly REPEAT_MODES: Array<{ mode: ImageRepeat; label: string }> = [
    { mode: ImageRepeat.NoRepeat, label: 'NoRepeat' },
    { mode: ImageRepeat.X, label: 'X(水平重复)' },
    { mode: ImageRepeat.Y, label: 'Y(垂直重复)' },
    { mode: ImageRepeat.XY, label: 'XY(双向重复)' }
  ]

  build() {
    Column() {
      Text('Image objectRepeat属性测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      Column() {
        Image($r('app.media.startIcon'))
          .width(this.containerWidth)
          .height(this.containerHeight)
          .objectRepeat(this.REPEAT_MODES[this.currentRepeatIndex].mode)
          .border({ width: 2, color: Color.Blue })
          .borderRadius(8)
      }
      .width(this.containerWidth)
      .height(this.containerHeight)
      .backgroundColor('#F5F5F5')
      .borderRadius(8)
      .margin({ bottom: 16 })

      Text(`当前模式: ${this.REPEAT_MODES[this.currentRepeatIndex].label}`)
        .fontSize(14)
        .fontColor(Color.Gray)
        .margin({ bottom: 12 })

      Row() {
        ForEach(this.REPEAT_MODES, (config: { mode: ImageRepeat; label: string }, index: number) => {
          Button(config.label)
            .fontSize(11)
            .onClick(() => {
              this.currentRepeatIndex = index
            })
            .backgroundColor(index === this.currentRepeatIndex ? '#2196F3' : '#EEEEEE')
            .fontColor(index === this.currentRepeatIndex ? Color.White : Color.Gray)
            .margin({ left: 4, right: 4 })
        })
      }
      .margin({ bottom: 16 })

      Divider()

      Text('各模式对比')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .margin({ top: 16, bottom: 8 })

      Row() {
        ForEach(this.REPEAT_MODES, (config: { mode: ImageRepeat; label: string }) => {
          Column() {
            Image($r('app.media.startIcon'))
              .width(120)
              .height(80)
              .objectRepeat(config.mode)
              .border({ width: 1, color: Color.Gray })
              .borderRadius(4)

            Text(config.label)
              .fontSize(10)
              .fontColor(Color.Gray)
              .margin({ top: 4 })
          }
          .margin({ left: 4, right: 4 })
        })
      }
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}
