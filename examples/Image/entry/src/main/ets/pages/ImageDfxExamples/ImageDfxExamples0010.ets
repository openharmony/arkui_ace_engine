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
 * Example Collection: Demonstrates multiple Image loading types.
 *
 * Includes:
 *   1. Local resource image ($r)
 *   2. Network image
 *   3. SVG vector image
 *   4. GIF animated image
 *   5. Base64-encoded image
 *   6. Image loading failure
 *
 * All examples share consistent layout and property styles.
 */
import { image } from '@kit.ImageKit'

@Entry
@Component
struct ImageLoadDemoCollection {
  @State selectedIndex: number = 0

  private demoNames: string[] = [
    'Local Resource',
    'Network Image',
    'SVG Image',
    'GIF Animation',
    'Base64 Image',
    'Load Fail Demo'
  ]

  build() {
    Column() {
      // Title section
      Text('Image Load Examples')
        .fontSize(22)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 40, bottom: 20 })

      // Tab bar for selecting demo
      Row({ space: 8 }) {
        ForEach(this.demoNames, (name: string, index: number) => {
          Button(name)
            .backgroundColor(this.selectedIndex === index ? '#007DFF' : '#F2F2F2')
            .fontColor(this.selectedIndex === index ? '#FFFFFF' : '#333333')
            .onClick(() => {
              this.selectedIndex = index
            })
        })
      }
      .padding(10)
      .justifyContent(FlexAlign.Center)

      // Switch displayed demo based on selected index
      if (this.selectedIndex === 0) {
        LocalResourceDemo()
      } else if (this.selectedIndex === 1) {
        NetworkImageDemo()
      } else if (this.selectedIndex === 2) {
        SvgImageDemo()
      } else if (this.selectedIndex === 3) {
        GifImageDemo()
      } else if (this.selectedIndex === 4) {
        Base64ImageDemo()
      } else {
        LoadFailDemo()
      }
    }
    .alignItems(HorizontalAlign.Center)
    .height('100%')
  }
}

/**
 * Demo 1: Load image from app resource using `$r`
 */
@Component
struct LocalResourceDemo {
  build() {
    Column() {
      Text('Local resource image ($r)')
        .fontSize(18)
        .margin({ top: 30 })

      Image($r('app.media.img_1'))
        .width(200)
        .height(200)
        .margin({ top: 20 })
    }
  }
}

/**
 * Demo 2: Load image from network URL
 */
@Component
struct NetworkImageDemo {
  @State url: string = 'https://xxx.jpg'
  @State reloadKey: number = 0

  build() {
    Column() {
      Text('Network image loading')
        .fontSize(18)
        .margin({ top: 30 })

      Image(this.url + '?v=' + this.reloadKey)
        .width(200)
        .height(200)
        .objectFit(ImageFit.Cover)
        .margin({ top: 20 })

      Button('Reload Image')
        .margin({ top: 20 })
        .onClick(() => {
          this.reloadKey++
        })
    }
  }
}

/**
 * Demo 3: Display SVG image
 */
@Component
struct SvgImageDemo {
  @State fillColor: string = '#007DFF'

  build() {
    Column() {
      Text('SVG image demo')
        .fontSize(18)
        .margin({ top: 30 })

      Image($r('app.media.icon_svg'))
        .width(150)
        .height(150)
        .fillColor(this.fillColor)
        .margin({ top: 20 })

      Button('Toggle Fill Color')
        .margin({ top: 20 })
        .onClick(() => {
          animateTo({}, () => {
            this.fillColor = this.fillColor === '#007DFF' ? '#FF3B30' : '#007DFF'
          })
        })
    }
  }
}

/**
 * Demo 4: Display GIF animation
 */
@Component
struct GifImageDemo {
  build() {
    Column() {
      Text('GIF animation demo')
        .fontSize(18)
        .margin({ top: 30 })

      Image($r('app.media.loading_gif'))
        .width(200)
        .height(200)
        .margin({ top: 20 })
        .alt('GIF load failed')
    }
  }
}

/**
 * Demo 5: Display Base64-encoded image
 */
@Component
struct Base64ImageDemo {
  // Example base64-encoded small red square (PNG)
  private base64Data: string =
    'data:image/png;base64,xxx'

  build() {
    Column() {
      Text('Base64-encoded image')
        .fontSize(18)
        .margin({ top: 30 })

      Image(this.base64Data)
        .width(150)
        .height(150)
        .margin({ top: 20 })
    }
  }
}

/**
 * Demo 6: Simulate image loading failure
 */
@Component
struct LoadFailDemo {
  @State showError: boolean = false

  build() {
    Column() {
      Text('Image loading failure demo')
        .fontSize(18)
        .margin({ top: 30 })

      if (!this.showError) {
        Image('https://xxx.png')
          .width(200)
          .height(200)
          .alt('Load failed')
          .margin({ top: 20 })
      } else {
        Text('Image load failed')
          .fontSize(18)
          .fontColor('#FF3B30')
          .margin({ top: 100 })
      }

      Button(this.showError ? 'Retry' : 'Simulate Failure')
        .margin({ top: 20 })
        .onClick(() => {
          this.showError = !this.showError
        })
    }
  }
}
