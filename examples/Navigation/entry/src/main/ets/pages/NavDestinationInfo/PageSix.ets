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

// // PageSix.ets
// import observer from '@ohos.arkui.observer';
// import {} from 'harTest'
// import {} from 'hspTest'
//
// @Builder
// export function pageSix(name: string, param: Object) {
//   CustomNode()
// }
//
// @Component
// struct CustomNode {
//   pathStack : NavPathStack = new NavPathStack()
//   @Consume('pageInfos') pageInfos: NavPathStack;
//   @State text1 : string = ""
//   @State text2 : string = ""
//
//   aboutToAppear() {
//     console.log("sxy:: enter navRouter")
//     // query navigation info
//     let navigationInfo : observer.NavigationInfo | undefined = this.queryNavigationInfo()
//     console.log("==================================")
//     console.log("page six navRouter aboutToappear")
//     console.log(JSON.stringify(navigationInfo))
//     if (navigationInfo !== undefined) {
//       this.pathStack = navigationInfo.pathStack;
//     }
//   }
//
//   build() {
//     Column(){
//       NavDestination() {
//         NavRouterExample()
//       }.title('pageSix')
//       .onBackPressed(() => {
//         this.pathStack.pop()
//         return true
//       })
//       .id('navDestination6')
//       .height(350)
//
//       Scroll(){
//         Column(){
//           Text('queryNavigationInfo:' + '\r' + this.text1)
//           Button('queryNavigationInfo', { stateEffect: true, type: ButtonType.Capsule })
//             .width('40%')
//             .height(30)
//             .margin(10)
//             .onClick(() => {
//               this.text1 = '获取栈中所有NavDestination页面的名称:' + JSON.stringify(this.pathStack.getAllPathName()) + '\r'
//                 + '获取index为1的NavDestination页面的参数信息:' + JSON.stringify(this.pathStack.getParamByIndex(1)) +'\r'
//                 + '获取全部名为MainPageTwo的NavDestination页面的参数信息:' + JSON.stringify(this.pathStack.getParamByName('MainPageTwo')) + '\r'
//                 + '获取全部名为MainPageOne的NavDestination页面的位置索引:' + JSON.stringify(this.pathStack.getIndexByName('MainPageOne')) + '\r'
//                 + '获取栈大小:' +   JSON.stringify(this.pathStack.size())
//               console.log('获取queryNavigationInfo-------------------')
//               console.log('获取栈中所有NavDestination页面的名称', JSON.stringify(this.pathStack.getAllPathName()))
//               console.log('获取index为0的NavDestination页面的参数信息', JSON.stringify(this.pathStack.getParamByIndex(0)))
//               console.log('获取index为1的NavDestination页面的参数信息', JSON.stringify(this.pathStack.getParamByIndex(1)))
//               console.log('获取全部名为MainPageOne的NavDestination页面的位置索引', JSON.stringify(this.pathStack.getIndexByName('MainPageOne')))
//               console.log('获取全部名为MainPageTwo的NavDestination页面的参数信息', JSON.stringify(this.pathStack.getParamByName('MainPageTwo')))
//               console.log('获取栈大小', JSON.stringify(this.pathStack.size()))
//               console.log('获取完整信息', JSON.stringify(this.pathStack))
//             })
//
//           Text('pageInfos:' + '\r' + this.text2)
//           Button('pageInfos', { stateEffect: true, type: ButtonType.Capsule })
//             .width('40%')
//             .height(30)
//             .margin(10)
//             .onClick(() => {
//               this.text2 = '获取栈中所有NavDestination页面的名称:' + JSON.stringify(this.pageInfos.getAllPathName()) + '\r'
//                 + '获取index为1的NavDestination页面的参数信息:' + JSON.stringify(this.pageInfos.getParamByIndex(1)) +'\r'
//                 + '获取全部名为MainPageTwo的NavDestination页面的参数信息:' + JSON.stringify(this.pageInfos.getParamByName('MainPageTwo')) + '\r'
//                 + '获取全部名为MainPageOne的NavDestination页面的位置索引:' + JSON.stringify(this.pageInfos.getIndexByName('MainPageOne')) + '\r'
//                 + '获取栈大小:' +   JSON.stringify(this.pageInfos.size())
//               console.log('获取pageInfos-------------------')
//               console.log('获取栈中所有NavDestination页面的名称', JSON.stringify(this.pageInfos.getAllPathName()))
//               console.log('获取index为0的NavDestination页面的参数信息', JSON.stringify(this.pageInfos.getParamByIndex(0)))
//               console.log('获取index为1的NavDestination页面的参数信息', JSON.stringify(this.pageInfos.getParamByIndex(1)))
//               console.log('获取全部名为MainPageOne的NavDestination页面的位置索引', JSON.stringify(this.pageInfos.getIndexByName('MainPageOne')))
//               console.log('获取全部名为MainPageTwo的NavDestination页面的参数信息', JSON.stringify(this.pageInfos.getParamByName('MainPageTwo')))
//               console.log('获取栈大小', JSON.stringify(this.pageInfos.size()))
//               console.log('获取完整信息', JSON.stringify(this.pageInfos))
//             })
//         }
//       }
//       .height(400)
//     }
//   }
// }
//
// @Component
// struct NavRouterExample {
//   @State isActiveWLAN: boolean = false
//   @State isActiveBluetooth: boolean = false
//
//
//   build() {
//     Navigation() {
//       NavRouter() {
//         Row() {
//           Row()
//             .width(30)
//             .height(30)
//             .borderRadius(30)
//             .margin({ left: 3, right: 10 })
//             .backgroundColor(Color.Pink)
//           Text(`WLAN`)
//             .fontSize(22)
//             .fontWeight(500)
//             .textAlign(TextAlign.Center)
//
//         }
//         .width('90%')
//         .height(60)
//
//         NavDestination() {
//           Flex({ direction: FlexDirection.Row }) {
//             Text('未找到可用WLAN').fontSize(30).padding({ left: 15 })
//
//           }
//         }.title("WLAN")
//         .onShown(() => {
//           console.log("navRouter enter WLAN")
//           let navigationInfo : observer.NavigationInfo | undefined = this.queryNavigationInfo()
//           console.log("获取NavigationInfo："+JSON.stringify(navigationInfo))
//         })
//       }
//       .margin({ top: 10, bottom: 10 })
//       .backgroundColor(this.isActiveWLAN ? '#ccc' : '#fff')
//       .borderRadius(20)
//       .mode(NavRouteMode.PUSH_WITH_RECREATE)
//       .onStateChange((isActivated: boolean) => {
//         this.isActiveWLAN = isActivated
//       })
//
//       NavRouter() {
//         Row() {
//           Row()
//             .width(30)
//             .height(30)
//             .borderRadius(30)
//             .margin({ left: 3, right: 10 })
//             .backgroundColor(Color.Pink)
//           Text(`蓝牙`)
//             .fontSize(22)
//             .fontWeight(500)
//             .textAlign(TextAlign.Center)
//         }
//         .width('90%')
//         .height(60)
//
//         NavDestination() {
//           Flex({ direction: FlexDirection.Row }) {
//             Text('未找到可用蓝牙').fontSize(30).padding({ left: 15 })
//           }
//         }.title("蓝牙")
//         .onShown(() => {
//           console.log("navRouter enter bluetooth")
//           let navigationInfo : observer.NavigationInfo | undefined = this.queryNavigationInfo()
//           console.log("ddd获取NavigationInfo："+JSON.stringify(navigationInfo))
//         })
//       }
//       .margin({ top: 10, bottom: 10 })
//       .backgroundColor(this.isActiveBluetooth ? '#ccc' : '#fff')
//       .borderRadius(20)
//       .mode(NavRouteMode.REPLACE)
//       .onStateChange((isActivated: boolean) => {
//         this.isActiveBluetooth = isActivated
//       })
//     }
//     .height('100%')
//     .width('100%')
//     .title('设置')
//     .backgroundColor("#F2F3F5")
//     .titleMode(NavigationTitleMode.Free)
//     .mode(NavigationMode.Auto)
//   }
// }

