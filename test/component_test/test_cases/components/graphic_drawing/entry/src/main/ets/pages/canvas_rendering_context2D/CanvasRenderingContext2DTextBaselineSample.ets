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
import canvasRenderingContext2DTextBaselineTest from '../MyTest/CanvasRenderingContext2DTextBaselineTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct CanvasRenderingContext2DTextBaseline {
  private settings: RenderingContextSettings = new RenderingContextSettings(true)
  private context: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings)

  aboutToAppear(): void {
    loadComponentTestEntry(canvasRenderingContext2DTextBaselineTest)
  }

  build() {
    Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center }) {
      Canvas(this.context)
        .width('100%')
        .height('100%')
        .backgroundColor('#ffff00')
        .id('canvasTextBaseline')
        .onReady(() => {
          this.context.strokeStyle = '#0000ff'
          this.context.moveTo(0, 120)
          this.context.lineTo(400, 120)
          this.context.stroke()
          this.context.font = '20px sans-serif'
          this.context.textBaseline = 'top'
          this.context.fillText('Top', 10, 120)
        })
      Button('CanvasTextBaseline1')
        .onClick(() => {
          this.context.textBaseline = 'bottom'
          this.context.fillText('bottom', 20, 120)
        })
      Button('CanvasTextBaseline2')
        .onClick(() => {
          this.context.textBaseline = 'middle'
          this.context.fillText('middle', 30, 120)
        })
      Button('CanvasTextBaseline3')
        .onClick(() => {
          this.context.textBaseline = 'alphabetic'
          this.context.fillText('alphabetic', 40, 120)
        })
      Button('CanvasTextBaseline4')
        .onClick(() => {
          this.context.textBaseline = 'hanging'
          this.context.fillText('hanging', 50, 120)
        })
      Button('CanvasTextBaseline5')
        .onClick(() => {
          this.context.textBaseline = 'ideographic'
          this.context.fillText('ideographic', 60, 120)
        })
    }
    .width('100%')
    .height('100%')
  }
}