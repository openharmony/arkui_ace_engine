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

import { PageOneTmp } from './PageOne'

@Component
export struct PageTwoTmp {
  @Consume('pageInfo') pageInfo: NavPathStack;
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
        Text('DIALOG自定义标题')
          .fontColor('black')
          .fontSize(20)
          .lineHeight(41)
          .fontWeight(700)
        Text('自定义副标题')
          .fontColor('black')
          .fontSize(14)
          .lineHeight(19)
          .opacity(0.4)
          .margin({ top: 2, bottom: 20 })
      }.alignItems(HorizontalAlign.Start)
    }
  }

  @Builder
  PageMap(name: string) {
    if (name === 'pageOne') {
      PageOneTmp()
    }
  }

  build() {
    NavDestination() {
      Column() {
        Button('STANDARD模式界面', { stateEffect: true, type: ButtonType.Capsule })
          .width('40%')
          .height(50)
          .margin(20)
          .onClick(() => {
            this.pageInfo.pushPath({ name: 'pageOne' });
          })
        Button('隐藏标题(是/否)', { stateEffect: true, type: ButtonType.Capsule })
          .backgroundColor('black')
          .width('40%')
          .height(50)
          .margin(20)
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
      }.width('100%').height('100%')
    }
    .title(this.NavigationTitle)
    .mode(NavDestinationMode.DIALOG)
    .hideTitleBar(this.hide)
    .backgroundColor('rgba(192,192,192,1)')
    .menus(this.menuItems)
  }
}