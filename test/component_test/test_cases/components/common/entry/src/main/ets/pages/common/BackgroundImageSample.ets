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

import backgroundImageTest from '../MyTest/BackgroundImageTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct BackgroundImageSample {
  index: number = 0
  resourceStrArr: ResourceStr[] = ['../../../resources/base/media/b.jpg', $r('app.media.app_icon')]
  imageRepeatArr: ImageRepeat[] = [ImageRepeat.NoRepeat, ImageRepeat.X, ImageRepeat.Y, ImageRepeat.XY]
  @State resourceStr: ResourceStr = this.resourceStrArr[this.index]
  @State imageRepeat: ImageRepeat = this.imageRepeatArr[this.index]

  aboutToAppear(): void {
    loadComponentTestEntry(backgroundImageTest)
  }

  build() {
    Column() {
      Row()
        .backgroundImage(this.resourceStr, this.imageRepeat)
        .backgroundImageSize({ width: '250px', height: '140px ' })
        .width('90%')
        .height(500)
        .border({ width: 1 })
        .id('rowBackgroundImage')

      Button('ButtonBackgroundImage').onClick(() => {
        this.index++
        this.resourceStr = this.resourceStrArr[this.index % 2]
        this.imageRepeat = this.imageRepeatArr[this.index % 4]
      })
    }
  }
}