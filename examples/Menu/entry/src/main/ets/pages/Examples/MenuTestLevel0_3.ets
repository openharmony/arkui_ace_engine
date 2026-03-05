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
 * 1. 验证bindMenu和bindContextMenu的弹出位置：placement和offset | 避让
 * 2. 对齐方式+偏移遮盖父组件，会进行对侧避让，避让后偏移不生效
 */
 
import { common } from '@kit.AbilityKit'
import { deviceInfo } from '@kit.BasicServicesKit';
import { MenuBuilder, MenuAttrOptions, SimpleMenuBuilder } from  '../../customBuilder/MenuBuilder'

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


@Entry
@Component
struct MenuTestLevel0_3 {
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, 0, 0]

  @State bindMenuEdgeSafePadding: Padding = {left: 16, right: 16, top: 0, bottom: 0}
  @State bindContextMenuEdgeSafePadding: Padding = {left: 16, right: 16, top: 16, bottom: 4}

  //column的对齐方式
  @State columnAlignHorizontal: HorizontalAlign = HorizontalAlign.Start
  @State columnAlignFlex: FlexAlign = FlexAlign.Start

  // menuShow
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

  // 显示的场景/ 组件
  @State sceneInfo: string = ''
  @State targetInfo: string = 'bindMenu菜单'



  // 监听设备横竖屏, 适配避让距离: safeEdge padding
  private context = this.getUIContext().getHostContext() as common.UIAbilityContext;
  private windowClass = (this.context as common.UIAbilityContext).windowStage.getMainWindowSync();
  aboutToAppear(): void {
    try {
      let deviceTypeInfo: string = deviceInfo.deviceType
      // ...
      this.windowClass.on('windowSizeChange', (size) => {
        let viewWidth = this.getUIContext().px2vp(size.width)
        let viewHeight = this.getUIContext().px2vp(size.height)
        // 根据不同设备类型和横竖屏状,设置避让边距
        if (deviceTypeInfo === 'phone') {
          this.bindMenuEdgeSafePadding = {top: 0, bottom: 0, left: 16, right: 16}
          // 手机
          if(viewWidth <= viewHeight) {
            this.bindContextMenuEdgeSafePadding = {top: 16, bottom: 4, left: 16, right: 16}
          } else {
            this.bindContextMenuEdgeSafePadding = {top: 24, bottom: 24, left: 16, right: 16}
          }
        } else if (deviceTypeInfo === '2in1') {
          this.bindMenuEdgeSafePadding = {top: 0, bottom: 0, left: 8, right: 8}
          this.bindContextMenuEdgeSafePadding = {top: 24, bottom: 24, left: 8, right: 8}
        }

      })

    } catch (err) {
      let error = err as BusinessError;
      console.error(`aboutToAppear err, error code: ${error.code}, error message: ${error.message}`);
    }
  }


  build() {
    Stack(){
      // bindMenu绑定组件区域
      if (this.targetInfo === 'bindMenu菜单') {
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
          .borderWidth(1.0)
          .borderColor(Color.Blue)
          .alignItems(this.columnAlignHorizontal)
          .justifyContent(this.columnAlignFlex)
          .width('100%').height('100%')
        }
        .padding(this.bindMenuEdgeSafePadding)
        .width('100%')
        .height('100%')
        .backgroundColor(Color.Transparent)
      }
      else if (this.targetInfo === '预览图菜单') {
        // 预览图菜单绑定组件区域
        Scroll(){
          Column(){
            Column(){
            }
            .backgroundColor(Color.Orange)
            .height(16).width(16)
            .bindContextMenu(this.menuShow[1], this.MenuBuilder(), {
              placement: this.contextMenuOptions.placement,
              offset: this.contextMenuOptions.offset,

              preview: this.MenuPreviewBuilder(),
              onDisappear: () => {
                this.menuShow[1] = false
              }
            })
          }
          .borderWidth(1.0)
          .borderColor(Color.Orange)
          .alignItems(this.columnAlignHorizontal)
          .justifyContent(this.columnAlignFlex)
          .width('100%').height('100%')
        }
        .padding(this.bindContextMenuEdgeSafePadding)
        .width('100%')
        .height('100%')
        .backgroundColor(Color.Transparent)
      }

      // 控制区域
      Scroll(this.scroller){
        Column({space: 5}) {
          Text('验证菜单布局边距属性')
            .paramTextStyle()
          Column({space: 5}){
            Text('选择菜单类型')
              .paramTextStyle()
            Select([
              {value: 'bindMenu菜单'},
              {value: '预览图菜单'}
            ])
              .id('select_scene')
              .value(this.targetInfo)
              .selectStyle()
              .onSelect((index: number, value:string) => {
                  this.targetInfo = value
              })
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

            Text('选择次级菜单类型')
              .paramTextStyle()
            Select([
              {value: 'SIDE'},
              {value: 'EMBEDDED'},
              {value: 'STACK'},
            ])
              .selectStyle()
              .onSelect((idx, value: string) => {
                switch (value) {
                  case 'SIDE':
                    this.menuAttrOption.submenuMode = SubMenuExpandingMode.SIDE_EXPAND
                    break;
                  case 'EMBEDDED':
                    this.menuAttrOption.submenuMode = SubMenuExpandingMode.EMBEDDED_EXPAND
                    break;
                  case 'STACK':
                    this.menuAttrOption.submenuMode = SubMenuExpandingMode.STACK_EXPAND
                    break;
                }
              })
              .key('select_sub_menu_mode')
          }
          .columnStyle()

          Column({space: 5}){
            Text(`选择菜单的placment`)
              .paramTextStyle()
            Select([
              { value: 'opt为{}' },
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
              .value('Opt为{}')
              .onSelect((idx, value: string) => {
                switch (value) {
                  case 'opt为{}':
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

            Text(`选择菜单的offset`)
              .paramTextStyle()
            Select([
              { value: 'opt为{}' },
              { value: '{x: 0, y: 0}'},
              { value: '{x: 30, y: 0}'},
              { value: '{x: 0, y: 30}'},
              { value: '{x: -30, y: 0}'},
              { value: '{x: 0, y: -30}'},
              { value: 'undefined'},
            ])
              .selectStyle()
              .value('Opt为{}')
              .onSelect((idx, value: string) => {
                switch (value) {
                  case 'opt为{}':
                    this.contextMenuOptions = {}
                    break;
                  case '{x: 0, y: 0}':
                    this.contextMenuOptions.offset = {x: 0, y: 0}
                    break;
                  // case '{x: 30, y: 30}':
                  //   this.contextMenuOptions.offset = {x: 30, y: 30}
                  //   break;
                  // case '{x: -30, y: -30}':
                  //   this.contextMenuOptions.offset = {x: -30, y: -30}
                  //   break;
                  // case '{x: -30, y: 30}':
                  //   this.contextMenuOptions.offset = {x: -30, y: 30}
                  //   break;
                  // case '{x: 30, y: -30}':
                  //   this.contextMenuOptions.offset = {x: 30, y: -30}
                  //   break;
                  case '{x: 0, y: 30}':
                    this.contextMenuOptions.offset = {x: 0, y: 30}
                    break;
                  case '{x: 30, y: 0}':
                    this.contextMenuOptions.offset = {x: 30, y: 0}
                    break;
                  case '{x: -30, y: 0}':
                    this.contextMenuOptions.offset = {x: -30, y: 0}
                    break;
                  case '{x: 0, y: -30}':
                    this.contextMenuOptions.offset = {x: 0, y: -30}
                    break;
                  case 'undefined':
                    this.contextMenuOptions.offset = undefined
                    break;
                }
              })
              .key('select_menuOffset')
          if (this.targetInfo === 'bindMenu菜单') {
            Text(`bindMenu位置`)
              .componentTextStyle()
              .onClick( () => {
                this.menuShow[0] = true
              })
          } else if (this.targetInfo === '预览图菜单') {
            Text(`contextMenu位置`)
              .componentTextStyle()
              .onClick( () => {
                this.menuShow[1] = true
              })
          }

          }
          .columnStyle()

          Text(`预览图菜单不设置placement横竖屏对齐方式差异`)
            .paramTextStyle()
          Column({space: 5}){
            Text(`previewMenu: unset_placement`)
              .componentTextStyle()
              .bindContextMenu(this.MenuBuilder(), ResponseType.LongPress, {
                preview: this.MenuPreviewBuilder()
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

  aboutToDisappear(): void {
    this.windowClass.off('windowSizeChange')
  }

  pageTransition() {
    //进入该界面没有跳转延迟
    PageTransitionEnter({ type: RouteType.None, duration: 0 })
  }
}