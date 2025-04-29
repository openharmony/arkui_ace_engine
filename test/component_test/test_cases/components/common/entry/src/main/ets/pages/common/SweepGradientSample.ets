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

import sweepGradientTest from '../MyTest/SweepGradientTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SweepGradientSample {
  @State any_Colors: Array<[ResourceColor, number]> =
    [[$r("app.string.common_color"), 0.0], [$r("app.string.common_color"), 0.3], [$r("app.string.common_color"), 1.0]]
  @State any_start: number | string = '6'
  @State any_end: number | string = '6'
  @State any_rotation: number | string = '6'
  @State my_boolean: boolean = true

  aboutToAppear(): void {
    loadComponentTestEntry(sweepGradientTest)
  }

  build() {
    Column({ space: 5 }) {
      Row({ space: 5 }) {
        Column()
          .width(150)
          .height(200)
          .sweepGradient({
            center: [50, 50],
            start: this.any_start,
            end: this.any_end,
            rotation: this.any_rotation,
            colors: this.any_Colors,
            repeating: this.my_boolean
          }).id('columnSweepGradient1')

        Button('ButtonSweepGradient1').onClick(() => {
          this.any_Colors =
            [['rgba(8, 0, 255, 1.00)', 0.0], ['rgba(122, 119, 119, 1.00)', 0.3], ['rgba(255, 0, 0, 1.00)', 1.0]]
          this.my_boolean = !this.my_boolean;
          this.any_start = 6
          this.any_end = 6
          this.any_rotation = 6
        })

        Button('ButtonSweepGradient2').onClick(() => {
          this.any_Colors = [[0xffaaaa, 0.0], [0xaaaaff, 0.3], [0xf1111f, 1.0]]
          this.my_boolean = !this.my_boolean;
          this.any_start = '6'
          this.any_end = '6'
          this.any_rotation = '6'
        })

        Button('ButtonSweepGradient3').onClick(() => {
          this.any_Colors = [[Color.Blue, 0.0], [Color.Green, 0.3], [Color.Pink, 1.0]]
          this.my_boolean = !this.my_boolean;
          this.any_start = -6
          this.any_end = -6
          this.any_rotation = -6
        })
      }
    }
  }
}