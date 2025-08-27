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
import { LengthUnit } from '@kit.ArkUI';

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
        Text('PatternLock-activateCircleStyle').fontSize(22).fontColor(0x000020).fontWeight(FontWeight.Bold)
      }
      .height('6%')
      .width('95%')
      .borderRadius(15)
      .backgroundColor('#ffa9cbd6',)
      .justifyContent(FlexAlign.Center)
      Text('(color、radius、enableWaveEffect、enableForeground)')
        .fontColor('#182431')
        .fontSize(18)
        .fontWeight(500)
        .lineHeight(14)
        .margin(5)
      Text('宫格圆点在“激活”状态的背景圆环样式')
        .fontColor('#182431')
        .fontSize(16)
        .fontWeight(500)
        .lineHeight(14)
        .margin(5)
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
          Text('color-color-0xffa500')
            .fontSize(14)
            .fontWeight(300)
            .lineHeight(14)
          PatternLock(this.patternLockController)
            .sideLength(70)
            .pathStrokeWidth(5)
            .activateCircleStyle({ color: 0xffa500 })
            .backgroundColor('#ffbbd1ea')
          Text('color-number-0xffffaa')
            .fontSize(14)
            .fontWeight(300)
            .lineHeight(14)
          PatternLock(this.patternLockController)
            .sideLength(70)
            .pathStrokeWidth(5)
            .activateCircleStyle({ color: 0xffffaa })
            .backgroundColor('#ffbbd1ea')
          Text('color-string-‘rgb(255, 100, 255)’')
            .fontSize(14)
            .fontWeight(300)
            .lineHeight(14)
          PatternLock(this.patternLockController)
            .sideLength(70)
            .pathStrokeWidth(5)
            .activateCircleStyle({ color: 'rgb(255, 100, 255)' })
            .backgroundColor('#ffbbd1ea')
          Row() {
            Column() {
              Text('color-string-undefined')
                .fontSize(14)
                .fontWeight(300)
                .lineHeight(14)
              PatternLock(this.patternLockController)
                .sideLength(70)
                .pathStrokeWidth(5)
                .activateCircleStyle({ color: undefined })
                .backgroundColor('#ffbbd1ea')
            }        .width('50%')
            Column() {
              Text('color-string-null')
                .fontSize(14)
                .fontWeight(300)
                .lineHeight(14)
              PatternLock(this.patternLockController)
                .sideLength(70)
                .pathStrokeWidth(5)
                .backgroundColor('#ffbbd1ea')
                .activateCircleStyle({ color: null })
            }        .width('50%')
          }
          Text('color-Resource-$r('app.color.grey')')
            .fontSize(14)
            .fontWeight(300)
            .lineHeight(14)
          PatternLock(this.patternLockController)
            .sideLength(70)
            .pathStrokeWidth(5)
            .activateCircleStyle({ color: $r('app.color.grey') })
            .backgroundColor('#ffbbd1ea')
        }
        .width('50%')
        Column() {
          Text('radius-number-undefined')
            .fontSize(14)
            .fontWeight(300)
            .lineHeight(14)
          PatternLock(this.patternLockController)
            .sideLength(70)
            .pathStrokeWidth(5)
            .activateCircleStyle({ radius: undefined })
            .backgroundColor('#ffead7bb')
          Text('radius-number-null')
            .fontSize(14)
            .fontWeight(300)
            .lineHeight(14)
          PatternLock(this.patternLockController)
            .sideLength(70)
            .pathStrokeWidth(5)
            .backgroundColor('#ffead7bb')
          .activateCircleStyle(null)
          Text('radius-LengthUnit-9VP' )
            .fontSize(14)
            .fontWeight(300)
            .lineHeight(14)
          PatternLock(this.patternLockController)
            .sideLength(70)
            .pathStrokeWidth(5)
            .backgroundColor('#ffead7bb')
            .activateCircleStyle({
              color: '#fff50000',
              radius: { value: 9, unit: LengthUnit.VP },
            })
          Text('enableForeground圆环是否在前景显示')
            .fontSize(14)
            .fontWeight(300)
            .lineHeight(14)
          Row() {
            Column() {
              Text('前景-true')
                .fontColor('#ff054894')
                .fontSize(14)
                .fontWeight(300)
                .lineHeight(14)
              PatternLock(this.patternLockController)
                .sideLength(70)
                .pathStrokeWidth(5)
                .activateCircleStyle({ color: 0xffa500 ,enableForeground:true})
                .backgroundColor('#ffbbd1ea')
            }
            .width('50%')
            Column() {
              Text('前景-false')
                .fontColor('#ff054894')
                .fontSize(14)
                .fontWeight(300)
                .lineHeight(14)
              PatternLock(this.patternLockController)
                .sideLength(70)
                .pathStrokeWidth(5)
                .activateCircleStyle({ color: 0xffa500, enableForeground: false })
                .backgroundColor('#ffbbd1ea')
            }
            .width('50%')
          }.backgroundColor('#ffdee7f6')
          .width('100%')
          .padding(7)
          .alignItems(VerticalAlign.Center)
          .justifyContent(FlexAlign.Center)
          Text('enableWaveEffect波浪效果')
            .fontSize(14)
            .fontWeight(300)
            .lineHeight(14)
          Row() {
            Column() {
              Text('波浪-true')
                .fontColor('#ff054894')
                .fontSize(14)
                .fontWeight(300)
                .lineHeight(14)
              PatternLock(this.patternLockController)
                .sideLength(70)
                .pathStrokeWidth(5)
                .activateCircleStyle({ color: 0xffa500 })
                .backgroundColor('#ffbbd1ea')
            }.margin(5)
            Column() {
              Text('波浪-false')
                .fontColor('#ff054894')
                .fontSize(14)
                .fontWeight(300)
                .lineHeight(14)
              PatternLock(this.patternLockController)
                .sideLength(70)
                .pathStrokeWidth(5)
                .activateCircleStyle({ color: 0xffa500, enableWaveEffect: false })
                .backgroundColor('#ffbbd1ea')
            }.margin(5)
          }.backgroundColor('#ffdee7f6')
          .width('100%')
          .alignItems(VerticalAlign.Center)
          .justifyContent(FlexAlign.Center)
        }
        .width('50%')
      }
    }
    .height('100%')
    .width('100%')
  }
}