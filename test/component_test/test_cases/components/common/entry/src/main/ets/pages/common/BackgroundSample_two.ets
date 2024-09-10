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

import backgroundTest_two from '../MyTest/BackgroundTest_two'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct BackgroundSample_two {
  @State alignmentTop: Alignment = Alignment.BottomEnd

  @Builder
  renderBackground() {
    Text('renderBackground')
      .backgroundColor(Color.Green)
      .width(30)
  }

  aboutToAppear(): void {
    loadComponentTestEntry(backgroundTest_two)
  }

  build() {
    Column() {
      Row() {
        Text("content")
          .width(100)
          .height(40)
          .fontColor("#FFF")
          .position({ x: 50, y: 80 })
          .textAlign(TextAlign.Center)
          .backgroundColor(Color.Green)
      }
      .width(200)
      .height(200)
      .background(this.renderBackground, { align: this.alignmentTop })
      .backgroundColor(Color.Gray)
      .id('rowBackground3')

      Row() {
        Button('ButtonBackground1')
          .onClick(() => {
            this.alignmentTop = Alignment.End
          })
        Button('ButtonBackground2')
          .onClick(() => {
            this.alignmentTop = Alignment.BottomStart
          })
        Button('ButtonBackground3')
          .onClick(() => {
            this.alignmentTop = Alignment.Bottom
          })
      }
    }
  }
}
