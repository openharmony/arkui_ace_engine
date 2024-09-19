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
import imageAnimatorDurationTest from '../MyTest/ImageAnimatorDurationTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ImageAnimatorDurationSample {
  @State duration: number = 0

  aboutToAppear(): void {
    loadComponentTestEntry(imageAnimatorDurationTest)
  }

  build() {
    Column({ space: 10 }) {
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
          }
        ])
        .state(AnimationStatus.Running)
        .duration(this.duration)
        .width(200)
        .height(200)
        .id('imageAnimatorDuration')
      Button('ImageAnimatorDuration')
        .onClick(() => {
          this.duration = 1000
        })
    }
  }
}