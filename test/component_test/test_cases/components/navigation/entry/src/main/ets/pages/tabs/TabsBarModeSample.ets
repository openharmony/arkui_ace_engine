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
import tabsBarModeTest from '../MyTest/TabsBarModeTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct TabsBarModeSample {
  private controller: TabsController = new TabsController()
  @State scrollMargin: Dimension = '10px'
  @State layoutStyle: LayoutStyle = LayoutStyle.ALWAYS_CENTER

  aboutToAppear(): void {
    loadComponentTestEntry(tabsBarModeTest)
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
      }.id('tabsBarMode1')
      .height('40%')
      .backgroundColor(0xf1f3f5)
      .barMode(BarMode.Fixed)

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
      }.id('tabsBarMode2')
      .height('40%')
      .backgroundColor(0xf1f3f5)
      .barMode(BarMode.Scrollable, { margin: this.scrollMargin, nonScrollableLayoutStyle: this.layoutStyle })

      Button('TabsBarMode1')
        .onClick(() => {
          this.scrollMargin = '10vp'
          this.layoutStyle = LayoutStyle.ALWAYS_AVERAGE_SPLIT
        })
      Button('TabsBarMode2')
        .onClick(() => {
          this.scrollMargin = '10fp'
          this.layoutStyle = LayoutStyle.SPACE_BETWEEN_OR_CENTER
        })
    }
  }
}