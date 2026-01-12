/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 
'use static'

import { Entry, Text, Scroll, Column, ColumnOptions, Row, Component, Button, ClickEvent, Slider, SliderStyle, SliderChangeMode, Axis, SliderAttribute, AttributeModifier } from '@ohos.arkui.component'
import { State } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'

@Entry
@Component
struct Slider005 {
  @State outSetValueOne: Int = 40;
  @State stepIndex: Int = 0
  @State stepList: (Int| undefined)[] = [
    5, 10, 20, 50, 100, 200, undefined
  ]
  build() {
    Row() {
      Column() {
        Slider({
          value: this.outSetValueOne,
          min: 0,
          max: 100,
          style: SliderStyle.OutSet
        })
          .accessibilityActionOptions({scrollStep:this.stepList[this.stepIndex]})
          .showTips(true)
        Button('切换').onClick(() => {
          this.stepIndex++
          if (this.stepIndex > this.stepList.length - 1) {
            this.stepIndex = 0
          }
        })
        Text(`参数：scrollstep = ${this.stepList[this.stepIndex]}`)
        Slider({
          value: 60,
          min: 0,
          max: 100,
          style: SliderStyle.OutSet
        })
          .accessibilityActionOptions({scrollStep:70})
          .showTips(true)
      }
      .width('100%')
    }
    .height('100%')
  }
}