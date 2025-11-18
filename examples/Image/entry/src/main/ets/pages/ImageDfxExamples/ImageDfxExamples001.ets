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
 * Example: Load and display a network image.
 * 
 * This demonstrates loading an image from an HTTP/HTTPS URL.
 * Ensure that the network permission is enabled in the application configuration.
 */
@Entry
@Component
struct networkImageDemo01 {
  @State imageUrl: string = 'https://xxx.jpg'

  build() {
    Column() {
      Text('Network Image Example')
        .fontSize(22)
        .margin({ top: 30 })

      Image(this.imageUrl)
        .width('60%')
        .height('auto')
        .margin({ top: 30 })
        .borderRadius(12)
        .onComplete(() => {
          console.info('Network image loaded successfully.')
        })
        .onError((error) => {
          console.error('Failed to load network image: ', JSON.stringify(error))
        })
    }
    .height('100%')
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
  }
}
