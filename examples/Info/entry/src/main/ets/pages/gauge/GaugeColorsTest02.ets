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
struct GaugeColorsTest02 {
  @State isDark: boolean = false;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext

  build() {
    Column({ space: 5 }) {
      Row() {
        Text('Colors属性测试02').fontSize(22).fontColor(0x000000).fontWeight(FontWeight.Bold)
      }
      .height('6%')
      .width('95%')
      .borderRadius(15)
      .backgroundColor(0x7B68EE)
      .justifyContent(FlexAlign.Center)

      Column({ space: 8 }) {
        Row({ space: 3 }) {
          Column({ space: 3 }) {
            Text('ResourceColor:ColorArr').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 })
              .colors([
                [Color.Brown, 1],
                [Color.Black, 2],
                [Color.Green, 3],
                [Color.Orange, 4],
                [Color.Pink, 5],
                [Color.Red, 6],
                [Color.Yellow, 7],
                [Color.Blue, 8]
              ])
              .strokeWidth(12)
              .width('90%')
              .height('15%')
          }.width('28%')

          Column({ space: 3 }) {
            Text('ResourceColor:NumberArr').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({
              value: 50,
              min: 1,
              max: 100
            })
              .colors([
                [0x0000ff, 1],
                [0xa52a2a, 2],
                [0x000000, 3],
                [0x008000, 4],
                [0xffa500, 5],
                [0xffc0cb, 6],
                [0xff0000, 7],
                [0xffff00, 8]
              ])
              .strokeWidth(12)
              .width('90%')
              .height('15%')
          }.width('28%')

          Column({ space: 3 }) {
            Text('ResourceColor:#ffffffArr').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({
              value: 50,
              min: 1,
              max: 100
            })
              .colors([
                ['#0000ff', 1],
                ['#a52a2a', 2],
                ['#000000', 3],
                ['#008000', 4],
                ['#ffa500', 5],
                ['#ffc0cb', 6],
                ['#ff0000', 7],
                ['#ffff00', 8]
              ])
              .strokeWidth(12)
              .width('90%')
              .height('15%')
          }.width('28%')
        }

        Row({ space: 3 }) {
          Column() {
            Text('ResourceColor:#ffffffffArr').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({
              value: 50,
              min: 1,
              max: 100
            })
              .colors([
                ['#ff0000ff', 1],
                ['#ffa52a2a', 2],
                ['#ff000000', 3],
                ['#ff008000', 4],
                ['#ffffa500', 5],
                ['#ffffc0cb', 6],
                ['#ffff0000', 7],
                ['#ffffff00', 8]
              ])
              .strokeWidth(12)
              .width('90%')
              .height('15%')
          }.width('28%')

          Column() {
            Text('ResourceColor:rgbArr').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({
              value: 50,
              min: 1,
              max: 100
            })
              .colors([
                ['rgb(0,0,255)', 1],
                ['rgb(165,42,42)', 2],
                ['rgb(0,0,0)', 3],
                ['rgb(0,128,0)', 4],
                ['rgb(255,165,0)', 5],
                ['rgb(255,192,203)', 6],
                ['rgb(255,0,0)', 7],
                ['rgb(255,255,0)', 8]
              ])
              .strokeWidth(12)
              .width('90%')
              .height('15%')
          }.width('28%')

          Column() {
            Text('ResourceColor:rgbaArr').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({
              value: 50,
              min: 1,
              max: 100
            })
              .colors([
                ['rgba(0,0,255,1)', 1],
                ['rgba(165,42,42,1)', 2],
                ['rgba(0,0,0,1)', 3],
                ['rgba(0,128,0,1)', 4],
                ['rgba(255,165,0,1)', 5],
                ['rgba(255,192,203,1)', 6],
                ['rgba(255,0,0,1)', 7],
                ['rgba(255,255,0,1)', 8]
              ])
              .strokeWidth(12)
              .width('90%')
              .height('15%')
          }.width('28%')
        }

        Row({ space: 3 }) {
          Column() {
            Text('ResourceColor:$rArr').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({
              value: 50,
              min: 1,
              max: 100
            })
              .colors([
                [$r('app.color.ColorBlue'), 1],
                [$r('app.color.ColorBrown'), 2],
                [$r('app.color.ColorBlack'), 3],
                [$r('app.color.ColorGreen'), 4],
                [$r('app.color.ColorOrange'), 5],
                [$r('app.color.ColorPink'), 6],
                [$r('app.color.ColorRed'), 7],
                [$r('app.color.ColorYellow'), 8]
              ])
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