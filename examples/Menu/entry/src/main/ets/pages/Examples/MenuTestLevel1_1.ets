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
/*
* 验证Menu的customBuilder:
* 菜单设置List滚动和拖拽
* 验证菜单设置组合手势：建议手工用例测试
* 菜单设置文本输入验证输入法避让
* 组件绑定bindMenu和bindContextMenu的效果: 点击弹出菜单只有bindMenu
* 组件绑定binMenu和bindPopup: 气泡在菜单的上层
* 验证菜单中显示气泡和弹窗中显示菜单
 */
import { MyComponent } from '../../common/MyComponent'
import { ExtraParamsOption } from '../../model/Model'

@Extend(Text)
function paramTextStyle() {
  .fontSize(9)
  .width('100%')
}

@Extend(Column)
function columnStyle() {
  .borderWidth(1.0)
  .padding(10)
  .width('100%')
  .backgroundColor(Color.Pink)
}

@Extend(Row)
function rowStyle() {
  .width(200)
  .height(80)
  .padding(5)
  .backgroundColor(0xAFEEEE)
}

// Builder: 自定义弹窗中弹出菜单
@CustomDialog
struct MenuInCustomDialogBuilder {
  controller?: CustomDialogController
  @Builder
  SubMenu() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
    }
  }

  @Builder
  MyMenu() {
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项' }).enabled(false)
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '二级菜单',
        endIcon: $r('app.media.app_icon'),
        builder: this.SubMenu()
      })
      MenuItemGroup({ header: '小标题' }) {
        MenuItem({ content: '菜单选项' }).selectIcon(true)
          .onChange((selected) => {
            console.info('menuItem select' + selected);
          })
        MenuItem({
          content: '菜单选项',
          builder: this.SubMenu()
        })
      }
    }
  }

  build() {
    Column() {
      Button('showMenu')
        .bindContextMenu(this.MyMenu, ResponseType.LongPress)
    }
    .borderRadius(10)
    .width('100%')
    .padding(10)
  }
}

@Entry
@Component
struct MenuTestLevel1_1 {
  scroller: Scroller = new Scroller()
  @State showInSubWindow: boolean = false
  //List滚动和拖拽的变量
  @State numbers?: string[] = ['one', 'two', 'three', 'four', 'five', 'six']
  @State text: string = ''
  @State bool: boolean = true
  @State eventType: string = ''
  @State appleVisible: Visibility = Visibility.Visible
  @State orangeVisible: Visibility = Visibility.Visible
  @State bananaVisible: Visibility = Visibility.Visible
  private dragList: string[] = ['apple', 'orange', 'banana']
  @State fruitVisible: Visibility[] = [Visibility.Visible, Visibility.Visible, Visibility.Visible]
  @State idx: number = 0
  @State index: number = 0
  private scroller1: Scroller = new Scroller()
  //组合手势事件的变量
  @State info: string = 'Info: 初始值'
  @State offsetX: number = 0
  @State offsetY: number = 0
  @State positionX: number = 0
  @State positionY: number = 0
  @State scaleValue: number = 1
  @State pinchValue: number = 1
  @State angle: number = 0
  @State rotateValue: number = 0
  @State rotateAngle: number = 0
  @State isShowSubWindow: boolean = false
  private panOption: PanGestureOptions = new PanGestureOptions({
    direction: PanDirection.All,
    distance: 1
  })
  //gap高度的变量
  @State gapHeight: number = 50
  //设置气泡的变量
  @State handlePopup: boolean[] = [false, false, false]
  @State popupShowInSubWindow: boolean = false

  // 自定义拖拽过程中显示的内容
  @Builder
  pixelMapBuilder() {
    Column() {
      Text(this.text).width('50%').height(60).fontSize(16).borderRadius(10).textAlign(TextAlign.Center)
      .backgroundColor(Color.Yellow)
    }
  }

