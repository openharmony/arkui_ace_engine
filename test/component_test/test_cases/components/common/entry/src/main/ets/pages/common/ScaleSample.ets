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
import scaleTest from '../MyTest/ScaleTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ScaleSample {
  @State centerXNumber: number | string = 2
  @State centerYNumber: number | string = 2

  aboutToAppear(): void {
    loadComponentTestEntry(scaleTest)
  }

  build() {
    Column() {
      Progress({ value: 10, type: ProgressType.Eclipse })
        .id('progressScale1')
        .scale({
          x: 2,
          y: 0.5,
          z: 3,
          centerX: 2,
          centerY: 30
        })
      Progress({ value: 10, type: ProgressType.Eclipse })
        .id('progressScale2')
        .scale({
          x: 2,
          y: 0.5,
          z: 3,
          centerX: this.centerXNumber,
          centerY: this.centerYNumber
        })

      Button('ButtonProgressScale1')
        .onClick((event: ClickEvent) => {
          this.centerXNumber = '80%'
          this.centerYNumber = '80%'
        })
    }
  }
}