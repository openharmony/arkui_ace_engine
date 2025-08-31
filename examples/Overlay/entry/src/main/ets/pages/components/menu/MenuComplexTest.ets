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
import { LengthMetrics } from '@kit.ArkUI';
import { MyComponent } from '../popup/MyComponenet'

@Builder
export function MenuComplexBuilder(name: string, param: Object) {
  MenuComplex()
}

class SizeOpt {
  public width?: Length | LayoutPolicy = '40%'
  public height?: Length | LayoutPolicy = '40%'
}
class MenuParentCompAttrOptions {
  public menuParentCompAlign?: Alignment = Alignment.Center
  public menuParentCompSafeAreaPadding?: Padding | LengthMetrics | LocalizedPadding = LengthMetrics.vp(0)

  public menuParentCompMargin?: Margin | Length | LocalizedMargin = 0
  public menuParentCompPadding?: Padding | Length | LocalizedPadding = 0
  public menuParentCompBorderWidth?: Length = 0
}
class IgnoreLayoutSafeAreaOptions {
  public types?: Array<LayoutSafeAreaType> = [LayoutSafeAreaType.SYSTEM]
  public edges?: Array<LayoutSafeAreaEdge> = [LayoutSafeAreaEdge.ALL]
}

@Builder function menuBackgroundBuilder(params: SizeOpt) {
  Image($r('app.media.app_icon'))
    .width(params.width)
    .height(params.height)
}

