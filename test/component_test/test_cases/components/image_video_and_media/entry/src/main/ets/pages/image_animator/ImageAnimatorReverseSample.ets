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
import imageAnimatorReverseTest from '../MyTest/ImageAnimatorReverseTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ImageAnimatorReverseSample {
  @State reverse: boolean = true

  aboutToAppear(): void {
    loadComponentTestEntry(imageAnimatorReverseTest)
  }

  build() {
    Column() {
      Button('ImageAnimatorReverse1')
        .onClick(() => {
          this.reverse = !this.reverse
        })
      ImageAnimator()
        .images([
          {
            src: $r('app.media.test_image')
          },
          {
            src: $r('app.media.test_icon')
          },
          {
            src: $r('app.media.run_icon')
          },
          {
            src: $r('app.media.city_icon')
          }
        ])
        .state(AnimationStatus.Running)
        .reverse(this.reverse)
        .width(200)
        .height(300)
        .margin(15)
        .id('imageAnimatorReverse')
    }
  }
}