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
      .textShadow({
        radius: 15,
      })
  }
}
class MyIndicatorComponentModifier2 implements AttributeModifier<TextClockAttribute> {
  applyNormalAttribute(instance: TextClockAttribute): void {
    instance
      .textShadow({
        radius: $r('app.string.number_10'),
      })
  }
}
class MyIndicatorComponentModifier3 implements AttributeModifier<TextClockAttribute> {
  applyNormalAttribute(instance: TextClockAttribute): void {
    instance
      .textShadow({
        radius: $r('app.string.number_10'),
        color: Color.Blue
      })
  }
}
class MyIndicatorComponentModifier4 implements AttributeModifier<TextClockAttribute> {
  applyNormalAttribute(instance: TextClockAttribute): void {
    instance
      .textShadow({
        radius: $r('app.string.number_10'),
        color: '#ff57a9ec'
      })
  }
}
class MyIndicatorComponentModifier5 implements AttributeModifier<TextClockAttribute> {
  applyNormalAttribute(instance: TextClockAttribute): void {
    instance
      .textShadow({
        radius: $r('app.string.number_10'),
        color: $r('app.color.start_red')
      })
  }
}
class MyIndicatorComponentModifier7 implements AttributeModifier<TextClockAttribute> {
  applyNormalAttribute(instance: TextClockAttribute): void {
    instance
      .textShadow({
        radius: $r('app.string.number_10'),
        offsetX: 10,
        offsetY: 10,
      })
  }
}
class MyIndicatorComponentModifier8 implements AttributeModifier<TextClockAttribute> {
  applyNormalAttribute(instance: TextClockAttribute): void {
    instance
      .textShadow({
        radius: $r('app.string.number_10'),
        offsetX: $r('app.string.number_10'),
        offsetY: $r('app.string.number_10')
      })
  }
}
@Entry
@Component
struct BadgeExample6 {
  @State modifier1:myIndicatorComponentModifier1 = new MyIndicatorComponentModifier1()
  @State modifier2:myIndicatorComponentModifier2 = new MyIndicatorComponentModifier2()
  @State modifier3:myIndicatorComponentModifier3 = new MyIndicatorComponentModifier3()
  @State modifier4:myIndicatorComponentModifier4 = new MyIndicatorComponentModifier4()
  @State modifier5:myIndicatorComponentModifier5 = new MyIndicatorComponentModifier5()
  @State modifier7:myIndicatorComponentModifier7 = new MyIndicatorComponentModifier7()
  @State modifier8:myIndicatorComponentModifier8 = new MyIndicatorComponentModifier8()
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
        Text('textShadow-radius（number）：15')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(15)
        TextClock()
          .attributeModifier(this.modifier1)
        Text('textShadow-radius（Resource）：$r("app.string.number_10")')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(15)
        TextClock()
          .attributeModifier(this.modifier2)
        Text('textShadow-color（color）：color.blue')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(15)
        TextClock()
          .attributeModifier(this.modifier3)
        Text('textShadow-color（string）：#ff57a9ec')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(15)
        TextClock()
          .attributeModifier(this.modifier4)
        Text('textShadow-color（Resource）：$r("app.color.start_red")')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(15)
        TextClock()
          .attributeModifier(this.modifier5)
        Text('textShadow-offsetX/Y（number）：10')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(15)
        TextClock()
          .attributeModifier(this.modifier7)
        Text('textShadow-offsetX/Y（Resource）：$r("app.string.number_10")')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(15)
        TextClock()
          .attributeModifier(this.modifier8)
      }.width('100%')
    }
  }
}