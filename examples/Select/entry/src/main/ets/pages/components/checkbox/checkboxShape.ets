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
export function CheckboxShapeBuilder(name: string, param: Object) {
  CheckboxShapeExample()
}

@Entry
@Component
struct CheckboxShapeExample {
  pathStack: NavPathStack = new NavPathStack()

  build() {
    NavDestination() {
      Flex({ justifyContent: FlexAlign.SpaceEvenly }) {
        Checkbox({ name: 'checkbox1', group: 'checkboxGroup' })
          .select(true)
          .selectedColor($r('app.color.selected_color_1'))
          .shape(CheckBoxShape.CIRCLE)
          .onChange((value: boolean) => {
            console.info('Checkbox1 change is' + value);
          })
          .padding({ top: 250 })
        Checkbox({ name: 'checkbox2', group: 'checkboxGroup' })
          .select(false)
          .selectedColor($r('app.color.selected_color_2'))
          .shape(CheckBoxShape.ROUNDED_SQUARE)
          .onChange((value: boolean) => {
            console.info('Checkbox2 change is' + value);
          })
          .padding({ top: 250 })
      }
      .backgroundColor($r('app.color.background_color_8'))
      .height('100%')
    }
    .title('CheckboxShape')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}