// PageSix.ets
import observer from '@ohos.arkui.observer';

@Builder
export function pageSix(name: string, param: Object) {
  CustomNode()
}

@Component
struct CustomNode {
  pathStack : NavPathStack = new NavPathStack()
  @Consume('pageInfos') pageInfos: NavPathStack;
  @State text1 : string = ""
  @State text2 : string = ""

  aboutToAppear() {
    console.log("sxy:: enter navRouter")
    // query navigation info
    let navigationInfo : observer.NavigationInfo | undefined = this.queryNavigationInfo()
    console.log("==================================")
    console.log("page six navRouter aboutToappear")
    console.log(JSON.stringify(navigationInfo))
    if (navigationInfo !== undefined) {
      this.pathStack = navigationInfo.pathStack;
    }
  }

  build() {
    Column(){
      // NavDestination() {
      //   NavRouterExample()
      // }.title('pageSix')
      // .onBackPressed(() => {
      //   this.pathStack.pop()
      //   return true
      // })
      // .id('navDestination6')
      // .height(350)

      Scroll(){
        Column(){
          NavDestination() {
            NavRouterExample()
          }.title('pageSix')
          .onBackPressed(() => {
            this.pathStack.pop()
            return true
          })
          .id('navDestination6')
          .height('100%')

          // Text('queryNavigationInfo:' + '\r' + this.text1)
          // Button('queryNavigationInfo', { stateEffect: true, type: ButtonType.Capsule })
          //   .width('40%')
          //   .height(30)
          //   .margin(10)
          //   .onClick(() => {
          //     this.text1 = '获取栈中所有NavDestination页面的名称:' + JSON.stringify(this.pathStack.getAllPathName()) + '\r'
          //       + '获取index为1的NavDestination页面的参数信息:' + JSON.stringify(this.pathStack.getParamByIndex(1)) +'\r'
          //       + '获取全部名为MainPageTwo的NavDestination页面的参数信息:' + JSON.stringify(this.pathStack.getParamByName('MainPageTwo')) + '\r'
          //       + '获取全部名为MainPageOne的NavDestination页面的位置索引:' + JSON.stringify(this.pathStack.getIndexByName('MainPageOne')) + '\r'
          //       + '获取栈大小:' +   JSON.stringify(this.pathStack.size())
          //     console.log('获取queryNavigationInfo-------------------')
          //     console.log('获取栈中所有NavDestination页面的名称', JSON.stringify(this.pathStack.getAllPathName()))
          //     console.log('获取index为0的NavDestination页面的参数信息', JSON.stringify(this.pathStack.getParamByIndex(0)))
          //     console.log('获取index为1的NavDestination页面的参数信息', JSON.stringify(this.pathStack.getParamByIndex(1)))
          //     console.log('获取全部名为MainPageOne的NavDestination页面的位置索引', JSON.stringify(this.pathStack.getIndexByName('MainPageOne')))
          //     console.log('获取全部名为MainPageTwo的NavDestination页面的参数信息', JSON.stringify(this.pathStack.getParamByName('MainPageTwo')))
          //     console.log('获取栈大小', JSON.stringify(this.pathStack.size()))
          //     console.log('获取完整信息', JSON.stringify(this.pathStack))
          //   })
          //
          // Text('pageInfos:' + '\r' + this.text2)
          // Button('pageInfos', { stateEffect: true, type: ButtonType.Capsule })
          //   .width('40%')
          //   .height(30)
          //   .margin(10)
          //   .onClick(() => {
          //     this.text2 = '获取栈中所有NavDestination页面的名称:' + JSON.stringify(this.pageInfos.getAllPathName()) + '\r'
          //       + '获取index为1的NavDestination页面的参数信息:' + JSON.stringify(this.pageInfos.getParamByIndex(1)) +'\r'
          //       + '获取全部名为MainPageTwo的NavDestination页面的参数信息:' + JSON.stringify(this.pageInfos.getParamByName('MainPageTwo')) + '\r'
          //       + '获取全部名为MainPageOne的NavDestination页面的位置索引:' + JSON.stringify(this.pageInfos.getIndexByName('MainPageOne')) + '\r'
          //       + '获取栈大小:' +   JSON.stringify(this.pageInfos.size())
          //     console.log('获取pageInfos-------------------')
          //     console.log('获取栈中所有NavDestination页面的名称', JSON.stringify(this.pageInfos.getAllPathName()))
          //     console.log('获取index为0的NavDestination页面的参数信息', JSON.stringify(this.pageInfos.getParamByIndex(0)))
          //     console.log('获取index为1的NavDestination页面的参数信息', JSON.stringify(this.pageInfos.getParamByIndex(1)))
          //     console.log('获取全部名为MainPageOne的NavDestination页面的位置索引', JSON.stringify(this.pageInfos.getIndexByName('MainPageOne')))
          //     console.log('获取全部名为MainPageTwo的NavDestination页面的参数信息', JSON.stringify(this.pageInfos.getParamByName('MainPageTwo')))
          //     console.log('获取栈大小', JSON.stringify(this.pageInfos.size()))
          //     console.log('获取完整信息', JSON.stringify(this.pageInfos))
          //   })
        }
      }
      .height(400)
    }.height('100%')
  }
}

@Component
struct NavRouterExample {

  build() {
    Navigation() {
      navDestinationInNavigation()
    }
    .height('100%')
    .width('100%')
    .title('设置')
    .backgroundColor("#F2F3F5")
    .titleMode(NavigationTitleMode.Free)
    .mode(NavigationMode.Auto)
    .id("navigationRouter")
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