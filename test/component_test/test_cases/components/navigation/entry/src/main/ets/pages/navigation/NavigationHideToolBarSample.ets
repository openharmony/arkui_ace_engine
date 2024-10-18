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
import navigationHideToolBarTest from '../MyTest/NavigationHideToolBarTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct NavigationHideToolBarSample {
  @State hideToolBar: boolean = true

  aboutToAppear(): void {
    loadComponentTestEntry(navigationHideToolBarTest)
  }

  build() {
    Column() {
      Navigation() {
      }
      .height(100)
      .width('100%')
      .margin(20)
      .title('title')
      .toolbarConfiguration([{ value: 'hello', icon: $r('sys.media.ohos_ic_public_drawer_open_filled') },
        { value: 'world', icon: $r('sys.media.ohos_ic_public_device_smartscreen') }])
      .hideToolBar(this.hideToolBar)
      .id('navigationHideToolBar')

      Button('NavigationHideToolBar')
        .onClick(() => {
          this.hideToolBar = false
        })
    }
  }
}