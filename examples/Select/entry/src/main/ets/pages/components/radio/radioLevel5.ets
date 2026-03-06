/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
export function RadioLevel5Builder(name: string, param: Object) {
  RadioLevel5Example()
}

@Entry
@Component
struct RadioLevel5Example {
  pathStack: NavPathStack = new NavPathStack()
  @State radioGroup1: string = 'radio1'
  @State radioGroup2: string = 'optionA'
  @State radioGroup3: string = 'red'
  @State radioGroup4: string = 'small'

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 20 }) {
          Text('Radio 基础示例')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .width('100%')

          Text('默认样式')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Radio({ value: 'radio1', group: 'group1' })
            .checked(this.radioGroup1 === 'radio1')
            .onChange((isChecked: boolean) => {
              if (isChecked) {
                this.radioGroup1 = 'radio1'
              }
            })

          Text('单选组')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Column({ space: 10 }) {
            Row({ space: 10 }) {
              Radio({ value: 'radio1', group: 'group1' })
                .checked(this.radioGroup1 === 'radio1')
                .onChange((isChecked: boolean) => {
                  if (isChecked) {
                    this.radioGroup1 = 'radio1'
                  }
                })
              Text('选项1')
            }
            Row({ space: 10.0 }) {
              Radio({ value: 'radio2', group: 'group1' })
                .checked(this.radioGroup1 === 'radio2')
                .onChange((isChecked: boolean) => {
                  if (isChecked) {
                    this.radioGroup1 = 'radio2'
                  }
                })
              Text('选项2')
            }
            Row({ space: 10 }) {
              Radio({ value: 'radio3', group: 'group1' })
                .checked(this.radioGroup1 === 'radio3')
                .onChange((isChecked: boolean) => {
                  if (isChecked) {
                    this.radioGroup1 = 'radio3'
                  }
                })
              Text('选项3')
            }
          }

          Text('自定义选中颜色')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Row({ space: 20 }) {
            Radio({ value: 'red', group: 'group2' })
              .checked(this.radioGroup3 === 'red')
              .radioStyle({
                checkedBackgroundColor: 0xff0000
              })
              .onChange((isChecked: boolean) => {
                if (isChecked) {
                  this.radioGroup3 = 'red'
                }
              })
            Radio({ value: 'green', group: 'group2' })
              .checked(this.radioGroup3 === 'green')
              .radioStyle({
                checkedBackgroundColor: 0x00ff00
              })
              .onChange((isChecked: boolean) => {
                if (isChecked) {
                  this.radioGroup3 = 'green'
                }
              })
            Radio({ value: 'blue', group: 'group2' })
              .checked(this.radioGroup3 === 'blue')
              .radioStyle({
                checkedBackgroundColor: 0x0000ff
              })
              .onChange((isChecked: boolean) => {
                if (isChecked) {
                  this.radioGroup3 = 'blue'
                }
              })
          }

          Text('不同尺寸')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Row({ space: 20 }) {
            Radio({ value: 'small', group: 'group3' })
              .checked(this.radioGroup4 === 'small')
              .width(20)
              .height(20)
              .onChange((isChecked: boolean) => {
                if (isChecked) {
                  this.radioGroup4 = 'small'
                }
              })
            Radio({ value: 'medium', group: 'group3' })
              .checked(this.radioGroup4 === 'medium')
              .width(30)
              .height(30)
              .onChange((isChecked: boolean) => {
                if (isChecked) {
                  this.radioGroup4 = 'medium'
                }
              })
            Radio({ value: 'large', group: 'group3' })
              .checked(this.radioGroup4 === 'large')
              .width(40)
              .height(40)
              .onChange((isChecked: boolean) => {
                if (isChecked) {
                  this.radioGroup4 = 'large'
                }
              })
          }

          Text('性别选择')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Row({ space: 20 }) {
            Radio({ value: 'male', group: 'gender' })
              .checked(false)
              .radioStyle({
                checkedBackgroundColor: 0x317aff
              })
            Text('男')
              .fontSize(16)
            Radio({ value: 'female', group: 'gender' })
              .checked(true)
              .radioStyle({
                checkedBackgroundColor: 0xff69b4
              })
            Text('女')
              .fontSize(16)
          }

          Text('语言选择')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Column({ space: 10 }) {
            Row({ space: 10 }) {
              Radio({ value: 'zh', group: 'lang' })
                .checked(true)
                .radioStyle({
                  checkedBackgroundColor: 0x317aff
                })
              Text('中文')
            }
            Row({ space: 10 }) {
              Radio({ value: 'en', group: 'lang' })
                .checked(false)
                .radioStyle({
                  checkedBackgroundColor: 0x317aff
                })
              Text('English')
            }
            Row({ space: 10 }) {
              Radio({ value: 'jp', group: 'lang' })
                .checked(false)
                .radioStyle({
                  checkedBackgroundColor: 0x317aff
                })
              Text('日本語')
            }
          }

          Text('禁用状态')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Row({ space: 20 }) {
            Radio({ value: 'disabled1', group: 'disabled' })
              .checked(false)
              .enabled(false)
            Radio({ value: 'disabled2', group: 'disabled' })
              .checked(true)
              .enabled(false)
          }

          Text('自定义样式')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Radio({ value: 'custom', group: 'group4' })
            .checked(false)
            .radioStyle({
              checkedBackgroundColor: 0x00d4ff
            })
            .width(25)
            .height(25)

          Text('带边框')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Row({ space: 10 }) {
            Radio({ value: 'bordered', group: 'group5' })
              .checked(false)
              .radioStyle({
                checkedBackgroundColor: 0x317aff
              })
              .border({ width: 2, color: 0xcccccc })
            Text('带边框的单选框')
          }
        }
        .padding(20)
      }
    }
    .title('RadioLevel5')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
