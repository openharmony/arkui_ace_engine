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
 * Example: `hdrBrightnessDemo04`
 * Demonstrates two dynamic adjustment scenarios using `hdrBrightness`:
 *   1. Cycles through a list of values including invalid/null/undefined
 *   2. Dynamically toggles brightness between 0 <-> 0.5 and 0.5 <-> 1.0
 *
 * ⚠️ Note: The `hdrBrightness` property only works with HDR images.
 */

import { image } from '@kit.ImageKit'

// Modifier #1: cycles through brightness values, including invalid/null/undefined
class CyclingBrightnessModifier implements AttributeModifier<ImageAttribute> {
  public brightArray: (number | null | undefined)[] = [-1, 1, 0.3, 0.8, 0, null, undefined]
  public index: number = 0

  applyNormalAttribute(instance: ImageAttribute): void {
    instance.hdrBrightness(this.brightArray[this.index])
  }

  getCurrentLabel(): string {
    let val = this.brightArray[this.index]
    return (val === null || val === undefined) ? String(val) : val.toFixed(2)
  }

  next(): void {
    this.index = (this.index + 1) % this.brightArray.length
  }
}

// Modifier #2: toggles brightness between 0, 0.5, and 1.0
class FixedBrightnessModifier implements AttributeModifier<ImageAttribute> {
  public bright: number = 0

  applyNormalAttribute(instance: ImageAttribute): void {
    instance.hdrBrightness(this.bright)
  }

  toggleToHalf(): void {
    this.bright = 0.5 - this.bright
  }

  toggleToFull(): void {
    this.bright = 1.5 - this.bright
  }
}

@Entry
@Component
struct hdrBrightnessDemo04 {
  @State imageUrl: string = 'img_1'
  @State modifier1: FixedBrightnessModifier = new FixedBrightnessModifier()
  @State modifier2: CyclingBrightnessModifier = new CyclingBrightnessModifier()

  aboutToAppear(): void {
    // Check HDR capability
    let img = getContext().resourceManager.getMediaByNameSync(this.imageUrl)
    let imageSource = image.createImageSource(img.buffer.slice(0))
    let imageInfo = imageSource.getImageInfoSync()
    if (!imageInfo) {
      console.error('Failed to obtain the image information')
    } else {
      console.info('imageInfo.isHdr: ' + imageInfo.isHdr)
    }
  }

  build() {
    Column({ space: 20 }) {
      // Section 1: Cycling brightness (including invalid/null/undefined)
      Text('Modifier #1: Cycling Brightness')
        .fontSize(18).fontWeight(FontWeight.Bold)

      Image($r('app.media.img_1'))
        .width('50%')
        .height('auto')
        .attributeModifier(this.modifier2)

      Button('Next Brightness: ' + this.modifier2.getCurrentLabel())
        .onClick(() => {
          animateTo({}, () => {
            this.modifier2.next()
          })
        })

      Divider()

      // Section 2: Fixed toggling brightness
      Text('Modifier #2: Toggle Between Levels')
        .fontSize(18).fontWeight(FontWeight.Bold)

      Image($r('app.media.img_1'))
        .width('60%')
        .height('auto')
        .attributeModifier(this.modifier1)

      Row({ space: 12 }) {
        Button('Toggle 0 ↔ 0.5')
          .onClick(() => {
            animateTo({}, () => {
              this.modifier1.toggleToHalf()
            })
          })

        Button('Toggle 0.5 ↔ 1.0')
          .onClick(() => {
            animateTo({}, () => {
              this.modifier1.toggleToFull()
            })
          })
      }
    }
    .height('100%')
    .align(Alignment.Top)
    .padding(20)
  }
}
