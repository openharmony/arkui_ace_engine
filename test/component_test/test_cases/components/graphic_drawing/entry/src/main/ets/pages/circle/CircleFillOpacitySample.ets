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
import circleFillOpacityTest from '../MyTest/CircleFillOpacityTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct CircleFillOpacitySample {
  @State private fillOpacityValue1: number | string = 0.2
  @State private fillOpacityValue2: number | Resource = -0.2

  aboutToAppear(): void {
    loadComponentTestEntry(circleFillOpacityTest)
  }

  build() {
    Column({ space: 10 }) {
      Circle({ width: 150, height: 150 })
        .fill(Color.Red)
        .fillOpacity(this.fillOpacityValue2)
        .id('circleFillOpacity1')
      Button('CircleFillOpacity1')
        .onClick(() => {
          this.fillOpacityValue2 = $r('app.string.fill_opacity')
        })
      Circle({ width: 150, height: 150 })
        .fill(Color.Red)
        .fillOpacity(this.fillOpacityValue1)
        .id('circleFillOpacity2')
      Button('CircleFillOpacity2')
        .onClick(() => {
          this.fillOpacityValue1 = '10px'
        })
    }
  }
}