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
import polylineStrokeDashArrayTest from '../MyTest/PolylineStrokeDashArrayTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct PolylineStrokeDashArraySample {
  @State private polylineStrokeDashArrayNumber: number = 5

  aboutToAppear(): void {
    loadComponentTestEntry(polylineStrokeDashArrayTest)
  }

  build() {
    Column({ space: 10 }) {
      Polyline()
        .width(100)
        .height(100)
        .stroke(Color.Red)
        .strokeWidth(5)
        .strokeDashArray([this.polylineStrokeDashArrayNumber])
        .strokeDashOffset(-10)
        .points([[0, 0], [50, 100], [100, 0]])
        .id('polylineStrokeDashArray')
      Button('PolylineStrokeDashArray')
        .onClick(() => {
          this.polylineStrokeDashArrayNumber = 10
        })
    }
  }
}