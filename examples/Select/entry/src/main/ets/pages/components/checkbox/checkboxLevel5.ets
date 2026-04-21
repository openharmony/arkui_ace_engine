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
export function CheckboxLevel5Builder(name: string, param: Object) {
  CheckboxLevel5Example()
}

@Entry
@Component
struct CheckboxLevel5Example {
  pathStack: NavPathStack = new NavPathStack()
  @State checkbox1: boolean = false
  @State checkbox2: boolean = true
  @State checkbox3: boolean = false
  @State checkbox4: boolean = false
  @State checkbox5: boolean = false
  @State checkbox6: boolean = false
  @State checkbox7: boolean = false
  @State checkbox8: boolean = false

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 20 }) {
          Text('Checkbox 基础示例')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .width('100%')

          Text('默认样式')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Checkbox({ name: 'checkbox1', group: 'group1' })
            .select(this.checkbox1)
            .selectedColor(0x317aff)
            .onChange((value: boolean) => {
              this.checkbox1 = value
            })

          Text('选中状态')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Checkbox({ name: 'checkbox2', group: 'group1' })
            .select(this.checkbox2)
            .selectedColor(0x317aff)
            .onChange((value: boolean) => {
              this.checkbox2 = value
            })

          Text('自定义选中颜色')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Checkbox({ name: 'checkbox3', group: 'group1' })
            .select(this.checkbox3)
            .selectedColor(0xff0000)
            .onChange((value: boolean) => {
              this.checkbox3 = value
            })

          Text('不同尺寸')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Row({ space: 20 }) {
            Checkbox({ name: 'checkbox4', group: 'group1' })
              .select(this.checkbox4)
              .width(20)
              .height(20)
              .onChange((value: boolean) => {
                this.checkbox4 = value
              })
            Checkbox({ name: 'checkbox5', group: 'group1' })
              .select(this.checkbox5)
              .width(30)
              .height(30)
              .onChange((value: boolean) => {
                this.checkbox5 = value
              })
            Checkbox({ name: 'checkbox6', group: 'group1' })
              .select(this.checkbox6)
              .width(40)
              .height(40)
              .onChange((value: boolean) => {
                this.checkbox6 = value
              })
          }

          Text('禁用状态')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Row({ space: 20 }) {
            Checkbox({ name: 'checkbox7', group: 'group1' })
              .select(this.checkbox7)
              .enabled(false)
              .onChange((value: boolean) => {
                this.checkbox7 = value
              })
            Checkbox({ name: 'checkbox8', group: 'group1' })
              .select(true)
              .enabled(false)
              .onChange((value: boolean) => {
                this.checkbox8 = value
              })
          }

          Text('带文本标签')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Row({ space: 10 }) {
            Checkbox({ name: 'checkbox9', group: 'group1' })
              .select(false)
              .selectedColor(0x317aff)
            Text('记住密码')
              .fontSize(16)
          }

          Text('多选组合')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Column({ space: 10 }) {
            Row({ space: 10 }) {
              Checkbox({ name: 'option1', group: 'options' })
                .select(false)
              Text('选项A')
            }
            Row({ space: 10 }) {
              Checkbox({ name: 'option2', group: 'options' })
                .select(true)
              Text('选项B')
            }
            Row({ space: 10 }) {
              Checkbox({ name: 'option3', group: 'options' })
                .select(false)
              Text('选项C')
            }
          }

          Text('自定义样式')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Checkbox({ name: 'custom', group: 'group1' })
            .select(false)
            .selectedColor(0x00d4ff)
            .width(25)
            .height(25)
            .borderRadius(5)

          Text('垂直排列')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Column({ space: 15 }) {
            Row({ space: 10 }) {
              Checkbox({ name: 'v1', group: 'vertical' })
                .select(false)
              Text('语文')
            }
            Row({ space: 10 }) {
              Checkbox({ name: 'v2', group: 'vertical' })
                .select(true)
              Text('数学')
            }
            Row({ space: 10 }) {
              Checkbox({ name: 'v3', group: 'vertical' })
                .select(false)
              Text('英语')
            }
          }

          Text('不同选中颜色')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Row({ space: 20 }) {
            Checkbox({ name: 'red', group: 'colors' })
              .select(false)
              .selectedColor(0xff0000)
            Checkbox({ name: 'green', group: 'colors' })
              .select(false)
              .selectedColor(0x00ff00)
            Checkbox({ name: 'blue', group: 'colors' })
              .select(false)
              .selectedColor(0x0000ff)
          }
        }
        .padding(20)
      }
    }
    .title('CheckboxLevel5')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
