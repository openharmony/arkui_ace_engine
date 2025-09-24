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

import ConfigurationConstant from '@ohos.app.ability.ConfigurationConstant';
import common from '@ohos.app.ability.common';
import { GaugeModifier } from '@ohos.arkui.modifier'

@Entry
@Component
struct GaugeModifierTrackShadowTest02 {
  @State isDark: boolean = false;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext
  @State modifier1: GaugeModifier = new GaugeModifier().trackShadow({ radius: 20, offsetY: 20 })
  @State modifier2: GaugeModifier = new GaugeModifier().trackShadow({ offsetX: 40, radius: 20, offsetY: 20 })
  @State modifier3: GaugeModifier = new GaugeModifier().trackShadow({ offsetX: 0, radius: 20, offsetY: 20 })
  @State modifier4: GaugeModifier = new GaugeModifier().trackShadow({ offsetX: -40, radius: 20, offsetY: 20 })
  @State modifier5: GaugeModifier =
    new GaugeModifier().trackShadow({ offsetX: $r('app.string.string_value_40'), radius: 20, offsetY: 20 })
  @State modifier6: GaugeModifier =
    new GaugeModifier().trackShadow({ offsetX: $r('app.float.float_value_40'), radius: 20, offsetY: 20 })
  @State modifier7: GaugeModifier =
    new GaugeModifier().trackShadow({ offsetX: $r('app.integer.integer_value_40'), radius: 20, offsetY: 20 })
  @State modifier8: GaugeModifier = new GaugeModifier()
    .trackShadow({
      offsetX: $r('app.integer.integer_value_40'), radius: 20, offsetY: 20
    })
    .trackShadow({
      offsetX: $r('app.string.string_value_40'), radius: 20, offsetY: 20
    })
    .trackShadow({
      offsetX: $r('app.float.float_value_40'), radius: 20, offsetY: 20
    })
    .trackShadow({
      offsetX: -40, radius: 20, offsetY: 20
    })
    .trackShadow({
      offsetX: 0, radius: 20, offsetY: 20
    })
    .trackShadow({
      offsetX: 40, radius: 20, offsetY: 20
    })
  @State modifier9: GaugeModifier = new GaugeModifier().trackShadow({ offsetX: undefined, radius: 20, offsetY: 20 })
  @State modifier10: GaugeModifier = new GaugeModifier().trackShadow({ offsetX: null, radius: 20, offsetY: 20 })

  build() {
    Column({ space: 5 }) {
      Row() {
        Text('trackShadow属性测试02').fontSize(22).fontColor(0x000000).fontWeight(FontWeight.Bold)
      }
      .height('6%')
      .width('95%')
      .borderRadius(15)
      .backgroundColor(0x7B68EE)
      .justifyContent(FlexAlign.Center)
      .margin({ bottom: 10 })

      Column() {
        Row({ space: 15 }) {
          Text('offsetX参数测试').fontColor(0x696969).width('40%')
          Button('ChangeDarkMode').backgroundColor(0x7B68EE).width(180).height(20)
            .onClick(() => {
              if (this.isDark) {
                this.isDark = false;
                this.context.getApplicationContext().setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_LIGHT);
              } else {
                this.isDark = true;
                this.context.getApplicationContext().setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_DARK);
              }
            })
        }.justifyContent(FlexAlign.Center).margin({ bottom: 20 })

        Row({ space: 15 }) {
          Column() {
            Text('offsetX: 不设置时为默认值5vp').fontSize(12).fontColor(0x696969)
            Gauge({ value: 50, min: 1, max: 100 }).colors($r('app.color.ColorBlue')).strokeWidth(12).height('15%')
              .attributeModifier(this.modifier1)
          }.width('50%')

          Column() {
            Text('offsetX: 40').fontSize(12).fontColor(0x696969)
            Gauge({ value: 50, min: 1, max: 100 }).colors($r('app.color.ColorBlue')).strokeWidth(12).height('15%')
              .attributeModifier(this.modifier2)
          }.width('50%')
        }.justifyContent(FlexAlign.Center)

        Row({ space: 15 }) {
          Column() {
            Text('offsetX: 0').fontSize(12).fontColor(0x696969)
            Gauge({ value: 50, min: 1, max: 100 }).colors($r('app.color.ColorBlue')).strokeWidth(12).height('15%')
              .attributeModifier(this.modifier3)
          }.width('50%')

          Column() {
            Text('offsetX: -40').fontSize(12).fontColor(0x696969)
            Gauge({ value: 50, min: 1, max: 100 }).colors($r('app.color.ColorBlue')).strokeWidth(12).height('15%')
              .attributeModifier(this.modifier4)
          }.width('50%')
        }.justifyContent(FlexAlign.Center)

        Row({ space: 15 }) {
          Column() {
            Text('offsetX: $r("app.string.string_value_40")').fontSize(12).fontColor(0x696969)
            Gauge({ value: 50, min: 1, max: 100 }).colors($r('app.color.ColorBlue')).strokeWidth(12).height('15%')
              .attributeModifier(this.modifier5)
          }.width('50%')

          Column() {
            Text('offsetX: $r("app.float.float_value_40")').fontSize(12).fontColor(0x696969)
            Gauge({ value: 50, min: 1, max: 100 }).colors($r('app.color.ColorBlue')).strokeWidth(12).height('15%')
              .attributeModifier(this.modifier6)
          }.width('50%')
        }.justifyContent(FlexAlign.Center)

        Row({ space: 15 }) {
          Column() {
            Text('offsetX: $r("app.integer.integer_value_40")').fontSize(12).fontColor(0x696969)
            Gauge({ value: 50, min: 1, max: 100 }).colors($r('app.color.ColorBlue')).strokeWidth(12).height('15%')
              .attributeModifier(this.modifier7)
          }.width('50%')

          Column() {
            Text('多次设置最后一次生效: 40').fontSize(12).fontColor(0x696969)
            Gauge({ value: 50, min: 1, max: 100 }).colors($r('app.color.ColorBlue')).strokeWidth(12).height('15%')
              .attributeModifier(this.modifier8)
          }.width('50%')
        }.justifyContent(FlexAlign.Center)

        Row({ space: 15 }) {
          Column() {
            Text('offsetX: undefined').fontSize(12).fontColor(0x696969)
            Gauge({ value: 50, min: 1, max: 100 }).colors($r('app.color.ColorBlue')).strokeWidth(12).height('15%')
              .attributeModifier(this.modifier9)
          }.width('50%')

          Column() {
            Text('offsetX: null').fontSize(12).fontColor(0x696969)
            Gauge({ value: 50, min: 1, max: 100 }).colors($r('app.color.ColorBlue')).strokeWidth(12).height('15%')
              .attributeModifier(this.modifier10)
          }.width('50%')
        }.justifyContent(FlexAlign.Center)

      }.width('90%').height('90%')

      // .backgroundColor(0xE6E6FA)
    }.width('100%').height('100%').alignItems(HorizontalAlign.Center)
  }
}