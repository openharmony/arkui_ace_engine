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

import { promptAction } from '@kit.ArkUI'

@Builder
export function ToastInteractionBuilder(name: string, param: Object) {
  ToastInteractionExample()
}

@Entry
@Component
struct ToastInteractionExample {
  pathStack: NavPathStack = new NavPathStack()
  @State buttonClickCount: number = 0
  @State dragOffsetX: number = 0
  @State dragOffsetY: number = 0
  @State timerCount: number = 0
  @State timerRunning: boolean = false
  @State checkbox1: boolean = false
  @State checkbox2: boolean = false
  @State checkbox3: boolean = false
  @State selectedOption: string = '选项1'
  @State switchValue: boolean = false
  @State sliderValue: number = 50
  @State inputText: string = ''

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 12 }) {
          Text('Toast 交互测试')
            .fontSize(20)
            .fontWeight(FontWeight.Bold)
            .width('100%')
            .textAlign(TextAlign.Center)

          Divider()

          Text('按钮点击交互')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Text(`点击次数: ${this.buttonClickCount}`)
            .fontSize(14)
            .fontColor('#666666')
            .width('100%')

          Button('点击显示 Toast')
            .width('100%')
            .onClick(() => {
              this.buttonClickCount++
              promptAction.showToast({
                message: `第 ${this.buttonClickCount} 次点击`,
                duration: 2000
              })
            })

          Divider()

          Text('输入框交互')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          TextInput({ placeholder: '输入内容显示在 Toast' })
            .width('100%')
            .onChange((value: string) => {
              this.inputText = value
            })

          Button('显示输入内容')
            .width('100%')
            .onClick(() => {
              if (this.inputText.length > 0) {
                promptAction.showToast({
                  message: this.inputText,
                  duration: 2000
                })
              } else {
                promptAction.showToast({
                  message: '请输入内容',
                  duration: 2000,
                  backgroundColor: '#FF9800',
                  textColor: '#FFFFFF'
                })
              }
            })

          Divider()

          Text('滑动条交互')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Slider({
            min: 0,
            max: 100,
            value: this.sliderValue,
            step: 1
          })
            .width('100%')
            .onChange((value: number) => {
              this.sliderValue = value
            })

          Text(`当前值: ${this.sliderValue}`)
            .fontSize(14)
            .fontColor('#666666')
            .width('100%')

          Button('显示滑动值')
            .width('100%')
            .onClick(() => {
              promptAction.showToast({
                message: `滑动值: ${this.sliderValue}`,
                duration: 2000
              })
            })

          Divider()

          Text('开关交互')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Row({ space: 8 }) {
            Text('开关状态:')
            Toggle({ type: ToggleType.Switch, isOn: this.switchValue })
              .onChange((isOn: boolean) => {
                this.switchValue = isOn
                promptAction.showToast({
                  message: `开关: ${isOn ? '开启' : '关闭'}`,
                  duration: 2000,
                  backgroundColor: isOn ? '#4CAF50' : '#F44336',
                  textColor: '#FFFFFF'
                })
              })
          }
          .width('100%')

          Divider()

          Text('单选框交互')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Row({ space: 8 }) {
            Radio({ value: '选项1', group: 'radioGroup' })
              .checked(this.selectedOption === '选项1')
              .onChange((isChecked: boolean) => {
                if (isChecked) {
                  this.selectedOption = '选项1'
                  promptAction.showToast({
                    message: '选择: 选项1',
                    duration: 2000
                  })
                }
              })
            Text('选项1')

            Radio({ value: '选项2', group: 'radioGroup' })
              .checked(this.selectedOption === '选项2')
              .onChange((isChecked: boolean) => {
                if (isChecked) {
                  this.selectedOption = '选项2'
                  promptAction.showToast({
                    message: '选择: 选项2',
                    duration: 2000
                  })
                }
              })
            Text('选项2')

            Radio({ value: '选项3', group: 'radioGroup' })
              .checked(this.selectedOption === '选项3')
              .onChange((isChecked: boolean) => {
                if (isChecked) {
                  this.selectedOption = '选项3'
                  promptAction.showToast({
                    message: '选择: 选项3',
                    duration: 2000
                  })
                }
              })
            Text('选项3')
          }
          .width('100%')

          Divider()

          Text('多选框交互')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Row({ space: 8 }) {
            Checkbox({ name: 'cb1' })
              .select(this.checkbox1)
              .onChange((value: boolean) => {
                this.checkbox1 = value
                promptAction.showToast({
                  message: `多选1: ${value}`,
                  duration: 1500
                })
              })
            Text('多选1')

            Checkbox({ name: 'cb2' })
              .select(this.checkbox2)
              .onChange((value: boolean) => {
                this.checkbox2 = value
                promptAction.showToast({
                  message: `多选2: ${value}`,
                  duration: 1500
                })
              })
            Text('多选2')

            Checkbox({ name: 'cb3' })
              .select(this.checkbox3)
              .onChange((value: boolean) => {
                this.checkbox3 = value
                promptAction.showToast({
                  message: `多选3: ${value}`,
                  duration: 1500
                })
              })
            Text('多选3')
          }
          .width('100%')

          Button('显示选中状态')
            .width('100%')
            .onClick(() => {
              let selected: Array<string> = []
              if (this.checkbox1) selected.push('多选1')
              if (this.checkbox2) selected.push('多选2')
              if (this.checkbox3) selected.push('多选3')
              let message = selected.length > 0 ? `选中: ${selected.join(', ')}` : '未选择任何项'
              promptAction.showToast({
                message: message,
                duration: 2000
              })
            })

          Divider()

          Text('长按交互')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Button('长按显示 Toast')
            .width('100%')
            .gesture(
              LongPressGesture({ repeat: false })
                .onAction(() => {
                  promptAction.showToast({
                    message: '长按触发',
                    duration: 2000,
                    backgroundColor: '#9C27B0',
                    textColor: '#FFFFFF'
                  })
                })
            )

          Divider()

          Text('拖动交互')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Text(`拖动偏移: X=${this.dragOffsetX}, Y=${this.dragOffsetY}`)
            .fontSize(14)
            .fontColor('#666666')
            .width('100%')

          Button('拖动区域')
            .width('100%')
            .height(80)
            .gesture(
              PanGesture({ direction: PanDirection.All })
                .onActionUpdate((event: GestureEvent) => {
                  this.dragOffsetX = event.offsetX
                  this.dragOffsetY = event.offsetY
                })
                .onActionEnd(() => {
                  promptAction.showToast({
                    message: `拖动结束: X=${Math.round(this.dragOffsetX)}, Y=${Math.round(this.dragOffsetY)}`,
                    duration: 2000
                  })
                })
            )

          Divider()

          Text('定时器交互')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Text(`定时器计数: ${this.timerCount}`)
            .fontSize(14)
            .fontColor('#666666')
            .width('100%')

          Row({ space: 8 }) {
            Button('启动定时器')
              .layoutWeight(1)
              .enabled(!this.timerRunning)
              .onClick(() => {
                this.timerRunning = true
                this.timerCount = 0
                let timer = setInterval(() => {
                  this.timerCount++
                  promptAction.showToast({
                    message: `定时: ${this.timerCount}s`,
                    duration: 1000
                  })
                  if (this.timerCount >= 5) {
                    clearInterval(timer)
                    this.timerRunning = false
                    promptAction.showToast({
                      message: '定时器结束',
                      duration: 2000,
                      backgroundColor: '#4CAF50',
                      textColor: '#FFFFFF'
                    })
                  }
                }, 1000)
              })

            Button('手动停止')
              .layoutWeight(1)
              .enabled(this.timerRunning)
              .onClick(() => {
                this.timerRunning = false
                promptAction.showToast({
                  message: '手动停止',
                  duration: 2000,
                  backgroundColor: '#F44336',
                  textColor: '#FFFFFF'
                })
              })
          }
          .width('100%')
        }
        .width('100%')
        .padding(12)
      }
      .height('100%')
      .width('100%')
    }
    .title('Interaction Test')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack
    })
  }
}
