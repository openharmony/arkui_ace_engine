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
// 测试代码路径
import navRouterModeTest from '../MyTest/NavRouterModeTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct NavRouterModeSample {
  @State navRouter: NavRouteMode = NavRouteMode.PUSH

  aboutToAppear(): void {
    loadComponentTestEntry(navRouterModeTest)
  }

  build() {
    Column() {
      Navigation() {
        NavRouter() {
          Text(`navRouterModeText1`)
          NavDestination() {
            Text('navDestinationText1')
          }
        }.mode(NavRouteMode.PUSH_WITH_RECREATE)
        .id('navRouterMode1')

        NavRouter() {
          Text(`navRouterModeText2`)
          NavDestination() {
            Text('navDestinationText2')
          }
        }.mode(this.navRouter)
        .id('navRouterMode2')
      }.height('50%')

      Button('NavRouterMode1')
        .onClick(() => {
          this.navRouter = NavRouteMode.REPLACE
        })
    }

  }
}