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
import SampleTest from '../MyTest/OffScreenCanvasRenderingContext2DGlobalCompositeOperationTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct OffScreenCanvasRenderingContext2DGlobalCompositeOperationSample {
  private settings: RenderingContextSettings = new RenderingContextSettings(true)
  private context: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings)
  private numCount: number = 0

  aboutToAppear(): void {
    loadComponentTestEntry(SampleTest)
  }

  build() {
    Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center }) {
      Canvas(this.context)
        .width('100%')
        .height('100%')
        .backgroundColor('#ffff00')
        .id('offCanvasRenderingContext2DGlobalCompositeOperation')
        .onReady(() => {
          this.context.fillStyle = 'rgb(255,0,0)'
          this.context.fillRect(20, 20, 50, 50)
          this.context.globalCompositeOperation = 'source-over'
        })
      Button('OffCanvasRenderingContext2DGlobalCompositeOperation')
        .onClick(() => {
          this.numCount++
          this.numCount % 11
          switch (this.numCount) {
            case 0: {
              this.context.fillStyle = 'rgb(255,0,0)'
              this.context.fillRect(20, 20, 50, 50)
              this.context.globalCompositeOperation = 'source-over'
            }
              break
            case 1: {
              this.context.fillStyle = 'rgba(230, 255, 0, 1.00)'
              this.context.fillRect(30, 20, 50, 50)
              this.context.globalCompositeOperation = 'source-atop'
            }
              break
            case 2: {
              this.context.fillStyle = 'rgba(68, 255, 0, 1.00)'
              this.context.fillRect(40, 20, 50, 50)
              this.context.globalCompositeOperation = 'source-in'
            }
              break
            case 3: {
              this.context.fillStyle = 'rgba(0, 255, 136, 1.00)'
              this.context.fillRect(50, 20, 50, 50)
              this.context.globalCompositeOperation = 'source-out'
            }
              break
            case 4: {
              this.context.fillStyle = 'rgba(0, 234, 255, 1.00)'
              this.context.fillRect(60, 20, 50, 50)
              this.context.globalCompositeOperation = 'destination-over'
            }
              break
            case 5: {
              this.context.fillStyle = 'rgba(0, 64, 255, 1.00)'
              this.context.fillRect(70, 20, 50, 50)
              this.context.globalCompositeOperation = 'destination-atop'
            }
              break
            case 6: {
              this.context.fillStyle = 'rgba(119, 0, 255, 1.00)'
              this.context.fillRect(80, 20, 50, 50)
              this.context.globalCompositeOperation = 'destination-in'
            }
              break
            case 7: {
              this.context.fillStyle = 'rgba(208, 0, 255, 1.00)'
              this.context.fillRect(90, 20, 50, 50)
              this.context.globalCompositeOperation = 'destination-out'
            }
              break
            case 8: {
              this.context.fillStyle = 'rgba(255, 0, 140, 1.00)'
              this.context.fillRect(100, 20, 50, 50)
              this.context.globalCompositeOperation = 'lighter'
            }
              break
            case 9: {
              this.context.fillStyle = 'rgba(255, 162, 0, 1.00)'
              this.context.fillRect(110, 20, 50, 50)
              this.context.globalCompositeOperation = 'copy'
            }
              break
            case 10: {
              this.context.fillStyle = 'rgba(156, 191, 160, 0.40)'
              this.context.fillRect(120, 20, 50, 50)
              this.context.globalCompositeOperation = 'xor'
            }
              break
            default:
              this.numCount = 0
              break
          }
        })
    }
    .width('100%')
    .height('100%')
  }
}