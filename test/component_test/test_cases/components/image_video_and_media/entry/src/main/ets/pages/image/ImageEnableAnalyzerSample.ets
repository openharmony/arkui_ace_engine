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
//测试代码路径
import image from '@ohos.multimedia.image'
import imageEnableAnalyzerTest from '../MyTest/ImageEnableAnalyzerTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ImageEnableAnalyzerSample {
  @State imagePixelMap: image.PixelMap | undefined = undefined
  @State enableAnalyzer: boolean = true

  async aboutToAppear() {
    this.imagePixelMap = await this.getPixmapFromMedia($r('app.media.app_icon'))
    loadComponentTestEntry(imageEnableAnalyzerTest)
  }

  build() {
    Column() {
      Image(this.imagePixelMap)
        .enableAnalyzer(this.enableAnalyzer)
        .width(200)
        .height(200)
        .id('imageEnableAnalyzer')
      Button('ImageEnableAnalyzer')
        .onClick(() => {
          this.enableAnalyzer = !this.imagePixelMap
        })
    }
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
