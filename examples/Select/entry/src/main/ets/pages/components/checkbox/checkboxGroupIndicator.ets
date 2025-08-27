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
export function CheckboxGroupIndicatorBuilder(name: string, param: Object) {
  CheckboxGroupIndicatorExample()
}

@Entry
@Component
struct CheckboxGroupIndicatorExample {
  pathStack: NavPathStack = new NavPathStack()

  build() {
    NavDestination() {
      Scroll() {
        Column() {
          // 全选按钮
          Flex({ justifyContent: FlexAlign.Start, alignItems: ItemAlign.Center }) {
            CheckboxGroup({ group: 'checkboxGroup' })
              .checkboxShape(CheckBoxShape.ROUNDED_SQUARE)
              .selectedColor('#007DFF')
              .onChange((itemName: CheckboxGroupResult) => {
                console.info('checkbox group content' + JSON.stringify(itemName));
              })
            Text('Select All')
              .fontSize(14)
              .lineHeight(20)
              .fontColor('#182431')
              .fontWeight(500)
          }

          // 选项1
          Flex({ justifyContent: FlexAlign.Start, alignItems: ItemAlign.Center }) {
            Checkbox({ name: 'checkbox1', group: 'checkboxGroup' })
              .selectedColor('#007DFF')
              .shape(CheckBoxShape.ROUNDED_SQUARE)
              .onChange((value: boolean) => {
                console.info('Checkbox1 change is' + value);
              })
            Text('Checkbox1')
              .fontSize(14)
              .lineHeight(20)
              .fontColor('#182431')
              .fontWeight(500)
          }.margin({ left: 36 })

          // 选项2
          Flex({ justifyContent: FlexAlign.Start, alignItems: ItemAlign.Center }) {
            Checkbox({ name: 'checkbox2', group: 'checkboxGroup' })
              .selectedColor('#007DFF')
              .shape(CheckBoxShape.ROUNDED_SQUARE)
              .onChange((value: boolean) => {
                console.info('Checkbox2 change is' + value);
              })
            Text('Checkbox2')
              .fontSize(14)
              .lineHeight(20)
              .fontColor('#182431')
              .fontWeight(500)
          }.margin({ left: 36 })

          // 选项3
          Flex({ justifyContent: FlexAlign.Start, alignItems: ItemAlign.Center }) {
            Checkbox({ name: 'checkbox3', group: 'checkboxGroup' })
              .selectedColor('#007DFF')
              .shape(CheckBoxShape.ROUNDED_SQUARE)
              .onChange((value: boolean) => {
                console.info('Checkbox3 change is' + value);
              })

            Text('Checkbox3')
              .fontSize(14)
              .lineHeight(20)
              .fontColor('#182431')
              .fontWeight(500)
          }.margin({ left: 36 })
        }
      }
    }
    .title('CheckboxGroupIndicator')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}