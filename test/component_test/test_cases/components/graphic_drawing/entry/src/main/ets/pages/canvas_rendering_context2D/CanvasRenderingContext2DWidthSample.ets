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
import canvasRenderingContext2DWidthTest from '../MyTest/CanvasRenderingContext2DWidthTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct CanvasRenderingContext2DWidth {
  private settings: RenderingContextSettings = new RenderingContextSettings(true)
  private context: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings)
  private myWidth: number = 0

  aboutToAppear(): void {
    loadComponentTestEntry(canvasRenderingContext2DWidthTest)
  }

  build() {
    Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center }) {
      Canvas(this.context)
        .width(300)
        .height(300)
        .backgroundColor('#ffff00')
        .id('canvasWidth')
        .onReady(() => {
          let w = this.context.height
          this.context.fillRect(0, 0, 100, w / 2)
          this.myWidth = w / 2
          this.context.fillRect(0, 0, 100, 100)
        })
        .margin({ top: 30, bottom: 50 })
      Button('CanvasWidth')
        .onClick(() => {
          this.myWidth += 100;
          this.context.fillRect(0, 0, 300, this.myWidth)
          this.context.fillStyle = ('rgb(255,0,0)')
        })
    }
    .width('100%')
    .height('100%')
  }
}