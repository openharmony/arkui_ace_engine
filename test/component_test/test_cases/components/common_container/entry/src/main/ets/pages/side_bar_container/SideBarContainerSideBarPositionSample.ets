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
import sideBarContainerSideBarPositionTest from '../MyTest/SideBarContainerSideBarPositionTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SideBarContainerSideBarPositionSample {
  @State sideBarContainerSideBarPosition: SideBarPosition = SideBarPosition.Start

  aboutToAppear(): void {
    loadComponentTestEntry(sideBarContainerSideBarPositionTest)
  }

  build() {
    Column() {
      Row() {
        Column() {
          SideBarContainer() {
            Column() {
              Text('SideBar').fontSize(8)
            }
            .backgroundColor(Color.Green)

            Column() {
              Text('SideBarContainer content text1').fontSize(15)
              Text('SideBarContainer content text2').fontSize(15)
            }
          }
          .id('sideBarContainerSideBarPosition1')
          .showSideBar(true)
          .sideBarWidth('50px')
          .sideBarPosition(this.sideBarContainerSideBarPosition)
        }
        .borderWidth(1)
        .width('50%')

        Button('SideBarContainerSideBarPosition').onClick(() => {
          this.sideBarContainerSideBarPosition = SideBarPosition.End
        })
      }
      .width('100%')
      .height('30%')
    }
  }
}