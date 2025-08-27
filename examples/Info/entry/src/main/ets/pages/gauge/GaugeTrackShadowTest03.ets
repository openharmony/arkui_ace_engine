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

@Entry
@Component
struct GaugeTrackShadowTest03 {
  @State isDark: boolean = false;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext

  build() {
    Column({ space: 5 }) {
      Row() {
        Text('trackShadow属性测试03')
          .fontSize(22)
          .fontColor(0x000000)
          .textAlign(TextAlign.Start)
          .fontWeight(FontWeight.Bold)
      }
      .height('6%')
      .width('95%')
      .borderRadius(15)
      .backgroundColor(0x7B68EE)
      .justifyContent(FlexAlign.Center)
      .margin({ bottom: 10 })

      Column() {
        Row({ space: 15 }) {
          Text('offsetY参数测试').fontColor(0x696969).width('40%')
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
        }.justifyContent(FlexAlign.Center)


        Row({ space: 15 }) {
          Column() {
            Text('offsetY: 不设置时为默认值5vp').fontSize(12).fontColor(0x696969)
            Gauge({ value: 50, min: 1, max: 100 }).colors(Color.Orange).strokeWidth(12).height('15%')
          }.width('50%')

          Column() {
            Text('offsetY: 40').fontSize(12).fontColor(0x696969)
            Gauge({ value: 50, min: 1, max: 100 }).colors(Color.Orange).strokeWidth(12).height('15%')
              .trackShadow({
                offsetY: 40, offsetX: 7, radius: 7
              })
          }.width('50%')
        }.justifyContent(FlexAlign.Center)

        Row({ space: 15 }) {
          Column() {
            Text('offsetY: 0').fontSize(12).fontColor(0x696969)
            Gauge({ value: 50, min: 1, max: 100 }).colors(Color.Orange).strokeWidth(12).height('15%')
              .trackShadow({
                offsetY: 0, offsetX: 7, radius: 7
              })
          }.width('50%')

          Column() {
            Text('offsetY: -40').fontSize(12).fontColor(0x696969)
            Gauge({ value: 50, min: 1, max: 100 }).colors(Color.Orange).strokeWidth(12).height('15%')
              .trackShadow({
                offsetY: -40, offsetX: 7, radius: 7
              })
          }.width('50%')
        }.justifyContent(FlexAlign.Center)

        Row({ space: 15 }) {
          Column() {
            Text('offsetY: $r("app.string.string_value_40")').fontSize(12).fontColor(0x696969)
            Gauge({ value: 50, min: 1, max: 100 }).colors(Color.Orange).strokeWidth(12).height('15%')
              .trackShadow({
                offsetY: $r('app.string.string_value_40'), offsetX: 7, radius: 7
              })
          }.width('50%')

          Column() {
            Text('offsetY: $r("app.float.float_value_40")').fontSize(12).fontColor(0x696969)
            Gauge({ value: 50, min: 1, max: 100 }).colors(Color.Orange).strokeWidth(12).height('15%')
              .trackShadow({
                offsetY: $r('app.float.float_value_40'), offsetX: 7, radius: 7
              })
          }.width('50%')
        }.justifyContent(FlexAlign.Center)

        Row({ space: 15 }) {
          Column() {
            Text('offsetY: $r("app.integer.integer_value_40")').fontSize(12).fontColor(0x696969)
            Gauge({ value: 50, min: 1, max: 100 }).colors(Color.Orange).strokeWidth(12).height('15%')
              .trackShadow({
                offsetY: $r('app.integer.integer_value_40'), offsetX: 7, radius: 7
              })
          }.width('50%')

          Column() {
            Text('多次设置最后一次生效: 40').fontSize(12).fontColor(0x696969)
            Gauge({ value: 50, min: 1, max: 100 })
              .colors(Color.Orange)
              .strokeWidth(12)
              .height('15%')
              .trackShadow({
                offsetY: $r('app.integer.integer_value_40'), offsetX: 7, radius: 7
              })
              .trackShadow({
                offsetY: $r('app.string.string_value_40'), offsetX: 7, radius: 7
              })
              .trackShadow({
                offsetY: $r('app.float.float_value_40'), offsetX: 7, radius: 7
              })
              .trackShadow({
                offsetY: -40, offsetX: 7, radius: 7
              })
              .trackShadow({
                offsetY: 0, offsetX: 7, radius: 7
              })
              .trackShadow({
                offsetY: 40, offsetX: 7, radius: 7
              })
          }.width('50%')
        }.justifyContent(FlexAlign.Center)

        Row({ space: 15 }) {
          Column() {
            Text('offsetY: undefined').fontSize(12).fontColor(0x696969)
            Gauge({ value: 50, min: 1, max: 100 }).colors(Color.Orange).strokeWidth(12).height('15%')
              .trackShadow({
                radius: 7, offsetY: undefined, offsetX: 7
              })
          }.width('50%')

          Column() {
            Text('offsetY: null').fontSize(12).fontColor(0x696969)
            Gauge({ value: 50, min: 1, max: 100 }).colors(Color.Orange).strokeWidth(12).height('15%')
              .trackShadow({
                offsetY: null, radius: 7, offsetX: 7
              })
          }.width('50%')
        }.justifyContent(FlexAlign.Center)

      }.width('90%').height('90%')
    }.width('100%').height('100%').alignItems(HorizontalAlign.Center)
  }
}