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
export function CheckboxIndicatorBuilder(name: string, param: Object) {
  CheckboxIndicatorExample()
}

@Entry
@Component
struct CheckboxIndicatorExample {
  pathStack: NavPathStack = new NavPathStack()

  @Builder
  indicatorBuilder(value: number) {
    Column() {
      Text(value > 99 ? '99+' : value.toString())
        .textAlign(TextAlign.Center)
        .fontSize(value > 99 ? '16vp' : '20vp')
        .fontWeight(FontWeight.Medium)
        .fontColor('#ffffffff')
    }
  }

  build() {
    NavDestination() {
      Row() {
        Column() {
          Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
            Checkbox({
              name: 'checkbox1', group: 'checkboxGroup', indicatorBuilder: () => {
                this.indicatorBuilder(9)
              }
            })
              .shape(CheckBoxShape.CIRCLE)
              .onChange((value: boolean) => {
                console.info('Checkbox1 change is' + value);
              })
              .mark({
                strokeColor: Color.Black,
                size: 50,
                strokeWidth: 5
              })
              .width(30)
              .height(30)
            Text('Checkbox1').fontSize(20)
          }
          .padding(15)

          Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
            Checkbox({
              name: 'checkbox2', group: 'checkboxGroup', indicatorBuilder: () => {
                this.indicatorBuilder(100)
              }
            })
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
    .title('CheckboxIndicator')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}