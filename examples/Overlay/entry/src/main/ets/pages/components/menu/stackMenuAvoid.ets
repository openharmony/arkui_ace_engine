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

@Builder
export function stackMenuAvoidBuilder(name: string, param: Object) {
  stackMenuAvoidExample()
}

@Extend(Column)
function columnStyle() {
  .borderWidth(1.0)
  .padding(5)
  .width('100%')
  .backgroundColor(Color.Pink)
}

@CustomDialog
struct CustomDialogExampleTwo {
  controllerTwo?: CustomDialogController;

  build() {
    Column() {
      Text('我是第二个弹窗')
        .fontSize(30)
        .height(100)
      Button('点我关闭第二个弹窗')
        .onClick(() => {
          if (this.controllerTwo != undefined) {
            this.controllerTwo.close();
          }
        })
        .margin(20)
    }
  }
}

class Params {
  public text: string = '';

  constructor(text: string) {
    this.text = text;
  }
}

@Builder
function buildText(params: Params) {
  Column() {
    Text(params.text)
      .fontSize(50)
      .fontWeight(FontWeight.Bold)
      .margin({ bottom: 36 })
  }.backgroundColor('#FFF0F0F0')
}

@CustomDialog
@Component
struct CustomDialogExample {
  @Builder
  FirstMenu_Short() {
    Menu() {
      MenuItem({
        content: '菜单选项A',
        builder: this.SubMenu_Short
      })
      MenuItem({
        content: '菜单选项A',
        builder: this.SubMenu_Short
      })
      MenuItem({
        content: '菜单选项A',
        builder: this.SubMenu_Short
      })
      MenuItemGroup() {
        MenuItem({
          content: '菜单选项B',
          builder: this.SubMenu_Short
        })
        MenuItem({
          content: '菜单选项C',
          builder: this.SubMenu_Short
        })
        MenuItem({
          content: '菜单选项C',
          builder: this.SubMenu_Short
        })
        MenuItem({
          content: '菜单选项C',
          builder: this.SubMenu_Short
        })
        MenuItem({
          content: '菜单选项C',
          builder: this.SubMenu_Short
        })
        MenuItem({
          content: '菜单选项C',
          builder: this.SubMenu_Short
        })
        MenuItem({
          content: '菜单选项C',
          builder: this.SubMenu_Short
        })
        MenuItem({
          content: '菜单选项C',
          builder: this.SubMenu_Short
        })
      }
    }
    .subMenuExpandingMode(SubMenuExpandingMode.STACK_EXPAND)
  }

  @Builder
  SubMenu_Short() {
    Menu() {
      MenuItem({ content: '复制1', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '复制2', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '复制2', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '复制2', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '复制2', labelInfo: 'Ctrl+C' })

    }
  }

  @Link textValue: string;
  @Link inputValue: string;
  @State placement: Placement = Placement.BottomLeft;
  dialogControllerTwo: CustomDialogController | null = new CustomDialogController({
    builder: CustomDialogExampleTwo(),
    alignment: DialogAlignment.Bottom,
    onWillDismiss: (dismissDialogAction: DismissDialogAction) => {
      console.info('reason=' + JSON.stringify(dismissDialogAction.reason));
      console.log('dialog onWillDismiss');
      if (dismissDialogAction.reason == DismissReason.PRESS_BACK) {
        dismissDialogAction.dismiss();
      }
      if (dismissDialogAction.reason == DismissReason.TOUCH_OUTSIDE) {
        dismissDialogAction.dismiss();
      }
    },
    offset: { dx: 0, dy: -25 }
  })
  controller?: CustomDialogController;
  // 若尝试在CustomDialog中传入多个其他的Controller，以实现在CustomDialog中打开另一个或另一些CustomDialog，那么此处需要将指向自己的controller放在所有controller的后面
  cancel: () => void = () => {
  }
  confirm: () => void = () => {
  }

