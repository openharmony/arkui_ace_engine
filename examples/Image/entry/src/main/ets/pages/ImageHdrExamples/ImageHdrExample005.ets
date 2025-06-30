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
 * This example demonstrates how to decode an HDR image using the ImageSource API
 * and display it using a PixelMap in an ArkTS component.
 */
import { Size } from '@kit.ArkUI';
import image from '@ohos.multimedia.image';

@Entry
@Component
struct Index {
  @State label: boolean = false;
  @State s: Size = { width: 100, height: 100 }
  @State pixelMap?: PixelMap = undefined

  async decodeHdrImage(fileName: Resource) {
    let img = await getContext(this).resourceManager.getMediaContent(fileName)
    let imageSource:image.ImageSource = image.createImageSource(img.buffer.slice(0))

    let options:image.DecodingOptions = {};
    options.index = 0;
    options.desiredDynamicRange = image.DecodingDynamicRange.AUTO; // 为AUTO表示按照图片本身是否为HDR来解码
    imageSource.createPixelMap(options).then((pixelMap) => {
      this.pixelMap = pixelMap
    })
  }

  build() {
    Stack() {
      Column() {
        Button('makePixelMap')
          .width(100)
          .height(100)
          .onClick((event)=>{
            this.decodeHdrImage($r('app.media.cat'))
          })
        Image(this.pixelMap)
          .width(this.s.width)
          .height(this.s.height)
          .objectFit(ImageFit.Contain)
      }
    }
    .width('100%')
    .height('100%')
  }
}