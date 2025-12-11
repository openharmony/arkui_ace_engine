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
  SizeOptions, SliderBlockStyle, Ellipse, SliderStyle, SlideRange,  SliderInteraction, SliderChangeMode,
  SliderAttribute, AttributeModifier, Divider, SliderStepItemAccessibility, Map, Axis, WrappedBuilder,
  FontWeight, SliderSuffixOptions, ResourceStr, wrapBuilder, UIContext, ComponentContent, LinearGradient
} from '@ohos.arkui.component'
import {State} from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'
@Builder
export function SliderPrefixSuffixStaticBuilder(name: string, param: Object) {
  SliderPrefixSuffixStatic()
}

@Builder
function textBuilder() {
  Text('低')
    .clip(true)
    .fontColor(Color.Black)
}
@Builder
function textBuilder1() {
  Text('高')
    .clip(true)
    .fontColor(Color.Black)
}

@Entry
@Component
struct SliderPrefixSuffixStatic {
  private uiContext: UIContext = this.getUIContext();
  private preNode1: ComponentContent = new ComponentContent(this.uiContext, wrapBuilder(textBuilder));
  private sufNode1: ComponentContent = new ComponentContent(this.uiContext, wrapBuilder(textBuilder1));
  private preNode2: ComponentContent = new ComponentContent(this.uiContext, wrapBuilder(textBuilder));
  private sufNode2: ComponentContent = new ComponentContent(this.uiContext, wrapBuilder(textBuilder1));
  private preNode3: ComponentContent = new ComponentContent(this.uiContext, wrapBuilder(textBuilder));
  private sufNode3: ComponentContent = new ComponentContent(this.uiContext, wrapBuilder(textBuilder1));

  build() {
    Column({ space: 8 } as ColumnOptions) {
      Text(`outset slider`)
        .fontSize(16)
        .width('100%')
      Row() {
        Slider({
          value: 50,
          min: 0,
          max: 100,
          style: SliderStyle.OutSet
        })
          .showTips(true)
          .prefix(this.preNode1)
          .suffix(this.sufNode1)
      }
      .width('80%')
      Text(`inset slider`)
        .fontSize(16)
        .width('100%')
      Row() {
        Slider({
          value: 50,
          min: 0,
          max: 100,
          style: SliderStyle.InSet
        })
          .trackColor('#ADD8E6')
          .selectedColor('#4169E1')
          .showTips(true)
          .trackThickness(36)
          .prefix(this.preNode2)
          .suffix(this.sufNode2)
      }
      .width('80%')
      Text(`slider Show Step`)
        .fontSize(16)
        .width('100%')
      Row() {
        Slider({
          value: 50,
          min: 0,
          max: 100,
          step:10,
          style: SliderStyle.InSet
        })
          .trackColor('#ADD8E6')
          .selectedColor('#4169E1')
          .showTips(true)
          .trackThickness(36)
          .showSteps(true)
          .prefix(this.preNode3, {
            accessibilityText: 'prefixText',
            accessibilityDescription: 'prefixDescription',
            accessibilityLevel: 'auto',
            accessibilityGroup: true
          })
          .suffix(this.sufNode3, {
            accessibilityText: 'suffixText',
            accessibilityDescription: 'suffixDescription',
            accessibilityLevel: 'auto',
            accessibilityGroup: true
          })
      }
      .width('80%')
      Text(`undefined`)
        .fontSize(16)
        .width('100%')
      Row() {
        Slider({
          value: 50,
          min: 0,
          max: 100,
          style: SliderStyle.InSet
        })
          .trackColor('#ADD8E6')
          .selectedColor('#4169E1')
          .showTips(true)
          .trackThickness(36)
          .prefix(undefined)
          .suffix(undefined)
      }
      .width('80%')
    }.width('100%')
  }
}