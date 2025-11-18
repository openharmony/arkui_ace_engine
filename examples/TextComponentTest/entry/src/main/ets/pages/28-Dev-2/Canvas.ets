/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// xxx.ets
import image from '@ohos.multimedia.image'
@Entry
@Component
struct ImageExample {
  @State imagePixelMap: image.PixelMap | undefined = undefined
  @State enableAnalyzer: boolean = true
  @State text: string = ''
  private aiController: ImageAnalyzerController = new ImageAnalyzerController()
  private settings: RenderingContextSettings = new RenderingContextSettings(true)
  private context: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings)
  private context2: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings)
  private img: ImageBitmap = new ImageBitmap('resources/base/media/81.jpg')
  @State options: ImageAIOptions = {
    types: [ImageAnalyzerType.SUBJECT, ImageAnalyzerType.TEXT],
    aiController: this.aiController
  }

  async aboutToAppear() {
    this.imagePixelMap = await this.getPixmapFromMedia($r('app.media.81'))
  }

  build() {
    Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center }) {

      Canvas(this.context, this.options)
        .width('100%')
        .height(400)
        .backgroundColor('#ffff00')
        .onReady(() => {
          this.context.drawImage(this.img, 0, 0, 130, 130)
          let imagedata = this.context.getImageData(0, 0, 130, 130)
          this.context.putImageData(imagedata, 150, 150)
        })

      Text(this.text)

      Row() {
        Button('types: 空')
          .width(150)
          .onClick(() => {
            this.options = {
              types: [],
              aiController: this.aiController
            }
          })
        Button('types: SUBJECT')
          .width(150)
          .onClick(() => {
            this.options = {
              types: [ImageAnalyzerType.SUBJECT],
              aiController: this.aiController
            }
          })
      }.width(300)

      Row() {
        Button('types: TEXT')
          .width(150)
          .onClick(() => {
            this.options = {
              types: [ImageAnalyzerType.TEXT],
              aiController: this.aiController
            }
          })

        Button('types: [SUBJECT, TEXT]')
          .width(150)
          .onClick(() => {
            this.options = {
              types: [ImageAnalyzerType.SUBJECT, ImageAnalyzerType.TEXT],
              aiController: this.aiController
            }
          })
      }.width(300)

      Row() {
        Button('enableAnalyzer:' + this.enableAnalyzer)
          .width(150)
          .onClick(() => {
            this.enableAnalyzer = !this.enableAnalyzer
          })

        Button('getTypes')
          .width(150)
          .onClick(() => {
            this.text = JSON.stringify(this.aiController.getImageAnalyzerSupportTypes())
          })
      }.width(300)

    }
    .width('100%')
    .height('100%')
  }

  private async getPixmapFromMedia(resource: Resource) {
    let unit8Array = await getContext(this)?.resourceManager?.getMediaContent({
      bundleName: resource.bundleName,
      moduleName: resource.moduleName,
      id: resource.id
    })
    let imageSource = image.createImageSource(unit8Array.buffer.slice(0, unit8Array.buffer.byteLength))
    let createPixelMap: image.PixelMap = await imageSource.createPixelMap({
      desiredPixelFormat: image.PixelMapFormat.RGBA_8888
    })
    await imageSource.release()
    return createPixelMap
  }
}