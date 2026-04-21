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

// PageOne.ets
import observer from '@ohos.arkui.observer'
// import { uiObserver as observer } from '@kit.ArkUI';
// import { uiObserver } from '@kit.ArkUI'

@Builder
export function PageOneTmp(name: string, param: Object) {
  PageOne()
}

@Component
export struct PageOne {
  @Consume('pageInfos') pageInfos: NavPathStack;
  name : ResourceStr = ""

  @State text1 : string = ""
  @State text2 : string = ""

  pathStack : NavPathStack = new NavPathStack()
  //navDesInfo: uiObserver.NavDestinationInfo | undefined;
  build() {
    NavDestination() {
      Scroll(){
        Column() {
          Column() {

            // Button('查询NavDestinationInfo', { stateEffect: true, type: ButtonType.Capsule })
            //   .width('40%')
            //   .height(30)
            //   .margin(10)
            //   .onClick(() => {
            //     this.navDesInfo = this.queryNavDestinationInfo();
            //     console.log('testTag NavDestinationInfo_PageOne: ' + JSON.stringify(this.navDesInfo))
            //   })
            Button('pushPath', { stateEffect: true, type: ButtonType.Capsule })
              .width('40%')
              .height(30)
              .margin(10)
              .onClick(() => {
                this.pathStack.pushPath({name: 'MainPageTwo', param: 'MainPageTwo'})
              })
            Button('pushNavdestination', { stateEffect: true, type: ButtonType.Capsule })
              .width('40%')
              .height(30)
              .margin(10)
              .onClick(() => {
                let returnvalue = this.pathStack.pushDestination({name: 'MainPageTwo', param: 'MainPageTwo'})
                console.log('pushNavdestination returns' + JSON.stringify(returnvalue))
              })
            Button('pushDestinationByName', { stateEffect: true, type: ButtonType.Capsule })
              .width('40%')
              .height(30)
              .margin(10)
              .onClick(() => {
                let returnvalue = this.pathStack.pushDestinationByName('MainPageTwo', 'MainPageTwo')
                console.log('pushNavdestinationByName returns' + JSON.stringify(returnvalue))
              })
            Button('replacePath', { stateEffect: true, type: ButtonType.Capsule })
              .width('40%')
              .height(30)
              .margin(10)
              .onClick(() => {
                this.pathStack.replacePath({name: 'MainPageTwo', param: 'MainPageTwo'})
              })
            Button('replacePathByName', { stateEffect: true, type: ButtonType.Capsule })
              .width('40%')
              .height(30)
              .margin(10)
              .onClick(() => {
                this.pathStack.replacePathByName('MainPageTwo', 'MainPageTwo')
              })
            Button('removeByIndexes', { stateEffect: true, type: ButtonType.Capsule })
              .width('40%')
              .height(30)
              .margin(10)
              .onClick(() => {
                this.pathStack.removeByIndexes([0])
              })
            Button('removeByName', { stateEffect: true, type: ButtonType.Capsule })
              .width('40%')
              .height(30)
              .margin(10)
              .onClick(() => {
                this.pathStack.removeByName("MainPageOne")
              })
            Button('pop', { stateEffect: true, type: ButtonType.Capsule })
              .width('40%')
              .height(30)
              .margin(10)
              .onClick(() => {
                this.pathStack.pop()
              })
          }
          Column() {
            Button('pushPathByName', { stateEffect: true, type: ButtonType.Capsule })
              .width('40%')
              .height(30)
              .margin(10)
              .onClick(() => {
                this.pathStack.pushPathByName('MainPageTwo', 'MainPageTwo') //将name指定的NavDestination页面信息入栈，传递的数据为param
              })
            Button('popToname', { stateEffect: true, type: ButtonType.Capsule })
              .width('40%')
              .height(30)
              .margin(10)
              .onClick(() => {
                this.pathStack.popToName('MainPageTwo') //回退路由栈到第一个名为name的NavDestination页面
                console.log('popToName' + JSON.stringify(this.pathStack), '返回值' + JSON.stringify(this.pathStack.popToName('MainPageTwo')))
              })
            Button('popToIndex', { stateEffect: true, type: ButtonType.Capsule })
              .width('40%')
              .height(30)
              .margin(10)
              .onClick(() => {
                this.pathStack.popToIndex(1) // 回退路由栈到index指定的NavDestination页面
                console.log('popToIndex' + JSON.stringify(this.pathStack))
              })
            Button('moveToTop', { stateEffect: true, type: ButtonType.Capsule })
              .width('40%')
              .height(30)
              .margin(10)
              .onClick(() => {
                this.pathStack.moveToTop('MainPageTwo') // 将第一个名为name的NavDestination页面移到栈顶
                console.log('moveToTop' + JSON.stringify(this.pathStack), '返回值' + JSON.stringify(this.pathStack.moveToTop('MainPageTwo')))
              })
            Button('moveIndexToTop', { stateEffect: true, type: ButtonType.Capsule })
              .width('40%')
              .height(30)
              .margin(10)
              .onClick(() => {
                this.pathStack.moveIndexToTop(1) // 将index指定的NavDestination页面移到栈顶
                console.log('moveIndexToTop' + JSON.stringify(this.pathStack))
              })
            Button('clear', { stateEffect: true, type: ButtonType.Capsule })
              .width('40%')
              .height(30)
              .margin(10)
              .onClick(() => {
                this.pathStack.clear() //清除栈中所有页面
              })
            Button('getParent', { stateEffect: true, type: ButtonType.Capsule })
              .width('40%')
              .height(30)
              .margin(10)
              .onClick(() => {
                let info = this.pathStack.getParent() //清除栈中所有页面
                console.log(JSON.stringify(info));
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
          }
        }
      }.height(500)


    }.title('pageOne')
    .onBackPressed(() => {
      const popDestinationInfo = this.pathStack.pop() // 弹出路由栈栈顶元素
      console.log('pop' + '返回值' + JSON.stringify(popDestinationInfo))
      return true
    })
    .onShown(() => {
      console.log("==================================")
      console.log("testTag pageOne onShown")
      let navigationInfo : observer.NavigationInfo | undefined = this.queryNavigationInfo()
      console.log("onShown 获取navigationInfo："+JSON.stringify(navigationInfo))
      if (navigationInfo !== undefined) {
        this.pathStack = navigationInfo.pathStack;
      }
    })
    .onWillAppear(()=>{
      console.log("testTag pageOne onWillAppear")
    })
    .onAppear(()=>{
      console.log("testTag pageOne onAppear")
    })
    .onWillShow(()=>{
      console.log("testTag pageOne onWillShow")
    })
    .onWillHide(()=>{
      console.log("testTag pageOne onWillHide")
    })
    .onHidden(()=>{
      console.log("testTag pageOne onHidden")
    })
    .onWillDisappear(()=>{
      console.log("testTag pageOne onWillDisappear")
    })
    .onDisAppear(()=>{
      console.log("testTag pageOne onDisAppear")
    })
  }
}

