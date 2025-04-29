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
import lineStrokeOpacityTest from '../MyTest/LineStrokeOpacityTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct LineStrokeOpacitySample {
  @State lineStrokeOpacityValue: string | Resource = '10px'

  aboutToAppear(): void {
    loadComponentTestEntry(lineStrokeOpacityTest)
  }

  build() {
    Column({ space: 10 }) {
      Line()
        .width(200)
        .height(150)
        .startPoint([50, 50])
        .endPoint([150, 150])
        .strokeWidth(5)
        .stroke(Color.Orange)
        .strokeOpacity(-10)
        .id('lineStrokeOpacity1')
      Line()
        .width(200)
        .height(150)
        .startPoint([50, 50])
        .endPoint([150, 150])
        .strokeWidth(5)
        .stroke(Color.Orange)
        .strokeOpacity(this.lineStrokeOpacityValue)
        .id('lineStrokeOpacity2')
      Button("LineStrokeOpacity1")
        .onClick(() => {
          this.lineStrokeOpacityValue = $r('app.string.stroke_opacity')
        })
      Button("LineStrokeOpacity2")
        .onClick(() => {
          this.lineStrokeOpacityValue = '-10px'
        })
    }
  }
}