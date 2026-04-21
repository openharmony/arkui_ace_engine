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
import { inputMethod } from '@kit.IMEKit';
import { LengthMetrics } from '@kit.ArkUI';

@Entry
@Component
struct Index {
  private inputController: inputMethod.InputMethodController = inputMethod.getController();
  
  keyboardAvoidModeArr: (MenuKeyboardAvoidMode | undefined)[] = [
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
  
  alignRuleArr: AlignRuleOption[] = [
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
  @State showInSubwindowIndex: number = 0
  
  @State enableArrow: boolean = false
  @State mySystemMaterial: SystemUiMaterial | undefined = undefined
  @State arrowOffset: number = 0
  
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
    Column() {
      Scroll() {
        Column({ space: 10 }) {
          Row({ space: 10 }) {
            Column({ space: 5 }) {
              Text('键盘避让模式')
                .fontSize(12)
              Button(this.keyboardAvoidModeArr[this.keyboardAvoidModeIndex]?.toString() ?? 'undefined')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.keyboardAvoidModeIndex = (this.keyboardAvoidModeIndex + 1) % this.keyboardAvoidModeArr.length
                })
            }.layoutWeight(1)
            
            Column({ space: 5 }) {
              Text('避让距离')
                .fontSize(12)
              Button(this.minKeyboardAvoidDistanceArr[this.minKeyboardAvoidDistanceIndex]?.value?.toString() ?? 'undefined')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.minKeyboardAvoidDistanceIndex = (this.minKeyboardAvoidDistanceIndex + 1) % this.minKeyboardAvoidDistanceArr.length
                })
            }.layoutWeight(1)
            
            Column({ space: 5 }) {
              Text('菜单位置')
                .fontSize(12)
              Button(this.menuPlacementArr[this.menuPlacementIndex]?.toString() ?? 'undefined')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.menuPlacementIndex = (this.menuPlacementIndex + 1) % this.menuPlacementArr.length
                })
            }.layoutWeight(1)
          }
          
          Row({ space: 10 }) {
            Column({ space: 5 }) {
              Text('对齐规则')
                .fontSize(12)
              Button('alignRule=' + this.alignRuleIndex)
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.alignRuleIndex = (this.alignRuleIndex + 1) % this.alignRuleArr.length
                })
            }.layoutWeight(1)
            
            Column({ space: 5 }) {
              Text('子窗口显示')
                .fontSize(12)
              Button('showInSubwindow=' + this.showInSubwindowArr[this.showInSubwindowIndex]?.toString() ?? 'undefined')
                .controlSize(ControlSize.SMALL)
                .onClick(() => {
                  this.showInSubwindowIndex = (this.showInSubwindowIndex + 1) % this.showInSubwindowArr.length
                })
            }.layoutWeight(1)
            
            Column({ space: 5 }) {
              Text('启用箭头')
                .fontSize(12)
              Select([{ value: 'false' }, { value: 'true' }])
                .selected(this.enableArrow ? 1 : 0)
                .value(this.enableArrow ? 'true' : 'false')
                .onSelect((index: number) => {
                  this.enableArrow = index === 1
                })
            }.layoutWeight(1)
          }
          
          Row({ space: 10 }) {
            Column({ space: 5 }) {
              Text('Material类型')
                .fontSize(12)
              Select([{ value: 'undefined' }, { value: 'SEMI_TRANSPARENT' }, { value: 'NONE' }])
                .selected(0)
                .value('undefined')
                .onSelect((index: number, value: string) => {
                  if (index == 0) {
                    this.mySystemMaterial = undefined
                  } else if (index == 1) {
                    this.mySystemMaterial = new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT })
                  } else if (index == 2) {
                    this.mySystemMaterial = new uiMaterial.Material({ type: uiMaterial.MaterialType.NONE })
                  }
                })
            }.layoutWeight(1)
            
            Column({ space: 5 }) {
              Text('箭头偏移')
                .fontSize(12)
              Row({ space: 5 }) {
                Button('+')
                  .controlSize(ControlSize.SMALL)
                  .onClick(() => {
                    this.arrowOffset += 10
                  })
                Button('-')
                  .controlSize(ControlSize.SMALL)
                  .onClick(() => {
                    this.arrowOffset -= 10
                  })
                Text(this.arrowOffset.toString())
                  .fontSize(12)
              }
            }.layoutWeight(1)
            
            Column()
              .layoutWeight(1)
          }
        }
        .padding(10)
      }
      .height(180)
      .width('100%')
      .backgroundColor('#F5F5F5')
      
      RelativeContainer() {
        Button('Click Show Menu')
          .alignRules(this.alignRuleArr[this.alignRuleIndex])
          .bindMenu(this.MyMenu, {
            keyboardAvoidMode: this.keyboardAvoidModeArr[this.keyboardAvoidModeIndex],
            minKeyboardAvoidDistance: this.minKeyboardAvoidDistanceArr[this.minKeyboardAvoidDistanceIndex],
            placement: this.menuPlacementArr[this.menuPlacementIndex],
            showInSubWindow: this.showInSubwindowArr[this.showInSubwindowIndex],
            enableArrow: this.enableArrow,
            systemMaterial: this.mySystemMaterial,
            arrowOffset: this.arrowOffset,
          })
          .onClick(() => {
            setTimeout(() => {
              this.attachAndListener()
            }, 2000)
          })
      }
      .height('100%')
      .layoutWeight(1)
      .width('100%')
      .backgroundColor(Color.Pink)
    }
    .height('100%')
    .width('100%')
    .alignItems(HorizontalAlign.Start)
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