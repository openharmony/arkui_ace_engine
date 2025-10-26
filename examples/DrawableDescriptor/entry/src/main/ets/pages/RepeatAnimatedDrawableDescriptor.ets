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
import image from '@ohos.multimedia.image'
import { JSON } from '@kit.ArkTS';
import {  } from "@arkts.collections"


@Entry
@Component
struct RepeatAnimatedDrawableDescriptor {
  @State createCount: number = 0
  @State animatedDrawable1?: AnimatedDrawableDescriptor = undefined
  @State pixelMaps: Array<image.PixelMap> = []
  drawables: Array<AnimatedDrawableDescriptor> = []

  aboutToAppear(): void {
    let resManager = this.getUIContext().getHostContext()?.resourceManager
    if (resManager) {
      try {
        let buffer = resManager.getMediaContentSync($r('app.media.img2')).buffer
        let imageSource = image.createImageSource(buffer)
        if (imageSource) {
          imageSource.createPixelMapList().then((pixelMaps: Array<PixelMap>) => {
            this.pixelMaps = pixelMaps
            this.animatedDrawable1 = new AnimatedDrawableDescriptor(pixelMaps, { duration: 2000, iterations: -1 })
          }).catch((error: BusinessError<void>) => {
            console.error(`Lee, erorr = ${JSON.stringify(error)}`)
          })
        }
      } catch (error) {
        console.error(`Lee, error = ${JSON.stringify(error)}`)
      }
    }
  }

  createAnimatedDrawableDescriptorRepeat(index: number) {
    if (index === 10000) {
      return
    }
    this.animatedDrawable1 = new AnimatedDrawableDescriptor(this.pixelMaps, { duration: 1000, iterations: -1 })
    this.createCount++
    setTimeout(() => {
      this.createAnimatedDrawableDescriptorRepeat(index++)
    }, 2000)
  }

  createAnimatedDrawableDescriptorForeach() {
    for (let i = 0; i < 5000; i++) {
      this.drawables.push(new AnimatedDrawableDescriptor(this.pixelMaps, { duration: i * 10, iterations: -1 }))
      this.drawables.push(new AnimatedDrawableDescriptor(this.pixelMaps,
        { frameDurations: [10, 20, 30], autoPlay: false }))
    }
    console.info(`Lee, create 10000 drawable completed`)
  }

  createAnimatedDrawableDescriptorForLoad() {
    for (let i = 0; i < 2000; i++) {
      let drawable = new AnimatedDrawableDescriptor($r('app.media.img2'))
      console.info(`Lee, create animated drawable to load`)
      drawable.load().catch(() => {
        // TODO: Implement error handling.
      })
    }
  }

  build() {
    Column() {
      Text(this.createCount + "").fontSize(20)
      Button("点击创建AnimatedDrawableDescriptor并触发销毁10000次")
        .onClick(() => {
          this.createAnimatedDrawableDescriptorRepeat(0)
        })

      Button("点击循环创建10000个对象并保存下来")
        .onClick(() => {
          this.createAnimatedDrawableDescriptorForeach()
        })

      Button("点击循环创建10000个对象并触发load")
        .onClick(() => {
          this.createAnimatedDrawableDescriptorForLoad()
        })
    }
    .height('100%')
    .width('100%')
  }
}
