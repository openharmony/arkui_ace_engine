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
 * Image component border properties examples
 */
@Entry
@Component
struct ImageBorderExample {
  @State borderWidth: number = 2
  @State borderRadius: number = 10
  @State borderColor: Color = Color.Black

  build() {
    Column({ space: 20 }) {
      Text('Border 属性示例')
        .fontSize(20)
        .fontColor(Color.Gray)

      // 边框宽度调整
      Column({ space: 15 }) {
        Text('边框宽度 (borderWidth)')
          .fontSize(16)
        Slider({ value: this.borderWidth, min: 0, max: 10, step: 1 })
          .onChange((value: number) => {
            this.borderWidth = value
          })
        Image($r('app.media.app_icon'))
          .width(200)
          .height(200)
          .border({ width: this.borderWidth, color: this.borderColor })
      }

      // 边框圆角
      Column({ space: 15 }) {
        Text('边框圆角 (borderRadius)')
          .fontSize(16)
        Slider({ value: this.borderRadius, min: 0, max: 50, step: 1 })
          .onChange((value: number) => {
            this.borderRadius = value
          })
        Image($r('app.media.app_icon'))
            .width(200)
            .height(200)
            .borderRadius(this.borderRadius)
            .border({ width: 2, color: this.borderColor })
          .border({ width: 2, color: Color.Green })
      }

      Divider().strokeWidth(2)

      // 边框颜色
      Column({ space: 15 }) {
        Text('边框颜色 (borderColor)')
          .fontSize(16)
        Row({ space: 10 }) {
          ForEach([Color.Black, Color.Red, Color.Green, Color.Blue, Color.Yellow, Color.Pink], (color: Color) => {
            Column({ space: 5 }) {
              Text(color.toString())
                .fontSize(14)
              Button('选择')
                .onClick(() => {
                  this.borderColor = color
                })
                .border({ width: 2, color: color })
            }
          })
        }
      }

      Divider().strokeWidth(2)

      // 说明
      Column({ space: 15 }) {
        Text('borderWidth/borderRadius/borderColor 控制图片边框样式')
          .fontSize(14)
          .fontColor(Color.Blue)
      }

      // 组合示例
      Column({ space: 20 }) {
        Text('组合效果示例')
          .fontSize(16)
        Image($r('app.media.app_icon'))
          .width(250)
          .height(250)
          .border({ width: 3, color: this.borderColor, radius: this.borderRadius })
      }

      Divider().strokeWidth(2)

      Text('当前设置: 宽度' + this.borderWidth + ' 圆角' + this.borderRadius)
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Blue)
        .margin({ top: 10 })
    }
    .width('100%')
    .height('100%')
    .padding(20)
    .backgroundColor(Color.White)
  }
}
