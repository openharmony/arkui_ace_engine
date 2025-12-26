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

import { State } from '@ohos.arkui.stateManagement'
import { Entry, Component, NavDestination, ClickEvent, Dimension, EdgeColors, Column, ColumnOptions, Row, RowOptions,
  Scroll, Scroller, Button, Text, Color, $r, Image, ResourceStr, ResourceColor, SubMenuExpandingMode, MenuOptions,
  ContextMenuOptions, MenuElement, Menu, MenuItem, MenuItemOptions, CustomDialog, PopupOptions, CustomPopupOptions,
  PopupCommonOptions, PopupStateChangeParam, EdgeOutlineWidths, wrapBuilder, AvoidanceMode, Placement,
  PopupMessageOptions, PopupBorderLinearGradient, GradientDirection, ContextMenuAnimationOptions, MenuPreviewMode,
  BlurStyle, ModalMode, PreviewScaleMode, AvailableLayoutArea, ResponseType, CustomDialogController, CustomBuilder,
  CustomBuilderT, FontWeight, Length, TextAlign, TransitionEffect, Curve,AnimationNumberRange, Margin, FlexAlign
} from '@ohos.arkui.component'
import { BusinessError } from '@kit.BasicServicesKit';
import { ComponentContent, FrameNode, Frame } from '@ohos.arkui.node';
import { UIContext, PromptAction, TargetInfo } from '@ohos.arkui.UIContext'
import { SymbolGlyphModifier } from 'arkui.SymbolGlyphModifier';
import promptAction from '@ohos.promptAction';
import hilog from '@ohos.hilog'

let startIcon: ResourceStr = $r('app.media.startIcon')
let endIcon: ResourceStr = $r('app.media.startIcon')
let subMenuExpandingMode: SubMenuExpandingMode | undefined = SubMenuExpandingMode.SIDE_EXPAND;

@Builder
function subMenuBuilder() {
  Menu() {
    MenuItem({
      startIcon: $r('app.media.startIcon'),
      content: '图标',
      builder: subMenuBuilder,
    } as MenuItemOptions)
    MenuItem({
      startIcon: $r('app.media.startIcon'),
      content: '列表',
      builder: subMenuBuilder,
    } as MenuItemOptions)
  }.backgroundColor(Color.Grey)
}

@Builder
function menuBuilder() {
  Menu() {
    MenuItem({
      startIcon: startIcon,
      endIcon: endIcon,
      content: '新建文件夹',
      builder: subMenuBuilder,
    } as MenuItemOptions)
    MenuItem({
      startIcon: startIcon,
      content: '排序方式',
      builder: subMenuBuilder,
    } as MenuItemOptions)
    MenuItem({
      startIcon: startIcon,
      content: '查看方式',
      builder: subMenuBuilder,
    } as MenuItemOptions)
  }
  .backgroundColor(Color.Grey)
  .subMenuExpandingMode(subMenuExpandingMode)
}

@Entry
@Component
struct Index {
  @Builder
  MyPreview() {
    Column({ space: 10 } as ColumnOptions) {
      Image($r('app.media.startIcon'))
        .width(200)
        .height(200)
    }
  }