  build() {
    Scroll() {
      Column() {
        Text('Change text').fontSize(20).margin({ top: 10, bottom: 10 })
        TextInput({ placeholder: '', text: this.textValue }).height(60).width('90%')
          .onChange((value: string) => {
            this.textValue = value;
          })
        Text('Whether to change a text?').fontSize(16).margin({ bottom: 10 })
        Button('menu')
          .bindMenu([
            {
              value: 'Menu1',
              action: () => {
                console.info('handle Menu1 select');
              }
            },
            {
              value: 'Menu2',
              action: () => {
                console.info('handle Menu1 select');
              }
            }, {
            value: 'Menu3',
            action: () => {
              console.info('handle Menu1 select');
            }
          },
            {
              value: 'Menu2',
              action: () => {
                console.info('handle Menu2 select');
              }
            },
          ])
        Button('menu1')
          .bindMenu(this.FirstMenu_Short(), {
            placement: this.placement,
            // showInSubWindow: this.showInSubWindow
          })
        Flex({ justifyContent: FlexAlign.SpaceAround }) {
          Button('cancel')
            .onClick(() => {
              if (this.controller != undefined) {
                this.controller.close();
                this.cancel();
              }
            }).backgroundColor(0xffffff).fontColor(Color.Black)
          Button('confirm')
            .onClick(() => {
              if (this.controller != undefined) {
                this.inputValue = this.textValue;
                this.controller.close();
                this.confirm();
              }
            }).backgroundColor(0xffffff).fontColor(Color.Red)
        }.margin({ bottom: 10 })

        Button('点我打开第二个弹窗')
          .onClick(() => {
            if (this.dialogControllerTwo != null) {
              this.dialogControllerTwo.open();
            }
          })
          .margin(20)
      }.borderRadius(10)

      // 如果需要使用border属性或cornerRadius属性，请和borderRadius属性一起使用。
    }
  }
}

@Entry
@Component
struct stackMenuAvoidExample {
  pathStack: NavPathStack = new NavPathStack()
  @State message: string = 'hello';
  @State placement: Placement = Placement.BottomLeft;
  @State showInSubWindow: boolean = true;
  @State textValue: string = ''
  @State inputValue: string = 'click me'
  dialogController: CustomDialogController | null = new CustomDialogController({
    builder: CustomDialogExample({
      cancel: () => {
        this.onCancel();
      },
      confirm: () => {
        this.onAccept();
      },
      textValue: this.textValue,
      inputValue: this.inputValue
    }),
    cancel: this.exitApp,
    autoCancel: true,
    onWillDismiss: (dismissDialogAction: DismissDialogAction) => {
      console.info('reason=' + JSON.stringify(dismissDialogAction.reason));
      console.log('dialog onWillDismiss');
      if (dismissDialogAction.reason == DismissReason.PRESS_BACK) {
        dismissDialogAction.dismiss();
      }
      if (dismissDialogAction.reason == DismissReason.TOUCH_OUTSIDE) {
        dismissDialogAction.dismiss();
      }
    },
    alignment: DialogAlignment.Bottom,
    offset: { dx: 0, dy: -20 },
    gridCount: 4,
    customStyle: false,
    cornerRadius: 10,
  })

  aboutToDisappear() {
    this.dialogController = null; // 将dialogController置空
  }

  onCancel() {
    console.info('Callback when the first button is clicked');
  }

  onAccept() {
    console.info('Callback when the second button is clicked');
  }

  exitApp() {
    console.info('Click the callback in the blank area');
  }