@Extend(Text)
function paramTextStyle() {
  .fontSize(11)
  .width('100%')
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
export struct MenuItemSafeArea {
  scroller: Scroller = new Scroller()

  // select value/idx
  @State selectIndex: Array<number> = [0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,]
  @State selectValue: Array<string> = ['', '', '', '', '', '', '', '', '', '', '', '',]

  // 组件布局
  @State testInfo: string = 'MenuItem组件background设置builder'
  // MenuItem组件尺寸
  @State menuSize: SizeOpt = {
    width: '40%',
    height: '100%'
  }

  // MenuItem组件background
  @State backgroundOptions: BackgroundOptions = {
    align: Alignment.Center
  }

  //MenuItem组件父容器属性
  @State menuParentCompAttrOptions: MenuParentCompAttrOptions = {}
  //MenuItem组件ignoreLayoutSafeArea
  @State ignoreLayoutSafeAreaOptions: IgnoreLayoutSafeAreaOptions = {}

  //MenuItem组件LayoutPolicy
  @State menuLayoutSize: SizeOpt = {
    width: undefined,
    height: undefined
  }
  @State menuItemSize: SizeOpt = {
    width: 200,
    height: 200
  }
  @State menuItemContentValue: number = 2

  // 半模态内容builder
  @State bindSheetShow: boolean = false
  @State bindSheetHeight: Length = '60%'
  @Builder bindSheetBuilder() {
    Column({space: 5}) {
      Column({space: 5}){
        Text('选择验证场景')
          .paramTextStyle()
        Select([
          { value: 'MenuItem组件background设置builder' },
          { value: 'MenuItem组件background设置resourceColor' },
          { value: 'MenuItem组件ignoreSafe' },
          { value: 'MenuItem组件尺寸的LayoutPolicy' },
        ])
          .selectStyle()
          .selected(this.selectIndex[8]!!)
          .value(this.selectValue[8]!!)
          .onSelect((idx, value: string) => {
            this.selectIndex[8] = idx
            this.selectValue[8] = value
            this.testInfo = value
          })
          .key('select_test_scene')
      }
      .columnStyle()

      Column({space: 5}){
        Text(`切换父容器Menu的对齐参数: ${this.menuParentCompAttrOptions.menuParentCompAlign}`)
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
          .selected(this.selectIndex[2]!!)
          .value(this.selectValue[2]!!)
          .onSelect((idx, value: string) => {
            this.selectIndex[2] = idx
            this.selectValue[2] = value
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

        Text(`切换父容器Menu的safeAreaPadding参数: ${this.menuParentCompAttrOptions.menuParentCompSafeAreaPadding}`)
          .paramTextStyle()
        Select([
          { value: '0vp' },
          { value: '10vp' },
        ])
          .selectStyle()
          .selected(this.selectIndex[3]!!)
          .value(this.selectValue[3]!!)
          .onSelect((idx, value: string) => {
            this.selectIndex[3] = idx
            this.selectValue[3] = value
            switch (value) {
              case 'safePadding:0vp':
                this.menuParentCompAttrOptions.menuParentCompSafeAreaPadding = LengthMetrics.vp(0)
                break;
              case 'safePadding:10vp':
                this.menuParentCompAttrOptions.menuParentCompSafeAreaPadding = LengthMetrics.vp(10)
                break;
            }
          })
          .key('select_comp_safePadding')

        Text(`切换父容器Menu的borderWidth参数: ${this.menuParentCompAttrOptions.menuParentCompBorderWidth}`)
          .paramTextStyle()
        Select([
          { value: 'borderWidth:0vp' },
          { value: 'borderWidth:2vp' },
        ])
          .selectStyle()
          .selected(this.selectIndex[5]!!)
          .value(this.selectValue[5]!!)
          .onSelect((idx, value: string) => {
            this.selectIndex[5] = idx
            this.selectValue[5] = value
            switch (value) {
              case 'borderWidth:0vp':
                this.menuParentCompAttrOptions.menuParentCompBorderWidth = 0
                break;
              case 'borderWidth:2vp':
                this.menuParentCompAttrOptions.menuParentCompBorderWidth = 2
                break;
            }
          })
          .key('select_comp_borderWidth')

        Text(`切换父容器Menu的padding参数: ${this.menuParentCompAttrOptions.menuParentCompPadding}`)
          .paramTextStyle()
        Select([
          { value: 'padding:0vp' },
          { value: 'padding:10vp' },
        ])
          .selectStyle()
          .selected(this.selectIndex[6]!!)
          .value(this.selectValue[6]!!)
          .onSelect((idx, value: string) => {
            this.selectIndex[6] = idx
            this.selectValue[6] = value
            switch (value) {
              case 'padding:0vp':
                this.menuParentCompAttrOptions.menuParentCompPadding = 0
                break;
              case 'padding:10vp':
                this.menuParentCompAttrOptions.menuParentCompPadding = 10
                break;
            }
          })
          .key('select_comp_padding')

        Text(`切换父容器Menu的margin参数: ${this.menuParentCompAttrOptions.menuParentCompMargin}`)
          .paramTextStyle()
        Select([
          { value: 'margin:0vp' },
          { value: 'margin:10vp' },
        ])
          .selectStyle()
          .selected(this.selectIndex[7]!!)
          .value(this.selectValue[7]!!)
          .onSelect((idx, value: string) => {
            this.selectIndex[7] = idx
            this.selectValue[7] = value
            switch (value) {
              case 'margin:0vp':
                this.menuParentCompAttrOptions.menuParentCompMargin = 0
                break;
              case 'margin:10vp':
                this.menuParentCompAttrOptions.menuParentCompMargin = 10
                break;
            }
          })
          .key('select_comp_margin')

        Text(`切换MenuItem组件尺寸: width-${this.menuSize.width}, height: ${this.menuSize.height}`)
          .paramTextStyle()
        Row({space: 3}){
          MyComponent({title: 'W40%', func: () => {
            this.menuSize.width = '40%'
          }})
          MyComponent({title: 'W100%', func: () => {
            this.menuSize.width = '100%'
          }})
        }
        Row({space: 3}){
          MyComponent({title: 'matchParent', func: () => {
            this.menuSize.height = LayoutPolicy.matchParent
          }})
          MyComponent({title: 'wrapContent', func: () => {
            this.menuSize.height = LayoutPolicy.wrapContent
          }})
          MyComponent({title: 'idealSize', func: () => {
            this.menuSize.height = LayoutPolicy.fixAtIdealSize
          }})
          MyComponent({title: 'H100%', func: () => {
            this.menuSize.height = '100%'
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
          .selected(this.selectIndex[0]!!)
          .value(this.selectValue[0]!!)
          .onSelect((idx, value: string) => {
            this.selectIndex[0] = idx
            this.selectValue[0] = value
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
          .key('select_menuItem_background_align')

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
          .selected(this.selectIndex[1]!!)
          .value(this.selectValue[1]!!)
          .onSelect((idx, value: string) => {
            this.selectIndex[1] = idx
            this.selectValue[1] = value
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
          .key('select_menuItem_background_ignoreEdges')
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
          .selected(this.selectIndex[4]!!)
          .value(this.selectValue[4]!!)
          .onSelect((idx, value: string) => {
            this.selectIndex[4] = idx
            this.selectValue[4] = value
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
        Text(`选择MenuItem组件LayoutPolicy的参数`)
          .paramTextStyle()
        Select([
          { value: '默认值' },
          { value: 'LayoutPolicy.matchParent' },
          { value: 'LayoutPolicy.wrapContent' },
          { value: 'LayoutPolicy.fixAtIdealSize' },
        ])
          .selectStyle()
          .selected(this.selectIndex[10]!!)
          .value(this.selectValue[10]!!)
          .onSelect((idx, value: string) => {
            this.selectIndex[10] = idx
            this.selectValue[10] = value
            switch (value) {
              case '默认值':
                this.menuLayoutSize = {
                  width: undefined,
                  height: undefined
                }
                break;
              case 'LayoutPolicy.matchParent':
                this.menuLayoutSize = {
                  width: LayoutPolicy.matchParent,
                  height: LayoutPolicy.matchParent
                }
                break;
              case 'LayoutPolicy.wrapContent':
                this.menuLayoutSize = {
                  width: LayoutPolicy.wrapContent,
                  height: LayoutPolicy.wrapContent
                }
                break;
              case 'LayoutPolicy.fixAtIdealSize':
                this.menuLayoutSize = {
                  width: LayoutPolicy.fixAtIdealSize,
                  height: LayoutPolicy.fixAtIdealSize
                }
                break;
            }
          })
          .key('select_layoutPolicy')

        Text(`LayoutPolicy中的MenuItem内容重复次数: ${this.menuItemContentValue}`)
          .paramTextStyle()
        Row({space: 3}){
          MyComponent({title: '2', func: () => {
            this.menuItemContentValue = 2
          }})
          MyComponent({title: '10', func: () => {
            this.menuItemContentValue = 10
          }})
          MyComponent({title: '20', func: () => {
            this.menuItemContentValue = 20
          }})
          MyComponent({title: '100', func: () => {
            this.menuItemContentValue = 100
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
        // MenuItem组件布局区
        if (this.testInfo === 'MenuItem组件background设置builder') {
          MenuItem({
            content: '菜单选项'
          })
            .borderWidth(1.0)
            .borderColor(Color.Blue)
            .height('100%')
            .width(this.menuSize.width)
            .height(this.menuSize.height)

            .background(menuBackgroundBuilder({
              width: '75%',
              height: '100%',
            }), {
              align: this.backgroundOptions.align,
              ignoresLayoutSafeAreaEdges: this.backgroundOptions.ignoresLayoutSafeAreaEdges,
            })
        } else if (this.testInfo === 'MenuItem组件background设置resourceColor') {
          MenuItem({
            content: '菜单选项'
          })
            .borderWidth(1.0)
            .borderColor(Color.Blue)
            .height('100%')
            .width(this.menuSize.width)
            .height(this.menuSize.height)

            .background('#C7C7CC', {
              align: this.backgroundOptions.align,
              ignoresLayoutSafeAreaEdges: this.backgroundOptions.ignoresLayoutSafeAreaEdges,
            })
        } else if (this.testInfo === 'MenuItem组件ignoreSafe') {
          MenuItem({
            content: '菜单选项'
          })
            .height(this.menuSize.height)
            .width(this.menuSize.width)
            .backgroundColor(Color.Orange)
            .ignoreLayoutSafeArea(this.ignoreLayoutSafeAreaOptions.types,
              this.ignoreLayoutSafeAreaOptions.edges)
        } else if (this.testInfo === 'MenuItem组件尺寸的LayoutPolicy') {
          Menu(){
            MenuItem({
              content: '菜单选项 '.repeat(this.menuItemContentValue)
            })
              .borderWidth(1.0)
              .borderColor(Color.Blue)
              .width(this.menuLayoutSize.width)
              .height(this.menuLayoutSize.height)
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
struct MenuComplex {
  pathStack: NavPathStack = new NavPathStack()
  build() {
    NavDestination() {
      Column(){
        MenuItemSafeArea()
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
  pageTransition() {
    //进入该界面没有跳转延迟
    PageTransitionEnter({ type: RouteType.None, duration: 0 })
  }
}