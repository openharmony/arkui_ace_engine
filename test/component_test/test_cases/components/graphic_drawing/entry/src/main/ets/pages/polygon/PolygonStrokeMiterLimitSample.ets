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
import polygonStrokeMiterLimitTest from '../MyTest/PolygonStrokeMiterLimitTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct PolygonStrokeMiterLimitSample {
  @State PolygonStrokeMiterLimitValue: number | string = 5

  aboutToAppear(): void {
    loadComponentTestEntry(polygonStrokeMiterLimitTest)
  }

  build() {
    Column({ space: 10 }) {
      Polygon()
        .width(100)
        .height(100)
        .points([[0, 0], [0, 100], [100, 100], [100, 0]])
        .stroke(Color.Blue)
        .strokeWidth(3)
        .strokeLineJoin(LineJoinStyle.Miter)
        .strokeMiterLimit(this.PolygonStrokeMiterLimitValue)
        .id('polygonStrokeMiterLimit')
      Button('PolygonStrokeMiterLimit1')
        .onClick(() => {
          this.PolygonStrokeMiterLimitValue = '0.5'
        })
      Button('PolygonStrokeMiterLimit2')
        .onClick(() => {
          this.PolygonStrokeMiterLimitValue = -10
        })
    }
  }
}