  // Builder设置List和组件拖拽
  @Builder
  ListAndDragInMenuBuilder() {
    Column() {
      Text('There are three Text elements here').fontSize(12).width('90%').textAlign(TextAlign.Start).margin(5)
      Row({ space: 15 }) {
        ForEach(this.dragList, (item: string, index) => {
          Text(item)
            .padding(5)
            .borderWidth(1.0)
            .backgroundColor(0xAFEEEE)
            .visibility(this.fruitVisible[index])
            .onDragStart(() => {
              this.bool = true
              this.text = item
              this.fruitVisible[index] = Visibility.None
              return this.pixelMapBuilder
            })
            .onTouch((event: TouchEvent) => {
              if (event.type === TouchType.Down) {
                this.eventType = 'Down'
                this.idx = index
              }
              if (event.type === TouchType.Up) {
                this.eventType = 'Up'
                if (this.bool) {
                  this.fruitVisible[index] = Visibility.Visible
                }
              }
            })
        })
      }.padding({ top: 10, bottom: 10 })

      Text('This is a List element').fontSize(12).width('90%').textAlign(TextAlign.Start).margin(5)
      List({ space: 20, scroller: this.scroller1 }) {
        ForEach(this.numbers, (item: string) => {
          ListItem() {
            Text(item)
              .width('100%')
              .height(80)
              .fontSize(16)
              .borderRadius(10)
              .textAlign(TextAlign.Center)
              .backgroundColor(0xAFEEEE)
          }
        }, (item: string) => item)
      }
      .height('65%')
      .width('90%')
      .padding(15)
      .divider({
        strokeWidth: 2,
        color: 0xFFFFFF,
        startMargin: 20,
        endMargin: 20
      })
      .onDragEnter((event: DragEvent, extraParams: string) => {
        console.log('List onDragEnter, ' + extraParams + 'X:' + event.getWindowX() + 'Y:' + event.getWindowY())
      })
      .onDragMove((event: DragEvent, extraParams: string) => {
        console.log('List onDragMove, ' + extraParams + 'X:' + event.getWindowX() + 'Y:' + event.getWindowY())
      })
      .onDragLeave((event: DragEvent, extraParams: string) => {
        console.log('List onDragLeave, ' + extraParams + 'X:' + event.getWindowX() + 'Y:' + event.getWindowY())
      })
      .onDrop((event: DragEvent, extraParams: string) => {
        let jsonString: ExtraParamsOption = JSON.parse(extraParams);
        if (this.bool) {
          this.numbers!.splice(jsonString.insertIndex, 0, this.text)
          this.bool = false
        }
        this.fruitVisible[this.idx] = Visibility.None
      })
      .scrollBar(BarState.Off)
      .onAppear(() => {
        this.scroller1.scrollEdge(Edge.Bottom)
      })
    }
    .width('75%').height(300).margin({ top: 20 })
  }

