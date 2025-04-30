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

class IsChecked {
  public checkedName: string = ''
  public isChecked: boolean = false

  constructor(checkedName: string, isChecked: boolean) {
    this.isChecked = isChecked
    this.checkedName = checkedName
  }
}

@Builder
export function CheckboxChangeBuilder(name: string, param: Object) {
  CheckboxChangeExample()
}

@Entry
@Component
struct CheckboxChangeExample {
  pathStack: NavPathStack = new NavPathStack()
  @State isSelectAll: boolean = false
  @State selectArray: Array<IsChecked> = []
  @State checkboxArray: Array<string> = ['checkbox1', 'checkbox2', 'checkbox3', 'checkbox4', 'checkbox5']
  @State checkedBoxArray: Array<string> = []

  build() {
    NavDestination() {
      Scroll() {
        Column() {
          Button('点击')
            .onClick((event: ClickEvent) => {
              console.log(JSON.stringify(this.selectArray))
              this.checkedBoxArray.forEach((item: string) => {
                if (this.checkboxArray.indexOf(item) != -1) {
                  this.checkboxArray.splice(this.checkboxArray.indexOf(item), 1)
                  this.isSelectAll = false
                }
              })
            })

          Flex({ justifyContent: FlexAlign.Start, alignItems: ItemAlign.Center }) {
            CheckboxGroup({ group: 'checkboxGroup' })
              .selectAll($$this.isSelectAll)
              .checkboxShape(CheckBoxShape.ROUNDED_SQUARE)
              .selectedColor('#007DFF')
              .onChange((itemName: CheckboxGroupResult) => {
                this.checkedBoxArray = itemName.name
                console.info('checkbox group content' + JSON.stringify(itemName))
              })
            Text('Select All')
              .fontSize(14)
              .lineHeight(20)
              .fontColor('#182431')
              .fontWeight(500)
          }

          ForEach(this.checkboxArray, (item: string) => {
            Flex({ justifyContent: FlexAlign.Start, alignItems: ItemAlign.Center }) {
              Checkbox({ name: item, group: 'checkboxGroup' })
                .selectedColor('#007DFF')
                .shape(CheckBoxShape.ROUNDED_SQUARE)
                .onChange((value: boolean) => {
                  const index = this.selectArray.findIndex(obj => obj.checkedName === item);
                  if (index !== -1) {
                    this.selectArray[index].isChecked = value
                  } else {
                    this.selectArray.push(new IsChecked(item, value))
                  }
                })
              Text(item)
                .fontSize(14)
                .lineHeight(20)
                .fontColor('#182431')
                .fontWeight(500)
            }
            .margin({ left: 36 })
          }, (item: string, index: number) => item + index)
        }
      }
    }
    .title('CheckboxChange')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}

export { CheckboxChangeExample };