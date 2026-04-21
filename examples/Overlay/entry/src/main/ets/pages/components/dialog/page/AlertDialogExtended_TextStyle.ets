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


interface GeneratedTypeLiteralInterface_1 {
  size: number;
  name: string;
}

interface GeneratedTypeLiteralInterface_2 {
  weight: number | FontWeight;
  name: string;
}

@Entry
@Component
struct AlertDialogExtendedTextStyle {
  pathStack: NavPathStack = new NavPathStack()
  @State logMessage: string = '选择上方按钮查看不同文本样式'

  showAlertDialogWithTitleSize(fontSize: number, name: string) {
    this.logMessage = `标题字体大小: ${name}`
    AlertDialog.show({
      title: '标题文本样式测试',
      message: '此弹窗测试不同的标题字体大小效果',
      autoCancel: true,
      primaryButton: {
        value: '确定',
        action: () => {
          console.log(`Title font size: ${fontSize}`)
        }
      }
    })
  }

  showAlertDialogWithMessageSize(fontSize: number, name: string) {
    this.logMessage = `消息字体大小: ${name}`
    AlertDialog.show({
      title: '消息文本样式测试',
      message: '此弹窗测试不同的消息字体大小效果',
      autoCancel: true,
      primaryButton: {
        value: '确定',
        action: () => {}
      }
    })
  }

  showAlertDialogWithTitleColor(color: ResourceColor, name: string) {
    this.logMessage = `标题颜色: ${name}`
    AlertDialog.show({
      title: '标题颜色测试',
      message: '此弹窗测试不同的标题颜色效果',
      autoCancel: true,
      primaryButton: {
        value: '确定',
        action: () => {}
      }
    })
  }

  showAlertDialogWithMessageColor(color: ResourceColor, name: string) {
    this.logMessage = `消息颜色: ${name}`
    AlertDialog.show({
      title: '消息颜色测试',
      message: '此弹窗测试不同的消息颜色效果',
      autoCancel: true,
      primaryButton: {
        value: '确定',
        action: () => {}
      }
    })
  }

  showAlertDialogWithFontWeight(weight: number, name: string) {
    this.logMessage = `字体粗细: ${name}`
    AlertDialog.show({
      title: '字体粗细测试',
      message: '此弹窗测试不同的字体粗细效果',
      autoCancel: true,
      primaryButton: {
        value: '确定',
        action: () => {}
      }
    })
  }

  showAlertDialogWithLongText() {
    this.logMessage = '测试长文本显示'
    AlertDialog.show({
      title: '长文本测试',
      message: '这是一个测试长文本的弹窗。\n\n' +
        '当文本内容较长时，弹窗会自动调整大小以适应内容。\n\n' +
        '多行文本也能正确显示和换行。\n\n' +
        '这样可以测试弹窗对长文本内容的支持情况。',
      autoCancel: true,
      primaryButton: {
        value: '确定',
        action: () => {}
      }
    })
  }

  showAlertDialogWithEmoji() {
    this.logMessage = '测试emoji显示'
    AlertDialog.show({
      title: 'Emoji 测试 😊',
      message: '这是一个包含emoji的弹窗测试。\n\n' +
        '表情符号: 😀 😃 😄 😁 😆 😅 🤣 😂 🙂 🙃 😉 😊 😇 🥰 😍 🤩 😘 😗 😚 😙 😋 😛 😜 🤪 😝 🤑 🤗 🤭 🤫 🤔 🤐 🤨 😐 😑 😶 😏 😒 🙄 😬 🤥 😌 😔 😪 🤤 😴 😷 🤒 🤕 🤢 🤮 🤧  🤠 🤡 🥳 🥴 🥺 🤵 👰 🤰 👶 👧 👦 👧‍🦱 👦‍🦱 👧‍🦰 👦‍🦰 👱‍♀️ 👱 👱‍♂️ 👩‍🦳 👨‍🦳 👩‍🦲 👨‍🦲 🧓 👴 👵 👲 🤴 👸 👳‍♂️ 👳‍♀️ 👷‍♀️ 👷 👷‍♂️ 💂‍♀️ 💂 💂‍♂️ 🕵️‍♀️ 🕵️ 🕵️‍♂️ 👮‍♀️ 👮 👮‍♂️ 👩‍⚖️ 👨‍⚖️ 👩‍🌾 👨‍🌾 👩‍🍳 👨‍🍳 👩‍🔧 👨‍🔧 👩‍🏭 👨‍🏭 👩‍💼 👨‍💼 👩‍🏫 👨‍🏫 👩‍🎓 👨‍🎓 👩‍🎨 👨‍🎨 👩‍🚒 👨‍🚒 👩‍✈️ 👨‍✈️ 👩‍🚀 👨‍🚀 👩‍⚕️ 👨‍⚕️ 👩‍🔬 👨‍🔬 👩‍💻 👨‍💻 👩‍🎤 👨‍🎤 👩‍🏌️‍♀️ 👨‍🏌️',
      autoCancel: true,
      primaryButton: {
        value: '确定',
        action: () => {}
      }
    })
  }

