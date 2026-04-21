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


@Entry
@Component
struct AlertDialogExtendedAutoCancel {
  pathStack: NavPathStack = new NavPathStack()
  @State autoCancelState: string = '默认'
  @State logMessage: string = '点击按钮测试不同自动取消行为'

  showAutoCancelTrue() {
    this.autoCancelState = '自动取消: 开启'
    this.logMessage = '点击弹窗外部或返回键可关闭弹窗'
    AlertDialog.show({
      title: '自动取消开启',
      message: '点击弹窗外部区域或按返回键可以关闭此弹窗\n\nautoCancel: true',
      autoCancel: true,
      cancel: () => {
        this.logMessage = '弹窗已自动取消'
      },
      primaryButton: {
        value: '确定',
        action: () => {
          this.logMessage = '用户点击了确定按钮'
        }
      }
    })
  }

  showAutoCancelFalse() {
    this.autoCancelState = '自动取消: 关闭'
    this.logMessage = '只能通过点击按钮关闭弹窗'
    AlertDialog.show({
      title: '自动取消关闭',
      message: '点击弹窗外部区域或按返回键无法关闭此弹窗\n\nautoCancel: false\n\n必须点击按钮关闭',
      autoCancel: false,
      primaryButton: {
        value: '确定',
        action: () => {
          this.logMessage = '用户点击了确定按钮关闭弹窗'
        }
      },
      secondaryButton: {
        value: '取消',
        action: () => {
          this.logMessage = '用户点击了取消按钮关闭弹窗'
        }
      }
    })
  }

  showAutoCancelWithCallback() {
    this.autoCancelState = '自动取消: 带回调'
    this.logMessage = '测试取消时的回调函数'
    AlertDialog.show({
      title: '自动取消回调测试',
      message: '点击外部或返回键时会触发cancel回调\n点击按钮也会触发相应的action回调',
      autoCancel: true,
      cancel: () => {
        this.logMessage = 'cancel回调被触发！'
        console.log('Dialog cancelled callback executed')
      },
      primaryButton: {
        value: '主要操作',
        action: () => {
          this.logMessage = '主按钮action回调被触发'
        }
      },
      secondaryButton: {
        value: '次要操作',
        action: () => {
          this.logMessage = '次级按钮action回调被触发'
        }
      }
    })
  }

  showAutoCancelWithDelay() {
    this.autoCancelState = '自动取消: 延时测试'
    this.logMessage = '测试延时关闭效果'
    AlertDialog.show({
      title: '延时关闭测试',
      message: '此弹窗将在3秒后自动关闭',
      autoCancel: true,
      cancel: () => {
        this.logMessage = '弹窗已关闭'
      },
      primaryButton: {
        value: '立即关闭',
        action: () => {
          this.logMessage = '用户主动关闭了弹窗'
        }
      }
    })

    setTimeout(() => {
      this.logMessage = '弹窗应该已经自动关闭'
    }, 3000)
  }

  showAutoCancelMultiple() {
    this.autoCancelState = '自动取消: 多弹窗'
    this.logMessage = '测试多个弹窗的自动取消行为'
    const messages = [
      '第一个弹窗\nautoCancel: true',
      '第二个弹窗\nautoCancel: true',
      '第三个弹窗\nautoCancel: false'
    ]

    messages.forEach((msg, index) => {
      setTimeout(() => {
        AlertDialog.show({
          title: `弹窗 ${index + 1}`,
          message: msg,
          autoCancel: index < 2,
          primaryButton: {
            value: '关闭',
            action: () => {
              this.logMessage = `弹窗 ${index + 1} 已通过按钮关闭`
            }
          }
        })
      }, index * 500)
    })
  }

  showAutoCancelWithClickOutside() {
    this.autoCancelState = '自动取消: 外部点击'
    this.logMessage = '测试点击外部区域的行为'
    AlertDialog.show({
      title: '外部点击测试',
      message: '点击弹窗外部区域观察自动取消行为\n\nautoCancel: true',
      autoCancel: true,
      cancel: () => {
        this.logMessage = '通过点击外部区域取消了弹窗'
      },
      primaryButton: {
        value: '保持弹窗',
        action: () => {
          this.logMessage = '用户选择保持弹窗'
        }
      }
    })
  }

