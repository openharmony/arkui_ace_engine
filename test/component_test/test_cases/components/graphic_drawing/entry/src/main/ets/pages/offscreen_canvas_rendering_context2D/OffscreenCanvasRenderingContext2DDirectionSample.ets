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
import offScreenCanvasRenderingContext2DDirectionTest from '../MyTest/OffScreenCanvasRenderingContext2DDirectionTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct OffScreenCanvasRenderingContext2DDirectionSample {
  private settings: RenderingContextSettings = new RenderingContextSettings(true)
  private context: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings)
  private offCanvas: OffscreenCanvas = new OffscreenCanvas(600, 600)
  private directionCanvasDirection: CanvasDirection = 'inherit'

  aboutToAppear(): void {
    loadComponentTestEntry(offScreenCanvasRenderingContext2DDirectionTest)
  }

  build() {
    Flex({
      direction: FlexDirection.Column, alignItems: ItemAlign.Center,
      justifyContent: FlexAlign.Center
    }) {
      Canvas(this.context)
        .width('100%')
        .height('100%')
        .backgroundColor('#ffff00')
        .id('offScreenCanvasRenderingContext2DDirection')
        .onReady(() => {
          let offContext = this.offCanvas.getContext("2d", this.settings)
          let offCtx = offContext
          offCtx.font = '48px serif'
          offCtx.direction = this.directionCanvasDirection
          offCtx.fillText("Hi rtl!", 200, 50)
          let image = offCtx.transferToImageBitmap()
          this.context.transferFromImageBitmap(image)
        })
      Button('OffScreenCanvasRenderingContext2DDirection1')
        .onClick(() => {
          this.directionCanvasDirection = 'rtl'
          let offContext = this.offCanvas.getContext("2d", this.settings)
          let offCtx = offContext
          offCtx.font = '48px serif'
          offCtx.direction = this.directionCanvasDirection
          offCtx.fillText("Hi rtl!", 200, 100)
          let image = offCtx.transferToImageBitmap()
          this.context.transferFromImageBitmap(image)
        })
      Button('OffScreenCanvasRenderingContext2DDirection2')
        .onClick(() => {
          this.directionCanvasDirection = 'ltr'
          let offContext = this.offCanvas.getContext("2d", this.settings)
          let offCtx = offContext
          offCtx.font = '48px serif'
          offCtx.direction = this.directionCanvasDirection
          offCtx.fillText("Hi rtl!", 200, 150)
          let image = offCtx.transferToImageBitmap()
          this.context.transferFromImageBitmap(image)
        })
    }
    .width('100%')
    .height('100%')
  }
}
