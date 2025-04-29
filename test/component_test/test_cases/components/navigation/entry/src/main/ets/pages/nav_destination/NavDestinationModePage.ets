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
import { NavDestinationModeSample } from '../MyTest/NavDestinationModeSample'
import navDestinationModeTest from '../MyTest/NavDestinationModeTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';

@Entry
@ComponentV2
struct NavDestinationModePage {
  @Provider('pageInfos') pageInfos: NavPathStack = new NavPathStack()

  aboutToAppear(): void {
    loadComponentTestEntry(navDestinationModeTest);
  }

  @Builder
  PageMap(name: string) {
    NavDestinationModeSample()
  }

  build() {
    Navigation(this.pageInfos) {
      Column() {
        Button('PushNavDestination', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            this.pageInfos.pushPath({ name: 'NavDestinationMode' })
          })
      }
    }.title('NavIndex').navDestination(this.PageMap)
  }
}