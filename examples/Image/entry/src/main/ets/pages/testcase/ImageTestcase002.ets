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
 * 测试PixelMapDrawableDescriptor
 */
import image from '@ohos.multimedia.image'
import { PixelMapDrawableDescriptor } from '@kit.ArkUI'

@Entry
@Component
struct DrawableTestCase2 {
  drawable: DrawableDescriptor | undefined = undefined

  aboutToAppear(): void {
    let uint8 = getContext(this).resourceManager.getMediaContentSync($r('app.media.3'))
    let imageSource = image.createImageSource(uint8.buffer)
    let pixmap = imageSource.createPixelMapSync()
    this.drawable = new PixelMapDrawableDescriptor(pixmap)
  }

  build() {
    Column() {
      Image(this.drawable)
        .width(100)
        .height(100)
    }
    .height('100%')
    .width('100%')
  }
}
