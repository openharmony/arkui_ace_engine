/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import router from '@ohos.router'
@CustomDialog
struct CustomDialogExamplepage3 {
  controller?: CustomDialogController
  cancel: () => void = () => {
  }
  confirm: () => void = () => {
  }
  build() {
    Column() {
      Text('TextTextTextTextTextTextText')
        .copyOption(CopyOptions.InApp)
      Search({placeholder: 'Search key'})
        .margin({ top: 10 })

      TextInput({placeholder: 'TextInput key'})
        .margin({ top: 10 })

      TextArea({placeholder: 'TextArea key'})
        .margin({ top: 10 })
      Button('关闭弹窗')
        .onClick(() => {
          if (this.controller != undefined) {
            this.controller.close()
          }
        })
        .margin(20)
    }
  }
}

@Entry
@Component
struct TextInputpage1 {
  controller: TextInputController = new TextInputController()
  controller2: TextAreaController = new TextAreaController()
  @State inputValue: string = ""
  @State inputValue2: string = ""
  @State inputValue3: string = ""
  @State isSupportAvoidance: boolean = true
  @State marginTop: number = 0
  @State cusHeight: number = 300
  @State focusable1: boolean = true
  @State visibility1: Visibility = Visibility.Visible

  createWindow() {
    try {
      window.createWindow({ name: "testWindowPage4", windowType: window.WindowType.TYPE_DIALOG, ctx: getContext(this) })
        .then((windowObj: window.Window) => {
          console.log(`testTag success to createWindow`)
          this.myWindow = windowObj;
          this.myWindow.showWindow().then(() => {
            console.log(`testTag success to showWindow`)
            this.myWindow?.resize(1000, 2200);
            this.myWindow?.moveWindowTo(50, 200);
            let ls = new LocalStorage();
            this.myWindow?.loadContent('pages/32C00/page5', ls)
              .then(() => {
                console.log(`testTag success to loadContent`)
              }).catch((e: base.BusinessError) => {
              console.log(`testTag failed to loadContent: ${JSON.stringify(e)}`)
            })
          }).catch((e: base.BusinessError) => {
            console.log(`testTag failed to showWindow: ${JSON.stringify(e)}`)
          });
        }).catch((e: base.BusinessError) => {
        console.log(`testTag failed to createWindow: ${JSON.stringify(e)}`)
      })
    } catch (e) {
      console.log(`testTag catch exception: ${JSON.stringify(e)}`)
    }
  }

  @Builder
  CustomKeyboardBuilder() {
    Column() {
      Button('close Window')
        .width('100%')
        .onClick(() => {
          this.closeWindow();
        })
      Row() {
        Button('x')
          .width('50%')
          .onClick(() => {
            this.controller.stopEditing()
          })

        Button('focusable:' + this.focusable1)
          .width('50%')
          .onClick(() => {
            this.focusable1 = !this.focusable1
          })
      }.width('100%').margin({ top: 10 })

      Row() {
        Button('height+,' + this.cusHeight)
          .width('50%')
          .onClick(() => {
            this.cusHeight += 10
          })

        Button('height-,' + this.cusHeight)
          .width('50%')
          .onClick(() => {
            this.cusHeight -= 10
          })
      }.width('100%').margin({ top: 10 })

      Grid() {
        ForEach([1, 2, 3, 4, 5, 6, '*', 0, '#'], (item: number | string) => {
          GridItem() {
            Button(item + "")
              .width(110).onClick(() => {
              this.inputValue += item
            })
          }
        })
      }.maxCount(3).columnsGap(10).rowsGap(10).padding(5)
    }.backgroundColor(Color.Gray).height(this.cusHeight)
  }

  onPageShow(): void {
    window.findWindow('testWindowPage4')?.setSubWindowModal(false)
      .then(() => {
        console.info('Succeeded in setting subwindow modal');
      }).catch((err: BusinessError) => {
      console.error('Failed to set subwindow modal. Cause:' + JSON.stringify(err));
    })
  }

  closeWindow() {
    console.log(`testTag prepare to close Window`)
    try {
      this.curWindow = window.findWindow('testWindowPage4');
      if (!this.curWindow) {
        console.log(`testTag failed to findWindow`);
        return;
      }

      this.curWindow.destroyWindow().then(() => {
        console.log(`testTag success to destroy curWindow`);
      }).catch((err: BusinessError) => {
        console.log(`failed to destroy curWindow`)
      })
    } catch (e) {
      console.log(`testTag catch exception when find Window: ${JSON.stringify(e)}`)
    }
  }

