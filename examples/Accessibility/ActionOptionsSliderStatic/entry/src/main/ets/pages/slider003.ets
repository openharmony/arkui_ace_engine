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

import { Entry, Text, Scroll, Column, ColumnOptions, Row, Component, Button, ClickEvent, Slider, SliderStyle, SliderChangeMode, Axis } from '@ohos.arkui.component'
import { State } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'

@Entry
@Component
struct Slider003 {
  @State outSetValueOne: number = 40;
  @State inSetValueOne: number = 40;
  @State noneValueOne: number = 40;
  @State outSetValueTwo: number = 40;
  @State inSetValueTwo: number = 40;
  @State vOutSetValueOne: number = 40;
  @State vInSetValueOne: number = 40;
  @State vOutSetValueTwo: number = 40;
  @State vInSetValueTwo: number = 40;

  build() {
    Column({ space: 8 } as ColumnOptions) {
      // Text('outset slider').fontSize(9).fontColor(0xCCCCCC).width('90%').margin(15)
      // Text('scrollStep:5.5').fontSize(9).fontColor(0xCCCCCC).width('90%')
      // Row() {
      //   Slider({
      //     value: this.outSetValueOne,
      //     min: 0,
      //     max: 100,
      //     style: SliderStyle.OutSet,
      //     step: 10,
      //   })
      //     .accessibilityActionOptions({scrollStep:5.5})
      //     .showTips(true)

        // toFixed(0)将滑动条返回值处理为整数精度
      //   Text(this.outSetValueOne.toFixed(0)).fontSize(12)
      // }
      // .width('80%')
      Text('scrollStep:-1').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Row() {
        Slider({
          value: this.outSetValueTwo,
          step: 10,
          style: SliderStyle.OutSet
        })
          .accessibilityActionOptions({scrollStep:-1})
          .showSteps(true)

        Text(this.outSetValueTwo.toFixed(0)).fontSize(12)
      }
      .width('80%')
      Text('scrollStep:0').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Row() {
        Slider({
          value: this.outSetValueTwo,
          step: 10,
          style: SliderStyle.OutSet
        })
          .accessibilityActionOptions({scrollStep:0})
          .showSteps(true)

        Text(this.outSetValueTwo.toFixed(0)).fontSize(12)
      }
      .width('80%')

      Text('inset slider').fontSize(9).fontColor(0xCCCCCC).width('90%').margin(15)

      Text('scrollStep:102').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Row() {
        Slider({
          value: this.inSetValueTwo,
          step: 10,
          style: SliderStyle.InSet
        })
          .accessibilityActionOptions({scrollStep:102})
          .blockColor('#191970')
          .trackColor('#ADD8E6')
          .selectedColor('#4169E1')
          .showSteps(true)

        Text(this.inSetValueTwo.toFixed(0)).fontSize(12)
      }
      .width('80%')

      Row() {
        Column() {
          Text('vertical outset slider').fontSize(9).fontColor(0xCCCCCC).width('50%').margin(15)
          Text('undefined').fontSize(9).fontColor(0xCCCCCC).width('50%')
          Row() {
            Text().width('10%')
            Slider({
              step: 10,
              value: this.vOutSetValueOne,
              style: SliderStyle.OutSet,
              direction: Axis.Vertical
            })
              .accessibilityActionOptions({scrollStep:undefined})
              .blockColor('#191970')
              .trackColor('#ADD8E6')
              .selectedColor('#4169E1')
              .showTips(true)

          }
        }.width('50%').height(300)

        Column() {
          Text('99999').fontSize(9).fontColor(0xCCCCCC).width('50%').margin(15)
          // Row() {
          //   Slider({
          //     value: this.vInSetValueOne,
          //     style: SliderStyle.InSet,
          //     direction: Axis.Vertical,
          //     reverse: true // 竖向的Slider默认是上端是min值，下端是max值，因此想要从下往上滑动，需要设置reverse为true
          //   })
          //     .accessibilityActionOptions({scrollStep:0.02})
          //     .showTips(true)

            Slider({
              value: this.vInSetValueTwo,
              step: 10,
              style: SliderStyle.InSet,
              direction: Axis.Vertical,
              reverse: true
            })
              .showSteps(true)
              .accessibilityActionOptions({scrollStep:99999})

        }.width('50%').height(300)
      }
    }.width('100%')
  }
}