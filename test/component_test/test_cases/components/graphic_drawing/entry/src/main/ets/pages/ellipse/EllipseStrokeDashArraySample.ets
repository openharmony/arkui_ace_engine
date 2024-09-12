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
import ellipseStrokeDashArrayTest from '../MyTest/EllipseStrokeDashArrayTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct EllipseStrokeDashArraySample {
  @State ellipseStrokeDashArrayValue: Array<number> = [1, 2]

  aboutToAppear(): void {
    loadComponentTestEntry(ellipseStrokeDashArrayTest)
  }

  build() {
    Column({ space: 10 }) {
      Ellipse({ width: 150, height: 90 })
        .stroke(Color.Blue)
        .strokeDashArray(this.ellipseStrokeDashArrayValue)
        .strokeDashOffset(10)
        .id('ellipseStrokeDashArray')
      Button('EllipseStrokeDashArray')
        .onClick(() => {
          this.ellipseStrokeDashArrayValue = [5, 10]
        })
    }
  }
}