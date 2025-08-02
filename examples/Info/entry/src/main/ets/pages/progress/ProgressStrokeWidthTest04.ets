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
struct ProgressStrokeWidthTest04 {
  @State isDark: boolean = false;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext
  @State strokeWidth01: Resource = $r('app.string.string_value_20')
  @State strokeWidth02: Resource = $r('app.float.float_value_20')

  build() {
    Column({ space: 15 }) {
      Row() {
        Text('StrokeWidth属性测试04')
          .fontSize(22)
          .fontColor(0x000000)
          .textAlign(TextAlign.Start)
          .fontWeight(FontWeight.Bold)
      }
      .height('6%')
      .width('95%')
      .borderRadius(15)
      .backgroundColor(0x7B68EE)
      .justifyContent(FlexAlign.Center)
      .margin({ bottom: 10 })

      Row() {
        Text('strokeWidth Resource').fontSize(12).fontColor(0xCCCCCC).width('45%')
        Button('ChangeDarkMode').backgroundColor(0x7B68EE).width(180).height(30)
          .onClick(() => {
            if (this.isDark) {
              this.isDark = false;
              this.context.getApplicationContext().setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_LIGHT);
            } else {
              this.isDark = true;
              this.context.getApplicationContext().setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_DARK);
            }
          })
      }

      Text('Linear Progress').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Progress({ value: 10, type: ProgressType.Linear }).width(200).style({ strokeWidth: this.strokeWidth01 })
      Progress({ value: 20, total: 150, type: ProgressType.Linear }).color(Color.Pink).value(50).width(200)
        .style({ strokeWidth: this.strokeWidth02 })


      Text('ScaleRing Progress').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Row({ space: 40 }) {
        Progress({ value: 10, type: ProgressType.ScaleRing }).width(100).style({ strokeWidth: this.strokeWidth01 })
        Progress({ value: 20, total: 150, type: ProgressType.ScaleRing })
          .color(Color.Pink).value(50).width(100)
          .style({ strokeWidth: 15, scaleCount: 15, scaleWidth: 5 })
      }

      Row({ space: 40 }) {
        Progress({ value: 20, total: 150, type: ProgressType.ScaleRing })
          .color(Color.Pink).value(50).width(100)
          .style({ strokeWidth: this.strokeWidth02, scaleCount: 20, scaleWidth: 5 })
        Progress({ value: 20, total: 150, type: ProgressType.ScaleRing })
          .color(Color.Pink).value(50).width(100)
          .style({ strokeWidth: this.strokeWidth02, scaleCount: 30, scaleWidth: 3 })
      }

      Text('Ring Progress').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Row({ space: 40 }) {
        Progress({ value: 10, type: ProgressType.Ring }).width(100).style({ strokeWidth: this.strokeWidth01 })
        Progress({ value: 20, total: 150, type: ProgressType.Ring })
          .color(Color.Pink).value(50).width(100)
          .style({ strokeWidth: this.strokeWidth02 })
      }
    }.width('100%').margin({ top: 30 })
  }
}