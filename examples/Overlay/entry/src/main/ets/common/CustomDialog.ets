/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

@CustomDialog
export struct Scroll_CustomDialog {
  //控制本自定义弹窗的controller放在其他自定义弹窗的controller的最后
  controller?: CustomDialogController
  cancel: () => void = () => {
  }
  confirm: () => void = () => {
  }
  @State message: string = 'Hello World'
  @State arr: number[] = []

  @Styles
  listCard() {
    .backgroundColor(Color.White)
    .height(72)
    .width('100%')
    .borderRadius(12)
  }

  build() {
    Scroll() {
      Column({ space: 10 }) {

        Text('Scroll Area')
          .width('100%')
          .height('10%')
          .backgroundColor('#0080DC')
          .textAlign(TextAlign.Center)

        Tabs({ barPosition: BarPosition.Start }) {
          TabContent() {
            List({ space: 10 }) {
              ForEach(this.arr, (item: number) => {
                ListItem() {
                  Text('item' + item)
                    .fontSize(16)
                }.listCard()
              }, (item: string) => item)
            }.width('100%')
            .edgeEffect(EdgeEffect.Spring)
            .nestedScroll({
              scrollForward: NestedScrollMode.PARENT_FIRST,
              scrollBackward: NestedScrollMode.SELF_FIRST
            })
          }.tabBar('Tab1')

          TabContent() {
          }.tabBar('Tab2')
        }
        .vertical(false)
        .height('100%')

        Divider()
        Flex({ justifyContent: FlexAlign.SpaceAround }) {
          Button('cancel')
            .onClick(() => {
              if (this.controller != undefined) {
                this.controller.close()
                this.cancel()
              }
            }).backgroundColor(0xffffff).fontColor(Color.Black)

          Button('confirm')
            .onClick(() => {
              if (this.controller != undefined) {
                this.controller.close()
                this.confirm()
              }
            }).backgroundColor(0xffffff).fontColor(Color.Red)
        }.margin({ bottom: 10 })
      }.width('100%')
    }
    .edgeEffect(EdgeEffect.Spring)
    .friction(0.6)
    .backgroundColor('#DCDCDC')
    .scrollBar(BarState.Off)
    .width('100%')
    .height('100%')
    .borderRadius(10)
    .key('scroll_in_customDialog')
  }

  aboutToAppear() {
    for (let i = 0; i < 8; i++) {
      this.arr.push(i)
    }
  }
}

//自定义弹窗:builder打开其他弹窗类组件
@CustomDialog
export struct MainCustomDialog {
  //自定义弹窗的子弹窗的controller
  subDialogController: CustomDialogController | null = new CustomDialogController({
    builder: SubCustomDialogExample(),
    alignment: DialogAlignment.Bottom,
    offset: { dx: 0, dy: 0 }
  })
  //控制本自定义弹窗的controller放在其他自定义弹窗的controller的最后
  controller?: CustomDialogController
  //自定义弹窗的Menu
  @State menuShow: boolean = false
  @State select: boolean = true
  private iconStr: ResourceStr = $r('app.media.startIcon')
  private iconStr2: ResourceStr = $r('app.media.startIcon')

