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

import { promptAction, ComponentContent } from '@kit.ArkUI'
import { BusinessError } from '@kit.BasicServicesKit';
import { TargetInfo } from '@ohos.arkui.UIContext'
import { MyComponent } from '../base/MyComponent'
import { MenuBuilder, MenuAttrOptions } from './MenuBuilder'

@Builder
export function MenuLevel2Builder() {
  MenuLevel2Example()
}

// 菜单的wrapBuilder
@Builder
export function MenuDemo(params: MenuAttrOptions) {
  MenuBuilder({ menuAttrOptions: { submenuMode: params.submenuMode } })
}

// 菜单预览图
@Builder
export function PreviewBuilder() {
  Image($r('app.media.app_icon'))
    .width(200)
    .height(120)
}

@Extend(Text)
function paramTextStyle() {
  .fontSize(9)
  .width('100%')
}

@Extend(Text)
function componentTextStyle() {
  .fontSize(15)
  .backgroundColor(Color.Orange)
  .margin(3)
  .padding(3)
  .borderWidth(1.0)
}

@Extend(Column)
function columnStyle() {
  .borderWidth(1.0)
  .padding(10)
  .width('100%')
  .backgroundColor(Color.Pink)
}


@Entry
@Component
struct MenuLevel2Example {
  pathStack: NavPathStack = new NavPathStack()
  scroller: Scroller = new Scroller()
  @State index: number[] = [0,]
  @State isShow: boolean = false
  // setTimeOut duration
  @State duration: number = 2000
  // Menu指向的绑定节点
  @State targetInfo: TargetInfo = {
    id: 'targetComponent',
  }
  // partialUpdate
  @State partialUpdate: boolean = false
  // MenuBuilder的入参
  @State menuAttrOptions: MenuAttrOptions = {
    submenuMode: 2,
  }
  // openMenu的options
  @State menuOptions: MenuOptions = {
    title: '菜单Title',
    placement: Placement.Bottom,
    offset: { x: 30, y: 30 },
    borderRadius: 10,
    enableArrow: true,
    arrowOffset: 20,
    backgroundColor: Color.Orange,
    backgroundBlurStyle: BlurStyle.NONE,
    preview: MenuPreviewMode.IMAGE,
    previewBorderRadius: 4,
    layoutRegionMargin: { top: 100, left: 20, right: 20 },
    previewAnimationOptions: {
      hoverScale: [0.3, 0.95],
      scale: [0.95, 2.0]
    },
    transition: TransitionEffect.OPACITY.animation({ duration: 800, curve: Curve.Ease }),
  }
  private iconStr: Resource = $r('app.media.app_icon')
  @State modalModeArray: Array<ModalMode | undefined> = [
    ModalMode.AUTO,
    ModalMode.NONE,
    ModalMode.TARGET_WINDOW,
    undefined,
    -1,
    4,
  ]
  @State modalModeIndex: number = 0
  private showInSunWindowArray: (boolean | undefined)[] = [
    true,
    false,
    undefined,
  ]
  @State showInSunWindowIndex: number = 0
  @State isShow1: boolean = false
  @State isShow2: boolean = false
  @State isShow3: boolean = false

