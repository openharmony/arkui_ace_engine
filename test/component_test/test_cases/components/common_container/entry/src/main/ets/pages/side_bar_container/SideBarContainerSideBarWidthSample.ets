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
import sideBarContainerSideBarWidthTest from '../MyTest/SideBarContainerSideBarWidthTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SideBarContainerSideBarWidthSample {
  @State sideBarWidth: number | string = 40

  aboutToAppear(): void {
    loadComponentTestEntry(sideBarContainerSideBarWidthTest)
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
          .id('sideBarContainerSideBarWidth1')
          .showSideBar(true)
          .sideBarWidth(-10)
        }
        .borderWidth(1)
        .width('30%')

        Column() {
          SideBarContainer() {
            Column() {
              Text('SideBar').fontSize(8)
            }
            .backgroundColor(Color.Green)
            .width('100px')

            Column() {
              Text('SideBarContainer content text1').fontSize(15)
              Text('SideBarContainer content text2').fontSize(15)
            }
          }
          .id('sideBarContainerSideBarWidth2')
          .showSideBar(true)
          .sideBarWidth($r('app.string.SideBarContainer_size'))
        }
        .borderWidth(1)
        .width('30%')

        Column() {
          SideBarContainer() {
            Column() {
              Text('SideBar').fontSize(8)
            }
            .backgroundColor(Color.Green)
            .width('20vp')

            Column() {
              Text('SideBarContainer content text1').fontSize(15)
              Text('SideBarContainer content text2').fontSize(15)
            }
          }
          .id('sideBarContainerSideBarWidth3')
          .showSideBar(true)
        }
        .borderWidth(1)
        .width('30%')
      }
      .width('100%')
      .height('30%')

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
          .id('sideBarContainerSideBarWidth4')
          .showSideBar(true)
          .sideBarWidth(this.sideBarWidth)
        }
        .borderWidth(1)
        .width('30%')

        Button('SideBarContainerSideBarWidth').onClick(() => {
          this.sideBarWidth = '40px'
        })
      }
      .width('100%')
      .height('30%')
    }
  }
}