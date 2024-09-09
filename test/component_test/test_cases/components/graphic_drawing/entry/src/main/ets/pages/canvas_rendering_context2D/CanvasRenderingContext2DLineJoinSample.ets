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
import canvasRenderingContext2DLineJoinTest from '../MyTest/CanvasRenderingContext2DLineJoin'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct CanvasRenderingContext2DLineJoinSample {
  private settings: RenderingContextSettings = new RenderingContextSettings(true)
  private context: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings)

  aboutToAppear(): void {
    loadComponentTestEntry(canvasRenderingContext2DLineJoinTest)
  }

  build() {
    Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center }) {
      Canvas(this.context)
        .width('30%')
        .height('30%')
        .backgroundColor('#ffff00')
        .id('canvasLineJoin')
        .onReady(() => {
          this.context.beginPath()
          this.context.lineWidth = 8
          this.context.lineJoin = 'bevel'
          this.context.moveTo(30, 30)
          this.context.lineTo(120, 60)
          this.context.lineTo(30, 110)
          this.context.stroke()
        })
        .margin({ bottom: 20 })
      Button('CanvasLineJoin1')
        .onClick(() => {
          this.context.beginPath()
          this.context.lineWidth = 8
          this.context.lineJoin = 'round'
          this.context.moveTo(60, 30)
          this.context.lineTo(150, 60)
          this.context.lineTo(60, 110)
          this.context.stroke()
        })
      Button('CanvasLineJoin2')
        .onClick(() => {
          this.context.beginPath()
          this.context.lineWidth = 8
          this.context.lineJoin = 'miter'
          this.context.moveTo(90, 30)
          this.context.lineTo(180, 60)
          this.context.lineTo(90, 110)
          this.context.stroke()
        })
    }
    .width('100%')
    .height('100%')
  }
}