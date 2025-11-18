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
 * Example: Demonstrates displaying a GIF image from a network URL.
 *
 * The `Image` component supports automatic network loading.
 * This example shows a simple loading animation and a reload button on failure.
 */
@Entry
@Component
struct gifNetworkDemo01 {
  // GIF URL (should be accessible)
  @State gifUrl: string = 'https://xxx.gif'

  // Track loading state
  @State isLoading: boolean = true
  @State hasError: boolean = false

  onAppear() {
    // Simulate a loading delay for demonstration
    setTimeout(() => {
      this.isLoading = false
      this.hasError = false
    }, 1000)
  }

  build() {
    Column() {
      if (this.isLoading) {
        // Loading placeholder
        Text('Loading GIF...')
          .fontSize(18)
          .margin({ top: 100 })
      } else if (this.hasError) {
        // Error placeholder
        Text('Failed to load GIF')
          .fontSize(18)
          .fontColor('#FF3B30')
          .margin({ top: 100 })
      } else {
        // Display the GIF image
        Image(this.gifUrl)
          .width(200)
          .height(200)
          .margin({ top: 80 })
      }

      // Reload button
      Button('Reload')
        .margin({ top: 20 })
        .onClick(() => {
          this.isLoading = true
          this.hasError = false
          this.onAppear()
        })
    }
    .alignItems(HorizontalAlign.Center)
    .height('100%')
  }
}
