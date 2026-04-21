/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under * License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See * License for * specific language governing permissions and
 * limitations under * License.
 */

@Builder
export function ToggleMultiTestLevel6Builder(name: string, param: Object) {
  ToggleMultiTestLevel6Example()
}

@Entry
@Component
struct ToggleMultiTestLevel6Example {
  pathStack: NavPathStack = new NavPathStack()
  @State toggle1: boolean = false
  @State toggle2: boolean = true
  @State toggle3: boolean = false
  @State toggle4: boolean = false
  @State toggle5: boolean = false
  @State toggle6: boolean = false
  @State toggle7: boolean = false
  @State toggle8: boolean = false

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 20 }) {
          Text('Toggle 基础示例')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .width('100%')

          Text('默认开关')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Toggle({ type: ToggleType.Switch, isOn: this.toggle1 })
            .onChange((isOn: boolean) => {
              this.toggle1 = isOn
            })

          Text('选中状态')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Toggle({ type: ToggleType.Switch, isOn: this.toggle2 })
            .onChange((isOn: boolean) => {
              this.toggle2 = isOn
            })

          Text('自定义颜色')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Toggle({ type: ToggleType.Switch, isOn: this.toggle3 })
            .selectedColor(0x317aff)
            .onChange((isOn: boolean) => {
              this.toggle3 = isOn
            })

          Text('不同类型')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Column({ space: 10 }) {
            Toggle({ type: ToggleType.Switch, isOn: false })
            Toggle({ type: ToggleType.Checkbox, isOn: true })
            Toggle({ type: ToggleType.Button, isOn: false })
          }

          Text('不同尺寸')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Row({ space: 20 }) {
            Toggle({ type: ToggleType.Switch, isOn: this.toggle4 })
              .width(40)
              .height(24)
              .onChange((isOn: boolean) => {
                this.toggle4 = isOn
              })
            Toggle({ type: ToggleType.Switch, isOn: this.toggle5 })
              .width(50)
              .height(30)
              .onChange((isOn: boolean) => {
                this.toggle5 = isOn
              })
            Toggle({ type: ToggleType.Switch, isOn: this.toggle6 })
              .width(60)
              .height(36)
              .onChange((isOn: boolean) => {
                this.toggle6 = isOn
              })
          }

          Text('禁用状态')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Row({ space: 20 }) {
            Toggle({ type: ToggleType.Switch, isOn: false })
              .enabled(false)
            Toggle({ type: ToggleType.Switch, isOn: true })
              .enabled(false)
          }

          Text('带文本标签')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Row({ space: 10 }) {
            Toggle({ type: ToggleType.Switch, isOn: this.toggle7 })
              .onChange((isOn: boolean) => {
                this.toggle7 = isOn
              })
            Text('启用通知')
              .fontSize(16)
          }

          Text('按钮类型')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Column({ space: 10 }) {
            Toggle({ type: ToggleType.Button, isOn: false })
              .width(100)
              .height(40)
            Toggle({ type: ToggleType.Button, isOn: true })
              .width(100)
              .height(40)
              .selectedColor(0x317aff)
          }

          Text('复选框类型')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Row({ space: 20 }) {
            Toggle({ type: ToggleType.Checkbox, isOn: false })
            Toggle({ type: ToggleType.Checkbox, isOn: true })
              .selectedColor(0x317aff)
          }

          Text('垂直排列')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Column({ space: 15 }) {
            Row({ space: 10 }) {
              Toggle({ type: ToggleType.Switch, isOn: false })
              Text('WiFi')
            }
            Row({ space: 10 }) {
              Toggle({ type: ToggleType.Switch, isOn: true })
              Text('蓝牙')
            }
            Row({ space: 10 }) {
              Toggle({ type: ToggleType.Switch, isOn: false })
              Text('定位')
            }
          }

          Text('不同颜色')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Row({ space: 20 }) {
            Toggle({ type: ToggleType.Switch, isOn: false })
              .selectedColor(0xff0000)
            Toggle({ type: ToggleType.Switch, isOn: false })
              .selectedColor(0x00ff00)
            Toggle({ type: ToggleType.Switch, isOn: false })
              .selectedColor(0x0000ff)
          }

          Text('自定义样式按钮')
            .fontSize(14)
            .fontColor(0x666666)
            .width('100%')
          Toggle({ type: ToggleType.Button, isOn: this.toggle8 })
            .width(120)
            .height(45)
            .selectedColor(0x317aff)
            .borderRadius(22)
            .onChange((isOn: boolean) => {
              this.toggle8 = isOn
            })
        }
        .padding(20)
      }
    }
    .title('ToggleMultiTestLevel6')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
