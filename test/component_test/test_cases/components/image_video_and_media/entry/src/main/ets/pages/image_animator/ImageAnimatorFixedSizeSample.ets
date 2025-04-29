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
import imageAnimatorFixedSizeTest from '../MyTest/ImageAnimatorFixedSizeTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ImageAnimatorFixedSizeSample {
  @State fixedSize: boolean = true

  aboutToAppear(): void {
    loadComponentTestEntry(imageAnimatorFixedSizeTest)
  }

  build() {
    Column() {
      Button('ImageAnimatorFixedSize1')
        .onClick(() => {
          this.fixedSize = !this.fixedSize
        })
      ImageAnimator()
        .images([
          {
            src: $r('app.media.test_image'),
            width: 100,
            height: 100,
            top: 10,
            left: 10
          },
          {
            src: $r('app.media.test_icon'),
            width: 200,
            height: 100,
            top: 15,
            left: 15
          },
          {
            src: $r('app.media.run_icon'),
            width: 300,
            height: 100,
            top: 20,
            left: 20
          }
        ])
        .state(AnimationStatus.Running)
        .fixedSize(this.fixedSize)
        .id('imageAnimatorFixedSize')
    }
  }
}