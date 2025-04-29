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

import radialGradientTest_two from '../MyTest/RadialGradientTest_two'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct RadialGradientSample_two {
  @State my_boolean: boolean = true

  aboutToAppear(): void {
    loadComponentTestEntry(radialGradientTest_two)
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
            radius: 60,
            colors: [['rgba(8, 0, 255, 1.00)', 0.0], ['rgba(122, 119, 119, 1.00)', 0.3],
              ['rgba(255, 0, 0, 1.00)', 1.0]],
            repeating: this.my_boolean
          }).id('columnRadialGradient2')

        Button('ButtonRadialGradient1')
          .onClick(() => {
            this.my_boolean = !this.my_boolean;
          })
      }
    }
  }
}
