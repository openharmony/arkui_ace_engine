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
import { Popup, PopupTextOptions, PopupButtonOptions, PopupIconOptions } from '@ohos.arkui.advanced.Popup';

@Builder
export function PopupBigBuilder(name: string, param: Object) {
  PopupBigExample()
}

@Extend(Column)
function pinkColumnStyle() {
  .width(30).height(30)
  .borderWidth(1.0)
  .backgroundColor(Color.Pink)
}

@Extend(Text)
function textStyle() {
  .fontSize(9)
  .fontColor(0x000000)
  .width('100%')
}

@Entry
@Component
struct PopupBigExample {
  pathStack: NavPathStack = new NavPathStack()
  @State customPopupList: boolean[] = [false, false, false, false, false, false, false]
  @State showInSubWindow?: (boolean | undefined) = undefined
  @State popupFocusable: boolean = true
  @State oneButtonColor: string = '#FFC0CB'
  @State twoButtonColor: string = '#87CEFA'
  @State threeButtonColor: string = '#90EE90'

  //尺寸较大的builder
  @Builder
  sizePopupBuilder() {
    Row({ space: 2 }) {
      Column()
        .width('80%').height('80%')
        .backgroundColor(Color.Green)
    }
    .justifyContent(FlexAlign.Center)
    .padding(10)

    .width('60%').height('120%')
  }

  //builder内设置close关闭气泡，设置autoCancel为false
  @Builder
  closeEventPopupBuilder() {
    Row({ space: 2 }) {
      Column() {
        Text('Close')
          .margin(10)
          .onClick(() => {
            this.customPopupList[1] = false
          })
          .borderWidth(1.0)
      }
      .width('80%').height('80%')
      .backgroundColor(Color.Green)
    }
    .justifyContent(FlexAlign.Center)
    .padding(10)

    .width('60%').height('30%')
  }

  //builder内组件绘制超出父组件，是否被气泡剪裁
  @Builder
  componentClipPopupBuilder() {
    Column() {
      Column() {
      }
      .width(180).height(200)
      .backgroundColor(Color.Green)
    }
    .clip(false)
    .borderWidth(1.0)
    .width(160)
    .height(120)
    .margin(20)
  }

  //builder内组件设置position属性验证气泡绘制效果
  @Builder
  componentPositionPopupBuilder() {
    Column() {
      Column() {
        Text('Position')
      }
      .width(180).height(140)
      .backgroundColor(Color.Green)
    }
    .position({ x: 50, y: 50 })
    .borderWidth(1.0)
    .width(160)
    .height(120)
    .margin(20)
  }

  //builder内组件设置offset属性验证气泡绘制效果
  @Builder
  componentOffsetPopupBuilder() {
    Column() {
      Column() {
        Text('Offset')
      }
      .width(180).height(140)
      .backgroundColor(Color.Green)
    }
    .offset({ x: 50, y: 50 })
    .borderWidth(1.0)
    .width(160)
    .height(120)
    .margin(20)
  }

  //builder内组件设置验证气泡和主窗口的走焦：验证走焦
  @Builder
  focusEventPopupBuilder() {
    Column({ space: 20 }) {
      // 通过外接键盘的上下键可以让焦点在三个按钮间移动，按钮获焦时颜色变化，失焦时变回原背景色
      Button('First Button')
        .backgroundColor(this.oneButtonColor)
        .width(200)
        .height(70)
        .fontColor(Color.Black)
        .focusable(true)
        .onFocus(() => {
          this.oneButtonColor = '#FF0000'
        })
        .onBlur(() => {
          this.oneButtonColor = '#FFC0CB'
        })
      Button('Second Button')
        .backgroundColor(this.twoButtonColor)
        .width(200)
        .height(70)
        .fontColor(Color.Black)
        .focusable(true)
        .onFocus(() => {
          this.twoButtonColor = '#FF0000'
        })
        .onBlur(() => {
          this.twoButtonColor = '#87CEFA'
        })
      Button('Third Button')
        .backgroundColor(this.threeButtonColor)
        .width(200)
        .height(70)
        .fontColor(Color.Black)
        .focusable(true)
        .onFocus(() => {
          this.threeButtonColor = '#FF0000'
        })
        .onBlur(() => {
          this.threeButtonColor = '#90EE90'
        })
    }.width(240).margin(10)
  }

  //builder内设置高级组件Popup：验证走焦和关闭回调
  @Builder
  popupAdPopupBuilder() {
    Row() {
      // popup 自定义高级组件
      Popup({
        //PopupIconOptions 类型设置图标内容
        icon: {
          image: $r('app.media.app_icon'),
          width: 20,
          height: 20,
          fillColor: Color.Green
        } as PopupIconOptions,
        // PopupTextOptions 类型设置文字内容
        title: {
          text: 'This is a popup with PopupOptions',
          fontWeight: FontWeight.Normal,
        } as PopupTextOptions,
        //PopupTextOptions 类型设置文字内容
        message: {
          text: 'This is the message',
        } as PopupTextOptions,

        showClose: true,
        onClose: () => {
          this.customPopupList[6] = false
          console.info('close Button click')
        },
        // PopupButtonOptions 类型设置按钮内容
        buttons: [{
          text: 'confirm',
          action: () => {
            this.customPopupList[6] = false
            console.info('confirm button click')
          },
          fontColor: Color.Black,
        },
          {
            text: 'cancel',
            action: () => {
              this.customPopupList[6] = false
              console.info('cancel button click')
            },
            fontColor: Color.Black,
          },] as [PopupButtonOptions?, PopupButtonOptions?],

      })
    }
    .width(240)
    .height(120)
    .borderRadius(20)
    .justifyContent(FlexAlign.Center)
  }

