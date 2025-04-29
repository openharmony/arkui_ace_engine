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

import sphericalEffectTest from '../MyTest/SphericalEffectTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SphericalEffectSample {
  valueArr: number[] = [-1, 0, 0.5, 1, 1.1]
  index: number = 0
  @State value: number = this.valueArr[this.index]

  aboutToAppear(): void {
    loadComponentTestEntry(sphericalEffectTest)
  }

  build() {
    Column() {
      Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Start }) {
        Row({ space: 5 }) {

          Image($r('app.media.app_icon'))
            .sphericalEffect(this.value)
            .id('imageSphericalEffect')
        }.width(400).height(400)

        Button('ButtonSphericalEffect').onClick(() => {
          this.index++
          this.value = this.valueArr[this.index]
        }).width(200).height(50).margin(20)
      }
    }
  }
}