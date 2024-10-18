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
import polylineFillTest from '../MyTest/PolylineFillTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct PolylineFillSample {
  @State polylineFillOpacityColorValue1: number | Color = 0xff0000
  @State polylineFillOpacityColorValue2: Resource | string = 'rgba(0, 0,255)'

  aboutToAppear(): void {
    loadComponentTestEntry(polylineFillTest)
  }

  build() {
    Column({ space: 10 }) {
      Polyline({ width: 100, height: 100 })
        .points([[0, 0], [20, 60], [100, 100]])
        .fill(this.polylineFillOpacityColorValue1)
        .id('polylineFill1')
      Button('PolylineFill1')
        .onClick(() => {
          this.polylineFillOpacityColorValue1 = Color.Blue
        })
      Polyline({ width: 100, height: 100 })
        .points([[0, 0], [20, 60], [100, 100]])
        .fill(this.polylineFillOpacityColorValue2)
        .id('polylineFill2')
      Button('PolylineFill2')
        .onClick(() => {
          this.polylineFillOpacityColorValue2 = $r('app.color.color_red')
        })
    }
  }
}