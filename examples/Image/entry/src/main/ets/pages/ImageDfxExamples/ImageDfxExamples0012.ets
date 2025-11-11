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

import image from '@ohos.multimedia.image'

@Entry
@Component
struct ImagePixelMapDemo {
  @State pixmap: image.PixelMap | undefined = undefined

  aboutToAppear(): void {
    // 从本地资源获取 PixelMap
    const uint8 = getContext(this).resourceManager.getMediaContentSync($r('app.media.local_image'))
    const imageSource = image.createImageSource(uint8.buffer)
    this.pixmap = imageSource.createPixelMapSync()
    imageSource?.release()
  }

  build() {
    Column() {
      Text('PixelMap Image 示例')
      Image(this.pixmap)
        .width(120)
        .height(120)
        .borderRadius(8)
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
  }
}
