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
class MyIndicatorComponentModifier1 implements AttributeModifier<TextClockAttribute> {
  applyNormalAttribute(instance: TextClockAttribute): void {
    instance
      .format('yyyy/MM/dd')
  }
}
class MyIndicatorComponentModifier2 implements AttributeModifier<TextClockAttribute> {
  applyNormalAttribute(instance: TextClockAttribute): void {
    instance
      .format(undefined)
  }
}
class MyIndicatorComponentModifier3 implements AttributeModifier<TextClockAttribute> {
  applyNormalAttribute(instance: TextClockAttribute): void {
    instance
      .format(null)
  }
}

@Entry
@Component
struct BadgeExample6 {
  @State modifier1:myIndicatorComponentModifier1 = new MyIndicatorComponentModifier1()
  @State modifier2:myIndicatorComponentModifier2 = new MyIndicatorComponentModifier2()
  @State modifier3:myIndicatorComponentModifier3 = new MyIndicatorComponentModifier3()
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
        Text('TextClock组件')
          .fontColor('#182431')
          .fontSize(30)
          .fontWeight(500)
          .lineHeight(14)
          .margin(20)
        Text('textShadow-阴影效果')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
        Text('format-string-("yyyy/MM/dd")')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(15)
        TextClock()
          .attributeModifier(this.modifier1)
        Text('format-string-undefined')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(15)
        TextClock()
          .attributeModifier(this.modifier2)
        Text('format-string-null')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(15)
        TextClock()
          .attributeModifier(this.modifier3)
      }.width('100%')
    }
  }
}