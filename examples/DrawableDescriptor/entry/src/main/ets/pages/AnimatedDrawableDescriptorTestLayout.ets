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
struct AnimatedDrawableDescriptorLayout {
  @State drawable?: AnimatedDrawableDescriptor = undefined

  aboutToAppear(): void {
    let resManager = this.getUIContext().getHostContext()?.resourceManager
    if (resManager) {
      let buffer = resManager.getMediaContentSync($r('app.media.img2')).buffer
      let imageSource = image.createImageSource(buffer)
      if (imageSource) {
        imageSource.createPixelMapList().then((pixelMaps: Array<PixelMap>) => {
          this.drawable = new AnimatedDrawableDescriptor(pixelMaps, { iterations: -1, duration: 3000 })
        })
      }
    }
  }

  build() {
    Column() {
      Image(this.drawable)
      Image(this.drawable).width(100)
      Image(this.drawable).height(100)
      Image(this.drawable).height(200).width(200).objectFit(ImageFit.None).borderColor(Color.Red).borderWidth(1)
    }
    .height('100%')
    .width('100%')
  }
}
