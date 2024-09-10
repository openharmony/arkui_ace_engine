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

import bindPopupTest_nine from '../MyTest/BindPopupTest_nine'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct BindPopupSample_nine {
  @State my_boolean: boolean = true
  @State any_boolean: boolean = true
  @State onStateChange_boolean: boolean = true
  @State my_shadow: ShadowOptions | ShadowStyle = ShadowStyle.OUTER_DEFAULT_XS
  @State shadow_1: ShadowOptions = {
    radius: 10,
    type: ShadowType.COLOR,
    color: Color.Blue,
    offsetX: 1,
    offsetY: 1,
    fill: true
  }

  @Builder
  popupBuilder() {
    Row({ space: 2 }) {
      Image($r("app.media.app_icon")).width(24).height(24)
      Text('CustomPopup').fontSize(10)
    }.width(100).height(50)
  }

  aboutToAppear(): void {
    loadComponentTestEntry(bindPopupTest_nine)
  }

  build() {
    Column({ space: 20 }) {

      Button('ButtonBindPopup1')
        .onClick(() => {
          this.my_boolean = !this.my_boolean
        })
        .bindPopup(this.my_boolean, {
          builder: this.popupBuilder,
          mask: { color: Color.Green },
          arrowHeight: '10px',
          radius: '10px',
          shadow: this.my_shadow,
          backgroundBlurStyle: BlurStyle.BACKGROUND_REGULAR,
          focusable: this.any_boolean
        }).id('buttonBindPopup9')

      Button('ButtonBindPopup2')
        .onClick(() => {
          this.any_boolean = !this.any_boolean
          this.my_shadow = this.shadow_1
        })
    }
  }
}