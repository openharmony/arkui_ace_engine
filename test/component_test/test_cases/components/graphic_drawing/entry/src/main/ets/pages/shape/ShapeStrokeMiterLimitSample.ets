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
import shapeStrokeMiterLimitTest from '../MyTest/ShapeStrokeMiterLimitTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ShapeStrokeMiterLimitSample {
  @State shapeStrokeMiterLimitValue: number | string = 5

  aboutToAppear(): void {
    loadComponentTestEntry(shapeStrokeMiterLimitTest)
  }

  build() {
    Column({ space: 10 }) {
      Shape() {
        Path().width(200).height(60).commands('M0 0 L400 0 L400 150 Z')
      }
      .width(300)
      .height(200)
      .viewPort({
        x: -20,
        y: -5,
        width: 310,
        height: 90
      })
      .stroke(0xEE8443)
      .strokeWidth(10)
      .strokeLineJoin(LineJoinStyle.Miter)
      .strokeMiterLimit(this.shapeStrokeMiterLimitValue)
      .id('shapeStrokeMiterLimit')

      Button('ShapeStrokeMiterLimit1')
        .onClick(() => {
          this.shapeStrokeMiterLimitValue = '-10'
        })
      Button('ShapeStrokeMiterLimit2')
        .onClick(() => {
          this.shapeStrokeMiterLimitValue = 0.5
        })
    }.width('100%').margin({ top: 15 })
  }
}