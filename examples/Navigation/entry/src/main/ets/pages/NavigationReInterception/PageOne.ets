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
class TmpClass{
  count:number=10
}
@Entry
@Component
export struct PageOneTmp {
  pageInfos: NavPathStack = new NavPathStack();
  @State isChange: boolean = false;

  build() {
    NavDestination() {
      Column() {
        Text(`${this.isChange ? 'PushPathByName' : 'pushDestinationByName'}`)
        Button('changePush', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(()=>{
            this.isChange = !this.isChange;
          })
        Button('pushPageTwo', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            let tmp = new TmpClass()
            if (this.isChange) {
              this.pageInfos.pushPath({name: 'pageTwo', param: tmp}) //将name指定的NavDestination页面信息入栈，传递的数据为param
            } else {
              this.pageInfos.pushDestinationByName('pageTwo', null);
            }
          })
        NavRouter({name: 'pageTwo'}) {
          Button('pushPageTwoByNavRouter')
        }
        Button('pageThree', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            let tmp = new TmpClass()
            this.pageInfos.pushPathByName('pageThree', tmp) //将name指定的NavDestination页面信息入栈，传递的数据为param
          })

        Button('Auto', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            AppStorage.setOrCreate('mode', NavigationMode.Auto);
          })
        Button('Split', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            AppStorage.setOrCreate('mode', NavigationMode.Split);
          })
        Button('Stack', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            AppStorage.setOrCreate('mode', NavigationMode.Stack);
          })
        Button(`remove start page`, { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            this.pageInfos.setInterception({
              willShow: (from: NavDestinationContext| "navBar", to: NavDestinationContext| "navBar", operation: NavigationOperation, isAnimated: boolean)=>{
                if (typeof from !== "string") {
                  this.pageInfos.removeByName(from.pathInfo.name);
                }
              }
            })
          })
      }.width('100%').height('100%')
    }.title('pageOne')
    .onReady((context: NavDestinationContext) => {
      this.pageInfos = context.pathStack;
    })
  }
}