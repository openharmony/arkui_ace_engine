/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { memo, __memo_context_type, __memo_id_type, State, MutableState, stateOf, observableProxy } from '@ohos.arkui.stateManagement'
import { Entry, Builder, Color, Text, TextAttribute, Scroll,Column, Row,Component, Button, ButtonAttribute, ClickEvent, UserView, TextStyle, DialogButtonDirection, AlertDialogButtonOptions, List, ListItem, wrapBuilder, Menu, MenuItem, MenuItemOptions, MenuItemGroup, TextInput, ComponentV2} from '@ohos.arkui.component'
import { LevelMode, ImmersiveMode, LevelOrder} from '@ohos.promptAction'
import promptAction from '@ohos.promptAction';
import { Callback, BusinessError } from '@ohos.base';
import { ComponentContent, FrameNode, Frame } from '@ohos.arkui.node';
import { UIContext, OverlayManager, UIInspector, OverlayManagerOptions, PromptAction } from '@ohos.arkui.UIContext'
import { $r } from "@ohos.arkui.component"
import hilog from '@ohos.hilog'
import { BlurStyle, ShadowOptions, ShadowStyle, HoverModeAreaType, Rectangle, TransitionEffect, KeyboardAvoidMode, DismissReason, BackgroundBlurStyleOptions, BackgroundEffectOptions, BlurStyleActivePolicy, ThemeColorMode, AdaptiveColor, ShadowType  } from 'arkui.component.common';
import { DismissDialogAction } from 'arkui.component.actionSheet';
import { AlertDialogParamWithConfirm, AlertDialogParamWithButtons, AlertDialogParamWithOptions,DialogAlignment } from 'arkui.component.alertDialog';
import { WordBreak, DialogButtonStyle, BorderStyle, Alignment, Curve } from 'arkui.component.enums';
import { ActionSheetOptions, ActionSheetButtonOptions } from 'arkui.component.actionSheet';
import { NavPathStack, NavigationOperation, NavBar, Navigation } from 'arkui.component.navigation';
import { ButtonType, ButtonStyleMode, ButtonRole } from 'arkui.component.button';
import { NavDestination } from 'arkui.component.navDestination';
import { Scroller } from 'arkui.component.scroll';
import { ColoringStrategy } from "arkui.component.enums"
import { Size, Position, Edges, LengthMetrics, SizeT } from 'arkui.Graphics';

let contentNode1: ComponentContent<Params2> | undefined = undefined
let contentNode2: ComponentContent<Params2> | undefined = undefined
let dialogController: promptAction.DialogController = new promptAction.DialogController();

class Params1 {
  text: string = ""

  constructor(text: string) {
    this.text = text
  }
}

class Params2 {
  promptAction: PromptAction
  baseUpdateDialogOptions: promptAction.BaseDialogOptions

  constructor(promptAction: PromptAction, baseUpdateDialogOptions: promptAction.BaseDialogOptions) {
    this.promptAction = promptAction
    this.baseUpdateDialogOptions = baseUpdateDialogOptions
  }
}

@Builder
function myBuilder2(params: Params2) {
  Column() {
    Button("change height")
      .margin(10)
      .fontSize(20)
    TextInput().height(50)
    Button("updateCustomDialog")
      .margin(10)
      .fontSize(20)
      .onClick((e: ClickEvent) => {
        console.log('testTag  updateCustomDialog');
        if (contentNode1 !== undefined) {
          params.promptAction.updateCustomDialog(contentNode1!!, params.baseUpdateDialogOptions);
        }
      })
    Button("closeCustomDialog")
      .margin(10)
      .fontSize(20).onClick((e: ClickEvent) => {
      console.log('testTag  closeCustomDialog');
      if (contentNode1 !== undefined) {
        params.promptAction.closeCustomDialog(contentNode1!!);
      }
    })
  }
  .backgroundColor(Color.Red)
  .width('100%')
  .height('50%')
}

@Builder
function myBuilder3(params: Params2) {
  Column() {
    Button("updateCustomDialog")
      .margin(10)
      .fontSize(20)
      .onClick((e: ClickEvent) => {
        console.log('testTag  updateCustomDialog');
        if (contentNode2 !== undefined) {
          params.promptAction.updateCustomDialog(contentNode2!!, params.baseUpdateDialogOptions);
        }
      })
    TextInput().height(50)
    Button("closeCustomDialog")
      .margin(10)
      .fontSize(20)
      .onClick((e: ClickEvent) => {
        if (contentNode2 !== undefined) {
          params.promptAction.closeCustomDialog(contentNode2!!);
        }
      })

    Button("dialogController close")
      .margin(10)
      .fontSize(20).onClick((e: ClickEvent) => {
      dialogController.close();
    })
  }
  .backgroundColor(Color.Red)
  .width('100%')
  .height('50%')
}

@Entry
@Component
struct MyStateSample {
  private uiContext: UIContext = this.getUIContext()
  private promptAction: PromptAction = this.getUIContext().getPromptAction()
  customDialogComponentId: number = 0;
  private contentNode11: ComponentContent<Params1> | undefined = undefined
  private contentNode22: ComponentContent<Params1> | undefined = undefined
  private dialogController11: promptAction.DialogController = new promptAction.DialogController();

