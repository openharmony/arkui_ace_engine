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
import polygonStrokeOpacityTest from '../MyTest/PolygonStrokeOpacityTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct PolygonStrokeOpacitySample {
  @State polygonStrokeOpacityValue: number | string = -10

  aboutToAppear(): void {
    loadComponentTestEntry(polygonStrokeOpacityTest)
  }

  build() {
    Column({ space: 10 }) {
      Polygon()
        .width(100)
        .height(100)
        .points([[0, 0], [0, 100], [100, 100], [100, 0]])
        .strokeWidth(5)
        .stroke(Color.Blue)
        .strokeOpacity(this.polygonStrokeOpacityValue)
        .id('polygonStrokeOpacity1')
      Button('PolygonStrokeOpacity')
        .onClick(() => {
          this.polygonStrokeOpacityValue = '10px'
        })
      Polygon()
        .width(100)
        .height(100)
        .points([[0, 0], [0, 100], [100, 100], [100, 0]])
        .strokeWidth(5)
        .stroke(Color.Blue)
        .strokeOpacity($r('app.string.stroke_opacity'))
        .id('polygonStrokeOpacity2')
    }
  }
}