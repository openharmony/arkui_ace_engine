'use static'

import { Entry, Component, Builder, Color, Text, TextAttribute, Scroll,Column, Row, Button, ButtonAttribute,
  ClickEvent, UserView, TextStyle, DialogButtonDirection, AlertDialogButtonOptions, List, ListItem, wrapBuilder,
  Menu, MenuItem, MenuItemOptions, MenuItemGroup, TextInput, ComponentV2} from '@ohos.arkui.component'
import { State } from '@ohos.arkui.stateManagement'
import { LevelMode, ImmersiveMode, LevelOrder} from '@ohos.promptAction'
import promptAction from '@ohos.promptAction';
import { Callback, BusinessError } from '@ohos.base';
import { ComponentContent, FrameNode, Frame } from '@ohos.arkui.node';
import { UIContext, OverlayManager, UIInspector, OverlayManagerOptions, PromptAction } from '@ohos.arkui.UIContext'
import { $r } from '@ohos.arkui.component'
import hilog from '@ohos.hilog'
import { BlurStyle, ShadowOptions, ShadowStyle, HoverModeAreaType, Rectangle, TransitionEffect, KeyboardAvoidMode,
  DismissReason, BackgroundBlurStyleOptions, BackgroundEffectOptions, BlurStyleActivePolicy, ThemeColorMode,
  AdaptiveColor, ShadowType  } from 'arkui.component.common';
import { DismissDialogAction } from 'arkui.component.actionSheet';
import { AlertDialogParamWithConfirm, AlertDialogParamWithButtons, AlertDialogParamWithOptions,
  DialogAlignment } from 'arkui.component.alertDialog';
import { WordBreak, DialogButtonStyle, BorderStyle, Alignment, Curve } from 'arkui.component.enums';
import { ActionSheetOptions, ActionSheetButtonOptions } from 'arkui.component.actionSheet';
import { NavPathStack, NavigationOperation, NavBar, Navigation } from 'arkui.component.navigation';
import { ButtonType, ButtonStyleMode, ButtonRole } from 'arkui.component.button';
import { NavDestination } from 'arkui.component.navDestination';
import { Scroller } from 'arkui.component.scroll';
import { ColoringStrategy } from 'arkui.component.enums'
import { Size, Position, Edges, LengthMetrics, SizeT } from 'arkui.Graphics';

@Entry
@Component
struct ActionSheetExample {
  actionSheetOptions: ActionSheetOptions = {
    title: 'title',
    message: 'text',
    sheets: [
      {
        title: '确认',
        action: () => {
          console.log('Click确认');
        }
      },
      {
        title: '取消',
        action: () => {
          console.log('Click取消');
        }
      },
      {
        title: '确认取消',
        action: () => {
          console.log('Click确认取消');
        }
      },
      {
        title: '取消确认',
        action: () => {
          console.log('Click取消确认');
        }
      }],
  } as ActionSheetOptions
  confirm: ActionSheetButtonOptions = {
    value: 'Confirm button',
    action: () => {
      console.info('Click Confirm');
    }
  } as ActionSheetButtonOptions
  scroller: Scroller = new Scroller() as Scroller

