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

// PageTwo.ets
import observer from '@ohos.arkui.observer';
import router from '@ohos.router';
import { pageThree } from './PageThree'


export class Pages {
  names: string = ""
  values: NavPathStack | null = null
}

@Builder
export function pageTwoTmpDialog(name: string, param: Object) {

  NavDestination() {
    CustomNode()
  }.title('pageTwo')
  .mode(NavDestinationMode.DIALOG)
  .id('navDestination')
  .onWillAppear(()=>{
    console.log("testTag pageTwo onWillAppear")
  })
  .onAppear(()=>{
    console.log("testTag pageTwo onAppear")
  })
  .onWillShow(()=>{
    console.log("testTag pageTwo onWillShow")
  })
  .onShown(()=>{
    console.log("testTag pageTwo onShown")
  })
  .onWillHide(()=>{
    console.log("testTag pageTwo onWillHide")
  })
  .onHidden(()=>{
    console.log("testTag pageTwo onHidden")
  })
  .onWillDisappear(()=>{
    console.log("testTag pageTwo onWillDisappear")
  })
  .onDisAppear(()=>{
    console.log("testTag pageTwo onDisAppear")
  })
}

@Component
export struct CustomNode {
  pathStack : NavPathStack = new NavPathStack()
  @Consume('pageInfos') pageInfos: NavPathStack;
  @State text1 : string = ""
  @State text2 : string = ""
  navDesUpdateCallback1(info: NavDestinationInfo) {
    console.log(`testTag navDesUpdateCallback1, info: ${JSON.stringify(info)}`);
  }
  navDestinationSwitchCallbackWithUIContext1(info: observer.NavDestinationSwitchInfo) {
    if (info) {
      if (info.context) {
        console.log(`testTag navDestinationSwitchCallbackWithUIContext1, info: \"from\":${typeof info.from === 'string' ? ('"' + info.from + '"') : JSON.stringify(info.from)},\"to\":${typeof info.to === 'string' ? ('"' + info.to + '"') : JSON.stringify(info.to)}`);
      }}

  }
  navDesInfo: observer.NavDestinationInfo | undefined
  aboutToAppear() {
    this.navDesInfo = this.queryNavDestinationInfo();
    console.log('get navDestinationInfo: ' + JSON.stringify(this.navDesInfo))
    this.getUIContext().getUIObserver().on('navDestinationSwitch', this.navDestinationSwitchCallbackWithUIContext1);
    this.getUIContext().getUIObserver().on('navDestinationUpdate', this.navDesUpdateCallback1);
    // query navigation info
    let navigationInfo : observer.NavigationInfo | undefined = this.queryNavigationInfo()
    console.log("==================================")
    console.log("page two navDestination aboutToappear")
    console.log("获取navigationInfo："+JSON.stringify(navigationInfo))
    if (navigationInfo !== undefined) {
      this.pathStack = navigationInfo.pathStack;
    }
  }

  @Builder
  PageMap(name: string) {
    if (name === 'pageThree') {
      pageThree()
    }
  }

  @Provide('secondPageInfos') secondPageInfos: NavPathStack = new NavPathStack()

