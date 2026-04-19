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

import uiMaterial from '@ohos.arkui.uiMaterial'
import { ComponentContent } from '@kit.ArkUI'

@Builder
function MyMenu() {
  Menu() {
    MenuItem({ content: '我是菜单项' })
    MenuItem({ content: '我是菜单项' })
    MenuItem({ content: '我是菜单项' })
    MenuItem({ content: '我是菜单项' })
  }
}

@Entry
@Component
struct Index {
  @State menuType: string = 'bindMenu'
  @State enableArrow: boolean = false
  @State updateEnableArrow: boolean = false
  @State placement: Placement = Placement.Bottom
  @State updatePlacement: Placement = Placement.Bottom
  @State marginStep: number = 50;
  @State marginX: number = 0;
  @State marginY: number = 0;
  @State mySystemMaterial: SystemUiMaterial | undefined = undefined
  @State myUpdateSystemMaterial: SystemUiMaterial | undefined = undefined
  @State useAnimation: boolean = false;
  @State arrowOffset: number = 0;
  @State updateArrowOffset: number = 0;
  @State borderRadiusArray: (Length | BorderRadiuses | LocalizedBorderRadiuses | undefined)[] = [
    undefined,
    0,
    10,
    20,
    1000,
    {
      topLeft: 10,
      topRight: 10,
      bottomLeft: 10,
      bottomRight: 10
    },
    {
      topLeft: 10,
      topRight: 20,
      bottomLeft: 30,
      bottomRight: 40
    },
  ]
  @State myBorderRadiusIndex: number = 0;
  @State myUpdateBorderRadiusIndex: number = 0;
  @State anchorPositionArray: (Position | undefined)[] = [
    undefined,
    { x: 0, y: 100 },
    { x: 200, y: 200 },
    { x: 100, y: 0 }
  ]
  @State myAnchorPositionIndex: number = 0;
  @State myUpdateAnchorPositionIndex: number = 0;
  @State menuHeightArray: (number | undefined)[] = [
    undefined,
    300,
    400,
    800,
  ]
  @State blurStyleArray: (BlurStyle | undefined)[] = [
    undefined,
    BlurStyle.Thin,
    BlurStyle.Regular,
    BlurStyle.Thick,
    BlurStyle.BACKGROUND_THIN,
    BlurStyle.BACKGROUND_REGULAR,
    BlurStyle.BACKGROUND_ULTRA_THICK,
    BlurStyle.NONE,
    BlurStyle.COMPONENT_THICK
  ]
  @State myBlurStyleIndex: number = 0;
  @State myUpdateBlurStyleIndex: number = 0;
  @State myPreviewMode: number = 0
  @State showInSubwindowIndex: number = 0
  @State options: MenuOptions = {
    enableArrow: this.enableArrow,
    placement: this.placement,
    systemMaterial: this.mySystemMaterial,
    arrowOffset: this.arrowOffset,
    borderRadius: this.borderRadiusArray[this.myBorderRadiusIndex],
    anchorPosition: this.anchorPositionArray[this.myAnchorPositionIndex],
    backgroundBlurStyle: this.blurStyleArray[this.myBlurStyleIndex],
    showInSubWindow: this.showInSubwindowIndex == 0,
  }
  @State updateOptions: MenuOptions = {
    enableArrow: this.updateEnableArrow,
    placement: this.updatePlacement,
    systemMaterial: this.myUpdateSystemMaterial,
    arrowOffset: this.updateArrowOffset,
    borderRadius: this.borderRadiusArray[this.myUpdateBorderRadiusIndex],
    anchorPosition: this.anchorPositionArray[this.myUpdateAnchorPositionIndex],
    backgroundBlurStyle: this.blurStyleArray[this.myUpdateBlurStyleIndex],
    showInSubWindow: this.showInSubwindowIndex == 0,
  }
  alignRuleArr: (AlignRuleOption)[] = [
    {
      top: { anchor: '__container__', align: VerticalAlign.Top },
      left: { anchor: '__container__', align: HorizontalAlign.Start },
    },
    {
      top: { anchor: '__container__', align: VerticalAlign.Top },
      middle: { anchor: '__container__', align: HorizontalAlign.Center },
    },
    {
      top: { anchor: '__container__', align: VerticalAlign.Top },
      right: { anchor: '__container__', align: HorizontalAlign.End },
    },
    {
      center: { anchor: '__container__', align: VerticalAlign.Center },
      left: { anchor: '__container__', align: HorizontalAlign.Start },
    },
    {
      center: { anchor: '__container__', align: VerticalAlign.Center },
      middle: { anchor: '__container__', align: HorizontalAlign.Center },
    },
    {
      center: { anchor: '__container__', align: VerticalAlign.Center },
      right: { anchor: '__container__', align: HorizontalAlign.End },
    },
    {
      bottom: { anchor: '__container__', align: VerticalAlign.Bottom },
      left: { anchor: '__container__', align: HorizontalAlign.Start },
    },
    {
      bottom: { anchor: '__container__', align: VerticalAlign.Bottom },
      middle: { anchor: '__container__', align: HorizontalAlign.Center },
    },
    {
      bottom: { anchor: '__container__', align: VerticalAlign.Bottom },
      right: { anchor: '__container__', align: HorizontalAlign.End },
    },
  ]
  @State alignRuleIndex: number = 4

