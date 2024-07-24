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

import bindPopupTest_eight from '../MyTest/BindPopupTest_eight'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct BindPopupSample_eight {
  @State my_boolean: boolean = true

  @Builder
  popupBuilder() {
    Row({ space: 2 }) {
      Image($r("app.media.app_icon")).width(24).height(24)
      Text('CustomPopup').fontSize(10)
    }.width(100).height(50)
  }

  aboutToAppear(): void {
    loadComponentTestEntry(bindPopupTest_eight)
  }

  build() {
    Column({ space: 20 }) {

      Button('ButtonBindPopup')
        .onClick(() => {
          this.my_boolean = !this.my_boolean
        })
        .bindPopup(this.my_boolean, {
          builder: this.popupBuilder,
          mask: { color: Color.Green },
          width: '10px',
          arrowPointPosition: ArrowPointPosition.START,
          arrowWidth: '10px'
        }).id('buttonBindPopup8')
    }
  }
}