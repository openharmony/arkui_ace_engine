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
import { BusinessError } from '@kit.BasicServicesKit'

@Builder
export function ToastDurationBuilder(name: string, param: Object) {
  ToastDurationDurationExample()
}

@Entry
@Component
struct ToastDurationDurationExample {
  pathStack: NavPathStack = new NavPathStack()
  @State logMessages: string[] = []
  @State customDuration: number = 2000

  private addLog(message: string) {
    let timestamp = new Date().toLocaleTimeString()
    this.logMessages.unshift(`[${timestamp}] ${message}`)
    if (this.logMessages.length > 20) {
      this.logMessages.pop()
    }
  }

  build() {
    NavDestination() {
      Column({ space: 12 }) {
        Text('Toast 持续时间测试')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .width('100%')
          .textAlign(TextAlign.Center)

        Divider()

        Text('标准持续时间')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .width('100%')

        Row({ space: 8 }) {
          Button('1500ms')
            .layoutWeight(1)
            .onClick(() => {
              try {
                promptAction.showToast({
                  message: '标准短提示',
                  duration: 1500
                })
                this.addLog('显示 1500ms Toast: 标准短提示')
              } catch (error) {
                let err = error as BusinessError
                this.addLog(`错误: ${err.code} - ${err.message}`)
              }
            })

          Button('2000ms')
            .layoutWeight(1)
            .onClick(() => {
              try {
                promptAction.showToast({
                  message: '标准提示',
                  duration: 2000
                })
                this.addLog('显示 2000ms Toast: 标准提示')
              } catch (error) {
                let err = error as BusinessError
                this.addLog(`错误: ${err.code} - ${err.message}`)
              }
            })

          Button('3000ms')
            .layoutWeight(1)
            .onClick(() => {
              try {
                promptAction.showToast({
                  message: '标准长提示',
                  duration: 3000
                })
                this.addLog('显示 3000ms Toast: 标准长提示')
              } catch (error) {
                let err = error as BusinessError
                this.addLog(`错误: ${err.code} - ${err.message}`)
              }
            })
        }
        .width('100%')

        Row({ space: 8 }) {
          Button('5000ms')
            .layoutWeight(1)
            .onClick(() => {
              try {
                promptAction.showToast({
                  message: '5秒提示',
                  duration: 5000
                })
                this.addLog('显示 5000ms Toast: 5秒提示')
              } catch (error) {
                let err = error as BusinessError
                this.addLog(`错误: ${err.code} - ${err.message}`)
              }
            })

          Button('10000ms')
            .layoutWeight(1)
            .onClick(() => {
              try {
                promptAction.showToast({
                  message: '10秒提示',
                  duration: 10000
                })
                this.addLog('显示 10000ms Toast: 10秒提示')
              } catch (error) {
                let err = error as BusinessError
                this.addLog(`错误: ${err.code} - ${err.message}`)
              }
            })
        }
        .width('100%')

        Divider()

        Text('短持续时间测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .width('100%')

        Row({ space: 8 }) {
          Button('0ms')
            .layoutWeight(1)
            .onClick(() => {
              try {
                promptAction.showToast({
                  message: '0ms测试',
                  duration: 0
                })
                this.addLog('显示 0ms Toast: 0ms测试')
              } catch (error) {
                let err = error as BusinessError
                this.addLog(`错误: ${err.code} - ${err.message}`)
              }
            })

          Button('100ms')
            .layoutWeight(1)
            .onClick(() => {
              try {
                promptAction.showToast({
                  message: '100ms测试',
                  duration: 100
                })
                this.addLog('显示 100ms Toast: 100ms测试')
              } catch (error) {
                let err = error as BusinessError
                this.addLog(`错误: ${err.code} - ${err.message}`)
              }
            })

          Button('500ms')
            .layoutWeight(1)
            .onClick(() => {
              try {
                promptAction.showToast({
                  message: '500ms测试',
                  duration: 500
                })
                this.addLog('显示 500ms Toast: 500ms测试')
              } catch (error) {
                let err = error as BusinessError
                this.addLog(`错误: ${err.code} - ${err.message}`)
              }
            })
        }
        .width('100%')

        Row({ space: 8 }) {
          Button('800ms')
            .layoutWeight(1)
            .onClick(() => {
              try {
                promptAction.showToast({
                  message: '800ms测试',
                  duration: 800
                })
                this.addLog('显示 800ms Toast: 800ms测试')
              } catch (error) {
                let err = error as BusinessError
                this.addLog(`错误: ${err.code} - ${err.message}`)
              }
            })

          Button('1000ms')
            .layoutWeight(1)
            .onClick(() => {
              try {
                promptAction.showToast({
                  message: '1000ms测试',
                  duration: 1000
                })
                this.addLog('显示 1000ms Toast: 1000ms测试')
              } catch (error) {
                let err = error as BusinessError
                this.addLog(`错误: ${err.code} - ${err.message}`)
              }
            })
        }
        .width('100%')

        Divider()

        Text('长持续时间测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .width('100%')

        Row({ space: 8 }) {
          Button('15000ms')
            .layoutWeight(1)
            .onClick(() => {
              try {
                promptAction.showToast({
                  message: '15秒提示',
                  duration: 15000
                })
                this.addLog('显示 15000ms Toast: 15秒提示')
              } catch (error) {
                let err = error as BusinessError
                this.addLog(`错误: ${err.code} - ${err.message}`)
              }
            })

          Button('30000ms')
            .layoutWeight(1)
            .onClick(() => {
              try {
                promptAction.showToast({
                  message: '30秒提示',
                  duration: 30000
                })
                this.addLog('显示 30000ms Toast: 30秒提示')
              } catch (error) {
                let err = error as BusinessError
                this.addLog(`错误: ${err.code} - ${err.message}`)
              }
            })
        }
        .width('100%')

        Row({ space: 8 }) {
          Button('60000ms')
            .layoutWeight(1)
            .onClick(() => {
              try {
                promptAction.showToast({
                  message: '60秒提示',
                  duration: 60000
                })
                this.addLog('显示 60000ms Toast: 60秒提示')
              } catch (error) {
                let err = error as BusinessError
                this.addLog(`错误: ${err.code} - ${err.message}`)
              }
            })

          Button('120000ms')
            .layoutWeight(1)
            .onClick(() => {
              try {
                promptAction.showToast({
                  message: '2分钟提示',
                  duration: 120000
                })
                this.addLog('显示 120000ms Toast: 2分钟提示')
              } catch (error) {
                let err = error as BusinessError
                this.addLog(`错误: ${err.code} - ${err.message}`)
              }
            })
        }
        .width('100%')

        Divider()

        Text('自定义持续时间')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .width('100%')

        Row({ space: 8 }) {
          Text(`当前: ${this.customDuration}ms`)
            .fontSize(14)
            .layoutWeight(1)

          Button('显示')
            .onClick(() => {
              try {
                promptAction.showToast({
                  message: `自定义 ${this.customDuration}ms`,
                  duration: this.customDuration
                })
                this.addLog(`显示 ${this.customDuration}ms Toast: 自定义 ${this.customDuration}ms`)
              } catch (error) {
                let err = error as BusinessError
                this.addLog(`错误: ${err.code} - ${err.message}`)
              }
            })
        }
        .width('100%')

        Slider({
          min: 1000,
          max: 60000,
          value: this.customDuration,
          step: 1000
        })
          .width('100%')
          .onChange((value: number) => {
            this.customDuration = value
          })

        Divider()

        Text('边界值测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .width('100%')

        Row({ space: 8 }) {
          Button('-1000ms')
            .layoutWeight(1)
            .onClick(() => {
              try {
                promptAction.showToast({
                  message: '负数测试',
                  duration: -1000
                })
                this.addLog('显示 -1000ms Toast: 负数测试')
              } catch (error) {
                let err = error as BusinessError
                this.addLog(`错误: ${err.code} - ${err.message}`)
              }
            })

          Button('1ms')
            .layoutWeight(1)
            .onClick(() => {
              try {
                promptAction.showToast({
                  message: '1ms测试',
                  duration: 1
                })
                this.addLog('显示 1ms Toast: 1ms测试')
              } catch (error) {
                let err = error as BusinessError
                this.addLog(`错误: ${err.code} - ${err.message}`)
              }
            })
        }
        .width('100%')

        Row({ space: 8 }) {
          Button('999999ms')
            .layoutWeight(1)
            .onClick(() => {
              try {
                promptAction.showToast({
                  message: '超大值测试',
                  duration: 999999
                })
                this.addLog('显示 999999ms Toast: 超大值测试')
              } catch (error) {
                let err = error as BusinessError
                this.addLog(`错误: ${err.code} - ${err.message}`)
              }
            })

          Button('max int')
            .layoutWeight(1)
            .onClick(() => {
              try {
                promptAction.showToast({
                  message: '最大值测试',
                  duration: 2147483647
                })
                this.addLog('显示 2147483647ms Toast: 最大值测试')
              } catch (error) {
                let err = error as BusinessError
                this.addLog(`错误: ${err.code} - ${err.message}`)
              }
            })
        }
        .width('100%')

        Divider()

        Text('日志')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .width('100%')

        List({ space: 4 }) {
          ForEach(this.logMessages, (log: string) => {
            ListItem() {
              Text(log)
                .fontSize(11)
                .fontColor('#666666')
                .width('100%')
            }
          })
        }
        .layoutWeight(1)
        .width('100%')
      }
      .width('100%')
      .height('100%')
      .padding(12)
    }
    .title('Duration Test')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack
    })
  }
}
