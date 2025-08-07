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
struct Page {
  @State message: string = 'Hello World';
  @State value: number = 0;
  @State isDark: boolean = false;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext
  @State fontSizeIndex: number = 0;
  @State fontSizeList: (number | string | null | undefined | Resource)[] = [
    null, $r('app.string.FeiFaZhi'), $r('app.color.pink'), $r('app.string.string_value_10'), undefined,
    $r('app.string.format'), $r('app.string.number_10'), 48, $r('app.string.number_10'), '38vp',
    $r('app.string.number_10'), $r('app.string.number_10')
  ]
  @State fontSizeListStr: string[] = [
    'null',
    '$r("app.string.FeiFaZhi")-￥%123abc',
    '$r("app.color.pink")--#FFF38FEA',
    '$r("app.string.string_value_10")-L10-D1',
    'undefined',
    '$r("app.string.format")-yyyy-mm-dd',
    '$r("app.string.number_10")-L10-D30',
    '48',
    '$r("app.string.number_10")-L10-D30',
    '38vp',
    '$r("app.string.number_10")-L10-D30',
    '$r("app.string.number_10")-L10-D30'
  ]
  @Builder
  itemBuilder(value: string) {
    Row() {
      Text(value)
        .width(177)
        .height(21)
        .margin({ left: 15, right: 76 })
        .textAlign(TextAlign.Start)
        .fontColor('#182431')
        .fontWeight(500)
        .fontSize(16)
        .opacity(0.9)
    }.width('100%').padding({ left: 12, right: 12 }).height(56)
  }
  build() {
    Column() {
      Row() {
        Text('Badge-fontSize文本大小').fontSize(22).fontColor(0x000020).fontWeight(FontWeight.Bold)
      }
      .height('6%')
      .width('95%')
      .borderRadius(15)
      .backgroundColor('#ffa9cbd6',)
      .justifyContent(FlexAlign.Center)
      Column() {
        Button('Change')
          .onClick(() => {
            if (this.isDark) {
              this.isDark = false;
              this.context.getApplicationContext().setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_LIGHT);
            } else {
              this.isDark = true;
              this.context.getApplicationContext().setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_DARK);
            }
          })
        Row() {
          Badge({
            value: 'New',
            style: {}
          }) {
            Text('原生badge').fontSize(16).fontColor(0x696969).width('95%')
          }.width(240).height(21).margin({ left: 15, right: 19 })
        }.width('100%').padding({ left: 12, right: 12 }).height(76)
        Text('当前fontSize: ' + this.fontSizeListStr[this.fontSizeIndex])
          .fontSize(12)
          .fontColor(0x696969)
          .margin({ top: 20, bottom: 20 })
        Button('动态切换fontSize')
          .onClick(() => {
            this.fontSizeIndex = (this.fontSizeIndex + 1) % this.fontSizeList.length;
          })
        Row() {
          Badge({
            value: 'New',
            position: BadgePosition.Right,
            style: {
              fontSize: this.fontSizeList[this.fontSizeIndex],
              badgeSize: 60,
              fontWeight: 18,
            }
          }) {
            Text('效果').fontSize(16).fontColor(0x696969).width('30%')
          }.width(130).height(21).margin({ left: 15, right: 19 })
        }.width('100%').padding({ left: 12, right: 12 }).height(76)
        Row() {
          Badge({
            value: 'New',
            position: BadgePosition.Right,
            style: {
              fontSize: $r('app.string.number_10'),
              badgeSize: 48,
              fontWeight: 1
            }
          }) {
            Text('fontSize：resourse').fontSize(16).fontColor(0x696969).width('95%')
          }.width(240).height(21).margin({ left: 15, right: 11 })
        }.width('100%').padding({ left: 12, right: 12 }).height(76)
        Row() {
          Badge({
            value: 'New',
            position: BadgePosition.Right,
            style: {
              fontSize: 18,
              badgeSize: 48,
              fontWeight: 900
            }
          }) {
            Text('fontSize：正常值18').fontSize(16).fontColor(0x696969).width('95%')
          }.width(240).height(21).margin({ left: 15, right: 11 })
        }.width('100%').padding({ left: 12, right: 12 }).height(76)
        Row() {
          Badge({
            value: 'New',
            position: BadgePosition.Right,
            style: {
              fontSize: undefined,
              badgeSize: 48,
            }
          }) {
            Text('fontSize：null').fontSize(16).fontColor(0x696969).width('95%')
          }.width(240).height(21).margin({ left: 15, right: 11 })
        }.width('100%').padding({ left: 12, right: 12 }).height(76)
        Row() {
          Badge({
            value: 'New',
            position: BadgePosition.Right,
            style: {
              fontSize: undefined,
              badgeSize: 48,
            }
          }) {
            Text('fontSize：undefined').fontSize(16).fontColor(0x696969).width('95%')
          }.width(240).height(21).margin({ left: 15, right: 11 })
        }.width('100%').padding({ left: 12, right: 12 }).height(76)
      }.width('100%')
      .padding({ bottom: 12 })
    }
  }
}