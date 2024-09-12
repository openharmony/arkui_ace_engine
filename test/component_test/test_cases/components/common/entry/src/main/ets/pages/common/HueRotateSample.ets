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

import hueRotateTest from '../MyTest/HueRotateTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct HueRotateSample {
  @State hueRotateType: number | string = 0
  @State hueRotateType2: number = 0

  aboutToAppear(): void {
    loadComponentTestEntry(hueRotateTest)
  }

  build() {
    Column() {
      Circle({ width: 150, height: 150 })
        .fill(Color.Blue)
        .id('circle1')
        .hueRotate(this.hueRotateType)
        .margin({ bottom: 10 })
      Button('ButtonHueRotate1')
        .onClick(() => {
          this.hueRotateType = '90deg'
        })
      Circle({ width: 150, height: 150 })
        .fill(Color.Blue)
        .id('circle2')
        .hueRotate(10)
        .margin({ bottom: 10 })

      Circle({ width: 150, height: 150 })
        .fill(Color.Blue)
        .id('circle3')
        .hueRotate(this.hueRotateType2)
        .margin({ bottom: 10 })
      Button('ButtonHueRotate2')
        .onClick(() => {
          this.hueRotateType2 += 180
        })
    }
  }
}