  // Builder中设置手势交互
  @Builder
  GestureInMenuBuilder() {
    Column({ space: 10 }) {
      Row({ space: 2 }) {
        Text('双击/长按手势').fontSize(10)
      }
      .rowStyle()
      .gesture(
        TapGesture({ count: 2 })
          .onAction((event: GestureEvent) => {
            this.info = `Info: Doubleclick`
          })
      )
      .gesture(
        LongPressGesture({ repeat: true })// 由于repeat设置为true，长按动作存在时会连续触发，触发间隔为duration（默认值500ms）
          .onAction((event: GestureEvent) => {
            this.info = `Info: LongPressGesture`
          })
      )
      Row({ space: 2 }) {
        Text('平移手势').fontSize(10)
      }
      .rowStyle()
      .translate({ x: this.offsetX, y: this.offsetY, z: 0 })
      .gesture(
        PanGesture(this.panOption)
          .onActionStart((event: GestureEvent) => {
            this.info = `Info: Pan start`
          })
          .onActionUpdate((event: GestureEvent) => {
            console.info(`Info: x=${event.offsetX},y=${event.offsetY}`)
            this.offsetX = this.positionX + event.offsetX
            this.offsetY = this.positionY + event.offsetY
            this.info = `Info: pan offsetX=${this.offsetX} \n offsetY=${this.offsetY}`
          })
          .onActionEnd(() => {
            this.positionX = this.offsetX
            this.positionY = this.offsetY
            this.info = `Info: Pan end`
          })
      )
      Row({ space: 2 }) {
        Text('缩放手势').fontSize(10)
      }
      .rowStyle()
      .scale({ x: this.scaleValue, y: this.scaleValue, z: 1 })
      .gesture(
        PinchGesture({ fingers: 2 })
          .onActionStart((event: GestureEvent) => {
            this.info = `Info: Pinch start`
          })
          .onActionUpdate((event: GestureEvent) => {
            this.scaleValue = this.pinchValue * event.scale
            this.info = `Info: Pinch scaleValue=${this.scaleValue}`
          })
          .onActionEnd(() => {
            this.pinchValue = this.scaleValue
            this.info = `Info: Pinch end`
          })
      )
      Row({ space: 2 }) {
        Text('旋转手势').fontSize(10)
      }
      .rowStyle()
      .rotate({ angle: this.angle })
      .gesture(
        RotationGesture()
          .onActionStart((event: GestureEvent) => {
            this.info = `Info: Rotation start`
          })
          .onActionUpdate((event: GestureEvent) => {
            this.angle = this.rotateValue + event.angle
            this.info = `Info: Rotation angle=${this.angle}`
          })
          .onActionEnd(() => {
            this.rotateValue = this.angle
            this.info = `Info: Rotation end`
          })
      )
      Row({ space: 2 }) {
        Text('轻扫手势').fontSize(10)
      }
      .rowStyle()
      .rotate({ angle: this.rotateAngle })
      .gesture(
        SwipeGesture({ direction: SwipeDirection.All })
          .onAction((event: GestureEvent) => {
            this.rotateAngle = event.angle
            this.info = `Info: Swipe`
          })
      )
      Row({ space: 2 }) {
        Text('拖拽手势').fontSize(10)
      }
      .rowStyle()
      .onDragStart(() => {
        this.info = `Info: DragStart`
      })
      Text(this.info).fontSize(10).width(200)
    }
    .width('70%').padding(10)
  }

  // Builder设置文本输入
  @Builder
  TextInMenuBuilder() {
    Column({ space: 5 }) {
      TextInput({ placeholder: '普通TextInput' }).enterKeyType(EnterKeyType.Send)
      TextArea({ placeholder: '普通TextArea' }).borderWidth(1)
    }.width('50%').padding(10)
  }

