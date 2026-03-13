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
* 菜单组合测试：安全区易用性测试用例
*
 */
import { LengthMetrics } from '@kit.ArkUI';
import { MyComponent } from '../../common/MyComponent'

class SizeOpt {
  Width?: Length |  LayoutPolicy = '40%'
  Height?: Length |  LayoutPolicy = '40%'
}
class MenuParentCompAttrOptions {
  menuParentCompAlign?: Alignment = Alignment.Center
  menuParentCompSafeAreaPadding?: Padding | LengthMetrics | LocalizedPadding = LengthMetrics.vp(0)

  menuParentCompMargin?: Margin | Length | LocalizedMargin = 0
  menuParentCompPadding?: Padding |  Length |   LocalizedPadding = 0
  menuParentCompBorderWidth?: Length = 0
}
class IgnoreLayoutSafeAreaOptions {
  types?: Array <LayoutSafeAreaType> = [LayoutSafeAreaType.SYSTEM]
  edges?: Array <LayoutSafeAreaEdge> = [LayoutSafeAreaEdge.ALL]
}

@Builder function MenuBackgroundBuilder(params: SizeOpt) {
  Image($r('app.media.app_icon'))
    .width(params.Width)
    .height(params.Height)
}

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
  .backgroundColor(Color.Orange)
}

@Preview
@Component
export struct MenuSafeArea {
  scroller: Scroller = new Scroller()

  // select value/idx
  @State select_index: Array<number> = [0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,]
  @State select_value: Array<string> = ['', '', '', '', '', '', '', '', '', '', '', '',]

  // 组件布局
  @State testInfo: string = 'Menu组件background设置builder'
  // Menu组件尺寸
  @State menuSize: SizeOpt = {
    Width: '40%',
    Height: '100%'
}

  // Menu组件background
  @State backgroundOptions: BackgroundOptions = {
    align: Alignment.Center
  }

  //Menu组件父容器属性
  @State menuParentCompAttrOptions: MenuParentCompAttrOptions = {}
  //Menu组件ignoreLayoutSafeArea
  @State ignoreLayoutSafeAreaOptions: IgnoreLayoutSafeAreaOptions = {}

  //Menu组件LayoutPolicy
  @State menuLayoutSize: SizeOpt = {
    Width: undefined,
    Height: undefined
  }
  @State menuItemSize: SizeOpt = {
    Width: 200,
    Height: 200
  }

