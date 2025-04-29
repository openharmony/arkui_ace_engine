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
import offScreenCanvasRenderingContext2DTextAlignTest from '../MyTest/OffScreenCanvasRenderingContext2DTextAlignTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct OffScreenCanvasRenderingContext2DTextAlignSample {
  private settings: RenderingContextSettings = new RenderingContextSettings(true)
  private context: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings)
  private textAlignCanvasTextAlign: CanvasTextAlign = 'start'

  aboutToAppear(): void {
    loadComponentTestEntry(offScreenCanvasRenderingContext2DTextAlignTest)
  }

  build() {
    Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center }) {
      Canvas(this.context)
        .width('100%')
        .height('100%')
        .backgroundColor('#ffff00')
        .id('offScreenCanvasRenderingContext2DTextAlign')
        .onReady(() => {
          this.context.strokeStyle = '#0000ff'
          this.context.moveTo(140, 10)
          this.context.lineTo(140, 160)
          this.context.stroke()
          this.context.font = '18px sans-serif'
          this.context.textAlign = this.textAlignCanvasTextAlign
          this.context.fillText('textAlign=start', 140, 60)
        })
      Button('OffScreenCanvasRenderingContext2DTextAlign1')
        .onClick(() => {
          this.textAlignCanvasTextAlign = 'end'
          this.context.textAlign = this.textAlignCanvasTextAlign
          this.context.fillText('textAlign=end', 140, 80)
        })
      Button('OffScreenCanvasRenderingContext2DTextAlign2')
        .onClick(() => {
          this.textAlignCanvasTextAlign = 'left'
          this.context.textAlign = this.textAlignCanvasTextAlign
          this.context.fillText('textAlign=left', 140, 80)
        })
      Button('OffScreenCanvasRenderingContext2DTextAlign3')
        .onClick(() => {
          this.textAlignCanvasTextAlign = 'center'
          this.context.textAlign = this.textAlignCanvasTextAlign
          this.context.fillText('textAlign=center', 140, 90)
        })
      Button('OffScreenCanvasRenderingContext2DTextAlign4')
        .onClick(() => {
          this.textAlignCanvasTextAlign = 'right'
          this.context.textAlign = this.textAlignCanvasTextAlign
          this.context.fillText('textAlign=right', 140, 100)
        })
    }
    .width('100%')
    .height('100%')
  }
}