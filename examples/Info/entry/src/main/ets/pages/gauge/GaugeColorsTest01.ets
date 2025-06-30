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
struct GaugeColorsTest01 {
  @State isDark: boolean = false;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext

  build() {
    Column({ space: 5 }) {
      Row() {
        Text('Colors属性测试01').fontSize(22).fontColor(0x000000).fontWeight(FontWeight.Bold)
      }
      .height('6%')
      .width('95%')
      .borderRadius(15)
      .backgroundColor(0x7B68EE)
      .justifyContent(FlexAlign.Center)

      Column({ space: 5 }) {
        Row({ space: 3 }) {
          Column({ space: 3 }) {
            Text('ResourceColor:Color').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 }).colors(Color.Orange).strokeWidth(12).width('90%').height('15%')
          }.width('28%')

          Column({ space: 3 }) {
            Text('ResourceColor:Number').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 }).colors(0xffa500).strokeWidth(12).width('90%').height('15%')
          }.width('28%')

          Column({ space: 3 }) {
            Text('ResourceColor:#ffffff').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 }).colors('#a5d61d').strokeWidth(12).width('90%').height('15%')
          }.width('28%')
        }

        Row({ space: 3 }) {
          Column() {
            Text('ResourceColor:#ffffffff').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 }).colors('#ffa52a2a').strokeWidth(12).width('90%').height('15%')
          }.width('28%')

          Column() {
            Text('ResourceColor:rgb').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 }).colors('rgb(255,165,0)').strokeWidth(12).width('90%').height('15%')
          }.width('28%')

          Column() {
            Text('ResourceColor:rgba').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 })
              .colors('rgba(255,165,0,1)')
              .strokeWidth(12)
              .width('90%')
              .height('15%')
          }.width('28%')
        }

        Row({ space: 3 }) {
          Column() {
            Text('ResourceColor:$r').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 })
              .colors($r('app.color.ColorBlue'))
              .strokeWidth(12)
              .width('90%')
              .height('15%')
          }.width('28%')

          Column() {
            Text('ResourceColor:null').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 }).colors(null).strokeWidth(12).width('90%').height('15%')
          }.width('28%')

          Column() {
            Text('ResourceColor:undefined').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 }).colors(undefined).strokeWidth(12).width('90%').height('15%')
          }.width('28%')
        }

        Row({ space: 3 }) {
          Column() {
            Text('ResourceColor:-10000').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 }).colors(-10000).strokeWidth(12).width('90%').height('15%')
          }.width('28%')

          Column() {
            Text('ResourceColor:"hhhhhh"').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 }).colors('hhhhhh').strokeWidth(12).width('90%').height('15%')
          }.width('28%')

          Column() {
            Text('ResourceColor:"12abh"').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 }).colors('12abh').strokeWidth(12).width('90%').height('15%')
          }.width('28%')
        }
      }.width('100%').height('80%')

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
    }.width('100%').height('100%').alignItems(HorizontalAlign.Center)
  }
}