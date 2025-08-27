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
import App from '@system.app';

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
        Text('TextClock-fontSize字体尺寸').fontSize(22).fontColor(0x000020).fontWeight(FontWeight.Bold)
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
      Text('fontSize-length-string：90px')
        .fontColor('#182431')
        .fontSize(18)
        .fontWeight(400)
        .lineHeight(14)
        .margin(20)
      TextClock()
        .fontSize('90px')
        .fontWeight(600)
        .fontColor('#ff57a9ec')
        .fontFamily($r('app.string.sans-serif'))
      Text('fontSize-length-null')
        .fontColor('#182431')
        .fontSize(18)
        .fontWeight(400)
        .lineHeight(14)
        .margin(20)
      TextClock()
        .fontSize(40)
        .fontWeight(600)
        .fontColor(0xffffb)
      Text('fontSize-length-undefined')
        .fontColor('#182431')
        .fontSize(18)
        .fontWeight(400)
        .lineHeight(14)
        .margin(20)
      TextClock()
        .fontSize(40)
        .fontWeight(600)
        .fontColor('rgb(255, 100, 255)')
      Text('fontSize-length-number：40')
        .fontColor('#182431')
        .fontSize(18)
        .fontWeight(400)
        .lineHeight(14)
        .margin(20)
      TextClock()
        .fontSize(40)
        .fontWeight(600)
        .fontColor(undefined)
      Text('fontSize-length-Resource:$r("app.string.number_50")')
        .fontColor('#182431')
        .fontSize(18)
        .fontWeight(400)
        .lineHeight(14)
        .margin(20)
      TextClock()
        .fontSize($r('app.string.number_50'))
        .fontWeight(600)
    }
    .height('100%')
    .width('100%')
  }
}