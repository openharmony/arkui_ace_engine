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
 * Purpose: This example demonstrates how to create an ArkTS component that allows dynamic modification of
 * image attributes.
 *
 * It includes controls for toggling image visibility, adjusting dynamic range mode, resolution quality,
 * render mode, and opacity. The 'opacity' property is used to control the transparency of the image.
 */
import { BusinessError } from '@ohos.base';
import image from '@ohos.multimedia.image';

class ImageModifier implements AttributeModifier<ImageAttribute> {
  public value: DynamicRangeMode = DynamicRangeMode.HIGH
  public bo: number = 10
  public qulity: image.ResolutionQuality = image.ResolutionQuality.MEDIUM

  applyNormalAttribute(instance: ImageAttribute): void {
    instance.dynamicRangeMode(this.value)
    instance.borderRadius(this.bo)
    instance.enhancedImageQuality(this.qulity)
  }
}

@Entry
@Component
struct DarkModeTest {
  @State modifier: ImageModifier = new ImageModifier()
  @State show: Boolean = true
  @State het: number = 216
  @State wid: number = 384
  @State opacityValue: number = 0.4
  @State parmDynamicRangeModeStr: string[] = [
    'dynamicRangeMode = HIGH', 'dynamicRangeMode = CONSTRAINT', 'dynamicRangeMode = STANDARD'
  ]
  @State parmImageQualityStr: string[] = [
    'ResolutionQuality.LOW', 'ResolutionQuality.MEDIUM', 'ResolutionQuality.HIGH'
  ]
  @State parmRenderModeStr: string[] = [
    'ImageRenderMode.Origin', 'ImageRenderMode.Template'
  ]
  @State parmDynamicRangeMode: DynamicRangeMode[] = [
    DynamicRangeMode.HIGH, DynamicRangeMode.CONSTRAINT, DynamicRangeMode.STANDARD
  ]
  @State parmImageQuality: image.ResolutionQuality[] = [
    image.ResolutionQuality.LOW, image.ResolutionQuality.MEDIUM, image.ResolutionQuality.HIGH
  ]
  @State parmRenderMode: ImageRenderMode[] = [
    ImageRenderMode.Original, ImageRenderMode.Template
  ]
  @State parm: DynamicRangeMode | undefined | number = DynamicRangeMode.HIGH
  @State idx1: number = 0
  @State idx2: number = 0
  @State idx3: number = 0

  build() {
    Column() {
      Button('IsShow')
        .onClick(() => {
          if (this.show) {
            this.show = false;
          } else {
            this.show = true;
          }
        })
      Divider()
      Button('Change idx_DynamicRangeMode++ = ' + this.idx1)
        .onClick(() => {
          this.idx1 = (this.idx1 + 1) % 3
        })
      Divider()
      Button('Change idx_ResolutionQuality++ = ' + this.idx2)
        .onClick(() => {
          this.idx2 = (this.idx2 + 1) % 3
        })
      Divider()
      Button('Change idx_ImageRenderMode++ = ' + this.idx3)
        .onClick(() => {
          this.idx3 = (this.idx3 + 1) % 2
        })
      Divider()
      Button('add opacity +0.1 ')
        .onClick(() => {
          this.opacityValue = this.opacityValue + 0.1
        })
      if (this.show) {
        Divider()
        Text(this.parmDynamicRangeModeStr[this.idx1])
          .fontWeight(FontWeight.Bolder)
        Divider()
        Text(this.parmImageQualityStr[this.idx2])
          .fontWeight(FontWeight.Bolder)
        Divider()
        Text(this.parmRenderModeStr[this.idx3])
          .fontWeight(FontWeight.Bolder)
        Divider()
        Image($r('app.media.JPEGVividSingle'))
          .height(this.het)
          .width(this.wid)
          .alt($r('app.media.JPEGISOSingle'))
          .dynamicRangeMode(this.parmDynamicRangeMode[this.idx1])
          .enhancedImageQuality(this.parmImageQuality[this.idx2])
          .opacity(this.opacityValue)
      }
    }.backgroundColor('#CCCCCC').width('100%').height('100%')
  }
}