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
import { MyComponent } from './MyComponenet'
import { Popup, PopupTextOptions, PopupButtonOptions, PopupIconOptions, ComponentContent } from '@kit.ArkUI';
import { BusinessError } from '@kit.BasicServicesKit'

@Builder
export function UIContextPopupBuilder(name: string, param: Object) {
  UIContextPopupExample()
}

interface TargetTransOptions {
  // 尺寸
  width?: Length
  height?: Length

  // 偏移
  offset?: Position

  // 图形变化
  rotation?: Optional<RotateOptions>
  translate?: Optional<TranslateOptions>
  scale?: Optional<ScaleOptions>
}

// 全局气泡的wrapperBuilder
@Builder
export function popupDemo() {
  Row() {
    // popup 自定义高级组件
    Popup({
      // PopupIconOptions类型设置图标内容
      icon: {
        image: $r('app.media.app_icon'),
        width: 32,
        height: 32,
        fillColor: Color.White,
        borderRadius: 16
      } as PopupIconOptions,
      // PopupTextOptions类型设置文字内容
      title: {
        text: 'This is a popup with PopupOptions',
        fontSize: 20,
        fontColor: Color.Black,
        fontWeight: FontWeight.Normal
      } as PopupTextOptions,
      // PopupTextOptions类型设置文字内容
      message: {
        text: 'This is the message',
        fontSize: 15,
        fontColor: Color.Black
      } as PopupTextOptions,
      showClose: false,
      onClose: () => {
        console.info('close Button click')
      },
      // PopupButtonOptions类型设置按钮内容
      buttons: [{
        text: 'confirm',
        action: () => {
          console.info('confirm button click')
        },
        fontSize: 15,
        fontColor: Color.Black,
      },
        {
          text: 'cancel',
          action: () => {
            console.info('cancel button click')
          },
          fontSize: 15,
          fontColor: Color.Black
        }] as [PopupButtonOptions?, PopupButtonOptions?]
    })
  }
}

@Extend(Text) function paramTextStyle() {
  .fontSize(9)
  .width('100%')
}

@Extend(Text) function componentTextStyle() {
  .fontSize(15)
  .backgroundColor(Color.Orange)
  .margin(5)
  .padding(5)
}

@Extend(Column) function columnStyle() {
  .borderWidth(1.0)
  .padding(10)
  .width('100%')
  .backgroundColor(Color.Pink)
}

@Extend(Select) function selectStyle() {
  .width('50%')
  .controlSize(ControlSize.SMALL)
  .backgroundColor(Color.Orange)
}

@Entry
@Component
struct UIContextPopupExample {
  pathStack: NavPathStack = new NavPathStack()
  scroller: Scroller = new Scroller()

  @State duration: number = 1000
  @State partialUpdate: boolean = false
  @State openPopupOptInfo: string = 'openPopupOpt不设置'
  @State updatePopupOptionInfo: string = 'updatePopupOpt'
  @State popupOption: PopupCommonOptions = {}
  @State columnAlignHorizontal: HorizontalAlign = HorizontalAlign.Center
  @State columnAlignFlex: FlexAlign = FlexAlign.Start
  @State targetTransOpt: TargetTransOptions | undefined = undefined

