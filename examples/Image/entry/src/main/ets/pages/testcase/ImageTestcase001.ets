/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

/**
 * 测试LayeredDrawableDescriptor
 */
import { DrawableDescriptor, LayeredDrawableDescriptor, PixelMapDrawableDescriptor } from '@kit.ArkUI'
import { image } from '@kit.ImageKit'

@Entry
@Component
struct DrawableTestCase1 {
  @State fore: image.PixelMap | undefined = undefined
  @State back: image.PixelMap | undefined = undefined
  @State foregroundDraw: DrawableDescriptor | undefined = undefined
  @State backgroundDraw: DrawableDescriptor | undefined = undefined
  @State maskDraw: DrawableDescriptor | undefined = undefined
  @State maskPixel: image.PixelMap | undefined = undefined
  @State draw: LayeredDrawableDescriptor | undefined = undefined
  @State drawTest: LayeredDrawableDescriptor | undefined = undefined
  @State undefinedDraw: DrawableDescriptor | undefined = undefined

  async aboutToAppear() {
    this.fore = await this.getPixmapFromMedia($r('app.media.foreground'))
    this.back = await this.getPixmapFromMedia($r('app.media.background'))
    this.maskPixel = await this.getPixmapFromMedia($r('app.media.mask'))

    // 使用PixelMapDrawableDescriptor创建LayeredDrawableDescriptor
    this.foregroundDraw = new PixelMapDrawableDescriptor(this.fore)
    this.backgroundDraw = new PixelMapDrawableDescriptor(this.back)
    this.maskDraw = new PixelMapDrawableDescriptor(this.maskPixel)
    this.draw = new LayeredDrawableDescriptor(this.foregroundDraw, this.backgroundDraw, this.maskDraw)
    this.undefinedDraw = new PixelMapDrawableDescriptor(undefined)
    this.drawTest = new LayeredDrawableDescriptor(this.undefinedDraw, this.backgroundDraw, this.maskDraw)
  }

  build() {
    Row() {
      Column() {
        Image(this.draw)
          .width(100)
          .height(100)

        Image(this.draw?.getForeground())
          .width(100)
          .height(100)

        Image(this.draw?.getBackground())
          .width(100)
          .height(100)

        Image(this.draw?.getMask())
          .width(100)
          .height(100)

        Image(this.draw?.getPixelMap())
          .width(100)
          .height(100)

        Image(this.drawTest)
          .width(100)
          .height(100)
      }
      .height('100%')
      .justifyContent(FlexAlign.Center)
    }
    .width('100%')
    .height('100%')
    .backgroundColor(Color.Pink)
  }

  // 根据资源，通过图片框架获取pixelMap
  private async getPixmapFromMedia(resource: Resource) {
    let unit8Array = await getContext(this)?.resourceManager?.getMediaContent({
      bundleName: resource.bundleName,
      moduleName: resource.moduleName,
      id: resource.id
    })
    let imageSource = image.createImageSource(unit8Array.buffer.slice(0, unit8Array.buffer.byteLength))
    let createPixelMap: image.PixelMap = await imageSource.createPixelMap({
      desiredPixelFormat: image.PixelMapFormat.BGRA_8888
    })
    await imageSource.release()
    return createPixelMap
  }
}

