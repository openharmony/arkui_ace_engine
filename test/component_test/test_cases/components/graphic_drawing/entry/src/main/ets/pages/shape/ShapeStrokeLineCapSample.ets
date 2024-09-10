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
import shapeStrokeLineCapTest from '../MyTest/ShapeStrokeLineCapTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ShapeStrokeLineCapSample {
  @State shapeLineCapStyle: LineCapStyle = LineCapStyle.Round

  aboutToAppear(): void {
    loadComponentTestEntry(shapeStrokeLineCapTest)
  }

  build() {
    Column({ space: 10 }) {
      Shape() {
        Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
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
      .stroke(Color.Black)
      .strokeWidth(4)
      .strokeLineCap(this.shapeLineCapStyle)
      .id('shapeStrokeLineCap1')

      Button('ShapeStrokeLineCap')
        .onClick(() => {
          this.shapeLineCapStyle = LineCapStyle.Square
        })
      Shape() {
        Path().width(300).height(10).commands('M0 0 L900 0').offset({ x: 0, y: 120 })
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
      .stroke(Color.Blue)
      .strokeWidth(4)
      .strokeLineCap(LineCapStyle.Butt)
      .id('shapeStrokeLineCap2')
    }.width('100%').margin({ top: 15 })
  }
}