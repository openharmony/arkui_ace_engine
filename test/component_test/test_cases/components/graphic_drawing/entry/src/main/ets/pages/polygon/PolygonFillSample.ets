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
import polygonFillTest from '../MyTest/PolygonFillTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct PolygonFillSample {
  @State polygonFillColorValue: Color | number = Color.Green

  aboutToAppear(): void {
    loadComponentTestEntry(polygonFillTest)
  }

  build() {
    Column({ space: 10 }) {
      Polygon({ width: 100, height: 100 })
        .points([[0, 0], [50, 100], [100, 0]])
        .fill(this.polygonFillColorValue)
        .id('polygonFill1')
      Button('PolygonFill')
        .onClick(() => {
          this.polygonFillColorValue = 0xff0000
        })
      Polygon({ width: 100, height: 100 })
        .points([[0, 0], [50, 100], [100, 0]])
        .fill('rgb(0,255,0)')
        .id('polygonFill2')
      Polygon({ width: 100, height: 100 })
        .points([[0, 0], [50, 100], [100, 0]])
        .fill($r('app.color.color_red'))
        .id('polygonFill3')
    }
  }
}