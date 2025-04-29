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

@Builder
export function ButtonStyleBuilder(name: string, param: Object) {
  ButtonStyleExample()
}

@Entry
@Component
struct ButtonStyleExample {
  pathStack: NavPathStack = new NavPathStack()

  build() {
    NavDestination() {
      Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Start, justifyContent: FlexAlign.SpaceBetween }) {
        Text('Normal button')
          .fontSize(9)
          .fontColor($r('app.color.text_font_color'))
        Flex({ alignItems: ItemAlign.Center, justifyContent: FlexAlign.SpaceBetween }) {
          Button('OK', { type: ButtonType.Normal, stateEffect: true })
            .borderRadius(8)
            .backgroundColor($r('app.color.background_color_6'))
            .width(90)
            .onClick(() => {
              console.log('ButtonType.Normal')
            })
          Button({ type: ButtonType.Normal, stateEffect: true }) {
            Row() {
              LoadingProgress().width(20).height(20).margin({ left: 12 }).color($r('app.color.start_window_background'))
              Text('loading')
                .fontSize(12)
                .fontColor(0xffffff)
                .margin({ left: 5, right: 12 })
            }
            .alignItems(VerticalAlign.Center)
          }
          .borderRadius(8)
          .backgroundColor($r('app.color.background_color_6'))
          .width(90)
          .height(40)

          Button('Disable', { type: ButtonType.Normal, stateEffect: false }).opacity(0.4)
            .borderRadius(8)
            .backgroundColor($r('app.color.background_color_6'))
            .width(90)
        }

        Text('Capsule button')
          .fontSize(9)
          .fontColor($r('app.color.text_font_color'))
        Flex({ alignItems: ItemAlign.Center, justifyContent: FlexAlign.SpaceBetween }) {
          Button('OK', { type: ButtonType.Capsule, stateEffect: true })
            .backgroundColor($r('app.color.background_color_6'))
            .width(90)
          Button({ type: ButtonType.Capsule, stateEffect: true }) {
            Row() {
              LoadingProgress().width(20).height(20).margin({ left: 12 }).color($r('app.color.start_window_background'))
              Text('loading')
                .fontSize(12)
                .fontColor(0xffffff)
                .margin({ left: 5, right: 12 })
            }
            .alignItems(VerticalAlign.Center)
            .width(90)
            .height(40)
          }
          .backgroundColor($r('app.color.background_color_6'))

          Button('Disable', { type: ButtonType.Capsule, stateEffect: false }).opacity(0.4)
            .backgroundColor($r('app.color.background_color_6')).width(90)
        }

        Text('Circle button')
          .fontSize(9)
          .fontColor($r('app.color.text_font_color'))
        Flex({ alignItems: ItemAlign.Center, wrap: FlexWrap.Wrap }) {
          Button({ type: ButtonType.Circle, stateEffect: true }) {
            LoadingProgress().width(20).height(20).color($r('app.color.start_window_background'))
          }
          .width(55)
          .height(55)
          .backgroundColor($r('app.color.background_color_6'))

          Button({ type: ButtonType.Circle, stateEffect: true }) {
            LoadingProgress().width(20).height(20).color($r('app.color.start_window_background'))
          }
          .width(55)
          .height(55)
          .margin({ left: 20 })
          .backgroundColor($r('app.color.background_color_7'))
        }
      }
      .height(400)
      .padding({ left: 35, right: 35, top: 35 })
    }
    .title('ButtonStyle')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}