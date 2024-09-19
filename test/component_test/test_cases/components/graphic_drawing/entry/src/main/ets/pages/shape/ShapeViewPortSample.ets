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
import shapeViewPortTest from '../MyTest/ShapeViewPortTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ShapeViewPortSample {
  @State shapeViewPortValueX: number | string = -2
  @State shapeViewPortValueY: number | string = -2
  @State shapeViewPortMyWidth: number | string = 304
  @State shapeViewPortMyHeight: number | string = 130

  aboutToAppear(): void {
    loadComponentTestEntry(shapeViewPortTest)
  }

  build() {
    Column({ space: 10 }) {
      Shape() {
        Rect().width(300).height(50)
      }
      .width(350)
      .height(140)
      .viewPort({
        x: this.shapeViewPortValueX,
        y: this.shapeViewPortValueY,
        width: this.shapeViewPortMyWidth,
        height: this.shapeViewPortMyHeight
      })
      .id('shapeViewPort')

      Button('ShapeViewPort').onClick(() => {
        this.shapeViewPortValueX = '2'
        this.shapeViewPortValueY = '2'
        this.shapeViewPortMyWidth = '400'
        this.shapeViewPortMyHeight = '200'
      })
    }.width('100%').margin({ top: 15 })
  }
}