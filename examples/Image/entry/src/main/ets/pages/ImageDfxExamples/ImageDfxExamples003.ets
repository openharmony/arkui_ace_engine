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
 * Example 3: Load image from a local file path.
 *
 * - Supports both `file:///` and sandbox-relative paths (under app's storage).
 * - Commonly used for user-generated images (e.g., photos, downloads).
 * - Ensure the file exists and the app has read permission.
 */
@Entry
@Component
struct filePathImageDemo03 {
  // Example local image path in application sandbox
  @State imagePath: string = 'file:///data/storage/el2/base/entry/files/sample.png'

  build() {
    Column() {
      Text('Local File Path Image Example')
        .fontSize(22)
        .margin({ top: 30 })

      Image(this.imagePath)
        .width('50%')
        .height('auto')
        .borderRadius(10)
        .margin({ top: 30 })
        .onComplete(() => {
          console.info('Local file image loaded successfully.')
        })
        .onError((error) => {
          console.error('Failed to load local image: ', JSON.stringify(error))
        })

      Text('Ensure the file path and permissions are valid before loading.')
        .fontSize(16)
        .fontColor('#666')
        .margin({ top: 20 })
    }
    .height('100%')
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
  }
}