  showAutoCancelWithBackKey() {
    this.autoCancelState = '自动取消: 返回键'
    this.logMessage = '测试按返回键的行为'
    AlertDialog.show({
      title: '返回键测试',
      message: '按返回键观察自动取消行为\n\nautoCancel: true',
      autoCancel: true,
      cancel: () => {
        this.logMessage = '通过返回键取消了弹窗'
      },
      primaryButton: {
        value: '不取消',
        action: () => {
          this.logMessage = '用户点击了按钮'
        }
      }
    })
  }

  showAutoCancelComparison() {
    this.autoCancelState = '自动取消: 对比测试'
    this.logMessage = '同时显示两个不同autoCancel设置的弹窗'

    AlertDialog.show({
      title: '自动取消开启',
      message: 'autoCancel: true\n点击外部或返回键可关闭',
      autoCancel: true,
      cancel: () => {
        this.logMessage = 'autoCancel=true 的弹窗已关闭'
      }
    })

    setTimeout(() => {
      AlertDialog.show({
        title: '自动取消关闭',
        message: 'autoCancel: false\n只能点击按钮关闭',
        autoCancel: false,
        primaryButton: {
          value: '关闭',
          action: () => {
            this.logMessage = 'autoCancel=false 的弹窗已通过按钮关闭'
          }
        }
      })
    }, 200)
  }

  build() {
    NavDestination() {
      Column({ space: 12 }) {
        Text('AlertDialog 自动取消测试用例')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })

        // 当前状态显示
        Row() {
          Text('当前状态: ')
            .fontSize(14)
            .fontColor(Color.Gray)
          Text(this.autoCancelState)
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
            .fontColor(Color.Blue)
        }
        .width('100%')
        .padding(10)
        .backgroundColor('#F0F8FF')
        .borderRadius(8)
        .margin({ left: 10, right: 10 })

        // 基础测试
        Text('基础测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ left: 10, top: 10 })

        Row({ space: 8 }) {
          Button('自动取消: 开启')
            .width('48%')
            .onClick(() => this.showAutoCancelTrue())
          Button('自动取消: 关闭')
            .width('48%')
            .onClick(() => this.showAutoCancelFalse())
        }.width('100%').padding({ left: 10, right: 10 })

        // 回调测试
        Text('回调测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ left: 10, top: 10 })

        Button('自动取消带回调')
          .width('100%')
          .margin({ left: 10, right: 10 })
          .onClick(() => this.showAutoCancelWithCallback())

        // 高级测试
        Text('高级测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ left: 10, top: 10 })

        GridRow({ columns: 2, gutter: 8 }) {
          GridCol() {
            Button('延时关闭测试')
              .width('100%')
              .onClick(() => this.showAutoCancelWithDelay())
          }
          GridCol() {
            Button('多弹窗测试')
              .width('100%')
              .onClick(() => this.showAutoCancelMultiple())
          }
          GridCol() {
            Button('外部点击测试')
              .width('100%')
              .onClick(() => this.showAutoCancelWithClickOutside())
          }
          GridCol() {
            Button('返回键测试')
              .width('100%')
              .onClick(() => this.showAutoCancelWithBackKey())
          }
        }.width('100%').margin({ left: 10, right: 10 })

        // 对比测试
        Text('对比测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ left: 10, top: 10 })

        Button('同时显示对比')
          .width('100%')
          .margin({ left: 10, right: 10 })
          .onClick(() => this.showAutoCancelComparison())

        // 日志显示区域
        Divider()
        Text('操作日志')
          .fontSize(14)
          .fontColor(Color.Gray)
          .margin({ left: 10 })

        Text(this.logMessage)
          .fontSize(13)
          .fontColor(Color.Black)
          .padding(12)
          .width('100%')
          .backgroundColor('#F5F5F5')
          .borderRadius(8)
          .margin({ left: 10, right: 10 })

        Blank()
      }
      .width('100%')
      .height('100%')
    }
    .title('AlertDialog 自动取消')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
