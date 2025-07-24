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
struct BadgeParamWithStringIndex {
  @State isDark: boolean = false;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext
  @State badgeWithStringIndex: number = 0;
  @State badgeWithStringList: (ResourceStr | null | undefined)[] = [
    '11111', $r('app.string.FeiFaZhi'), $r('app.color.pink'), $r('app.string.QRcode'), $r('app.string.format'), null,
    $r('app.string.QRcode'), undefined, $r('app.string.QRcode'), $r('app.string.QRcode')
  ]
  @State badgeWithStringListStr: string[] = [
    '11111',
    '$r("app.string.FeiFaZhi")-￥%123abc',
    '$r("app.color.pink")--#FFF38FEA',
    '$r("app.string.QRcode")-hello',
    '$r("app.string.format")-yyyy-mm-dd',
    'null',
    '$r("app.string.QRcode")-hello',
    'undefined',
    '$r("app.string.QRcode")-hello',
    '$r("app.string.QRcode")-hello'
  ]

  build() {
    Column() {
      Row() {
        Text('Badge-BadgeParamWithString').fontSize(22).fontColor(0x000020).fontWeight(FontWeight.Bold)
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
            style: {},
            value: 'New',
          }) {
            Text('原生badge').fontSize(16).fontColor(0x696969).width('95%')
          }.width(200).height(21).margin({ left: 15, right: 19 })
        }.width('100%').padding({ left: 12, right: 12 }).height(76)
        Badge({
          style: {},
          value: this.badgeWithStringList[this.badgeWithStringIndex],
        }) {
          Text('效果').fontSize(16).fontColor(0x696969).width('30%')
        }.width(130).height(21).margin({ left: 15, right: 19 })
        Text('当前badgeValue：' + this.badgeWithStringListStr[this.badgeWithStringIndex])
          .fontSize(12)
          .fontColor(0x696969)
          .margin({ top: 20, bottom: 20 })
        Button('动态切换BadgeValue')
          .onClick(() => {
            this.badgeWithStringIndex = (this.badgeWithStringIndex + 1) % this.badgeWithStringList.length;
          })
        Row() {
          Badge({
            value: $r('app.string.QRcode'),
            position: BadgePosition.Right,
            style: {
              fontSize: 15,
              badgeSize: 60,
              fontWeight: 18,
            }
          }) {
            Text('BadgeParamWithString：resource').fontSize(16).fontColor(0x696969).width('95%')
          }.width(240).height(21).margin({ left: 15, right: 19 })
        }.width('100%').padding({ left: 12, right: 12 }).height(76)
        Row() {
          Badge({
            value: '1111',
            position: BadgePosition.Right,
            style: {
              fontSize: 15,
              badgeSize: 60,
              fontWeight: 18,
            }
          }) {
            Text('BadgeParamWithString：string').fontSize(16).fontColor(0x696969).width('95%')
          }.width(240).height(21).margin({ left: 15, right: 19 })
        }.width('100%').padding({ left: 12, right: 12 }).height(76)
        Row() {
          Badge({
            value: undefined,
            position: BadgePosition.Right,
            style: {
              color: 0x696969,
              fontSize: 20,
              badgeSize: 60,
              fontWeight: 18,
            }
          }) {
            Text('BadgeParamWithString：undefined').fontSize(16).fontColor(0x696969).width('95%')
          }.width(240).height(21).margin({ left: 15, right: 19 })
        }.width('100%').padding({ left: 12, right: 12 }).height(76)
        Row() {
          Badge({
            value: null,
            position: BadgePosition.Right,
            style: {
              color: 0x696969,
              fontSize: 20,
              badgeSize: 60,
              fontWeight: 18,
            }
          }) {
            Text('BadgeParamWithString：null').fontSize(16).fontColor(0x696969).width('95%')
          }.width(240).height(21).margin({ left: 15, right: 11 })
        }.width('100%').padding({ left: 12, right: 12 }).height(76)
      }.width('100%').padding({ bottom: 12 })
    }.width('100%')
  }
}