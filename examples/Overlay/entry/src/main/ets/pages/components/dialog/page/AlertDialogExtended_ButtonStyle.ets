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


interface AlertDialogExtendedButtonStyleInterfaceTwo {
  primary: ResourceColor;
  secondary: ResourceColor;
  name: string;
}

interface AlertDialogExtendedButtonStyleInterfaceOne {
  color: ResourceColor;
  name: string;
}

@Entry
@Component
struct AlertDialogExtendedButtonStyle {
  pathStack: NavPathStack = new NavPathStack()
  @State logMessage: string = '选择上方按钮查看不同按钮样式'

  showPrimaryButtonColor(color: ResourceColor, name: string) {
    this.logMessage = `主按钮颜色: ${name}`
    AlertDialog.show({
      title: '主按钮颜色测试',
      message: '测试主按钮的不同颜色效果',
      autoCancel: true,
      primaryButton: {
        value: '主按钮',
        fontColor: color,
        action: () => {
          console.log(`Primary button color: ${name}`)
        }
      },
      secondaryButton: {
        value: '取消',
        action: () => {}
      }
    })
  }

  showSecondaryButtonColor(color: ResourceColor, name: string) {
    this.logMessage = `次级按钮颜色: ${name}`
    AlertDialog.show({
      title: '次级按钮颜色测试',
      message: '测试次级按钮的不同颜色效果',
      autoCancel: true,
      primaryButton: {
        value: '确定',
        action: () => {}
      },
      secondaryButton: {
        value: '次级按钮',
        fontColor: color,
        action: () => {
          console.log(`Secondary button color: ${name}`)
        }
      }
    })
  }

  showBothButtonColors(primaryColor: ResourceColor, secondaryColor: ResourceColor, name: string) {
    this.logMessage = `按钮组合: ${name}`
    AlertDialog.show({
      title: '按钮颜色组合测试',
      message: `主按钮颜色和次级按钮颜色的组合效果`,
      autoCancel: true,
      primaryButton: {
        value: '主要操作',
        fontColor: primaryColor,
        action: () => {
          console.log('Primary button clicked')
        }
      },
      secondaryButton: {
        value: '次要操作',
        fontColor: secondaryColor,
        action: () => {
          console.log('Secondary button clicked')
        }
      }
    })
  }

  showButtonLongText() {
    this.logMessage = '测试长按钮文本'
    AlertDialog.show({
      title: '长按钮文本测试',
      message: '测试按钮文本较长时的显示效果',
      autoCancel: true,
      primaryButton: {
        value: '这是一个很长的按钮文本用于测试显示效果',
        action: () => {
          console.log('Long text primary button')
        }
      }
    })
  }

  showButtonWithEmoji() {
    this.logMessage = '测试带Emoji的按钮'
    AlertDialog.show({
      title: 'Emoji按钮测试',
      message: '测试按钮包含emoji的显示效果',
      autoCancel: true,
      primaryButton: {
        value: '确定 👍',
        action: () => {
          console.log('Button with emoji')
        }
      },
      secondaryButton: {
        value: '取消 ❌',
        action: () => {
          console.log('Cancel with emoji')
        }
      }
    })
  }

  showButtonWithSpecialChars() {
    this.logMessage = '测试带特殊字符的按钮'
    AlertDialog.show({
      title: '特殊字符按钮测试',
      message: '测试按钮包含特殊字符的显示效果',
      autoCancel: true,
      primaryButton: {
        value: '确定 (√)',
        action: () => {}
      },
      secondaryButton: {
        value: '取消 (×)',
        action: () => {}
      }
    })
  }

  showButtonOnlyPrimary() {
    this.logMessage = '仅显示主按钮'
    AlertDialog.show({
      title: '单按钮测试',
      message: '只显示一个主按钮的情况',
      autoCancel: true,
      primaryButton: {
        value: '确定',
        action: () => {
          console.log('Primary button only')
        }
      }
    })
  }

  showButtonOnlySecondary() {
    this.logMessage = '仅显示次级按钮'
    AlertDialog.show({
      title: '单次级按钮测试',
      message: '只显示一个次级按钮的情况',
      autoCancel: true,
      secondaryButton: {
        value: '关闭',
        action: () => {
          console.log('Secondary button only')
        }
      }
    })
  }

  showThreeButtons() {
    this.logMessage = '测试三个按钮'
    AlertDialog.show({
      title: '三按钮测试',
      message: '测试同时显示三个按钮的情况',
      autoCancel: true,
      primaryButton: {
        value: '主要',
        action: () => {
          console.log('Primary button clicked')
        }
      },
      secondaryButton: {
        value: '次要',
        action: () => {
          console.log('Secondary button clicked')
        }
      }
    })
  }

  showButtonFocus() {
    this.logMessage = '测试按钮焦点'
    AlertDialog.show({
      title: '按钮焦点测试',
      message: '测试按钮的默认焦点设置',
      autoCancel: true,
      primaryButton: {
        value: '确定',
        defaultFocus: true,
        action: () => {
          console.log('Focused primary button clicked')
        }
      },
      secondaryButton: {
        value: '取消',
        action: () => {
          console.log('Cancel clicked')
        }
      }
    })
  }

  showButtonDisabledEffect() {
    this.logMessage = '测试按钮禁用效果模拟'
    AlertDialog.show({
      title: '按钮禁用效果',
      message: '模拟按钮禁用的视觉效果（通过样式）',
      autoCancel: true,
      primaryButton: {
        value: '确定',
        fontColor: Color.Gray,
        action: () => {
          this.logMessage = '点击了"禁用"效果的按钮'
        }
      },
      secondaryButton: {
        value: '取消',
        action: () => {}
      }
    })
  }

