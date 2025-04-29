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

import lineStrokeDashArrayTest from '../MyTest/LineStrokeDashArrayTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct LineStrokeDashArraySample {
  @State LineStrokeDashArray: Array<number> = [50, 10, 20, 30]

  aboutToAppear(): void {
    loadComponentTestEntry(lineStrokeDashArrayTest)
  }

  build() {
    Column({ space: 10 }) {
      Line()
        .width(300)
        .height(30)
        .startPoint([50, 20])
        .endPoint([300, 20])
        .stroke(Color.Black)
        .strokeWidth(10)
        .strokeDashArray(this.LineStrokeDashArray)
        .strokeDashOffset(5)
        .id('lineStrokeDashArray')
      Button('LineStrokeDashArray')
        .onClick(() => {
          this.LineStrokeDashArray = [60, 20, 30, 40]
        })
    }
  }
}