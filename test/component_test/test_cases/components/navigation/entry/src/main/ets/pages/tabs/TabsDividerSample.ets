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
import tabsDividerTest from '../MyTest/TabsDividerTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct TabsDividerSample {
  private controller: TabsController = new TabsController()
  @State dividerColor: ResourceColor = '#FFF000'
  @State strokeWidth: Length = 2
  @State startMargin: Length = 0
  @State endMargin: Length = 0

  aboutToAppear(): void {
    loadComponentTestEntry(tabsDividerTest)
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
          Column().width('100%').height('100%').backgroundColor(Color.Red)
        }.tabBar('Red')

        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Orange)
        }.tabBar('Orange')
      }
      .id('tabsDivider1')
      .vertical(false)
      .height('40%')
      .backgroundColor(0xf1f3f5)
      .divider({
        strokeWidth: this.strokeWidth,
        color: this.dividerColor,
        startMargin: this.startMargin,
        endMargin: this.endMargin
      })

      Button('TabsDivider1')
        .onClick(() => {
          this.dividerColor = 0xff60ff
          this.strokeWidth = '50px'
          this.startMargin = '500px'
          this.endMargin = '500px'
        })
      Button('TabsDivider2')
        .onClick(() => {
          this.dividerColor = Color.Orange
          this.strokeWidth = $r('app.string.tabs_resource2')
          this.startMargin = $r('app.string.tabs_resource2')
          this.endMargin = $r('app.string.tabs_resource2')
        })
      Button('TabsDivider3')
        .onClick(() => {
          this.dividerColor = $r('app.color.tabs_color')
        })
      Tabs({ barPosition: BarPosition.End, controller: this.controller }) {
        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Pink)
        }.tabBar('pink')

        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Red)
        }.tabBar('Red')

        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Orange)
        }.tabBar('Orange')
      }
      .id('tabsDivider2')
      .height('40%')
      .divider(null)
    }
  }
}