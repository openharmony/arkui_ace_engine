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
* 菜单生命周期函数测试用例
*
 */

import { MyComponent } from '../../common/MyComponent'
import { MenuBuilder, MenuAttrOptions } from '../../customBuilder/MenuBuilder'


@Extend(Text) function paramTextStyle() {
  .fontSize(9)
  .width('100%')
}
@Extend(Text) function  componentTextStyle() {
  .fontSize(15)
  .backgroundColor(Color.Orange)
  .margin(3).padding(3)
  .borderWidth(1.0)
}
@Extend(Column) function columnStyle() {
  .borderWidth(1.0)
  .padding(10)
  .width('100%')
  .backgroundColor(Color.Pink)
}
@Extend(Select) function selectStyle() {
  .width('50%')
  .controlSize(ControlSize.SMALL)
  .selected(0)
  .backgroundColor(Color.Orange)
}


@Entry
@Component
struct MenuTestLevel0_22 {
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, 0, 0]
  @State show: boolean = false
  @State show_1: boolean = false
  @State menuOption: ContextMenuOptions = {

  }
  @State old_life_style_show: Array<boolean> = [false, false]
  @State new_life_style_show: Array<boolean> = [false, false]
  @State showCount: number = 1
  @State plusShow: boolean = false

  // menuBuilder
  @State menuAttrOption: MenuAttrOptions = {
    submenuMode: undefined
  }
  @Builder
  MenuBuilder() {
    MenuBuilder({menuAttrOptions: this.menuAttrOption})
  }
  @Builder
  MenuPreviewBuilder() {
      Image($r('app.media.app_icon'))
        .width(160)
        .height(120)
  }

  build() {
    Scroll(this.scroller) {
      Column({ space: 5 }) {
        Text(`验证菜单生命周期函数`)
          .paramTextStyle()
        Column({space: 5}){
          Text(`菜单的生命周期回调`)
            .paramTextStyle()

          Text(`预览图菜单：生命周期`)
            .componentTextStyle()
            .bindContextMenu(this.show!!, this.MenuBuilder(), {
              onAppear: () => {
                console.info('---LCG---    menu onAppear callback')
              },
              aboutToAppear: () => {
                console.info('---LCG---    menu aboutToAppear callback')
              },
              onDisappear: () => {
                console.info('---LCG---    menu onDisappear callback')
              },
              aboutToDisappear: () => {
                console.info('---LCG---    menu aboutToDisappear callback')
              },

              onWillAppear: () => {
                console.info('---LCG---    menu onWillAppear callback')
              },
              onDidAppear: () => {
                console.info('---LCG---    menu onDidAppear callback')
              },
              onWillDisappear: () => {
                console.info('---LCG---    menu onWillDisappear callback')
              },
              onDidDisappear: () => {
                console.info('---LCG---    menu onDidDisappear callback')
              },
              preview: this.MenuPreviewBuilder(),
              transition: TransitionEffect.OPACITY.animation({ duration: 3000, curve: Curve.Ease }).combine(
                TransitionEffect.rotate({ x: 1, angle: 30 })),
            })
            .onClick((e: ClickEvent) => {
              if(!this.show) {
                this.show = true
              }
            })
        }
        .columnStyle()
        Column({space: 5}){
          Text(`菜单接续弹出的旧的生命周期回调`)
            .paramTextStyle()
          Column({space: 5}){
            Text(`菜单_1:旧生命周期回调`)
              .componentTextStyle()
              .bindContextMenu(this.old_life_style_show[0], this.MenuBuilder(), {
                backgroundColor: Color.Orange,
                backgroundBlurStyle: BlurStyle.COMPONENT_ULTRA_THICK,
                onAppear: () => {
                  console.info('---LCG---    menu 1 onAppear callback')
                },
                aboutToAppear: () => {
                  console.info('---LCG---    menu 1 aboutToAppear callback')
                },
                onDisappear: () => {
                  console.info('---LCG---    menu 1 onDisappear callback')
                  this.old_life_style_show[0] = false
                },
                aboutToDisappear: () => {
                  console.info('---LCG---    menu 1 aboutToDisappear callback')
                  this.old_life_style_show[0] = false
                },
              })
              .onClick(() => {
                this.old_life_style_show[0] = true
              })
            Text(`菜单_2:旧生命周期回调`)
              .componentTextStyle()
              .bindContextMenu(this.old_life_style_show[1], this.MenuBuilder(), {
                onAppear: () => {
                  console.info('---LCG---    menu 2 onAppear callback')
                },
                aboutToAppear: () => {
                  console.info('---LCG---    menu 2 aboutToAppear callback')
                },
                onDisappear: () => {
                  console.info('---LCG---    menu 2 onDisappear callback')
                  this.old_life_style_show[1] = false
                },
                aboutToDisappear: () => {
                  console.info('---LCG---    menu 2 aboutToDisappear callback')
                  this.old_life_style_show[1] = false
                },
              })
              .onClick(() => {
                this.old_life_style_show[1] = true
              })
            Text(`菜单_先1后2:旧生命周期回调`)
              .componentTextStyle()
              .onClick(() => {
                this.old_life_style_show[0] = true
                setTimeout( () => {
                  this.old_life_style_show[1] = true
                }, 100)
              })
          }
          Text(`菜单接续弹出的新的生命周期回调`)
            .paramTextStyle()
          Column({space: 5}){
            Text(`菜单_1:新生命周期回调`)
              .componentTextStyle()
              .bindContextMenu(this.new_life_style_show[0], this.MenuBuilder(), {
                backgroundColor: Color.Orange,
                backgroundBlurStyle: BlurStyle.COMPONENT_ULTRA_THICK,
                onWillAppear: () => {
                  console.info('---LCG---    menu 1 onWillAppear callback')
                },
                onDidAppear: () => {
                  console.info('---LCG---    menu 1 onDidAppear callback')
                },
                onWillDisappear: () => {
                  console.info('---LCG---    menu 1 onWillDisappear callback')
                  this.new_life_style_show[0] = false
                },
                onDidDisappear: () => {
                  console.info('---LCG---    menu 1 onDidDisappear callback')
                  this.new_life_style_show[0] = false
                },
              })
              .onClick(() => {
                this.new_life_style_show[0] = true
              })
            Text(`菜单_2:新生命周期回调`)
              .componentTextStyle()
              .bindContextMenu(this.new_life_style_show[1], this.MenuBuilder(), {
                onWillAppear: () => {
                  console.info('---LCG---    menu 2 onWillAppear callback')
                },
                onDidAppear: () => {
                  console.info('---LCG---    menu 2 onDidAppear callback')
                },
                onWillDisappear: () => {
                  console.info('---LCG---    menu 2 onWillDisappear callback')
                  this.new_life_style_show[1] = false
                },
                onDidDisappear: () => {
                  console.info('---LCG---    menu 2 onDidDisappear callback')
                  this.new_life_style_show[1] = false
                },
              })
              .onClick(() => {
                this.new_life_style_show[1] = true
              })
            Text(`菜单_先1后2:新生命周期回调`)
              .componentTextStyle()
              .onClick(() => {
                this.new_life_style_show[0] = true
                setTimeout( () => {
                  this.new_life_style_show[1] = true
                })
              }, 100)
          }

          Text(`畅联应用+弹出菜单`)
            .paramTextStyle()
          if ( this.showCount > 0) {
            Text(`畅联+的菜单`)
              .componentTextStyle()
              .bindContextMenu(this.plusShow, this.MenuBuilder(), {
                backgroundColor: Color.Blue,
                backgroundBlurStyle: BlurStyle.COMPONENT_ULTRA_THICK,
                onWillDisappear: () => {
                  console.info('---LCG---    menu + onWillDisappear callback')
                  this.plusShow = false
                },
                onDidDisappear: () => {
                  console.info('---LCG---    menu + onDidDisappear callback')
                  this.plusShow = false
                },
              })
              .onClick(() => {
                this.showCount = 0
                this.plusShow = true
              })
          } else {
            Text(`畅联++的菜单`)
              .componentTextStyle()
              .bindContextMenu(this.plusShow, this.MenuBuilder(), {
                backgroundColor: Color.Blue,
                backgroundBlurStyle: BlurStyle.COMPONENT_ULTRA_THICK,
                onWillDisappear: () => {
                  console.info('---LCG---    menu ++ onWillDisappear callback')
                  this.plusShow = false
                },
                onDidDisappear: () => {
                  console.info('---LCG---    menu ++ onDidDisappear callback')
                  this.plusShow = false
                },
              })
              .onClick(() => {
                this.plusShow = true
                this.showCount = 1
              })
          }

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
