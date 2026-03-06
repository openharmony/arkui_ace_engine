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
* 菜单锚定组件布局的测试用例anchorPosition
*
 */

import { MyComponent } from '../../common/MyComponent'
import { SimpleMenuBuilder, MenuAttrOptions } from  '../../customBuilder/MenuBuilder'

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
  .borderWidth(1.0)
  .padding(5)
}
@Extend(Select) function selectStyle() {
  .width('50%')
  .controlSize(ControlSize.SMALL)
  .selected(0)
  .backgroundColor(Color.Orange)
}

@Preview
@Component
export struct MenuAnchorPosition {
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, 0, 0]
  @State menuOption: ContextMenuOptions = {
  }

  //column的对齐方式
  @State columnAlignHorizontal: HorizontalAlign = HorizontalAlign.Start
  @State columnAlignFlex: FlexAlign = FlexAlign.Start

  // menu Show state
  @State menuShow: boolean[] = [false, false]

  //Menu的builder option
  @State menuAttrOption: MenuAttrOptions = {
    submenuMode: 0
  }

  @Builder
  MenuBuilder() {
    SimpleMenuBuilder({menuAttrOptions: {submenuMode: this.menuAttrOption.submenuMode}})
  }

  // 菜单的预览图
  @Builder
  MenuPreviewBuilder() {
    Image($r('app.media.app_icon'))
      .width(120)
      .height(60)
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
          .backgroundColor('#ff848f6b')
          .height(20).width(20)
          .bindMenu(this.menuShow[0]!!, this.MenuBuilder(), this.menuOption)
        }
        .alignItems(this.columnAlignHorizontal)
        .justifyContent(this.columnAlignFlex)
        .width('100%').height('100%')
      }
      .padding({top: 10, bottom: 10, left: 16, right: 16})
      .width('100%')
      .height('100%')
      .backgroundColor(Color.Transparent)

      // 控制区域
      Scroll(this.scroller){
        Column({space: 5}) {
          Text('验证菜单的锚定偏移')
            .paramTextStyle()
          Column({space: 5}){
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

            Text(`切换次级菜单类型: ${this.menuAttrOption.submenuMode}`)
              .paramTextStyle()
            Row({space: 3}){
              MyComponent({title: 'SIDE', func: () => {
                this.menuAttrOption.submenuMode = SubMenuExpandingMode.SIDE_EXPAND
              }})
              MyComponent({title: 'EMBEDDED', func: () => {
                this.menuAttrOption.submenuMode = SubMenuExpandingMode.EMBEDDED_EXPAND
              }})
              MyComponent({title: 'STACK', func: () => {
                this.menuAttrOption.submenuMode = SubMenuExpandingMode.STACK_EXPAND
              }})
            }
          }
          .columnStyle()

          Column({space: 5}){
            Text(`设置锚定偏移`)
              .paramTextStyle()
            Select([
              { value:'undefined' },
              { value:'{x: 60, y: 0}' },
              { value:'{x: 0, y: 60}' },
              { value:'{x: -60, y: 0}' },
              { value:'{x: 0, y: -60}' },
              { value:'{x: 240, y: 0}' },
              { value:'{x: 0, y: 240}' },
              { value:'{x: -60, y: -60}' },
            ])
              .selectStyle()
              .onSelect((idx, value: string) => {
                switch (value) {
                  case 'undefined':
                    this.menuOption.anchorPosition = undefined
                    break;
                  case '{x: 60, y: 0}':
                    this.menuOption.anchorPosition = {x: 60, y: 0}
                    break;
                  case '{x: 0, y: 60}':
                    this.menuOption.anchorPosition = {x: 0, y: 60}
                    break;
                  case '{x: -60, y: 0}':
                    this.menuOption.anchorPosition = {x: -60, y: 0}
                    break;
                  case '{x: 0, y: -60}':
                    this.menuOption.anchorPosition = {x: 0, y: -60}
                    break;
                  case '{x: 240, y: 0}':
                    this.menuOption.anchorPosition = {x: 240, y: 0}
                    break;
                  case '{x: 0, y: 240}':
                    this.menuOption.anchorPosition = {x: 0, y: 240}
                    break;
                  case '{x: -60, y: -60}':
                    this.menuOption.anchorPosition = {x: -60, y: -60}
                    break;
                }
              })
              .key('select_menuAnchorPos')

            Text('菜单锚定偏移')
              .componentTextStyle()
              .onClick( () => {
                this.menuShow[0] = true
              })
            Text('预览图菜单锚定偏移')
              .componentTextStyle()
              .bindContextMenu(this.menuShow[1], this.MenuBuilder(), {
                anchorPosition: this.menuOption.anchorPosition,
                preview: this.MenuPreviewBuilder(),
                onDisappear: () => {
                  this.menuShow[1] = false
                }
              })
              .onClick( () => {
                this.menuShow[1] = true
              })
          }
          .columnStyle()

          Column({space: 5}){
            Text(`菜单anchorPos的组合测试`)
              .paramTextStyle()

            Text(`菜单锚定和对齐`)
              .componentTextStyle()
              .bindMenu(this.MenuBuilder(), {
                placement: Placement.Bottom,
                anchorPosition: {x: 0, y: 120}
              })

            Text(`菜单锚定和偏移`)
              .componentTextStyle()
              .bindMenu(this.MenuBuilder(), {
                offset: {x: 0, y: -120},

                anchorPosition: {x: 0, y: 120}
              })

            Text(`长按菜单双负值锚定`)
              .componentTextStyle()
              .bindContextMenu(this.MenuBuilder(), ResponseType.LongPress, {
                anchorPosition: {x: -120, y: -120}
              })
          }
          .columnStyle()
        }
        .width('100%')
      }
      .padding(24)
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

@Entry
@Component
struct MenuTestLevel0_23 {
  build() {
    Column(){
      MenuAnchorPosition()
    }
  }
  pageTransition() {
    //进入该界面没有跳转延迟
    PageTransitionEnter({ type: RouteType.None, duration: 0 })
  }
}