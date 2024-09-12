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
import sideBarContainerMaxSideBarWidthTest from '../MyTest/SideBarContainerMaxSideBarWidthTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SideBarContainerMaxSideBarWidthSample {
  @State sideBarContainerMaxSideBarWidth: number | string = -10

  aboutToAppear(): void {
    loadComponentTestEntry(sideBarContainerMaxSideBarWidthTest)
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
          .id('sideBarContainerMaxSideBarWidth1')
          .showSideBar(true)
          .sideBarWidth(100)
          .maxSideBarWidth(50)
        }
        .borderWidth(1)
        .width('30%')

        Column() {
          SideBarContainer() {
            Column() {
              Text('SideBar').fontSize(8)
            }
            .constraintSize({ maxWidth: 20 })
            .backgroundColor(Color.Green)

            Column() {
              Text('SideBarContainer content text1').fontSize(15)
              Text('SideBarContainer content text2').fontSize(15)
            }
          }
          .id('sideBarContainerMaxSideBarWidth2')
          .showSideBar(true)
          .sideBarWidth(100)
          .maxSideBarWidth(50)
        }
        .borderWidth(1)
        .width('30%')

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
          .id('sideBarContainerMaxSideBarWidth3')
          .showSideBar(true)
          .sideBarWidth('100px')
          .maxSideBarWidth($r('app.string.SideBarContainer_size'))
        }
        .borderWidth(1)
        .width('30%')
      }
      .width('100%')
      .height('20%')

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
          .id('sideBarContainerMaxSideBarWidth4')
          .width(50)
          .showSideBar(true)
          .sideBarWidth(100)
          .maxSideBarWidth(200)
        }
        .borderWidth(1)
        .width('50%')

        Column() {
          SideBarContainer() {
            Column() {
              Text('SideBar').fontSize(8)
            }
            .constraintSize({ maxWidth: '100px' })
            .backgroundColor(Color.Green)

            Column() {
              Text('SideBarContainer content text1').fontSize(15)
              Text('SideBarContainer content text2').fontSize(15)
            }
          }
          .id('sideBarContainerMaxSideBarWidth5')
          .showSideBar(true)
          .width('400px')
          .sideBarWidth('300px')
          .maxSideBarWidth('200px')
        }
        .borderWidth(1)
        .width('50%')
      }
      .width('100%')
      .height('20%')

      Row() {
        Column() {
          SideBarContainer() {
            Column() {
              Text('SideBar').fontSize(8)
            }
            .constraintSize({ maxWidth: '300px' })
            .backgroundColor(Color.Green)

            Column() {
              Text('SideBarContainer content text1').fontSize(15)
              Text('SideBarContainer content text2').fontSize(15)
            }
          }
          .id('sideBarContainerMaxSideBarWidth6')
          .showSideBar(true)
          .sideBarWidth('320vp')
        }
        .borderWidth(1)
        .width('50%')
      }
      .width('100%')
      .height('20%')

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
          .id('sideBarContainerMaxSideBarWidth7')
          .showSideBar(true)
          .sideBarWidth('300vp')
          .maxSideBarWidth(this.sideBarContainerMaxSideBarWidth)
        }
        .borderWidth(1)
        .width('50%')

        Button('SideBarContainerMaxSideBarWidth').onClick(() => {
          this.sideBarContainerMaxSideBarWidth = '50px'
        })
      }
      .width('100%')
      .height('20%')
    }
  }
}