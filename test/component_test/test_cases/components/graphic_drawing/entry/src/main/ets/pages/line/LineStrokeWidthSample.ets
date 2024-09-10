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
import lineStrokeWidthTest from '../MyTest/LineStrokeWidthTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct LineStrokeWidthSample {
  @State lineStrokeWidthValue: number | string = 2

  aboutToAppear(): void {
    loadComponentTestEntry(lineStrokeWidthTest)
  }

  build() {
    Column({ space: 10 }) {
      Line()
        .width(200)
        .height(150)
        .startPoint([50, 50])
        .endPoint([150, 150])
        .stroke(Color.Black)
        .strokeWidth(this.lineStrokeWidthValue)
        .id('lineStrokeWidth1')
      Button('LineStrokeWidth1')
        .onClick(() => {
          this.lineStrokeWidthValue = '10px'
        })
      Button('LineStrokeWidth2')
        .onClick(() => {
          this.lineStrokeWidthValue = '50%'
        })
      Line()
        .width(200)
        .height(150)
        .startPoint([50, 50])
        .endPoint([150, 150])
        .stroke(Color.Black)
        .strokeWidth($r('app.string.stroke_width'))
        .id('lineStrokeWidth2')
    }
  }
}