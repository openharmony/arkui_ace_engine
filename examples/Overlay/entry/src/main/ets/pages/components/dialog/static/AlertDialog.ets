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

'use static'

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

@Entry
@Component
struct AlertDialogSample {
  alertDialogParamWithConfirm: AlertDialogParamWithConfirm = {
    message: 'text',
  } as AlertDialogParamWithConfirm
  alertDialogParamWithButtons: AlertDialogParamWithButtons = {
    message: 'text',
    primaryButton: {
      value: '确定',
      action: () => {
        console.info('shjb+primaryButton');
      }
    },
    secondaryButton: {
      value: '取消',
      action: () => {
        console.info('shjb+secondaryButton');
      }
    },
  } as AlertDialogParamWithButtons
  alertDialogParamWithOptions: AlertDialogParamWithOptions = {
    buttons: new Array<AlertDialogButtonOptions>(
      {
        value: '确定',
        action: () => {
          console.info('shjb+确定');
        }
      } as AlertDialogButtonOptions,
      {
        value: '取消',
        action: () => {
          console.info('shjb+取消');
        }
      } as AlertDialogButtonOptions,
      {
        value: '确定取消',
        action: () => {
          console.info('shjb+确定取消');
        }
      } as AlertDialogButtonOptions,
      {
        value: '取消确定',
        action: () => {
          console.info('shjb+取消确定');
        }
      } as AlertDialogButtonOptions,
    ),
    message: 'text',
  } as AlertDialogParamWithOptions
  scroller: Scroller = new Scroller() as Scroller

