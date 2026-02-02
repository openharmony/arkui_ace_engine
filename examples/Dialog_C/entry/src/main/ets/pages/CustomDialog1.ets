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
  myBuilder1() {
    Column() {
      Button("change height")
        .margin(10)
        .fontSize(20)
      TextInput().height(50)
      Button("Set Illegal height")
        .margin(10)
        .fontSize(20)
      Button("closeCustomDialog")
        .margin(10)
        .fontSize(20)
        .onClick((e: ClickEvent) => {
          console.log('testTag  closeCustomDialog');
          this.promptAction.closeCustomDialog(this.customDialogComponentId);
        })
    }
    .backgroundColor(Color.Red)
    .width('100%')
    .height('50%')
  }

  @Builder
  myBuilder22(params: Params1) {
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
          if (this.contentNode11 !== undefined) {
            this.promptAction.updateCustomDialog(this.contentNode11!!, this.baseUpdateDialogOptions);
          }
        })
      Button("closeCustomDialog")
        .margin(10)
        .fontSize(20).onClick((e: ClickEvent) => {
        console.log('testTag  closeCustomDialog');
        if (this.contentNode11 !== undefined) {
          this.promptAction.closeCustomDialog(this.contentNode11!!);
        }
      })
    }
    .backgroundColor(Color.Red)
    .width('100%')
    .height('50%')
  }

  @Builder
  myBuilder33(params: Params1) {
    Column() {
      Button("updateCustomDialog")
        .margin(10)
        .fontSize(20)
        .onClick((e: ClickEvent) => {
          console.log('testTag  updateCustomDialog');
          this.promptAction.updateCustomDialog(this.contentNode22!!, this.baseUpdateDialogOptions);
        })
      TextInput().height(50)
      Button("closeCustomDialog")
        .margin(10)
        .fontSize(20)
        .onClick((e: ClickEvent) => {
          if (this.contentNode22 !== undefined) {
            this.promptAction.closeCustomDialog(this.contentNode22!!);
          }
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
        Column() {
          Text(`openCustomDialog 1个参数`)
            .fontSize(15)
            .backgroundColor(Color.Orange)
            .margin(3)
            .padding(3)
            .borderWidth(1.0)
            .onClick((e: ClickEvent) => {
              this.promptAction.openCustomDialog(this.customDialogOptions).then((dialogId: number) => {
                this.customDialogComponentId = dialogId;
              })
            })
          Text(`openCustomDialog 2个参数且不带第二个参数`)
            .fontSize(15)
            .backgroundColor(Color.Orange)
            .margin(3)
            .padding(3)
            .borderWidth(1.0)
            .onClick((e: ClickEvent) => {
              contentNode1 = new ComponentContent<Params2>(
                this.uiContext, wrapBuilder(myBuilder2), new Params2(this.promptAction, this.baseUpdateDialogOptions))
              if (contentNode1 !== undefined) {
                this.promptAction.openCustomDialog(contentNode1!!);
              }
              // this.contentNode11 = new ComponentContent<Params1>(
              //   this.uiContext, wrapBuilder(this.myBuilder22), new Params1('弹窗'))
              // if (this.contentNode11 !== undefined) {
              //   this.promptAction.openCustomDialog(this.contentNode11!!);
              // }
            })
          Text(`openCustomDialog 2个参数`)
            .fontSize(15)
            .backgroundColor(Color.Orange)
            .margin(3)
            .padding(3)
            .borderWidth(1.0)
            .onClick((e: ClickEvent) => {
              contentNode1 = new ComponentContent<Params2>(
                this.uiContext, wrapBuilder(myBuilder2), new Params2(this.promptAction, this.baseUpdateDialogOptions))
              if (contentNode1 !== undefined) {
                this.promptAction.openCustomDialog(contentNode1!!, this.baseDialogOptions);
              }
              // this.contentNode11 = new ComponentContent<Params1>(
              //   this.uiContext, wrapBuilder(this.myBuilder22), new Params1('弹窗'))
              // if (this.contentNode11 !== undefined) {
              //   this.promptAction.openCustomDialog(this.contentNode11!!, this.baseDialogOptions);
              // }
            })
          Text(`openCustomDialogWithController 不带第三个参数`)
            .fontSize(15)
            .backgroundColor(Color.Orange)
            .margin(3)
            .padding(3)
            .borderWidth(1.0)
            .onClick((e: ClickEvent) => {
              contentNode2 = new ComponentContent<Params2>(
                this.uiContext, wrapBuilder(myBuilder3), new Params2(this.promptAction, this.baseUpdateDialogOptions)
              )
              if (contentNode2 !== undefined) {
                this.promptAction.openCustomDialogWithController(contentNode2!!, dialogController);
              }
              // this.contentNode22 = new ComponentContent<Params1>(
              //   this.uiContext, wrapBuilder(this.myBuilder33), new Params1('弹窗'))
              // if (this.contentNode22 !== undefined) {
              //   this.promptAction.openCustomDialogWithController(this.contentNode22!!, this.dialogController11);
              // }
            })
          Text(`openCustomDialogWithController 3个参数`)
            .fontSize(15)
            .backgroundColor(Color.Orange)
            .margin(3)
            .padding(3)
            .borderWidth(1.0)
            .onClick((e: ClickEvent) => {
              contentNode2 = new ComponentContent<Params2>(
                this.uiContext, wrapBuilder(myBuilder3), new Params2(this.promptAction, this.baseUpdateDialogOptions)
              )
              if (contentNode2 !== undefined) {
                this.promptAction.openCustomDialogWithController(contentNode2!!, dialogController,
                  this.baseDialogOptions);
              }
              // this.contentNode22 = new ComponentContent<Params1>(
              //   this.uiContext, wrapBuilder(this.myBuilder33), new Params1('弹窗'))
              // if (this.contentNode22 !== undefined) {
              //   this.promptAction.openCustomDialogWithController(this.contentNode22!!, this.dialogController11,
              //     this.baseDialogOptions);
              // }
            })
          Text(`presentCustomDialog 不带第二、三个参数`)
            .fontSize(15)
            .backgroundColor(Color.Orange)
            .margin(3)
            .padding(3)
            .borderWidth(1.0)
            .onClick((e: ClickEvent) => {
              this.promptAction.presentCustomDialog(
                this.myBuilder4
              ).then((dialogId: number) => {
                this.customDialogComponentId = dialogId;
              });
            })
          Text(`presentCustomDialog 不带第三个参数`)
            .fontSize(15)
            .backgroundColor(Color.Orange)
            .margin(3)
            .padding(3)
            .borderWidth(1.0)
            .onClick((e: ClickEvent) => {
              this.promptAction.presentCustomDialog(this.myBuilder4
                , this.dialogController11).then((dialogId: number) => {
                this.customDialogComponentId = dialogId;
              });
            })
          Text(`presentCustomDialog 3个参数`)
            .fontSize(15)
            .backgroundColor(Color.Orange)
            .margin(3)
            .padding(3)
            .borderWidth(1.0)
            .onClick((e: ClickEvent) => {
              this.promptAction.presentCustomDialog(
                this.myBuilder4
                , this.dialogController11, this.dialogOptions).then((dialogId: number) => {
                this.customDialogComponentId = dialogId;
              });
            })
        }.borderWidth(1.0)
        .padding(10)
        .width("100%")
        .backgroundColor(Color.Pink)

        Scroll(this.scroller) {
          Column() {
            Column() {
              Text(`BaseDialogOptions`)
                .fontSize(9)
                .width("100%")
              Text(`BaseDialogOptions`)
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
                    this.baseDialogOptions.maskRect = {
                      x: 0,
                      y: 0,
                      width: '0%',
                      height: '0%'
                    }
                    this.dialogOptions.maskRect = {
                      x: 0,
                      y: 0,
                      width: '0%',
                      height: '0%'
                    }
                    this.customDialogOptions.maskRect = {
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
                    this.baseDialogOptions.maskRect = {
                      x: 50,
                      y: 50,
                      width: '50%',
                      height: '50%'
                    }
                    this.dialogOptions.maskRect = {
                      x: 50,
                      y: 50,
                      width: '50%',
                      height: '50%'
                    }
                    this.customDialogOptions.maskRect = {
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
                    this.baseDialogOptions.maskRect = undefined
                    this.dialogOptions.maskRect = undefined
                    this.customDialogOptions.maskRect = undefined
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
                    this.baseDialogOptions.alignment = DialogAlignment.Top
                    this.dialogOptions.alignment = DialogAlignment.Top
                    this.customDialogOptions.alignment = DialogAlignment.Top
                  })
                Text(`Center`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.alignment = DialogAlignment.Center
                    this.dialogOptions.alignment = DialogAlignment.Center
                    this.customDialogOptions.alignment = DialogAlignment.Center
                  })
                Text(`Bottom`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.alignment = DialogAlignment.Bottom
                    this.dialogOptions.alignment = DialogAlignment.Bottom
                    this.customDialogOptions.alignment = DialogAlignment.Bottom
                  })
                Text(`Default`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.alignment = DialogAlignment.Default
                    this.dialogOptions.alignment = DialogAlignment.Default
                    this.customDialogOptions.alignment = DialogAlignment.Default
                  })
                Text(`TopStart`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.alignment = DialogAlignment.TopStart
                    this.dialogOptions.alignment = DialogAlignment.TopStart
                    this.customDialogOptions.alignment = DialogAlignment.TopStart
                  })
                Text(`TopEnd`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.alignment = DialogAlignment.TopEnd
                    this.dialogOptions.alignment = DialogAlignment.TopEnd
                    this.customDialogOptions.alignment = DialogAlignment.TopEnd
                  })
              }

              Row() {
                Text(`CenterStart`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.alignment = DialogAlignment.CenterStart
                    this.dialogOptions.alignment = DialogAlignment.CenterStart
                    this.customDialogOptions.alignment = DialogAlignment.CenterStart
                  })
                Text(`CenterEnd`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.alignment = DialogAlignment.CenterEnd
                    this.dialogOptions.alignment = DialogAlignment.CenterEnd
                    this.customDialogOptions.alignment = DialogAlignment.CenterEnd
                  })
                Text(`BottomStart`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.alignment = DialogAlignment.BottomStart
                    this.dialogOptions.alignment = DialogAlignment.BottomStart
                    this.customDialogOptions.alignment = DialogAlignment.BottomStart
                  })
                Text(`BottomEnd`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.alignment = DialogAlignment.BottomEnd
                    this.dialogOptions.alignment = DialogAlignment.BottomStart
                    this.customDialogOptions.alignment = DialogAlignment.BottomEnd
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.alignment = undefined
                    this.dialogOptions.alignment = undefined
                    this.customDialogOptions.alignment = undefined
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
                    this.baseDialogOptions.offset = { dx: 40, dy: 40 }
                    this.dialogOptions.offset = { dx: 40, dy: 40 }
                    this.customDialogOptions.offset = { dx: 40, dy: 40 }
                  })
                Text(`aaa`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.offset = { dx: $r("app.float.aaa"), dy: '30%' }
                    this.dialogOptions.offset = { dx: $r("app.float.aaa"), dy: '30%' }
                    this.customDialogOptions.offset = { dx: $r("app.float.aaa"), dy: '30%' }
                  })
                Text(`bbb`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.offset = { dx: '30%', dy: $r("app.float.bbb") }
                    this.dialogOptions.offset = { dx: '30%', dy: $r("app.float.bbb") }
                    this.customDialogOptions.offset = { dx: '30%', dy: $r("app.float.bbb") }
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.offset = undefined
                    this.dialogOptions.offset = undefined
                    this.customDialogOptions.offset = undefined
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
                    this.baseDialogOptions.isModal = true
                    this.dialogOptions.isModal = true
                    this.customDialogOptions.isModal = true
                  })
                Text(`false`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.isModal = false
                    this.dialogOptions.isModal = false
                    this.customDialogOptions.isModal = false
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.isModal = undefined
                    this.dialogOptions.isModal = undefined
                    this.customDialogOptions.isModal = undefined
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
                    this.baseDialogOptions.showInSubWindow = true
                    this.dialogOptions.showInSubWindow = true
                    this.customDialogOptions.showInSubWindow = true
                  })
                Text(`false`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.showInSubWindow = false
                    this.dialogOptions.showInSubWindow = false
                    this.customDialogOptions.showInSubWindow = false
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.showInSubWindow = undefined
                    this.dialogOptions.showInSubWindow = undefined
                    this.customDialogOptions.showInSubWindow = undefined
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
                    this.baseDialogOptions.onWillDismiss = (dismissDialogAction: DismissDialogAction) => {
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
                    this.dialogOptions.onWillDismiss = (dismissDialogAction: DismissDialogAction) => {
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
                    this.customDialogOptions.onWillDismiss = (dismissDialogAction: DismissDialogAction) => {
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
                    this.baseDialogOptions.onWillDismiss = undefined
                    this.dialogOptions.onWillDismiss = undefined
                    this.customDialogOptions.onWillDismiss = undefined
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
                    this.baseDialogOptions.autoCancel = true
                    this.dialogOptions.autoCancel = true
                    this.customDialogOptions.autoCancel = true
                  })
                Text(`false`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.autoCancel = false
                    this.dialogOptions.autoCancel = false
                    this.customDialogOptions.autoCancel = false
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.autoCancel = undefined
                    this.dialogOptions.autoCancel = undefined
                    this.customDialogOptions.autoCancel = undefined
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
                    this.baseDialogOptions.maskColor = Color.Red
                    this.dialogOptions.maskColor = Color.Red
                    this.customDialogOptions.maskColor = Color.Red
                  })
                Text('#330be9d0')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.maskColor = '#330be9d0'
                    this.dialogOptions.maskColor = '#330be9d0'
                    this.customDialogOptions.maskColor = '#330be9d0'
                  })
                Text('资源值')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.maskColor = $r("app.color.aaa")
                    this.dialogOptions.maskColor = $r("app.color.aaa")
                    this.customDialogOptions.maskColor = $r("app.color.aaa")
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.maskColor = undefined
                    this.dialogOptions.maskColor = undefined
                    this.customDialogOptions.maskColor = undefined
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
                    this.baseDialogOptions.transition = TransitionEffect.asymmetric(
                      TransitionEffect.OPACITY.animation({ duration: 3000, curve: Curve.Sharp })
                        .combine(TransitionEffect.scale({ x: 1.5, y: 1.5 })
                          .animation({ duration: 3000, curve: Curve.Sharp })),
                      TransitionEffect.OPACITY.animation({ duration: 100, curve: Curve.Smooth })
                        .combine(TransitionEffect.scale({ x: 0.5, y: 0.5 })
                          .animation({ duration: 100, curve: Curve.Smooth })))
                    this.dialogOptions.transition = TransitionEffect.asymmetric(
                      TransitionEffect.OPACITY.animation({ duration: 3000, curve: Curve.Sharp })
                        .combine(TransitionEffect.scale({ x: 1.5, y: 1.5 })
                          .animation({ duration: 3000, curve: Curve.Sharp })),
                      TransitionEffect.OPACITY.animation({ duration: 100, curve: Curve.Smooth })
                        .combine(TransitionEffect.scale({ x: 0.5, y: 0.5 })
                          .animation({ duration: 100, curve: Curve.Smooth })))
                    this.customDialogOptions.transition = TransitionEffect.asymmetric(
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
                    this.baseDialogOptions.transition =
                      TransitionEffect.scale({ x: 1, y: 0 }).animation({ duration: 3000, curve: Curve.Ease })
                    this.dialogOptions.transition =
                      TransitionEffect.scale({ x: 1, y: 0 }).animation({ duration: 3000, curve: Curve.Ease })
                    this.customDialogOptions.transition =
                      TransitionEffect.scale({ x: 1, y: 0 }).animation({ duration: 3000, curve: Curve.Ease })
                  })
                Text(`ccc`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.transition =
                      TransitionEffect.OPACITY.animation({ duration: 4000, curve: Curve.Ease })
                        .combine(TransitionEffect.rotate({ z: 1, angle: 180 }))
                    this.dialogOptions.transition =
                      TransitionEffect.OPACITY.animation({ duration: 4000, curve: Curve.Ease })
                        .combine(TransitionEffect.rotate({ z: 1, angle: 180 }))
                    this.customDialogOptions.transition =
                      TransitionEffect.OPACITY.animation({ duration: 4000, curve: Curve.Ease })
                        .combine(TransitionEffect.rotate({ z: 1, angle: 180 }))
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.transition = undefined
                    this.dialogOptions.transition = undefined
                    this.customDialogOptions.transition = undefined
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
                    this.baseDialogOptions.dialogTransition = TransitionEffect.asymmetric(
                      TransitionEffect.OPACITY.animation({ duration: 3000, curve: Curve.Sharp })
                        .combine(TransitionEffect.scale({ x: 1.5, y: 1.5 })
                          .animation({ duration: 3000, curve: Curve.Sharp })),
                      TransitionEffect.OPACITY.animation({ duration: 100, curve: Curve.Smooth })
                        .combine(TransitionEffect.scale({ x: 0.5, y: 0.5 })
                          .animation({ duration: 100, curve: Curve.Smooth })))
                    this.dialogOptions.dialogTransition = TransitionEffect.asymmetric(
                      TransitionEffect.OPACITY.animation({ duration: 3000, curve: Curve.Sharp })
                        .combine(TransitionEffect.scale({ x: 1.5, y: 1.5 })
                          .animation({ duration: 3000, curve: Curve.Sharp })),
                      TransitionEffect.OPACITY.animation({ duration: 100, curve: Curve.Smooth })
                        .combine(TransitionEffect.scale({ x: 0.5, y: 0.5 })
                          .animation({ duration: 100, curve: Curve.Smooth })))
                    this.customDialogOptions.dialogTransition = TransitionEffect.asymmetric(
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
                    this.baseDialogOptions.dialogTransition =
                      TransitionEffect.scale({ x: 1, y: 0 }).animation({ duration: 3000, curve: Curve.Ease })
                    this.dialogOptions.dialogTransition =
                      TransitionEffect.scale({ x: 1, y: 0 }).animation({ duration: 3000, curve: Curve.Ease })
                    this.customDialogOptions.dialogTransition =
                      TransitionEffect.scale({ x: 1, y: 0 }).animation({ duration: 3000, curve: Curve.Ease })
                  })
                Text(`ccc`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.dialogTransition =
                      TransitionEffect.OPACITY.animation({ duration: 4000, curve: Curve.Ease })
                        .combine(TransitionEffect.rotate({ z: 1, angle: 180 }))
                    this.dialogOptions.dialogTransition =
                      TransitionEffect.OPACITY.animation({ duration: 4000, curve: Curve.Ease })
                        .combine(TransitionEffect.rotate({ z: 1, angle: 180 }))
                    this.customDialogOptions.dialogTransition =
                      TransitionEffect.OPACITY.animation({ duration: 4000, curve: Curve.Ease })
                        .combine(TransitionEffect.rotate({ z: 1, angle: 180 }))
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.dialogTransition = undefined
                    this.dialogOptions.dialogTransition = undefined
                    this.customDialogOptions.dialogTransition = undefined
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
                    this.baseDialogOptions.maskTransition = TransitionEffect.asymmetric(
                      TransitionEffect.OPACITY.animation({ duration: 3000, curve: Curve.Sharp })
                        .combine(TransitionEffect.scale({ x: 1.5, y: 1.5 })
                          .animation({ duration: 3000, curve: Curve.Sharp })),
                      TransitionEffect.OPACITY.animation({ duration: 100, curve: Curve.Smooth })
                        .combine(TransitionEffect.scale({ x: 0.5, y: 0.5 })
                          .animation({ duration: 100, curve: Curve.Smooth })))
                    this.dialogOptions.maskTransition = TransitionEffect.asymmetric(
                      TransitionEffect.OPACITY.animation({ duration: 3000, curve: Curve.Sharp })
                        .combine(TransitionEffect.scale({ x: 1.5, y: 1.5 })
                          .animation({ duration: 3000, curve: Curve.Sharp })),
                      TransitionEffect.OPACITY.animation({ duration: 100, curve: Curve.Smooth })
                        .combine(TransitionEffect.scale({ x: 0.5, y: 0.5 })
                          .animation({ duration: 100, curve: Curve.Smooth })))
                    this.customDialogOptions.maskTransition = TransitionEffect.asymmetric(
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
                    this.baseDialogOptions.maskTransition =
                      TransitionEffect.scale({ x: 1, y: 0 }).animation({ duration: 3000, curve: Curve.Ease })
                    this.dialogOptions.maskTransition =
                      TransitionEffect.scale({ x: 1, y: 0 }).animation({ duration: 3000, curve: Curve.Ease })
                    this.customDialogOptions.maskTransition =
                      TransitionEffect.scale({ x: 1, y: 0 }).animation({ duration: 3000, curve: Curve.Ease })
                  })
                Text(`ccc`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.maskTransition =
                      TransitionEffect.OPACITY.animation({ duration: 4000, curve: Curve.Ease })
                        .combine(TransitionEffect.rotate({ z: 1, angle: 180 }))
                    this.dialogOptions.maskTransition =
                      TransitionEffect.OPACITY.animation({ duration: 4000, curve: Curve.Ease })
                        .combine(TransitionEffect.rotate({ z: 1, angle: 180 }))
                    this.customDialogOptions.maskTransition =
                      TransitionEffect.OPACITY.animation({ duration: 4000, curve: Curve.Ease })
                        .combine(TransitionEffect.rotate({ z: 1, angle: 180 }))
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.maskTransition = undefined
                    this.dialogOptions.maskTransition = undefined
                    this.customDialogOptions.maskTransition = undefined
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
                    this.baseDialogOptions.onWillAppear = () => {
                      console.info("shjb+dialog onWillAppear");
                    }
                    this.dialogOptions.onWillAppear = () => {
                      console.info("shjb+dialog onWillAppear");
                    }
                    this.customDialogOptions.onWillAppear = () => {
                      console.info("shjb+dialog onWillAppear");
                    }
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.onWillAppear = undefined
                    this.dialogOptions.onWillAppear = undefined
                    this.customDialogOptions.onWillAppear = undefined
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
                    this.baseDialogOptions.onDidAppear = () => {
                      console.info("shjb+dialog onDidAppear");
                    }
                    this.dialogOptions.onDidAppear = () => {
                      console.info("shjb+dialog onDidAppear");
                    }
                    this.customDialogOptions.onDidAppear = () => {
                      console.info("shjb+dialog onDidAppear");
                    }
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.onDidAppear = undefined
                    this.dialogOptions.onDidAppear = undefined
                    this.customDialogOptions.onDidAppear = undefined
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
                    this.baseDialogOptions.onWillDisappear = () => {
                      console.info("shjb+dialog onWillDisappear");
                    }
                    this.dialogOptions.onWillDisappear = () => {
                      console.info("shjb+dialog onWillDisappear");
                    }
                    this.customDialogOptions.onWillDisappear = () => {
                      console.info("shjb+dialog onWillDisappear");
                    }
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.onWillDisappear = undefined
                    this.dialogOptions.onWillDisappear = undefined
                    this.customDialogOptions.onWillDisappear = undefined
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
                    this.baseDialogOptions.onDidDisappear = () => {
                      console.info("shjb+dialog onDidDisappear");
                    }
                    this.dialogOptions.onDidDisappear = () => {
                      console.info("shjb+dialog onDidDisappear");
                    }
                    this.customDialogOptions.onDidDisappear = () => {
                      console.info("shjb+dialog onDidDisappear");
                    }
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.onDidDisappear = undefined
                    this.dialogOptions.onDidDisappear = undefined
                    this.customDialogOptions.onDidDisappear = undefined
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
                    this.baseDialogOptions.keyboardAvoidMode = KeyboardAvoidMode.DEFAULT
                    this.dialogOptions.keyboardAvoidMode = KeyboardAvoidMode.DEFAULT
                    this.customDialogOptions.keyboardAvoidMode = KeyboardAvoidMode.DEFAULT
                  })
                Text(`false`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.keyboardAvoidMode = KeyboardAvoidMode.NONE
                    this.dialogOptions.keyboardAvoidMode = KeyboardAvoidMode.NONE
                    this.customDialogOptions.keyboardAvoidMode = KeyboardAvoidMode.NONE
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.keyboardAvoidMode = undefined
                    this.dialogOptions.keyboardAvoidMode = undefined
                    this.customDialogOptions.keyboardAvoidMode = undefined
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
                    this.baseDialogOptions.keyboardAvoidDistance = LengthMetrics.px(50)
                    this.dialogOptions.keyboardAvoidDistance = LengthMetrics.px(50)
                    this.customDialogOptions.keyboardAvoidDistance = LengthMetrics.px(50)
                  })
                Text(`50vp`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.keyboardAvoidDistance = LengthMetrics.vp(50)
                    this.dialogOptions.keyboardAvoidDistance = LengthMetrics.vp(50)
                    this.customDialogOptions.keyboardAvoidDistance = LengthMetrics.vp(50)
                  })
                Text(`50fp`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.keyboardAvoidDistance =
                      LengthMetrics.resource($r('app.float.page_text_font_size'))
                    this.dialogOptions.keyboardAvoidDistance =
                      LengthMetrics.resource($r('app.float.page_text_font_size'))
                    this.customDialogOptions.keyboardAvoidDistance =
                      LengthMetrics.resource($r('app.float.page_text_font_size'))
                  })
                Text(`50%`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.baseDialogOptions.keyboardAvoidDistance = LengthMetrics.percent(0.5)
                    this.dialogOptions.keyboardAvoidDistance = LengthMetrics.percent(0.5)
                    this.customDialogOptions.keyboardAvoidDistance = LengthMetrics.percent(0.5)
                  })
              }
            }
          }
        }
      }
    }
  }
}