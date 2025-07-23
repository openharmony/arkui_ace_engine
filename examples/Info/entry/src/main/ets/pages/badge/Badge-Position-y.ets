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
  @State positionYIndex: number = 0;
  @State positionYList: (string | number | Resource | null | undefined)[] = [
    '10', $r('app.string.FeiFaZhi'), null, $r('app.color.pink'), undefined, $r('app.string.string_value_10'), 10,
    $r('app.string.format'), $r('app.string.number_10')
  ]
  @State positionYListStr: (string | number | Resource | null | undefined)[] = [
    '10',
    '$r("app.string.FeiFaZhi")-￥%123abc',
    'null',
    '$r("app.color.pink")--#FFF38FEA',
    'undefined',
    '$r("app.string.string_value_10")-L10-D1',
    '10',
    '$r("app.string.format")-yyyy-mm-dd',
    '$r("app.string.number_10")-L10-D30'
  ]

  @Builder
  itemBuilder(value: string) {
    Row() {
      Image('common/public_icon.svg').width(32).height(32).opacity(0.6)
      Text(value)
        .width(177)
        .height(21)
        .margin({ left: 15, right: 76 })
        .textAlign(TextAlign.Start)
        .fontColor('#182431')
        .fontWeight(500)
        .fontSize(16)
        .opacity(0.9)
      Image('common/public_icon_arrow_right.svg').width(12).height(24).opacity(0.6)
    }.width('100%').padding({ left: 12, right: 12 }).height(56)
  }

  build() {
    Column() {
      Row() {
        Text('Badge-position-y').fontSize(22).fontColor(0x000020).fontWeight(FontWeight.Bold)
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
            style: {
              fontSize: 15,
              badgeSize: 62,
              fontWeight: 18,
              badgeColor: '#ff354ee0',
            }
          }) {
            Text('原生badge').fontSize(16).fontColor(0x696969).width('95%')
          }.width(240).height(21).margin({ left: 15, right: 19 })
        }.width('100%').padding({ left: 12, right: 12 }).height(76)

        Badge({
          style: {
            fontSize: 15,
            badgeSize: 62,
            fontWeight: 18,
            badgeColor: '#ff354ee0',
          },
          value: 'New',
          position: { x: 10, y: this.positionYList[this.positionYIndex] },
        }) {
          Text('效果').fontSize(16).fontColor(0x696969).width('30%')
        }

        Text('当前positionY: ' + this.positionYListStr[this.positionYIndex])
          .fontSize(12)
          .fontColor(0x696969)
          .margin({ top: 50, bottom: 20 })

        Button('动态切换positionY')
          .onClick(() => {
            this.positionYIndex = (this.positionYIndex + 1) % this.positionYList.length;
          })

        Row() {
          Badge({
            value: 'New',
            position: { x: 10, y: $r('app.string.number_10') },
            style: {
              fontSize: 15,
              badgeSize: 62,
              fontWeight: 18,
              badgeColor: '#ff354ee0',
            }
          }) {
            Text('position-y：resource').fontSize(16).fontColor(0x696969).width('95%')
          }.width(240).height(21).margin({ left: 15, right: 11 })
        }.width('100%').padding({ left: 12, right: 12 }).height(76)

        Row() {
          Badge({
            value: 'New',
            position: { x: 10, y: '10' },
            style: {
              fontSize: 15,
              badgeSize: 62,
              fontWeight: 18,
              badgeColor: '#ff354ee0',
            }
          }) {
            Text('position-y：string').fontSize(16).fontColor(0x696969).width('95%')
          }.width(240).height(21).margin({ left: 15, right: 11 })
        }.width('100%').padding({ left: 12, right: 12 }).height(76)

        Row() {
          Badge({
            value: 'New',
            position: { x: 10, y: 10 },
            style: {
              fontSize: 15,
              badgeSize: 62,
              fontWeight: 18,
              badgeColor: '#ff354ee0',
            }
          }) {
            Text('position-y：number').fontSize(16).fontColor(0x696969).width('95%')
          }.width(240).height(21).margin({ left: 15, right: 11 })
        }.width('100%').padding({ left: 12, right: 12 }).height(76)

        Row() {
          Badge({
            value: 'New',
            position: { x: 10, y: undefined },
            style: {
              fontSize: 15,
              badgeSize: 62,
              fontWeight: 18,
              badgeColor: '#ff354ee0',
            }
          }) {
            Text('position-y：undefined').fontSize(16).fontColor(0x696969).width('95%')
          }.width(240).height(21).margin({ left: 15, right: 11 })
        }.width('100%').padding({ left: 12, right: 12 }).height(76)

        Row() {
          Badge({
            value: 'New',
            position: { x: 10, y: null },
            style: {
              fontSize: 15,
              badgeSize: 62,
              fontWeight: 18,
              badgeColor: '#ff354ee0',
            }
          }) {
            Text('position-y：null').fontSize(16).fontColor(0x696969).width('95%')
          }.width(240).height(21).margin({ left: 15, right: 11 })
        }.width('100%').padding({ left: 12, right: 12 }).height(76)
      }.width('100%').padding({ bottom: 12 })
    }.width('100%')
  }
}