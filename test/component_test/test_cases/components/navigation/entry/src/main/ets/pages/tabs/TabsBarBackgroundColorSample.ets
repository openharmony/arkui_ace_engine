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
import tabsBarBackgroundColorTest from '../MyTest/TabsBarBackgroundColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct TabsBarBackgroundColorSample {
  private controller: TabsController = new TabsController()
  @State groundColor: ResourceColor = 0xf1f3f5

  aboutToAppear(): void {
    loadComponentTestEntry(tabsBarBackgroundColorTest)
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
      }.id('tabsBarBackgroundColor')
      .vertical(false)
      .height('60%')
      .barBackgroundColor(this.groundColor)

      Button('TabsBarBackgroundColor1')
        .onClick(() => {
          this.groundColor = Color.Orange
        })
      Button('TabsBarBackgroundColor2')
        .onClick(() => {
          this.groundColor = '#FFF000'
        })
      Button('TabsBarBackgroundColor3')
        .onClick(() => {
          this.groundColor = $r('app.color.tabs_color')
        })
    }
  }
}