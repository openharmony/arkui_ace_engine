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
import directionTest from '../MyTest/DirectionTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct DirectionSample {
  @State directionLtr: Direction = Direction.Ltr

  aboutToAppear(): void {
    loadComponentTestEntry(directionTest)
  }

  build() {
    Column() {
      Text('direction').fontSize(9).fontColor(0xCCCCCC).width('90%')

      Row() {
        Text('direction1').height(50).width('25%').fontSize(16).backgroundColor(0xF5DEB3)
        Text('direction2').height(50).width('25%').fontSize(16).backgroundColor(0xD2B48C)
        Text('direction3').height(50).width('25%').fontSize(16).backgroundColor(0xF5DEB3)
        Text('direction4').height(50).width('25%').fontSize(16).backgroundColor(0xD2B48C)
      }
      .width('90%')
      .id('rowDirection1')
      .direction(this.directionLtr)

      Button('ButtonDirection1')
        .onClick(() => {
          this.directionLtr = Direction.Rtl
        })

      Button('ButtonDirection2')
        .onClick(() => {
          this.directionLtr = Direction.Auto
        })
    }
  }
}