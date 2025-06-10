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
  build() {
    Column() {
      Row() {
        Text('QRCode-value二维码内容字符串').fontSize(22).fontColor(0x000020).fontWeight(FontWeight.Bold)
      }
      .height('6%')
      .width('95%')
      .borderRadius(15)
      .backgroundColor('#ffa9cbd6',)
      .justifyContent(FlexAlign.Center)
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
      Text('value-string-hellooo')
        .fontSize(14)
        .fontWeight(300)
        .lineHeight(14)
      QRCode('hellooo')
        .width(140)
        .height(140)
        .color($r('app.color.start_blue'))
      Text('value-string-null')
        .fontSize(14)
        .fontWeight(300)
        .lineHeight(14)
      QRCode(null)
        .width(140)
        .height(140)
        .color($r('app.color.start_blue'))
      Text('value-string-undefined')
        .fontSize(14)
        .fontWeight(300)
        .lineHeight(14)
      QRCode(undefined)
        .width(140)
        .height(140)
        .color($r('app.color.start_blue'))
    }
    .height('100%')
    .width('100%')
  }
}