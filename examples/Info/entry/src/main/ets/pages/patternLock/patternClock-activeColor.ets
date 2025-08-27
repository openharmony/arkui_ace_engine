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
  @State value: number = 0;
  @State isDark: boolean = false;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext
  private patternLockController: PatternLockController = new PatternLockController()

  build() {
    Column() {

      Row() {
        Text('PatternLock-activeColor').fontSize(22).fontColor(0x000020).fontWeight(FontWeight.Bold)
      }
      .height('6%')
      .width('95%')
      .borderRadius(15)
      .backgroundColor('#ffa9cbd6',)
      .justifyContent(FlexAlign.Center)
      Row() {
        Text('“激活”状态的填充颜色').fontSize(16).fontColor(0x000020).fontWeight(FontWeight.Bold)
      }
      .height('6%')
      .width('95%')
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

      Text('color-0xffa500')
        .fontColor('#182431')
        .fontSize(14)
        .fontWeight(300)
        .lineHeight(14)
      PatternLock(this.patternLockController)
        .sideLength(70)
        .pathStrokeWidth(5)
        .activeColor(0xffa500)

      Text('string-rgb(255, 100, 255)')
        .fontColor('#182431')
        .fontSize(14)
        .fontWeight(300)
        .lineHeight(14)
      PatternLock(this.patternLockController)
        .sideLength(70)
        .pathStrokeWidth(5)
        .activeColor('rgb(255, 100, 255)')
      Text('string-null')
        .fontColor('#182431')
        .fontSize(14)
        .fontWeight(300)
        .lineHeight(14)
      PatternLock(this.patternLockController)
        .sideLength(70)
        .pathStrokeWidth(5)
        .activeColor(null)

      Text('string-undefined')
        .fontColor('#182431')
        .fontSize(14)
        .fontWeight(300)
        .lineHeight(14)
      PatternLock(this.patternLockController)
        .sideLength(70)
        .pathStrokeWidth(5)
        .activeColor(undefined)

      Text('number-0xffff0000')
        .fontColor('#182431')
        .fontSize(14)
        .fontWeight(300)
        .lineHeight(14)
      PatternLock(this.patternLockController)
        .sideLength(70)
        .pathStrokeWidth(5)
        .activeColor(0xffff0000)

      Text('Resource-app.color.start_green')
        .fontColor('#182431')
        .fontSize(14)
        .fontWeight(300)
        .lineHeight(14)
      PatternLock(this.patternLockController)
        .sideLength(70)
        .pathStrokeWidth(5)
        .activeColor($r('app.color.start_green'))
    }
    .height('100%')
    .width('100%')
  }
}