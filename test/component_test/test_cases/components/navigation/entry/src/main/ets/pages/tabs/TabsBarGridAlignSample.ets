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
import tabsBarGridAlignTest from '../MyTest/TabsBarGridAlignTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct TabsBarGridAlignSample {
  private controller: TabsController = new TabsController()
  @State columnOptions: BarGridColumnOptions = { sm: 2, margin: '10px', gutter: '10px' }
  @State columnHeight: string = '500vp'

  aboutToAppear(): void {
    loadComponentTestEntry(tabsBarGridAlignTest)
  }

  build() {
    Column() {
      Button('TabsBarGridAlign1')
        .onClick(() => {
          this.columnHeight = '600vp'
          this.columnOptions = { md: 2, margin: '10fp', gutter: '10fp' }
        })
      Button('TabsBarGridAlign2')
        .onClick(() => {
          this.columnHeight = '840vp'
          this.columnOptions = { lg: 0, margin: '5lpx', gutter: '5lpx' }
        })
      Tabs({ barPosition: BarPosition.Start, controller: this.controller }) {
        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Pink)
        }.tabBar(BottomTabBarStyle.of($r("sys.media.ohos_app_icon"), "Pink"))

        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Green)
        }.tabBar(BottomTabBarStyle.of($r("sys.media.ohos_app_icon"), "Green"))

        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Blue)
        }.tabBar(BottomTabBarStyle.of($r("sys.media.ohos_app_icon"), "Blue"))
      }.id('tabsBarGridAlign')
      .height(this.columnHeight)
      .barGridAlign(this.columnOptions)
    }
  }
}