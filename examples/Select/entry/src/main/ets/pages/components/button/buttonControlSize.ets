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
export function ButtonControlSizeBuilder(name: string, param: Object) {
  ButtonControlSizeExample()
}

@Entry
@Component
struct ButtonControlSizeExample {
  pathStack: NavPathStack = new NavPathStack()

  build() {
    NavDestination() {
      Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Start, justifyContent: FlexAlign.SpaceBetween }) {
        Text('Normal size button')
          .fontSize(9)
          .fontColor($r('app.color.text_font_color'))
        Flex({ alignItems: ItemAlign.Center, justifyContent: FlexAlign.SpaceBetween }) {
          Button('Emphasized', { buttonStyle: ButtonStyleMode.EMPHASIZED });
          Button('Normal', { buttonStyle: ButtonStyleMode.NORMAL });
          Button('Textual', { buttonStyle: ButtonStyleMode.TEXTUAL });
        }

        Text('Small size button')
          .fontSize(9)
          .fontColor($r('app.color.text_font_color'))
        Flex({ alignItems: ItemAlign.Center, justifyContent: FlexAlign.SpaceBetween }) {
          Button('Emphasized', { controlSize: ControlSize.SMALL, buttonStyle: ButtonStyleMode.EMPHASIZED });
          Button('Normal', { controlSize: ControlSize.SMALL, buttonStyle: ButtonStyleMode.NORMAL });
          Button('Textual', { controlSize: ControlSize.SMALL, buttonStyle: ButtonStyleMode.TEXTUAL });
        }

        Text('Small size button')
          .fontSize(9)
          .fontColor($r('app.color.text_font_color'))
        Flex({ alignItems: ItemAlign.Center, justifyContent: FlexAlign.SpaceBetween }) {
          Button('Emphasized')
            .controlSize(ControlSize.SMALL)
            .buttonStyle(ButtonStyleMode.EMPHASIZED);
          Button('Normal')
            .controlSize(ControlSize.SMALL)
            .buttonStyle(ButtonStyleMode.NORMAL);
          Button('Textual')
            .controlSize(ControlSize.SMALL)
            .buttonStyle(ButtonStyleMode.TEXTUAL);
        }

      }
      .height(400)
      .padding({ left: 35, right: 35, top: 35 })
    }
    .title('ButtonControlSize')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}