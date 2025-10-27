/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
import { AnimatedDrawableDescriptor } from '@kit.ArkUI'
import { image } from '@kit.ImageKit'

@Entry
@Component
struct AnimatedDrawableDescriptorTestFrameDurations {
  @State drawable1?: DrawableDescriptor = undefined
  @State drawable2?: DrawableDescriptor = undefined
  resources: Resource[] = [
    $r('app.media.1'),
    $r('app.media.2'),
    $r('app.media.3'),
    $r('app.media.4')
  ]

  createPixelMap(src: Resource): image.PixelMap | undefined {
    let manager = this.getUIContext().getHostContext()?.resourceManager
    if (manager) {
      try {
        let buffer = manager.getMediaContentSync(src.id).buffer
        let source = image.createImageSource(buffer)
        let pixelmap = source.createPixelMapSync()
        return pixelmap;
      } catch (error) {
        console.info(`error = ${JSON.stringify(error)}`)
      }
    }
    return undefined
  }

  createAnimationDrawable() {
    let pixelMaps: Array<PixelMap> = []
    let frameDurations: Array<number> = []
    for (let i = 0; i < this.resources.length; i++) {
      let pixelMap = this.createPixelMap(this.resources[i])
      if (pixelMap) {
        pixelMaps.push(pixelMap)
        frameDurations.push(1000)
      }
    }
    this.drawable1 = new AnimatedDrawableDescriptor(pixelMaps, { iterations: -1, duration: 400 })
    this.drawable2 = new AnimatedDrawableDescriptor(pixelMaps, { iterations: -1, frameDurations: frameDurations })
  }

  aboutToAppear(): void {
    this.createAnimationDrawable()
  }

  build() {
    Column() {
      Image(this.drawable1)
        .width(200)
        .height(200)
        .borderColor(Color.Red)
        .borderWidth(1)
      Image(this.drawable2)
        .width(200)
        .height(200)
        .borderColor(Color.Red)
        .borderWidth(1)
    }
    .height('100%')
    .width('100%')
  }
}
