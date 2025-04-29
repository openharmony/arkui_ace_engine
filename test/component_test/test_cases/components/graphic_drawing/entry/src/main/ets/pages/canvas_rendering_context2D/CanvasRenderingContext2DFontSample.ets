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
import canvasRenderingContext2DFontTest from '../MyTest/CanvasRenderingContext2DFontTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct CanvasRenderingContext2DFontSample {
  private settings: RenderingContextSettings = new RenderingContextSettings(true)
  private context: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings)

  aboutToAppear(): void {
    loadComponentTestEntry(canvasRenderingContext2DFontTest)
  }

  build() {
    Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center }) {
      Canvas(this.context)
        .width('100%')
        .height('100%')
        .backgroundColor('#ffff00')
        .id('canvasFont')
        .onReady(() => {
          this.context.font = '30px sans-serif'
          this.context.fillText("Hello px", 20, 60)
        })
      Button('CanvasFont1')
        .onClick(() => {
          this.context.font = 'normal normal 14px sans-serif'
          this.context.fillText("Hello px", 70, 60)
        })
      Button('CanvasFont2')
        .onClick(() => {
          this.context.font = 'italic bold 14px serif'
          this.context.fillText("Hello px", 150, 60)
        })
      Button('CanvasFont3')
        .onClick(() => {
          this.context.font = 'normal bolder 14px monospace'
          this.context.fillText("Hello px", 250, 60)
        })
      Button('CanvasFont4')
        .onClick(() => {
          this.context.font = 'normal lighter 14px monospace'
          this.context.fillText("Hello px", 350, 60)
        })
      Button('CanvasFont5')
        .onClick(() => {
          this.context.font = 'normal 100 14px serif'
          this.context.fillText("Hello px", 250, 120)
        })
    }
    .width('100%')
    .height('100%')
  }
}