  getPlacement(value: string): Placement {
    switch (value) {
      case 'Top':
        return Placement.Top
      case 'Bottom':
        return Placement.Bottom
      case 'Left':
        return Placement.Left
      case 'Right':
        return Placement.Right
      case 'TopLeft':
        return Placement.TopLeft
      case 'TopRight':
        return Placement.TopRight
      case 'BottomLeft':
        return Placement.BottomLeft
      case 'BottomRight':
        return Placement.BottomRight
      case 'LeftTop':
        return Placement.LeftTop
      case 'LeftBottom':
        return Placement.LeftBottom
      case 'RightTop':
        return Placement.RightTop
      case 'RightBottom':
        return Placement.RightBottom
      default:
        return Placement.Bottom
    }
  }

  openMenuOption() {
    this.options = {
      enableArrow: this.enableArrow,
      placement: this.placement,
      systemMaterial: this.mySystemMaterial,
      arrowOffset: this.arrowOffset,
      borderRadius: this.borderRadiusArray[this.myBorderRadiusIndex],
      anchorPosition: this.anchorPositionArray[this.myAnchorPositionIndex],
      backgroundBlurStyle: this.blurStyleArray[this.myBlurStyleIndex],
      showInSubWindow: this.showInSubwindowIndex == 0,
      preview: this.myPreviewMode == 0 ? undefined : MenuPreviewMode.IMAGE
    }
  }

  updateMenuOption() {
    this.updateOptions = {
      enableArrow: this.updateEnableArrow,
      placement: this.updatePlacement,
      systemMaterial: this.myUpdateSystemMaterial,
      arrowOffset: this.updateArrowOffset,
      borderRadius: this.borderRadiusArray[this.myUpdateBorderRadiusIndex],
      anchorPosition: this.anchorPositionArray[this.myUpdateAnchorPositionIndex],
      backgroundBlurStyle: this.blurStyleArray[this.myUpdateBlurStyleIndex],
      showInSubWindow: this.showInSubwindowIndex == 0,
      preview: this.myPreviewMode == 0 ? undefined : MenuPreviewMode.IMAGE
    }
  }

  @Builder
  MyMenu() {
    Menu() {
      MenuItem({ content: '我是菜单项' })
      MenuItem({ content: '我是菜单项' })
      MenuItem({ content: '我是菜单项' })
      MenuItem({ content: '我是菜单项' })
    }
  }

  @Builder
  MyPreview() {
    Column() {
      Text('自定义预览菜单')
    }
    .width(100)
    .height(100)
    .backgroundColor(Color.Yellow)
  }

