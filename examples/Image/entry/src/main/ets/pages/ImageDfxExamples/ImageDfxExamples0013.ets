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
 * 多资源类型 Image Demo（Button 切换 + 固定尺寸）
 * PixelMap / Base64 / SVG / GIF / 网络图片
 */
import image from '@ohos.multimedia.image'

@Entry
@Component
struct MultiImageDemoFixedSize {
  // 当前选中资源索引：0=PixelMap, 1=Base64, 2=SVG, 3=GIF, 4=Network
  @State selectedIndex: number = 0

  // PixelMap 示例
  @State pixmap: image.PixelMap | undefined = undefined

  // Base64 示例
  private base64Data: string =
    'data:image/png;base64,xxx'

  // SVG 资源
  private svgResource = $r('app.media.sample_svg')

  // GIF 本地资源
  private gifResource = $r('app.media.sample_gif')

  // 网络图片 URL
  private netImageUrl = 'https://xxx.png'

  aboutToAppear(): void {
    // PixelMap 加载（本地资源）
    const uint8 = getContext(this).resourceManager.getMediaContentSync($r('app.media.local_image'))
    const imageSource = image.createImageSource(uint8.buffer)
    this.pixmap = imageSource.createPixelMapSync()
    imageSource?.release()
  }

  build() {
    Column() {
      Text('多资源类型 Image Demo（Button 切换 + 固定尺寸）')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      // 按钮行
      Row() {
        Button('PixelMap').onClick(() => { this.selectedIndex = 0 })
        Button('Base64').onClick(() => { this.selectedIndex = 1 })
        Button('SVG').onClick(() => { this.selectedIndex = 2 })
        Button('GIF').onClick(() => { this.selectedIndex = 3 })
        Button('Network').onClick(() => { this.selectedIndex = 4 })
      }
      .justifyContent(FlexAlign.SpaceAround)
      .margin({ bottom: 20 })

      // Image 显示区
      Column() {
        if (this.selectedIndex === 0 && this.pixmap) {
          Image(this.pixmap)
            .width(120)
            .height(120)
            .borderRadius(8)
        } else if (this.selectedIndex === 1) {
          Image(this.base64Data)
            .width(120)
            .height(120)
            .borderRadius(8)
        } else if (this.selectedIndex === 2) {
          Image(this.svgResource)
            .width(120)
            .height(120)
        } else if (this.selectedIndex === 3) {
          Image(this.gifResource)
            .width(120)
            .height(120)
        } else if (this.selectedIndex === 4) {
          Image(this.netImageUrl)
            .width(120)
            .height(120)
        }
      }
      .alignItems(HorizontalAlign.Center)
      .justifyContent(FlexAlign.Center)
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
