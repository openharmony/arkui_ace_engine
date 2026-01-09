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

import { inputMethod } from '@kit.IMEKit';
import { LengthMetrics } from '@kit.ArkUI';

@Entry
@Component
struct Index {
  private inputController: inputMethod.InputMethodController = inputMethod.getController();
  keyboardAvoidModeArr: (MenuKeyboardAvoidMode | undefined)[] =
    [
      MenuKeyboardAvoidMode.NONE,
      MenuKeyboardAvoidMode.TRANSLATE_AND_RESIZE,
      undefined
    ]
  @State keyboardAvoidModeIndex: number = 0
  minKeyboardAvoidDistanceArr: (LengthMetrics | undefined)[] = [
    LengthMetrics.vp(0),
    LengthMetrics.px(100),
    LengthMetrics.px(-100),
    LengthMetrics.vp(100),
    LengthMetrics.vp(1000),
    LengthMetrics.vp(-100),
    LengthMetrics.vp(-1000),
    LengthMetrics.percent(0.5),
    undefined
  ]
  @State minKeyboardAvoidDistanceIndex: number = 0
  menuPlacementArr: (Placement | undefined)[] = [
    undefined,
    Placement.BottomLeft,
    Placement.Bottom,
    Placement.BottomRight,
    Placement.TopLeft,
    Placement.Top,
    Placement.TopRight,
    Placement.LeftTop,
    Placement.Left,
    Placement.LeftBottom,
    Placement.RightTop,
    Placement.Right,
    Placement.RightBottom
  ]
  @State menuPlacementIndex: number = 0
  @State isShow: boolean = false;
  alignRuleArr: (AlignRuleOption)[] = [
    {
      center: { anchor: '__container__', align: VerticalAlign.Center },
      middle: { anchor: '__container__', align: HorizontalAlign.Center },
    },
    {
      center: { anchor: '__container__', align: VerticalAlign.Center },
      left: { anchor: '__container__', align: HorizontalAlign.Start },
    },
    {
      center: { anchor: '__container__', align: VerticalAlign.Center },
      right: { anchor: '__container__', align: HorizontalAlign.End },
    },
    {
      top: { anchor: '__container__', align: VerticalAlign.Top },
      middle: { anchor: '__container__', align: HorizontalAlign.Center },
    },
    {
      top: { anchor: '__container__', align: VerticalAlign.Top },
      left: { anchor: '__container__', align: HorizontalAlign.Start },
    },
    {
      top: { anchor: '__container__', align: VerticalAlign.Top },
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
  @State alignRuleIndex: number = 0

  GetPreview(index: number): undefined | MenuPreviewMode {
    if (index == 1) {
      return MenuPreviewMode.IMAGE
    } else if (index == 2) {
      return MenuPreviewMode.NONE
    }
    return undefined
  }

  @State previewIndex: number = 0

  @Builder
  MyPreview() {
    Image($r('app.media.app_icon'))
      .width(200)
      .height(200)
  }

  @Builder
  MyMenu() {
    Menu() {
      MenuItem({ content: 'MenuItemContent' })
      MenuItem({ content: 'MenuItemContent' })
      MenuItem({ content: 'MenuItemContent' })
      MenuItem({ content: 'MenuItemContent' })
      MenuItem({ content: 'MenuItemContent' })
    }
  }

  build() {
    Column({ space: 5 }) {
      Column() {
        Scroll() {
          Row() {
            Column() {
              Button('keyboardAvoidMode=' + this.keyboardAvoidModeArr[this.keyboardAvoidModeIndex])
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  if (this.keyboardAvoidModeIndex < this.keyboardAvoidModeArr.length - 1) {
                    this.keyboardAvoidModeIndex++
                  } else {
                    this.keyboardAvoidModeIndex = 0
                  }
                })
              Button('alignRules=' + this.alignRuleIndex)
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  if (this.alignRuleIndex < this.alignRuleArr.length - 1) {
                    this.alignRuleIndex++
                  } else {
                    this.alignRuleIndex = 0
                  }
                })
            }

            Column() {
              Button('distance=' + (this.minKeyboardAvoidDistanceArr[this.minKeyboardAvoidDistanceIndex]?.value) +
                'unit=' +
                (this.minKeyboardAvoidDistanceArr[this.minKeyboardAvoidDistanceIndex]?.unit))
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  if (this.minKeyboardAvoidDistanceIndex < this.minKeyboardAvoidDistanceArr.length - 1) {
                    this.minKeyboardAvoidDistanceIndex++
                  } else {
                    this.minKeyboardAvoidDistanceIndex = 0
                  }
                })
              Button('placement=' + this.menuPlacementArr[this.menuPlacementIndex])
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  if (this.menuPlacementIndex < this.menuPlacementArr.length - 1) {
                    this.menuPlacementIndex++
                  } else {
                    this.menuPlacementIndex = 0
                  }
                })
            }

            Column() {
              Button('preview=' + this.previewIndex)
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  if (this.previewIndex < 3) {
                    this.previewIndex++
                  } else {
                    this.previewIndex = 0
                  }
                })
              Button('any')
                .controlSize(ControlSize.SMALL)
            }
          }
        }.scrollable(ScrollDirection.Horizontal)
        .height('20%')
        .width('100%')
      }

      RelativeContainer() {
        Button('Click Show Menu')
          .alignRules(this.alignRuleArr[this.alignRuleIndex])
          .bindContextMenu(this.isShow, this.MyMenu, this.previewIndex != 3 ? {
            keyboardAvoidMode: this.keyboardAvoidModeArr[this.keyboardAvoidModeIndex],
            minKeyboardAvoidDistance: this.minKeyboardAvoidDistanceArr[this.minKeyboardAvoidDistanceIndex],
            placement: this.menuPlacementArr[this.menuPlacementIndex],
            onDisappear: () => {
              this.isShow = false
            },
            preview: this.GetPreview(this.previewIndex)
          } : {
            keyboardAvoidMode: this.keyboardAvoidModeArr[this.keyboardAvoidModeIndex],
            minKeyboardAvoidDistance: this.minKeyboardAvoidDistanceArr[this.minKeyboardAvoidDistanceIndex],
            placement: this.menuPlacementArr[this.menuPlacementIndex],
            onDisappear: () => {
              this.isShow = false
            },
            preview: this.MyPreview()
          })
          .onClick(() => {
            this.isShow = true;
            setTimeout(() => {
              this.attachAndListener()
            }, 2000)
          })
      }
      .height('80%')
      .width('100%')
    }.alignItems(HorizontalAlign.Start)

  }

  async attachAndListener() {
    focusControl.requestFocus('Index')
    try {
      await this.inputController.attach(true, {
        inputAttribute: {
          textInputType: inputMethod.TextInputType.TEXT,
          enterKeyType: inputMethod.EnterKeyType.SEARCH
        }
      })
    } catch (err) {
      console.error('Fail to attach')
    }
  }
}