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
import imageAnimatorImagesTest from '../MyTest/ImageAnimatorImagesTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ImageAnimatorImagesSample {
  @State images: Array<ImageFrameInfo> = [{
    src: 'pages/imageAnimator/imageAnimator_one.png',
    width: '200px',
    height: '200px',
    top: '10px',
    left: '10px',
    duration: 2000
  }]

  aboutToAppear(): void {
    loadComponentTestEntry(imageAnimatorImagesTest)
  }

  build() {
    Column() {
      Button('ImageAnimatorImages')
        .onClick(() => {
          this.images = [{
            src: $r('app.media.city_icon'),
            width: 400,
            height: 200,
            top: 10,
            left: 10,
            duration: 2000
          }]
        })
      ImageAnimator()
        .images(this.images)
        .fixedSize(false)
        .width(500)
        .height(500)
        .id('imageAnimatorImages')
    }
  }
}