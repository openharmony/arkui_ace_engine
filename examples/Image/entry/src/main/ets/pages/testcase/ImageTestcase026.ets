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
 * 测试Image组件dynamicRangeMode属性
 * 验证HDR/SDR动态范围模式在不同配置下的表现
 */

@Entry
@Component
struct ImageDynamicRangeTestCase026 {
  @State currentModeIndex: number = 0

  private readonly DYNAMIC_MODES: Array<{ mode: DynamicRangeMode; label: string }> = [
    { mode: DynamicRangeMode.STANDARD, label: 'STANDARD' },
    { mode: DynamicRangeMode.HIGH, label: 'HIGH' },
    { mode: DynamicRangeMode.CONSTRAINT, label: 'CONSTRAINT' }
  ]

  build() {
    Column() {
      Text('Image dynamicRangeMode属性测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      Row() {
        ForEach(this.DYNAMIC_MODES, (config: { mode: DynamicRangeMode; label: string }, index: number) => {
          Column() {
            Text(config.label)
              .fontSize(14)
              .fontWeight(index === this.currentModeIndex ? FontWeight.Bold : FontWeight.Normal)
              .fontColor(index === this.currentModeIndex ? Color.Blue : Color.Gray)
              .margin({ bottom: 8 })

            Image($r('app.media.startIcon'))
              .width(120)
              .height(120)
              .dynamicRangeMode(config.mode)
              .objectFit(ImageFit.Cover)
              .border({
                width: index === this.currentModeIndex ? 3 : 1,
                color: index === this.currentModeIndex ? Color.Blue : Color.Gray
              })
              .borderRadius(8)
          }
          .margin({ left: 8, right: 8 })
        })
      }
      .margin({ bottom: 16 })

      Text(`当前模式: ${this.DYNAMIC_MODES[this.currentModeIndex].label}`)
        .fontSize(14)
        .fontColor(Color.Gray)

      Divider()
        .margin({ top: 16, bottom: 16 })

      Row({ space: 12 }) {
        ForEach(this.DYNAMIC_MODES, (config: { mode: DynamicRangeMode; label: string }, index: number) => {
          Button(config.label)
            .onClick(() => {
              this.currentModeIndex = index
            })
            .backgroundColor(index === this.currentModeIndex ? '#2196F3' : '#EEEEEE')
            .fontColor(index === this.currentModeIndex ? Color.White : Color.Gray)
        })
      }

      Divider()
        .margin({ top: 16, bottom: 16 })

      Text('HDR图片对比')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 8 })

      Row() {
        Image($r('app.media.background'))
          .width(100)
          .height(100)
          .dynamicRangeMode(DynamicRangeMode.STANDARD)
          .border({ width: 1, color: Color.Gray })
          .borderRadius(4)

        Image($r('app.media.background'))
          .width(100)
          .height(100)
          .dynamicRangeMode(DynamicRangeMode.HIGH)
          .border({ width: 1, color: Color.Blue })
          .borderRadius(4)

        Image($r('app.media.background'))
          .width(100)
          .height(100)
          .dynamicRangeMode(DynamicRangeMode.CONSTRAINT)
          .border({ width: 1, color: Color.Orange })
          .borderRadius(4)
      }
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}
