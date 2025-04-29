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
import canvasRenderingContext2DHeightTest from '../MyTest/CanvasRenderingContext2DHeightTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct CanvasRenderingContext2DHeightSample {
  private settings: RenderingContextSettings = new RenderingContextSettings(true)
  private context: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings)
  private myHeight: number = 0

  aboutToAppear(): void {
    loadComponentTestEntry(canvasRenderingContext2DHeightTest)
  }

  build() {
    Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center }) {
      Canvas(this.context)
        .width(500)
        .height(500)
        .backgroundColor('#ffff00')
        .id('canvasHeight')
        .onReady(() => {
          let h = this.context.height
          this.context.fillRect(0, 0, 100, h / 2)
          this.myHeight = h / 2
          this.context.fillRect(0, 0, 100, 100)
        })
      Button('CanvasHeight')
        .onClick(() => {
          this.myHeight += 100;
          this.context.fillRect(0, 0, 300, this.myHeight)
          this.context.fillStyle = ('rgb(255,0,0)')
        })
    }
    .width('100%')
    .height('100%')
  }
}