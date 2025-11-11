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
 * Example 5: Demonstrate image loading failure handling.
 *
 * - This case intentionally uses an invalid URL to trigger the onError callback.
 * - The developer can use `onError` to show fallback content, retry logic, or user hint.
 * - Both `onError` and `onComplete` callbacks help track loading results.
 */
@Entry
@Component
struct imageLoadFailDemo05 {
  // Invalid URL to trigger a load failure
  @State brokenUrl: string = 'https://xxx.png'

  build() {
    Column() {
      Text('Image Load Fail Example')
        .fontSize(22)
        .margin({ top: 30 })

      Image(this.brokenUrl)
        .width('60%')
        .height('auto')
        .margin({ top: 40 })
        .borderRadius(8)
        // This will not be called since the image does not exist
        .onComplete(() => {
          console.info('Unexpected: broken image loaded successfully.')
        })
        // The expected callback path for load failure
        .onError((error) => {
          console.error('Expected failure: ', JSON.stringify(error))
        })

      Text('→ This example intentionally demonstrates load error handling.')
        .fontSize(16)
        .fontColor('#666')
        .margin({ top: 20 })
    }
    .height('100%')
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
  }
}
