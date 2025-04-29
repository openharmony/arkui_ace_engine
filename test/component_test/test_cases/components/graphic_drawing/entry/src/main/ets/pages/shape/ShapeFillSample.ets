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
import shapeFillTest from '../MyTest/ShapeFillTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ShapeFillSample {
  @State shapeFillValue: number | string = 0x317AF7

  aboutToAppear(): void {
    loadComponentTestEntry(shapeFillTest)
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
      .fill(this.shapeFillValue)
      .id('shapeFill1')

      Button('ShapeFill')
        .onClick(() => {
          this.shapeFillValue = 'rgb(0,255,0)'
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
      .fill(Color.Blue)
      .id('shapeFill2')

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
      .fill($r('app.color.color_red'))
      .id('shapeFill3')
    }.width('100%').margin({ top: 15 })
  }
}