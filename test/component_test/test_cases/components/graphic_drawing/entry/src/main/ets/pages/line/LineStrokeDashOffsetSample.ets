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
import lineStrokeDashOffsetTest from '../MyTest/LineStrokeDashOffsetTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct LineStrokeDashOffsetSample {
  @State lineStrokeDashOffsetValue: number | string = -5

  aboutToAppear(): void {
    loadComponentTestEntry(lineStrokeDashOffsetTest)
  }

  build() {
    Column({ space: 10 }) {
      Line()
        .width(200)
        .height(150)
        .startPoint([0, 0])
        .endPoint([100, 100])
        .stroke(Color.Black)
        .strokeWidth(3)
        .strokeDashArray([50, 10, 20, 30])
        .strokeDashOffset(this.lineStrokeDashOffsetValue)
        .id('lineStrokeDashOffset')
      Button('LineStrokeDashOffset')
        .onClick(() => {
          this.lineStrokeDashOffsetValue = '5'
        })
    }
  }
}