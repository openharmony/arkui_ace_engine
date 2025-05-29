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
        Text('Counter-Size尺寸').fontSize(22).fontColor(0x000020).fontWeight(FontWeight.Bold)
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

      Row() {
        Column() {
          Text('Size width：Resource-120').fontSize(16).fontColor(0x696969).width('95%')
          Counter() {
            Text(this.value.toString())
          }
          .size({
            width: ($r('app.string.number_120')),
            height: (25),
          })
          .onInc(() => {
            this.value++;
          })
          .onDec(() => {
            this.value--;
          })

          Text('Size width：string-\'120\'').fontSize(16).fontColor(0x696969).width('95%')
          Counter() {
            Text(this.value.toString())
          }
          .size({
            width: '120',
            height: (25),
          })
          .onInc(() => {
            this.value++;
          })
          .onDec(() => {
            this.value--;
          })
          Text('Size width：number-120').fontSize(16).fontColor(0x696969).width('95%')
          Counter() {
            Text(this.value.toString())
          }
          .size({
            width: (120),
            height: (25),
          })
          .onInc(() => {
            this.value++;
          })
          .onDec(() => {
            this.value--;
          })
          Text('Size width：undefined').fontSize(16).fontColor(0x696969).width('95%')
          Counter() {
            Text(this.value.toString())
          }
          .size({
            width: (undefined),
            height: (25),
          })
          .onInc(() => {
            this.value++;
          })
          .onDec(() => {
            this.value--;
          })

          Text('Size width：null').fontSize(16).fontColor(0x696969).width('95%')
          Counter() {
            Text(this.value.toString())
          }
          .size({
            width: (null),
            height: (25),
          })
          .onInc(() => {
            this.value++;
          })
          .onDec(() => {
            this.value--;
          })
        }
      }

      Text('Size height：Resource-30').fontSize(16).fontColor(0x696969).width('95%')
      Counter() {
        Text(this.value.toString())
      }
      .size({
        width: (120),
        height: ($r('app.string.number_30')),
      })
      .onInc(() => {
        this.value++;
      })
      .onDec(() => {
        this.value--;
      })
      Text('Size height：string：\'30\'').fontSize(16).fontColor(0x696969).width('95%')
      Counter() {
        Text(this.value.toString())
      }
      .size({
        width: (120),
        height: ('30'),
      })
      .onInc(() => {
        this.value++;
      })
      .onDec(() => {
        this.value--;
      })
      Text('Size height：number：30').fontSize(16).fontColor(0x696969).width('95%')
      Counter() {
        Text(this.value.toString())
      }
      .size({
        width: (120),
        height: (30),
      })
      .onInc(() => {
        this.value++;
      })
      .onDec(() => {
        this.value--;
      })
      Text('Size height：undefined').fontSize(16).fontColor(0x696969).width('95%')
      Counter() {
        Text(this.value.toString())
      }
      .size({
        width: (120),
        height: (undefined),
      })
      .onInc(() => {
        this.value++;
      })
      .onDec(() => {
        this.value--;
      })
      Text('Size height：null').fontSize(16).fontColor(0x696969).width('95%')
      Counter() {
        Text(this.value.toString())
      }
      .size({
        width: (120),
        height: (null),
      })
      .onInc(() => {
        this.value++;
      })
      .onDec(() => {
        this.value--;
      })
      Text('Size：undefined').fontSize(16).fontColor(0x696969).width('95%')
      Counter() {
        Text(this.value.toString())
      }
      .size(undefined)
      .onInc(() => {
        this.value++;
      })
      .onDec(() => {
        this.value--;
      })
      Text('Size：null').fontSize(16).fontColor(0x696969).width('95%')
      Counter() {
        Text(this.value.toString())
      }
      .size(null)
      .onInc(() => {
        this.value++;
      })
      .onDec(() => {
        this.value--;
      })
    }
  }
}