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

// PageThree.ets
import observer from '@ohos.arkui.observer';

@Builder
export function pageThree() {
  CustomNode()

}



@Component
export struct CustomNode {
  // @Consume('secondPageInfos') pageInfos: NavPathStack;
  private pageInfos: NavPathStack | null = null;
   pathStack : NavPathStack = new NavPathStack()
  @State text1 : string = ""
  @State text2 : string = ""
  aboutToAppear() {
    // query navigation info
    let navigationInfo : observer.NavigationInfo | undefined = this.queryNavigationInfo()
    console.log("==================================")
    console.log("page three navDestination aboutToappear")
    console.log("获取NavigationInfo："+JSON.stringify(navigationInfo))
    if (navigationInfo !== undefined) {
      this.pathStack = navigationInfo.pathStack;
    }
  }

  build() {
    NavDestination() {
      Scroll(){
        Column() {
          Button('跳转到PageThree')
            .width('80%')
            .height(30)
            .margin(10)
            .onClick(()=>{
              this.pathStack.pushPathByName('pageThree', 'pageThree')
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
              this.text2 = '获取栈中所有NavDestination页面的名称:' + JSON.stringify(this.pageInfos?.getAllPathName()) + '\r'
                + '获取index为1的NavDestination页面的参数信息:' + JSON.stringify(this.pageInfos?.getParamByIndex(1)) +'\r'
                + '获取全部名为MainPageTwo的NavDestination页面的参数信息:' + JSON.stringify(this.pageInfos?.getParamByName('MainPageTwo')) + '\r'
                + '获取全部名为MainPageOne的NavDestination页面的位置索引:' + JSON.stringify(this.pageInfos?.getIndexByName('MainPageOne')) + '\r'
                + '获取栈大小:' +   JSON.stringify(this.pageInfos?.size())
              console.log('获取pageInfos-------------------')
              console.log('获取栈中所有NavDestination页面的名称', JSON.stringify(this.pageInfos?.getAllPathName()))
              console.log('获取index为0的NavDestination页面的参数信息', JSON.stringify(this.pageInfos?.getParamByIndex(0)))
              console.log('获取index为1的NavDestination页面的参数信息', JSON.stringify(this.pageInfos?.getParamByIndex(1)))
              console.log('获取全部名为MainPageOne的NavDestination页面的位置索引', JSON.stringify(this.pageInfos?.getIndexByName('MainPageOne')))
              console.log('获取全部名为MainPageTwo的NavDestination页面的参数信息', JSON.stringify(this.pageInfos?.getParamByName('MainPageTwo')))
              console.log('获取栈大小', JSON.stringify(this.pageInfos?.size()))
              console.log('获取完整信息', JSON.stringify(this.pageInfos))
            })
        }
      }.height(500)

    }.title('pageThree')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .id('navDestination2')
    .onReady((ctx: NavDestinationContext) => {
      // 在NavDestination中能够拿到传来的NavPathInfo和当前所处的NavPathStack
      try {

        this.pageInfos=ctx.pathStack

      } catch (e) {
        console.log(`testTag onReady catch exception: ${JSON.stringify(e)}`)
      }
    })
    .onShown(() => {
      console.log("==================================")
      console.log("page one navDestination OnShown")
      let navigationInfo : observer.NavigationInfo | undefined = this.queryNavigationInfo()
      console.log("onShown 获取navigationInfo："+JSON.stringify(navigationInfo))
      if (navigationInfo !== undefined) {
        this.pathStack = navigationInfo.pathStack;
      }
    })
  }
}