  @Builder
  SubMenu_Router() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '跳转', labelInfo: 'Router Go' })
    }
  }

  @Builder
  MyMenu_Router() {
    Menu() {
      MenuItem({ startIcon: $r('app.media.startIcon'), content: '跳转选项' })
      MenuItem({ startIcon: $r('app.media.startIcon'), content: '菜单选项' })
        .enabled(false)

      MenuItem({
        startIcon: this.iconStr,
        content: '菜单选项',
        endIcon: this.iconStr2,
        builder: (): void => this.SubMenu_Router()
      })

      MenuItemGroup({ header: '小标题' }) {
        MenuItem({ content: '菜单选项' })
          .selectIcon(true)
          .selected(this.select)
          .onChange((selected) => {
            console.info('menuItem select' + selected);
            this.iconStr2 = $r('app.media.startIcon');
          })
        MenuItem({
          startIcon: this.iconStr,
          content: '菜单选项',
          endIcon: this.iconStr2,
          builder: (): void => this.SubMenu_Router()
        })
      }

      MenuItem({
        startIcon: $r('app.media.startIcon'),
        content: '菜单选项',
      })
    }
  }

  //自定义弹窗的popup
  @State handlePopup: boolean = false

  build() {
    Column({ space: 10 }) {
      //自定义弹窗中弹其他弹窗类组件
      Button('点我打开弹窗类')
        .margin({ top: 10, bottom: 40 })
        .onClick(() => {
          setTimeout(() => {
            // 弹出气泡
            this.handlePopup = !this.handlePopup
          }, 100)
          setTimeout(() => {
            // 弹出子窗子弹窗
            if (this.subDialogController != null) {
              this.subDialogController.open()
            }
          }, 200)

          setTimeout(() => {
            // 弹出菜单
            this.menuShow = !this.menuShow
          }, 300)
        })

        //设置浮层
        .overlay('This is the overlay text.', {
          align: Alignment.Bottom,
          offset: { x: 0, y: 30 }
        })
        //绑定Menu
        .bindMenu(this.menuShow!!, this.MyMenu_Router(), { placement: Placement.Bottom })
        //绑定popup
        .bindPopup(this.handlePopup, {
          message: 'This is a popup with PopupOptions',
          placement: Placement.Bottom,
          showInSubWindow: false,
          primaryButton: {
            value: 'confirm',
            action: () => {
              this.handlePopup = !this.handlePopup
              console.info('confirm Button click')
            }
          },
          // 第二个按钮
          secondaryButton: {
            value: 'cancel',
            action: () => {
              this.handlePopup = !this.handlePopup
              console.info('cancel Button click')
            }
          },
          onStateChange: (e) => {
            console.info(JSON.stringify(e.isVisible))
            if (!e.isVisible) {
              this.handlePopup = false
            }
          }
        })

      Divider()
      Flex({ justifyContent: FlexAlign.SpaceAround }) {
        Button('cancel')
          .onClick(() => {
            if (this.controller != undefined) {
              this.controller.close()
            }
          }).backgroundColor(0xffffff).fontColor(Color.Black)

        Button('confirm')
          .onClick(() => {
            if (this.controller != undefined) {
              this.controller.close()
            }
          }).backgroundColor(0xffffff).fontColor(Color.Red)
      }.margin({ bottom: 10 })
    }.borderRadius(10)
  }
}

//自定义弹窗：doc示例的builder
@CustomDialog
export struct SubCustomDialogExample {
  subController?: CustomDialogController

  build() {
    Column() {
      Text('我是第二个弹窗')
        .fontSize(30)
        .height(100)
      Button('点我关闭第二个弹窗')
        .onClick(() => {
          if (this.subController != undefined) {
            this.subController.close()
          }
        })
        .margin(20)
    }
  }
}

@CustomDialog
export struct CustomDialogExample {
  @Link textValue: string
  @Link inputValue: string
  subDialogController: CustomDialogController | null = new CustomDialogController({
    builder: SubCustomDialogExample(),
    alignment: DialogAlignment.Bottom,
    offset: { dx: 0, dy: -25 }
  })
  controller?: CustomDialogController
  // 若尝试在CustomDialog中传入多个其他的Controller，以实现在CustomDialog中打开另一个或另一些CustomDialog，那么此处需要将指向自己的controller放在所有controller的后面
  cancel: () => void = () => {
  }
  confirm: () => void = () => {
  }

