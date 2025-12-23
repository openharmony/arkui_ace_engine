/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
import {
  Entry, Text, Column, Component, Button, ClickEvent, LengthMetrics, Color, Slider, SliderBlockType,
  TextAlign, List, ListItem, ListScroller, Builder, ForEach, Row, TransitionType, FlexAlign, ColumnOptions,
  SizeOptions, SliderBlockStyle, Ellipse, SliderStyle, SlideRange, SliderInteraction, SliderChangeMode,
  SliderAttribute, AttributeModifier, Divider, SliderStepItemAccessibility, Map, Axis, ResourceStr,
  ResourceColor, Resource, $r, SliderShowStepOptions
} from '@ohos.arkui.component'
import { State } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'
@Builder
export function SliderShowStepsStaticBuilder(name: string, param: Object) {
  SliderShowStepsStatic()
}
@Entry
@Component
struct SliderShowStepsStatic {
  @State optionMaps:Map<number, SliderStepItemAccessibility> = new Map<number, SliderStepItemAccessibility>();

  aboutToAppear(){
    this.optionMaps.set(1, {text : '123123'})
    this.optionMaps.set(2, {text : 'Slider无障碍文本'})
    this.optionMaps.set(3, {text : $r('app.string.EntryAbility_desc')})
    this.optionMaps.set(4, {text : '!@#$%^&*()'})
  }
  build() {
    Column({ space: 8 } as ColumnOptions) {
      Text(`不设置:`)
        .fontSize(16)
        .width('100%')
      Slider({
        style: SliderStyle.InSet,
        value: 20,
        step: 10,
        max: 50,
        min: 0,
        direction: Axis.Horizontal
      })
        .stepSize(8)
        .stepColor(Color.Yellow)
      Text(`设置`)
        .fontSize(16)
        .width('100%')
      Slider({
        style: SliderStyle.InSet,
        value: 20,
        step: 10,
        max: 50,
        min: 0,
        direction: Axis.Horizontal
      })
        .stepSize(8)
        .stepColor(Color.Yellow)
        .showSteps(true, {stepsAccessibility: this.optionMaps} as SliderShowStepOptions)
      Text(`undefined`)
        .fontSize(16)
        .width('100%')
      Slider({
        style: SliderStyle.InSet,
        value: 20,
        step: 10,
        max: 50,
        min: 0,
        direction: Axis.Horizontal
      })
        .stepSize(8)
        .stepColor(Color.Yellow)
        .showSteps(undefined)
    }
  }
}
