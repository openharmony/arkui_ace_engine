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
import rectStrokeLineCapTest from '../MyTest/RectStrokeLineCapTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct RectStrokeLineCapSample {
  @State lineCapStyleType: LineCapStyle = LineCapStyle.Round

  aboutToAppear(): void {
    loadComponentTestEntry(rectStrokeLineCapTest)
  }

  build() {
    Column({ space: 10 }) {
      Rect()
        .width('90%')
        .height(50)
        .stroke(Color.Red)
        .strokeLineCap(LineCapStyle.Butt)
        .id('rectStrokeLineCap1')
      Rect()
        .width('90%')
        .height(50)
        .stroke(Color.Red)
        .strokeLineCap(this.lineCapStyleType)
        .id('rectStrokeLineCap2')
      Button('RectStrokeLineCap')
        .onClick(() => {
          this.lineCapStyleType = LineCapStyle.Square
        })
    }
  }
}