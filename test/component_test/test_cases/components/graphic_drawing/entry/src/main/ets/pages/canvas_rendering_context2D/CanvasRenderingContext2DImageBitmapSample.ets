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
import canvasRenderingContext2DImageBitmapTest from '../MyTest/CanvasRenderingContext2DImageBitmapTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct CanvasImageBitmapSample {
  private settings: RenderingContextSettings = new RenderingContextSettings(true)
  private context: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings)
  private img: ImageBitmap = new ImageBitmap("../image_bitmap/image.jpg")

  aboutToAppear(): void {
    loadComponentTestEntry(canvasRenderingContext2DImageBitmapTest)
  }

  build() {
    Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center }) {
      Canvas(this.context)
        .width('100%')
        .height('100%')
        .backgroundColor('#ffff00')
        .id('canvasImageBitmap')
        .onReady(() => {
          this.context.drawImage(this.img, 0, 0, 500, 500, 0, 0, 400, 200)
        })
    }
    .width('100%')
    .height('100%')
  }
}