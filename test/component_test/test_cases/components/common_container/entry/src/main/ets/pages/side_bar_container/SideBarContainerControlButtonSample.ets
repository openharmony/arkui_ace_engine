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
import sideBarContainerControlButtonTest from '../MyTest/SideBarContainerControlButtonTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SideBarContainerControlButtonSample {
  @State controlButtonPosition: number = 150
  @State controlButtonSize: number = 150
  @State controlButtonIconState: string | PixelMap | Resource = '../../../resources/base/media/icon.png'

  aboutToAppear(): void {
    loadComponentTestEntry(sideBarContainerControlButtonTest)
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
          .id('sideBarContainerControlButton1')
          .controlButton({
            left: this.controlButtonPosition,
            top: this.controlButtonPosition,
            width: this.controlButtonSize,
            height: this.controlButtonSize,
            icons: {
              shown: this.controlButtonIconState,
              hidden: this.controlButtonIconState,
              switching: this.controlButtonIconState
            }
          })
        }
        .borderWidth(1)
        .width('30%')

        Button('SideBarContainerControlButton').onClick(() => {
          this.controlButtonPosition = 80
          this.controlButtonSize = 80
          this.controlButtonIconState = $r('app.media.startIcon')
        })
      }
      .width('100%')
      .height('30%')
    }
  }
}
