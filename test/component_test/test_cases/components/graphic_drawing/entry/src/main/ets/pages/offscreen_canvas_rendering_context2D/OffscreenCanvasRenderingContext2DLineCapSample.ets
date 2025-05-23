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
import offScreenCanvasRenderingContext2DLineCapSquareTest
  from '../MyTest/OffScreenCanvasRenderingContext2DLineCapSquareTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct OffScreenCanvasRenderingContext2DLineCapSquareSample {
  private settings: RenderingContextSettings = new RenderingContextSettings(true)
  private context: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings)

  aboutToAppear(): void {
    loadComponentTestEntry(offScreenCanvasRenderingContext2DLineCapSquareTest)
  }

  build() {
    Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center }) {
      Canvas(this.context)
        .width('100%')
        .height('100%')
        .backgroundColor('#ffff00')
        .id('offScreenCanvasRenderingContext2DLineCapSquare')
        .onReady(() => {
          this.context.lineWidth = 8
          this.context.beginPath()
          this.context.lineCap = 'square'
          this.context.moveTo(30, 50)
          this.context.lineTo(220, 50)
          this.context.stroke()
        })
      Button('OffScreenCanvasRenderingContext2DLineCapSquare1')
        .onClick(() => {
          this.context.lineWidth = 8
          this.context.beginPath()
          this.context.lineCap = 'round'
          this.context.moveTo(50, 120)
          this.context.lineTo(220, 70)
          this.context.stroke()
        })
      Button('OffScreenCanvasRenderingContext2DLineCapSquare2')
        .onClick(() => {
          this.context.lineWidth = 8
          this.context.beginPath()
          this.context.lineCap = 'butt'
          this.context.moveTo(110, 180)
          this.context.lineTo(220, 90)
          this.context.stroke()
        })
    }
    .width('100%')
    .height('100%')
  }
}