  build() {
    NavDestination() {
      Scroll() {
        Column() {
          Row() {

            Text('showInSubWindow: ')
            Select([{ value: 'true' }, { value: 'false' }])
              .onSelect((index: number, text?: string | undefined) => {
                switch (text) {
                  case 'false':
                    this.showInSubWindow = false;
                    break
                  case 'true':
                    this.showInSubWindow = true;
                    break
                }
              })
            Blank()
          }

          Row() {
            Text('一级菜单placement: ')
            Select([{ value: 'BottomLeft' }, { value: 'Bottom' }, { value: 'BottomRight' },
              { value: 'Left' }, { value: 'LeftTop' }, { value: 'LeftBottom' },
              { value: 'Right' }, { value: 'RightTop' }, { value: 'RightBottom' },
              { value: 'Top' }, { value: 'TopLeft' }, { value: 'TopRight' }])
              .onSelect((index: number, text?: string | undefined) => {
                switch (text) {
                  case 'BottomLeft':
                    this.placement = Placement.BottomLeft;
                    break
                  case 'Bottom':
                    this.placement = Placement.Bottom;
                    break
                  case 'BottomRight':
                    this.placement = Placement.BottomRight;
                    break
                  case 'Left':
                    this.placement = Placement.Left;
                    break
                  case 'LeftTop':
                    this.placement = Placement.LeftTop;
                    break
                  case 'LeftBottom':
                    this.placement = Placement.LeftBottom;
                    break
                  case 'Right':
                    this.placement = Placement.Right;
                    break
                  case 'RightTop':
                    this.placement = Placement.RightTop;
                    break
                  case 'RightBottom':
                    this.placement = Placement.RightBottom;
                    break
                  case 'Top':
                    this.placement = Placement.Top;
                    break
                  case 'TopLeft':
                    this.placement = Placement.TopLeft;
                    break
                  case 'TopRight':
                    this.placement = Placement.TopRight;
                    break
                }
              })

          }

          Row() {
            Column() {
              Button(this.inputValue)
                .onClick(() => {
                  if (this.dialogController != null) {
                    this.dialogController.open();
                  }
                }).backgroundColor(0x317aff)
            }.width('100%').margin({ top: 5 })
          }

          Row() {
            Button('无预览-短菜单')
              .bindMenu(this.FirstMenu_Short(), {
                placement: this.placement,
                showInSubWindow: this.showInSubWindow
              })
          }
          .width('100%')
          .justifyContent(FlexAlign.Center)

          Row() {
            Button('无预览-短菜单（right）')
              .bindMenu(this.FirstMenu_Short(), {
                placement: this.placement,
                showInSubWindow: this.showInSubWindow
              })
          }
          .width('100%')
          .justifyContent(FlexAlign.Start)

          Row() {
            Button('无预览-短菜单(left)')
              .bindMenu(this.FirstMenu_Medium(), {
                placement: this.placement,
                showInSubWindow: this.showInSubWindow
              })
          }
          .width('100%')
          .justifyContent(FlexAlign.End)

          Row() {
            Button('无预览-中菜单')
              .bindMenu(this.FirstMenu_Medium(), {
                placement: this.placement,
                showInSubWindow: this.showInSubWindow
              })
          }
          .width('100%')
          .justifyContent(FlexAlign.Center)

          Row() {
            Button('无预览-中菜单(left)')
              .bindMenu(this.FirstMenu_Medium(), {
                placement: this.placement,
                showInSubWindow: this.showInSubWindow
              })
          }
          .width('100%')
          .justifyContent(FlexAlign.End)

          Row() {
            Button('无预览-中菜单（right）')
              .bindMenu(this.FirstMenu_Short(), {
                placement: this.placement,
                showInSubWindow: this.showInSubWindow
              })
          }
          .width('100%')
          .justifyContent(FlexAlign.Start)

          Row() {
            Button('无预览-长菜单')
              .bindMenu(this.FirstMenu_Long(), {
                placement: this.placement,
                showInSubWindow: this.showInSubWindow
              })
          }.justifyContent(FlexAlign.Center)
          .width('100%')

          Row() {
            Button('无预览-长菜单(left)')
              .bindMenu(this.FirstMenu_Long(), {
                placement: this.placement,
                showInSubWindow: this.showInSubWindow
              })
          }
          .justifyContent(FlexAlign.End)
          .width('100%')

          Row() {
            Button('无预览-长菜单(reight)')
              .bindMenu(this.FirstMenu_Long(), {
                placement: this.placement,
                showInSubWindow: this.showInSubWindow
              })
          }
          .justifyContent(FlexAlign.Start)
          .width('100%')

          Row() {
            Button('有预览-短菜单').bindContextMenu(this.FirstMenu_Short(), ResponseType.LongPress, {
              placement: this.placement,
              preview: MenuPreviewMode.IMAGE
            })
          }.justifyContent(FlexAlign.Center)
          .width('100%')

          Row() {
            Button('有预览-短菜单left').bindContextMenu(this.FirstMenu_Short(), ResponseType.LongPress, {
              placement: this.placement,
              preview: MenuPreviewMode.IMAGE
            })
          }.justifyContent(FlexAlign.Start)
          .width('100%')

          Row() {
            Button('有预览-短菜单right').bindContextMenu(this.FirstMenu_Short(), ResponseType.LongPress, {
              placement: this.placement,
              preview: MenuPreviewMode.IMAGE
            })
          }.justifyContent(FlexAlign.End)
          .width('100%')

          Row() {
            Button('有预览-中菜单').bindContextMenu(this.FirstMenu_Medium(), ResponseType.LongPress, {
              placement: this.placement,
              preview: MenuPreviewMode.IMAGE
            })
          }
          .justifyContent(FlexAlign.Center)
          .width('100%')

          Row() {
            Button('有预览-中菜单left').bindContextMenu(this.FirstMenu_Medium(), ResponseType.LongPress, {
              placement: this.placement,
              preview: MenuPreviewMode.IMAGE
            })
          }.justifyContent(FlexAlign.Start)
          .width('100%')

          Row() {
            Button('有预览-中菜单right').bindContextMenu(this.FirstMenu_Medium(), ResponseType.LongPress, {
              placement: this.placement,
              preview: MenuPreviewMode.IMAGE
            })
          }.justifyContent(FlexAlign.End)
          .width('100%')

          Row() {

            Button('有预览-长菜单').bindContextMenu(this.FirstMenu_Long(), ResponseType.LongPress, {
              placement: this.placement,
              preview: MenuPreviewMode.IMAGE
            })
          }
          .justifyContent(FlexAlign.Center)
          .width('100%')

          Row() {

            Button('有预览-长菜单-left').bindContextMenu(this.FirstMenu_Long(), ResponseType.LongPress, {
              placement: this.placement,
              preview: MenuPreviewMode.IMAGE
            })
          }
          .justifyContent(FlexAlign.Start)
          .width('100%')

          Row() {

            Button('有预览-长菜单-button').bindContextMenu(this.FirstMenu_Long(), ResponseType.LongPress, {
              placement: this.placement,
              preview: MenuPreviewMode.IMAGE
            })
          }
          .justifyContent(FlexAlign.End)
          .width('100%')

          Row() {
            Text('______________')
          }

          Row() {
            Text('______________')
          }

          Row() {
            Text('______________')
          }

          Row() {
            Text('______________').width('10')
          }

          Row() {
            Text('______________').width('10')
          }

          Row() {
            Text('______________').width('10')
          }

          Row() {
            Text('______________').width('10')
          }
        }
        .justifyContent(FlexAlign.Center)
        .alignItems(HorizontalAlign.Start)
        .width('100%')
      }
      .height('100%')
      .border({ width: 1, color: Color.Red })
    }
    .title('stackMenuAvoid')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }

