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
import sideBarContainerMinContentWidthTest from '../MyTest/SideBarContainerMinContentWidthTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SideBarContainerMinContentWidthSample {
  index: number = 0
  sideBarContainerMinContentWidthArr: Dimension[] =
    ['100px', '100vp', '100fp', '100lpx', '30%', $r('app.string.SideBarContainer_size')]
  @State sideBarContainerMinContentWidth: Dimension = this.sideBarContainerMinContentWidthArr[this.index]

  aboutToAppear(): void {
    loadComponentTestEntry(sideBarContainerMinContentWidthTest)
  }

  build() {
    Column() {
      Row() {
        Column() {
          SideBarContainer(SideBarContainerType.Embed) {
            Column() {
              Text('SideBar').fontSize(8)
            }
            .backgroundColor(Color.Green)

            Column() {
              Text('SideBarContainer content text1').fontSize(15)
              Text('SideBarContainer content text2').fontSize(15)
            }
          }
          .id('sideBarContainerMinContentWidth1')
          .showSideBar(true)
          .width('500vp')
          .minContentWidth(-10)
          .sideBarWidth('100vp')
        }
        .borderWidth(1)
      }
      .width('50%')
      .height('20%')

      Row() {
        Column() {
          SideBarContainer(SideBarContainerType.Embed) {
            Column() {
              Text('SideBar').fontSize(8)
            }
            .backgroundColor(Color.Green)

            Column() {
              Text('SideBarContainer content text1').fontSize(15)
              Text('SideBarContainer content text2').fontSize(15)
            }
          }
          .id('sideBarContainerMinContentWidth2')
          .showSideBar(true)
          .width('200vp')
          .sideBarWidth('100vp')
          .borderWidth(1)
        }
        .width('20%')

        Column() {
          SideBarContainer(SideBarContainerType.Embed) {
            Column() {
              Text('SideBar').fontSize(8)
            }
            .backgroundColor(Color.Green)

            Column() {
              Text('SideBarContainer content text1').fontSize(15)
              Text('SideBarContainer content text2').fontSize(15)
            }
          }
          .id('sideBarContainerMinContentWidth3')
          .showSideBar(true)
          .width('400vp')
          .sideBarWidth('380vp')
          .minSideBarWidth('370vp')
          .borderWidth(1)
        }
      }
      .width('50%')
      .height('10%')

      Row() {
        Column() {
          SideBarContainer(SideBarContainerType.Embed) {
            Column() {
              Text('SideBar').fontSize(8)
            }
            .backgroundColor(Color.Green)

            Column() {
              Text('SideBarContainer content text1').fontSize(15)
              Text('SideBarContainer content text2').fontSize(15)
            }
          }
          .id('sideBarContainerMinContentWidth4')
          .showSideBar(true)
          .width('400vp')
          .sideBarWidth('380vp')
          .maxSideBarWidth('350vp')
          .borderWidth(1)
        }

        Column() {
          SideBarContainer(SideBarContainerType.Embed) {
            Column() {
              Text('SideBar').fontSize(8)
            }
            .backgroundColor(Color.Green)

            Column() {
              Text('SideBarContainer content text1').fontSize(15)
              Text('SideBarContainer content text2').fontSize(15)
            }
          }
          .id('sideBarContainerMinContentWidth5')
          .showSideBar(true)
          .width('500px')
          .minContentWidth('300px')
          .sideBarWidth('400px')
          .maxSideBarWidth('400px')
        }
      }
      .width('50%')
      .height('20%')

      Row() {
        Column() {
          SideBarContainer(SideBarContainerType.Embed) {
            Column() {
              Text('SideBar').fontSize(8)
            }
            .backgroundColor(Color.Green)

            Column() {
              Text('SideBarContainer content text1').fontSize(15)
              Text('SideBarContainer content text2').fontSize(15)
            }
          }
          .id('sideBarContainerMinContentWidth6')
          .borderWidth(1)
          .showSideBar(true)
          .autoHide(false)
          .width('500px')
          .sideBarWidth('200px')
          .minSideBarWidth('100px')
          .minContentWidth('100px')
        }

        Column() {
          SideBarContainer(SideBarContainerType.Embed) {
            Column() {
              Text('SideBar').fontSize(8)
            }
            .backgroundColor(Color.Green)

            Column() {
              Text('SideBarContainer content text1').fontSize(15)
              Text('SideBarContainer content text2').fontSize(15)
            }
          }
          .id('sideBarContainerMinContentWidth7')
          .borderWidth(1)
          .showSideBar(true)
          .autoHide(true)
          .width('500px')
          .sideBarWidth('200px')
          .minSideBarWidth('100px')
          .minContentWidth('100px')
        }
      }
      .width('50%')
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
          .id('sideBarContainerMinContentWidth8')
          .showSideBar(true)
          .minContentWidth(this.sideBarContainerMinContentWidth)
        }
        .borderWidth(1)
        .width('30%')

        Button('SideBarContainerMinContentWidth').onClick(() => {
          ++this.index
          this.sideBarContainerMinContentWidth = this.sideBarContainerMinContentWidthArr[this.index % 7]
        })
      }
      .width('50%')
      .height('20%')
    }

  }
}