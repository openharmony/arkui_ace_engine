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
export function CheckboxGroupBuilder(name: string, param: Object) {
  CheckboxGroupExample()
}

@Component
struct CheckboxGroupExample {
  pathStack: NavPathStack = new NavPathStack()
  @State isShow: boolean = true;

  build() {
    NavDestination() {
      Column() {
        Text('动态切换同一组group的checkbox，checkboxGroup状态正确')
          .margin({ top: 100, bottom: 100 })
        Column() {
          Flex({ justifyContent: FlexAlign.Start, alignItems: ItemAlign.Center }) {
            CheckboxGroup({ group: 'checkboxGroup' })
              .onChange((itemName: CheckboxGroupResult) => {
                console.info('checkbox group content' + JSON.stringify(itemName))
              })
            Text('Select All')
              .fontSize(14)
          }

          if (this.isShow) {
            Flex({ justifyContent: FlexAlign.Start, alignItems: ItemAlign.Center }) {
              Checkbox({ name: 'checkbox1', group: 'checkboxGroup' })
              Text('Checkbox1')
                .fontSize(14)
            }
            .margin({ left: 36 })
          }

          Flex({ justifyContent: FlexAlign.Start, alignItems: ItemAlign.Center }) {
            Checkbox({ name: 'checkbox2', group: 'checkboxGroup' })
            Text('Checkbox2')
              .fontSize(14)
          }
          .margin({ left: 36 })

          Flex({ justifyContent: FlexAlign.Start, alignItems: ItemAlign.Center }) {
            Checkbox({ name: 'checkbox3', group: 'checkboxGroup' })
            Text('Checkbox3')
              .fontSize(14)
          }
          .margin({ left: 36 })

          if (!this.isShow) {
            Flex({ justifyContent: FlexAlign.Start, alignItems: ItemAlign.Center }) {
              Checkbox({ name: 'checkbox4', group: 'checkboxGroup' })
                .select(true)
              Text('Checkbox4')
                .fontSize(14)
            }
            .margin({ left: 36 })
          }

          Button('click').onClick(() => {
            this.isShow = !this.isShow
          })
        }
      }.width('100%')
    }
    .title('CheckboxGroup')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}

export { CheckboxGroupExample };