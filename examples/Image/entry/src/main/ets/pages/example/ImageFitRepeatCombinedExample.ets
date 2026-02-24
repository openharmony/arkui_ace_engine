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
 * Image component objectFit and objectRepeat combined examples
 */
@Entry
@Component
struct ImageFitRepeatCombinedExample {
  @State selectedFit: ImageFit = ImageFit.Cover
  @State selectedRepeat: ImageRepeat = ImageRepeat.Repeat
  @State selectedRepeatXY: ImageRepeat = ImageRepeat.Repeat

  build() {
    Column({ space: 20 }) {
      Text('ObjectFit + ObjectRepeat 组合示例')
        .fontSize(20)
        .fontColor(Color.Gray)

      // Fit 选择
      Column({ space: 15 }) {
        Text('图片填充模式:')
          .fontSize(16)
        Row({ space: 10 }) {
          ForEach([ImageFit.Cover, ImageFit.Contain, ImageFit.Fill, ImageFit.None], (fit: ImageFit) => {
            Button(fit.toString())
              .onClick(() => {
                this.selectedFit = fit
              })
                .border({ width: 2, color: this.selectedFit === fit ? Color.Green : Color.Transparent })
          })
        }
      }

      Divider().strokeWidth(2)

      // Repeat 选择
      Column({ space: 15 }) {
        Text('图片重复模式:')
          .fontSize(16)
        Row({ space: 10 }) {
          ForEach([ImageRepeat.NoRepeat, ImageRepeat.RepeatX, ImageRepeat.RepeatY, ImageRepeat.Repeat], (repeat: ImageRepeat) => {
            Button(repeat.toString())
              .onClick(() => {
                this.selectedRepeat = repeat
              })
                .border({ width: 2, color: this.selectedRepeat === repeat ? Color.Green : Color.Transparent })
          })
        }
      }

      Divider().strokeWidth(2)

      // RepeatXY 选择
      Column({ space: 15 }) {
        Text('双向重复:')
          .fontSize(16)
        Row({ space: 10 }) {
          Button('X方向重复')
            .onClick(() => {
              this.selectedRepeatXY = ImageRepeat.RepeatX
              })
            .border({ width: 2, color: this.selectedRepeatXY === ImageRepeat.RepeatX ? Color.Green : Color.Transparent })
          Button('Y方向重复')
            .onClick(() => {
              this.selectedRepeatXY = ImageRepeat.RepeatY
              })
            .border({ width: 2, color: this.selectedRepeatXY === ImageRepeat.RepeatY ? Color.Green : Color.Transparent })
        }
      }

      Divider().strokeWidth(2)

      // 组合效果展示
      Column({ space: 20 }) {
        Text('组合效果预览')
          .fontSize(16)
        Image($r('app.media.app_icon'))
            .width(300)
            .height(300)
            .objectFit(this.selectedFit)
            .objectRepeat(this.selectedRepeat)
            .border({ width: 2, color: Color.Blue })
      }

      Divider().strokeWidth(2)

      Text('当前设置: Fit=' + this.selectedFit + ' Repeat=' + this.selectedRepeat)
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
