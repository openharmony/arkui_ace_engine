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
* 0123商分 暂不支持菜单isShow!!
* 验证菜单设置layoutRegionMargin的布局绘制效果
 */

import { MyComponent } from  '../../common/MyComponent'
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
  .backgroundColor(Color.Orange)
}

@Entry
@Component
struct MenuTestLevel0_6 {
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, 0]

  //column的对齐方式
  @State columnAlignHorizontal: HorizontalAlign = HorizontalAlign.Start
  @State columnAlignFlex: FlexAlign = FlexAlign.Start

  //Menu组件的属性
  @State menuAttrOption: MenuAttrOptions = {
  }
  //菜单和次级菜单
  @Builder
  MenuBuilder() {
    MenuBuilder({menuAttrOptions: {submenuMode: this.menuAttrOption.submenuMode}})
  }

  //PreviewBuilder
  @Builder
  MenuPreviewBuilder() {
    Image($r('app.media.app_icon'))
      .width(240)
      .height(180)
  }

  //
  @State menuShow: boolean = false
  //菜单regionMargin组合测试的其他菜单属性
  @State contextMenuOptions: ContextMenuOptions = {
  }

  // base margin
  @State baseMarginList: Margin[] = [
  //1
    {top: 16, bottom: 4, left: 16, right: 16},
    //2
    {top: 16, bottom: 4, left: 16, right: 16},
    //3
    {top: 16, bottom: 4, left: 16, right: 16},
    //4
    {
      top: '20vp',
      bottom: '20px',
      left: '20lpx',
      right: '20fp'
    },
    //5
    {top: 16, bottom: 4, left: 16, right: 16},
    //6
    {
      top: 120, bottom: 120, left: 60, right: 60
    },
    //7
    {top: 16, bottom: 4, left: 16, right: 16},
    //8
    {
      top: '10%', bottom: '10%', left: '10%', right: '10%'
    },
    //9
    {
      top: 20, bottom: 20, left: '10%', right: '10%'
    },
    //10
    {top: 16, bottom: 4, left: 16, right: 16},
    //11
    {top: 16, bottom: 4, left: 16, right: 16},
  ]

  // layoutMargin param list
  @State layoutRegionMarginTestList: ContextMenuOptions[] = [
    //1
    {},
    //2
    {
      layoutRegionMargin: undefined
    },
    //3
    {
      layoutRegionMargin: {top: 16, bottom: 4, left: 16, right: 16},  //UX默认值, 竖屏
    },
    //4 str不同单位
    {
      layoutRegionMargin: {
        top: '20vp',
        bottom: '20px',
        left: '20lpx',
        right: '20fp'
      }
    },
    //5 设置负值
    {
      layoutRegionMargin: {
        top: -10,
        bottom: 30, left: 30, right: 30
      }
    },
    //6 设置较大值(未超过各方向最大布局尺寸)
    {
      layoutRegionMargin: {
        top: 120, bottom: 120, left: 60, right: 60
      }
    },
    //7 设置超大值(超过各方向最大布局尺寸)
    {
      layoutRegionMargin: {
        top: 480, bottom: 480, left: 240, right: 240
      }
    },
    //8 str设置百分比
    {
      layoutRegionMargin: {
        top: '10%', bottom: '10%', left: '10%', right: '10%'
      }
    },
    //9
    {
      layoutRegionMargin: {
        top: 20, bottom: 20, left: '10%', right: '10%'
      }
    },
    //10 res设置异常值
    {
      layoutRegionMargin: {
        top: $r('app.string.EntryAbility_label'),
        bottom: 30, left: 30, right: 30
      }
    },
    //11 缺省设置
    {
      layoutRegionMargin: {
        top: 60
      }
    },
  ]

  build() {
    Stack(){
      // 避让安全距离边框
      // Scroll(){
      // }
      // .margin(10)
      // .borderWidth(0.5)
      // .borderColor(Color.Red)
      // .width('100%')
      // .height('100%')
      // .backgroundColor(Color.Transparent)

      // 绑定组件区域
      Scroll(){
        Column(){
          Column(){
          }
          .backgroundColor(Color.Pink)
          .height(10).width(10)
          .bindContextMenu(this.menuShow!!, this.MenuBuilder(), {
            layoutRegionMargin: this.layoutRegionMarginTestList[this.index[0]].layoutRegionMargin,

            preview: this.MenuPreviewBuilder(),

            placement: this.contextMenuOptions.placement,

            previewAnimationOptions: this.contextMenuOptions.previewAnimationOptions,
            onDisappear: () => {
              this.menuShow = false
            }
          })
        }
        .alignItems(this.columnAlignHorizontal)
        .justifyContent(this.columnAlignFlex)
        .width('100%').height('100%')
      }
      .width('100%')
      .height('100%')
      .borderWidth(0.5)
      .borderColor(Color.Green)
      .backgroundColor(Color.Transparent)

      // 控制区域
      Scroll(this.scroller){
        Column({space: 5}) {
          Text('验证预览图菜单布局边距属性')
            .paramTextStyle()
          Column({space: 5}) {
            Text(`切换次级菜单类型`)
              .paramTextStyle()
            Select([
              { value: 'SIDE' },
              { value: 'EMBEDDED' },
              { value: 'STACK' },
            ])
              .selectStyle()
              .onSelect((idx, value: string) => {
                switch (value) {
                  case 'SIDE':
                    this.menuAttrOption.submenuMode = 0
                    break;
                  case 'EMBEDDED':
                    this.menuAttrOption.submenuMode = 1
                    break;
                  case 'STACK':
                    this.menuAttrOption.submenuMode = 2
                    break;

                }
              })
              .key('select_subMenuMode')

            Text(`切换绑定组件位置`)
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

            Text(`切换菜单对齐方式`)
              .paramTextStyle()
            Select([
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

            Text(`预览图的scale`)
              .paramTextStyle()
            Select([
              { value: '[0.95, 1.1]' },
              { value: '[0.95, 1.4]' },
              { value: '[0.95, 1.7]' },
              { value: '[0.95, 2.1]' },
            ])
              .selectStyle()
              .onSelect((idx, value: string) => {
                switch (value) {
                  case '[0.95, 1.1]':
                    this.contextMenuOptions.previewAnimationOptions = {
                      scale: [0.95, 1.1]
                    }
                    break;
                  case '[0.95, 1.4]':
                    this.contextMenuOptions.previewAnimationOptions = {
                      scale: [0.95, 1.4]
                    }
                    break;
                  case '[0.95, 1.7]':
                    this.contextMenuOptions.previewAnimationOptions = {
                      scale: [0.95, 1.7]
                    }
                    break;
                  case '[0.95, 2.1]':
                    this.contextMenuOptions.previewAnimationOptions = {
                      scale: [0.95, 2.1]
                    }
                    break;
                }
              })
              .key('select_previewScale')
          }
          .columnStyle()

          Column({space: 5}){
            Text(`切换菜单的布局边距`)
              .paramTextStyle()
            Row({space: 3}){
              Text(`${this.index[0] + 1}` + ' / ')
                .fontSize(9)
              Text(`${this.layoutRegionMarginTestList.length}`)
                .key('paramSets_key_0')
                .fontSize(9)
              MyComponent({ title: 'Test0+', func: () => {
                this.index[0]++
                if (this.index[0] == this.layoutRegionMarginTestList.length) {
                  this.index[0] = 0
                }
              } })
              MyComponent({ title: 'Test0-', func: () => {
                this.index[0]--
                if (this.index[0] <= -1) {
                  this.index[0] = this.layoutRegionMarginTestList.length - 1
                }
              } })
            }

            Text('previewMenu: layoutRegionMargin')
              .key('previewMenu: layoutRegionMargin')
              .componentTextStyle()
              .onClick( () => {
                this.menuShow = true
              })
          }
          .columnStyle()

          Text('非预览图菜单不生效布局边距')
            .paramTextStyle()
          Column({space: 5}){
            Text(`bindMenu: layoutRegionMargin`)
              .componentTextStyle()
              .bindMenu(this.MenuBuilder(), {
                layoutRegionMargin: {top: 120, bottom: 30, left: 30, right: 30},

                placement: Placement.Top,
              })
          }
          .columnStyle()
        }
        .width('100%')
      }
      .padding(20)
      .align(Alignment.TopStart)
      .width('100%').height('100%')
    }
    .alignContent(Alignment.Center)
    .borderColor(Color.Black)
    .borderWidth(0.5)
    .width('100%')
    .height('100%')
  }
}