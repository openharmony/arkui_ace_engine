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

import pixelRoundTest from '../MyTest/PixelRoundTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct PixelRoundSample {
  pixelRoundCalcArr: PixelRoundCalcPolicy[] =
    [PixelRoundCalcPolicy.NO_FORCE_ROUND, PixelRoundCalcPolicy.FORCE_CEIL, PixelRoundCalcPolicy.FORCE_FLOOR]
  index: number = 0
  @State pixelRoundCalc: PixelRoundCalcPolicy = this.pixelRoundCalcArr[this.index]

  aboutToAppear(): void {
    loadComponentTestEntry(pixelRoundTest)
  }

  build() {
    Column() {
      Row() {
        Row() {
        }
        .width('100%')
        .height('100%')
        .backgroundColor(Color.Yellow)
      }
      .id('rowPixelRound')
      .width('300.6px')
      .height('300.6px')
      .backgroundColor(Color.Red)
      .position({ x: '200.2px', y: '100.2px' })
      .pixelRound({
        start: this.pixelRoundCalc,
        top: this.pixelRoundCalc,
        end: this.pixelRoundCalc,
        bottom: this.pixelRoundCalc
      })

      Button('ButtonPixelRound').onClick(() => {
        this.index++
        this.pixelRoundCalc = this.pixelRoundCalcArr[this.index % 3]
      })
    }
    .width("100%")
    .height('100%')
    .backgroundColor('#ffe5e5e5')
  }
}