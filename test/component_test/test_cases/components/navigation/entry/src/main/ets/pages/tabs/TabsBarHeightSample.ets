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
import tabsBarHeightTest from '../MyTest/TabsBarHeightTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct TabsBarHeightSample {
  private controller: TabsController = new TabsController()
  @State barHeight: Length = 100

  aboutToAppear(): void {
    loadComponentTestEntry(tabsBarHeightTest)
  }

  build() {
    Column() {
      Tabs({ barPosition: BarPosition.End, controller: this.controller }) {
        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Pink)
        }.tabBar('pink')

        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Green)
        }.tabBar('green')

        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Blue)
        }.tabBar('blue')

        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Red)
        }.tabBar('Red')

        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Orange)
        }.tabBar('Orange')
      }
      .id('tabsBarHeight')
      .vertical(false)
      .barHeight(this.barHeight)
      .height('60%')

      Button('TabsBarHeight1')
        .onClick(() => {
          this.barHeight = '50'
        })
      Button('TabsBarHeight2')
        .onClick(() => {
          this.barHeight = $r("app.string.tabs_resource1")
        })
      Button('TabsBarHeight3')
        .onClick(() => {
          this.barHeight = -1
        })
    }
  }
}