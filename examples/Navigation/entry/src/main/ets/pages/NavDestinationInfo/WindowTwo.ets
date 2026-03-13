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
import { BusinessError } from '@ohos.base';
import observer from '@ohos.arkui.observer'


@Entry
@Component
struct Window {

  private curWindow: window.Window | null = null;
  @State x: number = 50;
  @State y: number = 200;

  @Provide('pageInfos') pageInfos: NavPathStack = new NavPathStack()

  pathStack : NavPathStack = new NavPathStack()
  @State text1 : string = ""
  @State text2 : string = ""

  // aboutToAppear() {
  //   // query navigation info
  //   let navigationInfo : observer.NavigationInfo | undefined = this.queryNavigationInfo()
  //   console.log("==================================")
  //   console.log("page two navDestination aboutToappear")
  //   console.log(JSON.stringify(navigationInfo))
  //   if (navigationInfo !== undefined) {
  //     this.pathStack = navigationInfo.pathStack;
  //   }
  // }

  // @Builder
  // PageMap(name: string) {
  //   if (name === 'pageThree') {
  //
  //   }
  // }

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
    Column({space:10}) {
      Button('close Window')
        .onClick(() => {
          this.closeWindow();
        })
      Navigation(this.pageInfos) {
        OtherNode()
        // Scroll(){
        //   Column(){
        //     Button('pushPath PageOne')
        //       .onClick(()=>{
        //          this.pathStack.pushPathByName('MainPageOne', 'MainPageOne')
        //         //this.pageInfos.pushPathByName('MainPageOne', 'MainPageOne')
        //       })
        //
        //     Text('queryNavigationInfo:' + '\r' + this.text1)
        //     Button('queryNavigationInfo', { stateEffect: true, type: ButtonType.Capsule })
        //       .width('40%')
        //       .height(30)
        //       .margin(10)
        //       .onClick(() => {
        //         this.text1 = '获取栈中所有NavDestination页面的名称:' + JSON.stringify(this.pathStack.getAllPathName()) + '\r'
        //           + '获取index为1的NavDestination页面的参数信息:' + JSON.stringify(this.pathStack.getParamByIndex(1)) +'\r'
        //           + '获取全部名为MainPageTwo的NavDestination页面的参数信息:' + JSON.stringify(this.pathStack.getParamByName('MainPageTwo')) + '\r'
        //           + '获取全部名为MainPageOne的NavDestination页面的位置索引:' + JSON.stringify(this.pathStack.getIndexByName('MainPageOne')) + '\r'
        //           + '获取栈大小:' +   JSON.stringify(this.pathStack.size())
        //         console.log('-------------------')
        //         console.log('获取栈中所有NavDestination页面的名称', JSON.stringify(this.pathStack.getAllPathName()))
        //         console.log('获取index为1的NavDestination页面的参数信息', JSON.stringify(this.pathStack.getParamByIndex(1)))
        //         console.log('获取全部名为MainPageTwo的NavDestination页面的参数信息', JSON.stringify(this.pathStack.getParamByName('MainPageTwo')))
        //         console.log('获取全部名为MainPageOne的NavDestination页面的位置索引', JSON.stringify(this.pathStack.getIndexByName('MainPageOne')))
        //         console.log('获取栈大小', JSON.stringify(this.pathStack.size()))
        //       })
        //
        //     Text('pageInfos:' + '\r' + this.text2)
        //     Button('pageInfos', { stateEffect: true, type: ButtonType.Capsule })
        //       .width('40%')
        //       .height(30)
        //       .margin(10)
        //       .onClick(() => {
        //         this.text2 = '获取栈中所有NavDestination页面的名称:' + JSON.stringify(this.pageInfos.getAllPathName()) + '\r'
        //           + '获取index为1的NavDestination页面的参数信息:' + JSON.stringify(this.pageInfos.getParamByIndex(1)) +'\r'
        //           + '获取全部名为MainPageTwo的NavDestination页面的参数信息:' + JSON.stringify(this.pageInfos.getParamByName('MainPageTwo')) + '\r'
        //           + '获取全部名为MainPageOne的NavDestination页面的位置索引:' + JSON.stringify(this.pageInfos.getIndexByName('MainPageOne')) + '\r'
        //           + '获取栈大小:' +   JSON.stringify(this.pageInfos.size())
        //         console.log('-------------------')
        //         console.log('获取栈中所有NavDestination页面的名称', JSON.stringify(this.pageInfos.getAllPathName()))
        //         console.log('获取index为1的NavDestination页面的参数信息', JSON.stringify(this.pageInfos.getParamByIndex(1)))
        //         console.log('获取全部名为MainPageTwo的NavDestination页面的参数信息', JSON.stringify(this.pageInfos.getParamByName('MainPageTwo')))
        //         console.log('获取全部名为MainPageOne的NavDestination页面的位置索引', JSON.stringify(this.pageInfos.getIndexByName('MainPageOne')))
        //         console.log('获取栈大小', JSON.stringify(this.pageInfos.size()))
        //       })
        //   }
        // }
      }
      .title('子窗口')
      //.navDestination(this.PageMap)
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

@Component
struct OtherNode {
  pathStack : NavPathStack = new NavPathStack()
  @State text1 : string = ""
  @State text2 : string = ""
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

      Scroll(){
        Column(){
          Button('pushPath PageOne')
            .onClick(()=>{
              this.pathStack.pushPathByName('MainPageOne', 'MainPageOne')
              //this.pageInfos.pushPathByName('MainPageOne', 'MainPageOne')
            })

          Text('queryNavigationInfo:' + '\r' + this.text1)
          Button('queryNavigationInfo', { stateEffect: true, type: ButtonType.Capsule })
            .width('40%')
            .height(30)
            .margin(10)
            .onClick(() => {
              this.text1 = '获取栈中所有NavDestination页面的名称:' + JSON.stringify(this.pathStack.getAllPathName()) + '\r'
                + '获取index为1的NavDestination页面的参数信息:' + JSON.stringify(this.pathStack.getParamByIndex(1)) +'\r'
                + '获取全部名为MainPageTwo的NavDestination页面的参数信息:' + JSON.stringify(this.pathStack.getParamByName('MainPageTwo')) + '\r'
                + '获取全部名为MainPageOne的NavDestination页面的位置索引:' + JSON.stringify(this.pathStack.getIndexByName('MainPageOne')) + '\r'
                + '获取栈大小:' +   JSON.stringify(this.pathStack.size())
              console.log('-------------------')
              console.log('获取栈中所有NavDestination页面的名称', JSON.stringify(this.pathStack.getAllPathName()))
              console.log('获取index为1的NavDestination页面的参数信息', JSON.stringify(this.pathStack.getParamByIndex(1)))
              console.log('获取全部名为MainPageTwo的NavDestination页面的参数信息', JSON.stringify(this.pathStack.getParamByName('MainPageTwo')))
              console.log('获取全部名为MainPageOne的NavDestination页面的位置索引', JSON.stringify(this.pathStack.getIndexByName('MainPageOne')))
              console.log('获取栈大小', JSON.stringify(this.pathStack.size()))
            })
      }
    }


  }
}