  build() {
    Column() {
      Scroll() {
        Column({ space: 4 }) {
          Row() {
            Text('目标节点位置')
            Select([{ value: '上左' }, { value: '上中' }, { value: '上右' },
              { value: '中左' }, { value: '居中' }, { value: '中右' },
              { value: '下左' }, { value: '下中' }, { value: '下右' },])
              .selected(4)
              .value('居中')
              .onSelect((index: number, value: string) => {
                this.alignRuleIndex = index
              })
              .controlSize(ControlSize.SMALL)
          }.width('100%')

          Row() {
            Row() {
              Text('使用动画:')
              Select([{ value: 'false' }, { value: 'true' }])
                .selected(0)
                .value('false')
                .onSelect((index: number, value: string) => {
                  this.useAnimation = value == 'true'
                })
                .controlSize(ControlSize.SMALL)
            }.layoutWeight(1)

            Row() {
              Text('Margin增减系数:')
              Select([{ value: '50' }, { value: '100' }, { value: '150' }, { value: '200' }])
                .selected(0)
                .value('50')
                .onSelect((index: number, value: string) => {
                  this.marginStep = (index + 1) * 50
                })
                .controlSize(ControlSize.SMALL)
            }.layoutWeight(1)
          }

          //以下几个属性不支持更新，OpenMenu固有规格
          Row() {
            Row() {
              Text('showInSubwindow')
              Button('++')
                .onClick(() => {
                  if (this.showInSubwindowIndex == 1) {
                    this.showInSubwindowIndex = 0
                  } else {
                    this.showInSubwindowIndex++
                  }
                  this.updateMenuOption()
                })
                .controlSize(ControlSize.SMALL)
              Text('当前值index =' + this.showInSubwindowIndex)
            }
          }.width('100%')

          Row() {
            Row() {
              Text('previewMode')
              Button('++')
                .onClick(() => {
                  if (this.myPreviewMode == 1) {
                    this.myPreviewMode = 0
                  } else {
                    this.myPreviewMode++
                  }
                  this.updateMenuOption()
                })
                .controlSize(ControlSize.SMALL)
              Text('当前值index =' + this.myPreviewMode)
            }
          }.width('100%')

          Row() {
            Row() {
              Text('blurStyle')
              Button('++')
                .onClick(() => {
                  if (this.myBlurStyleIndex == this.blurStyleArray.length - 1) {
                    this.myBlurStyleIndex = 0;
                  } else {
                    this.myBlurStyleIndex++
                  }
                  this.openMenuOption()
                })
                .controlSize(ControlSize.SMALL)
              Text('当前值index =' + this.myBlurStyleIndex)

            }
          }.width('100%')

          //改变Margin可以改变目标节点位置
          Row() {
            Text('Margin')
            Button('X++')
              .onClick(() => {
                this.marginX += this.marginStep
              })
              .controlSize(ControlSize.SMALL)
            Button('X--')
              .onClick(() => {
                this.marginX -= this.marginStep
              })
              .controlSize(ControlSize.SMALL)
            Button('Y++')
              .onClick(() => {
                this.marginY += this.marginStep
              })
              .controlSize(ControlSize.SMALL)
            Button('Y--')
              .onClick(() => {
                this.marginY -= this.marginStep
              })
              .controlSize(ControlSize.SMALL)
            Text('当前值(' + this.marginX + ',' + this.marginY + ')')
          }.width('100%')

          Text('OpenMenu的Option配置')
            .backgroundColor(Color.Green)
            .fontColor(Color.Blue)
            .width(200)
            .height(40)

          Row() {
            Row() {
              Text('启用箭头:')
              Select([{ value: 'false' }, { value: 'true' }])
                .selected(0)
                .value('false')
                .onSelect((index: number, value: string) => {
                  this.enableArrow = value == 'true'
                  this.openMenuOption()
                })
                .controlSize(ControlSize.SMALL)
            }.layoutWeight(1)
          }.width('100%')

          Row() {
            Row() {
              Text('菜单方向:')
              Select([{ value: 'Top' }, { value: 'Bottom' }, { value: 'Left' }, { value: 'Right' },
                { value: 'TopLeft' }, { value: 'TopRight' }, { value: 'BottomLeft' }, { value: 'BottomRight' },
                { value: 'LeftTop' }, { value: 'LeftBottom' }, { value: 'RightTop' }, { value: 'RightBottom' }])
                .selected(1)
                .value('Bottom')
                .onSelect((index: number, value: string) => {
                  this.placement = this.getPlacement(value)
                  this.openMenuOption()
                })
                .controlSize(ControlSize.SMALL)
            }.layoutWeight(1)

          }

          Row() {
            Row() {
              Text('Material:')
              Select([{ value: 'undefined' }, { value: 'NONE' }, { value: 'SEMI' }, { value: 'hds1' },
                { value: 'hds2' }])
                .selected(0)
                .value('undefined')
                .onSelect((index: number, value: string) => {
                  if (index == 0) {
                    this.mySystemMaterial = undefined
                  } else if (index == 1) {
                    this.mySystemMaterial = new uiMaterial.Material({ type: uiMaterial.MaterialType.NONE })
                  } else if (index == 2) {
                    this.mySystemMaterial = new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT })
                  } else {
                    console.log('当前Material暂不可用')
                  }
                  this.openMenuOption()
                })
                .controlSize(ControlSize.SMALL)
            }.layoutWeight(1)
          }


          Row() {
            Row() {
              Text('ArrowOffset')
              Button('++')
                .onClick(() => {
                  this.arrowOffset += 10
                  this.openMenuOption()
                })
                .controlSize(ControlSize.SMALL)
              Button('--')
                .onClick(() => {
                  this.arrowOffset -= 10
                  this.openMenuOption()
                })
                .controlSize(ControlSize.SMALL)
              Button('RESET')
                .onClick(() => {
                  this.arrowOffset = 0
                  this.openMenuOption()
                })
                .controlSize(ControlSize.SMALL)
              Text('当前值' + this.arrowOffset)
            }
          }.width('100%')

          Row() {
            Row() {
              Text('BorderRadius')
              Button('++')
                .onClick(() => {
                  if (this.myBorderRadiusIndex == this.borderRadiusArray.length - 1) {
                    this.myBorderRadiusIndex = 0;
                  } else {
                    this.myBorderRadiusIndex++
                  }
                  this.openMenuOption()
                })
                .controlSize(ControlSize.SMALL)
              Text('当前值index =' + this.myBorderRadiusIndex)
            }
          }.width('100%')

          Row() {
            Row() {
              Text('AnchorPosition')
              Button('++')
                .onClick(() => {
                  if (this.myAnchorPositionIndex == this.anchorPositionArray.length - 1) {
                    this.myAnchorPositionIndex = 0;
                  } else {
                    this.myAnchorPositionIndex++
                  }
                  this.openMenuOption()
                })
                .controlSize(ControlSize.SMALL)
              Text('当前值index =' + this.myAnchorPositionIndex)
            }
          }.width('100%')


          Text('updateMenu的Option配置')
            .backgroundColor(Color.Green)
            .fontColor(Color.Blue)
            .width(200)
            .height(40)

          Row() {
            Row() {
              Text('update启用箭头:')
              Select([{ value: 'false' }, { value: 'true' }])
                .selected(0)
                .value('false')
                .onSelect((index: number, value: string) => {
                  this.updateEnableArrow = value == 'true'
                  this.updateMenuOption()
                })
                .controlSize(ControlSize.SMALL)
            }.layoutWeight(1)
          }.width('100%')

          Row() {
            Row() {
              Text('update方向:')
              Select([{ value: 'Top' }, { value: 'Bottom' }, { value: 'Left' }, { value: 'Right' },
                { value: 'TopLeft' }, { value: 'TopRight' }, { value: 'BottomLeft' }, { value: 'BottomRight' },
                { value: 'LeftTop' }, { value: 'LeftBottom' }, { value: 'RightTop' }, { value: 'RightBottom' }])
                .selected(1)
                .value('Bottom')
                .onSelect((index: number, value: string) => {
                  this.updatePlacement = this.getPlacement(value)
                  this.updateMenuOption();
                })
                .controlSize(ControlSize.SMALL)
            }.layoutWeight(1)
          }.width('100%')

          Row() {
            Row() {
              Text('Material:')
              Select([{ value: 'undefined' }, { value: 'NONE' }, { value: 'SEMI' }, { value: 'hds1' },
                { value: 'hds2' }])
                .selected(0)
                .value('undefined')
                .onSelect((index: number, value: string) => {
                  if (index == 0) {
                    this.myUpdateSystemMaterial = undefined
                  } else if (index == 1) {
                    this.myUpdateSystemMaterial = new uiMaterial.Material({ type: uiMaterial.MaterialType.NONE })
                  } else if (index == 2) {
                    this.myUpdateSystemMaterial =
                      new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT })
                  } else {
                    console.log('当前Material暂不可用')
                  }
                  this.updateMenuOption()
                })
                .controlSize(ControlSize.SMALL)
            }.layoutWeight(1)
          }


