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
  @State borderColorIndex: number = 0;
  @State colorNum: number = 0
  @State foregroundColor1: (Color | undefined)[] = [Color.Red, undefined, Color.Blue]
  @State borderColorList: (ResourceColor | null | undefined)[] = [
    0xffffff, $r('app.string.FeiFaZhi'), $r('app.color.pink'), $r('app.string.string_value_10'), null,
    $r('app.color.pink'), undefined, $r('app.color.pink'), '#ff0be32f',
    $r('app.color.pink'), 0x008000, $r('app.string.format'), $r('app.color.pink'), $r('app.color.pink')
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
        Text('Badge-foregroundColor').fontSize(22).fontColor(0x000020).fontWeight(FontWeight.Bold)
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
        Button('切前景色')
          .onClick(() => {
            this.colorNum = (this.colorNum + 1) % this.foregroundColor1.length;
          })
        Row() {
          Badge({
            value: 'New',
            style: {},
          }) {
            Text('原生badge').fontSize(16).fontColor(0x696969).width('95%')
          }.width(240).height(21).margin({ left: 15, right: 19 }).foregroundColor(this.foregroundColor1[this.colorNum])
        }.width('100%').padding({ left: 12, right: 12 }).height(76)
      }.width('100%').padding({ bottom: 12 })
    }.width('100%')
  }
}