  // 标准bindMenu的Builder
  @Builder
  MenuAndContextMenuBuilder() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl V' })
    }
  }

  // Menu的Builder中弹出气泡
  @Builder
  PopupInMenuBuilder() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl C' })
        .onHover(() => {
          this.handlePopup[1] = true
        })
        .bindPopup(this.handlePopup[1], {
          message: 'PopupTips: Ctrl C',
          showInSubWindow: this.popupShowInSubWindow,
          primaryButton: {
            value: 'Confirm',
            action: () => {
              console.info('Confirm Button Click')
              this.handlePopup[1] = false
            }
          },
          onStateChange: (e) => {
            console.info(JSON.stringify(e.isVisible))
            if (!e.isVisible) {
              this.handlePopup[1] = false
            }
          }
        })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl V' })
    }
  }

  // CustomDialog的控制器
  @State dialogShowInSubWindow: boolean = false
  dialogController: CustomDialogController = new CustomDialogController({
    builder: MenuInCustomDialogBuilder(),
    autoCancel: true,
    alignment: DialogAlignment.Default,
    gridCount: 4,
    backgroundColor: 0xd9ffffff,
    cornerRadius: 10,
    showInSubWindow: this.dialogShowInSubWindow
  })

  build() {
    Scroll(this.scroller) {
      Column({ space: 5 }) {
        Text(`验证Menu中设置List和事件拖拽 `)
          .paramTextStyle()
        Column({ space: 3 }) {
          Text('ListAndDrag')
            .backgroundColor(Color.Orange)
            .bindMenu(this.ListAndDragInMenuBuilder(), {
              placement: Placement.Bottom,
              showInSubWindow: this.showInSubWindow
            })
        }
        .columnStyle()

        Text(`验证Menu中设置组合手势事件 `)
          .paramTextStyle()
        Column({ space: 3 }) {
          Text('GestureX')
            .backgroundColor(Color.Orange)
            .bindMenu(this.GestureInMenuBuilder(), {
              placement: Placement.Bottom,
              showInSubWindow: this.showInSubWindow
            })
        }
        .columnStyle()

        Text(`验证Menu中设置文本输入进行输入法避让 `)
          .paramTextStyle()
        Column({ space: 5 }) {
          Text('调整Popup避让输入法的位置')
            .fontSize(9)
            .fontColor(0x000000)
          Row({ space: 10 }) {
            MyComponent({
              title: 'height+50', func: () => {
                this.gapHeight += 50
              }
            })
            MyComponent({
              title: 'height-50', func: () => {
                this.gapHeight -= 50

                if (this.gapHeight <= 0) {
                  this.gapHeight = 50
                }
              }
            })
          }
        }
        .height(this.gapHeight).width('100%').borderWidth(1.0).backgroundColor(Color.Pink)

        Column({ space: 3 }) {
          Text('TextInput').backgroundColor(Color.Orange)
            .bindMenu(this.TextInMenuBuilder(), {
              placement: Placement.Bottom,
              showInSubWindow: this.showInSubWindow
            })
        }
        .columnStyle()

        Text(`验证组件同时设置bindMenu,bindContextMenu和bindPopup `)
          .paramTextStyle()
        Column({ space: 3 }) {
          Text('PopupAndMenu')
            .backgroundColor(Color.Orange)//设置bindPopup
            .bindPopup(this.handlePopup[0], {
              message: 'This is a popup with PopupOptions',
              showInSubWindow: false,
              primaryButton: {
                value: 'confirm',
                action: () => {
                  console.info('confirm Button click')
                  this.handlePopup[0] = false
                }
              },
              // 第二个按钮
              secondaryButton: {
                value: 'cancel',
                action: () => {
                  console.info('cancel Button click')
                  this.handlePopup[0] = false
                }
              },
              onStateChange: (e) => {
                console.info(JSON.stringify(e.isVisible))
                if (!e.isVisible) {
                  this.handlePopup[0] = false
                }
              }
            })
            .onClick(() => {
              this.handlePopup[0] = true
            })//设置bindMenu和bindContextMenu
            .bindMenu(this.MenuAndContextMenuBuilder(), {
              placement: Placement.Bottom,
              showInSubWindow: this.showInSubWindow
            })
            .bindContextMenu(this.MenuAndContextMenuBuilder(), ResponseType.LongPress, {
              placement: Placement.Top
            })
        }
        .columnStyle()

        Text(`验证菜单(子窗-${this.showInSubWindow})是否显示气泡(子窗-${this.popupShowInSubWindow})： `)
          .paramTextStyle()
        Column({ space: 3 }) {
          Row({ space: 3 }) {
            MyComponent({
              title: 'P: True', func: () => {
                this.popupShowInSubWindow = true
              }
            })
            MyComponent({
              title: 'P: False', func: () => {
                this.popupShowInSubWindow = false
              }
            })
          }
          Text('PopupInMenu').backgroundColor(Color.Orange)
            .bindMenu(this.PopupInMenuBuilder(), {
              placement: Placement.Bottom,
              showInSubWindow: this.showInSubWindow,
            })
        }
        .columnStyle()

        Text(`验证自定义弹窗(子窗-${this.dialogShowInSubWindow})能否弹出菜单(子窗-${this.showInSubWindow})： `)
          .paramTextStyle()
        Column({ space: 3 }) {
          Row({ space: 3 }) {
            MyComponent({
              title: 'D: True', func: () => {
                this.dialogShowInSubWindow = true
              }
            })
            MyComponent({
              title: 'D: False', func: () => {
                this.dialogShowInSubWindow = false
              }
            })
          }
          Text('MenuInCustomDialog')
            .backgroundColor(Color.Orange)
            .onClick(() => {
              this.dialogController.open()
            })
        }
        .columnStyle()
      }
      .width('100%')
    }
    .padding(12)
    .align(Alignment.TopStart)
    .width('100%').height('100%')
  }

  pageTransition() {
    //进入该界面没有跳转延迟
    PageTransitionEnter({ type: RouteType.None, duration: 0 })
  }
}