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
struct ActionMenuSample {
  actionMenuOptions: promptAction.ActionMenuOptions = {
    buttons:[
      {
        text: 'button1',
        color: '#000000',
        primary:true,
      } as promptAction.Button,
    ] as [promptAction.Button]
  } as promptAction.ActionMenuOptions
  scroller: Scroller = new Scroller() as Scroller

  build() {
    NavDestination() {
      Column() {
        Column() {
          Text(`showActionMenu 1个参数`)
            .fontSize(15)
            .backgroundColor(Color.Orange)
            .margin(3)
            .padding(3)
            .borderWidth(1.0)
            .onClick((e: ClickEvent) => {
              this.getUIContext()
                .getPromptAction()
                .showActionMenu(this.actionMenuOptions)
                .then((data: promptAction.ActionMenuSuccessResponse | null): void => {
                  if(data){
                    console.info('showActionMenu 1个参数 success, click button: ' + data.index);
                  }
                })
                .catch((err: Error) => {
                  console.error('showActionMenu 1个参数 error: ' + err);
                })
            })
          Text(`showActionMenu 2个参数`)
            .fontSize(15)
            .backgroundColor(Color.Orange)
            .margin(3)
            .padding(3)
            .borderWidth(1.0)
            .onClick((e: ClickEvent) => {
              try {
                this.getUIContext().getPromptAction().showActionMenu(
                  this.actionMenuOptions,
                  (err: BusinessError<void> | null, data: promptAction.ActionMenuSuccessResponse | undefined): void => {
                    if (err) {
                      console.error('showActionMenu 2个参数 err: ' + err);
                      return;
                    }
                    if (data) {
                      console.info('showActionMenu 2个参数 success callback, click button: ' + data.index);
                    }
                  });
              } catch (error) {
                let message = (error as BusinessError).message;
                let code = (error as BusinessError).code;
                console.error(`showActionMenu 2个参数 args error code is ${code}, message is ${message}`);
              };
            })
        }.borderWidth(1.0)
        .padding(10)
        .width("100%")
        .backgroundColor(Color.Pink)

        Scroll(this.scroller) {
          Column() {
            Column() {
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
                    this.actionMenuOptions.title = 'aaa'
                  })
                Text(`bbb`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.actionMenuOptions.title = 'bbb'
                  })
                Text(`ccc`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.actionMenuOptions.title = $r("app.string.showActionMenu_title")
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.actionMenuOptions.title = undefined
                  })
              }


              Text(`buttons`)
                .fontSize(9)
                .width("100%")
              Row() {
                Text(`一个`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.actionMenuOptions.buttons = [
                      {
                        text: 'button1',
                        color: '#000000',
                        primary: false,
                      } as promptAction.Button,
                    ] as [promptAction.Button]
                  })
                Text(`两个`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.actionMenuOptions.buttons = [
                      {
                        text: 'button1',
                        color: '#ff15b39b',
                        primary:true,
                      },
                      {
                        text: 'button2',
                        color: '#ffea0909',
                        primary:true,
                      },
                    ] as [promptAction.Button, promptAction.Button | undefined]
                  })
                Text(`三个`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.actionMenuOptions.buttons = [
                      {
                        text: 'button1',
                        color: '#ff15b39b',
                        primary: false,
                      } as promptAction.Button,
                      {
                        text: 'button2',
                        color: '#ffea0909',
                        primary: false,
                      } as promptAction.Button,
                      {
                        text: 'button3',
                        color: '#ff1a36c4',
                        primary: false,
                      } as promptAction.Button,
                    ] as [promptAction.Button, promptAction.Button | undefined, promptAction.Button | undefined]
                  })
                Text(`四个`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.actionMenuOptions.buttons = [
                      {
                        text: 'button1',
                        color: '#ff15b39b',
                        primary: false,
                      } as promptAction.Button,
                      {
                        text: 'button2',
                        color: '#ffea0909',
                        primary: true,
                      } as promptAction.Button,
                      {
                        text: 'button3',
                        color: '#ff1a36c4',
                        primary: false,
                      } as promptAction.Button,
                      {
                        text: 'button',
                        color: '#ffc80ed6',
                        primary: false,
                      } as promptAction.Button,
                    ] as [promptAction.Button, promptAction.Button | undefined, promptAction.Button | undefined, promptAction.Button | undefined]
                  })
                Text(`六个`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.actionMenuOptions.buttons = [
                      {
                        text: 'button1',
                        color: '#ff15b39b',
                        primary: false,
                      } as promptAction.Button,
                      {
                        text: 'button2',
                        color: '#ffea0909',
                        primary: true,
                      } as promptAction.Button,
                      {
                        text: 'button3',
                        color: '#ff1a36c4',
                        primary: false,
                      } as promptAction.Button,
                      {
                        text: 'button4',
                        color: '#ffc80ed6',
                        primary: true,
                      } as promptAction.Button,
                      {
                        text: 'button5',
                        color: '#ffd5d7e3',
                        primary: false,
                      } as promptAction.Button,
                      {
                        text: 'button6',
                        color: '#ff408f44',
                        primary: true,
                      } as promptAction.Button,
                    ] as [promptAction.Button,promptAction.Button | undefined,promptAction.Button | undefined,promptAction.Button | undefined,promptAction.Button | undefined,promptAction.Button | undefined]
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
                    this.actionMenuOptions.showInSubWindow = true
                  })
                Text(`false`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.actionMenuOptions.showInSubWindow = false
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.actionMenuOptions.showInSubWindow = undefined
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
                    this.actionMenuOptions.isModal = true
                  })
                Text(`false`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.actionMenuOptions.isModal = false
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.actionMenuOptions.isModal = undefined
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
                    this.actionMenuOptions.levelMode = LevelMode.OVERLAY
                  })
                Text('EMBEDDED')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.actionMenuOptions.levelMode = LevelMode.EMBEDDED
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.actionMenuOptions.levelMode = undefined
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
                    this.actionMenuOptions.levelUniqueId = 11
                  })
                Text('20')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.actionMenuOptions.levelUniqueId = 20
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.actionMenuOptions.levelUniqueId = undefined
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
                    this.actionMenuOptions.immersiveMode = ImmersiveMode.DEFAULT
                  })
                Text('EXTEND')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.actionMenuOptions.immersiveMode = ImmersiveMode.EXTEND
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.actionMenuOptions.immersiveMode = undefined
                  })
              }
            }.borderWidth(1.0)
            .padding(10)
            .width("100%")
            .backgroundColor(Color.Pink)

            Column()
              .borderWidth(1.0)
              .padding(10)
              .width("100%")
              .backgroundColor(Color.Pink)
              .height(200)
          }
        }
      }
    }
  }
}
