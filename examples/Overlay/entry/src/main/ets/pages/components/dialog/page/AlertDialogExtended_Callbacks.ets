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


interface AlertDialogExtendedCallbacksInterface {
  timestamp: number;
  userId: string;
  action: string;
}

@Entry
@Component
struct AlertDialogExtendedCallbacks {
  pathStack: NavPathStack = new NavPathStack()
  @State eventLogs: string[] = []
  @State dialogTitle: string = '事件回调测试'
  @State dialogMessage: string = '测试各种事件回调功能'

  addLog(message: string) {
    const timestamp = new Date().toLocaleTimeString()
    this.eventLogs.unshift(`[${timestamp}] ${message}`)
    if (this.eventLogs.length > 20) {
      this.eventLogs.pop()
    }
  }

  clearLogs() {
    this.eventLogs = []
  }

  showPrimaryButtonCallback() {
    this.addLog('显示主按钮回调测试弹窗')
    AlertDialog.show({
      title: '主按钮回调测试',
      message: '点击确定按钮查看回调执行情况',
      autoCancel: true,
      primaryButton: {
        value: '确定',
        fontColor: Color.Green,
        action: () => {
          this.addLog('主按钮(确定)被点击')
          console.log('Primary button clicked')
        }
      },
      secondaryButton: {
        value: '取消',
        fontColor: Color.Gray,
        action: () => {
          this.addLog('次级按钮(取消)被点击')
          console.log('Secondary button clicked')
        }
      }
    })
  }

  showSecondaryButtonCallback() {
    this.addLog('显示次级按钮回调测试弹窗')
    AlertDialog.show({
      title: '次级按钮回调测试',
      message: '点击取消按钮查看回调执行情况',
      autoCancel: true,
      primaryButton: {
        value: '确定',
        action: () => {
          this.addLog('主按钮被点击')
        }
      },
      secondaryButton: {
        value: '取消',
        action: () => {
          this.addLog('次级按钮(取消)回调触发')
          console.log('Secondary button action executed')
        }
      }
    })
  }

  showCancelCallback() {
    this.addLog('显示自动取消回调测试弹窗')
    AlertDialog.show({
      title: '自动取消回调测试',
      message: '点击弹窗外部区域或返回键来测试取消回调',
      autoCancel: true,
      cancel: () => {
        this.addLog('弹窗被取消（点击外部或返回键）')
        console.log('Dialog auto cancelled')
      },
      primaryButton: {
        value: '确定',
        action: () => {
          this.addLog('主按钮被点击')
        }
      }
    })
  }

  showAllCallbacks() {
    this.addLog('显示完整回调测试弹窗')
    AlertDialog.show({
      title: '完整回调测试',
      message: '测试所有回调：确定、取消、自动取消',
      autoCancel: true,
      cancel: () => {
        this.addLog('取消回调触发（点击外部或返回）')
      },
      primaryButton: {
        value: '主要操作',
        fontColor: Color.Green,
        action: () => {
          this.addLog('主要操作按钮回调触发')
        }
      },
      secondaryButton: {
        value: '次要操作',
        fontColor: Color.Blue,
        action: () => {
          this.addLog('次要操作按钮回调触发')
        }
      }
    })
  }

  showActionWithData() {
    this.addLog('显示带数据传递的弹窗')
    AlertDialog.show({
      title: '数据传递测试',
      message: '按钮点击时会传递数据到日志中',
      autoCancel: true,
      primaryButton: {
        value: '传递数据',
        action: () => {
          const data: AlertDialogExtendedCallbacksInterface = {
            timestamp: Date.now(),
            userId: 'user_12345',
            action: 'confirm'
          }
          this.addLog(`主按钮回调，数据: ${JSON.stringify(data)}`)
        }
      },
      secondaryButton: {
        value: '不传递',
        action: () => {
          this.addLog('次级按钮回调，无数据传递')
        }
      }
    })
  }

  showAsyncCallback() {
    this.addLog('显示异步回调测试弹窗')
    AlertDialog.show({
      title: '异步回调测试',
      message: '点击按钮后执行异步操作',
      autoCancel: true,
      primaryButton: {
        value: '异步执行',
        action: async () => {
          this.addLog('开始异步操作...')
          this.addLog('异步操作完成！')
        }
      },
      secondaryButton: {
        value: '取消',
        action: () => {
          this.addLog('用户取消了异步操作')
        }
      }
    })
  }

