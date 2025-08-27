/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
import { MyComponent } from './MyComponenet'

@Builder
export function PopupMessageBuilder(name: string, param: Object) {
  PopupExample08()
}

interface ButtonItem {
  value: string
  action: () => void
}

interface PopupOptions1 {
  message?: string
  messageOptions?: PopupMessageOptions
  primaryButton?: ButtonItem
  secondaryButton?: ButtonItem
}

@Extend(Column)
function columnStyle() {
  .backgroundColor(Color.Pink)
  .width('100%')
  .padding(5)
  .borderWidth(1.0)
}

@Entry
@Component
struct PopupExample08 {
  pathStack: NavPathStack = new NavPathStack()
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, 0, 0]
  @State handlePopup: boolean = false
  @State handlePopup_1: boolean = false
  @State showInSubwindow: boolean = false
  private popupOptionMessageList: PopupOptions1[] = [
    // 1
    {
      message: 'Popup message',
    },
    // 2
    {
      message: undefined
    },
    // 3
    {
      message: 'Popup message '.repeat(0),
    },
    // 4
    {
      message: 'Popup message '.repeat(20),
    },
    // 5
    {
      message: 'Popup message Popup message Popup message \n'.repeat(3),
    },
    // 6
    {
      message: 'Popup message '.repeat(200),
    },
    // 7
    {
      message: 'Popup message Popup message Popup message \n'.repeat(30),
    },
    // 8
    {
      message: 'Popup message Popup \n'.repeat(3),
      messageOptions: undefined,
    },
    // 9
    {
      message: 'Popup message Popup \n'.repeat(3),
      messageOptions: {},
    },
    // 10
    {
      message: 'Popup message Popup \n'.repeat(3),
      messageOptions: {
        textColor: undefined,
        font: undefined,
      }
    },
    // 11
    {
      message: 'Popup message Popup \n'.repeat(3),
      messageOptions: {
        font: {},
      }
    },
    // 12
    {
      message: 'Popup message Popup \n'.repeat(3),
      messageOptions: {
        textColor: Color.Blue,
        font: {
          size: undefined,
          weight: -100,
          style: FontStyle.Normal,
          family: undefined
        },
      }
    },
    // 13
    {
      message: 'Popup message Popup \n'.repeat(3),
      messageOptions: {
        textColor: '#FF0000FF',
        font: {
          size: 16.0,
          weight: '0',
          style: FontStyle.Italic,
          family: undefined,
        },
      }
    },
    // 14
    {
      message: 'Popup message Popup \n'.repeat(3),
      messageOptions: {
        textColor: 0X0000FF,
        font: {
          size: '-16.0',
          weight: '300',
          style: undefined,
        },
      }
    },
    // 15
    {
      message: 'Popup message Popup \n'.repeat(3),
      messageOptions: {
        textColor: undefined,
        font: {
          size: '0vp',
        },
      }
    },
    // 16
    {
      message: 'Popup message Popup \n'.repeat(3),
      messageOptions: {
        textColor: 'rgba(0, 0, 255, 1.0)',
        font: {
          size: '60',
          weight: 600,
        },
      }
    },
    // 17
    {
      message: 'Popup message Popup \n'.repeat(3),
      messageOptions: {
        textColor: 'color-blue',
        font: {
          size: 'popup',
          weight: 1200,
        },
      }
    },
    // 18
    {
      message: 'Popup message Popup \n'.repeat(3),
      messageOptions: {
        textColor: Color.Transparent,
      }
    },
    // 19
    {
      message: 'Popup message Popup \n'.repeat(3),
      messageOptions: {
        font: {
          weight: '50%',
        }
      }
    },
    // 20
    {
      message: 'Popup message Popup \n'.repeat(3),
      messageOptions: {
        font: {
          weight: '50vp',
        }
      }
    },
    // 21
    {
      message: 'Popup message Popup \n'.repeat(3),
      messageOptions: {
        font: {
          weight: undefined,
        }
      }
    },
  ]

  private popupOptionButtonList: PopupOptions1[] = [
    // 1
    {
      message: 'Popup message Popup message',
      primaryButton: {
        value: 'cancel',
        action: () => {
          console.info('popup cancel button on')
          this.handlePopup = false
        }
      },
      secondaryButton: {
        value: 'confirm',
        action: () => {
          console.info('popup confirm button on')
          this.handlePopup = false
        }
      },
    },
    // 2
    {
      message: 'Popup message Popup message',
      primaryButton: {
        value: 'cancel'.repeat(0),
        action: () => {
          console.info('popup cancel button on')
          this.handlePopup = false
        }
      },
      secondaryButton: {
        value: 'confirm'.repeat(0),
        action: () => {
          console.info('popup confirm button on')
          this.handlePopup = false
        }
      },
    },
    // 3
    {
      message: 'Popup message Popup message',
      primaryButton: {
        value: 'cancel'.repeat(20),
        action: () => {
          console.info('popup cancel button on')
          this.handlePopup = false
        }
      },
      secondaryButton: {
        value: 'confirm'.repeat(20),
        action: () => {
          console.info('popup confirm button on')
          this.handlePopup = false
        }
      },
    },
    // 4
    {
      message: 'Popup message Popup message',
      primaryButton: {
        value: 'cancel \n'.repeat(3),
        action: () => {
          console.info('popup cancel button on')
          this.handlePopup = false
        }
      },
      secondaryButton: {
        value: 'confirm \n'.repeat(3),
        action: () => {
          console.info('popup confirm button on')
          this.handlePopup = false
        }
      },
    },
    // 5
    {
      message: 'Popup message Popup message',
      primaryButton: {
        value: 'cancel'.repeat(20),
        action: () => {
          console.info('popup cancel button on')
          this.handlePopup = false
        }
      }
    },
    // 6
    {
      message: 'Popup message Popup message',
      secondaryButton: {
        value: 'confirm'.repeat(0),
        action: () => {
          console.info('popup confirm button on')
          this.handlePopup = false
        }
      },
    },
  ]

  build() {
    NavDestination() {
      Scroll(this.scroller) {
        Column({ space: 5 }) {
          Text('切换测试参数：')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
            .margin({ left: 10 })
          Text('切换message参数：')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
            .margin({ left: 10 })
          Row({ space: 2 }) {
            Text(`${this.index[0] + 1}` + '/')
              .fontSize(9)
              .fontColor(0xCCCCCC)
            Text(`${this.popupOptionMessageList.length}`)
              .fontSize(9)
              .fontColor(0xCCCCCC)
            MyComponent({
              title: 'Test0+', func: () => {
                this.index[0]++
                if (this.index[0] == this.popupOptionMessageList.length) {
                  this.index[0] = 0
                }
              }
            })
            MyComponent({
              title: 'Test0+', func: () => {
                this.index[0]--
                if (this.index[0] <= -1) {
                  this.index[0] = this.popupOptionMessageList.length - 1
                }
              }
            })
          }

          Text('切换button参数：')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
            .margin({ left: 10 })
          Row({ space: 2 }) {
            Text(`${this.index[1] + 1}` + '/')
              .fontSize(9)
              .fontColor(0xCCCCCC)
            Text(`${this.popupOptionButtonList.length}`)
              .fontSize(9)
              .fontColor(0xCCCCCC)
            MyComponent({
              title: 'Test1+', func: () => {
                this.index[1]++
                if (this.index[1] == this.popupOptionButtonList.length) {
                  this.index[1] = 0
                }
              }
            })
            MyComponent({
              title: 'Test1-', func: () => {
                this.index[1]--
                if (this.index[1] <= -1) {
                  this.index[1] = this.popupOptionButtonList.length - 1
                }
              }
            })
          }

          Divider()

          Column({ space: 5 }) {
            Text('popup设置message参数')
              .fontSize(9)
              .width('100%')
            Button('Popup message')
              .backgroundColor(Color.Blue)
              .fontSize(9)
              .onClick(() => {
                this.handlePopup = !this.handlePopup
              })
              .bindPopup(this.handlePopup, {
                message: this.popupOptionMessageList[this.index[0]].message,
                messageOptions: this.popupOptionMessageList[this.index[0]].messageOptions,
                showInSubWindow: false,
                onStateChange: (e) => {
                  console.info(JSON.stringify(e.isVisible))
                  if (!e.isVisible) {
                    this.handlePopup = false
                  }
                }
              })

            Text('popup设置Button参数')
              .fontSize(9)
              .width('100%')
            Button('Popup button')
              .backgroundColor(Color.Blue)
              .fontSize(9)
              .onClick(() => {
                this.handlePopup_1 = !this.handlePopup_1
              })
              .bindPopup(this.handlePopup_1, {
                message: this.popupOptionButtonList[this.index[1]].message,
                primaryButton: this.popupOptionButtonList[this.index[1]].primaryButton,
                secondaryButton: this.popupOptionButtonList[this.index[1]].secondaryButton,
                showInSubWindow: false,
                onStateChange: (e) => {
                  console.info(JSON.stringify(e.isVisible))
                  if (!e.isVisible) {
                    this.handlePopup_1 = false
                  }
                }
              })
          }
          .columnStyle()
        }
        .width('100%')
        .height('100%')
        .padding(10)
      }
      .width('100%')
      .height('100%')
    }
    .title('PopupStyleBuilder')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}