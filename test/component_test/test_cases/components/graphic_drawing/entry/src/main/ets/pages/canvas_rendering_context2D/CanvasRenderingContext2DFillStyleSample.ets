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
import canvasCanvasRenderingContext2DFillStyleTest from '../MyTest/CanvasCanvasRenderingContext2DFillStyleTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct CanvasCanvasRenderingContext2DFillStyleSample {
  private settings: RenderingContextSettings = new RenderingContextSettings(true)
  private context: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings)

  aboutToAppear(): void {
    loadComponentTestEntry(canvasCanvasRenderingContext2DFillStyleTest)
  }

  build() {
    Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center }) {
      Canvas(this.context)
        .width('50%')
        .height('50%')
        .backgroundColor('#ffff00')
        .id('canvasFillStyle')
        .onReady(() => {
          this.context.fillStyle = 0xff0000
          this.context.fillRect(170, 100, 150, 100)
        })
      Button('CanvasFillStyle')
        .onClick(() => {
          this.context.fillStyle = 'rgb(0,0,255)'
          this.context.fillRect(20, 20, 150, 100)
        })
        .margin({ top: 30, bottom: 50 })
    }
    .width('100%')
    .height('100%')
  }
}