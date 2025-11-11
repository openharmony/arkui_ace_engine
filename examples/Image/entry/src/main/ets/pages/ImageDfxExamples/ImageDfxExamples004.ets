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
/*
 * Example 4: Display an image from a Base64-encoded data string.
 *
 * - The Base64 format is useful for dynamically generated or inline images.
 * - The string must include the MIME type prefix, e.g.:
 *   'data:image/png;base64,xxxxx...'
 * - Decoding occurs in-memory, no file I/O involved.
 */
@Entry
@Component
struct base64ImageDemo04 {
  // Sample 1x1 transparent PNG Base64 string
  @State base64Img: string = 'data:image/png;base64,xxx'

  build() {
    Column() {
      Text('Base64 Image Example')
        .fontSize(22)
        .margin({ top: 30 })

      // The Image component recognizes and decodes the Base64 string automatically
      Image(this.base64Img)
        .width(150)
        .height(150)
        .borderRadius(8)
        .margin({ top: 40 })
        .onComplete(() => {
          console.info('Base64 image rendered successfully.')
        })
        .onError((error) => {
          console.error('Failed to render Base64 image: ', JSON.stringify(error))
        })

      Text('Base64 images are decoded in memory without file access.')
        .fontSize(16)
        .fontColor('#666')
        .margin({ top: 20 })
    }
    .height('100%')
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
  }
}