  build() {
    NavDestination() {
      Stack(){
        // 绑定组件的布局
        Scroll(){
          Column(){
            Text('绑定组件')
              .backgroundColor('#4d000000')
              .id('targetCube')
              .rotate(this.targetTransOpt?.rotation)
              .scale(this.targetTransOpt?.scale)
          }
          .alignItems(this.columnAlignHorizontal)
          .justifyContent(this.columnAlignFlex)
          .width('100%')
          .height('100%')
        }
        .width('100%')
        .height('100%')
        .borderWidth(0.5)
        .borderColor(Color.Green)
        .backgroundColor(Color.Transparent)

        // 控制区域
        Scroll(this.scroller){
          Column({space: 5}){
            Text(`UIContext_updatePopup`)
              .paramTextStyle()
            Column({space: 5}){
              Text(`验证updatePopup入参content/ 错误码`)
                .paramTextStyle()
              Text(`更新不同content气泡`)
                .componentTextStyle()
                .id('targetComponent')
                .onClick( () => {
                  let contentNode = new ComponentContent(this.getUIContext(), wrapBuilder(popupDemo));
                  this.getUIContext().getPromptAction().openPopup(contentNode, {id: 'targetComponent'}, {
                    popupColor: '#800a59f7',
                    backgroundBlurStyle: BlurStyle.Thin
                  })

                  setTimeout( () => {
                    let contentNode1 = new ComponentContent(this.getUIContext(), wrapBuilder(popupDemo));
                    try {
                      this.getUIContext().getPromptAction().updatePopup(contentNode1, {
                        popupColor: Color.Orange,
                        backgroundBlurStyle: BlurStyle.NONE
                      })
                        .then(() => {
                          console.info('LCG  updatePopup via dif content success');
                        })
                        .catch((err: BusinessError) => {
                          console.info('LCG  updatePopup via dif content error: ' + err.code + ' ' + err.message);
                        })

                    } catch (error) {
                      let message = (error as BusinessError).message;
                      let code = (error as BusinessError).code;
                      console.error(`LCG  updatePopup via dif content error code is ${code}, message is ${message}`);
                    };
                  }, this.duration)
                })
            }
            .columnStyle()

            Column({space: 5}){
              Text(`验证updatePopup入参options/ partialUpdate`)
                .paramTextStyle()
              Text(`调整绑定cube位置`)
                .paramTextStyle()
              Select([
                { value:'TopStart' },
                { value:'TopCenter' },
                { value:'TopEnd' },
                { value:'MidStart' },
                { value:'MidCenter' },
                { value:'MidEnd' },
                { value:'BotStart' },
                { value:'BotCenter' },
                { value:'BotEnd' },
              ])
                .value('TopCenter')
                .selected(1)
                .selectStyle()
                .onSelect((idx, value: string) => {
                  switch (value) {
                    case 'TopStart':
                      this.columnAlignHorizontal = HorizontalAlign.Start
                      this.columnAlignFlex = FlexAlign.Start
                      break;
                    case 'MidStart':
                      this.columnAlignHorizontal = HorizontalAlign.Start
                      this.columnAlignFlex = FlexAlign.Center
                      break;
                    case 'BotStart':
                      this.columnAlignHorizontal = HorizontalAlign.Start
                      this.columnAlignFlex = FlexAlign.End
                      break;
                    case 'TopCenter':
                      this.columnAlignHorizontal = HorizontalAlign.Center
                      this.columnAlignFlex = FlexAlign.Start
                      break;
                    case 'MidCenter':
                      this.columnAlignHorizontal = HorizontalAlign.Center
                      this.columnAlignFlex = FlexAlign.Center
                      break;
                    case 'BotCenter':
                      this.columnAlignHorizontal = HorizontalAlign.Center
                      this.columnAlignFlex = FlexAlign.End
                      break;
                    case 'TopEnd':
                      this.columnAlignHorizontal = HorizontalAlign.End
                      this.columnAlignFlex = FlexAlign.Start
                      break;
                    case 'MidEnd':
                      this.columnAlignHorizontal = HorizontalAlign.End
                      this.columnAlignFlex = FlexAlign.Center
                      break;
                    case 'BotEnd':
                      this.columnAlignHorizontal = HorizontalAlign.End
                      this.columnAlignFlex = FlexAlign.End
                      break;
                  }
                })
                .key('select_targetCube_placement')

              Text(`切换气泡更新方式`)
                .paramTextStyle()
              Select([
                { value:'增量更新(T)' },
                { value:'全量更新(F)' },

              ])
                .selectStyle()
                .onSelect((idx, value: string) => {
                  switch (value) {
                    case '增量更新(T)':
                      this.partialUpdate = true
                      break;
                    case '全量更新(F)':
                      this.partialUpdate = false
                      break;
                  }
                })
                .key('select_partialUpdate')

              Text(`更新气泡opt不可更新的属性: 预期不变更`)
                .paramTextStyle()
              Text(`不支持更新的属性`)
                .componentTextStyle()
                .onClick( () => {
                  let contentNode = new ComponentContent(this.getUIContext(), wrapBuilder(popupDemo));

                  try {
                    this.getUIContext().getPromptAction().openPopup(contentNode, {id: 'targetCube'},
                      {
                        showInSubWindow: false,
                        onStateChange: (e) => {
                          console.info('LCG  openPopup onStateChange log')
                        },
                        focusable: false,
                        transition: TransitionEffect.OPACITY.animation({ duration: 800, curve: Curve.Ease }),
                        onWillDismiss: ( (dismissPopupAction: DismissPopupAction) => {
                          console.info('dismissReason:' + JSON.stringify(dismissPopupAction.reason))
                          dismissPopupAction.dismiss()
                        }
                        )
                      })
                      .then(() => {
                        console.info('LCG  openPopup success');
                      })
                      .catch((err: BusinessError) => {
                        console.info('LCG  openPopup error: ' + err.code + ' ' + err.message);
                      })

                  } catch (error) {
                    let message = (error as BusinessError).message;
                    let code = (error as BusinessError).code;
                    console.error(`LCG  openPopup error code is ${code}, message is ${message}`);
                  };

                  setTimeout( () => {
                    try {
                      this.getUIContext().getPromptAction().updatePopup(contentNode,                       {
                        popupColor: '#26000000',
                        backgroundBlurStyle: BlurStyle.Thin,

                        showInSubWindow: true,
                        onStateChange: (e) => {
                          console.info('LCG  updatePopup onStateChange log')
                        },
                        focusable: true,
                        transition: TransitionEffect
                          .scale({ x: 1, y: 0 })
                          .animation({ duration: 800, curve: Curve.Ease }),
                        onWillDismiss: false,
                      })
                        .then(() => {
                          console.info('LCG  updatePopup success');
                        })
                        .catch((err: BusinessError) => {
                          console.info('LCG  updatePopup error: ' + err.code + ' ' + err.message);
                        })

                    } catch (error) {
                      let message = (error as BusinessError).message;
                      let code = (error as BusinessError).code;
                      console.error(`LCG  updatePopup error code is ${code}, message is ${message}`);
                    };
                  }, this.duration)
                })

              Text(`切换菜单opt可更新的属性不同参数`)
                .paramTextStyle()
              Row({space: 3}){
                Select([
                  { value:'openPopupOpt不设置' },
                  { value:'openPopupOpt设置{}' },
                  { value:'openPopupOpt设置跟随气泡' },
                  { value:'openPopupOpt设置无遮罩层/非auto' },
                ])
                  .selectStyle()
                  .onSelect((idx, value: string) => {
                    switch (value) {
                      case value:
                        this.openPopupOptInfo = value
                        break;
                    }
                  })
                  .key('select_openPopupOpt')
                  .layoutWeight(1)

                Select([
                  { value:'updatePopupOpt设置{}' },
                  { value:'updatePopupOpt更新位置' },
                  { value:'updatePopupOpt更新箭头' },
                  { value:'updatePopupOpt更新背板/遮罩层样式' },
                  { value:'updatePopupOpt更新跟随方式' },
                  { value:'updatePopupOpt设置跟随气泡' },
                ])
                  .selectStyle()
                  .onSelect((idx, value: string) => {
                    switch (value) {
                      case 'updatePopupOpt设置{}':
                        this.popupOption = {}
                        break;
                      case 'updatePopupOpt更新位置':
                        this.popupOption = {
                          placement: Placement.Right,
                          offset: {x: 0, y: 30}
                        }
                        break;
                      case 'updatePopupOpt更新箭头':
                        this.popupOption = {
                          enableArrow: true,
                          arrowOffset: 40
                        }
                        break;
                      case 'updatePopupOpt更新背板样式':
                        this.popupOption = {
                          popupColor: '#7F0A59F7',
                          backgroundBlurStyle: BlurStyle.Thin,

                          radius: 4,
                          mask: {color: '#260A59F7'}
                        }
                        break;
                      case 'updatePopupOpt设置跟随气泡':
                        this.updatePopupOptionInfo = 'updatePopupOpt设置跟随气泡'
                        this.popupOption = {
                          popupColor: '#26000000',
                          backgroundBlurStyle: BlurStyle.Thin,

                          followTransformOfTarget: true
                        }
                        break;
                    }
                  })
                  .key('select_updatePopupOpt')
                  .layoutWeight(1)
              }

              Text(`绑定组件变换的duration:${this.duration}`)
                .paramTextStyle()
              Row({space: 3}){
                MyComponent({title: 'dur: 1600', func: () => {
                  this.duration = 1600
                }})
                MyComponent({title: 'dur: 2400', func: () => {
                  this.duration = 2400
                }})
              }

              Text(`支持更新的属性`)
                .componentTextStyle()
                .onClick( () => {
                  let contentNode = new ComponentContent(this.getUIContext(), wrapBuilder(popupDemo));

                  try {
                    if (this.openPopupOptInfo === 'openPopupOpt不设置') {
                      this.getUIContext().getPromptAction().openPopup(contentNode, {id: 'targetCube'})
                    } else if ( this.openPopupOptInfo === 'openPopupOpt设置{}') {
                      this.getUIContext().getPromptAction().openPopup(contentNode, {id: 'targetCube'}, {
                      })
                    } else if ( this.openPopupOptInfo === 'openPopupOpt设置跟随气泡') {
                      this.getUIContext().getPromptAction().openPopup(contentNode, {id: 'targetCube'}, {
                        followTransformOfTarget: true
                      })
                    } else if ( this.openPopupOptInfo === 'openPopupOpt设置无遮罩层/非auto') {
                      this.getUIContext().getPromptAction().openPopup(contentNode, {id: 'targetCube'}, {
                        mask: false,
                        autoCancel: false
                      })
                    }
                  } catch (error) {
                    let message = (error as BusinessError).message;
                    let code = (error as BusinessError).code;
                    console.error(`LCG  openPopup error code is ${code}, message is ${message}`);
                  };

                  setTimeout( () => {
                    if (this.openPopupOptInfo === 'openPopupOpt设置跟随气泡' || this.updatePopupOptionInfo === 'updatePopupOpt设置跟随气泡') {
                      this.targetTransOpt = {
                        rotation: {
                          x: 0,
                          y: 0,
                          z: 1,
                          centerX: '50%',
                          centerY: '50%',
                          angle: 300
                        },
                        scale: { x: 2, y: 0.7 }
                      }
                    }
                  }, (this.duration - 1200))

                  setTimeout( () => {
                    try {
                      this.getUIContext()
                        .getPromptAction()
                        .updatePopup(contentNode, this.popupOption, this.partialUpdate)
                    } catch (error) {
                      let message = (error as BusinessError).message;
                      let code = (error as BusinessError).code;
                      console.error(`LCG  updatePopup error code is ${code}, message is ${message}`);
                    };
                  }, this.duration)

                  setTimeout( () => {
                    if (this.openPopupOptInfo === 'openPopupOpt设置跟随气泡' || this.updatePopupOptionInfo === 'updatePopupOpt设置跟随气泡') {
                      this.targetTransOpt = {
                      }
                      this.updatePopupOptionInfo = 'updatePopupOpt'
                    }
                  }, (this.duration + 1000))
                })
            }
            .columnStyle()

          }
          .width('100%')
        }
        .padding(12)
        .scrollBar(BarState.Off)
        .align(Alignment.TopStart)
        .width('100%')
        .height('100%')
      }
      .alignContent(Alignment.Center)
      .width('100%')
      .height('100%')
    }
    .title('UIContextPopup')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
