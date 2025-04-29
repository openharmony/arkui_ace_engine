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

import outlineRadiusTest from '../MyTest/OutlineRadiusTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct OutlineRadiusSample {
  @State any_Radius: Dimension | OutlineRadiuses = {
    topLeft: 20,
    topRight: '40vp',
    bottomLeft: $r("app.string.common_value_two"),
    bottomRight: 20
  }

  aboutToAppear(): void {
    loadComponentTestEntry(outlineRadiusTest)
  }

  build() {
    Column({ space: 50 }) {
      Text('textOutlineRadius1')
        .outlineRadius(this.any_Radius)
        .id('textOutlineRadius1')

      Button('ButtonOutlineRadius1')
        .onClick(() => {
          this.any_Radius = '10.00vp'
        })
      Button('ButtonOutlineRadius2')
        .onClick(() => {
          this.any_Radius = 60
        })

    }
  }
}