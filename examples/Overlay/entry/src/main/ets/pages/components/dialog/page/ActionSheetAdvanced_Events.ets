/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


@Entry
@Component
struct ActionSheetAdvancedEvents {
  pathStack: NavPathStack = new NavPathStack()
  @State eventLogs: string[] = []

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

  showBasicEvents() {
    this.addLog('显示基础事件测试ActionSheet')
    ActionSheet.show({
      title: '事件测试',
      autoCancel: true,
      confirm: {
        value: '确定',
        action: () => {
          this.addLog('确定按钮被点击')
          console.log('Confirm button clicked')
        }
      },
      cancel: () => {
        this.addLog('ActionSheet已取消')
        console.log('ActionSheet cancelled')
      },
      sheets: [
        {
          title: '选项1',
          action: () => {
            this.addLog('选项1被点击')
          }
        },
        {
          title: '选项2',
          action: () => {
            this.addLog('选项2被点击')
          }
        }
      ],
      message: ''
    })
  }

  showCancelCallback() {
    this.addLog('显示取消回调测试ActionSheet')
    ActionSheet.show({
      title: '取消回调测试',
      message: '点击外部区域或返回键来测试取消回调',
      autoCancel: true,
      cancel: () => {
        this.addLog('取消回调被触发')
      },
      confirm: {
        value: '确定',
        action: () => {
          this.addLog('确定按钮被点击')
        }
      },
      sheets: []
    })
  }

  showMultipleClicks() {
    this.addLog('显示多次点击测试ActionSheet')
    let clickCount = 0
    ActionSheet.show({
      title: '多次点击测试',
      autoCancel: false,
      confirm: {
        value: `点击计数: ${clickCount}`,
        action: () => {
          clickCount++
          this.addLog(`确定按钮被点击 ${clickCount} 次`)
        }
      },
      sheets: [
        {
          title: '重置计数',
          action: () => {
            clickCount = 0
            this.addLog('计数器已重置')
          }
        }
      ],
      message: ''
    })
  }

  showAsyncAction() {
    this.addLog('显示异步操作测试ActionSheet')
    ActionSheet.show({
      title: '异步操作测试',
      autoCancel: true,
      confirm: {
        value: '异步执行',
        action: async () => {
          this.addLog('开始异步操作...')
          //await new Promise(resolve => setTimeout(resolve, 1000))
          this.addLog('异步操作完成！')
        }
      },
      sheets: [
        {
          title: '同步操作',
          action: () => {
            this.addLog('同步操作执行完成')
          }
        }
      ],
      message: ''
    })
  }

  showActionWithData() {
    this.addLog('显示数据传递测试ActionSheet')
    ActionSheet.show({
      title: '数据传递测试',
      autoCancel: true,
      confirm: {
        value: '确定',
        action: () => {
          this.addLog('确定按钮数据: {type: "confirm", timestamp: ' + Date.now() + '}')
        }
      },
      sheets: [
        {
          title: '选项A',
          action: () => {
            this.addLog('选项A数据: {type: "option", value: "A", timestamp: ' + Date.now() + '}')
          }
        },
        {
          title: '选项B',
          action: () => {
            this.addLog('选项B数据: {type: "option", value: "B", timestamp: ' + Date.now() + '}')
          }
        },
        {
          title: '选项C',
          action: () => {
            this.addLog('选项C数据: {type: "option", value: "C", timestamp: ' + Date.now() + '}')
          }
        }
      ],
      message: ''
    })
  }

  showConditionalAction() {
    this.addLog('显示条件判断测试ActionSheet')
    ActionSheet.show({
      title: '条件判断测试',
      autoCancel: true,
      sheets: [
        {
          title: '随机操作',
          action: () => {
            const shouldExecute = Math.random() > 0.5
            if (shouldExecute) {
              this.addLog('条件满足，执行操作')
            } else {
              this.addLog('条件不满足，跳过操作')
            }
          }
        },
        {
          title: '总是执行',
          action: () => {
            this.addLog('无条件执行操作')
          }
        }
      ],
      message: ''
    })
  }

  showErrorHandling() {
    this.addLog('显示错误处理测试ActionSheet')
    ActionSheet.show({
      title: '错误处理测试',
      autoCancel: true,
      confirm: {
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
      sheets: [
        {
          title: '正常执行',
          action: () => {
            this.addLog('正常执行，无错误')
          }
        }
      ],
      message: ''
    })
  }

  showEventSequence() {
    this.addLog('显示事件序列测试ActionSheet')
    let eventOrder = 0
    ActionSheet.show({
      title: '事件序列测试',
      autoCancel: true,
      cancel: () => {
        eventOrder++
        this.addLog(`事件序列: 第${eventOrder}步 - 取消`)
      },
      confirm: {
        value: '确定',
        action: () => {
          eventOrder++
          this.addLog(`事件序列: 第${eventOrder}步 - 确定`)
        }
      },
      sheets: [
        {
          title: '选项1',
          action: () => {
            eventOrder++
            this.addLog(`事件序列: 第${eventOrder}步 - 选项1`)
          }
        },
        {
          title: '选项2',
          action: () => {
            eventOrder++
            this.addLog(`事件序列: 第${eventOrder}步 - 选项2`)
          }
        }
      ],
      message: ''
    })
  }

  build() {
    NavDestination() {
      Column({ space: 12 }) {
        Text('ActionSheet 事件处理测试用例')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })

        // 基础事件测试
        Text('基础事件测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ left: 10 })

        Button('基础事件')
          .width('100%')
          .margin({ left: 10, right: 10 })
          .onClick(() => this.showBasicEvents())

        // 取消回调测试
        Text('取消回调测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ left: 10, top: 5 })

        Button('取消回调')
          .width('100%')
          .margin({ left: 10, right: 10 })
          .onClick(() => this.showCancelCallback())

        // 高级事件测试
        Text('高级事件测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ left: 10, top: 5 })

        GridRow({ columns: 2, gutter: 8 }) {
          GridCol() {
            Button('多次点击')
              .width('100%')
              .onClick(() => this.showMultipleClicks())
          }
          GridCol() {
            Button('异步操作')
              .width('100%')
              .onClick(() => this.showAsyncAction())
          }
        }.width('100%').margin({ left: 10, right: 10 })

        Row({ space: 8 }) {
          Button('数据传递')
            .width('48%')
            .onClick(() => this.showActionWithData())
          Button('条件判断')
            .width('48%')
            .onClick(() => this.showConditionalAction())
        }.width('100%').padding({ left: 10, right: 10 })

        // 特殊事件测试
        Text('特殊事件测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ left: 10, top: 5 })

        GridRow({ columns: 2, gutter: 8 }) {
          GridCol() {
            Button('错误处理')
              .width('100%')
              .onClick(() => this.showErrorHandling())
          }
          GridCol() {
            Button('事件序列')
              .width('100%')
              .onClick(() => this.showEventSequence())
          }
        }.width('100%').margin({ left: 10, right: 10 })

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
                .fontSize(11)
                .fontColor(Color.Black)
                .width('100%')
            }
          }, (log: string, index: number) => `log_${index}`)
        }
        .width('100%')
        .height(180)
        .padding(10)
        .backgroundColor('#F5F5F5')
        .borderRadius(8)
        .margin({ left: 10, right: 10, bottom: 10 })

        Blank()
      }
      .width('100%')
      .height('100%')
    }
    .title('ActionSheet 事件处理')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
