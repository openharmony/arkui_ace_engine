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

import image from '@ohos.multimedia.image'
import {AnimationOptions, AnimatedDrawableDescriptor} from '@ohos.arkui.drawableDescriptor'

@Entry
@Component
struct ImageExampleTest {
  @State text: string = ''
  pixelmaps: Array<PixelMap> = [];
  option: AnimationOptions = { duration: 2000, iterations: 1 };
  @State animated: AnimatedDrawableDescriptor | undefined = undefined;
  @State enableAnalyzer: boolean = true
  @State imagePixelMap: image.PixelMap | undefined = undefined
  private aiController: ImageAnalyzerController = new ImageAnalyzerController()
  @State options: ImageAIOptions = {
    types: [ImageAnalyzerType.SUBJECT, ImageAnalyzerType.TEXT],
    aiController: this.aiController
  }

  async aboutToAppear() {
    this.pixelmaps = await this.getPixelMaps();
    this.animated = new AnimatedDrawableDescriptor(this.pixelmaps, this.option);
    this.imagePixelMap = await this.getPixmapFromMedia($r('app.media.81'))
  }

  build() {
    Column() {
      Text('PixelMap')
      Image(this.imagePixelMap, this.options)
        .enableAnalyzer(this.enableAnalyzer)
        .width(200)
        .height(200)

      Text('Resource')
      Image($r('app.media.81'), this.options)
        .enableAnalyzer(this.enableAnalyzer)
        .width(200)
        .height(200)

      Text('DrawableDescriptor')
      Image(this.animated, this.options)
        .enableAnalyzer(this.enableAnalyzer)
        .width(200)
        .height(200)

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
  }

  private async getPixmapListFromMedia(resource: Resource) {
    let unit8Array = await getContext(this)?.resourceManager?.getMediaContent({
      bundleName: resource.bundleName,
      moduleName: resource.moduleName,
      id: resource.id
    })
    let imageSource = image.createImageSource(unit8Array.buffer.slice(0, unit8Array.buffer.byteLength))
    let createPixelMap: Array<image.PixelMap> = await imageSource.createPixelMapList({
      desiredPixelFormat: image.PixelMapFormat.RGBA_8888
    })
    await imageSource.release()
    return createPixelMap
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

  private async getPixelMaps() {
    let Mypixelmaps: Array<PixelMap> = await this.getPixmapListFromMedia($r('app.media.22')) //gif图, 生成多张PixelMap
    Mypixelmaps.push(await this.getPixmapFromMedia($r('app.media.81'))) //添加一张图片
    return Mypixelmaps;
  }
}