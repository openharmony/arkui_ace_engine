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

import { AttributeUpdater, PixelMapDrawableDescriptor } from '@kit.ArkUI'
import image from '@ohos.multimedia.image'

class SelfModifier extends AttributeUpdater<ImageAttribute, ImageInterface> {
}

@Entry
@Component
struct SourceSizeTest {
  modifier: SelfModifier = new SelfModifier()

  build() {
    Column() {
      Image($r('app.media.1'))
        .width(300)
        .height(300)
        .attributeModifier(this.modifier)
        .onComplete((event) => {
          if (event?.loadingStatus == 0) {
            let imageWidth = event.width
            let imageHeight = event.height
            console.info(`image size = [${imageWidth}, ${imageHeight}]`)
            let newImageWidth = this.getUIContext().px2vp(imageWidth) / 2
            let newImageHeight = this.getUIContext().px2vp(imageHeight) / 2
            this.modifier.attribute?.sourceSize({ width: newImageWidth, height: newImageHeight });
          }
        })
    }
    .height('100%')
    .width('100%')
  }
}