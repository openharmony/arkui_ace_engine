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
 * 图片重复显示示例
 */
@Entry
@Component
struct ImageExample054 {
  @State imageRepeat: ImageRepeat = ImageRepeat.NoRepeat

  build() {
    Column() {
      Text('图片重复显示示例')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.png'))
        .width(200)
        .height(200)
        .objectFit(ImageFit.Cover)
        .imageRepeat(this.imageRepeat)
        .margin({ bottom: 20 })
        .border({ width: 1, color: Color.Gray })

      Row({ space: 10 }) {
        Button('不重复')
          .onClick(() => {
            this.imageRepeat = ImageRepeat.NoRepeat
          })
        Button('X轴')
          .onClick(() => {
            this.imageRepeat = ImageRepeat.RepeatX
          })
        Button('Y轴')
          .onClick(() => {
            this.imageRepeat = ImageRepeat.RepeatY
          })
        Button('XY轴')
          .onClick(() => {
            this.imageRepeat = ImageRepeat.Repeat
          })
      }

      Text('当前模式: ' + this.getRepeatName())
        .fontSize(14)
        .margin({ top: 10 })
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }

  getRepeatName(): string {
    switch (this.imageRepeat) {
      case ImageRepeat.NoRepeat:
        return '不重复'
      case ImageRepeat.RepeatX:
        return 'X轴重复'
      case ImageRepeat.RepeatY:
        return 'Y轴重复'
      case ImageRepeat.Repeat:
        return 'XY轴重复'
      default:
        return '未知'
    }
  }
}
