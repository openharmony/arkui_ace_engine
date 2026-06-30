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
 * 测试Image组件opacity和shadow属性
 * 验证透明度和阴影在不同参数组合下的效果
 */

@Entry
@Component
struct ImageOpacityShadowTestCase030 {
  @State currentOpacity: number = 1.0
  @State shadowRadius: number = 10
  @State shadowColor: ResourceColor = Color.Black
  @State shadowOffsetX: number = 5
  @State shadowOffsetY: number = 5

  private readonly OPACITY_VALUES: number[] = [0.0, 0.1, 0.3, 0.5, 0.7, 0.9, 1.0]
  private readonly SHADOW_PRESETS: Array<{ radius: number; color: ResourceColor; offsetX: number; offsetY: number; label: string }> = [
    { radius: 5, color: Color.Black, offsetX: 2, offsetY: 2, label: '轻阴影' },
    { radius: 10, color: Color.Black, offsetX: 5, offsetY: 5, label: '中阴影' },
    { radius: 20, color: Color.Gray, offsetX: 10, offsetY: 10, label: '重阴影' },
    { radius: 0, color: Color.Black, offsetX: 0, offsetY: 0, label: '无阴影' },
    { radius: 15, color: Color.Red, offsetX: 3, offsetY: 3, label: '红色阴影' }
  ]

  build() {
    Column() {
      Text('Image opacity/shadow属性测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      Image($r('app.media.startIcon'))
        .width(150)
        .height(150)
        .opacity(this.currentOpacity)
        .shadow({
          radius: this.shadowRadius,
          color: this.shadowColor,
          offsetX: this.shadowOffsetX,
          offsetY: this.shadowOffsetY
        })
        .borderRadius(12)
        .margin({ bottom: 16 })

      Text(`透明度: ${this.currentOpacity}, 阴影半径: ${this.shadowRadius}`)
        .fontSize(14)
        .fontColor(Color.Gray)
        .margin({ bottom: 8 })

      Text('透明度选择')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 8 })

      Row() {
        ForEach(this.OPACITY_VALUES, (opacity: number) => {
          Column() {
            Column()
              .width(30)
              .height(30)
              .backgroundColor(Color.Blue)
              .opacity(opacity)
              .borderRadius(4)
              .border({ width: 1, color: Color.Gray })
            Text(`${opacity}`)
              .fontSize(10)
              .fontColor(this.currentOpacity === opacity ? Color.Blue : Color.Gray)
              .margin({ top: 4 })
          }
          .onClick(() => {
            this.currentOpacity = opacity
          })
        })
      }
      .margin({ bottom: 16 })

      Text('阴影预设')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .margin({ bottom: 8 })

      Row() {
        ForEach(this.SHADOW_PRESETS, (preset: { radius: number; color: ResourceColor; offsetX: number; offsetY: number; label: string }) => {
          Button(preset.label)
            .fontSize(11)
            .onClick(() => {
              this.shadowRadius = preset.radius
              this.shadowColor = preset.color
              this.shadowOffsetX = preset.offsetX
              this.shadowOffsetY = preset.offsetY
            })
            .margin({ left: 4, right: 4 })
        })
      }
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}