  build() {
    Scroll(){
      Column() {
        Button('跳转到PageOne')
          .onClick(()=>{
            this.pathStack.pushPathByName('MainPageOne', 'MainPageOne')
          })
        Button('跳转到PageTwo')
          .onClick(()=>{
            this.pathStack.pushPathByName('MainPageTwo', 'MainPageTwo')
          })
        Button('pushPathThree')
          .onClick(()=>{
            this.pathStack.pushPathByName('MainPageThree7965', 'MainPageThree7965')
          })
        Button('跳转到PageSixNavRouter')
          .onClick(()=>{
            this.pathStack.pushPathByName('MainPageSix', 'MainPageSix')
          })
        Button('跳转到EmptyPage')
          .onClick(()=>{
            this.pathStack.pushPathByName('EmptyPage', 'EmptyPage')
          })
        Button('跳转到HarPageFour')
          .onClick(()=>{
            this.pathStack.pushPathByName('HarPageFour', 'HarPageFour')
          })
        Button('跳转到HspPageFive')
          .onClick(()=>{
            this.pathStack.pushPathByName('HspPageFive', 'HspPageFive')
          })
        Button('Router')
          .onClick(()=>{
            router.pushUrl({ url:'pages/NoId' })
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
            console.log('获取queryNavigationInfo-------------------')
            console.log('获取栈中所有NavDestination页面的名称', JSON.stringify(this.pathStack.getAllPathName()))
            console.log('获取index为0的NavDestination页面的参数信息', JSON.stringify(this.pathStack.getParamByIndex(0)))
            console.log('获取index为1的NavDestination页面的参数信息', JSON.stringify(this.pathStack.getParamByIndex(1)))
            console.log('获取全部名为MainPageOne的NavDestination页面的位置索引', JSON.stringify(this.pathStack.getIndexByName('MainPageOne')))
            console.log('获取全部名为MainPageTwo的NavDestination页面的参数信息', JSON.stringify(this.pathStack.getParamByName('MainPageTwo')))
            console.log('获取栈大小', JSON.stringify(this.pathStack.size()))
            console.log('获取完整信息', JSON.stringify(this.pathStack))
          })

        Text('pageInfos:' + '\r' + this.text2)
        Button('pageInfos', { stateEffect: true, type: ButtonType.Capsule })
          .width('40%')
          .height(30)
          .margin(10)
          .onClick(() => {
            this.text2 = '获取栈中所有NavDestination页面的名称:' + JSON.stringify(this.pageInfos.getAllPathName()) + '\r'
              + '获取index为1的NavDestination页面的参数信息:' + JSON.stringify(this.pageInfos.getParamByIndex(1)) +'\r'
              + '获取全部名为MainPageTwo的NavDestination页面的参数信息:' + JSON.stringify(this.pageInfos.getParamByName('MainPageTwo')) + '\r'
              + '获取全部名为MainPageOne的NavDestination页面的位置索引:' + JSON.stringify(this.pageInfos.getIndexByName('MainPageOne')) + '\r'
              + '获取栈大小:' +   JSON.stringify(this.pageInfos.size())
            console.log('获取pageInfos-------------------')
            console.log('获取栈中所有NavDestination页面的名称', JSON.stringify(this.pageInfos.getAllPathName()))
            console.log('获取index为0的NavDestination页面的参数信息', JSON.stringify(this.pageInfos.getParamByIndex(0)))
            console.log('获取index为1的NavDestination页面的参数信息', JSON.stringify(this.pageInfos.getParamByIndex(1)))
            console.log('获取全部名为MainPageOne的NavDestination页面的位置索引', JSON.stringify(this.pageInfos.getIndexByName('MainPageOne')))
            console.log('获取全部名为MainPageTwo的NavDestination页面的参数信息', JSON.stringify(this.pageInfos.getParamByName('MainPageTwo')))
            console.log('获取栈大小', JSON.stringify(this.pageInfos.size()))
            console.log('获取完整信息', JSON.stringify(this.pageInfos))
          })

        Navigation(this.secondPageInfos) {
          Column() {
            Button('pushPathThree', { stateEffect: true, type: ButtonType.Capsule })
              .width('80%')
              .height(40)
              .margin(20)
              .onClick(() => {
                this.secondPageInfos.pushPath({ name: 'pageThree', param: 'pageThree' }) //将name指定的NavDestination页面信息入栈
              })
            Button('pushPathOne', { stateEffect: true, type: ButtonType.Capsule })
              .width('80%')
              .height(40)
              .margin(20)
              .onClick(() => {
                this.secondPageInfos.pushPath({ name: 'MainPageOne', param: 'MainPageOne' }) //将name指定的NavDestination页面信息入栈
              })
          }
        }.title('SecondNavIndex')
        .navDestination(this.PageMap)
        .id('navigation2')
      }
    }.height(500)
  }
}