  // key组件
  @Builder
  CustomKeyboardBuilder() {
    Column() {
      Grid() {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8, 9, '*', 0, '#'], (item: number | string) => {
          GridItem() {
            Button(item + "")
              .width(110).onClick(() => {
              this.inputValue += item
            })
          }
        })
      }.maxCount(3).columnsGap(10).rowsGap(10).padding(5)
    }.backgroundColor(Color.Gray).height(this.cusHeight)
  }

  @Builder
  CustomKeyboardBuilder2() {
    Column() {
      Grid() {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8, 9, '*', 0, '#'], (item: number | string) => {
          GridItem() {
            Button(item + "")
              .width(110).onClick(() => {
              this.inputValue2 += item
            })
          }
        })
      }.maxCount(3).columnsGap(10).rowsGap(10).padding(5)
    }.backgroundColor(Color.Gray).height(this.cusHeight)
  }

  @Builder
  CustomKeyboardBuilder3() {
    Column() {
      Grid() {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8, 9, '*', 0, '#'], (item: number | string) => {
          GridItem() {
            Button(item + "")
              .width(110).onClick(() => {
              this.inputValue3 += item
            })
          }
        })
      }.maxCount(3).columnsGap(10).rowsGap(10).padding(5)
    }.backgroundColor(Color.Gray).height(this.cusHeight)
  }

  registerCallback() {
    console.log("===trigger pageOne onAppear get pageId: " + this.pageId)
    CustomTransition.getInstance().registerNavParam(this.pageId, (isPush: boolean, isExit: boolean) => {
      console.log("====== trigger current push start value is " + isPush);
      if (isPush) {
        this.x = '100%';
      } else {
        this.x = '0';
      }
      console.log(`===== current start pageOne ${this.pageId}, ${this.x}`);
    }, (isPush: boolean, isExit: boolean) => {
      console.log("====== trigger current push value is " + isPush);
      if (isPush) {
        this.x = '0';
      } else {
        this.x = '100%';
      }
      console.log(`===== current end pageOne ${this.pageId}, ${this.x}`);
    }, (isPush: boolean, isExit: boolean) => {
      this.x = '0';
      console.log("==== trigger pageOne endCallback ====");
    }, (operation: NavigationOperation) => {
      if (operation == NavigationOperation.PUSH) {
        console.log("tongshijia trigger push 100%->0%");
        this.x = '100%';
        animateTo({
          duration: 1000, onFinish: () => {
            this.x = '0';
          }
        }, () => {
          this.x = '0';
        })
      } else if (operation == NavigationOperation.REPLACE) {
        console.log("tongshijia trigger replace pageOne: 0->100%");
        this.x = '100%';
        animateTo({
          duration: 1000, onFinish: () => {
            this.x = "0";
          }
        }, () => {
          this.x = '0';
        })
      } else {
        console.log("tongshijia trigger pop 0 -> 100%")
        this.x = '0';
        animateTo({
          duration: 1000, onFinish: () => {
            this.x = '0';
          }
        }, () => {
          this.x = '100%';
        })
      }
    }, 200);
  }

  build() {
    NavDestination() {

      Column() {
        Column() {
          Button('addCount:' + this.count).onClick((event: ClickEvent) => {
            this.count++
          })
        }

        Column() {
          Text('getAllPathName:' + this.text)
        }.backgroundColor(0xFFFFFF).width('100%').padding({ left: 10, right: 10 }).borderRadius(15)

        Scroll() {
          Column() {
            Text('TextTextTextTextTextTextText')
              .copyOption(CopyOptions.InApp)
            Search({ placeholder: 'Search key' })
              .margin({ top: 10 })

            TextInput({ placeholder: 'TextInput key' })
              .margin({ top: 10 })

            TextArea({ placeholder: 'TextArea key' })
              .margin({ top: 10 })

            Row() {
              Text('从右向左滑操作:').fontSize(10)
              Blank()
              Column({ space: 5 }) {
                Row() {
                  Radio({ value: 'Radio0', group: 'radioGroup1' })
                    .checked(true)
                    .radioStyle({
                      checkedBackgroundColor: Color.Pink
                    })
                    .height(30)
                    .width(30)
                    .onChange((isChecked: boolean) => {
                      this.index = 0
                    })
                  Text('pushPath pageTwo').fontSize(10)
                }

                Row() {
                  Radio({ value: 'Radio8', group: 'radioGroup1' })
                    .checked(false)
                    .radioStyle({
                      checkedBackgroundColor: Color.Pink
                    })
                    .height(30)
                    .width(30)
                    .onChange((isChecked: boolean) => {
                      this.index = 8
                    })
                  Text('pop').fontSize(10)
                }

              }.alignItems(HorizontalAlign.Start)
            }.backgroundColor(0xFFFFFF).width('100%').padding({ left: 10, right: 10 }).borderRadius(15)

          }

        }.height('80%')

      }.width('100%').height('100%')

    }
    .title('pageOne')
    .mode(NavDestinationMode.STANDARD)
    .onBackPressed(() => {
      const popDestinationInfo = this.pageInfos.pop()
      console.log('pop' + '返回值' + JSON.stringify(popDestinationInfo))
      return true
    })
    .onShown(() => {
      this.x = '0'
    })
    .onDisAppear(() => {
      console.log("==== trigger remove pageOne callback " + this.pageId)
      CustomTransition.getInstance().unRegisterNavParam(this.pageId)
    })
    .onReady((context: NavDestinationContext) => {
      this.pageInfos = context.pathStack
      if (context.navDestinationId) {
        this.pageId = context.navDestinationId;
        console.log("==== onReady this pageId: " + this.pageId)
        this.registerCallback()
      }
    })
    .translate({ x: this.x, y: 0, z: 0 })
    .backgroundColor(Color.Red)
    .gesture(PanGesture()
      .onActionStart((event: GestureEvent) => {
        this.rectWidth = event.target.area.width as number;
        if (event.offsetX < 0) {
          console.log("=== push page two ====")
          if (this.index == 0) {
            this.pageInfos.pushPath({ name: 'pageTwo' })
          } else if (this.index == 1) {
            this.pageInfos.pushPathByName('pageTwo', 'a')
          } else if (this.index == 2) {
            this.pageInfos.pushDestination({ name: 'pageTwo' })
          } else if (this.index == 3) {
            this.pageInfos.pushDestinationByName('pageTwo', 'a')
          } else if (this.index == 4) {
            this.pageInfos.replacePath({ name: 'pageTwo' })
          } else if (this.index == 5) {
            this.pageInfos.replacePathByName('pageTwo', 'a')
          } else if (this.index == 6) {
            this.pageInfos.removeByIndexes([0])
          } else if (this.index == 7) {
            this.pageInfos.removeByName('pageTwo')
          } else if (this.index == 8) {
            this.pageInfos.pop()
          } else if (this.index == 9) {
            this.pageInfos.popToName('pageTwo')
          } else if (this.index == 10) {
            this.pageInfos.popToIndex(0)
          } else if (this.index == 11) {
            this.pageInfos.moveToTop('pageTwo')
          } else if (this.index == 12) {
            this.pageInfos.moveIndexToTop(0)
          } else if (this.index == 13) {
            this.pageInfos.clear()
          } else if (this.index == 14) {
            this.text = JSON.stringify(this.pageInfos.getAllPathName())
          } else if (this.index == 15) {
            this.pageInfos.pushPath({ name: 'pageOne' })
            this.pageInfos.pushPath({ name: 'pageTwo' })
            this.pageInfos.pushPath({ name: 'pageThree' })
            this.pageInfos.moveIndexToTop(0)
            this.pageInfos.moveIndexToTop(0)
          } else if (this.index == 16) {
            this.pageInfos.pushPath({ name: 'pageFour' })
          } else if (this.index == 17) {
            this.pageInfos.setInterception({
              willShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar",
                operation: NavigationOperation, animated: boolean) => {
                if (typeof to === "string") {
                  console.log("target page is navigation home");
                  return;
                }
                let target: NavDestinationContext = to as NavDestinationContext;
                if (target.pathInfo.name === 'pageTwo') {
                  target.pathStack.pop();
                  AlertDialog.show(
                    {
                      title: '弹窗',
                      message: 'text',
                      autoCancel: true,
                      alignment: DialogAlignment.Bottom,
                      offset: { dx: 0, dy: -20 },
                      gridCount: 3,
                      confirm: {
                        value: '确认',
                        action: () => {
                          target.pathStack.pushPath({ name: 'pageThree' })
                          console.info('Button-clicking callback')
                        }
                      },
                    }
                  )
                }
                console.log(`will show`)
              },
              didShow: (from: NavDestinationContext | "navBar", to: NavDestinationContext | "navBar",
                operation: NavigationOperation, animated: boolean) => {
                console.log(`did show`)
              }
            });
            this.pageInfos.pushPath({ name: 'pageTwo' })

          }
        } else {
          console.log("==== pop page two");
          this.pageInfos.pop()
        }
      })
      .onActionUpdate((event: GestureEvent) => {
        console.log("===== pan gesture update: ")
        if (event.fingerList.length !== 0) {
          if (event.fingerList[0]) {
            let rate = event.fingerList[0].localX / this.rectWidth;
            console.log("===== pan gesture update: " + rate);
            CustomTransition.getInstance().updateProgress(rate);
          }
        }

      })
      .onActionEnd((event: GestureEvent) => {
        console.log("==== pan gesture onAction end =====")
        if (event.fingerList.length !== 0) {
          if (event.fingerList[0]) {
            let rate: number = event.fingerList[0].localX / this.rectWidth;
            CustomTransition.getInstance().finishInteractiveAnimation(rate)
          }
        }

      })
      .onActionCancel(() => {
        console.log("===== pan gesture on action cancel");
        CustomTransition.getInstance().cancelTransition();
      })
    )
    .onWillAppear(() => {
      console.log("testTag pageOne onWillAppear")
    })
    .onAppear(() => {
      console.log("testTag pageOne onAppear")
    })
    .onWillShow(() => {
      console.log("testTag pageOne onWillShow")
    })
    .onShown(() => {
      console.log("testTag pageOne onShown")
    })
    .onWillHide(() => {
      console.log("testTag pageOne onWillHide")
    })
    .onHidden(() => {
      console.log("testTag pageOne onHidden")
    })
    .onWillDisappear(() => {
      console.log("testTag pageOne onWillDisappear")
    })
    .onDisAppear(() => {
      console.log("testTag pageOne onDisAppear")
    })

    NavDestination() {
      Column() {
        Button('pushPathByName', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            this.pageInfos.pushPath({ name: 'pageOne' })
          })
      }.width('100%').height('100%')
    }
    .title('pageThree')
    .gesture(PanGesture().onActionStart((event: GestureEvent) => {
      this.rectWidth = event.target.area.width as number;
      if (event.offsetX < 0) {
        this.pageInfos.pushPath({ name: 'pageOne' })
      } else {
        this.pageInfos.pop()
      }
    }).onActionUpdate((event: GestureEvent) => {
      let rate = event.fingerList[0].localX / this.rectWidth;
      CustomTransition.getInstance().updateProgress(rate);
    }).onActionEnd((event: GestureEvent) => {
      let rate = event.fingerList[0].localX / this.rectWidth;
      CustomTransition.getInstance().finishInteractiveAnimation2(rate);
    }).onActionCancel(() => {
      console.log("===== trigger animation cancel ====")
      CustomTransition.getInstance().cancelTransition()
    }))
    .onBackPressed(() => {
      const popDestinationInfo = this.pageInfos.pop()
      console.log('pop' + '返回值' + JSON.stringify(popDestinationInfo))
      return true
    })
    .onWillAppear(() => {
      console.log("testTag pageThree onWillAppear")
    })
    .onAppear(() => {
      console.log("testTag pageThree onAppear")
    })
    .onWillShow(() => {
      console.log("testTag pageThree onWillShow")
    })
    .onShown(() => {
      console.log("testTag pageThree onShown")
    })
    .onWillHide(() => {
      console.log("testTag pageThree onWillHide")
    })
    .onHidden(() => {
      console.log("testTag pageThree onHidden")
    })
    .onWillDisappear(() => {
      console.log("testTag pageThree onWillDisappear")
    })
    .onDisAppear(() => {
      console.log("testTag pageThree onDisAppear")
      CustomTransition.getInstance().unRegisterNavParam(this.pageId)
    })
    .onReady((context: NavDestinationContext) => {
      this.pageInfos = context.pathStack;
      if (context.navDestinationId) {
        this.pageId = context.navDestinationId;
        console.log("context navDestination id is " + this.pageId);
        this.registerCallback(context.navDestinationId)
      }
    })
    .translate({ x: this.x })
    .backgroundColor(Color.Yellow)

    NavDestination() {
      Column() {


        Text('TextTextTextTextTextTextText')
          .copyOption(CopyOptions.InApp)
        Search({ placeholder: 'Search key' })
          .margin({ top: 10 })

        TextInput({ placeholder: 'TextInput key' })
          .margin({ top: 10 })

        TextArea({ placeholder: 'TextArea key' })
          .margin({ top: 10 })


      }.width('100%').height('100%')
    }
    .title('pageTwo')
    .gesture(PanGesture()
      .onActionStart((event: GestureEvent) => {
        this.rectWidth = event.target.area.width as number;
        if (event.offsetX < 0) {
          this.pageInfos.pushPath({ name: "pageOne" })
        } else {
          console.log("==== pop page two");
          this.pageInfos.pop()
        }
      })
      .onActionUpdate((event: GestureEvent) => {
        console.log("===== pan gesture update: ")
        if (event.fingerList.length !== 0) {
          if (event.fingerList[0]) {
            let rate = event.fingerList[0].localX / this.rectWidth;
            console.log("===== pan gesture update: " + rate);
            CustomTransition.getInstance().updateProgress(rate);
          }
        }
      })
      .onActionEnd((event: GestureEvent) => {
        console.log("==== pan gesture onAction end =====")
        if (event.fingerList.length !== 0) {
          if (event.fingerList[0]) {
            let rate: number = event.fingerList[0].localX / this.rectWidth;
            CustomTransition.getInstance().finishInteractiveAnimation(rate)
          }
        }

      })
      .onActionCancel(() => {
        console.log("===== pan gesture on action cancel");
        CustomTransition.getInstance().cancelTransition();
      })
    )
    .onBackPressed(() => {
      const popDestinationInfo = this.pageInfos.pop()
      console.log('pop' + '返回值' + JSON.stringify(popDestinationInfo))
      return true
    })
    .onWillAppear(() => {
      console.log("testTag pageTwo onWillAppear")
    })
    .onAppear(() => {
      console.log("testTag pageTwo onAppear")
    })
    .onWillShow(() => {
      console.log("testTag pageTwo onWillShow")
    })
    .onShown(() => {
      console.log("testTag pageTwo onShown")
    })
    .onWillHide(() => {
      console.log("testTag pageTwo onWillHide")
    })
    .onHidden(() => {
      console.log("testTag pageTwo onHidden")
    })
    .onWillDisappear(() => {
      console.log("testTag pageTwo onWillDisappear")
    })
    .onDisAppear(() => {
      console.log("testTag pageTwo onDisAppear")
      CustomTransition.getInstance().unRegisterNavParam(this.pageId)
    })
    .onReady((context: NavDestinationContext) => {
      this.pageInfos = context.pathStack;
      if (context.navDestinationId) {
        this.pageId = context.navDestinationId;
        console.log("context navDestination id is " + this.pageId);
        this.registerCallback(context.navDestinationId)
      }
    })
    .translate({ x: this.x })
    .backgroundColor(Color.Yellow)

    NavDestination() {

      Column() {
        Column() {
          Button('addCount:' + this.count).onClick((event: ClickEvent) => {
            this.count++
          })
        }

        Column() {
          Text('getAllPathName:' + this.text)
        }.backgroundColor(0xFFFFFF).width('100%').padding({ left: 10, right: 10 }).borderRadius(15)

        Scroll() {
          Column() {

            Row() {
              Text('从右向左滑操作:').fontSize(10)
              Blank()
              Column({ space: 5 }) {
                Row() {
                  Radio({ value: 'Radio0', group: 'radioGroup1' })
                    .checked(true)
                    .radioStyle({
                      checkedBackgroundColor: Color.Pink
                    })
                    .height(30)
                    .width(30)
                    .onChange((isChecked: boolean) => {
                      this.index = 0
                    })
                  Text('pushPath').fontSize(10)
                }

                Row() {
                  Radio({ value: 'Radio1', group: 'radioGroup1' })
                    .checked(false)
                    .radioStyle({
                      checkedBackgroundColor: Color.Pink
                    })
                    .height(30)
                    .width(30)
                    .onChange((isChecked: boolean) => {
                      this.index = 1
                    })
                  Text('pushPathByName').fontSize(10)
                }

                Row() {
                  Radio({ value: 'Radio2', group: 'radioGroup1' })
                    .checked(false)
                    .radioStyle({
                      checkedBackgroundColor: Color.Pink
                    })
                    .height(30)
                    .width(30)
                    .onChange((isChecked: boolean) => {
                      this.index = 2
                    })
                  Text('pushDestination').fontSize(10)
                }

                Row() {
                  Radio({ value: 'Radio3', group: 'radioGroup1' })
                    .checked(false)
                    .radioStyle({
                      checkedBackgroundColor: Color.Pink
                    })
                    .height(30)
                    .width(30)
                    .onChange((isChecked: boolean) => {
                      this.index = 3
                    })
                  Text('pushDestinationByName').fontSize(10)
                }

                Row() {
                  Radio({ value: 'Radio4', group: 'radioGroup1' })
                    .checked(false)
                    .radioStyle({
                      checkedBackgroundColor: Color.Pink
                    })
                    .height(30)
                    .width(30)
                    .onChange((isChecked: boolean) => {
                      this.index = 4
                    })
                  Text('replacePath').fontSize(10)
                }

                Row() {
                  Radio({ value: 'Radio5', group: 'radioGroup1' })
                    .checked(false)
                    .radioStyle({
                      checkedBackgroundColor: Color.Pink
                    })
                    .height(30)
                    .width(30)
                    .onChange((isChecked: boolean) => {
                      this.index = 5
                    })
                  Text('replacePathByName').fontSize(10)
                }

                Row() {
                  Radio({ value: 'Radio6', group: 'radioGroup1' })
                    .checked(false)
                    .radioStyle({
                      checkedBackgroundColor: Color.Pink
                    })
                    .height(30)
                    .width(30)
                    .onChange((isChecked: boolean) => {
                      this.index = 6
                    })
                  Text('removeByIndexes[0]').fontSize(10)
                }

                Row() {
                  Radio({ value: 'Radio7', group: 'radioGroup1' })
                    .checked(false)
                    .radioStyle({
                      checkedBackgroundColor: Color.Pink
                    })
                    .height(30)
                    .width(30)
                    .onChange((isChecked: boolean) => {
                      this.index = 7
                    })
                  Text('removeByName pageOne').fontSize(10)
                }

                Row() {
                  Radio({ value: 'Radio8', group: 'radioGroup1' })
                    .checked(false)
                    .radioStyle({
                      checkedBackgroundColor: Color.Pink
                    })
                    .height(30)
                    .width(30)
                    .onChange((isChecked: boolean) => {
                      this.index = 8
                    })
                  Text('pop').fontSize(10)
                }

                Row() {
                  Radio({ value: 'Radio9', group: 'radioGroup1' })
                    .checked(false)
                    .radioStyle({
                      checkedBackgroundColor: Color.Pink
                    })
                    .height(30)
                    .width(30)
                    .onChange((isChecked: boolean) => {
                      this.index = 9
                    })
                  Text('popToName pageTwo').fontSize(10)
                }

                Row() {
                  Radio({ value: 'Radio10', group: 'radioGroup1' })
                    .checked(false)
                    .radioStyle({
                      checkedBackgroundColor: Color.Pink
                    })
                    .height(30)
                    .width(30)
                    .onChange((isChecked: boolean) => {
                      this.index = 10
                    })
                  Text('popToIndex(0)').fontSize(10)
                }

                Row() {
                  Radio({ value: 'Radio11', group: 'radioGroup1' })
                    .checked(false)
                    .radioStyle({
                      checkedBackgroundColor: Color.Pink
                    })
                    .height(30)
                    .width(30)
                    .onChange((isChecked: boolean) => {
                      this.index = 11
                    })
                  Text('moveToTop pageTwo').fontSize(10)
                }

                Row() {
                  Radio({ value: 'Radio12', group: 'radioGroup1' })
                    .checked(false)
                    .radioStyle({
                      checkedBackgroundColor: Color.Pink
                    })
                    .height(30)
                    .width(30)
                    .onChange((isChecked: boolean) => {
                      this.index = 12
                    })
                  Text('moveIndexToTop 0').fontSize(10)
                }

                Row() {
                  Radio({ value: 'Radio13', group: 'radioGroup1' })
                    .checked(false)
                    .radioStyle({
                      checkedBackgroundColor: Color.Pink
                    })
                    .height(30)
                    .width(30)
                    .onChange((isChecked: boolean) => {
                      this.index = 13
                    })
                  Text('clear').fontSize(10)
                }

                Row() {
                  Radio({ value: 'Radio14', group: 'radioGroup1' })
                    .checked(false)
                    .radioStyle({
                      checkedBackgroundColor: Color.Pink
                    })
                    .height(30)
                    .width(30)
                    .onChange((isChecked: boolean) => {
                      this.index = 14
                    })
                  Text('getAllPathName').fontSize(10)
                }

                Row() {
                  Radio({ value: 'Radio15', group: 'radioGroup1' })
                    .checked(false)
                    .radioStyle({
                      checkedBackgroundColor: Color.Pink
                    })
                    .height(30)
                    .width(30)
                    .onChange((isChecked: boolean) => {
                      this.index = 15
                    })
                  Text('三次push pageTwo，两次moveIndexToTop 0').fontSize(10)
                }

              }.alignItems(HorizontalAlign.Start)
            }.backgroundColor(0xFFFFFF).width('100%').padding({ left: 10, right: 10 }).borderRadius(15)

          }

        }.height('80%')

      }.width('100%').height('100%')

    }
    .title('pageFour')
    .mode(NavDestinationMode.DIALOG)
    .onBackPressed(() => {
      const popDestinationInfo = this.pageInfos.pop()
      console.log('pop' + '返回值' + JSON.stringify(popDestinationInfo))
      return true
    })
    .onShown(() => {
      this.x = '0'
    })
    .onDisAppear(() => {
      console.log("==== trigger remove pageOne callback " + this.pageId)
      CustomTransition.getInstance().unRegisterNavParam(this.pageId)
    })
    .onReady((context: NavDestinationContext) => {
      this.pageInfos = context.pathStack
      if (context.navDestinationId) {
        this.pageId = context.navDestinationId;
        console.log("==== onReady this pageId: " + this.pageId)
        this.registerCallback()
      }
    })
    .translate({ x: this.x, y: 0, z: 0 })
    .border({ width: 1 })
    .gesture(PanGesture()
      .onActionStart((event: GestureEvent) => {
        this.rectWidth = event.target.area.width as number;
        if (event.offsetX < 0) {
          console.log("=== push page two ====")
          if (this.index == 0) {
            this.pageInfos.pushPath({ name: 'pageTwo' })
          } else if (this.index == 1) {
            this.pageInfos.pushPathByName('pageTwo', 'a')
          } else if (this.index == 2) {
            this.pageInfos.pushDestination({ name: 'pageTwo' })
          } else if (this.index == 3) {
            this.pageInfos.pushDestinationByName('pageTwo', 'a')
          } else if (this.index == 4) {
            this.pageInfos.replacePath({ name: 'pageTwo' })
          } else if (this.index == 5) {
            this.pageInfos.replacePathByName('pageTwo', 'a')
          } else if (this.index == 6) {
            this.pageInfos.removeByIndexes([0])
          } else if (this.index == 7) {
            this.pageInfos.removeByName('pageOne')
          } else if (this.index == 8) {
            this.pageInfos.pop()
          } else if (this.index == 9) {
            this.pageInfos.popToName('pageTwo')
          } else if (this.index == 10) {
            this.pageInfos.popToIndex(0)
          } else if (this.index == 11) {
            this.pageInfos.moveToTop('pageTwo')
          } else if (this.index == 12) {
            this.pageInfos.moveIndexToTop(0)
          } else if (this.index == 13) {
            this.pageInfos.clear()
          } else if (this.index == 14) {
            this.text = JSON.stringify(this.pageInfos.getAllPathName())
          } else if (this.index == 15) {
            this.pageInfos.pushPath({ name: 'pageOne' })
            this.pageInfos.pushPath({ name: 'pageTwo' })
            this.pageInfos.pushPath({ name: 'pageThree' })
            this.pageInfos.moveIndexToTop(0)
            this.pageInfos.moveIndexToTop(0)
          }
        } else {
          console.log("==== pop page two");
          this.pageInfos.pop()
        }
      })
      .onActionUpdate((event: GestureEvent) => {
        console.log("===== pan gesture update: ")
        let rate = event.fingerList[0].localX / this.rectWidth;
        console.log("===== pan gesture update: " + rate);
        CustomTransition.getInstance().updateProgress(rate);
      })
      .onActionEnd((event: GestureEvent) => {
        console.log("==== pan gesture onAction end =====")
        let rate: number = event.fingerList[0].localX / this.rectWidth;
        CustomTransition.getInstance().finishInteractiveAnimation(rate)
      })
      .onActionCancel(() => {
        console.log("===== pan gesture on action cancel");
        CustomTransition.getInstance().cancelTransition();
      })
    )
    .onWillAppear(() => {
      console.log("testTag pageFour onWillAppear")
    })
    .onAppear(() => {
      console.log("testTag pageFour onAppear")
    })
    .onWillShow(() => {
      console.log("testTag pageFour onWillShow")
    })
    .onShown(() => {
      console.log("testTag pageFour onShown")
    })
    .onWillHide(() => {
      console.log("testTag pageFour onWillHide")
    })
    .onHidden(() => {
      console.log("testTag pageFour onHidden")
    })
    .onWillDisappear(() => {
      console.log("testTag pageFour onWillDisappear")
    })
    .onDisAppear(() => {
      console.log("testTag pageFour onDisAppear")
    })

    Scroll() {
      Column() {
        Button("transition modal 1")
          .onClick(() => {
            this.isShow = true
          })
          .fontSize(20)
          .margin(10)
          .bindSheet($$this.isShow, this.myBuilder(), {
            height: this.sheetHeight,
            backgroundColor: Color.Green,
            onWillAppear: () => {
              console.log("BindSheet onWillAppear.")
            },
            onAppear: () => {
              console.log("BindSheet onAppear.")
            },
            onWillDisappear: () => {
              console.log("BindSheet onWillDisappear.")
            },
            onDisappear: () => {
              console.log("BindSheet onDisappear.")
            }
          })
      }
      .justifyContent(FlexAlign.Center)
      .width('100%')
      .height('100%')

      Column() {
        Row() {
          Button('marginTop+' + this.marginTop).onClick((event: ClickEvent) => {
            this.marginTop += 20
          })
          Button('marginTop-' + this.marginTop).onClick((event: ClickEvent) => {
            this.marginTop -= 20
          })
          Button('显示').onClick((event: ClickEvent) => {
            this.visibility1 = Visibility.Visible
          })
          Button('隐藏').onClick((event: ClickEvent) => {
            this.visibility1 = Visibility.None
          })

        }

        Text('TextTextTextTextTextTextText').height(this.marginTop)
          .copyOption(CopyOptions.InApp)

        Search({ value: this.inputValue3, placeholder: 'Search key' })
          .customKeyboard(this.CustomKeyboardBuilder3(), { supportAvoidance: this.isSupportAvoidance })
          .margin({ top: 10 })
          .visibility(this.visibility1)
          .onChange((value) => {
            this.inputValue3 = value
          })
          .border({ width: 1 })

        TextArea({ controller: this.controller2, placeholder: 'TextArea key', text: this.inputValue2 })
          .margin({ top: 10 })
          .customKeyboard(this.CustomKeyboardBuilder2(), { supportAvoidance: this.isSupportAvoidance })
          .visibility(this.visibility1)
          .onChange((value) => {
            this.inputValue2 = value
          })
          .border({ width: 1 })

        TextInput({ controller: this.controller, text: this.inputValue, placeholder: 'TextInput key' })
          .margin({ top: 10 })
          .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: this.isSupportAvoidance })
          .visibility(this.visibility1)
          .onChange((value) => {
            this.inputValue = value
          })
          .border({ width: 1 })

        Search({ placeholder: 'Search key' })
          .margin({ top: 10 })
          .visibility(this.visibility1)

        TextInput({ placeholder: 'TextInput key' })
          .margin({ top: 10 })
          .visibility(this.visibility1)

        TextArea({ placeholder: 'TextArea key' })
          .margin({ top: 10 })
          .visibility(this.visibility1)

      }.height('100%')
    }.height('100%')

  }
}