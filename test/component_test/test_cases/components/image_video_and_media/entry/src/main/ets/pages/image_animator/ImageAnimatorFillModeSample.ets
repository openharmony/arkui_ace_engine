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
import imageAnimatorFillModeTest from '../MyTest/ImageAnimatorFillModeTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ImageAnimatorFillModeSample {
  @State fillMode: FillMode = FillMode.None

  aboutToAppear(): void {
    loadComponentTestEntry(imageAnimatorFillModeTest)
  }

  build() {
    Column() {
      Row() {
        Button('ImageAnimatorFillMode1').onClick(() => {
          this.fillMode = FillMode.Forwards
        })
        Button('ImageAnimatorFillMode2').onClick(() => {
          this.fillMode = FillMode.Backwards
        })
      }

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
        .fillMode(this.fillMode)
        .width(150)
        .height(150)
        .margin(10)
        .id('imageAnimatorFillMode1')

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
        .fillMode(FillMode.Both)
        .width(150)
        .height(150)
        .margin(10)
        .id('imageAnimatorFillMode2')
    }
  }
}