  @Builder
  MyMenu1() {
    Menu() {
      MenuItem({ startIcon: this.iconStr, content: '菜单选项' })
      MenuItem({ content: '菜单选项' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项' })
      MenuItem({ content: '菜单选项' })
    }
  }

  build() {
    NavDestination() {
      Scroll() {
        Column() {
          Button('001、bindMenu_MenuElement')
            .fontWeight(FontWeight.Bold)
            .bindMenu(
              [
                {
                  value: 'Menu1',
                  action: () => {
                    console.info('handle Menu1 select');
                  }
                },
                {
                  value: 'Menu2',
                  action: () => {
                    console.info('handle Menu2 select');
                  }
                }
              ],
              {
                modalMode: this.modalModeArray[this.modalModeIndex],
                showInSubWindow: this.showInSunWindowArray[this.showInSunWindowIndex],
              }
            )
          Button('002、bindMenu_isShow')
            .fontWeight(FontWeight.Bold)
            .onClick(() => {
              this.isShow1 = true
            })
            .bindMenu(this.isShow1, this.MyMenu1(), {
              showInSubWindow: this.showInSunWindowArray[this.showInSunWindowIndex],
              modalMode: this.modalModeArray[this.modalModeIndex],
              onDisappear: () => {
                this.isShow1 = false
              }
            })

          Button('003、bindContextMenu')
            .fontWeight(FontWeight.Bold)
            .onClick(() => {

            })
            .bindContextMenu(this.MyMenu1(), ResponseType.LongPress, {
              modalMode: this.modalModeArray[this.modalModeIndex],

            })


          Button('004、bindContextMenu_isShow')
            .fontWeight(FontWeight.Bold)
            .onClick(() => {
              this.isShow2 = true
            })
            .bindContextMenu(this.isShow2, this.MyMenu1(), {
              modalMode: this.modalModeArray[this.modalModeIndex],
              onDisappear: () => {
                this.isShow2 = false
              }
            })
          Button('005、bindContextMenu_isShow')
            .fontWeight(FontWeight.Bold)
            .onClick(() => {
              this.isShow3 = true
            })
            .bindContextMenu(this.isShow3, this.MyMenu1(), {
              preview: MenuPreviewMode.IMAGE,
              mask: true,
              modalMode: this.modalModeArray[this.modalModeIndex],
              onDisappear: () => {
                this.isShow3 = false
              }
            })

          Button('111、modalMode=' + this.modalModeArray[this.modalModeIndex] + ', index=' + this.modalModeIndex)
            .onClick((event: ClickEvent) => {
              if (this.modalModeIndex >= this.modalModeArray.length - 1) {
                this.modalModeIndex = 0;
              } else {
                this.modalModeIndex = this.modalModeIndex + 1;
              }
            })
          Button('222、showInSunWindow=' + this.showInSunWindowArray[this.showInSunWindowIndex] + ', index=' +
          this.showInSunWindowIndex)
            .onClick((event: ClickEvent) => {
              if (this.showInSunWindowIndex >= this.showInSunWindowArray.length - 1) {
                this.showInSunWindowIndex = 0;
              } else {
                this.showInSunWindowIndex = this.showInSunWindowIndex + 1;
              }
            })
          Button('Hello')
            .width(100)
            .margin({ top: 50 })
            .height(50)
            .onClick(() => {
              promptAction.showToast({
                message: 'Clicked!'
              })
            })
          Scroll(this.scroller) {
            Column({ space: 5 }) {
              Text(`Text`)
                .paramTextStyle()
                .bindMenu(this.isShow!!, MenuDemo(this.menuAttrOptions), this.menuOptions)

              Column({ space: 5 }) {
                Text(`targetComponent`)
                  .componentTextStyle()
                  .id('targetComponent')
                  .bindMenu(this.isShow!!, MenuDemo(this.menuAttrOptions), this.menuOptions)

                MyComponent({
                  title: 'bindMenu菜单', func: () => {
                    this.isShow = !this.isShow
                  }
                })
                MyComponent({
                  title: '005、openMenu', func: () => {
                    let uiContext = this.getUIContext();
                    let promptAction = uiContext.getPromptAction();

                    let contentNode = new ComponentContent(uiContext, wrapBuilder(MenuDemo), this.menuAttrOptions);
                    try {
                      promptAction.openMenu(contentNode, this.targetInfo, {
                        modalMode: this.modalModeArray[this.modalModeIndex],
                        showInSubWindow: this.showInSunWindowArray[this.showInSunWindowIndex],
                      })
                        .then(() => {
                          console.info('---1237---    openMenu success');
                        })
                        .catch((err: BusinessError) => {
                          console.info('---1237----    openMenu error: ' + err.code + ' ' + err.message);
                        })

                    } catch (error) {
                      let message = (error as BusinessError).message;
                      let code = (error as BusinessError).code;
                      console.error(`---1237---    openMenu error code is ${code}, message is ${message}`);
                    }
                    ;
                  }
                })

                Column({ space: 5 }) {
                  Text(`updateMenu的功能验证`)
                    .paramTextStyle()
                  Text(`setTimeOut的duration: ${this.duration}`)
                    .paramTextStyle()
                  Row({ space: 3 }) {
                    MyComponent({
                      title: '2000', func: () => {
                        this.duration = 2000
                      }
                    })
                    MyComponent({
                      title: '4000', func: () => {
                        this.duration = 4000
                      }
                    })
                    MyComponent({
                      title: '6000', func: () => {
                        this.duration = 6000
                      }
                    })
                  }

                  Text(`partialUpdate: ${this.partialUpdate}`)
                    .paramTextStyle()
                  Row({ space: 3 }) {
                    MyComponent({
                      title: 'partUpdate: F', func: () => {
                        this.partialUpdate = false
                      }
                    })
                    MyComponent({
                      title: 'partUpdate: T', func: () => {
                        this.partialUpdate = true
                      }
                    })
                  }

                  MyComponent({
                    title: '006、updateMenu_更新为TARGET_WINDOW', func: () => {
                      let uiContext = this.getUIContext();
                      let promptAction = uiContext.getPromptAction();

                      let contentNode = new ComponentContent(uiContext, wrapBuilder(MenuDemo), this.menuAttrOptions);
                      try {
                        promptAction.openMenu(contentNode, this.targetInfo,
                          {
                            placement: Placement.Bottom,
                            modalMode: this.modalModeArray[this.modalModeIndex],
                            showInSubWindow: this.showInSunWindowArray[this.showInSunWindowIndex],
                          })
                          .then(() => {
                            console.info('---1237---    openMenu success');
                          })
                          .catch((err: BusinessError) => {
                            console.info('---1237----    openMenu error: ' + err.code + ' ' + err.message);
                          })

                      } catch (error) {
                        let message = (error as BusinessError).message;
                        let code = (error as BusinessError).code;
                        console.error(`---1237---    openMenu error code is ${code}, message is ${message}`);
                      }
                      ;

                      setTimeout(() => {
                        try {
                          promptAction.updateMenu(contentNode, {
                            placement: Placement.Right,
                            modalMode: ModalMode.TARGET_WINDOW,
                            showInSubWindow: this.showInSunWindowArray[this.showInSunWindowIndex],
                          }, this.partialUpdate)
                            .then(() => {
                              console.info('---1237---    updateMenu success');
                            })
                            .catch((err: BusinessError) => {
                              console.info('---1237----    updateMenu error: ' + err.code + ' ' + err.message);
                            })
                        } catch (error) {
                          let message = (error as BusinessError).message;
                          let code = (error as BusinessError).code;
                          console.error(`---1237---    updateMenu error code is ${code}, message is ${message}`);
                        }
                        ;
                      }, 2000)
                    }
                  })

                  MyComponent({
                    title: '007、updateMenu_更新为非TARGET_WINDOW', func: () => {
                      let uiContext = this.getUIContext();
                      let promptAction = uiContext.getPromptAction();

                      let contentNode = new ComponentContent(uiContext, wrapBuilder(MenuDemo), this.menuAttrOptions);
                      try {
                        promptAction.openMenu(contentNode, this.targetInfo, {
                          modalMode: ModalMode.TARGET_WINDOW,
                          // showInSubWindow: this.showInSunWindowArray[this.showInSunWindowIndex],
                        })
                          .then(() => {
                            console.info('---1237---    openMenu success');
                          })
                          .catch((err: BusinessError) => {
                            console.info('---1237----    openMenu error: ' + err.code + ' ' + err.message);
                          })

                      } catch (error) {
                        let message = (error as BusinessError).message;
                        let code = (error as BusinessError).code;
                        console.error(`---1237---    openMenu error code is ${code}, message is ${message}`);
                      }
                      ;

                      setTimeout(() => {
                        try {
                          promptAction.updateMenu(contentNode, {
                            modalMode: this.modalModeArray[this.modalModeIndex],
                            placement: Placement.Right,
                            showInSubWindow: this.showInSunWindowArray[this.showInSunWindowIndex],
                          })
                            .then(() => {
                              console.info('---1237---    updateMenu success');
                            })
                            .catch((err: BusinessError) => {
                              console.info('---1237----    updateMenu error: ' + err.code + ' ' + err.message);
                            })

                        } catch (error) {
                          let message = (error as BusinessError).message;
                          let code = (error as BusinessError).code;
                          console.error(`---1237---    updateMenu error code is ${code}, message is ${message}`);
                        }
                        ;
                      }, this.duration)
                    }
                  })
                }
                .columnStyle()
              }
              .width('100%')
            }
          }
          .padding(12)
          .scrollBar(BarState.Off)
          .align(Alignment.TopStart)
          .width('100%')
          .height('100%')
        }
        .width('100%')
      }
      .height('100%')
      .width('100%')
    }
    .title('MenuLevel2')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}