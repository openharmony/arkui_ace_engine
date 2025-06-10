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
        Text('Counter-backgroundColor背景颜色').fontSize(20).fontColor(0x000020).fontWeight(FontWeight.Bold)
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
        Column() {
          Text('backgroundColor：resource-pink').fontSize(16).fontColor(0x696969).width('95%')
          Counter() {
            Text(this.value.toString())
          }
          .margin(10)
          .backgroundColor($r('app.color.pink'))
          .size({
            width: (100),
            height: (25),
          })
          .onInc(() => {
            this.value++;
          })
          .onDec(() => {
            this.value--;
          })
          .margin(5)
          Text('backgroundColor：string-\'rgb(255, 100, 255)\'').fontSize(16).fontColor(0x696969).width('95%')
          Counter() {
            Text(this.value.toString())
          }
          .backgroundColor('rgb(255, 100, 255)')
          .size({
            width: (100),
            height: (25),
          })
          .margin(10)
          .onInc(() => {
            this.value++;
          })
          .onDec(() => {
            this.value--;
          })
        }
        Text('backgroundColor：color-0xffc0cb').fontSize(16).fontColor(0x696969).width('95%')
        Counter() {
          Text(this.value.toString())
        }
        .backgroundColor(0xffc0cb)
        .size({
          width: (100),
          height: (25),
        })
        .onInc(() => {
          this.value++;
        })
        .onDec(() => {
          this.value--;
        })
        Text('backgroundColor：number-0xffafff').fontSize(16).fontColor(0x696969).width('95%')
        Counter() {
          Text(this.value.toString())
        }
        .margin(10)
        .backgroundColor(0xffafff)
        .size({
          width: (100),
          height: (25),
        })
        .onInc(() => {
          this.value++;
        })
        .onDec(() => {
          this.value--;
        })
        Text('backgroundColor：null').fontSize(16).fontColor(0x696969).width('95%')
        Counter() {
          Text(this.value.toString())
        }
        .margin(10)
        .backgroundColor(null)
        .size({
          width: (100),
          height: (25),
        })
        .onInc(() => {
          this.value++;
        })
        .onDec(() => {
          this.value--;
        })
        Text('backgroundColor：undefined').fontSize(16).fontColor(0x696969).width('95%')
        Counter() {
          Text(this.value.toString())
        }
        .margin(10)
        .backgroundColor(undefined)
        .size({
          width: (100),
          height: (25),
        })
        .onInc(() => {
          this.value++;
        })
        .onDec(() => {
          this.value--;
        })
      }
      .height('100%')
      .width('100%')
  }
}