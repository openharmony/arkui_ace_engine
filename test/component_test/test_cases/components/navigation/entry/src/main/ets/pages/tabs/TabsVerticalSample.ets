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
import tabsVerticalTest from '../MyTest/TabsVerticalTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct TabsVerticalSample {
  private controller: TabsController = new TabsController()
  @State vertical: boolean = true

  aboutToAppear(): void {
    loadComponentTestEntry(tabsVerticalTest)
  }

  build() {
    Column() {
      Tabs({ controller: this.controller }) {
        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Pink)
        }.tabBar('pink').width('50%').height('50%')

        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Yellow)
        }.tabBar('yellow').width('50%').height('50%')

        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Blue)
        }.tabBar('blue').width('50%').height('50%')

        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Green)
        }.tabBar('green').width('50%').height('50%')

        TabContent() {
          Column().width('100%').height('100%').backgroundColor(Color.Red)
        }.tabBar('red').width('50%').height('50%')
      }
      .barWidth(400)
      .barHeight(400)
      .vertical(this.vertical)
      .height('80%')
      .id('tabsVertical')

      Button('TabsVertical')
        .onClick(() => {
          this.vertical = !this.vertical
        })
    }
  }
}