  build() {
    Column() {
      Text('Change text').fontSize(20).margin({ top: 10, bottom: 10 })
      TextInput({ placeholder: '', text: this.textValue }).height(60).width('90%')
        .onChange((value: string) => {
          this.textValue = value
        })
      Text('Whether to change a text?').fontSize(16).margin({ bottom: 10 })
      Flex({ justifyContent: FlexAlign.SpaceAround }) {
        Button('cancel')
          .onClick(() => {
            if (this.controller != undefined) {
              this.controller.close()
              this.cancel()
            }
          }).backgroundColor(0xffffff).fontColor(Color.Black)
        Button('confirm')
          .onClick(() => {
            if (this.controller != undefined) {
              this.inputValue = this.textValue
              this.controller.close()
              this.confirm()
            }
          }).backgroundColor(0xffffff).fontColor(Color.Red)
      }.margin({ bottom: 10 })

      Button('点我打开第二个弹窗')
        .onClick(() => {
          if (this.subDialogController != null) {
            this.subDialogController.open()
          }
        })
        .margin(20)
    }.borderRadius(10)

    // 如果需要使用border属性或cornerRadius属性，请和borderRadius属性一起使用。
  }
}

//自定义弹窗：builder设置验证customStyle
@CustomDialog
export struct UpgradeDialog1 {
  private controller: CustomDialogController

  build() {
    Column() {
      Text($r('app.string.custom_dialog_title'))
        .padding(8)
        .fontSize(24)
      this.PermissionIntroduction($r('app.media.startIcon'), $r('app.string.custom_dialog_permission_microphone'),
        $r('app.string.custom_dialog_permission_microphone_info'))
      this.PermissionIntroduction($r('app.media.startIcon'), $r('app.string.custom_dialog_permission_location'),
        $r('app.string.custom_dialog_permission_location_info'))
      Blank()
      Button($r('app.string.custom_dialog1'))
        .height(40)
        .fontSize(24)
        .fontColor(Color.White)
        .margin({ left: 4, right: 4, top: 12 })
        .onClick(() => {
          this.controller.close()
        })
    }
    .margin(20)
    .height(400)
    .borderRadius(24)
    .padding({ top: 20, bottom: 32 })
    .backgroundColor($r('app.color.background_shallow_grey'))
  }

  @Builder
  PermissionIntroduction(image: Resource, permissionName: Resource, introduction: Resource) {
    Row() {
      Image(image)
        .width(50)
        .height(50)
        .margin({ left: 30, right: 30 })
      Column({ space: 4 }) {
        Text(permissionName)
          .fontSize(20)
        Text(introduction)
          .fontSize(18)
          .fontColor($r('app.color.font_color_shallow'))
          .constraintSize({ maxWidth: 280 })
      }
      .alignItems(HorizontalAlign.Start)
    }
    .width('100%')
    .margin({ top: 20 })
  }
}

@CustomDialog
export struct UpgradeDialog2 {
  private controller: CustomDialogController

  build() {
    Column() {
      Text($r('app.string.custom_dialog_title'))
        .padding(8)
        .fontSize(24)
      this.PermissionIntroduction($r('app.media.startIcon'), $r('app.string.custom_dialog_permission_microphone'),
        $r('app.string.custom_dialog_permission_microphone_info'))
      this.PermissionIntroduction($r('app.media.startIcon'), $r('app.string.custom_dialog_permission_location'),
        $r('app.string.custom_dialog_permission_location_info'))
      Blank()
      Button($r('app.string.custom_dialog2'))
        .height(40)
        .fontSize(24)
        .fontColor(Color.White)
        .margin({ left: 4, right: 4, top: 12 })
        .onClick(() => {
          this.controller.close()
        })
    }
    .margin(20)
    .height(400)
    .borderRadius(24)
    .padding({ top: 20, bottom: 32 })
    .backgroundColor($r('app.color.background_shallow_grey'))
  }

  @Builder
  PermissionIntroduction(image: Resource, permissionName: Resource, introduction: Resource) {
    Row() {
      Image(image)
        .width(50)
        .height(50)
        .margin({ left: 30, right: 30 })
      Column({ space: 4 }) {
        Text(permissionName)
          .fontSize(20)
        Text(introduction)
          .fontSize(18)
          .fontColor($r('app.color.font_color_shallow'))
          .constraintSize({ maxWidth: 280 })
      }
      .alignItems(HorizontalAlign.Start)
    }
    .width('100%')
    .margin({ top: 20 })
  }
}

