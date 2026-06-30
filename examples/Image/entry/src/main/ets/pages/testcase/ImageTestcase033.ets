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
 * 测试Image组件interpolation属性
 * 验证不同插值算法在图片缩放时的效果
 */

@Entry
@Component
struct ImageInterpolationTestCase033 {
  @State currentInterpIndex: number = 0

  private readonly INTERP_MODES: Array<{ mode: ImageInterpolation; label: string }> = [
    { mode: ImageInterpolation.None, label: 'None(无插值)' },
    { mode: ImageInterpolation.Low, label: 'Low(低质量)' },
    { mode: ImageInterpolation.Medium, label: 'Medium(中等)' },
    { mode: ImageInterpolation.High, label: 'High(高质量)' }
  ]

  build() {
    Column() {
      Text('Image interpolation属性测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      Row() {
        Image($r('app.media.startIcon'))
          .width(80)
          .height(80)
          .interpolation(this.INTERP_MODES[this.currentInterpIndex].mode)
          .objectFit(ImageFit.Cover)
          .border({ width: 2, color: Color.Blue })
          .borderRadius(8)

        Image($r('app.media.background'))
          .width(80)
          .height(80)
          .interpolation(this.INTERP_MODES[this.currentInterpIndex].mode)
          .objectFit(ImageFit.Cover)
          .border({ width: 2, color: Color.Blue })
          .borderRadius(8)
      }
      .margin({ bottom: 16 })

      Text(`当前插值: ${this.INTERP_MODES[this.currentInterpIndex].label}`)
        .fontSize(14)
        .fontColor(Color.Gray)
        .margin({ bottom: 12 })

      Row() {
        ForEach(this.INTERP_MODES, (config: { mode: ImageInterpolation; label: string }, index: number) => {
          Button(config.label)
            .fontSize(11)
            .onClick(() => {
              this.currentInterpIndex = index
            })
            .backgroundColor(index === this.currentInterpIndex ? '#2196F3' : '#EEEEEE')
            .fontColor(index === this.currentInterpIndex ? Color.White : Color.Gray)
            .margin({ left: 4, right: 4 })
        })
      }
      .margin({ bottom: 16 })

      Divider()

      Text('各插值模式对比(放大显示)')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .margin({ top: 16, bottom: 8 })

      Row() {
        ForEach(this.INTERP_MODES, (config: { mode: ImageInterpolation; label: string }) => {
          Column() {
            Image($r('app.media.startIcon'))
              .width(80)
              .height(80)
              .interpolation(config.mode)
              .sourceSize({ width: 20, height: 20 })
              .objectFit(ImageFit.Cover)
              .border({ width: 1, color: Color.Gray })
              .borderRadius(4)

            Text(config.label)
              .fontSize(10)
              .fontColor(Color.Gray)
              .margin({ top: 4 })
              .maxLines(2)
              .textOverflow({ overflow: TextOverflow.Ellipsis })
          }
          .margin({ left: 8, right: 8 })
        })
      }
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}
