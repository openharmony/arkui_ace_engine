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

import pathStrokeOpacityTest from '../MyTest/PathStrokeOpacityTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct PathStrokeOpacitySample {
  @State pathStrokeOpacityValue: number | string = -5

  aboutToAppear(): void {
    loadComponentTestEntry(pathStrokeOpacityTest)
  }

  build() {
    Column({ space: 10 }) {
      Path()
        .width('210px')
        .height('310px')
        .commands('M0 100 A30 20 20 0 0 200 100 Z')
        .stroke(Color.Blue)
        .strokeWidth(3)
        .strokeOpacity(this.pathStrokeOpacityValue)
        .id('pathStrokeOpacity1')
      Button('PathStrokeOpacity')
        .onClick(() => {
          this.pathStrokeOpacityValue = '5px'
        })
      Path()
        .width('210px')
        .height('310px')
        .commands('M0 100 A30 20 20 0 0 200 100 Z')
        .stroke(Color.Blue)
        .strokeWidth(3)
        .strokeOpacity($r('app.string.stroke_opacity'))
        .id('pathStrokeOpacity2')
    }
  }
}