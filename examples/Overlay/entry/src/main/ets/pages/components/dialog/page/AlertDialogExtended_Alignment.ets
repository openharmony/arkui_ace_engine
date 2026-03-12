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
struct AlertDialogExtendedAlignment {
  pathStack: NavPathStack = new NavPathStack()
  @State currentAlignment: string = 'Center'
  @State logMessage: string = '选择上方对齐方式查看效果'

  showAlertDialogWithAlignment(alignment: DialogAlignment, name: string) {
    this.currentAlignment = name
    AlertDialog.show({
      title: '对齐方式测试',
      message: `当前对齐方式: ${name}\n\n对话框将在指定位置显示`,
      alignment: alignment,
      autoCancel: true,
      primaryButton: {
        value: '确定',
        action: () => {
          this.logMessage = `使用了 ${name} 对齐方式`
          console.log(`Dialog aligned to ${name}`)
        }
      },
      secondaryButton: {
        value: '取消',
        action: () => {
          this.logMessage = '用户取消了对齐测试'
        }
      }
    })
  }

  build() {
    NavDestination() {
      Column({ space: 15 }) {
        Text('AlertDialog 位置对齐测试用例')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })

        // 基础对齐方式
        Text('基础对齐方式')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ left: 10 })

        Row({ space: 8 }) {
          Button('顶部')
            .width('32%')
            .onClick(() => this.showAlertDialogWithAlignment(DialogAlignment.Top, 'Top'))
          Button('底部')
            .width('32%')
            .onClick(() => this.showAlertDialogWithAlignment(DialogAlignment.Bottom, 'Bottom'))
          Button('居中')
            .width('32%')
            .onClick(() => this.showAlertDialogWithAlignment(DialogAlignment.Center, 'Center'))
        }.width('100%').padding({ left: 10, right: 10 })

        // 水平对齐
        Text('水平对齐')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ left: 10 })

        Row({ space: 8 }) {
          Button('左对齐')
            .width('23%')
            .onClick(() => this.showAlertDialogWithAlignment(DialogAlignment.CenterStart, 'Start'))
          Button('右对齐')
            .width('23%')
            .onClick(() => this.showAlertDialogWithAlignment(DialogAlignment.CenterEnd, 'End'))
          Button('顶部左')
            .width('23%')
            .onClick(() => this.showAlertDialogWithAlignment(DialogAlignment.TopStart, 'TopStart'))
          Button('顶部右')
            .width('23%')
            .onClick(() => this.showAlertDialogWithAlignment(DialogAlignment.TopEnd, 'TopEnd'))
        }.width('100%').padding({ left: 10, right: 10 })

        Row({ space: 8 }) {
          Button('底部左')
            .width('23%')
            .onClick(() => this.showAlertDialogWithAlignment(DialogAlignment.BottomStart, 'BottomStart'))
          Button('底部右')
            .width('23%')
            .onClick(() => this.showAlertDialogWithAlignment(DialogAlignment.BottomEnd, 'BottomEnd'))
          Button('默认')
            .width('48%')
            .onClick(() => this.showAlertDialogWithAlignment(DialogAlignment.Default, 'Default'))
        }.width('100%').padding({ left: 10, right: 10 })

        // 自定义偏移测试
        Text('自定义偏移测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ left: 10 })

        GridRow({ columns: 3, gutter: 8 }) {
          GridCol() {
            Button('左偏移')
              .width('100%')
              .onClick(() => {
                AlertDialog.show({
                  title: '偏移测试',
                  message: '向左偏移的对话框',
                  alignment: DialogAlignment.Center,
                  autoCancel: true,
                  primaryButton: {
                    value: '确定',
                    action: () => {
                      this.logMessage = '左偏移测试完成'
                    }
                  }
                })
              })
          }
          GridCol() {
            Button('右偏移')
              .width('100%')
              .onClick(() => {
                AlertDialog.show({
                  title: '偏移测试',
                  message: '向右偏移的对话框',
                  alignment: DialogAlignment.Center,
                  autoCancel: true,
                  primaryButton: {
                    value: '确定',
                    action: () => {
                      this.logMessage = '右偏移测试完成'
                    }
                  }
                })
              })
          }
          GridCol() {
            Button('顶部偏移')
              .width('100%')
              .onClick(() => {
                AlertDialog.show({
                  title: '偏移测试',
                  message: '向顶部偏移的对话框',
                  alignment: DialogAlignment.Center,
                  autoCancel: true,
                  primaryButton: {
                    value: '确定',
                    action: () => {
                      this.logMessage = '顶部偏移测试完成'
                    }
                  }
                })
              })
          }
          GridCol() {
            Button('底部偏移')
              .width('100%')
              .onClick(() => {
                AlertDialog.show({
                  title: '偏移测试',
                  message: '向底部偏移的对话框',
                  alignment: DialogAlignment.Center,
                  autoCancel: true,
                  primaryButton: {
                    value: '确定',
                    action: () => {
                      this.logMessage = '底部偏移测试完成'
                    }
                  }
                })
              })
          }
          GridCol() {
            Button('左上偏移')
              .width('100%')
              .onClick(() => {
                AlertDialog.show({
                  title: '偏移测试',
                  message: '向左上角偏移的对话框',
                  alignment: DialogAlignment.TopStart,
                  autoCancel: true,
                  primaryButton: {
                    value: '确定',
                    action: () => {
                      this.logMessage = '左上偏移测试完成'
                    }
                  }
                })
              })
          }
          GridCol() {
            Button('右下偏移')
              .width('100%')
              .onClick(() => {
                AlertDialog.show({
                  title: '偏移测试',
                  message: '向右下角偏移的对话框',
                  alignment: DialogAlignment.BottomEnd,
                  autoCancel: true,
                  primaryButton: {
                    value: '确定',
                    action: () => {
                      this.logMessage = '右下偏移测试完成'
                    }
                  }
                })
              })
          }
        }.width('100%').margin({ left: 10, right: 10 })

        // 组合对齐测试
        Text('组合对齐测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ left: 10, top: 5 })

        Row({ space: 8 }) {
          Button('居中多弹窗')
            .width('48%')
            .onClick(() => {
              for (let i = 0; i < 3; i++) {
                setTimeout(() => {
                  AlertDialog.show({
                    title: `弹窗 ${i + 1}`,
                    message: '多个居中对齐的弹窗测试',
                    alignment: DialogAlignment.Center,
                    autoCancel: true,
                    primaryButton: {
                      value: '关闭',
                      action: () => {
                        this.logMessage = `弹窗 ${i + 1} 已关闭`
                      }
                    }
                  })
                }, i * 500)
              }
            })
          Button('不同位置')
            .width('48%')
            .onClick(() => {
              const alignments: DialogAlignment[] = [
                DialogAlignment.Top,
                DialogAlignment.Bottom,
                DialogAlignment.Center
              ]
              alignments.forEach((align, index) => {
                setTimeout(() => {
                  AlertDialog.show({
                    title: `位置 ${index + 1}`,
                    message: `对齐方式: ${align}`,
                    alignment: align,
                    autoCancel: true,
                    primaryButton: {
                      value: '确定',
                      action: () => {}
                    }
                  })
                }, index * 300)
              })
            })
        }.width('100%').padding({ left: 10, right: 10 })

        // 日志显示区域
        Divider()
        Text('操作日志')
          .fontSize(14)
          .fontColor(Color.Gray)
          .margin({ left: 10 })

        Text(this.logMessage)
          .fontSize(12)
          .fontColor(Color.Black)
          .padding(10)
          .width('100%')
          .backgroundColor('#F5F5F5')
          .borderRadius(8)
          .margin({ left: 10, right: 10 })

        Blank()
      }
      .width('100%')
      .height('100%')
    }
    .title('AlertDialog 位置对齐')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
