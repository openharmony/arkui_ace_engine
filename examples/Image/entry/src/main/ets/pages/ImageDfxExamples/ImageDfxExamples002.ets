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
 * Example 2: Load image from application resources using `$r('app.media.xxx')`.
 *
 * - `$r` references images stored in the `resources/base/media/` directory.
 * - The image is packaged into the application and decoded directly from resource memory.
 * - This method is the most efficient and stable for bundled media.
 */
@Entry
@Component
struct resourceImageDemo02 {
  build() {
    Column() {
      Text('Resource Image Example')
        .fontSize(22)
        .margin({ top: 30 })

      // $r references a static resource defined in media resources
      Image($r('app.media.img_logo'))
        .width('40%')
        .height('auto')
        .margin({ top: 40 })
        .borderRadius(10)
        .onComplete(() => {
          console.info('Resource image loaded successfully.')
        })
        .onError((error) => {
          console.error('Failed to load resource image: ', JSON.stringify(error))
        })

      Text('Resource-based images are loaded from the app package directly.')
        .fontSize(16)
        .fontColor('#666')
        .margin({ top: 20 })
    }
    .height('100%')
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
  }
}
