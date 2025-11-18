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

import window from '@ohos.window';
import { BusinessError } from '@ohos.base';
import observer from '@ohos.arkui.observer'

@Entry
@Component
struct Window {
  private curWindow: window.Window | null = null;
  @State x: number = 50;
  @State y: number = 200;
  @Provide('pageInfos') pageInfos: NavPathStack = new NavPathStack()
  pathStack: NavPathStack = new NavPathStack()
  @State text1: string = ''
  @State text2: string = ''

  onPageShow() {
    // query navigation info
    let navigationInfo: observer.NavigationInfo | undefined = this.queryNavigationInfo()
    console.log('==================================')
    console.log('page two navDestination aboutToappear')
    console.log(JSON.stringify(navigationInfo))
    if (navigationInfo !== undefined) {
      this.pathStack = navigationInfo.pathStack;
    }
  }

  @Builder
  PageMap(name: string) {
    if (name === 'pageTwo') {

    }
  }

  closeWindow() {
    console.log(`testTag prepare to close Window`)
    try {
      this.curWindow = window.findWindow('testWindow');
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

  build() {
    Column({ space: 10 }) {
      Button('close Window')
        .onClick(() => {
          this.closeWindow();
        })

      Navigation() {
        Scroll() {
          SideBarContainer(SideBarContainerType.Embed) {
            Column() {


            }.width('100%')
            .justifyContent(FlexAlign.SpaceEvenly)
            .backgroundColor('#19000000')

            Column() {
              Text('SideBarContainer content text1').fontSize(25)
              Text('SideBarContainer content text2').fontSize(25)
            }
            .margin({ top: 50, left: 20, right: 30 })
          }
          .controlButton({
            icons: {
              hidden: $r('app.media.icon'),
              shown: $r('app.media.icon'),
              switching: $r('app.media.icon')
            }
          })
          .sideBarWidth(150)
          .minSideBarWidth(50)
          .maxSideBarWidth(300)
          .minContentWidth(0)
        }
      }
      .title('子窗口')
      .navDestination(this.PageMap)
      .backgroundColor(Color.Pink)
      .width('100%')
      .height('280vp')
    }
    .backgroundColor(Color.Green)
    .width('100%')
    .height('100%')
    .borderWidth(1)
  }
}