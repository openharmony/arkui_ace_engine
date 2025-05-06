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
export function CheckboxMarkBuilder(name: string, param: Object) {
  CheckboxMarkExample()
}

@Entry
@Component
struct CheckboxMarkExample {
  pathStack: NavPathStack = new NavPathStack()

  build() {
    NavDestination() {
      Row() {
        Column() {
          Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
            Checkbox({ name: 'checkbox1', group: 'checkboxGroup' })
              .selectedColor($r('app.color.selected_color_2'))
              .shape(CheckBoxShape.ROUNDED_SQUARE)
              .onChange((value: boolean) => {
                console.info('Checkbox1 change is' + value);
              })
              .mark({
                strokeColor: Color.Black,
                size: 50,
                strokeWidth: 5
              })
              .unselectedColor(Color.Red)
              .width(30)
              .height(30)
            Text('Checkbox1').fontSize(20)
          }

          Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
            Checkbox({ name: 'checkbox2', group: 'checkboxGroup' })
              .selectedColor($r('app.color.selected_color_2'))
              .shape(CheckBoxShape.ROUNDED_SQUARE)
              .onChange((value: boolean) => {
                console.info('Checkbox2 change is' + value);
              })
              .width(30)
              .height(30)
            Text('Checkbox2').fontSize(20)
          }
        }
        .width('100%')
      }
      .height('100%')
    }
    .title('CheckboxMark')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}