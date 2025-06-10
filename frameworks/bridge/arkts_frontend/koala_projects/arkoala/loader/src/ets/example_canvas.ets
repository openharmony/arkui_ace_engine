/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
//import { Box } from "@koalaui/arkoala-extension-component"

@Entry
@Component
export struct Index {

  private settings: RenderingContextSettings = new RenderingContextSettings(true)
  private context: CanvasRenderingContext2D = new CanvasRenderingContext2D()

    build() {
      Column() {
              Text("Arkoala Analog Indicator")
                .fontSize(16)
                .backgroundColor(0xF9CF93)

              Canvas(this.context)
                      .width('100%')
                      .height('100%')
                      .backgroundColor('#aaaaaa')
                      .onReady(() =>{
                        console.log("[zzz] Example OnReady")
                        // this.context.fillStyle = '#ffffff'
                        this.context.fillRect(25, 75, 250, 250)
                        this.context.closePath()

                        //Black Cyrcle
                        this.context.beginPath()
                        this.context.arc(150, 200, 120, 0.0, 6.28, false)
                        // this.context.strokeStyle = 0x000000
                        this.context.lineWidth = 2
                        this.context.closePath()
                        this.context.stroke()

                        //Red Arc
                        this.context.beginPath()
                        this.context.arc(150, 200, 100, 3.49, 3.77, false)
                        // this.context.strokeStyle = 0xff0000
                        this.context.lineWidth = 20
                        this.context.closePath()
                        this.context.stroke()

                        //Orange Arc
                        this.context.beginPath()
                        this.context.arc(150, 200, 100, 3.77, 4.22, false)
                        // this.context.strokeStyle = Color.Orange
                        this.context.lineWidth = 20
                        this.context.closePath()
                        this.context.stroke()

                        this.context.beginPath()
                        this.context.moveTo(150, 200)
                        this.context.lineTo(250, 200)
                        // this.context.strokeStyle = 0xff0000
                        this.context.lineWidth = 5
                        this.context.closePath()
                        this.context.stroke()

                        this.context.beginPath()
                        this.context.arc(150, 200, 10, 0.0, 6.28, false)
                        // this.context.strokeStyle = 0x0000ff
                        this.context.lineWidth = 20
                        this.context.closePath()
                        this.context.stroke()
                      })
      }
      .width(300)
      .height(600)
      .backgroundColor(0x00ffff)
    }
}