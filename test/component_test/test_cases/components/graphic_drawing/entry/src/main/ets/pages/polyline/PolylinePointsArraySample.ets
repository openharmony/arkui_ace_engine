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
import polylinePointsTest from '../MyTest/PolylinePointsTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct PolylinePointsSample {
  @State polylinePointsArrayX: number = 0
  @State polylinePointsArrayY: number = 0

  aboutToAppear(): void {
    loadComponentTestEntry(polylinePointsTest)
  }

  build() {
    Column({ space: 10 }) {
      Polyline({ width: 100, height: 100 })
        .points([[this.polylinePointsArrayX, this.polylinePointsArrayY], [20, 60], [100, 100]])
        .id('polylinePoints')
      Button('PolylinePoints')
        .onClick(() => {
          this.polylinePointsArrayX = 10
          this.polylinePointsArrayY = 10
        })
    }
  }
}