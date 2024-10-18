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
import offScreenCanvasRenderingContext2DFilterTest from '../MyTest/OffScreenCanvasRenderingContext2DFilterTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct OffScreenCanvasRenderingContext2DFilterSample {
  private settings: RenderingContextSettings = new RenderingContextSettings(true)
  private context: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings)
  private img: ImageBitmap = new ImageBitmap("../image_bitmap/image.jpg")
  private numCount: number = 0

  aboutToAppear(): void {
    loadComponentTestEntry(offScreenCanvasRenderingContext2DFilterTest)
  }

  build() {
    Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center }) {
      Canvas(this.context)
        .width('100%')
        .height('100%')
        .backgroundColor('#ffff00')
        .id('offScreenCanvasRenderingContext2DFilter')
        .onReady(() => {
          this.context.drawImage(this.img, 0, 0, 100, 100)
          this.context.filter = 'none'
        })
      Button('OffScreenCanvasRenderingContext2DFilter')
        .onClick(() => {
          this.numCount++
          this.numCount %= 10
          switch (this.numCount) {
            case 0: {
              this.context.drawImage(this.img, 0, 0, 100, 100)
              this.context.filter = 'none'
            }
              break
            case 1: {
              this.context.drawImage(this.img, 100, 0, 100, 100)
              this.context.filter = 'grayscale(50%)'
            }
              break
            case 2: {
              this.context.drawImage(this.img, 200, 0, 100, 100)
              this.context.filter = 'sepia(60%)'
            }
              break
            case 3: {
              this.context.drawImage(this.img, 0, 100, 100, 100)
              this.context.filter = 'saturate(30%)'
            }
              break
            case 4: {
              this.context.drawImage(this.img, 100, 100, 100, 100)
              this.context.filter = 'hue-rotate(90deg)'
            }
              break
            case 5: {
              this.context.drawImage(this.img, 200, 100, 100, 100)
              this.context.filter = 'invert(100%)'
            }
              break
            case 6: {
              this.context.drawImage(this.img, 0, 200, 100, 100)
              this.context.filter = 'opacity(25%)'
            }
              break
            case 7: {
              this.context.drawImage(this.img, 100, 200, 100, 100)
              this.context.filter = 'brightness(0.4)'
            }
              break
            case 8: {
              this.context.drawImage(this.img, 200, 200, 100, 100)
              this.context.filter = 'contrast(200%)'
            }
              break
            case 9: {
              this.context.drawImage(this.img, 0, 300, 100, 100)
              this.context.filter = 'blur(5px)'
            }
              break
          }
        })
    }
    .width('100%')
    .height('100%')
  }
}