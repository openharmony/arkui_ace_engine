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


interface AlertDialogExtendedStylesInterface {
  color: ResourceColor;
  name: string;
}

@Entry
@Component
struct AlertDialogExtendedStyles {
  pathStack: NavPathStack = new NavPathStack()
  @State dialogBackgroundColor: ResourceColor = Color.White
  @State dialogTitle: string = '样式测试弹窗'
  @State dialogMessage: string = '这是一个样式测试弹窗，用于测试不同的背景颜色和样式效果'
  @State logMessage: string = '点击上方按钮查看不同样式效果'

  showAlertDialog(bgColor: ResourceColor, title: string, msg: string) {
    this.dialogBackgroundColor = bgColor
    this.dialogTitle = title
    this.dialogMessage = msg

    AlertDialog.show({
      title: this.dialogTitle,
      message: this.dialogMessage,
      autoCancel: true,
      alignment: DialogAlignment.Center,
      backgroundColor: this.dialogBackgroundColor,
      primaryButton: {
        value: '确定',
        action: () => {
          this.logMessage = `样式测试: 背景色=${this.bgColorToString(bgColor)}, 标题=${title}`
          console.log(this.logMessage)
        }
      },
      secondaryButton: {
        value: '取消',
        action: () => {
          this.logMessage = '用户点击了取消'
          console.log(this.logMessage)
        }
      }
    })
  }

  bgColorToString(color: ResourceColor): string {
    if (color === Color.White) return 'White'
    if (color === Color.Red) return 'Red'
    if (color === Color.Green) return 'Green'
    if (color === Color.Blue) return 'Blue'
    if (color === Color.Yellow) return 'Yellow'
    if (color === Color.Orange) return 'Orange'
    if (color === Color.Pink) return 'Pink'
    if (color === Color.Gray) return 'Gray'
    if (typeof color === 'string') return color
    if (typeof color === 'number') return `0x${color.toString(16)}`
    return 'Unknown'
  }

  build() {
    NavDestination() {
      Column({ space: 15 }) {
        Text('AlertDialog 样式测试用例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })

        // 基础颜色测试
        Text('基础颜色测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ left: 10 })

        GridRow({ columns: 3, gutter: 8 }) {
          ForEach([
            { color: Color.White, name: '白色' },
            { color: Color.Red, name: '红色' },
            { color: Color.Green, name: '绿色' },
            { color: Color.Blue, name: '蓝色' },
            { color: Color.Yellow, name: '黄色' },
            { color: Color.Orange, name: '橙色' }
          ], (item: AlertDialogExtendedStylesInterface, index: number) => {
            GridCol() {
              Button(item.name)
                .width('100%')
                .backgroundColor(item.color)
                .fontColor(item.color === Color.Yellow ? Color.Black : Color.White)
                .onClick(() => {
                  this.showAlertDialog(item.color, `${item.name}弹窗`, '这是使用' + item.name + '作为背景的弹窗')
                })
            }
          })
        }.width('100%').margin({ left: 10, right: 10 })

        // 深色系测试
        Text('深色系测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ left: 10, top: 10 })

        GridRow({ columns: 3, gutter: 8 }) {
          ForEach([
            { color: Color.Pink, name: '粉色' },
            { color: Color.Gray, name: '灰色' },
            { color: '#FF6B6B', name: '珊瑚红' },
            { color: '#4ECDC4', name: '绿松石' }
          ], (item: AlertDialogExtendedStylesInterface, index: number) => {
            GridCol() {
              Button(item.name)
                .width('100%')
                .backgroundColor(item.color)
                .fontColor(Color.White)
                .onClick(() => {
                  this.showAlertDialog(item.color, `${item.name}弹窗`, '这是使用' + item.name + '作为背景的弹窗')
                })
            }
          })
        }.width('100%').margin({ left: 10, right: 10 })

        // 十六进制颜色测试
        Text('十六进制颜色测试')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ left: 10, top: 10 })

        GridRow({ columns: 3, gutter: 8 }) {
          ForEach([
            { color: 0xFFF5F5DC, name: '米色' },
            { color: 0xFFFAFAD2, name: '浅金黄' },
            { color: 0xFFE0FFFF, name: '浅青' },
            { color: 0xFFFFE4E1, name: '薄雾玫瑰' },
            { color: 0xFFE6E6FA, name: '淡紫' },
            { color: 0xFFF0FFF0, name: '蜜露' }
          ], (item: AlertDialogExtendedStylesInterface, index: number) => {
            GridCol() {
              Button(item.name)
                .width('100%')
                .backgroundColor(item.color)
                .fontColor(Color.Black)
                .onClick(() => {
                  this.showAlertDialog(item.color, `${item.name}弹窗`, '这是使用' + item.name + '作为背景的弹窗')
                })
            }
          })
        }.width('100%').margin({ left: 10, right: 10 })

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
    .title('AlertDialog 样式测试')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
