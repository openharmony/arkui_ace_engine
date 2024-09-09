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
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import imageSpanObjectFitTest from '../MyTest/ImageSpanObjectFitTest'

@Entry
@Component
struct ImageSpanObjectFitSample {
  @State objectFitType: ImageFit = ImageFit.Auto

  aboutToAppear(): void {
    loadComponentTestEntry(imageSpanObjectFitTest)
  }

  build() {
    Column() {
      Text() {
        ImageSpan($r('app.media.startIcon'))
          .objectFit(ImageFit.Contain)
          .width('200px')
          .height('200px')
          .id('imageSpanObjectFit1')
      }

      Text() {
        ImageSpan($r('app.media.startIcon'))
          .objectFit(ImageFit.Cover)
          .width('200px')
          .height('200px')
          .id('imageSpanObjectFit2')
      }

      Text() {
        ImageSpan($r('app.media.startIcon'))
          .objectFit(this.objectFitType)
          .width('200px')
          .height('200px')
          .id('imageSpanObjectFit3')
      }

      Button('ImageSpanObjectFit1')
        .onClick(() => {
          this.objectFitType = ImageFit.Fill
        })
      Button('ImageSpanObjectFit2')
        .onClick(() => {
          this.objectFitType = ImageFit.ScaleDown
        })
      Button('ImageSpanObjectFit3')
        .onClick(() => {
          this.objectFitType = ImageFit.None
        })
    }
  }
}