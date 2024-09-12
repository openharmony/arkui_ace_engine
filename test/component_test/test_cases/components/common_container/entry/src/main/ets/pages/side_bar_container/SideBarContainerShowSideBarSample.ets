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
import sideBarContainerShowSideBarTest from '../MyTest/SideBarContainerShowSideBarTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SideBarContainerShowSideBarSample {
  @State showSideBar: boolean = false

  aboutToAppear(): void {
    loadComponentTestEntry(sideBarContainerShowSideBarTest)
  }

  build() {
    Column() {
      Row() {
        SideBarContainer() {
          Column() {
            Text('SideBar').fontSize(8)
          }
          .backgroundColor(Color.Green)
          .width(20)

          Column() {
            Text('SideBarContainer content text1').fontSize(15)
            Text('SideBarContainer content text2').fontSize(15)
          }
        }
        .id('sideBarContainerShowSideBar1')
        .showSideBar(this.showSideBar)
      }
      .height('50%')

      Button('SideBarContainerShowSideBar').onClick(() => {
        this.showSideBar = !this.showSideBar
      })
    }
  }
}