  build() {
    NavDestination() {
      Column() {
        Column() {
          Text(`showAlertDialog with AlertDialogParamWithConfirm`)
            .fontSize(15)
            .backgroundColor(Color.Orange)
            .margin(3)
            .padding(3)
            .borderWidth(1.0)
            .onClick((e: ClickEvent) => {
              this.getUIContext().showAlertDialog(
                this.alertDialogParamWithConfirm
              )
            })
          Text(`showAlertDialog with AlertDialogParamWithButtons`)
            .fontSize(15)
            .backgroundColor(Color.Orange)
            .margin(3)
            .padding(3)
            .borderWidth(1.0)
            .onClick((e: ClickEvent) => {
              this.getUIContext().showAlertDialog(
                this.alertDialogParamWithButtons
              )
            })
          Text(`showAlertDialog with AlertDialogParamWithOptions`)
            .fontSize(15)
            .backgroundColor(Color.Orange)
            .margin(3)
            .padding(3)
            .borderWidth(1.0)
            .onClick((e: ClickEvent) => {
              this.getUIContext().showAlertDialog(
                this.alertDialogParamWithOptions
              )
            })
        }.borderWidth(1.0)
        .padding(10)
        .width("100%")
        .backgroundColor(Color.Pink)

        Scroll(this.scroller) {
          Column() {
            Column() {
              Text(`AlertDialogParamWithOptions`)
                .fontSize(9)
                .width("100%")
              Text(`AlertDialogParamWithOptions`)
                .fontSize(9)
                .width("100%")
              Text(`buttonDirection`)
                .fontSize(9)
                .width("100%")
              Row() {
                Text(`AUTO`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithOptions.buttonDirection = DialogButtonDirection.AUTO
                  })
                Text(`HORIZONTAL`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithOptions.buttonDirection = DialogButtonDirection.HORIZONTAL
                  })
                Text(`VERTICAL`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithOptions.buttonDirection = DialogButtonDirection.VERTICAL
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithOptions.buttonDirection = undefined
                  })
              }

              Text(`primary`)
                .fontSize(9)
                .width("100%")
              Row() {
                Text(`aaa`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithOptions.buttons[0].primary = true
                    this.alertDialogParamWithOptions.buttons[1].primary = true
                    this.alertDialogParamWithOptions.buttons[2].primary = true
                    this.alertDialogParamWithOptions.buttons[3].primary = true
                  })
                Text(`bbb`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithOptions.buttons[0].primary = false
                    this.alertDialogParamWithOptions.buttons[1].primary = false
                    this.alertDialogParamWithOptions.buttons[2].primary = false
                    this.alertDialogParamWithOptions.buttons[3].primary = false
                  })
                Text(`ccc`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithOptions.buttons[0].primary = true
                    this.alertDialogParamWithOptions.buttons[1].primary = undefined
                    this.alertDialogParamWithOptions.buttons[2].primary = undefined
                    this.alertDialogParamWithOptions.buttons[3].primary = undefined
                  })
                Text(`ddd`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithOptions.buttons[0].primary = false
                    this.alertDialogParamWithOptions.buttons[1].primary = false
                    this.alertDialogParamWithOptions.buttons[2].primary = true
                    this.alertDialogParamWithOptions.buttons[3].primary = false
                  })
                Text(`eee`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithOptions.buttons[0].primary = true
                    this.alertDialogParamWithOptions.buttons[1].primary = false
                    this.alertDialogParamWithOptions.buttons[2].primary = false
                    this.alertDialogParamWithOptions.buttons[3].primary = true
                  })
                Text(`fff`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithOptions.buttons[0].primary = undefined
                    this.alertDialogParamWithOptions.buttons[1].primary = undefined
                    this.alertDialogParamWithOptions.buttons[2].primary = undefined
                    this.alertDialogParamWithOptions.buttons[3].primary = undefined
                  })
              }

              Text(`AlertDialogParamWithOptions && AlertDialogParamWithButtons`)
                .fontSize(9)
                .width("100%")
              Text(`AlertDialogParamWithOptions && AlertDialogParamWithButtons`)
                .fontSize(9)
                .width("100%")
              Text(`enabled`)
                .fontSize(9)
                .width("100%")
              Row() {
                Text(`true`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithOptions.buttons[0].enabled = true
                    this.alertDialogParamWithOptions.buttons[1].enabled = true
                    this.alertDialogParamWithOptions.buttons[2].enabled = true
                    this.alertDialogParamWithOptions.buttons[3].enabled = true
                    this.alertDialogParamWithButtons.primaryButton.enabled = true
                    this.alertDialogParamWithButtons.secondaryButton.enabled = true
                  })
                Text(`false`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithOptions.buttons[0].enabled = false
                    this.alertDialogParamWithOptions.buttons[1].enabled = false
                    this.alertDialogParamWithOptions.buttons[2].enabled = false
                    this.alertDialogParamWithOptions.buttons[3].enabled = false
                    this.alertDialogParamWithButtons.primaryButton.enabled = false
                    this.alertDialogParamWithButtons.secondaryButton.enabled = false
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithOptions.buttons[0].enabled = undefined
                    this.alertDialogParamWithOptions.buttons[1].enabled = undefined
                    this.alertDialogParamWithOptions.buttons[2].enabled = undefined
                    this.alertDialogParamWithOptions.buttons[3].enabled = undefined
                    this.alertDialogParamWithButtons.primaryButton.enabled = undefined
                    this.alertDialogParamWithButtons.secondaryButton.enabled = undefined
                  })
              }

              Text(`defaultFocus`)
                .fontSize(9)
                .width("100%")
              Row() {
                Text(`true`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithOptions.buttons[0].defaultFocus = true
                    this.alertDialogParamWithOptions.buttons[1].defaultFocus = true
                    this.alertDialogParamWithOptions.buttons[2].defaultFocus = true
                    this.alertDialogParamWithOptions.buttons[3].defaultFocus = true
                    this.alertDialogParamWithButtons.primaryButton.defaultFocus = true
                    this.alertDialogParamWithButtons.secondaryButton.defaultFocus = true
                  })
                Text(`false`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithOptions.buttons[0].defaultFocus = false
                    this.alertDialogParamWithOptions.buttons[1].defaultFocus = false
                    this.alertDialogParamWithOptions.buttons[2].defaultFocus = false
                    this.alertDialogParamWithOptions.buttons[3].defaultFocus = false
                    this.alertDialogParamWithButtons.primaryButton.defaultFocus = false
                    this.alertDialogParamWithButtons.secondaryButton.defaultFocus = false
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithOptions.buttons[0].defaultFocus = undefined
                    this.alertDialogParamWithOptions.buttons[1].defaultFocus = undefined
                    this.alertDialogParamWithOptions.buttons[2].defaultFocus = undefined
                    this.alertDialogParamWithOptions.buttons[3].defaultFocus = undefined
                    this.alertDialogParamWithButtons.primaryButton.defaultFocus = undefined
                    this.alertDialogParamWithButtons.secondaryButton.defaultFocus = undefined
                  })
              }

              Text(`style`)
                .fontSize(9)
                .width("100%")
              Row() {
                Text(`DEFAULT`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithOptions.buttons[0].style = DialogButtonStyle.DEFAULT
                    this.alertDialogParamWithOptions.buttons[1].style = DialogButtonStyle.DEFAULT
                    this.alertDialogParamWithOptions.buttons[2].style = DialogButtonStyle.DEFAULT
                    this.alertDialogParamWithOptions.buttons[3].style = DialogButtonStyle.DEFAULT
                    this.alertDialogParamWithButtons.primaryButton.style = DialogButtonStyle.DEFAULT
                    this.alertDialogParamWithButtons.secondaryButton.style = DialogButtonStyle.DEFAULT
                  })
                Text(`HIGHLIGHT`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithOptions.buttons[0].style = DialogButtonStyle.HIGHLIGHT
                    this.alertDialogParamWithOptions.buttons[1].style = DialogButtonStyle.HIGHLIGHT
                    this.alertDialogParamWithOptions.buttons[2].style = DialogButtonStyle.HIGHLIGHT
                    this.alertDialogParamWithOptions.buttons[3].style = DialogButtonStyle.HIGHLIGHT
                    this.alertDialogParamWithButtons.primaryButton.style = DialogButtonStyle.HIGHLIGHT
                    this.alertDialogParamWithButtons.secondaryButton.style = DialogButtonStyle.HIGHLIGHT
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithOptions.buttons[0].style = undefined
                    this.alertDialogParamWithOptions.buttons[1].style = undefined
                    this.alertDialogParamWithOptions.buttons[2].style = undefined
                    this.alertDialogParamWithOptions.buttons[3].style = undefined
                    this.alertDialogParamWithButtons.primaryButton.style = undefined
                    this.alertDialogParamWithButtons.secondaryButton.style = undefined
                  })
              }

              Text(`value`)
                .fontSize(9)
                .width("100%")
              Row() {
                Text(`ccc`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithOptions.buttons[0].value =
                      $r("app.string.AlertDialog_title")
                    this.alertDialogParamWithOptions.buttons[1].value =
                      $r("app.string.AlertDialog_title")
                    this.alertDialogParamWithOptions.buttons[2].value =
                      $r("app.string.AlertDialog_title")
                    this.alertDialogParamWithOptions.buttons[3].value =
                      $r("app.string.AlertDialog_title")
                    this.alertDialogParamWithButtons.primaryButton.value =
                      $r("app.string.AlertDialog_title")
                    this.alertDialogParamWithButtons.secondaryButton.value =
                      $r("app.string.AlertDialog_title")
                  })
              }

              Text(`fontColor`)
                .fontSize(9)
                .width("100%")
              Row() {
                Text(`Red`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithOptions.buttons[0].fontColor = Color.Red
                    this.alertDialogParamWithOptions.buttons[1].fontColor = Color.Red
                    this.alertDialogParamWithOptions.buttons[2].fontColor = Color.Red
                    this.alertDialogParamWithOptions.buttons[3].fontColor = Color.Red
                    this.alertDialogParamWithButtons.primaryButton.fontColor = Color.Red
                    this.alertDialogParamWithButtons.secondaryButton.fontColor = Color.Red
                  })
                Text(`Green`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithOptions.buttons[0].fontColor = Color.Green
                    this.alertDialogParamWithOptions.buttons[1].fontColor = Color.Green
                    this.alertDialogParamWithOptions.buttons[2].fontColor = Color.Green
                    this.alertDialogParamWithOptions.buttons[3].fontColor = Color.Green
                    this.alertDialogParamWithButtons.primaryButton.fontColor = Color.Green
                    this.alertDialogParamWithButtons.secondaryButton.fontColor = Color.Green
                  })
                Text(`资源值`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithOptions.buttons[0].fontColor = $r("app.color.Color_pink")
                    this.alertDialogParamWithOptions.buttons[1].fontColor = $r("app.color.Color_pink")
                    this.alertDialogParamWithOptions.buttons[2].fontColor = $r("app.color.Color_pink")
                    this.alertDialogParamWithOptions.buttons[3].fontColor = $r("app.color.Color_pink")
                    this.alertDialogParamWithButtons.primaryButton.fontColor = $r("app.color.Color_pink")
                    this.alertDialogParamWithButtons.secondaryButton.fontColor = $r("app.color.Color_pink")
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithOptions.buttons[0].fontColor = undefined
                    this.alertDialogParamWithOptions.buttons[1].fontColor = undefined
                    this.alertDialogParamWithOptions.buttons[2].fontColor = undefined
                    this.alertDialogParamWithOptions.buttons[3].fontColor = undefined
                    this.alertDialogParamWithButtons.primaryButton.fontColor = undefined
                    this.alertDialogParamWithButtons.secondaryButton.fontColor = undefined
                  })
              }

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
                    this.alertDialogParamWithOptions.buttons[0].backgroundColor = Color.Red
                    this.alertDialogParamWithOptions.buttons[1].backgroundColor = Color.Red
                    this.alertDialogParamWithOptions.buttons[2].backgroundColor = Color.Red
                    this.alertDialogParamWithOptions.buttons[3].backgroundColor = Color.Red
                    this.alertDialogParamWithButtons.primaryButton.backgroundColor = Color.Red
                    this.alertDialogParamWithButtons.secondaryButton.backgroundColor = Color.Red
                  })
                Text(`Green`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithOptions.buttons[0].backgroundColor = Color.Green
                    this.alertDialogParamWithOptions.buttons[1].backgroundColor = Color.Green
                    this.alertDialogParamWithOptions.buttons[2].backgroundColor = Color.Green
                    this.alertDialogParamWithOptions.buttons[3].backgroundColor = Color.Green
                    this.alertDialogParamWithButtons.primaryButton.backgroundColor = Color.Green
                    this.alertDialogParamWithButtons.secondaryButton.backgroundColor = Color.Green
                  })
                Text(`资源值`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithOptions.buttons[0].backgroundColor = $r("app.color.Color_pink")
                    this.alertDialogParamWithOptions.buttons[1].backgroundColor = $r("app.color.Color_pink")
                    this.alertDialogParamWithOptions.buttons[2].backgroundColor = $r("app.color.Color_pink")
                    this.alertDialogParamWithOptions.buttons[3].backgroundColor = $r("app.color.Color_pink")
                    this.alertDialogParamWithButtons.primaryButton.backgroundColor = $r("app.color.Color_pink")
                    this.alertDialogParamWithButtons.secondaryButton.backgroundColor = $r("app.color.Color_pink")
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithOptions.buttons[0].backgroundColor = undefined
                    this.alertDialogParamWithOptions.buttons[1].backgroundColor = undefined
                    this.alertDialogParamWithOptions.buttons[2].backgroundColor = undefined
                    this.alertDialogParamWithOptions.buttons[3].backgroundColor = undefined
                    this.alertDialogParamWithButtons.primaryButton.backgroundColor = undefined
                    this.alertDialogParamWithButtons.secondaryButton.backgroundColor = undefined
                  })
              }

              Text(`action`)
                .fontSize(9)
                .width("100%")
              Row() {
                Text(`shjb1`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithOptions.buttons[0].action = () => {
                      console.info('shjb+确定1');
                    }
                    this.alertDialogParamWithOptions.buttons[1].action = () => {
                      console.info('shjb+取消1');
                    }
                    this.alertDialogParamWithOptions.buttons[2].action = () => {
                      console.info('shjb+确定取消1');
                    }
                    this.alertDialogParamWithOptions.buttons[3].action = () => {
                      console.info('shjb+取消确定1');
                    }
                    this.alertDialogParamWithButtons.primaryButton.action = () => {
                      console.info('shjb+primaryButton1');
                    }
                    this.alertDialogParamWithButtons.secondaryButton.action = () => {
                      console.info('shjb+secondaryButton1');
                    }
                  })
              }

              Text(`AlertDialogParamWithOptions && AlertDialogParamWithButtons && AlertDialogParamWithConfirm`)
                .fontSize(9)
                .width("100%")
              Text(`AlertDialogParamWithOptions && AlertDialogParamWithButtons && AlertDialogParamWithConfirm`)
                .fontSize(9)
                .width("100%")
              Text(`title`)
                .fontSize(9)
                .width("100%")
              Row() {
                Text(`aaa`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.title = 'aaa'
                    this.alertDialogParamWithButtons.title = 'aaa'
                    this.alertDialogParamWithOptions.title = 'aaa'
                  })
                Text(`bbb`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.title = 'bbb'
                    this.alertDialogParamWithButtons.title = 'bbb'
                    this.alertDialogParamWithOptions.title = 'bbb'
                  })
                Text(`ccc`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.title = $r("app.string.AlertDialog_title")
                    this.alertDialogParamWithButtons.title = $r("app.string.AlertDialog_title")
                    this.alertDialogParamWithOptions.title = $r("app.string.AlertDialog_title")
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.title = undefined
                    this.alertDialogParamWithButtons.title = undefined
                    this.alertDialogParamWithOptions.title = undefined
                  })
              }

              Text(`subtitle`)
                .fontSize(9)
                .width("100%")
              Row() {
                Text(`aaa`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.subtitle = 'aaa'
                    this.alertDialogParamWithButtons.subtitle = 'aaa'
                    this.alertDialogParamWithOptions.subtitle = 'aaa'
                  })
                Text(`bbb`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.subtitle = 'bbb'
                    this.alertDialogParamWithButtons.subtitle = 'bbb'
                    this.alertDialogParamWithOptions.subtitle = 'bbb'
                  })
                Text(`ccc`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.subtitle = $r("app.string.AlertDialog_title")
                    this.alertDialogParamWithButtons.subtitle = $r("app.string.AlertDialog_title")
                    this.alertDialogParamWithOptions.subtitle = $r("app.string.AlertDialog_title")
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.subtitle = undefined
                    this.alertDialogParamWithButtons.subtitle = undefined
                    this.alertDialogParamWithOptions.subtitle = undefined
                  })
              }

              Text(`message`)
                .fontSize(9)
                .width("100%")
              Row() {
                Text(`aaa`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.message = 'aaa'
                    this.alertDialogParamWithButtons.message = 'aaa'
                    this.alertDialogParamWithOptions.message = 'aaa'
                  })
                Text(`bbb`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.message = 'bbb'
                    this.alertDialogParamWithButtons.message = 'bbb'
                    this.alertDialogParamWithOptions.message = 'bbb'
                  })
                Text(`ccc`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.message = $r("app.string.AlertDialog_message")
                    this.alertDialogParamWithButtons.message = $r("app.string.AlertDialog_message")
                    this.alertDialogParamWithOptions.message = $r("app.string.AlertDialog_message")
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
                    this.alertDialogParamWithConfirm.autoCancel = true
                    this.alertDialogParamWithButtons.autoCancel = true
                    this.alertDialogParamWithOptions.autoCancel = true
                  })
                Text(`false`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.autoCancel = false
                    this.alertDialogParamWithButtons.autoCancel = false
                    this.alertDialogParamWithOptions.autoCancel = false
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.autoCancel = undefined
                    this.alertDialogParamWithButtons.autoCancel = undefined
                    this.alertDialogParamWithOptions.autoCancel = undefined
                  })
              }

              Text(`cancel`)
                .fontSize(9)
                .width("100%")
              Row() {
                Text(`logshjb`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.cancel = () => {
                      console.log('shjb');
                    }
                    this.alertDialogParamWithButtons.cancel = () => {
                      console.log('shjb');
                    }
                    this.alertDialogParamWithOptions.cancel = () => {
                      console.log('shjb');
                    }
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.cancel = undefined
                    this.alertDialogParamWithButtons.cancel = undefined
                    this.alertDialogParamWithOptions.cancel = undefined
                  })
              }

              Text(`alignment`)
                .fontSize(9)
                .width("100%")
              Row() {
                Text(`Top`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.alignment = DialogAlignment.Top
                    this.alertDialogParamWithButtons.alignment = DialogAlignment.Top
                    this.alertDialogParamWithOptions.alignment = DialogAlignment.Top
                  })
                Text(`Center`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.alignment = DialogAlignment.Center
                    this.alertDialogParamWithButtons.alignment = DialogAlignment.Center
                    this.alertDialogParamWithOptions.alignment = DialogAlignment.Center
                  })
                Text(`Bottom`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.alignment = DialogAlignment.Bottom
                    this.alertDialogParamWithButtons.alignment = DialogAlignment.Bottom
                    this.alertDialogParamWithOptions.alignment = DialogAlignment.Bottom
                  })
                Text(`Default`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.alignment = DialogAlignment.Default
                    this.alertDialogParamWithButtons.alignment = DialogAlignment.Default
                    this.alertDialogParamWithOptions.alignment = DialogAlignment.Default
                  })
                Text(`TopStart`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.alignment = DialogAlignment.TopStart
                    this.alertDialogParamWithButtons.alignment = DialogAlignment.TopStart
                    this.alertDialogParamWithOptions.alignment = DialogAlignment.TopStart
                  })
                Text(`TopEnd`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.alignment = DialogAlignment.TopEnd
                    this.alertDialogParamWithButtons.alignment = DialogAlignment.TopEnd
                    this.alertDialogParamWithOptions.alignment = DialogAlignment.TopEnd
                  })
              }

              Row() {
                Text(`CenterStart`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.alignment = DialogAlignment.CenterStart
                    this.alertDialogParamWithButtons.alignment = DialogAlignment.CenterStart
                    this.alertDialogParamWithOptions.alignment = DialogAlignment.CenterStart
                  })
                Text(`CenterEnd`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.alignment = DialogAlignment.CenterEnd
                    this.alertDialogParamWithButtons.alignment = DialogAlignment.CenterEnd
                    this.alertDialogParamWithOptions.alignment = DialogAlignment.CenterEnd
                  })
                Text(`BottomStart`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.alignment = DialogAlignment.BottomStart
                    this.alertDialogParamWithButtons.alignment = DialogAlignment.BottomStart
                    this.alertDialogParamWithOptions.alignment = DialogAlignment.BottomStart
                  })
                Text(`BottomEnd`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.alignment = DialogAlignment.BottomEnd
                    this.alertDialogParamWithButtons.alignment = DialogAlignment.BottomStart
                    this.alertDialogParamWithOptions.alignment = DialogAlignment.BottomEnd
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.alignment = undefined
                    this.alertDialogParamWithButtons.alignment = undefined
                    this.alertDialogParamWithOptions.alignment = undefined
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
                    this.alertDialogParamWithConfirm.offset = { dx: 40, dy: 40 }
                    this.alertDialogParamWithButtons.offset = { dx: 40, dy: 40 }
                    this.alertDialogParamWithOptions.offset = { dx: 40, dy: 40 }
                  })
                Text(`aaa`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.offset = { dx: $r("app.float.float_3"), dy: '30%' }
                    this.alertDialogParamWithButtons.offset = { dx: $r("app.float.float_3"), dy: '30%' }
                    this.alertDialogParamWithOptions.offset = { dx: $r("app.float.float_3"), dy: '30%' }
                  })
                Text(`bbb`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.offset = { dx: '30%', dy: $r("app.float.float_9") }
                    this.alertDialogParamWithButtons.offset = { dx: '30%', dy: $r("app.float.float_9") }
                    this.alertDialogParamWithOptions.offset = { dx: '30%', dy: $r("app.float.float_9") }
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.offset = undefined
                    this.alertDialogParamWithButtons.offset = undefined
                    this.alertDialogParamWithOptions.offset = undefined
                  })
              }

              Text(`gridCount`)
                .fontSize(9)
                .width("100%")
              Row() {
                Text(`1`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.gridCount = 1
                    this.alertDialogParamWithButtons.gridCount = 1
                    this.alertDialogParamWithOptions.gridCount = 1
                  })
                Text(`2`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.gridCount = 2
                    this.alertDialogParamWithButtons.gridCount = 2
                    this.alertDialogParamWithOptions.gridCount = 2
                  })
                Text(`3`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.gridCount = 3
                    this.alertDialogParamWithButtons.gridCount = 3
                    this.alertDialogParamWithOptions.gridCount = 3
                  })
                Text(`4`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.gridCount = 4
                    this.alertDialogParamWithButtons.gridCount = 4
                    this.alertDialogParamWithOptions.gridCount = 4
                  })
                Text(`5`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.gridCount = 5
                    this.alertDialogParamWithButtons.gridCount = 5
                    this.alertDialogParamWithOptions.gridCount = 5
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.gridCount = undefined
                    this.alertDialogParamWithButtons.gridCount = undefined
                    this.alertDialogParamWithOptions.gridCount = undefined
                  })
              }

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
                    this.alertDialogParamWithConfirm.maskRect = {
                      x: 0,
                      y: 0,
                      width: '0%',
                      height: '0%'
                    }
                    this.alertDialogParamWithButtons.maskRect = {
                      x: 0,
                      y: 0,
                      width: '0%',
                      height: '0%'
                    }
                    this.alertDialogParamWithOptions.maskRect = {
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
                    this.alertDialogParamWithConfirm.maskRect = {
                      x: 50,
                      y: 50,
                      width: '50%',
                      height: '50%'
                    }
                    this.alertDialogParamWithButtons.maskRect = {
                      x: 50,
                      y: 50,
                      width: '50%',
                      height: '50%'
                    }
                    this.alertDialogParamWithOptions.maskRect = {
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
                    this.alertDialogParamWithConfirm.maskRect = undefined
                    this.alertDialogParamWithButtons.maskRect = undefined
                    this.alertDialogParamWithOptions.maskRect = undefined
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
                    this.alertDialogParamWithConfirm.showInSubWindow = true
                    this.alertDialogParamWithButtons.showInSubWindow = true
                    this.alertDialogParamWithOptions.showInSubWindow = true
                  })
                Text(`false`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.showInSubWindow = false
                    this.alertDialogParamWithButtons.showInSubWindow = false
                    this.alertDialogParamWithOptions.showInSubWindow = false
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.showInSubWindow = undefined
                    this.alertDialogParamWithButtons.showInSubWindow = undefined
                    this.alertDialogParamWithOptions.showInSubWindow = undefined
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
                    this.alertDialogParamWithConfirm.isModal = true
                    this.alertDialogParamWithButtons.isModal = true
                    this.alertDialogParamWithOptions.isModal = true
                  })
                Text(`false`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.isModal = false
                    this.alertDialogParamWithButtons.isModal = false
                    this.alertDialogParamWithOptions.isModal = false
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.isModal = undefined
                    this.alertDialogParamWithButtons.isModal = undefined
                    this.alertDialogParamWithOptions.isModal = undefined
                  })
              }

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
                    this.alertDialogParamWithConfirm.backgroundColor = Color.Red
                    this.alertDialogParamWithButtons.backgroundColor = Color.Red
                    this.alertDialogParamWithOptions.backgroundColor = Color.Red
                  })
                Text('#330be9d0')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.backgroundColor = '#330be9d0'
                    this.alertDialogParamWithButtons.backgroundColor = '#330be9d0'
                    this.alertDialogParamWithOptions.backgroundColor = '#330be9d0'
                  })
                Text('资源值')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.backgroundColor = $r("app.color.Color_pink")
                    this.alertDialogParamWithButtons.backgroundColor = $r("app.color.Color_pink")
                    this.alertDialogParamWithOptions.backgroundColor = $r("app.color.Color_pink")
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.backgroundColor = undefined
                    this.alertDialogParamWithButtons.backgroundColor = undefined
                    this.alertDialogParamWithOptions.backgroundColor = undefined
                  })
              }

              Text(`backgroundBlurStyle`)
                .fontSize(9)
                .width("100%")
              Row() {
                Text(`Thin`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.backgroundBlurStyle = BlurStyle.Thin
                    this.alertDialogParamWithButtons.backgroundBlurStyle = BlurStyle.Thin
                    this.alertDialogParamWithOptions.backgroundBlurStyle = BlurStyle.Thin
                  })
                Text(`Regular`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.backgroundBlurStyle = BlurStyle.Regular
                    this.alertDialogParamWithButtons.backgroundBlurStyle = BlurStyle.Regular
                    this.alertDialogParamWithOptions.backgroundBlurStyle = BlurStyle.Regular
                  })
                Text(`Thick`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.backgroundBlurStyle = BlurStyle.Thick
                    this.alertDialogParamWithButtons.backgroundBlurStyle = BlurStyle.Thick
                    this.alertDialogParamWithOptions.backgroundBlurStyle = BlurStyle.Thick
                  })
                Text(`BACKGROUND_THIN`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.backgroundBlurStyle = BlurStyle.BACKGROUND_THIN
                    this.alertDialogParamWithButtons.backgroundBlurStyle = BlurStyle.BACKGROUND_THIN
                    this.alertDialogParamWithOptions.backgroundBlurStyle = BlurStyle.BACKGROUND_THIN
                  })
                Text(`BACKGROUND_REGULAR`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.backgroundBlurStyle = BlurStyle.BACKGROUND_REGULAR
                    this.alertDialogParamWithButtons.backgroundBlurStyle = BlurStyle.BACKGROUND_REGULAR
                    this.alertDialogParamWithOptions.backgroundBlurStyle = BlurStyle.BACKGROUND_REGULAR
                  })
              }

              Row() {
                Text(`BACKGROUND_ULTRA_THICK`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.backgroundBlurStyle = BlurStyle.BACKGROUND_ULTRA_THICK
                    this.alertDialogParamWithButtons.backgroundBlurStyle = BlurStyle.BACKGROUND_ULTRA_THICK
                    this.alertDialogParamWithOptions.backgroundBlurStyle = BlurStyle.BACKGROUND_ULTRA_THICK
                  })
                Text(`NONE`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.backgroundBlurStyle = BlurStyle.NONE
                    this.alertDialogParamWithButtons.backgroundBlurStyle = BlurStyle.NONE
                    this.alertDialogParamWithOptions.backgroundBlurStyle = BlurStyle.NONE
                  })
                Text(`COMPONENT_ULTRA_THIN`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.backgroundBlurStyle = BlurStyle.COMPONENT_ULTRA_THIN
                    this.alertDialogParamWithButtons.backgroundBlurStyle = BlurStyle.COMPONENT_ULTRA_THIN
                    this.alertDialogParamWithOptions.backgroundBlurStyle = BlurStyle.COMPONENT_ULTRA_THIN
                  })
              }

              Row() {
                Text(`COMPONENT_THIN`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.backgroundBlurStyle = BlurStyle.COMPONENT_THIN
                    this.alertDialogParamWithButtons.backgroundBlurStyle = BlurStyle.COMPONENT_THIN
                    this.alertDialogParamWithOptions.backgroundBlurStyle = BlurStyle.COMPONENT_THIN
                  })
                Text(`COMPONENT_REGULAR`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.backgroundBlurStyle = BlurStyle.COMPONENT_REGULAR
                    this.alertDialogParamWithButtons.backgroundBlurStyle = BlurStyle.COMPONENT_REGULAR
                    this.alertDialogParamWithOptions.backgroundBlurStyle = BlurStyle.COMPONENT_REGULAR
                  })
                Text(`COMPONENT_THICK`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.backgroundBlurStyle = BlurStyle.COMPONENT_THICK
                    this.alertDialogParamWithButtons.backgroundBlurStyle = BlurStyle.COMPONENT_THICK
                    this.alertDialogParamWithOptions.backgroundBlurStyle = BlurStyle.COMPONENT_THICK
                  })
              }

              Row() {
                Text(`COMPONENT_ULTRA_THICK`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.backgroundBlurStyle = BlurStyle.COMPONENT_ULTRA_THICK
                    this.alertDialogParamWithButtons.backgroundBlurStyle = BlurStyle.COMPONENT_ULTRA_THICK
                    this.alertDialogParamWithOptions.backgroundBlurStyle = BlurStyle.COMPONENT_ULTRA_THICK
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.backgroundBlurStyle = undefined
                    this.alertDialogParamWithButtons.backgroundBlurStyle = undefined
                    this.alertDialogParamWithOptions.backgroundBlurStyle = undefined
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
                    this.alertDialogParamWithConfirm.backgroundBlurStyleOptions = {
                      policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                      inactiveColor: Color.Green,
                      colorMode: ThemeColorMode.DARK,
                      adaptiveColor: AdaptiveColor.DEFAULT,
                      blurOptions: {
                        grayscale: [127, 127]
                      },
                      scale: 1.0
                    } as BackgroundBlurStyleOptions
                    this.alertDialogParamWithButtons.backgroundBlurStyleOptions = {
                      policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                      inactiveColor: Color.Green,
                      colorMode: ThemeColorMode.DARK,
                      adaptiveColor: AdaptiveColor.DEFAULT,
                      blurOptions: {
                        grayscale: [127, 127]
                      },
                      scale: 1.0
                    } as BackgroundBlurStyleOptions
                    this.alertDialogParamWithOptions.backgroundBlurStyleOptions = {
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
                    this.alertDialogParamWithConfirm.backgroundBlurStyleOptions = {
                      policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                      inactiveColor: Color.Red,
                      colorMode: ThemeColorMode.SYSTEM,
                      adaptiveColor: AdaptiveColor.DEFAULT,
                      blurOptions: {
                        grayscale: [30.4, 30.4]
                      },
                      scale: 0.5
                    } as BackgroundBlurStyleOptions
                    this.alertDialogParamWithButtons.backgroundBlurStyleOptions = {
                      policy: BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE,
                      inactiveColor: Color.Red,
                      colorMode: ThemeColorMode.SYSTEM,
                      adaptiveColor: AdaptiveColor.DEFAULT,
                      blurOptions: {
                        grayscale: [30.4, 30.4]
                      },
                      scale: 0.5
                    } as BackgroundBlurStyleOptions
                    this.alertDialogParamWithOptions.backgroundBlurStyleOptions = {
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
                    this.alertDialogParamWithConfirm.backgroundBlurStyleOptions = {
                      policy: BlurStyleActivePolicy.ALWAYS_ACTIVE,
                      inactiveColor: '#330be9d0',
                      colorMode: ThemeColorMode.LIGHT,
                      adaptiveColor: AdaptiveColor.AVERAGE,
                      blurOptions: {
                        grayscale: [0, 127]
                      },
                      scale: 0
                    } as BackgroundBlurStyleOptions
                    this.alertDialogParamWithButtons.backgroundBlurStyleOptions = {
                      policy: BlurStyleActivePolicy.ALWAYS_ACTIVE,
                      inactiveColor: '#330be9d0',
                      colorMode: ThemeColorMode.LIGHT,
                      adaptiveColor: AdaptiveColor.AVERAGE,
                      blurOptions: {
                        grayscale: [0, 127]
                      },
                      scale: 0
                    } as BackgroundBlurStyleOptions
                    this.alertDialogParamWithOptions.backgroundBlurStyleOptions = {
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
                    this.alertDialogParamWithConfirm.backgroundBlurStyleOptions = {
                      policy: BlurStyleActivePolicy.ALWAYS_INACTIVE,
                      inactiveColor: $r('app.color.Color_pink'),
                      colorMode: ThemeColorMode.DARK,
                      adaptiveColor: undefined,
                      blurOptions: {
                        grayscale: [-100, -100]
                      },
                      scale: 1.0
                    } as BackgroundBlurStyleOptions
                    this.alertDialogParamWithButtons.backgroundBlurStyleOptions = {
                      policy: BlurStyleActivePolicy.ALWAYS_INACTIVE,
                      inactiveColor: $r('app.color.Color_pink'),
                      colorMode: ThemeColorMode.DARK,
                      adaptiveColor: undefined,
                      blurOptions: {
                        grayscale: [-100, -100]
                      },
                      scale: 1.0
                    } as BackgroundBlurStyleOptions
                    this.alertDialogParamWithOptions.backgroundBlurStyleOptions = {
                      policy: BlurStyleActivePolicy.ALWAYS_INACTIVE,
                      inactiveColor: $r('app.color.Color_pink'),
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
                    this.alertDialogParamWithConfirm.backgroundBlurStyleOptions = {
                      policy: undefined,
                      inactiveColor: 'rgba(23,169,141,0.5)',
                      colorMode: undefined,
                      blurOptions: {
                        grayscale: [1000, 1000]
                      },
                      scale: undefined
                    } as BackgroundBlurStyleOptions
                    this.alertDialogParamWithButtons.backgroundBlurStyleOptions = {
                      policy: undefined,
                      inactiveColor: 'rgba(23,169,141,0.5)',
                      colorMode: undefined,
                      blurOptions: {
                        grayscale: [1000, 1000]
                      },
                      scale: undefined
                    } as BackgroundBlurStyleOptions
                    this.alertDialogParamWithOptions.backgroundBlurStyleOptions = {
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
                    this.alertDialogParamWithConfirm.backgroundBlurStyleOptions = {
                      inactiveColor: undefined,
                      blurOptions: undefined,
                    } as BackgroundBlurStyleOptions
                    this.alertDialogParamWithButtons.backgroundBlurStyleOptions = {
                      inactiveColor: undefined,
                      blurOptions: undefined,
                    } as BackgroundBlurStyleOptions
                    this.alertDialogParamWithOptions.backgroundBlurStyleOptions = {
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
                    this.alertDialogParamWithConfirm.backgroundBlurStyleOptions = undefined
                    this.alertDialogParamWithButtons.backgroundBlurStyleOptions = undefined
                    this.alertDialogParamWithOptions.backgroundBlurStyleOptions = undefined
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
                    this.alertDialogParamWithConfirm.backgroundEffect = {
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
                    this.alertDialogParamWithButtons.backgroundEffect = {
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
                    this.alertDialogParamWithOptions.backgroundEffect = {
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
                    this.alertDialogParamWithConfirm.backgroundEffect = {
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
                    this.alertDialogParamWithButtons.backgroundEffect = {
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
                    this.alertDialogParamWithOptions.backgroundEffect = {
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
                    this.alertDialogParamWithConfirm.backgroundEffect = {
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
                    this.alertDialogParamWithButtons.backgroundEffect = {
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
                    this.alertDialogParamWithOptions.backgroundEffect = {
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
                    this.alertDialogParamWithConfirm.backgroundEffect = {
                      radius: -100,
                      saturation: -100,
                      brightness: -100,
                      color: $r('app.color.Color_pink'),
                      adaptiveColor: undefined,
                      blurOptions: {
                        grayscale: [-100, -100]
                      },
                      policy: BlurStyleActivePolicy.ALWAYS_INACTIVE,
                      inactiveColor: $r('app.color.Color_pink'),
                    } as BackgroundEffectOptions
                    this.alertDialogParamWithButtons.backgroundEffect = {
                      radius: -100,
                      saturation: -100,
                      brightness: -100,
                      color: $r('app.color.Color_pink'),
                      adaptiveColor: undefined,
                      blurOptions: {
                        grayscale: [-100, -100]
                      },
                      policy: BlurStyleActivePolicy.ALWAYS_INACTIVE,
                      inactiveColor: $r('app.color.Color_pink'),
                    } as BackgroundEffectOptions
                    this.alertDialogParamWithOptions.backgroundEffect = {
                      radius: -100,
                      saturation: -100,
                      brightness: -100,
                      color: $r('app.color.Color_pink'),
                      adaptiveColor: undefined,
                      blurOptions: {
                        grayscale: [-100, -100]
                      },
                      policy: BlurStyleActivePolicy.ALWAYS_INACTIVE,
                      inactiveColor: $r('app.color.Color_pink'),
                    } as BackgroundEffectOptions
                  })
                Text(`444`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.backgroundEffect = {
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
                    this.alertDialogParamWithButtons.backgroundEffect = {
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
                    this.alertDialogParamWithOptions.backgroundEffect = {
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
                    this.alertDialogParamWithConfirm.backgroundEffect = {
                      radius: 3,
                      saturation: undefined,
                      brightness: undefined,
                      color: undefined,
                      blurOptions: undefined,
                      inactiveColor: undefined,
                    } as BackgroundEffectOptions
                    this.alertDialogParamWithButtons.backgroundEffect = {
                      radius: 3,
                      saturation: undefined,
                      brightness: undefined,
                      color: undefined,
                      blurOptions: undefined,
                      inactiveColor: undefined,
                    } as BackgroundEffectOptions
                    this.alertDialogParamWithOptions.backgroundEffect = {
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
                    this.alertDialogParamWithConfirm.backgroundEffect = undefined
                    this.alertDialogParamWithButtons.backgroundEffect = undefined
                    this.alertDialogParamWithOptions.backgroundEffect = undefined
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
                    this.alertDialogParamWithConfirm.onWillDismiss = (dismissDialogAction: DismissDialogAction) => {
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
                    this.alertDialogParamWithButtons.onWillDismiss = (dismissDialogAction: DismissDialogAction) => {
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
                    this.alertDialogParamWithOptions.onWillDismiss = (dismissDialogAction: DismissDialogAction) => {
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
                    this.alertDialogParamWithConfirm.onWillDismiss = undefined
                    this.alertDialogParamWithButtons.onWillDismiss = undefined
                    this.alertDialogParamWithOptions.onWillDismiss = undefined
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
                    this.alertDialogParamWithConfirm.cornerRadius = '0vp'
                    this.alertDialogParamWithButtons.cornerRadius = '0vp'
                    this.alertDialogParamWithOptions.cornerRadius = '0vp'
                  })
                Text(`30%`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.cornerRadius = '30%'
                    this.alertDialogParamWithButtons.cornerRadius = '30%'
                    this.alertDialogParamWithOptions.cornerRadius = '30%'
                  })
                Text(`第二个`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.cornerRadius = {
                      topLeft: '50px',
                      topRight: '50vp',
                      bottomLeft: $r('app.float.float_30'),
                      bottomRight: '50%',
                    }
                    this.alertDialogParamWithButtons.cornerRadius = {
                      topLeft: '50px',
                      topRight: '50vp',
                      bottomLeft: $r('app.float.float_30'),
                      bottomRight: '50%',
                    }
                    this.alertDialogParamWithOptions.cornerRadius = {
                      topLeft: '50px',
                      topRight: '50vp',
                      bottomLeft: $r('app.float.float_30'),
                      bottomRight: '50%',
                    }
                  })
                Text(`第三个`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.cornerRadius = {
                      topStart: LengthMetrics.px(50),
                      topEnd: LengthMetrics.vp(50),
                      bottomStart: LengthMetrics.resource($r('app.float.float_30')),
                      bottomEnd: LengthMetrics.percent(0.5),
                    }
                    this.alertDialogParamWithButtons.cornerRadius = {
                      topStart: LengthMetrics.px(50),
                      topEnd: LengthMetrics.vp(50),
                      bottomStart: LengthMetrics.resource($r('app.float.float_30')),
                      bottomEnd: LengthMetrics.percent(0.5),
                    }
                    this.alertDialogParamWithOptions.cornerRadius = {
                      topStart: LengthMetrics.px(50),
                      topEnd: LengthMetrics.vp(50),
                      bottomStart: LengthMetrics.resource($r('app.float.float_30')),
                      bottomEnd: LengthMetrics.percent(0.5),
                    }
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.alertDialogParamWithConfirm.cornerRadius = undefined
                    this.alertDialogParamWithButtons.cornerRadius = undefined
                    this.alertDialogParamWithOptions.cornerRadius = undefined
                  })
              }
            }
          }
        }
      }
    }
  }
}
