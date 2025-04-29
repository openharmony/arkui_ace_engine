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
import imageAnimatorIterationTest from '../MyTest/ImageAnimatorIterationTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ImageAnimatorIterationsSample {
  @State iterations: number = 2

  aboutToAppear(): void {
    loadComponentTestEntry(imageAnimatorIterationTest)
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
        .iterations(this.iterations)
        .width(500)
        .height(500)
        .margin(15)
        .id('imageAnimatorIterations')
      Button('ImageAnimatorIterations')
        .onClick(() => {
          this.iterations = -1
        })
    }
  }
}