  showButtonWithDifferentLengths() {
    this.logMessage = '测试不同长度按钮'
    AlertDialog.show({
      title: '不同长度按钮测试',
      message: '测试主按钮和次级按钮文本长度不同时的对齐效果',
      autoCancel: true,
      primaryButton: {
        value: '确认操作',
        action: () => {
          console.log('Short text button')
        }
      },
      secondaryButton: {
        value: '取消操作并返回上一页',
        action: () => {
          console.log('Long text button')
        }
      }
    })
  }

  showMultipleClicks() {
    this.logMessage = '测试多次点击按钮'
    let clickCount = 0
    AlertDialog.show({
      title: '多次点击测试',
      message: '点击按钮查看点击次数变化\n当前点击次数: 0',
      autoCancel: false,
      primaryButton: {
        value: '点击计数',
        action: () => {
          clickCount++
          this.logMessage = `按钮已点击 ${clickCount} 次`
          console.log(`Button clicked ${clickCount} times`)
        }
      },
      secondaryButton: {
        value: '重置',
        action: () => {
          clickCount = 0
          this.logMessage = '计数器已重置'
        }
      }
    })
  }

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 12 }) {
          Text('AlertDialog 按钮样式测试用例')
            .fontSize(22)
            .fontWeight(FontWeight.Bold)
            .margin({ top: 20, bottom: 10 })

          // 主按钮颜色测试
          Text('主按钮颜色')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ left: 10 })

          GridRow({ columns: 3, gutter: 8 }) {
            GridCol() {
              Button('黑色')
                .width('100%')
                .onClick(() => this.showPrimaryButtonColor(Color.Black, '黑色'))
            }
            GridCol() {
              Button('蓝色')
                .width('100%')
                .onClick(() => this.showPrimaryButtonColor(Color.Blue, '蓝色'))
            }
            GridCol() {
              Button('红色')
                .width('100%')
                .onClick(() => this.showPrimaryButtonColor(Color.Red, '红色'))
            }
            GridCol() {
              Button('绿色')
                .width('100%')
                .onClick(() => this.showPrimaryButtonColor(Color.Green, '绿色'))
            }
            GridCol() {
              Button('橙色')
                .width('100%')
                .onClick(() => this.showPrimaryButtonColor(Color.Orange, '橙色'))
            }
            GridCol() {
              Button('紫色')
                .width('100%')
                .onClick(() => this.showPrimaryButtonColor(Color.Pink, '紫色'))
            }
          }.width('100%').margin({ left: 10, right: 10 })

          // 次级按钮颜色测试
          Text('次级按钮颜色')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ left: 10, top: 5 })

          Row({ space: 8 }) {
            ForEach([
              { color: Color.Gray, name: '灰色' },
              { color: Color.Brown, name: '棕色' },
              { color: Color.Green, name: '青色' },
              { color: Color.Pink, name: '粉色' }
            ], (item: AlertDialogExtendedButtonStyleInterfaceOne) => {
              Button(item.name)
                .width('24%')
                .onClick(() => this.showSecondaryButtonColor(item.color, item.name))
            })
          }.width('100%').padding({ left: 10, right: 10 })

          // 按钮颜色组合测试
          Text('按钮颜色组合')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ left: 10, top: 5 })

          Row({ space: 8 }) {
            ForEach([
              { primary: Color.Blue, secondary: Color.Gray, name: '蓝+灰' },
              { primary: Color.Red, secondary: Color.Green, name: '红+绿' },
              { primary: Color.Orange, secondary: Color.Orange, name: '橙+紫' },
              { primary: Color.Black, secondary: Color.Green, name: '黑+青' }
            ], (item: AlertDialogExtendedButtonStyleInterfaceTwo) => {
              Button(item.name)
                .width('24%')
                .onClick(() => this.showBothButtonColors(item.primary, item.secondary, item.name))
            })
          }.width('100%').padding({ left: 10, right: 10 })

          // 特殊按钮内容测试
          Text('特殊内容测试')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ left: 10, top: 5 })

          Row({ space: 8 }) {
            Button('长文本')
              .width('32%')
              .onClick(() => this.showButtonLongText())
            Button('Emoji')
              .width('32%')
              .onClick(() => this.showButtonWithEmoji())
            Button('特殊字符')
              .width('32%')
              .onClick(() => this.showButtonWithSpecialChars())
          }.width('100%').padding({ left: 10, right: 10 })

          // 按钮数量测试
          Text('按钮数量测试')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ left: 10, top: 5 })

          Row({ space: 8 }) {
            Button('仅主按钮')
              .width('48%')
              .onClick(() => this.showButtonOnlyPrimary())
            Button('仅次级按钮')
              .width('48%')
              .onClick(() => this.showButtonOnlySecondary())
          }.width('100%').padding({ left: 10, right: 10 })

          Button('三按钮')
            .width('100%')
            .margin({ left: 10, right: 10 })
            .onClick(() => this.showThreeButtons())

          // 按钮交互测试
          Text('按钮交互测试')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ left: 10, top: 5 })

          GridRow({ columns: 2, gutter: 8 }) {
            GridCol() {
              Button('按钮焦点')
                .width('100%')
                .onClick(() => this.showButtonFocus())
            }
            GridCol() {
              Button('禁用效果')
                .width('100%')
                .onClick(() => this.showButtonDisabledEffect())
            }
            GridCol() {
              Button('不同长度')
                .width('100%')
                .onClick(() => this.showButtonWithDifferentLengths())
            }
            GridCol() {
              Button('多次点击')
                .width('100%')
                .onClick(() => this.showMultipleClicks())
            }
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
            .margin({ left: 10, right: 10, bottom: 10 })
        }
        .width('100%')
      }
    }
    .title('AlertDialog 按钮样式')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