          Row() {
            Row() {
              Text('ArrowOffset')
              Button('++')
                .onClick(() => {
                  this.updateArrowOffset += 10
                  this.updateMenuOption()
                })
                .controlSize(ControlSize.SMALL)
              Button('--')
                .onClick(() => {
                  this.updateArrowOffset -= 10
                  this.updateMenuOption()
                })
                .controlSize(ControlSize.SMALL)
              Button('RESET')
                .onClick(() => {
                  this.updateArrowOffset = 0
                  this.updateMenuOption()
                })
                .controlSize(ControlSize.SMALL)
              Text('当前值' + this.updateArrowOffset)
            }
          }.width('100%')

          Row() {
            Row() {
              Text('BorderRadius')
              Button('++')
                .onClick(() => {
                  if (this.myUpdateBorderRadiusIndex == this.borderRadiusArray.length - 1) {
                    this.myUpdateBorderRadiusIndex = 0;
                  } else {
                    this.myUpdateBorderRadiusIndex++
                  }
                  this.updateMenuOption()
                })
                .controlSize(ControlSize.SMALL)
              Text('当前值index =' + this.myUpdateBorderRadiusIndex)
            }
          }.width('100%')

          Row() {
            Row() {
              Text('AnchorPosition')
              Button('++')
                .onClick(() => {
                  if (this.myUpdateAnchorPositionIndex == this.anchorPositionArray.length - 1) {
                    this.myUpdateAnchorPositionIndex = 0;
                  } else {
                    this.myUpdateAnchorPositionIndex++
                  }
                  this.updateMenuOption()
                })
                .controlSize(ControlSize.SMALL)
              Text('当前值index =' + this.myUpdateAnchorPositionIndex)
            }
          }.width('100%')

        }.padding({ left: 10, right: 10 })
      }
      .height(200)

      RelativeContainer() {
        Button('updateMenu')
          .width(100)
          .height(100)
          .margin({ left: this.marginX, top: this.marginY })
          .alignRules(this.alignRuleArr[this.alignRuleIndex])
          .id('updateMenu')
          .onClick(() => {
            let context = this.getUIContext();
            const contentNode = new ComponentContent(context, wrapBuilder(MyMenu));
            const promptAction = context.getPromptAction();
            promptAction.openMenu(contentNode, { id: 'updateMenu' }, this.options)
            if (this.useAnimation) {
              setTimeout(() => {
                animateTo({
                  duration: 2000,
                  curve: Curve.EaseOut,
                  iterations: 1,
                  playMode: PlayMode.Normal,
                  onFinish: () => {

                  }
                }, () => {
                  promptAction.updateMenu(contentNode, this.updateOptions, true)
                })
              }, 2000)
            } else {
              setTimeout(() => {
                promptAction.updateMenu(contentNode, this.updateOptions, true)
              }, 2000)
            }
          })

      }.layoutWeight(1)
      .width('100%')
      .backgroundColor(Color.Pink)
    }

    .height('100%')
    .width('100%')

  }
}