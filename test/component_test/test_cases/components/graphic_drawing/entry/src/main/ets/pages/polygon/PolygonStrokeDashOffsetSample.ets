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
import polygonStrokeDashOffsetTest from '../MyTest/PolygonStrokeDashOffsetTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct PolygonStrokeDashOffsetSample {
  @State private PolygonStrokeDashOffsetValue: number | string = 5

  aboutToAppear(): void {
    loadComponentTestEntry(polygonStrokeDashOffsetTest)
  }

  build() {
    Column({ space: 10 }) {
      Polygon()
        .width(100)
        .height(100)
        .points([[0, 0], [0, 100], [100, 100], [100, 0]])
        .stroke(Color.Blue)
        .strokeDashOffset(this.PolygonStrokeDashOffsetValue)
        .id('polygonStrokeDashOffset')
      Button('PolygonStrokeDashOffset')
        .onClick(() => {
          this.PolygonStrokeDashOffsetValue = '10'
        })
    }
  }
}