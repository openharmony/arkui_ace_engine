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
import ellipseFillOpacityTest from '../MyTest/EllipseFillOpacityTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct EllipseFillOpacitySample {
  @State ellipseFillOpacityValue: number | string = -10

  aboutToAppear(): void {
    loadComponentTestEntry(ellipseFillOpacityTest)
  }

  build() {
    Column({ space: 10 }) {
      Ellipse({ width: 150, height: 90 })
        .fill(Color.Red)
        .fillOpacity(0.5)
        .id('ellipseFillOpacity1')
      Ellipse({ width: 150, height: 90 })
        .fill(Color.Red)
        .fillOpacity(this.ellipseFillOpacityValue)
        .id('ellipseFillOpacity2')
      Button('EllipseFillOpacity')
        .onClick(() => {
          this.ellipseFillOpacityValue = '20px'
        })
    }
  }
}