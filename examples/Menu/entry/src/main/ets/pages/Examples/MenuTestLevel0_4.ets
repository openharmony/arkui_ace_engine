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

/*
* stack次级菜单避让
*
 */
import { MyComponent } from '../../common/MyComponent'
import { MenuBuilder, MenuAttrOptions } from  '../../customBuilder/MenuBuilder'

@Extend(Text)
function paramTextStyle() {
  .fontSize(11)
  .width('100%')
}
@Extend(Text) function  componentTextStyle() {
  .fontSize(15)
  .backgroundColor(Color.Orange)
  .margin(3).padding(3)
  .borderWidth(1.0)
}
@Extend(Column)
function columnStyle() {
  .backgroundColor(Color.Pink)
  .width('100%')
  .padding(5)
  .borderWidth(1.0)
}
@Extend(Select) function selectStyle() {
  .width('50%')
  .controlSize(ControlSize.SMALL)
  .selected(0)
  .backgroundColor(Color.Orange)
}

@Entry
@Component
struct MenuTestLevel0_4 {
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, 0, 0]

  //column的对齐方式
  @State columnAlignHorizontal: HorizontalAlign = HorizontalAlign.Start
  @State columnAlignFlex: FlexAlign = FlexAlign.Start

  //
  @State menuShow: boolean[] = [false, false]

  //Menu的builder option
  @State menuAttrOption: MenuAttrOptions = {
    submenuMode: 2
  }

  @Builder
  MenuBuilder() {
    MenuBuilder({menuAttrOptions: {submenuMode: this.menuAttrOption.submenuMode}})
  }

  // 菜单控制的opt
  @State contextMenuOptions: ContextMenuOptions = {
  }

  build() {
    Stack(){
      // bindMenu绑定组件区域
      Scroll(){
        Column(){
          Column(){
          }
          .backgroundColor(Color.Pink)
          .height(20).width(20)
          .bindMenu(this.menuShow[0], this.MenuBuilder(), {
            placement: this.contextMenuOptions.placement,
            offset: this.contextMenuOptions.offset,

            onDisappear: () => {
              this.menuShow[0] = false
            }
          })
        }
        .alignItems(this.columnAlignHorizontal)
        .justifyContent(this.columnAlignFlex)
        .width('100%').height('100%')
      }
      .padding({top: 0, bottom: 0, left: 16, right: 16})
      .width('100%')
      .height('100%')
      .backgroundColor(Color.Transparent)

      // 控制区域
      Scroll(this.scroller){
        Column({space: 5}) {
          Text('菜单避让场景')
            .paramTextStyle()
          Column({space: 5}){
            Text(`切换次级菜单类型`)
              .paramTextStyle()
            Row({space: 3}){
              MyComponent({title: 'SIDE', func: () => {
                this.menuAttrOption.submenuMode = 0
              }})
              MyComponent({title: 'EMBEDDED', func: () => {
                this.menuAttrOption.submenuMode = 1
              }})
              MyComponent({title: 'STACK', func: () => {
                this.menuAttrOption.submenuMode = 2
              }})
            }
            Text(`切换绑定组件的位置`)
              .paramTextStyle()
            Select([
              { value: 'TopStart' },
              { value: 'TopCenter' },
              { value: 'TopEnd' },
              { value: 'CenterStart' },
              { value: 'Center' },
              { value: 'CenterEnd' },
              { value: 'BottomStart' },
              { value: 'BottomCenter' },
              { value: 'BottomEnd' },
            ])
              .value('TopStart')
              .selected(0)
              .selectStyle()
              .onSelect((idx, value: string) => {
                switch (value) {
                  case 'TopStart':
                    this.columnAlignFlex = FlexAlign.Start
                    this.columnAlignHorizontal = HorizontalAlign.Start
                    break;
                  case 'TopCenter':
                    this.columnAlignFlex = FlexAlign.Start
                    this.columnAlignHorizontal = HorizontalAlign.Center
                    break;
                  case 'TopEnd':
                    this.columnAlignFlex = FlexAlign.Start
                    this.columnAlignHorizontal = HorizontalAlign.End
                    break;
                  case 'CenterStart':
                    this.columnAlignFlex = FlexAlign.Center
                    this.columnAlignHorizontal = HorizontalAlign.Start
                    break;
                  case 'Center':
                    this.columnAlignFlex = FlexAlign.Center
                    this.columnAlignHorizontal = HorizontalAlign.Center
                    break;
                  case 'CenterEnd':
                    this.columnAlignFlex = FlexAlign.Center
                    this.columnAlignHorizontal = HorizontalAlign.End
                    break;
                  case 'BottomStart':
                    this.columnAlignFlex = FlexAlign.End
                    this.columnAlignHorizontal = HorizontalAlign.Start
                    break;
                  case 'BottomCenter':
                    this.columnAlignFlex = FlexAlign.End
                    this.columnAlignHorizontal = HorizontalAlign.Center
                    break;
                  case 'BottomEnd':
                    this.columnAlignFlex = FlexAlign.End
                    this.columnAlignHorizontal = HorizontalAlign.End
                    break;
                }
              })
              .key('select_targetCompPos')

            Text(`菜单的对齐方式`)
              .paramTextStyle()
            Select([
              { value: '不设置placement' },
              { value: 'undefined' },
              { value: '枚举值13' },

              { value: 'Bottom' },
              { value: 'Top' },
              { value: 'Right' },
              { value: 'Left' },

              { value: 'BottomLeft' },
              { value: 'BottomRight' },
              { value: 'TopLeft' },
              { value: 'TopRight' },
              { value: 'LeftBottom' },
              { value: 'RightBottom' },
              { value: 'LeftTop' },
              { value: 'RightTop' },
            ])
              .selectStyle()
              .onSelect((idx, value: string) => {
                switch (value) {
                  case '不设置placement':
                    this.contextMenuOptions = {}
                    break;
                  case 'undefined':
                    this.contextMenuOptions.placement = undefined
                    break;
                  case '枚举值13':
                    this.contextMenuOptions.placement = 13
                    break;

                  case 'Bottom':
                    this.contextMenuOptions.placement = Placement.Bottom
                    break;
                  case 'Top':
                    this.contextMenuOptions.placement = Placement.Top
                    break;
                  case 'Right':
                    this.contextMenuOptions.placement = Placement.Right
                    break;
                  case 'Left':
                    this.contextMenuOptions.placement = Placement.Left
                    break;
                  case 'BottomLeft':
                    this.contextMenuOptions.placement = Placement.BottomLeft
                    break;
                  case 'BottomRight':
                    this.contextMenuOptions.placement = Placement.BottomRight
                    break;
                  case 'TopLeft':
                    this.contextMenuOptions.placement = Placement.TopLeft
                    break;
                  case 'TopRight':
                    this.contextMenuOptions.placement = Placement.TopRight
                    break;
                  case 'LeftBottom':
                    this.contextMenuOptions.placement = Placement.LeftBottom
                    break;
                  case 'RightBottom':
                    this.contextMenuOptions.placement = Placement.RightBottom
                    break;
                  case 'LeftTop':
                    this.contextMenuOptions.placement = Placement.LeftTop
                    break;
                  case 'RightTop':
                    this.contextMenuOptions.placement = Placement.RightTop
                    break;
                }
              })
              .key('select_menuPlacement')

            Text(`bindMenu: placement`)
              .componentTextStyle()
              .onClick( () => {
                this.menuShow[0] = true
              })

          }
          .columnStyle()
        }
        .width('100%')
      }
      .padding({top: 40, bottom: 0, left: 5, right: 5})
      .align(Alignment.TopStart)
      .width('100%').height('100%')
    }
    .alignContent(Alignment.Center)
    .width('100%')
    .height('100%')
  }

  pageTransition() {
    //进入该界面没有跳转延迟
    PageTransitionEnter({ type: RouteType.None, duration: 0 })
  }
}