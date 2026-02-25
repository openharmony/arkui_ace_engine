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
 * Image component matchTextDirection property examples
 */
@Entry
@Component
struct ImageMatchTextDirectionExample {
  @State isMatchDirection: boolean = false
  @State imageWidth: number = 200
  @State imageHeight: number = 200

  build() {
    Column({ space: 20 }) {
      Text('MatchTextDirection 属性示例')
        .fontSize(20)
        .fontColor(Color.Gray)

      // Toggle 按钮
      Row({ space: 20 }) {
        Text('匹配文本方向: ')
          .fontSize(16)
        Toggle({ type: ToggleType.Switch, isOn: this.isMatchDirection })
          .onChange((value: boolean) => {
            this.isMatchDirection = value
          })
      }

      Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.SpaceBetween }) {
        // 不匹配 - 图片保持原方向
        Column({ space: 15 }) {
          Text('不匹配 (false)')
            .fontSize(16)
            .fontColor(this.isMatchDirection ? Color.Gray : Color.Green)
          Image($r('app.media.app_icon'))
            .width(this.imageWidth)
            .height(this.imageHeight)
            .matchTextDirection(this.isMatchDirection)
            .border({ width: 2, color: this.isMatchDirection ? Color.Transparent : Color.Green })
          Text('图片方向不随文本变化')
            .fontSize(14)
            .fontColor(Color.Gray)
        }

        // 匹配 - 图片方向跟随文本
        Column({ space: 15 }) {
          Text('匹配 (true)')
            .fontSize(16)
            .fontColor(this.isMatchDirection ? Color.Green : Color.Gray)
          Image($r('app.media.app_icon'))
            .width(this.imageWidth)
            .height(this.imageHeight)
            .matchTextDirection(this.isMatchDirection)
            .border({ width: 2, color: this.isMatchDirection ? Color.Green : Color.Transparent })
          Text('图片方向跟随文本方向')
            .fontSize(14)
            .fontColor(Color.Gray)
        }
      }

      Divider().strokeWidth(2)

      // 说明文字
      Text('matchTextDirection 属性控制图片是否跟随文本方向')
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
