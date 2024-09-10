/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
//测试代码路径
import navigationNavDestinationTest from '../MyTest/NavigationNavDestinationTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import { PageOneTmp } from '../MyTest/PageOne'
import { Pages, pageTwoTmp } from '../MyTest/PageTwo'

@Entry
@Component
struct NavigationNavDestinationSample {
  aboutToAppear(): void {
    loadComponentTestEntry(navigationNavDestinationTest)
  }

  @Provide('pageInfos') pageInfos: NavPathStack = new NavPathStack()

  @Builder
  PageMap(name: string) {
    if (name === 'pageOne') {
      PageOneTmp()
    } else if (name === 'pageTwo') {
      pageTwoTmp({ names: name, values: this.pageInfos } as Pages)
    }
  }

  build() {
    Navigation(this.pageInfos) {
      Column() {
        Button('pageOne', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            this.pageInfos.pushPath({ name: 'pageOne' })
          })
      }
    }.title('NavIndex')
    .navDestination(this.PageMap)
    .id('navDestination')
  }
}