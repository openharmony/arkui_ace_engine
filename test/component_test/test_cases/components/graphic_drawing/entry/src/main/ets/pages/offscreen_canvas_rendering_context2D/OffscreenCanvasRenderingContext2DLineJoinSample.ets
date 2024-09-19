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
import offScreenCanvasRenderingContext2DLineJoinTest from '../MyTest/OffScreenCanvasRenderingContext2DLineJoinTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct OffScreenCanvasRenderingContext2DLineJoinSample {
  private settings: RenderingContextSettings = new RenderingContextSettings(true)
  private context: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings)

  aboutToAppear(): void {
    loadComponentTestEntry(offScreenCanvasRenderingContext2DLineJoinTest)
  }

  build() {
    Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center }) {
      Canvas(this.context)
        .width('100%')
        .height('100%')
        .backgroundColor('#ffff00')
        .id('offScreenCanvasRenderingContext2DLineJoin')
        .onReady(() => {
          this.context.lineWidth = 8
          this.context.beginPath()
          this.context.lineJoin = 'round'
          this.context.moveTo(30, 30)
          this.context.lineTo(220, 50)
          this.context.lineTo(30, 110)
          this.context.stroke()
        })
      Button('OffScreenCanvasRenderingContext2DLineJoin1')
        .onClick(() => {
          this.context.lineWidth = 8
          this.context.beginPath()
          this.context.lineJoin = 'bevel'
          this.context.moveTo(30, 130)
          this.context.lineTo(220, 70)
          this.context.lineTo(30, 210)
          this.context.stroke()
        })
      Button('OffScreenCanvasRenderingContext2DLineJoin2')
        .onClick(() => {
          this.context.lineWidth = 8
          this.context.beginPath()
          this.context.lineJoin = 'miter'
          this.context.moveTo(30, 250)
          this.context.lineTo(220, 90)
          this.context.lineTo(30, 310)
          this.context.stroke()
        })
    }
    .width('100%')
    .height('100%')
  }
}