  @Builder
  myBuilder4() {
    Column() {
      Button("change option")
        .margin(10)
        .fontSize(20)

      TextInput().height(50)
      Button("closeCustomDialog")
        .margin(10)
        .fontSize(20)
        .onClick((e: ClickEvent) => {
          console.log('testTag  closeCustomDialog');
          this.promptAction.closeCustomDialog(this.customDialogComponentId);
        })

      Button("dialogController close")
        .margin(10)
        .fontSize(20).onClick((e: ClickEvent) => {
        this.dialogController11.close();
      })
    }
    .backgroundColor(Color.Red)
    .width('100%')
    .height('50%')
  }

  baseDialogOptions: promptAction.BaseDialogOptions = {} as promptAction.BaseDialogOptions
  baseUpdateDialogOptions: promptAction.BaseDialogOptions = {
    maskColor: Color.Blue
  } as promptAction.BaseDialogOptions
  dialogOptions: promptAction.DialogOptions = {} as promptAction.DialogOptions
  customDialogOptions: promptAction.CustomDialogOptions = {
    builder: this.myBuilder1
  } as promptAction.CustomDialogOptions
  scroller: Scroller = new Scroller() as Scroller

  build() {
    NavDestination() {
      Column() {
        Scroll(this.scroller) {
          Column() {
            Text(`enableHoverMode`)
              .fontSize(9)
              .width("100%")
            Row() {
              Text(`true`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.enableHoverMode = true
                  this.dialogOptions.enableHoverMode = true
                  this.customDialogOptions.enableHoverMode = true
                })
              Text('false')
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.enableHoverMode = false
                  this.dialogOptions.enableHoverMode = false
                  this.customDialogOptions.enableHoverMode = false
                })
              Text(`undefined`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.enableHoverMode = undefined
                  this.dialogOptions.enableHoverMode = undefined
                  this.customDialogOptions.enableHoverMode = undefined
                })
            }

            Text(`backgroundBlurStyleOptions`)
              .fontSize(9)
              .width("100%")
            Row() {
              Text(`000`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.backgroundBlurStyleOptions = {
                    policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                    inactiveColor: Color.Green,
                    colorMode: ThemeColorMode.DARK,
                    adaptiveColor: AdaptiveColor.DEFAULT,
                    blurOptions: {
                      grayscale: [127, 127]
                    },
                    scale: 1.0
                  } as BackgroundBlurStyleOptions
                  this.dialogOptions.backgroundBlurStyleOptions = {
                    policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                    inactiveColor: Color.Green,
                    colorMode: ThemeColorMode.DARK,
                    adaptiveColor: AdaptiveColor.DEFAULT,
                    blurOptions: {
                      grayscale: [127, 127]
                    },
                    scale: 1.0
                  } as BackgroundBlurStyleOptions
                  this.customDialogOptions.backgroundBlurStyleOptions = {
                    policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                    inactiveColor: Color.Green,
                    colorMode: ThemeColorMode.DARK,
                    adaptiveColor: AdaptiveColor.DEFAULT,
                    blurOptions: {
                      grayscale: [127, 127]
                    },
                    scale: 1.0
                  } as BackgroundBlurStyleOptions
                })
              Text(`111`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.backgroundBlurStyleOptions = {
                    policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                    inactiveColor: Color.Red,
                    colorMode: ThemeColorMode.SYSTEM,
                    adaptiveColor: AdaptiveColor.DEFAULT,
                    blurOptions: {
                      grayscale: [30.4, 30.4]
                    },
                    scale: 0.5
                  } as BackgroundBlurStyleOptions
                  this.dialogOptions.backgroundBlurStyleOptions = {
                    policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                    inactiveColor: Color.Red,
                    colorMode: ThemeColorMode.SYSTEM,
                    adaptiveColor: AdaptiveColor.DEFAULT,
                    blurOptions: {
                      grayscale: [30.4, 30.4]
                    },
                    scale: 0.5
                  } as BackgroundBlurStyleOptions
                  this.customDialogOptions.backgroundBlurStyleOptions = {
                    policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                    inactiveColor: Color.Red,
                    colorMode: ThemeColorMode.SYSTEM,
                    adaptiveColor: AdaptiveColor.DEFAULT,
                    blurOptions: {
                      grayscale: [30.4, 30.4]
                    },
                    scale: 0.5
                  } as BackgroundBlurStyleOptions
                })
              Text(`222`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.backgroundBlurStyleOptions = {
                    policy: BlurStyleActivePolicy.ALWAYS_ACTIVE,
                    inactiveColor: '#330be9d0',
                    colorMode: ThemeColorMode.LIGHT,
                    adaptiveColor: AdaptiveColor.AVERAGE,
                    blurOptions: {
                      grayscale: [0, 127]
                    },
                    scale: 0
                  } as BackgroundBlurStyleOptions
                  this.dialogOptions.backgroundBlurStyleOptions = {
                    policy: BlurStyleActivePolicy.ALWAYS_ACTIVE,
                    inactiveColor: '#330be9d0',
                    colorMode: ThemeColorMode.LIGHT,
                    adaptiveColor: AdaptiveColor.AVERAGE,
                    blurOptions: {
                      grayscale: [0, 127]
                    },
                    scale: 0
                  } as BackgroundBlurStyleOptions
                  this.customDialogOptions.backgroundBlurStyleOptions = {
                    policy: BlurStyleActivePolicy.ALWAYS_ACTIVE,
                    inactiveColor: '#330be9d0',
                    colorMode: ThemeColorMode.LIGHT,
                    adaptiveColor: AdaptiveColor.AVERAGE,
                    blurOptions: {
                      grayscale: [0, 127]
                    },
                    scale: 0
                  } as BackgroundBlurStyleOptions
                })
              Text(`333`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.backgroundBlurStyleOptions = {
                    policy: BlurStyleActivePolicy.ALWAYS_INACTIVE,
                    inactiveColor: $r('app.color.aaa'),
                    colorMode: ThemeColorMode.DARK,
                    adaptiveColor: undefined,
                    blurOptions: {
                      grayscale: [-100, -100]
                    },
                    scale: 1.0
                  } as BackgroundBlurStyleOptions
                  this.dialogOptions.backgroundBlurStyleOptions = {
                    policy: BlurStyleActivePolicy.ALWAYS_INACTIVE,
                    inactiveColor: $r('app.color.aaa'),
                    colorMode: ThemeColorMode.DARK,
                    adaptiveColor: undefined,
                    blurOptions: {
                      grayscale: [-100, -100]
                    },
                    scale: 1.0
                  } as BackgroundBlurStyleOptions
                  this.customDialogOptions.backgroundBlurStyleOptions = {
                    policy: BlurStyleActivePolicy.ALWAYS_INACTIVE,
                    inactiveColor: $r('app.color.aaa'),
                    colorMode: ThemeColorMode.DARK,
                    adaptiveColor: undefined,
                    blurOptions: {
                      grayscale: [-100, -100]
                    },
                    scale: 1.0
                  } as BackgroundBlurStyleOptions
                })
              Text(`444`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.backgroundBlurStyleOptions = {
                    policy: undefined,
                    inactiveColor: 'rgba(23,169,141,0.5)',
                    colorMode: undefined,
                    blurOptions: {
                      grayscale: [1000, 1000]
                    },
                    scale: undefined
                  } as BackgroundBlurStyleOptions
                  this.dialogOptions.backgroundBlurStyleOptions = {
                    policy: undefined,
                    inactiveColor: 'rgba(23,169,141,0.5)',
                    colorMode: undefined,
                    blurOptions: {
                      grayscale: [1000, 1000]
                    },
                    scale: undefined
                  } as BackgroundBlurStyleOptions
                  this.customDialogOptions.backgroundBlurStyleOptions = {
                    policy: undefined,
                    inactiveColor: 'rgba(23,169,141,0.5)',
                    colorMode: undefined,
                    blurOptions: {
                      grayscale: [1000, 1000]
                    },
                    scale: undefined
                  } as BackgroundBlurStyleOptions
                })
              Text(`555`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.backgroundBlurStyleOptions = {
                    inactiveColor: undefined,
                    blurOptions: undefined,
                  } as BackgroundBlurStyleOptions
                  this.dialogOptions.backgroundBlurStyleOptions = {
                    inactiveColor: undefined,
                    blurOptions: undefined,
                  } as BackgroundBlurStyleOptions
                  this.customDialogOptions.backgroundBlurStyleOptions = {
                    inactiveColor: undefined,
                    blurOptions: undefined,
                  } as BackgroundBlurStyleOptions
                })
              Text(`undefined`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.backgroundBlurStyleOptions = undefined
                  this.dialogOptions.backgroundBlurStyleOptions = undefined
                  this.customDialogOptions.backgroundBlurStyleOptions = undefined
                })
            }

            Text(`backgroundEffect`)
              .fontSize(9)
              .width("100%")
            Row() {
              Text(`000`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.backgroundEffect = {
                    radius: 100,
                    saturation: 50,
                    brightness: 100,
                    color: Color.Orange,
                    adaptiveColor: AdaptiveColor.DEFAULT,
                    blurOptions: {
                      grayscale: [127, 127]
                    },
                    policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                    inactiveColor: Color.Green,
                  } as BackgroundEffectOptions
                  this.dialogOptions.backgroundEffect = {
                    radius: 100,
                    saturation: 50,
                    brightness: 100,
                    color: Color.Orange,
                    adaptiveColor: AdaptiveColor.DEFAULT,
                    blurOptions: {
                      grayscale: [127, 127]
                    },
                    policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                    inactiveColor: Color.Green,
                  } as BackgroundEffectOptions
                  this.customDialogOptions.backgroundEffect = {
                    radius: 100,
                    saturation: 50,
                    brightness: 100,
                    color: Color.Orange,
                    adaptiveColor: AdaptiveColor.DEFAULT,
                    blurOptions: {
                      grayscale: [127, 127]
                    },
                    policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                    inactiveColor: Color.Green,
                  } as BackgroundEffectOptions
                })
              Text(`111`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.backgroundEffect = {
                    radius: 60.4,
                    saturation: 15.4,
                    brightness: 1.4,
                    color: Color.Red,
                    adaptiveColor: AdaptiveColor.DEFAULT,
                    blurOptions: {
                      grayscale: [30.4, 30.4]
                    },
                    policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                    inactiveColor: Color.Red,
                  } as BackgroundEffectOptions
                  this.dialogOptions.backgroundEffect = {
                    radius: 60.4,
                    saturation: 15.4,
                    brightness: 1.4,
                    color: Color.Red,
                    adaptiveColor: AdaptiveColor.DEFAULT,
                    blurOptions: {
                      grayscale: [30.4, 30.4]
                    },
                    policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                    inactiveColor: Color.Red,
                  } as BackgroundEffectOptions
                  this.customDialogOptions.backgroundEffect = {
                    radius: 60.4,
                    saturation: 15.4,
                    brightness: 1.4,
                    color: Color.Red,
                    adaptiveColor: AdaptiveColor.DEFAULT,
                    blurOptions: {
                      grayscale: [30.4, 30.4]
                    },
                    policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                    inactiveColor: Color.Red,
                  } as BackgroundEffectOptions
                })
              Text(`222`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.backgroundEffect = {
                    radius: 0,
                    saturation: 0,
                    brightness: 0,
                    color: '#330be9d0',
                    adaptiveColor: AdaptiveColor.AVERAGE,
                    blurOptions: {
                      grayscale: [0, 127]
                    },
                    policy: BlurStyleActivePolicy.ALWAYS_ACTIVE,
                    inactiveColor: '#330be9d0',
                  } as BackgroundEffectOptions
                  this.dialogOptions.backgroundEffect = {
                    radius: 0,
                    saturation: 0,
                    brightness: 0,
                    color: '#330be9d0',
                    adaptiveColor: AdaptiveColor.AVERAGE,
                    blurOptions: {
                      grayscale: [0, 127]
                    },
                    policy: BlurStyleActivePolicy.ALWAYS_ACTIVE,
                    inactiveColor: '#330be9d0',
                  } as BackgroundEffectOptions
                  this.customDialogOptions.backgroundEffect = {
                    radius: 0,
                    saturation: 0,
                    brightness: 0,
                    color: '#330be9d0',
                    adaptiveColor: AdaptiveColor.AVERAGE,
                    blurOptions: {
                      grayscale: [0, 127]
                    },
                    policy: BlurStyleActivePolicy.ALWAYS_ACTIVE,
                    inactiveColor: '#330be9d0',
                  } as BackgroundEffectOptions
                })
              Text(`333`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.backgroundEffect = {
                    radius: -100,
                    saturation: -100,
                    brightness: -100,
                    color: $r('app.color.aaa'),
                    adaptiveColor: undefined,
                    blurOptions: {
                      grayscale: [-100, -100]
                    },
                    policy: BlurStyleActivePolicy.ALWAYS_INACTIVE,
                    inactiveColor: $r('app.color.aaa'),
                  } as BackgroundEffectOptions
                  this.dialogOptions.backgroundEffect = {
                    radius: -100,
                    saturation: -100,
                    brightness: -100,
                    color: $r('app.color.aaa'),
                    adaptiveColor: undefined,
                    blurOptions: {
                      grayscale: [-100, -100]
                    },
                    policy: BlurStyleActivePolicy.ALWAYS_INACTIVE,
                    inactiveColor: $r('app.color.aaa'),
                  } as BackgroundEffectOptions
                  this.customDialogOptions.backgroundEffect = {
                    radius: -100,
                    saturation: -100,
                    brightness: -100,
                    color: $r('app.color.aaa'),
                    adaptiveColor: undefined,
                    blurOptions: {
                      grayscale: [-100, -100]
                    },
                    policy: BlurStyleActivePolicy.ALWAYS_INACTIVE,
                    inactiveColor: $r('app.color.aaa'),
                  } as BackgroundEffectOptions
                })
              Text(`444`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.backgroundEffect = {
                    radius: 10000,
                    saturation: 10000,
                    brightness: 10000,
                    color: 'rgba(23,169,141,0.5)',
                    blurOptions: {
                      grayscale: [1000, 1000]
                    },
                    policy: undefined,
                    inactiveColor: 'rgba(23,169,141,0.5)',
                  } as BackgroundEffectOptions
                  this.dialogOptions.backgroundEffect = {
                    radius: 10000,
                    saturation: 10000,
                    brightness: 10000,
                    color: 'rgba(23,169,141,0.5)',
                    blurOptions: {
                      grayscale: [1000, 1000]
                    },
                    policy: undefined,
                    inactiveColor: 'rgba(23,169,141,0.5)',
                  } as BackgroundEffectOptions
                  this.customDialogOptions.backgroundEffect = {
                    radius: 10000,
                    saturation: 10000,
                    brightness: 10000,
                    color: 'rgba(23,169,141,0.5)',
                    blurOptions: {
                      grayscale: [1000, 1000]
                    },
                    policy: undefined,
                    inactiveColor: 'rgba(23,169,141,0.5)',
                  } as BackgroundEffectOptions
                })
              Text(`555`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.backgroundEffect = {
                    radius: 3,
                    saturation: undefined,
                    brightness: undefined,
                    color: undefined,
                    blurOptions: undefined,
                    inactiveColor: undefined,
                  } as BackgroundEffectOptions
                  this.dialogOptions.backgroundEffect = {
                    radius: 3,
                    saturation: undefined,
                    brightness: undefined,
                    color: undefined,
                    blurOptions: undefined,
                    inactiveColor: undefined,
                  } as BackgroundEffectOptions
                  this.customDialogOptions.backgroundEffect = {
                    radius: 3,
                    saturation: undefined,
                    brightness: undefined,
                    color: undefined,
                    blurOptions: undefined,
                    inactiveColor: undefined,
                  } as BackgroundEffectOptions
                })
              Text(`undefined`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.backgroundEffect = undefined
                  this.dialogOptions.backgroundEffect = undefined
                  this.customDialogOptions.backgroundEffect = undefined
                })
            }

            Text(`levelMode`)
              .fontSize(9)
              .width("100%")
            Row() {
              Text(`OVERLAY`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.levelMode = LevelMode.OVERLAY
                  this.dialogOptions.levelMode = LevelMode.OVERLAY
                  this.customDialogOptions.levelMode = LevelMode.OVERLAY
                })
              Text('EMBEDDED')
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.levelMode = LevelMode.EMBEDDED
                  this.dialogOptions.levelMode = LevelMode.EMBEDDED
                  this.customDialogOptions.levelMode = LevelMode.EMBEDDED
                })
              Text(`undefined`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.levelMode = undefined
                  this.dialogOptions.levelMode = undefined
                  this.customDialogOptions.levelMode = undefined
                })
            }

            Text(`levelUniqueId`)
              .fontSize(9)
              .width("100%")
            Row() {
              Text(`11`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.levelUniqueId = 11
                  this.dialogOptions.levelUniqueId = 11
                  this.customDialogOptions.levelUniqueId = 11
                })
              Text('20')
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.levelUniqueId = 20
                  this.dialogOptions.levelUniqueId = 20
                  this.customDialogOptions.levelUniqueId = 20
                })
              Text(`undefined`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.levelUniqueId = undefined
                  this.dialogOptions.levelUniqueId = undefined
                  this.customDialogOptions.levelUniqueId = undefined
                })
            }

            Text(`immersiveMode`)
              .fontSize(9)
              .width("100%")
            Row() {
              Text(`DEFAULT`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.immersiveMode = ImmersiveMode.DEFAULT
                  this.dialogOptions.immersiveMode = ImmersiveMode.DEFAULT
                  this.customDialogOptions.immersiveMode = ImmersiveMode.DEFAULT
                })
              Text('EXTEND')
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.immersiveMode = ImmersiveMode.EXTEND
                  this.dialogOptions.immersiveMode = ImmersiveMode.EXTEND
                  this.customDialogOptions.immersiveMode = ImmersiveMode.EXTEND
                })
              Text(`undefined`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.immersiveMode = undefined
                  this.dialogOptions.immersiveMode = undefined
                  this.customDialogOptions.immersiveMode = undefined
                })
            }

            Text(`levelOrder`)
              .fontSize(9)
              .width("100%")
            Row() {
              Text(`1000`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.levelOrder = LevelOrder.clamp(1000)
                  this.dialogOptions.levelOrder = LevelOrder.clamp(1000)
                  this.customDialogOptions.levelOrder = LevelOrder.clamp(1000)
                })
              Text('-10001')
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.levelOrder = LevelOrder.clamp(-10001)
                  this.dialogOptions.levelOrder = LevelOrder.clamp(-10001)
                  this.customDialogOptions.levelOrder = LevelOrder.clamp(-10001)
                })
              Text(`undefined`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.levelOrder = undefined
                  this.dialogOptions.levelOrder = undefined
                  this.customDialogOptions.levelOrder = undefined
                })
            }

            Text(`focusable`)
              .fontSize(9)
              .width("100%")
            Row() {
              Text(`true`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.focusable = true
                  this.dialogOptions.focusable = true
                  this.customDialogOptions.focusable = true
                })
              Text(`false`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.focusable = false
                  this.dialogOptions.focusable = false
                  this.customDialogOptions.focusable = false
                })
              Text(`undefined`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseDialogOptions.focusable = undefined
                  this.dialogOptions.focusable = undefined
                  this.customDialogOptions.focusable = undefined
                })
            }

            Text(`CustomDialogOptions	&& DialogOptions`)
              .fontSize(9)
              .width("100%")
            Text(`CustomDialogOptions	&& DialogOptions`)
              .fontSize(9)
              .width("100%")

            Text(`backgroundColor`)
              .fontSize(9)
              .width("100%")
            Row() {
              Text(`Red`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.backgroundColor = Color.Red
                  this.customDialogOptions.backgroundColor = Color.Red
                })
              Text('#330be9d0')
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.backgroundColor = '#330be9d0'
                  this.customDialogOptions.backgroundColor = '#330be9d0'
                })
              Text('资源值')
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.backgroundColor = $r("app.color.aaa")
                  this.customDialogOptions.backgroundColor = $r("app.color.aaa")
                })
              Text(`undefined`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.backgroundColor = undefined
                  this.customDialogOptions.backgroundColor = undefined
                })
            }

            Text(`cornerRadius`)
              .fontSize(9)
              .width("100%")
            Row() {
              Text(`0vp`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.cornerRadius = '0vp'
                  this.customDialogOptions.cornerRadius = '0vp'
                })
              Text(`30%`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.cornerRadius = '30%'
                  this.customDialogOptions.cornerRadius = '30%'
                })
              Text(`第二个`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.cornerRadius = {
                    topLeft: '50px',
                    topRight: '50vp',
                    bottomLeft: $r('app.float.page_text_font_size'),
                    bottomRight: '50%',
                  }
                  this.customDialogOptions.cornerRadius = {
                    topLeft: '50px',
                    topRight: '50vp',
                    bottomLeft: $r('app.float.page_text_font_size'),
                    bottomRight: '50%',
                  }
                })
              Text(`undefined`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.cornerRadius = undefined
                  this.customDialogOptions.cornerRadius = undefined
                })
            }

            Text(`borderWidth`)
              .fontSize(9)
              .width("100%")
            Row() {
              Text(`5vp`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.borderWidth = '5vp'
                  this.customDialogOptions.borderWidth = '5vp'
                })
              Text(`30%`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.borderWidth = '30%'
                  this.customDialogOptions.borderWidth = '30%'
                })
              Text(`第二个`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.borderWidth = {
                    top: '50px',
                    right: '50vp',
                    bottom: $r('app.float.page_text_font_size'),
                    left: '50%',
                  }
                  this.customDialogOptions.borderWidth = {
                    top: '50px',
                    right: '50vp',
                    bottom: $r('app.float.page_text_font_size'),
                    left: '50%',
                  }
                })
              Text(`undefined`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.borderWidth = undefined
                  this.customDialogOptions.borderWidth = undefined
                })
            }

            Text(`borderColor`)
              .fontSize(9)
              .width("100%")
            Row() {
              Text(`Red`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.borderColor = Color.Red
                  this.customDialogOptions.borderColor = Color.Red
                })
              Text('Yellow')
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.borderColor = Color.Yellow
                  this.customDialogOptions.borderColor = Color.Yellow
                })
              Text(`第二个`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.borderColor = {
                    top: Color.Red,
                    right: '#330be9d0',
                    bottom: $r('app.color.aaa'),
                    left: 'rgba(23,169,141,0.5)',
                  }
                  this.customDialogOptions.borderColor = {
                    top: Color.Red,
                    right: '#330be9d0',
                    bottom: $r('app.color.aaa'),
                    left: 'rgba(23,169,141,0.5)',
                  }
                })
              Text(`undefined`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.borderColor = undefined
                  this.customDialogOptions.borderColor = undefined
                })
            }

            Text(`borderStyle`)
              .fontSize(9)
              .width("100%")
            Row() {
              Text(`Dotted`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.borderStyle = BorderStyle.Dotted
                  this.customDialogOptions.borderStyle = BorderStyle.Dotted
                })
              Text('Dashed')
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.borderStyle = BorderStyle.Dashed
                  this.customDialogOptions.borderStyle = BorderStyle.Dashed
                })
              Text(`Solid`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.borderStyle = BorderStyle.Solid
                  this.customDialogOptions.borderStyle = BorderStyle.Solid
                })
              Text('aaa')
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.borderStyle = {
                    top: BorderStyle.Dotted,
                    right: BorderStyle.Dashed,
                    bottom: BorderStyle.Solid,
                    left: undefined
                  }
                  this.customDialogOptions.borderStyle = {
                    top: BorderStyle.Dotted,
                    right: BorderStyle.Dashed,
                    bottom: BorderStyle.Solid,
                    left: undefined
                  }
                })
              Text(`undefined`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.borderStyle = undefined
                  this.customDialogOptions.borderStyle = undefined
                })
            }

            Text(`width`)
              .fontSize(9)
              .width("100%")
            Row() {
              Text(`200vp`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.width = '200vp'
                  this.customDialogOptions.width = '200vp'
                })
              Text(`80%`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.width = '80%'
                  this.customDialogOptions.width = '80%'
                })
              Text(`undefined`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.width = undefined
                  this.customDialogOptions.width = undefined
                })
            }

            Text(`height`)
              .fontSize(9)
              .width("100%")
            Row() {
              Text(`200vp`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.height = '200vp'
                  this.customDialogOptions.height = '200vp'
                })
              Text(`80%`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.height = '80%'
                  this.customDialogOptions.height = '80%'
                })
              Text(`undefined`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.height = undefined
                  this.customDialogOptions.height = undefined
                })
            }

            Text(`shadow`)
              .fontSize(9)
              .width("100%")
            Row() {
              Text(`OUTER_DEFAULT_XS`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.shadow = ShadowStyle.OUTER_DEFAULT_XS
                  this.customDialogOptions.shadow = ShadowStyle.OUTER_DEFAULT_XS
                })
              Text(`OUTER_DEFAULT_SM`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.shadow = ShadowStyle.OUTER_DEFAULT_SM
                  this.customDialogOptions.shadow = ShadowStyle.OUTER_DEFAULT_SM
                })
              Text(`OUTER_DEFAULT_MD`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.shadow = ShadowStyle.OUTER_DEFAULT_MD
                  this.customDialogOptions.shadow = ShadowStyle.OUTER_DEFAULT_MD
                })
            }

            Row() {
              Text(`OUTER_DEFAULT_LG`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.shadow = ShadowStyle.OUTER_DEFAULT_LG
                  this.customDialogOptions.shadow = ShadowStyle.OUTER_DEFAULT_LG
                })
              Text(`OUTER_FLOATING_SM	`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.shadow = ShadowStyle.OUTER_FLOATING_SM
                  this.customDialogOptions.shadow = ShadowStyle.OUTER_FLOATING_SM
                })
              Text(`OUTER_FLOATING_MD`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.shadow = ShadowStyle.OUTER_FLOATING_MD
                  this.customDialogOptions.shadow = ShadowStyle.OUTER_FLOATING_MD
                })
            }

            Row() {
              Text('ShadowOptions1')
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.shadow = {
                    radius: 10,
                  }
                  this.customDialogOptions.shadow = {
                    radius: 10,
                  }
                })
              Text('ShadowOptions2')
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.shadow = {
                    radius: 10,
                    type: ShadowType.BLUR,
                    color: $r('app.color.aaa'),
                    offsetX: 22,
                    offsetY: $r('app.float.ccc'),
                    fill: true,
                  }
                  this.customDialogOptions.shadow = {
                    radius: 10,
                    type: ShadowType.BLUR,
                    color: $r('app.color.aaa'),
                    offsetX: 22,
                    offsetY: $r('app.float.ccc'),
                    fill: true,
                  }
                })
              Text(`undefined`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.dialogOptions.shadow = undefined
                  this.customDialogOptions.shadow = undefined
                })
            }

            Text(`updateCustomDialog`)
              .fontSize(9)
              .width("100%")
            Text(`updateCustomDialog`)
              .fontSize(9)
              .width("100%")
            Text(`maskRect`)
              .fontSize(9)
              .width("100%")
            Row() {
              Text(`0%`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseUpdateDialogOptions.maskRect = {
                    x: 0,
                    y: 0,
                    width: '0%',
                    height: '0%'
                  }
                })
              Text(`50%`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseUpdateDialogOptions.maskRect = {
                    x: 50,
                    y: 50,
                    width: '50%',
                    height: '50%'
                  }
                })
              Text(`undefined`)
                .fontSize(10)
                .backgroundColor(0x0000ff)
                .fontColor(0xffffff)
                .padding(5)
                .onClick((e: ClickEvent) => {
                  this.baseUpdateDialogOptions.maskRect = undefined
                })
            }
          }

          Row() {
            Text(`CenterStart`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.alignment = DialogAlignment.CenterStart
              })
            Text(`CenterEnd`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.alignment = DialogAlignment.CenterEnd
              })
            Text(`BottomStart`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.alignment = DialogAlignment.BottomStart
              })
            Text(`BottomEnd`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.alignment = DialogAlignment.BottomEnd
              })
            Text(`undefined`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.alignment = undefined
              })
          }

          Text(`offset`)
            .fontSize(9)
            .width("100%")
          Row() {
            Text(`40vp`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.offset = { dx: 40, dy: 40 }
              })
            Text(`aaa`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.offset = { dx: $r("app.float.aaa"), dy: '30%' }
              })
            Text(`bbb`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.offset = { dx: '30%', dy: $r("app.float.bbb") }
              })
            Text(`undefined`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.offset = undefined
              })
          }

          Text(`isModal`)
            .fontSize(9)
            .width("100%")
          Row() {
            Text(`true`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.isModal = true
              })
            Text(`false`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.isModal = false
              })
            Text(`undefined`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.isModal = undefined
              })
          }

          Text(`showInSubWindow`)
            .fontSize(9)
            .width("100%")
          Row() {
            Text(`true`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.showInSubWindow = true
              })
            Text(`false`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.showInSubWindow = false
              })
            Text(`undefined`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.showInSubWindow = undefined
              })
          }

          Text(`onWillDismiss`)
            .fontSize(9)
            .width("100%")
          Row() {
            Text(`onWillDismiss`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.onWillDismiss = (dismissDialogAction: DismissDialogAction) => {
                  console.info("shjb+reason=" + JSON.stringify(dismissDialogAction.reason));
                  console.info("shjb+dialog onWillDismiss");
                  if (dismissDialogAction.reason === DismissReason.PRESS_BACK) {
                    console.info("shjb1+dialog onWillDismiss");
                    dismissDialogAction.dismiss();
                  }
                  if (dismissDialogAction.reason === DismissReason.TOUCH_OUTSIDE) {
                    console.info("shjb2+dialog onWillDismiss");
                    dismissDialogAction.dismiss();
                  }
                }
              })
            Text(`undefined`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.onWillDismiss = undefined
              })
          }

          Text(`autoCancel`)
            .fontSize(9)
            .width("100%")
          Row() {
            Text(`true`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.autoCancel = true
              })
            Text(`false`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.autoCancel = false
              })
            Text(`undefined`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.autoCancel = undefined
              })
          }

          Text(`maskColor`)
            .fontSize(9)
            .width("100%")
          Row() {
            Text(`Red`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.maskColor = Color.Red
              })
            Text('#330be9d0')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.maskColor = '#330be9d0'
              })
            Text('资源值')
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.maskColor = $r("app.color.aaa")
              })
            Text(`undefined`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.maskColor = undefined
              })
          }

          Text(`transition`)
            .fontSize(9)
            .width("100%")
          Row() {
            Text(`aaa`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.transition = TransitionEffect.asymmetric(
                  TransitionEffect.OPACITY.animation({ duration: 3000, curve: Curve.Sharp })
                    .combine(TransitionEffect.scale({ x: 1.5, y: 1.5 })
                      .animation({ duration: 3000, curve: Curve.Sharp })),
                  TransitionEffect.OPACITY.animation({ duration: 100, curve: Curve.Smooth })
                    .combine(TransitionEffect.scale({ x: 0.5, y: 0.5 })
                      .animation({ duration: 100, curve: Curve.Smooth })))
              })
            Text(`bbb`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.transition =
                  TransitionEffect.scale({ x: 1, y: 0 }).animation({ duration: 3000, curve: Curve.Ease })
              })
            Text(`ccc`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.transition =
                  TransitionEffect.OPACITY.animation({ duration: 4000, curve: Curve.Ease })
                    .combine(TransitionEffect.rotate({ z: 1, angle: 180 }))
              })
            Text(`undefined`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.transition = undefined
              })
          }

          Text(`dialogTransition`)
            .fontSize(9)
            .width("100%")
          Row() {
            Text(`aaa`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.dialogTransition = TransitionEffect.asymmetric(
                  TransitionEffect.OPACITY.animation({ duration: 3000, curve: Curve.Sharp })
                    .combine(TransitionEffect.scale({ x: 1.5, y: 1.5 })
                      .animation({ duration: 3000, curve: Curve.Sharp })),
                  TransitionEffect.OPACITY.animation({ duration: 100, curve: Curve.Smooth })
                    .combine(TransitionEffect.scale({ x: 0.5, y: 0.5 })
                      .animation({ duration: 100, curve: Curve.Smooth })))
              })
            Text(`bbb`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.dialogTransition =
                  TransitionEffect.scale({ x: 1, y: 0 }).animation({ duration: 3000, curve: Curve.Ease })
              })
            Text(`ccc`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.dialogTransition =
                  TransitionEffect.OPACITY.animation({ duration: 4000, curve: Curve.Ease })
                    .combine(TransitionEffect.rotate({ z: 1, angle: 180 }))
              })
            Text(`undefined`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.dialogTransition = undefined
              })
          }

          Text(`maskTransition`)
            .fontSize(9)
            .width("100%")
          Row() {
            Text(`aaa`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.maskTransition = TransitionEffect.asymmetric(
                  TransitionEffect.OPACITY.animation({ duration: 3000, curve: Curve.Sharp })
                    .combine(TransitionEffect.scale({ x: 1.5, y: 1.5 })
                      .animation({ duration: 3000, curve: Curve.Sharp })),
                  TransitionEffect.OPACITY.animation({ duration: 100, curve: Curve.Smooth })
                    .combine(TransitionEffect.scale({ x: 0.5, y: 0.5 })
                      .animation({ duration: 100, curve: Curve.Smooth })))
              })
            Text(`bbb`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.maskTransition =
                  TransitionEffect.scale({ x: 1, y: 0 }).animation({ duration: 3000, curve: Curve.Ease })
              })
            Text(`ccc`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.maskTransition =
                  TransitionEffect.OPACITY.animation({ duration: 4000, curve: Curve.Ease })
                    .combine(TransitionEffect.rotate({ z: 1, angle: 180 }))
              })
            Text(`undefined`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.maskTransition = undefined
              })
          }

          Text(`onWillAppear`)
            .fontSize(9)
            .width("100%")
          Row() {
            Text(`onWillAppear`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.onWillAppear = () => {
                  console.info("shjb+dialog update onWillAppear");
                }
              })
            Text(`undefined`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.onWillAppear = undefined
              })
          }

          Text(`onDidAppear`)
            .fontSize(9)
            .width("100%")
          Row() {
            Text(`onDidAppear`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.onDidAppear = () => {
                  console.info("shjb+dialog update onDidAppear");
                }
              })
            Text(`undefined`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.onDidAppear = undefined
              })
          }

          Text(`onWillDisappear`)
            .fontSize(9)
            .width("100%")
          Row() {
            Text(`onWillDisappear`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.onWillDisappear = () => {
                  console.info("shjb+dialog update onWillDisappear");
                }
              })
            Text(`undefined`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.onWillDisappear = undefined
              })
          }

          Text(`onDidDisappear`)
            .fontSize(9)
            .width("100%")
          Row() {
            Text(`onDidDisappear`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.onDidDisappear = () => {
                  console.info("shjb+dialog update onDidDisappear");
                }
              })
            Text(`undefined`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.onDidDisappear = undefined
              })
          }

          Text(`keyboardAvoidMode`)
            .fontSize(9)
            .width("100%")
          Row() {
            Text(`true`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.keyboardAvoidMode = KeyboardAvoidMode.DEFAULT
              })
            Text(`false`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.keyboardAvoidMode = KeyboardAvoidMode.NONE
              })
            Text(`undefined`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.keyboardAvoidMode = undefined
              })
          }

          Text(`keyboardAvoidDistance`)
            .fontSize(9)
            .width("100%")
          Row() {
            Text(`50px`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.keyboardAvoidDistance = LengthMetrics.px(50)
              })
            Text(`50vp`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.keyboardAvoidDistance = LengthMetrics.vp(50)
              })
            Text(`50fp`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.keyboardAvoidDistance =
                  LengthMetrics.resource($r('app.float.page_text_font_size'))
              })
            Text(`50%`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.keyboardAvoidDistance = LengthMetrics.percent(0.5)
              })
            Text(`undefined`)
              .fontSize(10)
              .backgroundColor(0x0000ff)
              .fontColor(0xffffff)
              .padding(5)
              .onClick((e: ClickEvent) => {
                this.baseUpdateDialogOptions.keyboardAvoidDistance = undefined
              })
          }
        }
      }
    }

  }.borderWidth(1.0)
  .padding(10)
  .width("100%")
  .backgroundColor(Color.Pink)
}