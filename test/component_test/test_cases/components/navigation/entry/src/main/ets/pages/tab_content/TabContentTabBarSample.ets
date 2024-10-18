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
import tabContentTabBarTest from '../MyTest/TabContentTabBarTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct TabContentTabBarSample {
  private controller: TabsController = new TabsController()
  @State text1: ResourceStr = 'tabBar1'
  @State text2: ResourceStr = $r("app.string.tabs_string")
  @State text3: ResourceStr = 'tabBar3'
  @State icon1: ResourceStr = '../../../resources/base/media/Tab.jpg'
  @State icon2: ResourceStr = $r('sys.media.ohos_app_icon')

  aboutToAppear(): void {
    loadComponentTestEntry(tabContentTabBarTest)
  }

  @Builder
  tabBuilder(name: string) {
    Column() {
      Text(name)
    }.width('100%')
  }

  build() {
    Column() {
      Button('TabContentTabBar1')
        .onClick(() => {
          this.text1 = $r("app.string.tabs_string")
          this.icon1 = $r('sys.media.ohos_app_icon')
        }).margin(5)
      Button('TabContentTabBar2')
        .onClick(() => {
          this.icon2 = 'pages/tabContent/Tab.jpg'
          this.text2 = 'tabBar2'
        }).margin(5)
      Button('TabContentTabBar3')
        .onClick(() => {
          this.text3 = $r("app.string.tabs_string")
        }).margin(5)
      Tabs({ barPosition: BarPosition.Start, controller: this.controller }) {
        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Pink)
        }.tabBar('Pink').id('tabContentTabBar1')

        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Brown)
        }.tabBar($r("app.string.tabs_string")).id('tabContentTabBar2')

        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Green)
        }.tabBar(this.tabBuilder('blue')).id('tabContentTabBar3')

        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Black)
        }.tabBar({ icon: this.icon1, text: this.text1 }).id('tabContentTabBar4')

        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Red)
        }.tabBar(new SubTabBarStyle(this.text3)).id('tabContentTabBar5')

        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Yellow)
        }.tabBar(new BottomTabBarStyle(this.icon2, this.text2)).id('tabContentTabBar6')
      }
      .vertical(false)
      .height('90%')
      .backgroundColor(Color.Grey)
    }
    .width('100%')
    .height(500)
    .padding('24vp')
  }
}