  @Builder
  FirstMenu_Short() {
    Menu() {
      MenuItem({
        content: '菜单选项A',
        builder: this.SubMenu_Short
      })
      MenuItemGroup() {
        MenuItem({
          content: '菜单选项B',
          builder: this.SubMenu_Short
        })
      }
    }
    .subMenuExpandingMode(SubMenuExpandingMode.STACK_EXPAND)
  }

  @Builder
  FirstMenu_Medium() {
    Menu() {
      MenuItem({
        content: '菜单选项A',
        builder: this.SubMenu_Medium
      })
      MenuItemGroup() {
        MenuItem({
          content: '菜单选项B',
          builder: this.SubMenu_Medium
        })
        MenuItem({
          content: '菜单选项C',
          builder: this.SubMenu_Medium
        })
      }
    }
    .subMenuExpandingMode(SubMenuExpandingMode.STACK_EXPAND)
  }

  @Builder
  FirstMenu_Long() {
    Menu() {
      MenuItem({
        content: '菜单选项A',
        builder: this.SubMenu_Long
      })
      MenuItemGroup() {
        MenuItem({
          content: '菜单选项B',
          builder: this.SubMenu_Long
        })
        MenuItem({
          content: '菜单选项C',
          builder: this.SubMenu_Long
        })
      }

      MenuItem({
        content: '菜单选项D',
        builder: this.SubMenu_Long
      })
      MenuItem({
        content: '菜单选项E',
        builder: this.SubMenu_Long
      })
    }
    .subMenuExpandingMode(SubMenuExpandingMode.STACK_EXPAND)
  }

  @Builder
  SubMenu_Short() {
    Menu() {
      MenuItem({ content: '复制1', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '复制2', labelInfo: 'Ctrl+C' })
    }
  }

  @Builder
  SubMenu_Medium() {
    Menu() {
      MenuItem({ content: '复制1', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '复制2', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '复制3', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '复制4', labelInfo: 'Ctrl+C' })
    }
  }

  @Builder
  SubMenu_Long() {
    Menu() {
      MenuItem({ content: '复制1', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '复制2', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '复制3', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '复制4', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '复制5', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '复制6', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '复制7', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '复制8', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '复制9', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '复制10', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '复制11', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '复制12', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '复制13', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '复制15', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '复制16', labelInfo: 'Ctrl+C' })
    }
  }
}