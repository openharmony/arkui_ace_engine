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
import canvasRenderingContext2DLineCapTest from '../MyTest/CanvasRenderingContext2DLineCapTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct CanvasRenderingContext2DLineCapSample {
  private settings: RenderingContextSettings = new RenderingContextSettings(true)
  private context: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings)

  aboutToAppear(): void {
    loadComponentTestEntry(canvasRenderingContext2DLineCapTest)
  }

  build() {
    Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center }) {
      Column({ space: 10 }) {
        Canvas(this.context)
          .width('30%')
          .height('30%')
          .backgroundColor('#ffff00')
          .id('canvasLineCap')
          .onReady(() => {
            this.context.lineWidth = 8
            this.context.beginPath()
            this.context.lineCap = 'butt'
            this.context.moveTo(30, 50)
            this.context.lineTo(220, 50)
            this.context.stroke()
          })
      }

      Button("CanvasLineCap1")
        .onClick(() => {
          this.context.lineWidth = 8
          this.context.beginPath()
          this.context.lineCap = 'round'
          this.context.moveTo(30, 60)
          this.context.lineTo(220, 60)
          this.context.stroke()
        })
      Button('CanvasLineCap2')
        .onClick(() => {
          this.context.lineWidth = 8
          this.context.beginPath()
          this.context.lineCap = 'square'
          this.context.moveTo(30, 70)
          this.context.lineTo(220, 70)
          this.context.stroke()
        })
    }
    .width('100%')
    .height('100%')
  }
}