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
  @State badgeColorIndex: number = 0;
  @State badgeColorList: (ResourceColor | null | undefined)[] = [
    'rgba(61, 94, 252, 1.00)', $r('app.string.FeiFaZhi'), $r('app.string.string_value_10'), $r('app.string.format'),
    $r('app.color.pink'), $r('app.color.pink'), 0xffc0cb, $r('app.color.pink'), 0xffafff, $r('app.color.pink'),
    undefined, $r('app.color.pink'), null, $r('app.color.pink')
  ]
  @State colorNum: number = 0
  @State foregroundColor1: (Color | undefined)[] = [Color.Red, undefined, Color.Blue]

  build() {
    Column() {
      Row() {
        Text('Counter-backgroundColor背景颜色').fontSize(20).fontColor(0x000020).fontWeight(FontWeight.Bold)
      }
      .height('6%')
      .width('95%')
      .borderRadius(15)
      .backgroundColor('#ffa9cbd6',)
      .justifyContent(FlexAlign.Center)

      Row() {
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
      }

      Column() {
        Gauge({ value: 50 }).foregroundColor(this.foregroundColor1[this.colorNum])
      }
    }
    .height('100%')
    .width('100%')

  }
}