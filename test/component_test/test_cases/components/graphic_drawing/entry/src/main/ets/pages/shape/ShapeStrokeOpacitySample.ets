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
import shapeStrokeOpacityTest from '../MyTest/ShapeStrokeOpacityTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ShapeStrokeOpacitySample {
  @State shapeStrokeOpacityValue: number | string = '5px'

  aboutToAppear(): void {
    loadComponentTestEntry(shapeStrokeOpacityTest)
  }

  build() {
    Column({ space: 10 }) {
      Shape() {
        Path().width(300).height(10).commands('M0 0 L900 0')
      }
      .width(350)
      .height(20)
      .viewPort({
        x: 0,
        y: -5,
        width: 300,
        height: 20
      })
      .stroke(0xEE8443)
      .strokeWidth(10)
      .strokeOpacity(this.shapeStrokeOpacityValue)
      .id('shapeStrokeOpacity1')

      Button('ShapeStrokeOpacity')
        .onClick(() => {
          this.shapeStrokeOpacityValue = -10
        })
      Shape() {
        Path().width(300).height(10).commands('M0 0 L900 0')
      }
      .width(350)
      .height(20)
      .viewPort({
        x: 0,
        y: -5,
        width: 300,
        height: 20
      })
      .stroke(0xEE8443)
      .strokeWidth(10)
      .strokeOpacity($r('app.string.stroke_opacity'))
      .id('shapeStrokeOpacity2')
    }.width('100%').margin({ top: 15 })
  }
}