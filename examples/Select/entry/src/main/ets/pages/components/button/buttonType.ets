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
export function ButtonTypeBuilder(name: string, param: Object) {
  ButtonTypeExample()
}

@Entry
@Component
struct ButtonTypeExample {
  pathStack: NavPathStack = new NavPathStack()

  build() {
    NavDestination() {
      Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Start, justifyContent: FlexAlign.SpaceBetween }) {
        Text('Rounded rectangle button with rounded corners by default.')
          .fontSize(9)
          .fontColor($r('app.color.text_font_color'))
        Flex({ alignItems: ItemAlign.Center, justifyContent: FlexAlign.SpaceBetween }) {
          Button('Rounded rectangle')
            .type(ButtonType.ROUNDED_RECTANGLE)
            .backgroundColor($r('app.color.background_color_6'))
            .controlSize(ControlSize.NORMAL)
            .width(180)
        }

        Text('Rounded rectangle button configured with a borderRadius of 5.')
          .fontSize(9)
          .fontColor($r('app.color.text_font_color'))
        Flex({ alignItems: ItemAlign.Center, justifyContent: FlexAlign.SpaceBetween }) {
          Button('Rounded rectangle')
            .type(ButtonType.ROUNDED_RECTANGLE)
            .backgroundColor($r('app.color.background_color_6'))
            .controlSize(ControlSize.NORMAL)
            .width(180)
            .borderRadius(5)
        }

        Text('Rounded rectangle button configured extra long text.')
          .fontSize(9)
          .fontColor($r('app.color.text_font_color'))
        Flex({ alignItems: ItemAlign.Center, justifyContent: FlexAlign.SpaceBetween }) {
          Button('Rounded rectangle Rounded rectangle Rounded rectangle Rounded rectangle')
            .type(ButtonType.ROUNDED_RECTANGLE)
            .backgroundColor($r('app.color.background_color_6'))
            .width(180)
            .labelStyle({ overflow: TextOverflow.Ellipsis, maxLines: 3, minFontSize: 0 })
        }
      }.height(400)
      .padding({ left: 35, right: 35, top: 35 })
    }
    .title('ButtonType')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}