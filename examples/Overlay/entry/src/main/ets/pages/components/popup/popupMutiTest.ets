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
export function PopupMutiBuilder(name: string, param: Object) {
  PopupMutiExample()
}

class BindSheetStatement {
  public isShow?: boolean = false
}

@Extend(Column)
function columnStyle() {
  .backgroundColor(Color.Pink)
  .width(30)
  .height(30)
  .backgroundColor(Color.Pink)
  .borderWidth(1.0)
}

@Extend(Text)
function textStyle() {
  .fontSize(9)
  .fontColor(0x000000)
  .width('100%')
}

@CustomDialog
struct SubCustomDialogExample {
  subDialogController?: CustomDialogController

  build() {
    Column() {
      Text('我是第二个弹窗')
        .fontSize(30)
        .height(100)
      Button('点我关闭第二个弹窗')
        .onClick(() => {
          if (this.subDialogController != undefined) {
            this.subDialogController.close()
          }
        })
        .margin(20)
    }
  }
}

@CustomDialog
struct CustomDialogExample {
  @Link textValue: string
  @Link inputValue: string
  subDialogController: CustomDialogController | null = new CustomDialogController({
    builder: SubCustomDialogExample(),
    alignment: DialogAlignment.Bottom,
    offset: { dx: 0, dy: -40 }
  })
  controller?: CustomDialogController
  cancel: () => void = () => {
  }
  confirm: () => void = () => {
  }

   build() {
     Column() {
       Text('Change text')
         .fontSize(20)
         .margin({
           top: 10,
           bottom: 10
         })
       TextInput({
         placeholder: '',
         text: this.textValue
       })
         .height(60)
         .width('90%')
         .onChange((value: string) => {
           this.textValue = value
         })
       Text('whether to change a text?')
         .fontSize(16)
         .margin({ bottom: 10 })
       Button('点我打开第二个弹窗')
         .onClick(() => {
           if(this.subDialogController != undefined) {
             this.subDialogController.open()
           }
         })
         .margin(20)
       Flex({ justifyContent: FlexAlign.SpaceAround }){
         Button('cancel')
           .onClick(() => {
             if (this.controller != undefined) {
               this.controller.close()
               this.cancel()
             }
           })
           .backgroundColor(0xffffff)
           .fontColor(Color.Black)
         Button('confirm')
           .onClick(() => {
             if (this.controller != undefined) {
               this.inputValue = this.textValue
               this.controller.close()
               this.confirm()
             }
           })
           .backgroundColor(0xffffff)
           .fontColor(Color.Red)
       }
       .margin({ bottom: 10 })
     }
     .borderRadius(10)
   }
}

@Entry
@Component
struct PopupMutiExample {
  pathStack: NavPathStack = new NavPathStack()
  scroller: Scroller = new Scroller()
  @State columnJustifyContent: FlexAlign = FlexAlign.Start
  @State customPopupList: boolean[] = [false, false, false, false, false, false, false]
  @State showInSubwindow: boolean = false
  //自定义弹窗
  @State textValue: string = ''
  @State inputValue: string = '自定义弹窗'
  //气泡
  @State handlePopup: boolean = false
  //菜单
  @State listData: number[] = [0, 0, 0]
  @State menuShow: boolean = false
  //半模态
  @State isShow: boolean[] = [false, false, false]
  @State sheetDetents: [(SheetSize | Length), (SheetSize | Length)?, (SheetSize | Length)?] =
    [240, 480, 600]
  @State sheetDragBar: boolean = true

  onCancel() {
    console.info('Callback when the first button is clicked')
  }

  onAccept() {
    console.info('Callback when the second button is clicked')
  }

  exitApp() {
    console.info('Click the callback in the blank area')
  }