  showAlertDialogWithSpecialChars() {
    this.logMessage = '测试特殊字符显示'
    AlertDialog.show({
      title: '特殊字符测试',
      message: '特殊符号测试：\n\n' +
        '数学符号：∑ ∏ ∫ ∞ √ ≈ ≠ ≤ ≥ ± × ÷\n' +
        '货币符号：$ € £ ¥ ¢ ₽ ₹ ₩ ₪ ₱\n' +
        '箭头符号：← ↑ → ↓ ↔ ↕ ↖ ↗ ↘ ↙\n' +
        '其他符号：© ® ™ § ¶ • ○ ● ■ □ ▲ ▼',
      autoCancel: true,
      primaryButton: {
        value: '确定',
        action: () => {}
      }
    })
  }

  showAlertDialogWithRichContent() {
    this.logMessage = '测试富文本内容'
    AlertDialog.show({
      title: '富文本内容测试',
      message: '第一行普通文本\n\n' +
        '第二行较长的文本内容用于测试布局效果\n' +
        '继续第二行的内容看看是否会自动换行\n\n' +
        '第三行测试\n\n' +
        '最后一行结束测试',
      autoCancel: true,
      primaryButton: {
        value: '关闭',
        action: () => {}
      }
    })
  }

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 12 }) {
          Text('AlertDialog 文本样式测试用例')
            .fontSize(22)
            .fontWeight(FontWeight.Bold)
            .margin({ top: 20, bottom: 10 })

          // 标题字体大小测试
          Text('标题字体大小')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ left: 10 })

          Row({ space: 8 }) {
            ForEach([
              { size: 14, name: '14px' },
              { size: 16, name: '16px' },
              { size: 18, name: '18px' },
              { size: 20, name: '20px' },
              { size: 24, name: '24px' }
            ], (item: GeneratedTypeLiteralInterface_1) => {
              Button(item.name)
                .width('19%')
                .fontSize(12)
                .onClick(() => this.showAlertDialogWithTitleSize(item.size, item.name))
            })
          }.width('100%').padding({ left: 10, right: 10 })

          // 消息字体大小测试
          Text('消息字体大小')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ left: 10, top: 5 })

          Row({ space: 8 }) {
            ForEach([
              { size: 12, name: '12px' },
              { size: 14, name: '14px' },
              { size: 16, name: '16px' },
              { size: 18, name: '18px' },
              { size: 20, name: '20px' }
            ], (item: GeneratedTypeLiteralInterface_1) => {
              Button(item.name)
                .width('19%')
                .fontSize(12)
                .onClick(() => this.showAlertDialogWithMessageSize(item.size, item.name))
            })
          }.width('100%').padding({ left: 10, right: 10 })

          // 文本颜色测试
          Text('文本颜色')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ left: 10, top: 5 })

          GridRow({ columns: 3, gutter: 8 }) {
            GridCol() {
              Button('标题黑色')
                .width('100%')
                .onClick(() => this.showAlertDialogWithTitleColor(Color.Black, '黑色'))
            }
            GridCol() {
              Button('标题蓝色')
                .width('100%')
                .onClick(() => this.showAlertDialogWithTitleColor(Color.Blue, '蓝色'))
            }
            GridCol() {
              Button('标题红色')
                .width('100%')
                .onClick(() => this.showAlertDialogWithTitleColor(Color.Red, '红色'))
            }
            GridCol() {
              Button('消息绿色')
                .width('100%')
                .onClick(() => this.showAlertDialogWithMessageColor(Color.Green, '绿色'))
            }
            GridCol() {
              Button('消息橙色')
                .width('100%')
                .onClick(() => this.showAlertDialogWithMessageColor(Color.Orange, '橙色'))
            }
          }.width('100%').margin({ left: 10, right: 10 })

          // 字体粗细测试
          Text('字体粗细')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ left: 10, top: 5 })

          Row({ space: 8 }) {
            ForEach([
              { weight: FontWeight.Normal, name: '正常' },
              { weight: FontWeight.Medium, name: '中等' },
              { weight: FontWeight.Bold, name: '粗体' },
              { weight: 900, name: '超粗' }
            ], (item: GeneratedTypeLiteralInterface_2) => {
              Button(item.name)
                .width('24%')
                .fontSize(12)
                .onClick(() => this.showAlertDialogWithFontWeight(item.weight, item.name))
            })
          }.width('100%').padding({ left: 10, right: 10 })

          // 特殊内容测试
          Text('特殊内容测试')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ left: 10, top: 5 })

          GridRow({ columns: 2, gutter: 8 }) {
            GridCol() {
              Button('长文本')
                .width('100%')
                .onClick(() => this.showAlertDialogWithLongText())
            }
            GridCol() {
              Button('Emoji')
                .width('100%')
                .onClick(() => this.showAlertDialogWithEmoji())
            }
            GridCol() {
              Button('特殊字符')
                .width('100%')
                .onClick(() => this.showAlertDialogWithSpecialChars())
            }
            GridCol() {
              Button('富文本')
                .width('100%')
                .onClick(() => this.showAlertDialogWithRichContent())
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
    .title('AlertDialog 文本样式')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
