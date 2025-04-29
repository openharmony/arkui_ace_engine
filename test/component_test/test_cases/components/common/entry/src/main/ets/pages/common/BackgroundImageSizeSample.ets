/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import backgroundImageSizeTest from '../MyTest/BackgroundImageSizeTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct BackgroundImageSizeSample {
  imageSizeArr: (SizeOptions | ImageSize)[] = [{ width: '250px', height: '140px' },
    { width: $r('app.string.commonImage_width'), height: $r('app.string.commonImage_height') },
    { width: 1000, height: 500 },
    ImageSize.Auto, ImageSize.Cover, ImageSize.Contain]
  index: number = 0
  @State value: SizeOptions | ImageSize = this.imageSizeArr[this.index]

  aboutToAppear(): void {
    loadComponentTestEntry(backgroundImageSizeTest)
  }

  build() {
    Column({ space: 5 }) {
      Row()
        .width('80%')
        .backgroundImage($r('app.media.app_icon'))
        .backgroundImageSize({ height: '140px' })
        .height(70)
        .id('rowBackgroundImageSize1')
      Row()
        .width('80%')
        .backgroundImage($r('app.media.app_icon'))
        .backgroundImageSize({ width: -1, height: -1 })
        .height(70)
        .id('rowBackgroundImageSize2')
      Column()
        .width('80%')
        .height(150)
        .backgroundImage($r('app.media.app_icon'))
        .backgroundImageSize(this.value)
        .id('columnBackgroundImageSize')
      Button('ButtonBackgroundImageSize')
        .onClick(() => {
          this.index++
          this.value = this.imageSizeArr[this.index % 6]
        })
    }
  }
}