  // 半模态内容builder
  @State bindSheetShow: boolean = false
  @State bindSheetHeight: Length = '60%'
  @Builder bindSheetBuilder() {
    Column({space: 5}) {
      Column({space: 5}){
        Text('选择验证场景')
          .paramTextStyle()
        Select([
          { value: 'Menu组件background设置builder' },
          { value: 'Menu组件background设置resourceColor' },
          { value: 'Menu组件ignoreSafe' },
          { value: 'Menu组件尺寸的LayoutPolicy' },
        ])
          .selectStyle()
          .selected(this.select_index[8]!!)
          .value(this.select_value[8]!!)
          .onSelect((idx, value: string) => {
            this.select_index[8] = idx
            this.select_value[8] = value
            this.testInfo = value
          })
          .key('select_test_scene')
      }
      .columnStyle()

      Column({space: 5}){
        Text(`切换父容器Stack的对齐参数: ${this.menuParentCompAttrOptions.menuParentCompAlign}`)
          .paramTextStyle()
        Select([
          { value: 'align设置TopStart' },
          { value: 'align设置Top' },
          { value: 'align设置TopEnd' },
          { value: 'align设置Start' },
          { value: 'align设置Center' },
          { value: 'align设置End' },
          { value: 'align设置BottomStart' },
          { value: 'align设置Bottom' },
          { value: 'align设置BottomEnd' },
        ])
          .selectStyle()
          .selected(this.select_index[2]!!)
          .value(this.select_value[2]!!)
          .onSelect((idx, value: string) => {
            this.select_index[2] = idx
            this.select_value[2] = value
            switch (value) {
              case 'align设置TopStart':
                this.menuParentCompAttrOptions.menuParentCompAlign = Alignment.TopStart
                break;
              case 'align设置Top':
                this.menuParentCompAttrOptions.menuParentCompAlign = Alignment.Top
                break;
              case 'align设置TopEnd':
                this.menuParentCompAttrOptions.menuParentCompAlign = Alignment.TopEnd
                break;
              case 'align设置Start':
                this.menuParentCompAttrOptions.menuParentCompAlign = Alignment.Start
                break;
              case 'align设置Center':
                this.menuParentCompAttrOptions.menuParentCompAlign = Alignment.Center
                break;
              case 'align设置End':
                this.menuParentCompAttrOptions.menuParentCompAlign = Alignment.End
                break;
              case 'align设置BottomStart':
                this.menuParentCompAttrOptions.menuParentCompAlign = Alignment.BottomStart
                break;
              case 'align设置Bottom':
                this.menuParentCompAttrOptions.menuParentCompAlign = Alignment.Bottom
                break;
              case 'align设置BottomEnd':
                this.menuParentCompAttrOptions.menuParentCompAlign = Alignment.BottomEnd
                break;
            }
          })
          .key('select_comp_align')

        Text(`切换父容器Stack的safeAreaPadding参数: ${this.menuParentCompAttrOptions. menuParentCompSafeAreaPadding}`)
          .paramTextStyle()
        Select([
          { value: 'safePadding:0vp' },
          { value: 'safePadding:10vp' },
        ])
          .selectStyle()
          .selected(this.select_index[3]!!)
          .value(this.select_value[3]!!)
          .onSelect((idx, value: string) => {
            this.select_index[3] = idx
            this.select_value[3] = value
            switch (value) {
              case 'safePadding:0vp':
                this.menuParentCompAttrOptions. menuParentCompSafeAreaPadding = LengthMetrics.vp(0)
                break;
              case 'safePadding:10vp':
                this.menuParentCompAttrOptions. menuParentCompSafeAreaPadding = LengthMetrics.vp(10)
                break;
            }
          })
          .key('select_parent_comp_safePadding')

        Text(`切换父容器Stack的borderWidth参数: ${this.menuParentCompAttrOptions. menuParentCompBorderWidth}`)
          .paramTextStyle()
        Select([
          { value: 'borderWidth:0vp' },
          { value: 'borderWidth:2vp' },
        ])
          .selectStyle()
          .selected(this.select_index[5]!!)
          .value(this.select_value[5]!!)
          .onSelect((idx, value: string) => {
            this.select_index[5] = idx
            this.select_value[5] = value
            switch (value) {
              case 'borderWidth:0vp':
                this.menuParentCompAttrOptions. menuParentCompBorderWidth = 0
                break;
              case 'borderWidth:2vp':
                this.menuParentCompAttrOptions. menuParentCompBorderWidth = 2
                break;
            }
          })
          .key('select_parent_comp_borderWidth')

        Text(`切换父容器Stack的padding参数: ${this.menuParentCompAttrOptions. menuParentCompPadding}`)
          .paramTextStyle()
        Select([
          { value: 'padding:0vp' },
          { value: 'padding:10vp' },
        ])
          .selectStyle()
          .selected(this.select_index[6]!!)
          .value(this.select_value[6]!!)
          .onSelect((idx, value: string) => {
            this.select_index[6] = idx
            this.select_value[6] = value
            switch (value) {
              case 'padding:0vp':
                this.menuParentCompAttrOptions. menuParentCompPadding = 0
                break;
              case 'padding:10vp':
                this.menuParentCompAttrOptions. menuParentCompPadding = 10
                break;
            }
          })
          .key('select_parent_comp_padding')

        Text(`切换父容器Stack的margin参数: ${this.menuParentCompAttrOptions. menuParentCompMargin}`)
          .paramTextStyle()
        Select([
          { value: 'margin:0vp' },
          { value: 'margin:10vp' },
        ])
          .selectStyle()
          .selected(this.select_index[7]!!)
          .value(this.select_value[7]!!)
          .onSelect((idx, value: string) => {
            this.select_index[7] = idx
            this.select_value[7] = value
            switch (value) {
              case '0vp':
                this.menuParentCompAttrOptions. menuParentCompMargin = 0
                break;
              case '10vp':
                this.menuParentCompAttrOptions. menuParentCompMargin = 10
                break;
            }
          })
          .key('select_parent_comp_margin')

        Text(`切换Menu组件尺寸: width-${this.menuSize.Width}, height: ${this.menuSize.Height}`)
          .paramTextStyle()
        Row({space: 3}){
          MyComponent({title: 'W40%', func: () => {
            this.menuSize.Width = '40%'
          }})
          MyComponent({title: 'W100%', func: () => {
            this.menuSize.Width = '100%'
          }})
        }
        Row({space: 3}){
          MyComponent({title: 'matchParent', func: () => {
            this.menuSize.Height = LayoutPolicy.matchParent
          }})
          MyComponent({title: 'wrapContent', func: () => {
            this.menuSize.Height = LayoutPolicy.wrapContent
          }})
          MyComponent({title: 'idealSize', func: () => {
            this.menuSize.Height = LayoutPolicy.fixAtIdealSize
          }})
          MyComponent({title: 'H100%', func: () => {
            this.menuSize.Height = '100%'
          }})
        }
      }
      .columnStyle()

      Column({space: 5}){
        Text(`切换background.options.align参数: ${this.backgroundOptions.align}`)
          .paramTextStyle()
        Select([
          { value: 'align设置TopStart' },
          { value: 'align设置Top' },
          { value: 'align设置TopEnd' },
          { value: 'align设置Start' },
          { value: 'align设置Center' },
          { value: 'align设置End' },
          { value: 'align设置BottomStart' },
          { value: 'align设置Bottom' },
          { value: 'align设置BottomEnd' },
        ])
          .selectStyle()
          .selected(this.select_index[0]!!)
          .value(this.select_value[0]!!)
          .onSelect((idx, value: string) => {
            this.select_index[0] = idx
            this.select_value[0] = value
            switch (value) {
              case 'align设置TopStart':
                this.backgroundOptions.align = Alignment.TopStart
                break;
              case 'align设置Top':
                this.backgroundOptions.align = Alignment.Top
                break;
              case 'align设置TopEnd':
                this.backgroundOptions.align = Alignment.TopEnd
                break;
              case 'align设置Start':
                this.backgroundOptions.align = Alignment.Start
                break;
              case 'align设置Center':
                this.backgroundOptions.align = Alignment.Center
                break;
              case 'align设置End':
                this.backgroundOptions.align = Alignment.End
                break;
              case 'align设置BottomStart':
                this.backgroundOptions.align = Alignment.BottomStart
                break;
              case 'align设置Bottom':
                this.backgroundOptions.align = Alignment.Bottom
                break;
              case 'align设置BottomEnd':
                this.backgroundOptions.align = Alignment.BottomEnd
                break;
            }
          })
          .key('select_menu_background_align')

        Text(`切换background.options.ignoreEdges参数: ${this.backgroundOptions.ignoresLayoutSafeAreaEdges}`)
          .paramTextStyle()
        Select([
          { value: 'ignore设置TOP' },
          { value: 'ignore设置BOTTOM' },
          { value: 'ignore设置START' },
          { value: 'ignore设置END' },
          { value: 'ignore设置VERTICAL' },
          { value: 'ignore设置HORIZONTAL' },
          { value: 'ignore设置ALL' },
          { value: 'ignore设置TOP/BOTTOM' },
        ])
          .selectStyle()
          .selected(this.select_index[1]!!)
          .value(this.select_value[1]!!)
          .onSelect((idx, value: string) => {
            this.select_index[1] = idx
            this.select_value[1] = value
            switch (value) {
              case 'ignore设置TOP':
                this.backgroundOptions.ignoresLayoutSafeAreaEdges = [LayoutSafeAreaEdge.TOP]
                break;
              case 'ignore设置BOTTOM':
                this.backgroundOptions.ignoresLayoutSafeAreaEdges = [LayoutSafeAreaEdge.BOTTOM]
                break;
              case 'ignore设置START':
                this.backgroundOptions.ignoresLayoutSafeAreaEdges = [LayoutSafeAreaEdge.START]
                break;
              case 'ignore设置END':
                this.backgroundOptions.ignoresLayoutSafeAreaEdges = [LayoutSafeAreaEdge.END]
                break;
              case 'ignore设置VERTICAL':
                this.backgroundOptions.ignoresLayoutSafeAreaEdges = [LayoutSafeAreaEdge.VERTICAL]
                break;
              case 'ignore设置HORIZONTAL':
                this.backgroundOptions.ignoresLayoutSafeAreaEdges = [LayoutSafeAreaEdge.HORIZONTAL]
                break;
              case 'ignore设置ALL':
                this.backgroundOptions.ignoresLayoutSafeAreaEdges = [LayoutSafeAreaEdge.ALL]
                break;
              case 'ignore设置TOP/BOTTOM':
                this.backgroundOptions.ignoresLayoutSafeAreaEdges = [LayoutSafeAreaEdge.TOP, LayoutSafeAreaEdge.BOTTOM]
                break;
            }
          })
          .key('select_menu_background_ignoreEdges')
      }
      .columnStyle()

      // ignoreSafeArea属性
      Column({space: 5}){
        Text(`切换ignoreLayoutSA.edges参数: `)
          .paramTextStyle()
        Select([
          { value: 'ignore设置TOP' },
          { value: 'ignore设置BOTTOM' },
          { value: 'ignore设置START' },
          { value: 'ignore设置END' },
          { value: 'ignore设置VERTICAL' },
          { value: 'ignore设置HORIZONTAL' },
          { value: 'ignore设置ALL' },
          { value: 'ignore设置TOP/BOTTOM' },
        ])
          .selectStyle()
          .selected(this.select_index[4]!!)
          .value(this.select_value[4]!!)
          .onSelect((idx, value: string) => {
            this.select_index[4] = idx
            this.select_value[4] = value
            switch (value) {
              case 'ignore设置TOP':
                this.ignoreLayoutSafeAreaOptions.edges = [LayoutSafeAreaEdge.TOP]
                break;
              case 'ignore设置BOTTOM':
                this.ignoreLayoutSafeAreaOptions.edges = [LayoutSafeAreaEdge.BOTTOM]
                break;
              case 'ignore设置START':
                this.ignoreLayoutSafeAreaOptions.edges = [LayoutSafeAreaEdge.START]
                break;
              case 'ignore设置END':
                this.ignoreLayoutSafeAreaOptions.edges = [LayoutSafeAreaEdge.END]
                break;
              case 'ignore设置VERTICAL':
                this.ignoreLayoutSafeAreaOptions.edges = [LayoutSafeAreaEdge.VERTICAL]
                break;
              case 'ignore设置HORIZONTAL':
                this.ignoreLayoutSafeAreaOptions.edges = [LayoutSafeAreaEdge.HORIZONTAL]
                break;
              case 'ignore设置ALL':
                this.ignoreLayoutSafeAreaOptions.edges = [LayoutSafeAreaEdge.ALL]
                break;
              case 'ignore设置TOP/BOTTOM':
                this.ignoreLayoutSafeAreaOptions.edges = [LayoutSafeAreaEdge.TOP, LayoutSafeAreaEdge.BOTTOM]
                break;
            }
          })
          .key('select_ignoreEdges')
      }
      .columnStyle()

      Column({space: 5}){
        Text(`选择Menu组件LayoutPolicy的参数`)
          .paramTextStyle()
        Select([
          { value: '默认值' },
          { value: 'LayoutPolicy.matchParent' },
          { value: 'LayoutPolicy.wrapContent' },
          { value: 'LayoutPolicy.fixAtIdealSize' },
        ])
          .selectStyle()
          .selected(this.select_index[10]!!)
          .value(this.select_value[10]!!)
          .onSelect((idx, value: string) => {
            this.select_index[10] = idx
            this.select_value[10] = value
            switch (value) {
              case '默认值':
                this.menuLayoutSize = {
                  Width: undefined,
                  Height: undefined
                }
                break;
              case 'LayoutPolicy.matchParent':
                this.menuLayoutSize = {
                  Width: LayoutPolicy.matchParent,
                  Height: LayoutPolicy.matchParent
                }
                break;
              case 'LayoutPolicy.wrapContent':
                this.menuLayoutSize = {
                  Width: LayoutPolicy.wrapContent,
                  Height: LayoutPolicy.wrapContent
                }
                break;
              case 'LayoutPolicy.fixAtIdealSize':
                this.menuLayoutSize = {
                  Width: LayoutPolicy.fixAtIdealSize,
                  Height: LayoutPolicy.fixAtIdealSize
                }
                break;
            }
          })
          .key('select_layoutPolicy')

        Text(`LayoutPolicy中的MenuItem尺寸参数: ${this.menuItemSize.Width}`)
          .paramTextStyle()
        Row({space: 3}){
          MyComponent({title: `200`, func: () => {
            this.menuItemSize = {
              Width: 200,
              Height: 200
            }
          }})
          MyComponent({title: `320`, func: () => {
            this.menuItemSize = {
              Width: 320,
              Height: 320
            }
          }})
        }
      }
      .columnStyle()
    }
    .width('100%')
    .margin({top: 48})
    .padding(10)
  }