  dialogController: CustomDialogController | null = new CustomDialogController({
    builder: CustomDialogExample({
      cancel: this.onCancel,
      confirm: this.onAccept,
      textValue: $textValue,
      inputValue: $inputValue
    }),
    cancel: this.exitApp,
    autoCancel: true,
    alignment: DialogAlignment.Bottom,
    offset: {
      dx: 0,
      dy: -20
    },
    gridCount: 4,
    customStyle: false,
    cornerRadius: 10,
  })
  @Builder
  menuBuilder() {
    Flex({ direction: FlexDirection.Column, justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
      ForEach(this.listData, (item: number, index) => {
        Column() {
          Row() {
            Image($r('app.media.app_icon'))
              .width(20)
              .height(20)
              .margin({ right: 5 })
            Text(`Menu${index as number + 1}`)
              .fontSize(20)
          }
          .width('100%')
          .height(30)
          .justifyContent(FlexAlign.Center)
          .align(Alignment.Center)
          .onClick(() => {
            console.log(`Menu${index as number + 1} clicked!`)
          })
          if (index != this.listData.length - 1) {
            Divider()
              .height(10)
              .width('80%')
              .color('#ccc')
          }
        }
        .padding(5)
        .height(40)
      })
    }
    .width('100%')
  }

  @Builder
  sheetBuilder($$: BindSheetStatement) {
    Column({ space: 10 }) {
      Button('change detents')
        .width('60%')
        .fontSize(11)
        .onClick(() => {
          this.sheetDetents = [400, 300, 700]
        })
      Button('change dragBar')
        .width('60%')
        .fontSize(11)
        .onClick(() => {
          $$.isShow = !$$.isShow
        })
      Button('close modal')
        .width('60%')
        .fontSize(11)
        .onClick(() => {
          $$.isShow = false
        })
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }

  // popup构造器定义弹框内容
  @Builder
  toastComponentsInPopupBuilder() {
    Column({ space: 10 }) {
      Button('警告弹窗')
        .width('70%')
        .fontSize(11)
        .onClick(() => {
          AlertDialog.show({
            title: 'title',
            subtitle: 'subtitle',
            message: 'text',
            buttonDirection: DialogButtonDirection.HORIZONTAL,
            buttons: [
              {
                value: '按钮',
                action: () => {
                  console.info('Callback when button1 is clicked')
                }
              },
              {
                value: '按钮',
                action: () => {
                  console.info('Callback when button2 is clicked')
                }
              },
              {
                value: '按钮',
                enabled: true,
                defaultFocus: true,
                style: DialogButtonStyle.HIGHLIGHT,
                action: () => {
                  console.info('Callback when button3 is clicked')
                }
              },
            ],
            cancel: () => {
              console.info('Closed callbacks')
            }
          })
        })

      Button('自定义弹窗')
        .width('70%')
        .fontSize(11)
        .onClick(() => {
          this.dialogController?.open()
        })

      Button('Popup')
        .width('70%')
        .fontSize(11)
        .onClick(() => {
          this.handlePopup = !this.handlePopup
        })
        .bindPopup(this.handlePopup, {
          message: 'this is a popup',
          width: 200,
          showInSubWindow: false,
          mask: { color: '#9900ffff' },
          primaryButton: {
            value: 'confirm',
            action: () => {
              this.handlePopup = !this.handlePopup
              console.info('confirm Button click')
            }
          },
          // 第二个按钮
          secondaryButton: {
            value: 'cancel',
            action: () => {
              this.handlePopup = !this.handlePopup
              console.info('cancel Button click')
            }
          },
          onStateChange: (e) => {
            console.info(JSON.stringify(e.isVisible))
            if (!e.isVisible) {
              this.handlePopup = false
            }
          }
        })
      Button('bindMenu')
        .width('70%')
        .fontSize(11)
        .bindMenu(this.menuBuilder(), {
          placement: Placement.Bottom
        })
      Button('bindContextMenu')
        .width('70%')
        .fontSize(11)
        .bindContextMenu(this.menuBuilder(), ResponseType.LongPress, {
          placement: Placement.Bottom
        })

      Button('bindSheet')
        .width('70%')
        .fontSize(11)
        .onClick(() => {
          this.isShow[0] = true
        })
        .bindSheet(this.isShow[0], this.sheetBuilder({ isShow: this.isShow[0] }), {
          detents: this.sheetDetents,
          maskColor: '#9980ff00',
          backgroundColor: Color.Pink,
          dragBar: this.sheetDragBar,
          showClose: true,
          onDisappear: () => {
            this.isShow[0] = false
          }
        })
    }
    .width('75%')
    .padding(10)
  }

  build() {
    NavDestination() {
      Scroll(this.scroller) {
        Column({ space: 5 }) {
          Text('设置弹窗类的组件Popup')
            .textStyle()
          Row({ space: 5 }) {
            MyComponent({
              title: 'Start',
              func: () => {
                this.columnJustifyContent = FlexAlign.Start
              }
            })
            MyComponent({
              title: 'Center',
              func: () => {
                this.columnJustifyContent = FlexAlign.Center
              }
            })
            MyComponent({
              title: 'End',
              func: () => {
                this.columnJustifyContent = FlexAlign.End
              }
            })
          }
          Column({ space: 20 }) {
            Column(){
            }
            .columnStyle()
            .key('toastInPopup')
            .onClick(() => {
              this.customPopupList[0] = !this.customPopupList[0]
            })
            .bindPopup(this.customPopupList[0], {
              builder: this.toastComponentsInPopupBuilder,
              showInSubWindow: this.showInSubwindow,
              mask: true,
              placement: Placement.RightTop,
              popupColor: Color.Orange,
              onStateChange: (e) => {
                console.info(JSON.stringify(e.isVisible))
                if (!e.isVisible) {
                  this.customPopupList[0] = false
                }
              }
            })
            Column(){
            }
            .columnStyle()
            .key('toastXInSameMask')
            .onClick(() => {
              setTimeout(() => {
                this.customPopupList[1] = !this.customPopupList[1]
              }, 100)

              setTimeout(() => {
                if (this.dialogController != undefined) {
                  this.dialogController.open()
                }
              }, 200)

              setTimeout(() => {
                AlertDialog.show({
                  title: 'title',
                  subtitle: 'subtitle',
                  message: 'text',
                  autoCancel: true,
                  gridCount: 3,
                  confirm: {
                    value: 'confirm',
                    action: () => {
                      console.info('confirm callbacks')
                    }
                  },
                  cancel: () => {
                    console.info('Closed callbacks')
                  }
                })
              }, 300)

              setTimeout(() => {
                this.isShow[1] = true
              }, 400)

              setTimeout(() => {
                this.menuShow = true
              }, 500)
            })
            .bindPopup(this.customPopupList[1], {
              message: 'this is a popup',
              width: 200,
              showInSubWindow: false,
              mask: { color: '#9900ffff' },
              primaryButton: {
                value: 'confirm',
                action: () => {
                  this.handlePopup = !this.handlePopup
                  console.info('confirm Button click')
                }
              },
              // 第二个按钮
              secondaryButton: {
                value: 'cancel',
                action: () => {
                  this.handlePopup = !this.handlePopup
                  console.info('cancel Button click')
                }
              },
              onStateChange: (e) => {
                console.info(JSON.stringify(e.isVisible))
                if (!e.isVisible) {
                  this.customPopupList[1] = false
                }
              }
            })
            .bindMenu(this.menuShow!!, this.menuBuilder(), {
              placement: Placement.Bottom
            })
            .bindSheet(this.isShow[1], this.sheetBuilder({ isShow: this.isShow[1] }), {
              detents: this.sheetDetents,
              maskColor: '#9980ff00',
              backgroundColor: Color.Pink,
              dragBar: this.sheetDragBar,
              showClose: true,
              onDisappear: () => {
                this.isShow[1] = false
              }
            })
          }
          .justifyContent(this.columnJustifyContent)
          .alignItems(HorizontalAlign.Start)
          .width('100%')
          .height('90%')
          .borderWidth(1.0)
        }
        .alignItems(HorizontalAlign.Start)
        .width('100%')
        .height('100%')
        .padding(10)
      }
      .width('100%')
      .height('100%')
    }
    .title('Popup')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}