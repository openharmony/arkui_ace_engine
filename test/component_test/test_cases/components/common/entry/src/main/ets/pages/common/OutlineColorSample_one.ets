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

import outlineColorTest_one from '../MyTest/OutlineColorTest_one'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct OutlineColorSample_one {
  @State any_Color: ResourceColor | EdgeColors = {
    left: 0xBFAAFA,
    right: Color.Blue,
    top: 'rgb(255, 201, 0)',
    bottom: $r("app.string.common_color")
  }

  aboutToAppear(): void {
    loadComponentTestEntry(outlineColorTest_one)
  }

  build() {
    Column({ space: 20 }) {
      Text()
      Row() {
        Row({ space: 20 }) {
          Text()
          Menu() {
            MenuItem({ content: "outlineColor", labelInfo: "outlineColor" })
              .outline({ width: 2 })
              .outlineColor(this.any_Color)
              .id('menuItemOutlineColor1')
            MenuItem({ content: "outlineColor", labelInfo: "outlineColor" })
          }
        }
      }
    }
  }
}