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
import lineStartPointTest from '../MyTest/LineStartPointTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct LineStartPointSample {
  @State lineStartPointValue: Array<number> = [0, 0]

  aboutToAppear(): void {
    loadComponentTestEntry(lineStartPointTest)
  }

  build() {
    Column({ space: 10 }) {
      Line()
        .width(200)
        .height(150)
        .startPoint(this.lineStartPointValue)
        .endPoint([50, 100])
        .stroke(Color.Black)
        .strokeWidth(10)
        .id('lineStartPoint')
      Button('LineStartPoint')
        .onClick(() => {
          this.lineStartPointValue = [100, 100]
        })
    }
  }
}