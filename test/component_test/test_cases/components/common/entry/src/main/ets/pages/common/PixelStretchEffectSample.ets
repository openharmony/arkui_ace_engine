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

import pixelStretchEffectTest from '../MyTest/PixelStretchEffectTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct PixelStretchEffectSample {
  @State value: Length[] = ['100px', 50, $r('app.string.common_breadth')];
  @State index: number = 0
  @State pixelStretch: PixelStretchEffectOptions = {
    top: this.value[this.index],
    left: this.value[this.index],
    right: this.value[this.index],
    bottom: this.value[this.index]
  }

  aboutToAppear(): void {
    loadComponentTestEntry(pixelStretchEffectTest)
  }

  build() {
    Column({ space: 100 }) {
      Text('This is the text content with letterSpacing 0.')
        .id('textPixelStretchEffect')
        .clip(false)
        .border({ width: 1 })
        .pixelStretchEffect(this.pixelStretch)
        .margin({ top: 100 })
      Button('ButtonPixelStretchEffect').onClick(() => {
        this.index++
        this.pixelStretch = {
          top: this.value[this.index % 3],
          left: this.value[this.index % 3],
          right: this.value[this.index % 3],
          bottom: this.value[this.index % 3]
        }
      })
    }
  }
}