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

@Entry
@Component
struct NavigationExample {
  build() {
    Column(){
      OtherNode()
      NavigationNode()
    }
  }
}

@Component
struct NavigationNode {
  @Provide('pageInfos') pageInfos: NavPathStack = new NavPathStack()

  build() {
    Navigation(this.pageInfos) {
      Column() {
        Button('pushPath', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            this.pageInfos.pushPath({ name: 'MainPageOne', param: 'MainPageOne' }) //将name指定的NavDestination页面信息入栈
          })
      }
    }.title('NavIndex')
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
    console.log("获取Navigation信息"+JSON.stringify(navigationInfo))
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
