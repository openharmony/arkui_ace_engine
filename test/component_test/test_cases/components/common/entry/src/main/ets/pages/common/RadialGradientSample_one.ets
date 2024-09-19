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

import radialGradientTest_one from '../MyTest/RadialGradientTest_one'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct RadialGradientSample_one {
  @State my_boolean: boolean = true
  @State any_Radius: number | string = -15
  @State any_Colors: Array<[ResourceColor, number]> =
    [[$r("app.string.common_color"), 0.0], [$r("app.string.common_color"), 0.3], [$r("app.string.common_color"), 1.0]]

  aboutToAppear(): void {
    loadComponentTestEntry(radialGradientTest_one)
  }

  build() {
    Column({ space: 5 }) {
      Text()
      Row({ space: 5 }) {
        Text()
        Column()
          .width(150)
          .height(200)
          .radialGradient({
            center: [50, 50],
            radius: this.any_Radius,
            colors: this.any_Colors,
            repeating: this.my_boolean
          }).id('columnRadialGradient1')

        Button('ButtonRadialGradient1')
          .onClick(() => {
            this.my_boolean = !this.my_boolean;
            this.any_Colors = [[0xffaaaa, 0.0], [Color.Green, 0.3], [Color.Pink, 1.0]]
            this.any_Radius = '60'
          })
      }
    }
  }
}
