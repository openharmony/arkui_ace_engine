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
class MyIndicatorComponentModifier1 implements AttributeModifier<TextTimerAttribute> {
  applyNormalAttribute(instance: TextTimerAttribute): void {
    instance
      .fontWeight(600)
  }
}
class MyIndicatorComponentModifier2 implements AttributeModifier<TextTimerAttribute> {
  applyNormalAttribute(instance: TextTimerAttribute): void {
    instance
      .fontWeight('600')
  }
}
class MyIndicatorComponentModifier3 implements AttributeModifier<TextTimerAttribute> {
  applyNormalAttribute(instance: TextTimerAttribute): void {
    instance
      .fontWeight(undefined)
  }
}
class MyIndicatorComponentModifier4 implements AttributeModifier<TextTimerAttribute> {
  applyNormalAttribute(instance: TextTimerAttribute): void {
    instance
      .fontWeight(null)
  }
}
class MyIndicatorComponentModifier5 implements AttributeModifier<TextTimerAttribute> {
  applyNormalAttribute(instance: TextTimerAttribute): void {
    instance
      .fontWeight(FontWeight.Normal)
  }
}

@Entry
@Component
struct BadgeExample6 {
  @State modifier1:myIndicatorComponentModifier1 = new MyIndicatorComponentModifier1()
  @State modifier2:myIndicatorComponentModifier2 = new MyIndicatorComponentModifier2()
  @State modifier3:myIndicatorComponentModifier3 = new MyIndicatorComponentModifier3()
  @State modifier4:myIndicatorComponentModifier4 = new MyIndicatorComponentModifier4()
  @State modifier5:myIndicatorComponentModifier4 = new MyIndicatorComponentModifier5()
  @State isDark: boolean = false;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext

  build() {
    Scroll() {
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
        Text('TextTimer组件')
          .fontColor('#182431')
          .fontSize(30)
          .fontWeight(500)
          .lineHeight(14)
          .margin(20)
        Text('fontWeight-字体颜色')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
        TextTimer()
          .attributeModifier(this.modifier1)
        Text('fontWeight-number')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(20)
        TextTimer()
          .attributeModifier(this.modifier1)
        Text('fontWeight-string')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(20)
        TextTimer()
          .attributeModifier(this.modifier2)
        Text('fontWeight-undefined')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(20)
        TextTimer()
          .attributeModifier(this.modifier3)
        Text('fontWeight-null')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(20)
        TextTimer()
          .attributeModifier(this.modifier4)
        Text('fontWeight-ForWeight')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(20)
        TextTimer()
          .attributeModifier(this.modifier5)
      }.width('100%')
    }
  }
}