  build() {
    Stack(){
      Stack(){
        // Menu组件布局区
        if (this.testInfo === 'Menu组件background设置builder') {
          Menu(){
            MenuItem({
              content: '菜单选项'
            })
          }
          .borderWidth(1.0)
          .borderColor(Color.Blue)
          .height('100%')
          .width(this.menuSize.Width)
          .height(this.menuSize.Height)
          .background(MenuBackgroundBuilder({
            Width: '75%',
            Height: '100%',
          }), {
            align: this.backgroundOptions.align,
            ignoresLayoutSafeAreaEdges: this.backgroundOptions.ignoresLayoutSafeAreaEdges,
          })
        } else if (this.testInfo === 'Menu组件background设置resourceColor') {
          Menu(){
            MenuItem({
              content: '菜单选项'
            })
          }
          .borderWidth(1.0)
          .borderColor(Color.Blue)
          .height('100%')
          .width(this.menuSize.Width)
          .height(this.menuSize.Height)

          .background('#C7C7CC', {
            align: this.backgroundOptions.align,
            ignoresLayoutSafeAreaEdges: this.backgroundOptions.ignoresLayoutSafeAreaEdges,
          })
        } else if (this.testInfo === 'Menu组件ignoreSafe') {
          Menu(){
            MenuItem({
              content: '菜单选项'
            })
          }
          .height(this.menuSize.Height)
          .width(this.menuSize.Width)
          .backgroundColor(Color.Orange)
          .ignoreLayoutSafeArea(this.ignoreLayoutSafeAreaOptions.types,
            this.ignoreLayoutSafeAreaOptions.edges)
        } else if (this.testInfo === 'Menu组件尺寸的LayoutPolicy') {
          Column(){
            Menu(){
              MenuItem({
                content: '菜单选项'
              })
                .width(this.menuItemSize.Width)
                .height(this.menuItemSize.Height)
                .backgroundColor('#e6e84026')
            }
            .borderWidth(1.0)
            .borderColor(Color.Blue)
            .width(this.menuLayoutSize.Width)
            .height(this.menuLayoutSize.Height)
            .backgroundColor('#b3a5d61d')
          }
          .width(300)
          .height(300)
          .padding(10)
          .backgroundColor('#4d564af7')
        }
      }
      .width('100%')
      .height('100%')
      .backgroundColor('#0C000000')
      .align(this.menuParentCompAttrOptions.menuParentCompAlign)  // 子组件相对于父容器对齐方式
      .safeAreaPadding(this.menuParentCompAttrOptions.menuParentCompSafeAreaPadding)  // 设置组件级安全区
      .padding(this.menuParentCompAttrOptions.menuParentCompPadding)
      .margin(this.menuParentCompAttrOptions.menuParentCompMargin)
      .borderWidth(this.menuParentCompAttrOptions.menuParentCompBorderWidth)

      // 控制区域
      Column({space: 5}){
        Column()
        .padding(10)
        .width('80%').height('20%')
        .borderRadius(20)
        .backgroundColor('#4D0A59F7')
        .bindSheet(this.bindSheetShow!!, this.bindSheetBuilder(), {
          height: this.bindSheetHeight
        })
        .onClick(() => {
          this.bindSheetShow = true
        })
          .id('bindSheet')

        TextInput()
          .id('textInput_keyboard')
          .width('80%')
          .backgroundColor('#4df7b40a')
      }
    }
    .alignContent(Alignment.Bottom)
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
struct MenuTestLevel1_7 {
  build() {
    Column(){
      MenuSafeArea()
    }
    .width('100%')
    .height('100%')
  }
  pageTransition() {
    //进入该界面没有跳转延迟
    PageTransitionEnter({ type: RouteType.None, duration: 0 })
  }
}