  showCallbackWithValidation() {
    this.addLog('显示带验证的回调测试弹窗')
    AlertDialog.show({
      title: '回调验证测试',
      message: '点击按钮会进行条件验证',
      autoCancel: true,
      primaryButton: {
        value: '条件执行',
        action: () => {
          const shouldExecute = Math.random() > 0.5
          if (shouldExecute) {
            this.addLog('条件满足，执行操作')
          } else {
            this.addLog('条件不满足，跳过操作')
          }
        }
      },
      secondaryButton: {
        value: '总是执行',
        action: () => {
          this.addLog('次级按钮无条件执行')
        }
      }
    })
  }

  showCallbackWithErrorHandling() {
    this.addLog('显示错误处理回调测试弹窗')
    AlertDialog.show({
      title: '错误处理测试',
      message: '测试回调中的错误处理机制',
      autoCancel: true,
      primaryButton: {
        value: '模拟错误',
        action: () => {
          try {
            this.addLog('尝试执行可能出错的操作...')
            throw new Error('模拟的错误')
          } catch (error) {
            this.addLog(`捕获到错误: ${error}`)
          }
        }
      },
      secondaryButton: {
        value: '正常执行',
        action: () => {
          this.addLog('正常执行，无错误')
        }
      }
    })
  }

  showCallbackWithState() {
    this.addLog('显示状态更新回调测试弹窗')
    let clickCount = 0
    AlertDialog.show({
      title: '状态更新测试',
      message: '多次点击会累加点击次数',
      autoCancel: false,
      primaryButton: {
        value: '累加次数',
        action: () => {
          clickCount++
          this.addLog(`主按钮点击次数: ${clickCount}`)
        }
      },
      secondaryButton: {
        value: '重置',
        action: () => {
          clickCount = 0
          this.addLog('计数器已重置')
        }
      }
    })
  }

  build() {
    NavDestination() {
      Column({ space: 10 }) {
        Text('AlertDialog 事件回调测试用例')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })

        // 单按钮回调测试
        Text('单按钮回调测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ left: 10 })

        Row({ space: 8 }) {
          Button('主按钮回调')
            .width('48%')
            .onClick(() => this.showPrimaryButtonCallback())
          Button('次级按钮回调')
            .width('48%')
            .onClick(() => this.showSecondaryButtonCallback())
        }.width('100%').padding({ left: 10, right: 10 })

        // 自动取消回调测试
        Text('自动取消回调测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ left: 10, top: 5 })

        Button('测试自动取消回调')
          .width('100%')
          .margin({ left: 10, right: 10 })
          .onClick(() => this.showCancelCallback())

        // 组合回调测试
        Text('组合回调测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ left: 10, top: 5 })

        Button('完整回调测试')
          .width('100%')
          .margin({ left: 10, right: 10 })
          .onClick(() => this.showAllCallbacks())

        // 高级回调测试
        Text('高级回调测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ left: 10, top: 5 })

        GridRow({ columns: 2, gutter: 8 }) {
          GridCol() {
            Button('数据传递')
              .width('100%')
              .onClick(() => this.showActionWithData())
          }
          GridCol() {
            Button('异步回调')
              .width('100%')
              .onClick(() => this.showAsyncCallback())
          }
          GridCol() {
            Button('条件验证')
              .width('100%')
              .onClick(() => this.showCallbackWithValidation())
          }
          GridCol() {
            Button('错误处理')
              .width('100%')
              .onClick(() => this.showCallbackWithErrorHandling())
          }
        }.width('100%').margin({ left: 10, right: 10 })

        // 状态管理测试
        Text('状态管理测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ left: 10, top: 5 })

        Button('测试状态更新')
          .width('100%')
          .margin({ left: 10, right: 10 })
          .onClick(() => this.showCallbackWithState())

        // 日志显示区域
        Divider()
        Row() {
          Text('事件日志')
            .fontSize(14)
            .fontColor(Color.Gray)
          Blank()
          Button('清空')
            .fontSize(12)
            .height(30)
            .onClick(() => this.clearLogs())
        }
        .width('100%').margin({ left: 10, right: 10 })

        List({ space: 5 }) {
          ForEach(this.eventLogs, (log: string) => {
            ListItem() {
              Text(log)
                .fontSize(12)
                .fontColor(Color.Black)
                .width('100%')
            }
          }, (log: string, index: number) => `log_${index}`)
        }
        .width('100%')
        .height(200)
        .padding(10)
        .backgroundColor('#F5F5F5')
        .borderRadius(8)
        .margin({ left: 10, right: 10, bottom: 10 })

        Blank()
      }
      .width('100%')
      .height('100%')
    }
    .title('AlertDialog 事件回调')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
