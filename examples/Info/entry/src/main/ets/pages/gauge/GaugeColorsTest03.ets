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
struct GaugeColorsTest03 {
  @State isDark: boolean = false;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext
  public color01: LinearGradient =
    new LinearGradient([{ color: Color.Green, offset: 0 }, { color: Color.Orange, offset: 0.5 },
      { color: Color.Pink, offset: 1 }])
  public color02: LinearGradient = new LinearGradient([{ color: 0x008000, offset: 0 }, { color: 0xffa500, offset: 0.5 },
    { color: 0xffc0cb, offset: 1 }])
  public color03: LinearGradient =
    new LinearGradient([{ color: '#008000', offset: 0 }, { color: '#ffa500', offset: 0.5 },
      { color: '#ffc0cb', offset: 1 }])
  public color04: LinearGradient =
    new LinearGradient([{ color: '#ff008000', offset: 0 }, { color: '#ffffa500', offset: 0.5 },
      { color: '#ffffc0cb', offset: 1 }])
  public color05: LinearGradient =
    new LinearGradient([{ color: 'rgb(0,128,0)', offset: 0 }, { color: 'rgb(255,165,0)', offset: 0.5 },
      { color: 'rgb(255,192,203)', offset: 1 }])
  public color06: LinearGradient =
    new LinearGradient([{ color: 'rgba(0,128,0,1)', offset: 0 }, { color: 'rgba(255,165,0,1)', offset: 0.5 },
      { color: 'rgba(255,192,203,1)', offset: 1 }])
  public color07: LinearGradient = new LinearGradient([{ color: $r('app.color.ColorGreen'), offset: 0 },
    { color: $r('app.color.ColorOrange'), offset: 0.5 }, { color: $r('app.color.ColorPink'), offset: 1 }])
  public color08: LinearGradient =
    new LinearGradient([{ color: -10000, offset: 0 }, { color: 'hhhhh', offset: 0.5 }, { color: 0, offset: 1 }])

  build() {
    Column({ space: 5 }) {
      Row() {
        Text('Colors属性测试03').fontSize(22).fontColor(0x000000).fontWeight(FontWeight.Bold)
      }
      .height('6%')
      .width('95%')
      .borderRadius(15)
      .backgroundColor(0x7B68EE)
      .justifyContent(FlexAlign.Center)

      Column({ space: 5 }) {
        Row({ space: 3 }) {
          Column({ space: 3 }) {
            Text('LinearGradient:Color').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 }).colors(this.color01).strokeWidth(12).width('90%').height('15%')
          }.width('28%')

          Column({ space: 3 }) {
            Text('LinearGradient:Number').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 }).colors(this.color02).strokeWidth(12).width('90%').height('15%')
          }.width('28%')

          Column({ space: 3 }) {
            Text('LinearGradient:#ffffff').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 }).colors(this.color03).strokeWidth(12).width('90%').height('15%')
          }.width('28%')
        }

        Row({ space: 3 }) {
          Column() {
            Text('LinearGradient:#ffffffff').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 }).colors(this.color04).strokeWidth(12).width('90%').height('15%')
          }.width('28%')

          Column() {
            Text('LinearGradient:rgb').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 }).colors(this.color05).strokeWidth(12).width('90%').height('15%')
          }.width('28%')

          Column() {
            Text('LinearGradient:rgba').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 }).colors(this.color06).strokeWidth(12).width('90%').height('15%')
          }.width('28%')
        }

        Row({ space: 3 }) {
          Column() {
            Text('LinearGradient:$r').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 }).colors(this.color07).strokeWidth(12).width('90%').height('15%')
          }.width('28%')

          Column() {
            Text('LinearGradient:null').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 }).colors(null).strokeWidth(12).width('90%').height('15%')
          }.width('28%')

          Column() {
            Text('LinearGradient:undefined').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 }).colors(undefined).strokeWidth(12).width('90%').height('15%')
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