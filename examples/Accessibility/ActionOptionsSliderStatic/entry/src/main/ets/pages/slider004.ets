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
import { State, Observed } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'

@Observed
class Slider_Modifier1 implements AttributeModifier<SliderAttribute> {
  applyNormalAttribute(instance: SliderAttribute): void {
    instance
      .showSteps(true)
      .stepSize('4vp')
      .accessibilityActionOptions({ scrollStep: 5 })
  }
}
class Slider_Modifier2 implements AttributeModifier<SliderAttribute> {
  applyNormalAttribute(instance: SliderAttribute): void {
    instance
      .showSteps(true)
      .stepSize('4vp')
      .accessibilityActionOptions({ scrollStep: undefined })
  }
}
// class Slider_Modifier3 implements AttributeModifier<SliderAttribute> {
//   applyNormalAttribute(instance: SliderAttribute): void {
//     instance
//       .showSteps(true)
//       .stepSize('4vp')
//       .accessibilityActionOptions({ scrollStep: null })
//   }
// }
@Entry
@Component
struct Slider004 {
  @State outSetValueOne: number = 40;
  @State inSetValueOne: number = 40;
  @State noneValueOne: number = 40;
  @State outSetValueTwo: number = 40;
  @State inSetValueTwo: number = 40;
  @State vOutSetValueOne: number = 40;
  @State vInSetValueOne: number = 40;
  @State vOutSetValueTwo: number = 40;
  @State vInSetValueTwo: number = 40;
  @State modifier1 : Slider_Modifier1 = new Slider_Modifier1()
  @State modifier2 : Slider_Modifier2 = new Slider_Modifier2()
  // @State modifier3 : Slider_Modifier3 = new Slider_Modifier3()
  build() {
    Column({ space: 8 } as ColumnOptions) {
      Text('outset slider').fontSize(9).fontColor(0xCCCCCC).width('90%').margin(15)
      Row() {
        Slider({
          value: this.outSetValueOne,
          min: 0,
          max: 100,
          step: 10,
          style: SliderStyle.OutSet
        })
          .attributeModifier(this.modifier1)
          .showTips(true)
          .onChange((value: number, mode: SliderChangeMode) => {
            this.outSetValueOne = value;
            console.info('value:' + value + 'mode:' + mode.toString());
          })
        // toFixed(0)将滑动条返回值处理为整数精度
        Text(this.outSetValueOne.toFixed(0)).fontSize(12)
      }
      .width('80%')
      Row() {
        Slider({
          value: this.outSetValueTwo,
          step: 10,
          style: SliderStyle.OutSet
        })
          .attributeModifier(this.modifier2)
          .showSteps(true)
          .onChange((value: number, mode: SliderChangeMode) => {
            this.outSetValueTwo = value;
            console.info('value:' + value + 'mode:' + mode.toString());
          })
        Text(this.outSetValueTwo.toFixed(0)).fontSize(12)
      }
      .width('80%')

      // Text('inset slider').fontSize(9).fontColor(0xCCCCCC).width('90%').margin(15)
      // Row() {
      //   Slider({
      //     value: this.inSetValueOne,
      //     min: 0,
      //     max: 100,
      //     step: 10,
      //     style: SliderStyle.InSet
      //   })
      //     .attributeModifier(this.modifier3)
      //     .blockColor('#191970')
      //     .trackColor('#ADD8E6')
      //     .selectedColor('#4169E1')
      //     .showTips(true)
      //     .onChange((value: number, mode: SliderChangeMode) => {
      //       this.inSetValueOne = value;
      //       console.info('value:' + value + 'mode:' + mode.toString());
      //     })
      //   Text(this.inSetValueOne.toFixed(0)).fontSize(12)
      // }
      .width('80%')
    }.width('100%')
  }
}