  build() {
    NavDestination() {
      Column() {
        Column() {
          Text(`showActionSheet`)
            .fontSize(15)
            .backgroundColor(Color.Orange)
            .margin(3)
            .padding(3)
            .borderWidth(1.0)
            .onClick(() => {
              this.getUIContext().showActionSheet(
                this.actionSheetOptions
              )
            })
        }.borderWidth(1.0)
        .padding(10)
        .width('100%')
        .backgroundColor(Color.Pink)

        Scroll(this.scroller) {
          Column() {
            Column() {
              Text(`title`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`aaa`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.title = 'aaa'
                  })
                Text(`bbb`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.title = 'bbb'
                  })
                Text(`ccc`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.title = $r('app.string.ActionSheet_show_title1')
                  })
              }

              Text(`subtitle`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`aaa`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.subtitle = 'aaa'
                  })
                Text(`bbb`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.subtitle = 'bbb'
                  })
                Text(`ccc`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.subtitle = $r('app.string.ActionSheet_show_title2')
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.subtitle = undefined
                  })
              }

              Text(`message`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`aaa`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.message = 'aaa'
                  })
                Text(`bbb`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.message = 'bbb'
                  })
                Text(`ccc`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.message = $r('app.string.ActionSheet_show_message')
                  })
              }

              Text(`autoCancel`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`true`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.autoCancel = true
                  })
                Text(`false`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.autoCancel = false
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.autoCancel = undefined
                  })
              }

              Text(`confirm`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`confirm`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.confirm = this.confirm
                  })
                Text(`confirm1`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.confirm.value = $r('app.string.showDialog_text')
                    this.confirm.action = () => {
                      console.info('confirm1');
                    }
                    this.actionSheetOptions.confirm = this.confirm
                  })
              }

              Text(`confirm enabled`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`true`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.confirm.enabled = true
                  })
                Text(`false`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.confirm.enabled = false
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.confirm.enabled = undefined
                  })
              }

              Text(`confirm defaultFocus`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`true`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.confirm.defaultFocus = true
                  })
                Text(`false`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.confirm.defaultFocus = false
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.confirm.defaultFocus = undefined
                  })
              }

              Text(`confirm style`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`DEFAULT`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.confirm.style = DialogButtonStyle.DEFAULT
                  })
                Text(`HIGHLIGHT`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.confirm.style = DialogButtonStyle.HIGHLIGHT
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.confirm.style = undefined
                  })
              }

              Text(`cancel`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`logtest`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.cancel = () => {
                      console.log('test');
                    }
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.cancel = undefined
                  })
              }

              Text(`alignment`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`Top`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.alignment = DialogAlignment.Top
                  })
                Text(`Center`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.alignment = DialogAlignment.Center
                  })
                Text(`Bottom`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.alignment = DialogAlignment.Bottom
                  })
                Text(`Default`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.alignment = DialogAlignment.Default
                  })
                Text(`TopStart`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.alignment = DialogAlignment.TopStart
                  })
                Text(`TopEnd`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.alignment = DialogAlignment.TopEnd
                  })
              }
              Row() {
                Text(`CenterStart`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.alignment = DialogAlignment.CenterStart
                  })
                Text(`CenterEnd`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.alignment = DialogAlignment.CenterEnd
                  })
                Text(`BottomStart`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.alignment = DialogAlignment.BottomStart
                  })
                Text(`BottomEnd`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.alignment = DialogAlignment.BottomEnd
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.alignment = undefined
                  })
              }

              Text(`offset`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`40vp`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.offset = { dx: 40, dy: 40 }
                  })
                Text(`aaa`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.offset = { dx: $r('app.float.float_1'), dy: '30%' }
                  })
                Text(`bbb`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.offset = { dx: '30%', dy: $r('app.float.float_1') }
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.offset = undefined
                  })
              }

              Text(`sheets`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`ccc`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.sheets[0].title = $r('app.string.ActionSheet_show_title1')
                    this.actionSheetOptions.sheets[1].title = $r('app.string.ActionSheet_show_title2')
                    this.actionSheetOptions.sheets[2].title = $r('app.string.ActionSheet_show_title1')
                    this.actionSheetOptions.sheets[3].title = $r('app.string.ActionSheet_show_title2')
                    this.actionSheetOptions.sheets[0].action = () => {
                      console.log('确认1');
                    }
                    this.actionSheetOptions.sheets[1].action = () => {
                      console.log('取消1');
                    }
                    this.actionSheetOptions.sheets[2].action = () => {
                      console.log('确认取消1');
                    }
                    this.actionSheetOptions.sheets[3].action = () => {
                      console.log('取消确认1');
                    }
                    this.actionSheetOptions.sheets[0].icon = $r('app.media.startIcon')
                    this.actionSheetOptions.sheets[1].icon = $r('app.media.startIcon')
                    this.actionSheetOptions.sheets[2].icon = $r('app.media.startIcon')
                    this.actionSheetOptions.sheets[3].icon = $r('app.media.startIcon')
                  })
                Text(`资源值`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.sheets[0].title = $r('app.string.ActionSheet_show_title1')
                    this.actionSheetOptions.sheets[1].title = $r('app.string.ActionSheet_show_title2')
                    this.actionSheetOptions.sheets[2].title = $r('app.string.ActionSheet_show_title1')
                    this.actionSheetOptions.sheets[3].title = $r('app.string.ActionSheet_show_title2')
                    this.actionSheetOptions.sheets[0].action = () => {
                      console.log('确认11');
                    }
                    this.actionSheetOptions.sheets[1].action = () => {
                      console.log('取消1');
                    }
                    this.actionSheetOptions.sheets[2].action = () => {
                      console.log('确认取消1');
                    }
                    this.actionSheetOptions.sheets[3].action = () => {
                      console.log('取消确认1');
                    }
                    this.actionSheetOptions.sheets[0].icon = $r('app.media.background')
                    this.actionSheetOptions.sheets[1].icon = $r('app.media.background')
                    this.actionSheetOptions.sheets[2].icon = $r('app.media.background')
                    this.actionSheetOptions.sheets[3].icon = $r('app.media.background')
                  })
              }

              Text(`maskRect`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`0%`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.maskRect = {
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
                  .onClick(() => {
                    this.actionSheetOptions.maskRect = {
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
                  .onClick(() => {
                    this.actionSheetOptions.maskRect = undefined
                  })
              }

              Text(`showInSubWindow`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`true`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.showInSubWindow = true
                  })
                Text(`false`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.showInSubWindow = false
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.showInSubWindow = undefined
                  })
              }

              Text(`isModal`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`true`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.isModal = true
                  })
                Text(`false`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.isModal = false
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.isModal = undefined
                  })
              }

              Text(`backgroundColor`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`Red`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.backgroundColor = Color.Red
                  })
                Text('#330be9d0')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.backgroundColor = '#330be9d0'
                  })
                Text('资源值')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.backgroundColor = $r('app.color.Color_pink')
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.backgroundColor = undefined
                  })
              }

              Text(`backgroundBlurStyle`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`Thin`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.backgroundBlurStyle = BlurStyle.Thin
                  })
                Text(`Regular`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.backgroundBlurStyle = BlurStyle.Regular
                  })
                Text(`Thick`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.backgroundBlurStyle = BlurStyle.Thick
                  })
                Text(`BACKGROUND_THIN`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.backgroundBlurStyle = BlurStyle.BACKGROUND_THIN
                  })
                Text(`BACKGROUND_REGULAR`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.backgroundBlurStyle = BlurStyle.BACKGROUND_REGULAR
                  })
              }
              Row() {
                Text(`BACKGROUND_ULTRA_THICK`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.backgroundBlurStyle = BlurStyle.BACKGROUND_ULTRA_THICK
                  })
                Text(`NONE`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.backgroundBlurStyle = BlurStyle.NONE
                  })
                Text(`COMPONENT_ULTRA_THIN`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.backgroundBlurStyle = BlurStyle.COMPONENT_ULTRA_THIN
                  })
              }
              Row() {
                Text(`COMPONENT_THIN`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.backgroundBlurStyle = BlurStyle.COMPONENT_THIN
                  })
                Text(`COMPONENT_REGULAR`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.backgroundBlurStyle = BlurStyle.COMPONENT_REGULAR
                  })
                Text(`COMPONENT_THICK`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.backgroundBlurStyle = BlurStyle.COMPONENT_THICK
                  })
              }
              Row() {
                Text(`COMPONENT_ULTRA_THICK`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.backgroundBlurStyle = BlurStyle.COMPONENT_ULTRA_THICK
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.backgroundBlurStyle = undefined
                  })
              }

              Text(`backgroundBlurStyleOptions`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`000`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.backgroundBlurStyleOptions = {
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
                  .onClick(() => {
                    this.actionSheetOptions.backgroundBlurStyleOptions = {
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
                  .onClick(() => {
                    this.actionSheetOptions.backgroundBlurStyleOptions = {
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
                  .onClick(() => {
                    this.actionSheetOptions.backgroundBlurStyleOptions = {
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
                  .onClick(() => {
                    this.actionSheetOptions.backgroundBlurStyleOptions = {
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
                  .onClick(() => {
                    this.actionSheetOptions.backgroundBlurStyleOptions = {
                      inactiveColor: undefined,
                      blurOptions: undefined,
                    } as BackgroundBlurStyleOptions
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.backgroundBlurStyleOptions = undefined
                  })
              }

              Text(`backgroundEffect`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`000`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.backgroundEffect = {
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
                  .onClick(() => {
                    this.actionSheetOptions.backgroundEffect = {
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
                  .onClick(() => {
                    this.actionSheetOptions.backgroundEffect = {
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
                  .onClick(() => {
                    this.actionSheetOptions.backgroundEffect = {
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
                  .onClick(() => {
                    this.actionSheetOptions.backgroundEffect = {
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
                  .onClick(() => {
                    this.actionSheetOptions.backgroundEffect = {
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
                  .onClick(() => {
                    this.actionSheetOptions.backgroundEffect = undefined
                  })
              }

              Text(`onWillDismiss`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`onWillDismiss`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.onWillDismiss = (dismissDialogAction: DismissDialogAction) => {
                      console.info('reason=' + JSON.stringify(dismissDialogAction.reason));
                      console.info('dialog onWillDismiss');
                      if (dismissDialogAction.reason === DismissReason.PRESS_BACK) {
                        console.info('dialog onWillDismiss');
                        dismissDialogAction.dismiss();
                      }
                      if (dismissDialogAction.reason === DismissReason.TOUCH_OUTSIDE) {
                        console.info('dialog onWillDismiss');
                        dismissDialogAction.dismiss();
                      }
                    }
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.onWillDismiss = undefined
                  })
              }

              Text(`cornerRadius`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`0vp`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.cornerRadius = '0vp'
                  })
                Text(`30%`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.cornerRadius = '30%'
                  })
                Text(`第二个`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.cornerRadius = {
                      topLeft: '50px',
                      topRight: '50vp',
                      bottomLeft: $r('app.float.float_9'),
                      bottomRight: '50%',
                    }
                  })
                Text(`第三个`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.cornerRadius = {
                      topStart: LengthMetrics.px(50),
                      topEnd: LengthMetrics.vp(50),
                      bottomStart: LengthMetrics.resource($r('app.float.float_9')),
                      bottomEnd: LengthMetrics.percent(0.5),
                    }
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.cornerRadius = undefined
                  })
              }

              Text(`transition`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`aaa`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.transition = TransitionEffect.asymmetric(
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
                  .onClick(() => {
                    this.actionSheetOptions.transition = TransitionEffect.scale({ x: 1, y: 0 })
                      .animation({ duration: 3000, curve: Curve.Ease })
                  })
                Text(`ccc`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.transition = TransitionEffect.OPACITY
                      .animation({ duration: 4000, curve: Curve.Ease })
                      .combine(TransitionEffect.rotate({ z: 1, angle: 180 }))
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.transition = undefined
                  })
              }

              Text(`width`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`200vp`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.width = '200vp'
                  })
                Text(`80%`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.width = '80%'
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.width = undefined
                  })
              }

              Text(`height`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`200vp`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.height = '200vp'
                  })
                Text(`80%`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.height = '80%'
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.height = undefined
                  })
              }

              Text(`borderWidth`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`5vp`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.borderWidth = '5vp'
                  })
                Text(`30%`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.borderWidth = '30%'
                  })
                Text(`第二个`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.borderWidth = {
                      top: '50px',
                      right: '50vp',
                      bottom: $r('app.float.float_9'),
                      left: '50%',
                    }
                  })
                Text(`第三个`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.borderWidth = {
                      top: LengthMetrics.px(50),
                      end: LengthMetrics.vp(50),
                      bottom: LengthMetrics.resource($r('app.float.float_9')),
                      start: LengthMetrics.percent(0.5),
                    }
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.borderWidth = undefined
                  })
              }

              Text(`borderColor`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`Red`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.borderColor = Color.Red
                  })
                Text('Yellow')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.borderColor = Color.Yellow
                  })
                Text(`第二个`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.borderColor = {
                      top: Color.Red,
                      right: '#330be9d0',
                      bottom: $r('app.color.Color_pink'),
                      left: 'rgba(23,169,141,0.5)',
                    }
                  })
                Text(`第三个`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.borderColor = {
                      top: Color.Red,
                      end: '#330be9d0',
                      bottom: $r('app.color.Color_pink'),
                      start: 'rgba(23,169,141,0.5)',
                    }
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.borderColor = undefined
                  })
              }

              Text(`borderStyle`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`Dotted`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.borderStyle = BorderStyle.Dotted
                  })
                Text('Dashed')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.borderStyle = BorderStyle.Dashed
                  })
                Text(`Solid`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.borderStyle = BorderStyle.Solid
                  })
                Text('aaa')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.borderStyle = {
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
                  .onClick(() => {
                    this.actionSheetOptions.borderStyle = undefined
                  })
              }

              Text(`shadow`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`OUTER_DEFAULT_XS`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.shadow = ShadowStyle.OUTER_DEFAULT_XS
                  })
                Text(`OUTER_DEFAULT_SM`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.shadow = ShadowStyle.OUTER_DEFAULT_SM
                  })
                Text(`OUTER_DEFAULT_MD`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.shadow = ShadowStyle.OUTER_DEFAULT_MD
                  })
              }
              Row() {
                Text(`OUTER_DEFAULT_LG`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.shadow = ShadowStyle.OUTER_DEFAULT_LG
                  })
                Text(`OUTER_FLOATING_SM	`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.shadow = ShadowStyle.OUTER_FLOATING_SM
                  })
                Text(`OUTER_FLOATING_MD`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.shadow = ShadowStyle.OUTER_FLOATING_MD
                  })
              }
              Row() {
                Text('ShadowOptions1')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.shadow = {
                      radius: 10,
                    } as ShadowOptions
                  })
                Text('ShadowOptions2')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.shadow = {
                      radius: 10,
                      type: ShadowType.BLUR,
                      color: $r('app.color.Color_pink'),
                      offsetX: 22,
                      offsetY: $r('app.float.float_9'),
                      fill: true,
                    } as ShadowOptions
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.shadow = undefined
                  })
              }

              Text(`enableHoverMode`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`true`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.enableHoverMode = true
                  })
                Text('false')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.enableHoverMode = false
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.enableHoverMode = undefined
                  })
              }

              Text(`hoverModeArea`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`TOP_SCREEN`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.hoverModeArea = HoverModeAreaType.TOP_SCREEN
                  })
                Text('BOTTOM_SCREEN')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.hoverModeArea = HoverModeAreaType.BOTTOM_SCREEN
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.hoverModeArea = undefined
                  })
              }

              Text(`onWillAppear`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`onWillAppear`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.onWillAppear = () => {
                      console.info('dialog onWillAppear');
                    }
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.onWillAppear = undefined
                  })
              }

              Text(`onDidAppear`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`onDidAppear`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.onDidAppear = () => {
                      console.info('dialog onDidAppear');
                    }
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.onDidAppear = undefined
                  })
              }

              Text(`onWillDisappear`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`onWillDisappear`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.onWillDisappear = () => {
                      console.info('dialog onWillDisappear');
                    }
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.onWillDisappear = undefined
                  })
              }

              Text(`onDidDisappear`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`onDidDisappear`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.onDidDisappear = () => {
                      console.info('dialog onDidDisappear');
                    }
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.onDidDisappear = undefined
                  })
              }

              Text(`levelMode`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`OVERLAY`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.levelMode = LevelMode.OVERLAY
                  })
                Text('EMBEDDED')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.levelMode = LevelMode.EMBEDDED
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.levelMode = undefined
                  })
              }

              Text(`levelUniqueId`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`11`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.levelUniqueId = 11
                  })
                Text('20')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.levelUniqueId = 20
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.levelUniqueId = undefined
                  })
              }

              Text(`immersiveMode`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`DEFAULT`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.immersiveMode = ImmersiveMode.DEFAULT
                  })
                Text('EXTEND')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.immersiveMode = ImmersiveMode.EXTEND
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.immersiveMode = undefined
                  })
              }

              Text(`levelOrder`)
                .fontSize(9)
                .width('100%')
              Row() {
                Text(`1000`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.levelOrder = LevelOrder.clamp(1000)
                  })
                Text(`1000000000000`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.levelOrder = LevelOrder.clamp(1000000000000)
                  })
                Text('-10001')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.levelOrder = LevelOrder.clamp(-10001)
                  })
                Text('-1000000000000')
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.levelOrder = LevelOrder.clamp(-1000000000000)
                  })
                Text(`undefined`)
                  .fontSize(10)
                  .backgroundColor(0x0000ff)
                  .fontColor(0xffffff)
                  .padding(5)
                  .onClick(() => {
                    this.actionSheetOptions.levelOrder = undefined
                  })
              }
            }.borderWidth(1.0)
            .padding(10)
            .width('100%')
            .backgroundColor(Color.Pink)

            Column()
              .borderWidth(1.0)
              .padding(10)
              .width('100%')
              .backgroundColor(Color.Pink)
              .height(200)
          }
        }
      }
    }
  }
}
