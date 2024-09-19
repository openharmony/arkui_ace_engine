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
import rectStrokeTest from '../MyTest/RectStrokeTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct RectStrokeSample {
  @State rectStrokeColorValue1: ResourceColor = Color.Red
  @State rectStrokeColorValue2: ResourceColor = 'rgb(255,0,0)'

  aboutToAppear(): void {
    loadComponentTestEntry(rectStrokeTest)
  }

  build() {
    Column({ space: 10 }) {
      Rect()
        .width('90%')
        .height(50)
        .stroke(this.rectStrokeColorValue1)
        .id('rectStroke1')
      Button('RectStroke1')
        .onClick(() => {
          this.rectStrokeColorValue1 = 0xff0000
        })
      Rect()
        .width('90%')
        .height(50)
        .stroke(this.rectStrokeColorValue2)
        .id('rectStroke2')
      Button('RectStroke2')
        .onClick(() => {
          this.rectStrokeColorValue2 = $r('app.color.color_red')
        })
    }
  }
}