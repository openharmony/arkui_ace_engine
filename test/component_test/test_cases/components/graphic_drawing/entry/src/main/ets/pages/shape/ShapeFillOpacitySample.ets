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
import shapeFillOpacityTest from '../MyTest/ShapeFillOpacityTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ShapeFillOpacitySample {
  @State ShapeFillOpacity: number | string = -0.5

  aboutToAppear(): void {
    loadComponentTestEntry(shapeFillOpacityTest)
  }

  build() {
    Column({ space: 10 }) {
      Shape() {
        Rect().width(300).height(50)
      }
      .width(350)
      .height(140)
      .viewPort({
        x: -2,
        y: -2,
        width: 304,
        height: 130
      })
      .fill(0x317AF7)
      .fillOpacity(this.ShapeFillOpacity)
      .id('shapeFillOpacity1')

      Button('ShapeFillOpacity')
        .onClick(() => {
          this.ShapeFillOpacity = '0.2px'
        })
      Shape() {
        Rect().width(300).height(50)
      }
      .width(350)
      .height(140)
      .viewPort({
        x: -2,
        y: -2,
        width: 304,
        height: 130
      })
      .fill(0x317AF7)
      .fillOpacity($r('app.string.fill_opacity'))
      .id('shapeFillOpacity2')
    }.width('100%').margin({ top: 15 })
  }
}