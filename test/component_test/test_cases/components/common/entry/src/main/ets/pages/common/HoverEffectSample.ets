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

import hoverEffectTest from '../MyTest/HoverEffectTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct HoverEffectSample {
  hoverEffectTypeArr: HoverEffect[] = [HoverEffect.Auto, HoverEffect.Scale, HoverEffect.Highlight, HoverEffect.None]
  index: number = 0
  @State hoverEffectType: HoverEffect = this.hoverEffectTypeArr[this.index]

  aboutToAppear(): void {
    loadComponentTestEntry(hoverEffectTest)
  }

  build() {
    Column({ space: 5 }) {
      Column()
        .width('80%')
        .height(200)
        .backgroundColor(Color.Gray)
        .hoverEffect(this.hoverEffectType)
        .id('columnHoverEffect')
      Button('ButtonHoverEffect')
        .onClick(() => {
          this.index++
          this.hoverEffectType = this.hoverEffectTypeArr[this.index % 4]
        })
    }
    .width('100%').height('100%')
  }
}
