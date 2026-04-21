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
export function ToastAdvancedBuilder(name: string, param: Object) {
  ToastAdvancedExample()
}

@Entry
@Component
struct ToastAdvancedExample {
  pathStack: NavPathStack = new NavPathStack()
  @State memoryTestIds: number[] = []

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 12 }) {
          Text('Toast 高级测试')
            .fontSize(20)
            .fontWeight(FontWeight.Bold)
            .width('100%')
            .textAlign(TextAlign.Center)

          Divider()

          Text('特殊字符测试')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Button('包含 Emoji')
            .width('100%')
            .onClick(() => {
              promptAction.showToast({
                message: '🎉 成功！✨ 🚀',
                duration: 2000
              })
            })

          Button('特殊符号')
            .width('100%')
            .onClick(() => {
              promptAction.showToast({
                message: '特殊符号: !@#$%^&*()_+-=[]{}|;:\'",.<>?/~`',
                duration: 2000
              })
            })

          Button('Unicode 字符')
            .width('100%')
            .onClick(() => {
              promptAction.showToast({
                message: 'Unicode: 你好世界 Привет мир こんにちは',
                duration: 2000
              })
            })

          Button('空格和制表符')
            .width('100%')
            .onClick(() => {
              promptAction.showToast({
                message: '空格测试:   多个空格   ',
                duration: 2000
              })
            })

          Divider()

          Text('边界情况测试')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Button('空字符串')
            .width('100%')
            .onClick(() => {
              promptAction.showToast({
                message: '',
                duration: 2000
              })
            })

          Button('仅空格')
            .width('100%')
            .onClick(() => {
              promptAction.showToast({
                message: '   ',
                duration: 2000
              })
            })

          Button('超长文本 (500字符)')
            .width('100%')
            .onClick(() => {
              let longText = 'A'.repeat(500)
              promptAction.showToast({
                message: longText,
                duration: 5000
              })
            })

          Button('超长文本 (1000字符)')
            .width('100%')
            .onClick(() => {
              let longText = 'B'.repeat(1000)
              promptAction.showToast({
                message: longText,
                duration: 5000
              })
            })

          Divider()

          Text('参数组合测试')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Button('所有参数组合')
            .width('100%')
            .onClick(() => {
              promptAction.showToast({
                message: '完整配置',
                duration: 3000,
                bottom: 100,
                showMode: promptAction.ToastShowMode.TOP_MOST,
                alignment: Alignment.Center,
                backgroundColor: '#4CAF50',
                textColor: '#FFFFFF',
                backgroundBlurStyle: BlurStyle.COMPONENT_REGULAR
              })
            })

          Button('最小参数组合')
            .width('100%')
            .onClick(() => {
              promptAction.showToast({
                message: '最小配置'
              })
            })

          Divider()

          Text('并发场景测试')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Button('并发显示 10 个')
            .width('100%')
            .onClick(() => {
              for (let i = 0; i < 10; i++) {
                setTimeout(() => {
                  promptAction.showToast({
                    message: `并发 ${i + 1}`,
                    duration: 2000
                  })
                }, i * 100)
              }
            })

          Button('并发打开关闭')
            .width('100%')
            .onClick(() => {
              let ids: number[] = []
              for (let i = 0; i < 5; i++) {
                promptAction.openToast({
                  message: `并发 ${i + 1}`,
                  duration: 10000
                }).then((toastId: number) => {
                  ids.push(toastId)
                })
              }
              setTimeout(() => {
                ids.forEach(id => promptAction.closeToast(id))
              }, 2000)
            })

          Divider()

          Text('错误处理测试')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Button('关闭不存在的 ID')
            .width('100%')
            .onClick(() => {
              promptAction.closeToast(999999)
            })

          Button('关闭负数 ID')
            .width('100%')
            .onClick(() => {
              promptAction.closeToast(-1)
            })

          Button('关闭 0')
            .width('100%')
            .onClick(() => {
              promptAction.closeToast(0)
            })

          Button('重复关闭同一 ID')
            .width('100%')
            .onClick(() => {
              promptAction.openToast({
                message: '重复关闭测试',
                duration: 10000
              }).then((toastId: number) => {
                promptAction.closeToast(toastId)
                setTimeout(() => {
                  promptAction.closeToast(toastId)
                }, 500)
              })
            })

          Divider()

          Text('性能压力测试')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Button('快速连续 100 次')
            .width('100%')
            .onClick(() => {
              let startTime = Date.now()
              for (let i = 0; i < 100; i++) {
                setTimeout(() => {
                  promptAction.showToast({
                    message: `#`,
                    duration: 500
                  })
                }, i * 50)
              }
              let endTime = Date.now()
            })

          Button('快速连续 500 次')
            .width('100%')
            .onClick(() => {
              let startTime = Date.now()
              for (let i = 0; i < 500; i++) {
                setTimeout(() => {
                  promptAction.showToast({
                    message: `#`,
                    duration: 500
                  })
                }, i * 10)
              }
              let endTime = Date.now()
            })

          Divider()

          Text('内存泄漏测试')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Button('创建 100 个长时 Toast')
            .width('100%')
            .onClick(() => {
              for (let i = 0; i < 100; i++) {
                promptAction.openToast({
                  message: `内存测试 ${i + 1}`,
                  duration: 60000
                }).then((toastId: number) => {
                  this.memoryTestIds.push(toastId)
                })
              }
            })

          Button('关闭所有内存测试 Toast')
            .width('100%')
            .backgroundColor('#F44336')
            .onClick(() => {
              this.memoryTestIds.forEach(id => {
                promptAction.closeToast(id)
              })
              this.memoryTestIds = []
            })

          Text(`当前内存测试 Toast: ${this.memoryTestIds.length}`)
            .fontSize(12)
            .fontColor('#666666')
            .width('100%')

          Divider()

          Text('显示模式对比')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Button('DEFAULT 模式')
            .width('100%')
            .onClick(() => {
              promptAction.showToast({
                message: 'DEFAULT 模式',
                duration: 3000,
                showMode: promptAction.ToastShowMode.DEFAULT,
                backgroundColor: '#2196F3',
                textColor: '#FFFFFF'
              })
            })

          Button('TOP_MOST 模式')
            .width('100%')
            .onClick(() => {
              promptAction.showToast({
                message: 'TOP_MOST 模式',
                duration: 3000,
                showMode: promptAction.ToastShowMode.TOP_MOST,
                backgroundColor: '#FF9800',
                textColor: '#FFFFFF'
              })
            })

          Button('同时显示两种模式')
            .width('100%')
            .onClick(() => {
              promptAction.showToast({
                message: 'DEFAULT',
                duration: 5000,
                showMode: promptAction.ToastShowMode.DEFAULT,
                alignment: Alignment.Top,
                backgroundColor: '#2196F3',
                textColor: '#FFFFFF'
              })
              setTimeout(() => {
                promptAction.showToast({
                  message: 'TOP_MOST',
                  duration: 5000,
                  showMode: promptAction.ToastShowMode.TOP_MOST,
                  alignment: Alignment.Bottom,
                  backgroundColor: '#FF9800',
                  textColor: '#FFFFFF'
                })
              }, 500)
            })
        }
        .width('100%')
        .padding(12)
      }
      .height('100%')
      .width('100%')
    }
    .title('Advanced Test')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack
    })
  }
}