  @State changeIndex: Int = 0;
  @State changeList: (ResourceColor | undefined)[] = [
    'rgba(23,169,141,0.5)' as ResourceColor, Color.Red as ResourceColor, '#FFFFFF00' as ResourceColor,
    12345 as ResourceColor, $r('app.color.blue') as ResourceColor, undefined,
    $r('app.string.errorColor') as ResourceColor
  ]
  @State changeBlurIndex: Int = 0;
  @State changeBlurList: (BlurStyle | undefined)[] = [
    BlurStyle.Thin, BlurStyle.Regular, BlurStyle.Thick, BlurStyle.BACKGROUND_THIN, BlurStyle.BACKGROUND_REGULAR,
    BlurStyle.BACKGROUND_THICK, BlurStyle.BACKGROUND_ULTRA_THICK, BlurStyle.NONE, BlurStyle.COMPONENT_ULTRA_THIN,
    BlurStyle.COMPONENT_THIN, BlurStyle.COMPONENT_REGULAR, BlurStyle.COMPONENT_THICK, BlurStyle.COMPONENT_ULTRA_THICK,
    undefined
  ]
  private uiContext: UIContext = this.getUIContext();
  private promptAction: PromptAction = this.uiContext.getPromptAction();
  private targetInfo: TargetInfo = {
    id: 'open',
  } as TargetInfo
  private targetInfo1: TargetInfo = {
    id: 'open1',
  } as TargetInfo
  private targetInfo2: TargetInfo = {
    id: 'open2',
  } as TargetInfo
  private targetInfo3: TargetInfo = {
    id: 'open3',
  } as TargetInfo
  private targetInfo4: TargetInfo = {
    id: 'open4',
  } as TargetInfo
  private targetInfo5: TargetInfo = {
    id: 'open5',
  } as TargetInfo
  private targetInfo6: TargetInfo = {
    id: 'open6',
  } as TargetInfo
  private targetInfo7: TargetInfo = {
    id: 'open7',
  } as TargetInfo
  private targetInfo8: TargetInfo = {
    id: 'open8',
  } as TargetInfo
  private targetInfo9: TargetInfo = {
    id: 'open9',
  } as TargetInfo
  private targetInfo10: TargetInfo = {
    id: 'open10',
  } as TargetInfo
  private targetInfo11: TargetInfo = {
    id: 'open11',
  } as TargetInfo
  private targetInfo12: TargetInfo = {
    id: 'open12',
  } as TargetInfo
  private targetInfo13: TargetInfo = {
    id: 'open13',
  } as TargetInfo
  private targetInfo14: TargetInfo = {
    id: 'open14',
  } as TargetInfo
  private targetInfo15: TargetInfo = {
    id: 'open15',
  } as TargetInfo
  private targetInfo16: TargetInfo = {
    id: 'open16',
  } as TargetInfo
  private targetInfo17: TargetInfo = {
    id: 'open17',
  } as TargetInfo
  private targetInfo18: TargetInfo = {
    id: 'open18',
  } as TargetInfo
  private targetInfo19: TargetInfo = {
    id: 'open19',
  } as TargetInfo
  private targetInfo20: TargetInfo = {
    id: 'open20',
  } as TargetInfo
  private targetInfo21: TargetInfo = {
    id: 'open21',
  } as TargetInfo
  private targetInfo22: TargetInfo = {
    id: 'open22',
  } as TargetInfo
  private targetInfo23: TargetInfo = {
    id: 'open23',
  } as TargetInfo
  private targetInfo24: TargetInfo = {
    id: 'open24',
  } as TargetInfo
  menuOptions: MenuOptions = {
    title: '' + this.changeList[this.changeIndex] + '---' + this.changeBlurList[this.changeBlurIndex],
    mask: { color: this.changeList[this.changeIndex], backgroundBlurStyle: this.changeBlurList[this.changeBlurIndex] }

  } as MenuOptions

