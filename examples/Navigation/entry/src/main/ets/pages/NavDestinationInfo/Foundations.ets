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

// Index.ets
import observer from '@ohos.arkui.observer'
import window from '@ohos.window';
import base from '@ohos.base';


@Entry
@Component
struct NavigationExample {
  private myWindow: window.Window | null = null;

  createWindow() {
    try {
      window.createWindow({name: "testWindow", windowType: window.WindowType.TYPE_DIALOG, ctx: getContext(this)})
        .then((windowObj: window.Window) => {
          console.log(`testTag success to createWindow`)
          this.myWindow = windowObj;
          let ls = new LocalStorage();
          this.myWindow?.loadContent('pages/NavDestinationInfo/WindowTwo', ls)
            .then(() => {
              console.log(`testTag success to loadContent`)
            }).catch((e: base.BusinessError) => {
            console.log(`testTag failed to loadContent: ${JSON.stringify(e)}`)
          })
          this.myWindow.showWindow().then(() => {
            console.log(`testTag success to showWindow`)
            this.myWindow?.resize(1000, 2200);
            this.myWindow?.moveWindowTo(50, 200);
            // let ls = new LocalStorage();
            // this.myWindow?.loadContent('pages/WindowTwo', ls)
            //   .then(() => {
            //     console.log(`testTag success to loadContent`)
            //   }).catch((e: base.BusinessError) => {
            //   console.log(`testTag failed to loadContent: ${JSON.stringify(e)}`)
            // })
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


  build() {
    Column(){
      OtherNode()
      NavigationNode()
      Button('开启子窗口')
        .onClick(() => {
          this.createWindow();
        })
    }
  }
}

@Component
struct NavigationNode {
  @Provide('pageInfos') pageInfos: NavPathStack = new NavPathStack()

  build() {
    Navigation(this.pageInfos) {

      Column() {
        Button('disableAnimation true', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(10)
          .onClick(() => {
            this.pageInfos.disableAnimation(true)
          })
        Button('pushPath PageOne', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(10)
          .onClick(() => {
            this.pageInfos.pushPath({ name: 'MainPageOne', param: 'MainPageOne' },false) //将name指定的NavDestination页面信息入栈
          })
        Button('pushPath PageTwo', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(10)
          .onClick(() => {
            this.pageInfos.pushPath({ name: 'MainPageTwo', param: 'MainPageTwo' }) //将name指定的NavDestination页面信息入栈
          })
        Button('pushPath PageTwoDialog', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(10)
          .onClick(() => {
            this.pageInfos.pushPath({ name: 'MainPageTwoDialog', param: 'MainPageTwoDialog' }) //将name指定的NavDestination页面信息入栈
          })
        Button('pushDestination PageTwo', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(10)
          .onClick(() => {
            this.pageInfos.pushDestination({ name: 'MainPageTwo', param: 'MainPageTwo' }) //将name指定的NavDestination页面信息入栈
          })

        navDestinationInNavigation()

      }
    }.title('NavIndex')
    .mode(NavigationMode.Stack)
    .id('navigation1')
    .height(500)
  }
}


@Component
struct OtherNode {
  pathStack : NavPathStack = new NavPathStack()

  aboutToAppear() {
    // query navigation info
    console.log("==================================")
    console.log("other aboutToappear")
    let navigationInfo : observer.NavigationInfo | undefined = this.queryNavigationInfo()
    console.log("获取： "+JSON.stringify(navigationInfo))
    if (navigationInfo !== undefined) {
      this.pathStack = navigationInfo.pathStack;
    }
  }
  build() {
    Row() {
      Button('跳转到PageOne')
        .onClick(()=>{
          this.pathStack.pushPathByName('MainPageOne', 'MainPageOne')
        })
      Button('跳转到PageTwo')
        .onClick(()=>{
          this.pathStack.pushPathByName('MainPageTwo', 'MainPageTwo')
        })
    }
  }
}
@Component
struct navDestinationInNavigation {
  @State isActiveWLAN: boolean = false
  @State isActiveBluetooth: boolean = false

  build() {
    Column() {
      NavRouter() {
        Row() {
          Row()
            .width(30)
            .height(30)
            .borderRadius(30)
            .margin({ left: 3, right: 10 })
            .backgroundColor(Color.Pink)
          Text(`WLAN`)
            .fontSize(22)
            .fontWeight(500)
            .textAlign(TextAlign.Center)

        }
        .width('90%')
        .height(60)

        NavDestination() {
          Flex({ direction: FlexDirection.Row }) {
            Text('未找到可用WLAN').fontSize(30).padding({ left: 15 })

          }
        }.title("WLAN")
        .onShown(() => {
          console.log("navRouter enter WLAN")
          let navigationInfo : observer.NavigationInfo | undefined = this.queryNavigationInfo()
          console.log("获取NavigationInfo："+JSON.stringify(navigationInfo))
        })
      }
      .margin({ top: 10, bottom: 10 })
      .backgroundColor(this.isActiveWLAN ? '#ccc' : '#fff')
      .borderRadius(20)
      .mode(NavRouteMode.PUSH_WITH_RECREATE)
      .onStateChange((isActivated: boolean) => {
        this.isActiveWLAN = isActivated
      })

      NavRouter() {
        Row() {
          Row()
            .width(30)
            .height(30)
            .borderRadius(30)
            .margin({ left: 3, right: 10 })
            .backgroundColor(Color.Pink)
          Text(`蓝牙`)
            .fontSize(22)
            .fontWeight(500)
            .textAlign(TextAlign.Center)
        }
        .width('90%')
        .height(60)

        NavDestination() {
          Flex({ direction: FlexDirection.Row }) {
            Text('未找到可用蓝牙').fontSize(30).padding({ left: 15 })
          }
        }.title("蓝牙")
        .onShown(() => {
          console.log("navRouter enter bluetooth")
          let navigationInfo : observer.NavigationInfo | undefined = this.queryNavigationInfo()
          console.log("ddd获取NavigationInfo："+JSON.stringify(navigationInfo))
        })
      }
      .margin({ top: 10, bottom: 10 })
      .backgroundColor(this.isActiveBluetooth ? '#ccc' : '#fff')
      .borderRadius(20)
      .mode(NavRouteMode.REPLACE)
      .onStateChange((isActivated: boolean) => {
        this.isActiveBluetooth = isActivated
      })
    }
  }
}