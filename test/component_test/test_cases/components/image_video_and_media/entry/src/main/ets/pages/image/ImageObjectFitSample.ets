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
import imageObjectFitTest from '../MyTest/ImageObjectFitTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ImageObjectFitSample {
  @State objectFitImageFit: ImageFit = ImageFit.Auto

  aboutToAppear(): void {
    loadComponentTestEntry(imageObjectFitTest)
  }

  build() {
    Column() {
      Row() {
        Button('ImageObjectFit1')
          .onClick(() => {
            this.objectFitImageFit = ImageFit.Fill
          })
        Button('ImageObjectFit2')
          .onClick(() => {
            this.objectFitImageFit = ImageFit.None
          })
        Button('ImageObjectFit3')
          .onClick(() => {
            this.objectFitImageFit = ImageFit.Contain
          })
      }

      Button('ImageObjectFit4')
        .onClick(() => {
          this.objectFitImageFit = ImageFit.ScaleDown
        })
      Button('ImageObjectFit5')
        .onClick(() => {
          this.objectFitImageFit = ImageFit.Cover
        })
      Image($r('app.media.test_image'))
        .objectFit(this.objectFitImageFit)
        .id('imageObjectFit')
    }
  }
}