  // popup构造器定义弹框内容
  @Builder popupBuilder() {
    Row({ space: 2 }) {
      Image($r('app.media.app_icon'))
        .width(24)
        .height(24)
        .margin({ left: -5 })

      Text('Custom Popup')
        .fontSize(10)
    }
    .width(100)
    .height(50)
    .padding(5)
  }

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 5 }) {
          Text('尺寸较大的builder:')
            .textStyle()
          Column() {
          }
          .pinkColumnStyle()
          .key('extremeSize')
          .onClick(() => {
            this.customPopupList[0] = !this.customPopupList[0]
          })
          .bindPopup(this.customPopupList[0], {
            builder: this.sizePopupBuilder(),

            placement: Placement.RightTop,
            popupColor: Color.Orange,
            onStateChange: (e) => {
              console.info(JSON.stringify(e.isVisible))
              if (!e.isVisible) {
                this.customPopupList[0] = false
              }
            }
          })

          Text('关闭事件的builder:')
            .textStyle()
          Column() {
          }
          .pinkColumnStyle()
          .key('eventClose')
          .onClick(() => {
            this.customPopupList[1] = !this.customPopupList[1]
          })
          .bindPopup(this.customPopupList[1], {
            builder: this.closeEventPopupBuilder(),

            autoCancel: false,
            placement: Placement.RightTop,
            popupColor: Color.Orange,
            onStateChange: (e) => {
              console.info(JSON.stringify(e.isVisible))
              if (!e.isVisible) {
                this.customPopupList[1] = false
              }
            }
          })

          Text('组件偏移验证气泡剪裁的builder:')
            .textStyle()
          Column() {
          }
          .pinkColumnStyle()
          .key('attrClip')
          .onClick(() => {
            this.customPopupList[2] = !this.customPopupList[2]
          })
          .bindPopup(this.customPopupList[2], {
            builder: this.componentClipPopupBuilder(),

            placement: Placement.RightTop,
            popupColor: Color.Orange,
            width: 240,
            onStateChange: (e) => {
              console.info(JSON.stringify(e.isVisible))
              if (!e.isVisible) {
                this.customPopupList[2] = false
              }
            }
          })

          Text('组件偏移验证气泡绘制情况的builder:')
            .textStyle()
          Column() {
          }
          .pinkColumnStyle()
          .key('attrPosition')
          .onClick(() => {
            this.customPopupList[3] = !this.customPopupList[3]
          })
          .bindPopup(this.customPopupList[3], {
            builder: this.componentPositionPopupBuilder(),

            placement: Placement.RightTop,
            popupColor: Color.Orange,
            width: 240,
            onStateChange: (e) => {
              console.info(JSON.stringify(e.isVisible))
              if (!e.isVisible) {
                this.customPopupList[3] = false
              }
            }
          })

          Column() {
          }
          .key('attrOffset')
          .pinkColumnStyle()
          .onClick(() => {
            this.customPopupList[4] = !this.customPopupList[4]
          })
          .bindPopup(this.customPopupList[4], {
            builder: this.componentOffsetPopupBuilder(),

            placement: Placement.RightTop,
            popupColor: Color.Orange,
            width: 240,
            onStateChange: (e) => {
              console.info(JSON.stringify(e.isVisible))
              if (!e.isVisible) {
                this.customPopupList[4] = false
              }
            }
          })

          Text('气泡内走焦的builder: ' + this.popupFocusable)
            .key('changeFocusable')
            .textStyle()
            .onClick(() => {
              this.popupFocusable = !this.popupFocusable
            })
          Column() {
          }
          .pinkColumnStyle()
          .key('eventFocusable')
          .onClick(() => {
            this.customPopupList[5] = !this.customPopupList[5]
          })
          .bindPopup(this.customPopupList[5], {
            builder: this.focusEventPopupBuilder(),

            focusable: this.popupFocusable,
            placement: Placement.Right,
            popupColor: Color.Orange,
            onStateChange: (e) => {
              console.info(JSON.stringify(e.isVisible))
              if (!e.isVisible) {
                this.customPopupList[5] = false
              }
            }
          })

          Text('气泡内设置组件Popup的builder:')
            .textStyle()
          Column() {
          }
          .pinkColumnStyle()
          .key('componentPopup')
          .onClick(() => {
            this.customPopupList[6] = !this.customPopupList[6]
          })
          .bindPopup(this.customPopupList[6], {
            builder: this.popupAdPopupBuilder(),

            placement: Placement.Right,
            popupColor: Color.Orange,
            onStateChange: (e) => {
              console.info(JSON.stringify(e.isVisible))
              if (!e.isVisible) {
                this.customPopupList[6] = false
              }
            }
          })
        }
        .alignItems(HorizontalAlign.Start)
        .width('100%').height('100%')
        .padding(10)
      }
      .width('100%').height('100%')
    }
    .title('PopupBigTest')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}