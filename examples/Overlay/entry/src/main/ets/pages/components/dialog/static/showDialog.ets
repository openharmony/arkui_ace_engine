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


@Component
struct MyStateSample {
  showDialogOptions: promptAction.ShowDialogOptions = {} as promptAction.ShowDialogOptions
  scroller: Scroller = new Scroller() as Scroller

  build() {
    NavDestination() {
      Column() {
        Column() {
          Text(`showDialog 1个参数`)
            .fontSize(15)
            .backgroundColor(Color.Orange)
            .margin(3)
            .padding(3)
            .borderWidth(1.0)
            .onClick((e: ClickEvent) => {
              this.getUIContext()
                .getPromptAction()
                .showDialog(this.showDialogOptions)
                .then((data: promptAction.ShowDialogSuccessResponse | null): void => {
                  if(data){
                    console.info('showDialog 1个参数 success, click button: ' + data.index);
                  }
                })
                .catch((err: Error) => {
                  console.error('showDialog 1个参数 error: ' + err);
                })
            })
          Text(`showDialog 2个参数`)
            .fontSize(15)
            .backgroundColor(Color.Orange)
            .margin(3)
            .padding(3)
            .borderWidth(1.0)
            .onClick((e: ClickEvent) => {
              try {
                this.getUIContext().getPromptAction().showDialog(
                  this.showDialogOptions,
                  (err: BusinessError<void> | null, data: promptAction.ShowDialogSuccessResponse | undefined): void => {
                    if (err) {
                      console.error('showDialog 2个参数 err: ' + err);
                      return;
                    }
                    if (data) {
                      console.info('showDialog 2个参数 success callback, click button: ' + data.index);
                    }
                  });
              } catch (error) {
                let message = (error as BusinessError).message;
                let code = (error as BusinessError).code;
                console.error(`showDialog 2个参数 args error code is ${code}, message is ${message}`);
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
                    this.showDialogOptions.title = 'aaa'
                  })
                Text(`bbb`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.title = 'bbb'
                  })
                Text(`ccc`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.title = $r("app.string.ccc")
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.title = undefined
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
                    this.showDialogOptions.message = 'aaa'
                  })
                Text(`bbb`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.message = 'bbb'
                  })
                Text(`ccc`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.message = $r("app.string.ccc")
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.message = undefined
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
                    this.showDialogOptions.buttons = [
                      {
                        text: 'button1',
                        color: '#000000',
                        primary:false,
                      },
                    ]
                  })
                Text(`两个`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.buttons = [
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
                    ]
                  })
                Text(`四个`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.buttons = [
                      {
                        text: 'button1',
                        color: '#ff15b39b',
                        primary:false,
                      },
                      {
                        text: 'button2',
                        color: '#ffea0909',
                        primary:true,
                      },
                      {
                        text: 'button3',
                        color: '#ff1a36c4',
                        primary:false,
                      },
                      {
                        text: 'button',
                        color: '#ffc80ed6',
                        primary:false,
                      },
                    ]
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.buttons = undefined
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
                    this.showDialogOptions.alignment = DialogAlignment.Top
                  })
                Text(`Center`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.alignment = DialogAlignment.Center
                  })
                Text(`Bottom`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.alignment = DialogAlignment.Bottom
                  })
                Text(`Default`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.alignment = DialogAlignment.Default
                  })
                Text(`TopStart`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.alignment = DialogAlignment.TopStart
                  })
                Text(`TopEnd`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.alignment = DialogAlignment.TopEnd
                  })
              }

              Row() {
                Text(`CenterStart`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.alignment = DialogAlignment.CenterStart
                  })
                Text(`CenterEnd`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.alignment = DialogAlignment.CenterEnd
                  })
                Text(`BottomStart`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.alignment = DialogAlignment.BottomStart
                  })
                Text(`BottomEnd`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.alignment = DialogAlignment.BottomEnd
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.alignment = undefined
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
                    this.showDialogOptions.offset = { dx: 40, dy: 40 }
                  })
                Text(`aaa`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.offset = { dx: $r("app.float.aaa"), dy: '30%' }
                  })
                Text(`bbb`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.offset = { dx: '30%', dy: $r("app.float.bbb") }
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.offset = undefined
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
                    this.showDialogOptions.maskRect = {
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
                    this.showDialogOptions.maskRect = {
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
                    this.showDialogOptions.maskRect = undefined
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
                    this.showDialogOptions.showInSubWindow = true
                  })
                Text(`false`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.showInSubWindow = false
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.showInSubWindow = undefined
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
                    this.showDialogOptions.isModal = true
                  })
                Text(`false`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.isModal = false
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.isModal = undefined
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
                    this.showDialogOptions.backgroundColor = Color.Red
                  })
                Text('#330be9d0')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.backgroundColor = '#330be9d0'
                  })
                Text('资源值')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.backgroundColor = $r("app.color.aaa")
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.backgroundColor = undefined
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
                    this.showDialogOptions.backgroundBlurStyle = BlurStyle.Thin
                  })
                Text(`Regular`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.backgroundBlurStyle = BlurStyle.Regular
                  })
                Text(`Thick`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.backgroundBlurStyle = BlurStyle.Thick
                  })
                Text(`BACKGROUND_THIN`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.backgroundBlurStyle = BlurStyle.BACKGROUND_THIN
                  })
                Text(`BACKGROUND_REGULAR`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.backgroundBlurStyle = BlurStyle.BACKGROUND_REGULAR
                  })
              }
              Row() {
                Text(`BACKGROUND_ULTRA_THICK`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.backgroundBlurStyle = BlurStyle.BACKGROUND_ULTRA_THICK
                  })
                Text(`NONE`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.backgroundBlurStyle = BlurStyle.NONE
                  })
                Text(`COMPONENT_ULTRA_THIN`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.backgroundBlurStyle = BlurStyle.COMPONENT_ULTRA_THIN
                  })
              }
              Row() {
                Text(`COMPONENT_THIN`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.backgroundBlurStyle = BlurStyle.COMPONENT_THIN
                  })
                Text(`COMPONENT_REGULAR`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.backgroundBlurStyle = BlurStyle.COMPONENT_REGULAR
                  })
                Text(`COMPONENT_THICK`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.backgroundBlurStyle = BlurStyle.COMPONENT_THICK
                  })
              }
              Row() {
                Text(`COMPONENT_ULTRA_THICK`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.backgroundBlurStyle = BlurStyle.COMPONENT_ULTRA_THICK
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.backgroundBlurStyle = undefined
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
                    this.showDialogOptions.backgroundBlurStyleOptions = {
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
                    this.showDialogOptions.backgroundBlurStyleOptions = {
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
                    this.showDialogOptions.backgroundBlurStyleOptions = {
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
                    this.showDialogOptions.backgroundBlurStyleOptions = {
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
                    this.showDialogOptions.backgroundBlurStyleOptions = {
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
                    this.showDialogOptions.backgroundBlurStyleOptions = {
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
                    this.showDialogOptions.backgroundBlurStyleOptions = undefined
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
                    this.showDialogOptions.backgroundEffect = {
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
                    this.showDialogOptions.backgroundEffect = {
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
                    this.showDialogOptions.backgroundEffect = {
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
                    this.showDialogOptions.backgroundEffect = {
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
                    this.showDialogOptions.backgroundEffect = {
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
                    this.showDialogOptions.backgroundEffect = {
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
                    this.showDialogOptions.backgroundEffect = undefined
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
                    this.showDialogOptions.shadow = ShadowStyle.OUTER_DEFAULT_XS
                  })
                Text(`OUTER_DEFAULT_SM`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.shadow = ShadowStyle.OUTER_DEFAULT_SM
                  })
                Text(`OUTER_DEFAULT_MD`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.shadow = ShadowStyle.OUTER_DEFAULT_MD
                  })
              }

              Row() {
                Text(`OUTER_DEFAULT_LG`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.shadow = ShadowStyle.OUTER_DEFAULT_LG
                  })
                Text(`OUTER_FLOATING_SM	`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.shadow = ShadowStyle.OUTER_FLOATING_SM
                  })
                Text(`OUTER_FLOATING_MD`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.shadow = ShadowStyle.OUTER_FLOATING_MD
                  })
              }

              Row() {
                Text('ShadowOptions1')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.shadow = {
                      radius: 10,
                    }
                  })
                Text('ShadowOptions2')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.shadow = {
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
                    this.showDialogOptions.shadow = undefined
                  })
              }

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
                    this.showDialogOptions.enableHoverMode = true
                  })
                Text('false')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.enableHoverMode = false
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.enableHoverMode = undefined
                  })
              }

              Text(`hoverModeArea`)
                .fontSize(9)
                .width("100%")
              Row() {
                Text(`TOP_SCREEN`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.hoverModeArea = HoverModeAreaType.TOP_SCREEN
                  })
                Text('BOTTOM_SCREEN')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.hoverModeArea = HoverModeAreaType.BOTTOM_SCREEN
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.hoverModeArea = undefined
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
                    this.showDialogOptions.onWillAppear = () => {
                      console.info("dialog onWillAppear");
                    }
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.onWillAppear = undefined
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
                    this.showDialogOptions.onDidAppear = () => {
                      console.info("dialog onDidAppear");
                    }
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.onDidAppear = undefined
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
                    this.showDialogOptions.onWillDisappear = () => {
                      console.info("dialog onWillDisappear");
                    }
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.onWillDisappear = undefined
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
                    this.showDialogOptions.onDidDisappear = () => {
                      console.info("dialog onDidDisappear");
                    }
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.onDidDisappear = undefined
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
                    this.showDialogOptions.levelMode = LevelMode.OVERLAY
                  })
                Text('EMBEDDED')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.levelMode = LevelMode.EMBEDDED
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.levelMode = undefined
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
                    this.showDialogOptions.levelUniqueId = 11
                  })
                Text('20')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.levelUniqueId = 20
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.levelUniqueId = undefined
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
                    this.showDialogOptions.immersiveMode = ImmersiveMode.DEFAULT
                  })
                Text('EXTEND')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.immersiveMode = ImmersiveMode.EXTEND
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.immersiveMode = undefined
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
                    this.showDialogOptions.levelOrder = LevelOrder.clamp(1000)
                  })
                Text(`1000000000000`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.levelOrder = LevelOrder.clamp(1000000000000)
                  })
                Text('-10001')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.levelOrder = LevelOrder.clamp(-10001)
                  })
                Text('-1000000000000')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.levelOrder = LevelOrder.clamp(-1000000000000)
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick((e: ClickEvent) => {
                    this.showDialogOptions.levelOrder = undefined
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

@Component
struct Child {
  @State stateVar: string = "Child";
  build() {
    Text(this.stateVar).fontSize(50)
  }
}

export class ComExampleTrivialApplication extends UserView {
  getBuilder() {
    hilog.info(0x0000, 'testTag', 'getBuilder');
    let wrapper = @memo () => {
      hilog.info(0x0000, 'testTag', 'MyStateSample');
      MyStateSample(undefined)
    }
    return wrapper
  }
}