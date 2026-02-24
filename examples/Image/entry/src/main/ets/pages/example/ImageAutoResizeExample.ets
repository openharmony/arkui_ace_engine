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
 * Image component autoResize property examples
 */
@Entry
@Component
struct ImageAutoResizeExample {
  @State isAutoResize: boolean = false
  @State imageWidth: number = 200
  @State imageHeight: number = 200

  build() {
    Column({ space: 20 }) {
      Text('AutoResize 属性示例')
        .fontSize(20)
        .fontColor(Color.Gray)

      // Toggle 按钮
      Row({ space: 20 }) {
        Text('自动调整大小: ')
          .fontSize(16)
        Toggle({ type: ToggleType.Switch, isOn: this.isAutoResize })
          .onChange((value: boolean) => {
            this.isAutoResize = value
          })
      }

      Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.SpaceBetween }) {
        // 自动调整大小
        Column({ space: 15 }) {
          Text('自动调整大小 (true)')
            .fontSize(16)
            .fontColor(this.isAutoResize ? Color.Green : Color.Gray)
          Image($r('app.media.app_icon'))
            .width(300)
            .height(200)
            .autoResize(this.isAutoResize)
            .objectFit(ImageFit.Cover)
            .border({ width: 2, color: this.isAutoResize ? Color.Green : Color.Transparent })
          Text('根据容器大小自动调整图片尺寸')
            .fontSize(14)
            .fontColor(Color.Gray)
        }

        // 不自动调整
        Column({ space: 15 }) {
          Text('不适配自动调整大小 (false)')
            .fontSize(16)
            .fontColor(!this.isAutoResize ? Color.Green : Color.Gray)
          Image($r('app.media.app_icon'))
            .width(300)
            .height(200)
            .autoResize(this.isAutoResize)
            .objectFit(ImageFit.Cover)
            .border({ width: 2, color: !this.isAutoResize ? Color.Green : Color.Transparent })
          Text('图片按设定宽高显示')
            .fontSize(14)
            .fontColor(Color.Gray)
        }
      }

      Divider().strokeWidth(2)

      Text('autoResize 属性控制是否根据容器大小自动调整图片')
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
