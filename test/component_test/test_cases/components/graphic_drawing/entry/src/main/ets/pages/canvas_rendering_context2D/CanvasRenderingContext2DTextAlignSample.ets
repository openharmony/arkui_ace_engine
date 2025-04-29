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
import canvasRenderingContext2DTextAlignTest from '../MyTest/CanvasRenderingContext2DTextAlignTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct CanvasRenderingContext2DTextAlignSample {
  private settings: RenderingContextSettings = new RenderingContextSettings(true)
  private context: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings)

  aboutToAppear(): void {
    loadComponentTestEntry(canvasRenderingContext2DTextAlignTest)
  }

  build() {
    Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center }) {
      Canvas(this.context)
        .width('100%')
        .height('100%')
        .backgroundColor('#ffff00')
        .id('canvasTextAlign')
        .onReady(() => {
          this.context.strokeStyle = '#0000ff'
          this.context.moveTo(140, 10)
          this.context.lineTo(140, 160)
          this.context.stroke()
          this.context.font = '18px sans-serif'
          this.context.textAlign = 'start'
          this.context.fillText('textAlign=start', 140, 60)
        })
      Button('CanvasTextAlign1')
        .onClick(() => {
          this.context.textAlign = 'end'
          this.context.fillText('textAlign=end', 140, 80)
        })
      Button('CanvasTextAlign2')
        .onClick(() => {
          this.context.textAlign = 'left'
          this.context.fillText('textAlign=left', 140, 80)
        })
      Button('CanvasTextAlign3')
        .onClick(() => {
          this.context.textAlign = 'center'
          this.context.fillText('textAlign=center', 140, 90)
        })
      Button('CanvasTextAlign4')
        .onClick(() => {
          this.context.textAlign = 'right'
          this.context.fillText('textAlign=right', 140, 100)
        })
    }
    .width('100%')
    .height('100%')
  }
}