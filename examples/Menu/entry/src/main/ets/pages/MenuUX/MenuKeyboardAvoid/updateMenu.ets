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

import { ComponentContent, FrameNode, LengthMetrics } from '@kit.ArkUI';
import { inputMethod } from '@kit.IMEKit';

@Builder
function MyMenu() {
  Column() {
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项1' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项2' })
    }
  }
  .width('80%')
  .padding('20lpx')
}

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
  @State keyboardAvoidModeUpdateIndex: number = 0
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
  @State minKeyboardAvoidDistanceUpdateIndex: number = 0
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
  showInSubwindowArr: (boolean | undefined)[] = [
    undefined,
    false,
    true,
  ]
  @State showInSubwindowIndex: number = 0;

  build() {
    Column() {
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
              Button('showInSubwindow=' + this.showInSubwindowArr[this.showInSubwindowIndex])
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  if (this.showInSubwindowIndex < this.showInSubwindowArr.length - 1) {
                    this.showInSubwindowIndex++
                  } else {
                    this.showInSubwindowIndex = 0
                  }
                })
            }
          }
        }.scrollable(ScrollDirection.Horizontal)
        .width('100%')

        Row() {
          Button('keyboardAvoidModeUpdate=' + this.keyboardAvoidModeArr[this.keyboardAvoidModeUpdateIndex])
            .controlSize(ControlSize.SMALL)
            .onClick(() => {
              if (this.keyboardAvoidModeUpdateIndex < this.keyboardAvoidModeArr.length - 1) {
                this.keyboardAvoidModeUpdateIndex++
              } else {
                this.keyboardAvoidModeUpdateIndex = 0
              }
            })
          Button('minKeyboardAvoidDistanceUpdate=' +
            (this.minKeyboardAvoidDistanceArr[this.minKeyboardAvoidDistanceUpdateIndex]?.value) +
            'unit=' +
            (this.minKeyboardAvoidDistanceArr[this.minKeyboardAvoidDistanceUpdateIndex]?.unit))
            .controlSize(ControlSize.SMALL)
            .onClick(() => {
              if (this.minKeyboardAvoidDistanceUpdateIndex < this.minKeyboardAvoidDistanceArr.length - 1) {
                this.minKeyboardAvoidDistanceUpdateIndex++
              } else {
                this.minKeyboardAvoidDistanceUpdateIndex = 0
              }
            })
        }
        .width('100%')
      }
      .height('20%')
      .width('100%')


      RelativeContainer() {
        Button('OpenMenu', { type: ButtonType.Normal, stateEffect: true })
          .borderRadius('16lpx')
          .width('40%')
          .margin(10)
          .id('openMenu')
          .onClick(() => {
            let context = this.getUIContext();
            const contentNode = new ComponentContent(context, wrapBuilder(MyMenu));
            const promptAction = context.getPromptAction();
            promptAction.openMenu(contentNode, { id: 'openMenu' }, {
              keyboardAvoidMode: this.keyboardAvoidModeArr[this.keyboardAvoidModeIndex],
              minKeyboardAvoidDistance: this.minKeyboardAvoidDistanceArr[this.minKeyboardAvoidDistanceIndex],
              placement: this.menuPlacementArr[this.menuPlacementIndex],
              showInSubWindow: this.showInSubwindowArr[this.showInSubwindowIndex]
            });
            setTimeout(() => {
              this.attachAndListener()
            }, 2000)

            setTimeout(() => {
              promptAction.updateMenu(contentNode, {
                keyboardAvoidMode: this.keyboardAvoidModeArr[this.keyboardAvoidModeUpdateIndex],
                minKeyboardAvoidDistance: this.minKeyboardAvoidDistanceArr[this.minKeyboardAvoidDistanceUpdateIndex],
                placement: this.menuPlacementArr[this.menuPlacementIndex],
                showInSubWindow: this.showInSubwindowArr[this.showInSubwindowIndex]
              });
            }, 4000)
          })
          .alignRules(this.alignRuleArr[this.alignRuleIndex])
      }
      .height('80%')
      .width('100%')
    }
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

