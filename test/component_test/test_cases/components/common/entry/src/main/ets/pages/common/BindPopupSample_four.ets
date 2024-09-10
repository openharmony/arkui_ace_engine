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

import bindPopupTest_four from '../MyTest/BindPopupTest_four'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct BindPopupSample_four {
  @State my_boolean: boolean = true
  @State my_shadow: ShadowOptions | ShadowStyle = ShadowStyle.OUTER_DEFAULT_XS
  @State shadow_1: ShadowOptions = {
    radius: 10,
    type: ShadowType.COLOR,
    color: Color.Blue,
    offsetX: 1,
    offsetY: 1,
    fill: true
  }

  aboutToAppear(): void {
    loadComponentTestEntry(bindPopupTest_four)
  }

  build() {
    Column({ space: 20 }) {

      Button('ButtonBindPopup1')
        .onClick(() => {
          this.my_boolean = !this.my_boolean
        })
        .bindPopup(this.my_boolean, {
          message: "bindPopup",
          radius: '30px',
          shadow: this.my_shadow,
          backgroundBlurStyle: BlurStyle.BACKGROUND_THIN,
          arrowHeight: '100px'
        }).id('buttonBindPopup4')

      Button('ButtonBindPopup2').onClick(() => {
        this.my_shadow = this.shadow_1
      })
    }
  }
}