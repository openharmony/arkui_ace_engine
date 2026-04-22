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
  @State placement: Placement = Placement.Bottom
  @State updatePlacement: Placement = Placement.Bottom
  @State options: MenuOptions = {
    onDisappear: () => {
      this.isShow = false
    }
  }
  @State marginStep: number = 50;
  @State marginX: number = 0;
  @State marginY: number = 0;
  @State mySystemMaterial: SystemUiMaterial | undefined = undefined
  @State useAnimation: boolean = false;
  @State arrowOffset: number = 0;
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
  @State anchorPositionArray: (Position | undefined)[] = [
    undefined,
    { x: 0, y: 100 },
    { x: 200, y: 200 },
    { x: 100, y: 0 }
  ]
  @State myAnchorPositionIndex: number = 0;
  @State menuHeightArray: (number | undefined)[] = [
    undefined,
    300,
    400,
    800,
  ]
  @State myMenuHeightIndex: number = 0;
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
  @State myPreviewMode: number = 0
  @State showInSubwindowIndex: number = 0
  @State isShow: boolean = false
  @State myOutlineWidthArray: (Dimension | undefined)[] = [
    undefined,
    5,
    10,
    100,
    '100px',
    '100vp'
  ]
  @State myOutlineWidthIndex: number = 0;
  @State myOutlineColorArray: (ResourceColor | undefined)[] = [
    undefined,
    0xff00ff00,
    '#ff0000ff',
    Color.Yellow,
    $r('app.color.outlineColor'),
  ]
  @State myOutlineColorIndex: number = 0;
  @State myTransitionIndex: number = 0
  @State transitionArray: (TransitionEffect | undefined)[] = [
    undefined,
    TransitionEffect.OPACITY.animation({ duration: 4000, curve: Curve.Ease }).combine(
      TransitionEffect.rotate({ z: 1, angle: 180 })),
  ]

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

  updateMenuOption() {
    this.options = {
      enableArrow: this.enableArrow,
      placement: this.placement,
      systemMaterial: this.mySystemMaterial,
      arrowOffset: this.arrowOffset,
      borderRadius: this.borderRadiusArray[this.myBorderRadiusIndex],
      anchorPosition: this.anchorPositionArray[this.myAnchorPositionIndex],
      backgroundBlurStyle: this.blurStyleArray[this.myBlurStyleIndex],
      showInSubWindow: this.showInSubwindowIndex == 0,
      outlineColor: this.myOutlineColorArray[this.myOutlineColorIndex],
      outlineWidth: this.myOutlineWidthArray[this.myOutlineWidthIndex],
      transition: this.transitionArray[this.myTransitionIndex],
      onDisappear: () => {
        this.isShow = false
      }
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
    .height(this.menuHeightArray[this.myMenuHeightIndex])
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
            Row() {
              Text('类型:')
              Select([{ value: 'bindMenu' }, { value: 'bindMenuIsShow' }, { value: 'bindContextMenu' },
                { value: 'bindContextMenuIsShow' }, { value: 'openMenu' },
                { value: 'updateMenu' }])
                .selected(0)
                .value('bindMenu')
                .onSelect((index: number, value: string) => {
                  this.menuType = value
                })
                .controlSize(ControlSize.SMALL)
            }.layoutWeight(1)

            Row() {
              Text('启用箭头:')
              Select([{ value: 'false' }, { value: 'true' }])
                .selected(0)
                .value('false')
                .onSelect((index: number, value: string) => {
                  this.enableArrow = value == 'true'
                  this.updateMenuOption()
                })
                .controlSize(ControlSize.SMALL)
            }.layoutWeight(1)
          }

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
                  this.updateMenuOption()
                })
                .controlSize(ControlSize.SMALL)
            }.layoutWeight(1)

            Row() {
              Text('update方向:')
              Select([{ value: 'Top' }, { value: 'Bottom' }, { value: 'Left' }, { value: 'Right' },
                { value: 'TopLeft' }, { value: 'TopRight' }, { value: 'BottomLeft' }, { value: 'BottomRight' },
                { value: 'LeftTop' }, { value: 'LeftBottom' }, { value: 'RightTop' }, { value: 'RightBottom' }])
                .selected(1)
                .value('Bottom')
                .onSelect((index: number, value: string) => {
                  this.updatePlacement = this.getPlacement(value)
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
                  this.updateMenuOption()
                })
                .controlSize(ControlSize.SMALL)
            }.layoutWeight(1)

            Row() {
              Text('增减系数:')
              Select([{ value: '50' }, { value: '100' }, { value: '150' }, { value: '200' }])
                .selected(0)
                .value('50')
                .onSelect((index: number, value: string) => {
                  this.marginStep = (index + 1) * 50
                })
                .controlSize(ControlSize.SMALL)
            }.layoutWeight(1)
          }


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

          Row() {
            Row() {
              Text('ArrowOffset')
              Button('++')
                .onClick(() => {
                  this.arrowOffset += 10
                  this.updateMenuOption()
                })
                .controlSize(ControlSize.SMALL)
              Button('--')
                .onClick(() => {
                  this.arrowOffset -= 10
                  this.updateMenuOption()
                })
                .controlSize(ControlSize.SMALL)
              Button('RESET')
                .onClick(() => {
                  this.arrowOffset = 0
                  this.updateMenuOption()
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
                  this.updateMenuOption()
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
                  this.updateMenuOption()
                })
                .controlSize(ControlSize.SMALL)
              Text('当前值index =' + this.myAnchorPositionIndex)
            }
          }.width('100%')

          Row() {
            Row() {
              Text('OutLineWidth')
              Button('++')
                .onClick(() => {
                  if (this.myOutlineWidthIndex == this.myOutlineWidthArray.length - 1) {
                    this.myOutlineWidthIndex = 0;
                  } else {
                    this.myOutlineWidthIndex++
                  }
                  this.updateMenuOption()
                })
                .controlSize(ControlSize.SMALL)
              Text('当前值index =' + this.myOutlineWidthIndex)
            }
          }.width('100%')

          Row() {
            Row() {
              Text('OutLineColor')
              Button('++')
                .onClick(() => {
                  if (this.myOutlineColorIndex == this.myOutlineColorArray.length - 1) {
                    this.myOutlineColorIndex = 0;
                  } else {
                    this.myOutlineColorIndex++
                  }
                  this.updateMenuOption()
                })
                .controlSize(ControlSize.SMALL)
              Text('当前值index =' + this.myOutlineColorIndex)
            }
          }.width('100%')

          Row() {
            Row() {
              Text('MenuHeight')
              Button('++')
                .onClick(() => {
                  if (this.myMenuHeightIndex == this.menuHeightArray.length - 1) {
                    this.myMenuHeightIndex = 0;
                  } else {
                    this.myMenuHeightIndex++
                  }
                })
                .controlSize(ControlSize.SMALL)
              Text('当前值index =' + this.myMenuHeightIndex)
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
                  this.updateMenuOption()
                })
                .controlSize(ControlSize.SMALL)
              Text('当前值index =' + this.myBlurStyleIndex)

            }
          }.width('100%')

          Row() {
            Row() {
              Text('transition')
              Button('++')
                .onClick(() => {
                  if (this.myTransitionIndex == this.transitionArray.length - 1) {
                    this.myTransitionIndex = 0;
                  } else {
                    this.myTransitionIndex++
                  }
                  this.updateMenuOption()
                })
                .controlSize(ControlSize.SMALL)
              Text('当前值index =' + this.myTransitionIndex)

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

            }.layoutWeight(1)
          }
        }.padding({ left: 10, right: 10 })
      }
      .height(200)

      RelativeContainer() {
        Button('后面的按钮')
          .width(200)
          .height(100)
          .alignRules({
            center: { anchor: '__container__', align: VerticalAlign.Center },
            middle: { anchor: '__container__', align: HorizontalAlign.Center }
          })
          .margin({
            top: 200
          })
          .backgroundColor(Color.Black)
        if (this.menuType === 'bindMenu') {
          Button('bindMenu')
            .width(100)
            .height(100)
            .margin({ left: this.marginX, top: this.marginY })
            .alignRules({
              center: { anchor: '__container__', align: VerticalAlign.Center },
              middle: { anchor: '__container__', align: HorizontalAlign.Center }
            })
            .bindMenu(this.MyMenu(), this.options)
        } else if (this.menuType === 'bindMenuIsShow') {
          Button('bindMenuIsShow')
            .width(100)
            .height(100)
            .margin({ left: this.marginX, top: this.marginY })
            .alignRules({
              center: { anchor: '__container__', align: VerticalAlign.Center },
              middle: { anchor: '__container__', align: HorizontalAlign.Center }
            })
            .bindMenu(this.isShow, this.MyMenu(), this.options)
            .onClick(() => {
              this.isShow = true;
            })
        } else if (this.menuType === 'bindContextMenu') {
          Button('点击弹出菜单2')
            .width(100)
            .height(100)
            .margin({ left: this.marginX, top: this.marginY })
            .alignRules({
              center: { anchor: '__container__', align: VerticalAlign.Center },
              middle: { anchor: '__container__', align: HorizontalAlign.Center }
            })
            .bindContextMenu(this.MyMenu(), ResponseType.LongPress, {
              enableArrow: this.enableArrow,
              placement: this.placement,
              systemMaterial: this.mySystemMaterial,
              arrowOffset: this.arrowOffset,
              borderRadius: this.borderRadiusArray[this.myBorderRadiusIndex],
              anchorPosition: this.anchorPositionArray[this.myAnchorPositionIndex],
              backgroundBlurStyle: this.blurStyleArray[this.myBlurStyleIndex],
              preview: this.myPreviewMode == 0 ? undefined : MenuPreviewMode.IMAGE,
              // preview: this.MyPreview()
              outlineColor: this.myOutlineColorArray[this.myOutlineColorIndex],
              outlineWidth: this.myOutlineWidthArray[this.myOutlineWidthIndex],
              transition: this.transitionArray[this.myTransitionIndex],
            })
        } else if (this.menuType === 'bindContextMenuIsShow') {
          Button('bindContextMenuIsShow')
            .width(100)
            .height(100)
            .margin({ left: this.marginX, top: this.marginY })
            .alignRules({
              center: { anchor: '__container__', align: VerticalAlign.Center },
              middle: { anchor: '__container__', align: HorizontalAlign.Center }
            })
            .bindContextMenu(this.isShow, this.MyMenu(), {
              enableArrow: this.enableArrow,
              placement: this.placement,
              systemMaterial: this.mySystemMaterial,
              arrowOffset: this.arrowOffset,
              borderRadius: this.borderRadiusArray[this.myBorderRadiusIndex],
              anchorPosition: this.anchorPositionArray[this.myAnchorPositionIndex],
              // maxHeight: LengthMetrics.vp(200),
              backgroundBlurStyle: this.blurStyleArray[this.myBlurStyleIndex],
              preview: this.myPreviewMode == 0 ? undefined : MenuPreviewMode.IMAGE,
              // preview: this.MyPreview()
              outlineColor: this.myOutlineColorArray[this.myOutlineColorIndex],
              outlineWidth: this.myOutlineWidthArray[this.myOutlineWidthIndex],
              transition: this.transitionArray[this.myTransitionIndex],
              onDisappear: () => {
                this.isShow = false
              }
            })
            .onClick(() => {
              this.isShow = true;
            })
        } else if (this.menuType == 'openMenu') {
          Button('openMenu')
            .width(100)
            .height(100)
            .margin({ left: this.marginX, top: this.marginY })
            .alignRules({
              center: { anchor: '__container__', align: VerticalAlign.Center },
              middle: { anchor: '__container__', align: HorizontalAlign.Center }
            })
            .id('openMenu')
            .onClick(() => {
              let context = this.getUIContext();
              const contentNode = new ComponentContent(context, wrapBuilder(MyMenu));
              const promptAction = context.getPromptAction();
              promptAction.openMenu(contentNode, { id: 'openMenu' }, this.options)
            })
        } else if (this.menuType == 'updateMenu') {
          Button('updateMenu')
            .width(100)
            .height(100)
            .margin({ left: this.marginX, top: this.marginY })
            .alignRules({
              center: { anchor: '__container__', align: VerticalAlign.Center },
              middle: { anchor: '__container__', align: HorizontalAlign.Center }
            })
            .id('updateMenu')
            .onClick(() => {
              let context = this.getUIContext();
              const contentNode = new ComponentContent(context, wrapBuilder(MyMenu));
              const promptAction = context.getPromptAction();
              promptAction.openMenu(contentNode, { id: 'updateMenu' }, this.options)
              if (this.useAnimation) {
                setTimeout(() => {
                  animateTo({
                    duration: 1000,
                    curve: Curve.EaseOut,
                    iterations: 1,
                    playMode: PlayMode.Normal,
                    onFinish: () => {

                    }
                  }, () => {
                    promptAction.updateMenu(contentNode, {
                      enableArrow: true,
                      arrowOffset: this.arrowOffset,
                      borderRadius: this.borderRadiusArray[this.myBorderRadiusIndex],
                      placement: this.updatePlacement,
                    }, true)
                  })
                }, 2000)
              } else {
                setTimeout(() => {
                  promptAction.updateMenu(contentNode, {
                    enableArrow: true,
                    arrowOffset: this.arrowOffset,
                    borderRadius: this.borderRadiusArray[this.myBorderRadiusIndex],
                    placement: this.updatePlacement,
                  }, true)
                }, 2000)
              }
            })
        }

      }.layoutWeight(1)
      .width('100%')
      .backgroundColor(Color.Pink)
    }

    .height('100%')
    .width('100%')

  }
}
