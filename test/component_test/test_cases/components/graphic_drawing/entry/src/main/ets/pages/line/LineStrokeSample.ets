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
import lineStrokeTest from '../MyTest/LineStrokeTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct LineStrokeSample {
  @State lineStrokeColorValue1: string | number = '#FFFFFF00'
  @State lineStrokeColorValue2: Color | Resource = Color.Blue

  aboutToAppear(): void {
    loadComponentTestEntry(lineStrokeTest)
  }

  build() {
    Column({ space: 10 }) {
      Line({ width: 150, height: 90 })
        .startPoint([0, 0])
        .endPoint([50, 100])
        .stroke(this.lineStrokeColorValue1)
        .strokeWidth(5)
        .id('lineStroke1')
      Button('LineStroke1')
        .onClick(() => {
          this.lineStrokeColorValue1 = 0xff0000
        })
      Line({ width: 150, height: 90 })
        .startPoint([0, 0])
        .endPoint([50, 100])
        .stroke(this.lineStrokeColorValue2)
        .strokeWidth(5)
        .id('lineStroke2')
      Button('LineStroke2')
        .onClick(() => {
          this.lineStrokeColorValue2 = $r('app.color.color_red')
        })
    }
  }
}