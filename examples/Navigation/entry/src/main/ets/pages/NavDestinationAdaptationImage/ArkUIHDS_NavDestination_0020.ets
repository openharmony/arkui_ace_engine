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

import { TitleBar } from '../common/TitleBar'

@Entry
@Component
struct ArkUIHDS_NavDestination_0020 {
  @State isActiveWLAN: boolean = false
  @State isActiveBluetooth: boolean = false
  @State hide: boolean = false;
  private menuItems: Array<NavigationMenuItem> = [
    {
      value: "大数据",
      icon: "resources/base/media/startIcon.png",
    },
    {
      value: "接口",
      icon: 'resources/base/media/background.png',
      isEnabled: false,
    },
    {
      value: "文件",
      icon: 'resources/base/media/foreground.png',
      isEnabled: true,
    }
  ]

  @Builder NavigationTitle() {
    Row() {
      Column() {
        Text('自定义标题')
          .fontColor('red')
          .fontSize(30)
          .lineHeight(41)
          .fontWeight(700)
        Text('自定义副标题')
          .fontColor('red')
          .fontSize(14)
          .lineHeight(19)
          .opacity(0.4)
          .margin({ top: 2, bottom: 20 })
      }.alignItems(HorizontalAlign.Start)
    }
  }

  build() {
    Column() {
      TitleBar({ name: 'NavDestination_0020' })
      Navigation() {
        NavRouter() {
          Row() {
            Row()
              .width(30)
              .height(30)
              .borderRadius(30)
              .margin({ left: 3, right: 10 })
              .backgroundColor(Color.Blue)
            Text(`DIALOG模式嵌套DIALOG模式`)
              .fontSize(15)
              .fontWeight(300)
              .textAlign(TextAlign.Center)
          }
          .width('90%')
          .height(80)

          NavDestination() {
            NavDestination() {
              Button('隐藏标题(是/否)', { stateEffect: true, type: ButtonType.Capsule })
                .backgroundColor('black')
                .width('40%')
                .height(40)
                .margin(10)
                .onClick(() => {
                  try {
                    if (this.hide == false) {
                      this.hide = true;
                    } else {
                      this.hide = false;
                    }
                  } catch (error) {
                    console.error(`call hide_two failed`);
                  }
                })
            }
            .menus(this.menuItems)
            .mode(NavDestinationMode.DIALOG)
            .height('400')
            .title('嵌套DIALOG模式标题')
            .hideTitleBar(this.hide)
            .backgroundColor('rgba(255,250,250,0.6)')
          }
          .menus(this.menuItems)
          .mode(NavDestinationMode.DIALOG)
          .title({ builder: this.NavigationTitle, height: 82 })
          .hideTitleBar(this.hide)
          .backgroundColor('rgba(192,192,192,1)')
        }.backgroundColor(this.isActiveBluetooth ? '#ccc' : '#fff')
        .borderRadius(50)
        .onStateChange((isActivated: boolean) => {
          this.isActiveBluetooth = isActivated
        })

        NavRouter() {
          Row() {
            Row()
              .width(30)
              .height(30)
              .borderRadius(30)
              .margin({ left: 3, right: 10 })
              .backgroundColor(Color.Blue)
            Text(`STANDARD模式嵌套STANDARD模式`)
              .fontSize(15)
              .fontWeight(300)
              .textAlign(TextAlign.Center)
          }
          .width('90%')
          .height(80)

          NavDestination() {
            NavDestination() {
              Button('隐藏标题(是/否)', { stateEffect: true, type: ButtonType.Capsule })
                .backgroundColor('black')
                .width('40%')
                .height(40)
                .margin(10)
                .onClick(() => {
                  try {
                    if (this.hide == false) {
                      this.hide = true;
                    } else {
                      this.hide = false;
                    }
                  } catch (error) {
                    console.error(`call hide_two failed`);
                  }
                })
            }
            .menus(this.menuItems)
            .mode(NavDestinationMode.STANDARD)
            .hideTitleBar(this.hide)
            .height('400')
            .title('嵌套STANDARD模式标题')
            .backgroundColor('rgba(192,192,192,0.7)')
          }
          .menus(this.menuItems)
          .mode(NavDestinationMode.STANDARD)
          .title({ main: "STANDARD模式标题", sub: "STANDARD模式副标题" })
          .hideTitleBar(this.hide)
          .backgroundColor('#0c182431')
        }.backgroundColor(this.isActiveBluetooth ? '#ccc' : '#fff')
        .borderRadius(50)
        .onStateChange((isActivated: boolean) => {
          this.isActiveBluetooth = isActivated
        })
        Button('隐藏标题(是/否)', { stateEffect: true, type: ButtonType.Capsule })
          .backgroundColor('black')
          .width('40%')
          .height(50)
          .margin(10)
          .onClick(() => {
            try {
              if (this.hide == false) {
                this.hide = true;
              } else {
                this.hide = false;
              }
            } catch (error) {
              console.error(`call hide failed`);
            }
          })
      }
      .title('NavDestination20')
      .titleMode(NavigationTitleMode.Mini)
      .mode(NavigationMode.Auto)
      .hideTitleBar(this.hide)
      .hideToolBar(false)
    }.height('100%')
  }
}