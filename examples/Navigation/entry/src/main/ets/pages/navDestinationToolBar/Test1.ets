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

import window from '@ohos.window';
import base from '@ohos.base';

@Entry
@Component
struct Test1 {
  pathStack: NavPathStack = new NavPathStack();
  scroller: Scroller = new Scroller()
  @State navigationMode: NavigationMode = NavigationMode.Auto
  @State navBarPosition: NavBarPosition = NavBarPosition.Start

  build() {
    Navigation(this.pathStack){
      Scroll(this.scroller) {
        Column({space:'1vp'}) {
          Button('push pageOne').onClick(() => {
            this.pathStack.pushPathByName('PageOneNoToolBar', null)
          })
          Button('push pageTwo').onClick(() => {
            this.pathStack.pushPathByName('PageTwoWithToolBar', null)
          })
          Button('push pageThree').onClick(() => {
            this.pathStack.pushPathByName('PageThreeWithToolBar', null)
          })
          Button('push pageFour').onClick(() => {
            this.pathStack.pushPathByName('PageFourWithToolBar', null)
          })
          Button('push pageFive').onClick(() => {
            this.pathStack.pushPathByName('PageFiveWithToolBar', null)
          })
          Button('push pageSix').onClick(() => {
            this.pathStack.pushPathByName('PageSixWithToolBar', null)
          })
          Button('push pageSeven').onClick(() => {
            this.pathStack.pushPathByName('PageSevenWithToolBar', null)
          })
          Button('push pageEight').onClick(() => {
            this.pathStack.pushPathByName('PageEightWithToolBar', null)
          })
          Button('push pageNine').onClick(() => {
            this.pathStack.pushPathByName('PageNineWithToolBar', null)
          })
          Button('mode: Stack').onClick(() => {
            this.navigationMode = NavigationMode.Stack
          })
          Button('mode: Split').onClick(() => {
            this.navigationMode = NavigationMode.Split
          })
          Button("NavBarPosition: Start").onClick(() => {
            this.navBarPosition = NavBarPosition.Start
          })
          Button("NavBarPosition: End").onClick(() => {
            this.navBarPosition = NavBarPosition.End
          })
          Button("push Dialog").onClick(() => {
            this.pathStack.pushPathByName('DialogPageWithToolBar', null)
          })

          Button("开启子窗口").onClick(() => {
            this.createWindow()
          })
          Button("push page11").onClick(() => {
            this.pathStack.pushPathByName('Page11WithToolBar', null)
          })
        }
      }
    }
    .width('100%')
    .height('100%')
    .title("Navigation")
    .mode(this.navigationMode)
    .navBarPosition(this.navBarPosition)
  }

  private myWindow: window.Window | null = null;
  createWindow() {
    try {
      window.createWindow({name: "testWindow", windowType: window.WindowType.TYPE_DIALOG, ctx: getContext(this)})
        .then((windowObj: window.Window) => {
          console.log(`testTag success to createWindow`)
          this.myWindow = windowObj;
          let ls = new LocalStorage();
          this.myWindow?.loadContent('pages/NavDestinationToolBar/Test1', ls)
            .then(() => {
              console.log(`testTag success to loadContent`)
              this.myWindow?.showWindow().then(() => {
                console.log(`testTag success to showWindow`)
                this.myWindow?.resize(1000, 2000);
                this.myWindow?.moveWindowTo(50, 200);
              }).catch((e: base.BusinessError) => {
                console.log(`testTag failed to showWindow: ${JSON.stringify(e)}`)
              });
            }).catch((e: base.BusinessError) => {
            console.log(`testTag failed to loadContent: ${JSON.stringify(e)}`)
          })

        }).catch((e: base.BusinessError) => {
        console.log(`testTag failed to createWindow: ${JSON.stringify(e)}`)
      })
    } catch (e) {
      console.log(`testTag catch exception: ${JSON.stringify(e)}`)
    }
  }
}