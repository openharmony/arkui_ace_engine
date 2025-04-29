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
//测试代码路径
import imageInterpolationTest from '../MyTest/ImageInterpolationTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ImageInterpolationSample {
  @State interpolation: ImageInterpolation = ImageInterpolation.None

  aboutToAppear(): void {
    loadComponentTestEntry(imageInterpolationTest)
  }

  build() {
    Column() {
      Button('ImageInterpolation1')
        .onClick(() => {
          this.interpolation = ImageInterpolation.Low
        })
      Button('ImageInterpolation2')
        .onClick(() => {
          this.interpolation = ImageInterpolation.Medium
        })
      Button('ImageInterpolation3')
        .onClick(() => {
          this.interpolation = ImageInterpolation.High
        })
      Image($r('app.media.test_image'))
        .width(100)
        .height(100)
        .margin(5)
        .interpolation(this.interpolation)
        .id('imageInterpolation')
    }
  }
}