  build() {
    Column({ space: 10 } as ColumnOptions) {
      Row({ space: 10 } as RowOptions) {
        Text(`Color.Red`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open1')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo1, {
                title: 'Color.Red',
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Thin }

              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
          })
        Text(`rgba(23,169,141,0.5)`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open2')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo2, {
                title: 'rgba(23,169,141,0.5)',
                mask: { color: 'rgba(23,169,141,0.5)', backgroundBlurStyle: BlurStyle.Thin }

              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
          })
        Text(`#FFFFFF00`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open3')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo3, {
                title: '#FFFFFF00',
                mask: { color: '#FFFFFF00', backgroundBlurStyle: BlurStyle.Thin }

              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
          })
      }

      Row({ space: 10 } as RowOptions) {
        Text(`12345`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open4')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo4, {
                title: '12345',
                mask: { color: 12345, backgroundBlurStyle: BlurStyle.Thin }

              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
          })
        Text(`undefined`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open5')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo5, {
                title: 'undefined',
                mask: { color: undefined, backgroundBlurStyle: BlurStyle.Thin }
              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
          })
        Text(`app.color.blue`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open6')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo6, {
                title: 'app.color.blue',
                mask: { color: $r('app.color.blue'), backgroundBlurStyle: BlurStyle.Thin }

              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
          })
      }

      Row({ space: 10 } as RowOptions) {
        Text(`异常`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open21')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo21, {
                title: '异常',
                mask: { color: $r('app.string.errorColor'), backgroundBlurStyle: BlurStyle.Thin }
              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
          })
        Text(`预览默认显示蒙层`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open22')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo22, {
                title: '预览默认显示蒙层',
                preview: this.MyPreview,
                previewBorderRadius: 50,
                previewAnimationOptions: {
                  scale: [0, 0],
                  transition: TransitionEffect.OPACITY.animation({ duration: 4000, curve: Curve.Ease }).combine(
                    TransitionEffect.rotate({ z: 1, angle: 180 })),
                  hoverScale: [1.0, 0.95],
                  hoverScaleInterruption: true,
                },
                previewScaleMode: PreviewScaleMode.AUTO,
                mask: { color: Color.Blue, backgroundBlurStyle: BlurStyle.Thin }
              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
          })
      }

      Row({ space: 10 } as RowOptions) {
        Text(`BlurStyle.Thin`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open7')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo7, {
                title: 'BlurStyle.Thin',
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Thin }
              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
          })
        Text(`BlurStyle.Regular`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open8')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo8, {
                title: 'BlurStyle.Regular',
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Regular }
              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
          })
        Text(`BlurStyle.Thick`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open9')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo9, {
                title: 'BlurStyle.Thick',
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Thick }
              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
          })
      }

      Row({ space: 10 } as RowOptions) {
        Text(`BlurStyle.BACKGROUND_THIN`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open10')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo10, {
                title: 'BlurStyle.BACKGROUND_THIN',
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.BACKGROUND_THIN }
              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
          })
        Text(`BlurStyle.BACKGROUND_REGULAR`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open11')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo11, {
                title: 'BlurStyle.BACKGROUND_REGULAR',
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.BACKGROUND_REGULAR }
              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
          })
        Text(`BlurStyle.BACKGROUND_THICK`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open12')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo12, {
                title: 'BlurStyle.BACKGROUND_THICK',
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.BACKGROUND_THICK }
              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
          })
      }

      Row({ space: 10 } as RowOptions) {
        Text(`BlurStyle.BACKGROUND_ULTRA_THICK`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open13')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo13, {
                title: 'BlurStyle.BACKGROUND_ULTRA_THICK',
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.BACKGROUND_ULTRA_THICK }
              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
          })
        Text(`BlurStyle.NONE`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open14')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo14, {
                title: 'BlurStyle.NONE',
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.NONE }
              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
          })
        Text(`BlurStyle.COMPONENT_ULTRA_THIN`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open15')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo15, {
                title: 'BlurStyle.COMPONENT_ULTRA_THIN',
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.COMPONENT_ULTRA_THIN }
              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
          })
      }

      Row({ space: 10 } as RowOptions) {
        Text(`BlurStyle.COMPONENT_THIN`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open16')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo16, {
                title: 'BlurStyle.COMPONENT_THIN',
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.COMPONENT_THIN }
              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
          })
        Text(`BlurStyle.COMPONENT_REGULAR`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open17')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo17, {
                title: 'BlurStyle.COMPONENT_REGULAR',
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.COMPONENT_REGULAR }
              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
          })
        Text(`BlurStyle.COMPONENT_THICK`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open18')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo18, {
                title: 'BlurStyle.COMPONENT_THICK',
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.COMPONENT_THICK }
              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
          })
      }

      Row({ space: 10 } as RowOptions) {
        Text(`BlurStyle.COMPONENT_ULTRA_THICK`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open19')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo19, {
                title: 'BlurStyle.COMPONENT_ULTRA_THICK',
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.COMPONENT_ULTRA_THICK }
              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
          })
        Text(`undefined`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open20')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo20, {
                title: 'undefined',
                mask: { color: Color.Red, backgroundBlurStyle: undefined }
              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
          })
      }

      Row({ space: 10 } as RowOptions) {
        Text(`true`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open23')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo23, {
                title: 'true',
                mask: true
              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
          })
        Text(`false`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open24')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo24, {
                title: 'false',
                mask: false
              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
          })
      }

      Row({ space: 10 } as RowOptions) {
        Button('切换color')
          .onClick(() => {
            this.changeIndex++
            if (this.changeIndex > this.changeList.length - 1) {
              this.changeIndex = 0
            }
          })
        Button('切换blur')
          .onClick(() => {
            this.changeBlurIndex++
            if (this.changeBlurIndex > this.changeBlurList.length - 1) {
              this.changeBlurIndex = 0
            }
          })
      }

      Row({ space: 10 } as RowOptions) {
        Text(`动态切换调用Menu`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo, {
                title: '' + this.changeList[this.changeIndex] + '---' + this.changeBlurList[this.changeBlurIndex],
                mask: {
                  color: this.changeList[this.changeIndex],
                  backgroundBlurStyle: this.changeBlurList[this.changeBlurIndex]
                }

              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
          })
      }

      Text('Index: ' + this.changeIndex + '数值: ' + this.changeList[this.changeIndex]).fontColor(Color.Red)
      Text('Index: ' + this.changeBlurIndex + '数值: ' + this.changeBlurList[this.changeBlurIndex])
        .fontColor(Color.Green)
    }
    .width('100%')
    .height('100%')
  }
}