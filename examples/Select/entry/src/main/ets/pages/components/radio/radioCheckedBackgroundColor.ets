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
export function RadioCheckedBackgroundColorBuilder(name: string, param: Object) {
  RadioCheckedBackgroundColorExample()
}

@Entry
@Component
struct RadioCheckedBackgroundColorExample {
  pathStack: NavPathStack = new NavPathStack()
  @State context1: string = 'Radio1';
  @State context2: string = 'Radio2';
  @State context3: string = 'Radio3';

  build() {
    NavDestination() {
      Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
        Column() {
          Text(this.context1)
          Radio({ value: this.context1, group: 'radioGroup' })
            .checked(true)
            .radioStyle({
              checkedBackgroundColor: Color.Pink
            })
            .height(50)
            .width(50)
            .onChange((isChecked: boolean) => {
              console.log('Radio1 status is ' + isChecked);
            })
        }

        Column() {
          Text(this.context2)
          Radio({ value: this.context2, group: 'radioGroup' })
            .checked(false)
            .radioStyle({
              checkedBackgroundColor: Color.Pink
            })
            .height(50)
            .width(50)
            .onChange((isChecked: boolean) => {
              console.log('Radio2 status is ' + isChecked);
            })
        }

        Column() {
          Text(this.context3)
          Radio({ value: this.context3, group: 'radioGroup' })
            .checked(false)
            .radioStyle({
              checkedBackgroundColor: Color.Pink
            })
            .height(50)
            .width(50)
            .onChange((isChecked: boolean) => {
              console.log('Radio3 status is ' + isChecked);
            })
        }
      }
      .padding({ top: 30 })
    }
    .title('RadioCheckedBackgroundColor')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}