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
        Text('TextClock-FontColor字体颜色').fontSize(22).fontColor(0x000020).fontWeight(FontWeight.Bold)
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
      Text('FontColor-color')
        .fontColor('#182431')
        .fontSize(18)
        .fontWeight(400)
        .lineHeight(14)
        .margin(20)
      TextClock()
        .fontSize(40)
        .fontWeight(600)
        .fontColor('#ff57a9ec')
        .fontFamily($r('app.string.sans-serif'))
      Text('FontColor-number')
        .fontColor('#182431')
        .fontSize(18)
        .fontWeight(400)
        .lineHeight(14)
        .margin(20)
      TextClock()
        .fontSize(40)
        .fontWeight(600)
        .fontColor(0xffffb)
      Text('FontColor-string')
        .fontColor('#182431')
        .fontSize(18)
        .fontWeight(400)
        .lineHeight(14)
        .margin(20)
      TextClock()
        .fontSize(40)
        .fontWeight(600)
        .fontColor('rgb(255, 100, 255)')
      Text('FontColor-undefined')
        .fontColor('#182431')
        .fontSize(18)
        .fontWeight(400)
        .lineHeight(14)
        .margin(20)
      TextClock()
        .fontSize(40)
        .fontWeight(600)
        .fontColor(undefined)
      Text('FontColor-null')
        .fontColor('#182431')
        .fontSize(18)
        .fontWeight(400)
        .lineHeight(14)
        .margin(20)
      TextClock()
        .fontSize(40)
        .fontWeight(600)
        .fontColor(null)
      Text('FontColor-Resource')
        .fontColor('#182431')
        .fontSize(18)
        .fontWeight(400)
        .lineHeight(14)
        .margin(20)
      TextClock()
        .fontSize(40)
        .fontWeight(600)
        .fontColor($r('app.color.orange'))
    }
    .height('100%')
    .width('100%')
  }
}