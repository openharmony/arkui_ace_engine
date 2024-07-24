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
import sideBarContainerDividerTest from '../MyTest/SideBarContainerDividerTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SideBarContainerDividerSample {
  index: number = 0
  sideBarContainerDividerArr: DividerStyle[] = [{
    strokeWidth: 5,
    color: Color.Red,
    startMargin: 10,
    endMargin: 10
  }, {
    strokeWidth: '5px',
    color: 0x0000ff,
    startMargin: '10px',
    endMargin: '10px'
  }]
  @State sideBarContainerDivider: DividerStyle = this.sideBarContainerDividerArr[this.index]

  aboutToAppear(): void {
    loadComponentTestEntry(sideBarContainerDividerTest)
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
          .id('sideBarContainerDivider1')
          .showSideBar(true)
          .sideBarWidth('50px')
          .divider({
            strokeWidth: $r('app.string.pixel_size'),
            color: 'rgb(255, 0, 0)',
            startMargin: $r('app.string.pixel_size'),
            endMargin: $r('app.string.pixel_size')
          })
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
          .id('sideBarContainerDivider2')
          .showSideBar(true)
          .sideBarWidth('50px')
          .divider({
            strokeWidth: $r('app.string.pixel_size'),
            color: 'rgb(255, 0, 0, 0.5)',
            startMargin: $r('app.string.pixel_size'),
            endMargin: $r('app.string.pixel_size')
          })
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
          .id('sideBarContainerDivider3')
          .showSideBar(true)
          .sideBarWidth('50px')
          .divider({
            strokeWidth: $r('app.string.pixel_size'),
            color: $r('sys.color.ohos_fa_palette1'),
            startMargin: $r('app.string.pixel_size'),
            endMargin: $r('app.string.pixel_size')
          })
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
          .id('sideBarContainerDivider4')
          .showSideBar(true)
          .sideBarWidth('50px')
          .divider(null)
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
          .id('sideBarContainerDivider5')
          .showSideBar(true)
          .sideBarWidth('50px')
          .divider(this.sideBarContainerDivider)
        }
        .borderWidth(1)
        .width('30%')

        Button('SideBarContainerDivider').onClick(() => {
          ++this.index
          this.sideBarContainerDivider = this.sideBarContainerDividerArr[this.index % 2]
        })
      }
      .width('100%')
      .height('30%')
    }
  }
}