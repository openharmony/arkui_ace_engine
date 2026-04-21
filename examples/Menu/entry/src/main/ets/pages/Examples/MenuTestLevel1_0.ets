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
* 大尺寸的菜单验证PC设备高度和宽度限制 | 避让dock和导航栏
* builder内父容器设置offset和position的菜单绘制情况（对比气泡设置position不绘制的规范）
* builder内设置走焦事件
* bindContextMenu设置长按弹出菜单和长按手势事件的区分：duration的区分
* bindMenu和bindContextMenu分别设置router跳转：区分子窗口和浮层绘制的菜单
* Menu做父容器和Menu在其他父容器内的绘制效果：验证默认UX效果
 */
import { MyComponent } from '../../common/MyComponent'
import router from '@ohos.router';
import { BusinessError } from '@ohos.base';

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

@Entry
@Component
struct MenuTestLevel1_0 {
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, 0, 0]
  @State showInSubWindow: boolean = false
  //走焦builder的状态变量
  @State menuFocusable: boolean = false
  @State oneButtonColor: string = '#FFC0CB'
  @State twoButtonColor: string = '#87CEFA'
  @State threeButtonColor: string = '#90EE90'
  //长按手势的计数和长按间隔
  @State count: number = 0
  @State duration: number = 500

  //builder设置较大尺寸验证菜单的尺寸限制和避让dock和导航栏
  @Builder
  ExtremeSizeMenuBuilder() {
    Menu() {
      MenuItem({ content: 'sizeMenu', labelInfo: '1237' })
    }
    .backgroundColor(Color.Orange)
    .borderWidth(1.0)
    .height(800).width(400)
  }

  //builder内设置父容器offset验证菜单绘制效果
  @Builder
  ComponentOffsetMenuBuilder() {
    Column() {
      MenuItem({ content: 'offsetMenu', labelInfo: '右下offset' })
    }
    .offset({ x: 20, y: 20 })
    .backgroundColor(Color.Orange)
    .borderWidth(1.0)
  }

  //builder内设置父容器position验证菜单绘制效果
  @Builder
  ComponentPositionMenuBuilder() {
    Column() {
      MenuItem({ content: 'positionMenu', labelInfo: '右下offset' })
    }
    .position({ x: 10, y: 10 })
    .backgroundColor(Color.Green)
    .borderWidth(1.0)
  }

  //builder内设置走焦和输入法
  @Builder
  FocusEventMenuBuilder() {
    Column({ space: 20 }) {
      // 通过外接键盘的上下键可以让焦点在三个按钮间移动，按钮获焦时颜色变化，失焦时变回原背景色
      Button('First Button')
        .backgroundColor(this.oneButtonColor)
        .width(200)
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
        .fontColor(Color.Black)
        .focusable(true)
        .onFocus(() => {
          this.twoButtonColor = '#FF0000'
        })
        .onBlur(() => {
          this.twoButtonColor = '#87CEFA'
        })
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '走焦测试',
        labelInfo: `${this.menuFocusable}`,
        endIcon: $r('app.media.app_icon')
      })
        .backgroundColor(this.threeButtonColor)
        .width(200)
        .focusable(true)
        .onFocus(() => {
          this.threeButtonColor = '#FF0000'
          this.menuFocusable = true
        })
        .onBlur(() => {
          this.threeButtonColor = '#90EE90'
          this.menuFocusable = false
        })
    }.width(240).margin(10)
  }

  //normal builder验证bindContextMenu的弹出菜单和长按手势
  @Builder
  ContextMenuBuilder() {
    Menu() {
      MenuItem({ content: '测试绑定组件长按手势和长按菜单' })
    }
  }

  //builder中设置router跳转验证bindMenu和bindContextMenu的subWindow属性
  @Builder
  RouterMenuBuilder() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '跳转', labelInfo: 'Router Go' })
        .onClick(() => {
          console.info(`---LCG---  Succeeded in clicking the 'Router' button.`)
          // 跳转到Router页
          router.pushUrl({ url: 'pages/MenuNav' }).then(() => {
            console.info('---LCG---  Succeeded in jumping to the MenuNav page.')
          }).catch((err: BusinessError) => {
            console.error(`---LCG---  Failed to jump to the MenuNav page.Code is ${err.code}, message is ${err.message}`)
          })
        })
    }
  }

  build() {
    Scroll(this.scroller) {
      Column({ space: 5 }) {
        Text(`验证Menu设置较大尺寸：较大的高度和宽度菜单 `)
          .paramTextStyle()
        Column({ space: 3 }) {
          Text('extremeSize')
            .backgroundColor(Color.Orange)
            .bindMenu(this.ExtremeSizeMenuBuilder(), {
              placement: Placement.Bottom,
              showInSubWindow: this.showInSubWindow
            })
        }
        .columnStyle()

        Text(`验证菜单builder内父容器组件设置offset的绘制 `)
          .paramTextStyle()
        Column({ space: 3 }) {
          Text('componentOffset')
            .backgroundColor(Color.Orange)
            .bindMenu(this.ComponentOffsetMenuBuilder(), {
              placement: Placement.Bottom,
              showInSubWindow: this.showInSubWindow
            })
        }
        .columnStyle()

        Text(`验证菜单builder内父容器组件设置position的绘制 `)
          .paramTextStyle()
        Column({ space: 3 }) {
          Text('componentPosition')
            .backgroundColor(Color.Orange)
            .bindMenu(this.ComponentPositionMenuBuilder(), {
              placement: Placement.Bottom,
              showInSubWindow: this.showInSubWindow
            })
        }
        .columnStyle()

        Text(`验证菜单builder验证走焦 `)
          .paramTextStyle()
        Column({ space: 3 }) {
          Text('focusableMenu')
            .backgroundColor(Color.Orange)
            .bindMenu(this.FocusEventMenuBuilder(), {
              placement: Placement.Bottom,
              showInSubWindow: this.showInSubWindow
            })
        }
        .columnStyle()

        Text(`验证父组件长按手势和长按换出菜单: duration: ${this.duration}, count: ${this.count}`)
          .paramTextStyle()
        Column({ space: 3 }) {
          Row({ space: 2 }) {
            MyComponent({
              title: 'duration++', func: () => {
                if (this.duration >= 1100) {
                  this.duration = 1100
                } else {
                  this.duration += 150
                }
              }
            })
            MyComponent({
              title: 'duration--', func: () => {
                if (this.duration <= 350) {
                  this.duration = 350
                } else {
                  this.duration -= 150
                }
              }
            })
          }

          Text('componentLongPress')
            .backgroundColor(Color.Orange)
            .bindContextMenu(this.ContextMenuBuilder(), ResponseType.LongPress, {
              placement: Placement.Bottom,
            })
            .gesture(
              LongPressGesture({
                repeat: true,
                duration: this.duration
              })// 由于repeat设置为true，长按动作存在时会连续触发，触发间隔为duration（默认值500ms）
                .onAction((event: GestureEvent) => {
                  if (event.repeat) {
                    this.count++
                  }
                })// 长按动作一结束触发
                .onActionEnd(() => {
                  this.count = 0
                })
            )
        }
        .columnStyle()

        Text(`验证bindMenu和bindContextMenu跳转功能 `)
          .onClick(() => {
            this.showInSubWindow = !this.showInSubWindow
          })
          .paramTextStyle()
        Column({ space: 3 }) {
          Text('bindMenu: Router')
            .key('bindMenuRouter')
            .backgroundColor(Color.Orange)
            .bindMenu(this.RouterMenuBuilder(), {
              placement: Placement.Bottom,
              showInSubWindow: this.showInSubWindow
            })
          Text('bindContextMenu: Router')
            .key(`bindContextMenu: Router`)
            .backgroundColor(Color.Orange)
            .bindContextMenu(this.RouterMenuBuilder(), ResponseType.LongPress, {
              placement: Placement.Bottom,
              preview: MenuPreviewMode.IMAGE
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
