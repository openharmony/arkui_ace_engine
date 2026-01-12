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
import { LengthMetrics, SelectModifier } from '@kit.ArkUI';

@Observed
class MySelectAttribute extends SelectModifier {
  keyboardAvoidModeArr: (MenuKeyboardAvoidMode | undefined)[] =
    [
      MenuKeyboardAvoidMode.NONE,
      MenuKeyboardAvoidMode.TRANSLATE_AND_RESIZE,
      undefined
    ]
  keyboardAvoidModeIndex: number = 1
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
  minKeyboardAvoidDistanceIndex: number = 0
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
  menuPlacementIndex: number = 0
  isShow: boolean = false;
  avoidanceModeArr: (AvoidanceMode | undefined)[] = [
    undefined,
    AvoidanceMode.COVER_TARGET,
    AvoidanceMode.AVOID_AROUND_TARGET
  ]
  avoidanceModeIndex: number = 0
  menuAlignArr: (MenuAlignType | undefined)[] = [
    undefined,
    MenuAlignType.START,
    MenuAlignType.CENTER,
    MenuAlignType.END
  ]
  menuAlignIndex: number = 0

  applyNormalAttribute(instance: SelectAttribute): void {
    instance.keyboardAvoidMode(this.keyboardAvoidModeArr[this.keyboardAvoidModeIndex])
    instance.minKeyboardAvoidDistance(this.minKeyboardAvoidDistanceArr[this.minKeyboardAvoidDistanceIndex])
    instance.avoidance(this.avoidanceModeArr[this.avoidanceModeIndex])
    instance.menuAlign(this.menuAlignArr[this.menuAlignIndex])
  }
}

@Entry
@Component
struct Index {
  private inputController: inputMethod.InputMethodController = inputMethod.getController();
  @State selectModifier: MySelectAttribute = new MySelectAttribute();
  showInSubwindowArr: (boolean | undefined)[] = [
    undefined,
    false,
    true,
  ]
  @State showInSubwindowIndex: number = 0;
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
              Button('keyboardAvoidMode=' +
              this.selectModifier.keyboardAvoidModeArr[this.selectModifier.keyboardAvoidModeIndex])
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  if (this.selectModifier.keyboardAvoidModeIndex <
                    this.selectModifier.keyboardAvoidModeArr.length - 1) {
                    this.selectModifier.keyboardAvoidModeIndex++
                  } else {
                    this.selectModifier.keyboardAvoidModeIndex = 0
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
              Button('distance=' +
                (this.selectModifier.minKeyboardAvoidDistanceArr[this.selectModifier.minKeyboardAvoidDistanceIndex]?.value) +
                'unit=' +
                (this.selectModifier.minKeyboardAvoidDistanceArr[this.selectModifier.minKeyboardAvoidDistanceIndex]?.unit))
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  if (this.selectModifier.minKeyboardAvoidDistanceIndex <
                    this.selectModifier.minKeyboardAvoidDistanceArr.length - 1) {
                    this.selectModifier.minKeyboardAvoidDistanceIndex++
                  } else {
                    this.selectModifier.minKeyboardAvoidDistanceIndex = 0
                  }
                })
              Button('placement=' + this.selectModifier.avoidanceModeArr[this.selectModifier.avoidanceModeIndex])
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  if (this.selectModifier.avoidanceModeIndex < this.selectModifier.avoidanceModeArr.length - 1) {
                    this.selectModifier.avoidanceModeIndex++
                  } else {
                    this.selectModifier.avoidanceModeIndex = 0
                  }
                })
            }

            Column() {
              Button('showInSubwindow=' +
              this.showInSubwindowArr[this.showInSubwindowIndex])
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  if (this.showInSubwindowIndex < this.showInSubwindowArr.length - 1) {
                    this.showInSubwindowIndex++
                  } else {
                    this.showInSubwindowIndex = 0
                  }
                })
              Button('menuAlign=' + this.selectModifier.menuAlignArr[this.selectModifier.menuAlignIndex])
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  if (this.selectModifier.menuAlignIndex < this.selectModifier.menuAlignArr.length - 1) {
                    this.selectModifier.menuAlignIndex++
                  } else {
                    this.selectModifier.menuAlignIndex = 0
                  }
                })
            }
          }
        }.scrollable(ScrollDirection.Horizontal)
        .height('20%')
        .width('100%')
      }

      RelativeContainer() {
        Select([{ value: 'SelectOption' },
          { value: 'SelectOption' },
          { value: 'SelectOption' },
          { value: 'SelectOption' },
          { value: 'SelectOption' }])
          .value('Click Show Options')
          .alignRules(this.alignRuleArr[this.alignRuleIndex])
          .showInSubWindow(this.showInSubwindowArr[this.showInSubwindowIndex])
          .attributeModifier(this.selectModifier)
          .onClick(() => {
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