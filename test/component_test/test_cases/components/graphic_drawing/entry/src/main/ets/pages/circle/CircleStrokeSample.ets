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
import circleStrokeColorTest from '../MyTest/CircleStrokeTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct CircleStrokeSample {
  @State circleStrokeColorValue1: number | Color = 0x0000ff
  @State circleStrokeColorValue2: Resource | string = 'rgb(0,0,255)'

  aboutToAppear(): void {
    loadComponentTestEntry(circleStrokeColorTest)
  }

  build() {
    Column({ space: 10 }) {
      Circle({ width: 150, height: 150 })
        .stroke(this.circleStrokeColorValue1)
        .id('circleStrokeColor1')
      Button('CircleStrokeColor1')
        .onClick(() => {
          this.circleStrokeColorValue1 = Color.Red
        })
      Circle({ width: 150, height: 150 })
        .stroke(this.circleStrokeColorValue2)
        .id('circleStrokeColor2')
      Button('CircleStrokeColor2')
        .onClick(() => {
          this.circleStrokeColorValue2 = $r('app.color.color_red')
        })
    }
  }
}