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
import sideBarContainerMinSideBarWidthTest from '../MyTest/SideBarContainerMinSideBarWidthTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SideBarContainerMinSideBarWidthSample {
  @State sideBarContainerMinSideBarWidth: number | string = -10

  aboutToAppear(): void {
    loadComponentTestEntry(sideBarContainerMinSideBarWidthTest)
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
            .width(20)

            Column() {
              Text('SideBarContainer content text1').fontSize(15)
              Text('SideBarContainer content text2').fontSize(15)
            }
          }
          .id('sideBarContainerMinSideBarWidth1')
          .showSideBar(true)
          .sideBarWidth(10)
          .minSideBarWidth(100)
        }
        .borderWidth(1)
        .width('30%')

        Column() {
          SideBarContainer() {
            Column() {
              Text('SideBar').fontSize(8)
            }
            .constraintSize({ minWidth: 100 })
            .backgroundColor(Color.Green)
            .width('30px')

            Column() {
              Text('SideBarContainer content text1').fontSize(15)
              Text('SideBarContainer content text2').fontSize(15)
            }
          }
          .id('sideBarContainerMinSideBarWidth2')
          .showSideBar(true)
          .sideBarWidth(10)
          .minSideBarWidth(50)
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
          .id('sideBarContainerMinSideBarWidth3')
          .showSideBar(true)
          .sideBarWidth('1px')
          .minSideBarWidth($r('app.string.SideBarContainer_size'))
        }
        .borderWidth(1)
        .width('30%')

      }.width('100%')
      .height('20%')

      Row() {
        Column() {
          SideBarContainer() {
            Column() {
              Text('SideBar').fontSize(8)
            }
            .backgroundColor(Color.Green)
            .width(100)

            Column() {
              Text('SideBarContainer content text1').fontSize(15)
              Text('SideBarContainer content text2').fontSize(15)
            }
          }
          .id('sideBarContainerMinSideBarWidth4')
          .showSideBar(true)
          .sideBarWidth(1)
          .minSideBarWidth(200)
        }
        .borderWidth(1)
        .width('30%')

        Column() {
          SideBarContainer() {
            Column() {
              Text('SideBar').fontSize(8)
            }
            .constraintSize({ minWidth: '50px' })
            .backgroundColor(Color.Green)
            .width('10vp')

            Column() {
              Text('SideBarContainer content text1').fontSize(15)
              Text('SideBarContainer content text2').fontSize(15)
            }
          }
          .id('sideBarContainerMinSideBarWidth5')
          .showSideBar(true)
          .sideBarWidth('1px')
          .minSideBarWidth('100px')
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
            .constraintSize({ minWidth: '50vp' })
            .backgroundColor(Color.Green)

            Column() {
              Text('SideBarContainer content text1').fontSize(15)
              Text('SideBarContainer content text2').fontSize(15)
            }
          }
          .id('sideBarContainerMinSideBarWidth6')
          .showSideBar(true)
          .sideBarWidth('10px')
        }
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
          .id('sideBarContainerMinSideBarWidth7')
          .showSideBar(true)
          .sideBarWidth('10px')
          .minSideBarWidth(this.sideBarContainerMinSideBarWidth)
        }
        .borderWidth(1)
        .width('50%')

        Button('SideBarContainerMinSideBarWidth').onClick(() => {
          this.sideBarContainerMinSideBarWidth = '50px'
        })
      }
      .borderWidth(1)
      .width('100%')
      .height('20%')
    }
  }
}