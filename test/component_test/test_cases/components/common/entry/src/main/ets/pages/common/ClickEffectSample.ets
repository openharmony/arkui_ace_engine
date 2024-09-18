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

import clickEffectTest from '../MyTest/ClickEffectTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ClickEffectSample {
  @State clickEffectLevel: ClickEffectLevel | number[] =
    [1, ClickEffectLevel.LIGHT, ClickEffectLevel.MIDDLE, ClickEffectLevel.HEAVY]
  index: number = 0;
  @State anyClickEffectLevel: ClickEffectLevel | number = this.clickEffectLevel[this.index]

  aboutToAppear(): void {
    loadComponentTestEntry(clickEffectTest)
  }

  build() {
    Column() {
      Menu() {
        MenuItem({ content: "复制", labelInfo: "Ctrl+C" })
        MenuItem({ content: "粘贴", labelInfo: "Ctrl+V" })
      }
      .id('menuClickEffect1')
      .clickEffect(undefined)

      Menu() {
        MenuItem({ content: "复制", labelInfo: "Ctrl+C" })
        MenuItem({ content: "粘贴", labelInfo: "Ctrl+V" })
      }
      .id('menuClickEffect2')
      .clickEffect({ level: this.anyClickEffectLevel })

      Button('ButtonClickEffect1')
        .onClick(() => {
          this.index += 1
          this.anyClickEffectLevel = this.clickEffectLevel[this.index % 5]
        })
    }
  }
}