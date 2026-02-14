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
 * Image component fitOriginalSize property examples
 */
@Entry
@Component
struct ImageFitOriginalSizeExample {
  @State isFitOriginalSize: boolean = false
  @State imageWidth: number = 200
  @State imageHeight: number = 200

  build() {
    Column({ space: 20 }) {
      Text('FitOriginalSize 属性示例')
        .fontSize(20)
        .fontColor(Color.Gray)

      // Toggle 按钮
      Row({ space: 20 }) {
        Text('适配原始尺寸: ')
          .fontSize(16)
        Toggle({ type: ToggleType.Switch, isOn: this.isFitOriginalSize })
          .onChange((value: boolean) => {
            this.isFitOriginalSize = value
          })
      }

      Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.SpaceBetween }) {
        // 适配原始尺寸
        Column({ space: 15 }) {
          Text('适配原始尺寸 (true)')
            .fontSize(16)
            .fontColor(this.isFitOriginalSize ? Color.Green : Color.Gray)
          Image($r('app.media.app_icon'))
            .width(300)
            .height(200)
            .objectFit(ImageFit.Cover)
            .fitOriginalSize(this.isFitOriginalSize)
            .border({ width: 2, color: this.isFitOriginalSize ? Color.Green : Color.Transparent })
          Text('图片按原始宽高比显示，可能留白')
            .fontSize(14)
            .fontColor(Color.Gray)
        }

        // 不适配原始尺寸
        Column({ space: 15 }) {
          Text('不适配原始尺寸 (false)')
            .fontSize(16)
            .fontColor(!this.isFitOriginalSize ? Color.Green : Color.Gray)
          Image($r('app.media.app_icon'))
            .width(300)
            .height(200)
            .objectFit(ImageFit.Cover)
            .fitOriginalSize(this.isFitOriginalSize)
            .border({ width: 2, color: !this.isFitOriginalSize ? Color.Green : Color.Transparent })
          Text('图片填充整个容器，可能变形')
            .fontSize(14)
            .fontColor(Color.Gray)
        }
      }

      Divider().strokeWidth(2)

      Text('fitOriginalSize 属性控制是否保持图片原始宽高比')
        .fontSize(14)
        .fontColor(Color.Blue)
        .margin({ top: 10 })
    }
    .width('100%')
    .height('100%')
    .padding(20)
    .backgroundColor(Color.White)
  }
}
