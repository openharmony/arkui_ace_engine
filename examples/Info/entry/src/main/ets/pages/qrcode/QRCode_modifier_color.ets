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
class MyIndicatorComponentModifier1 implements AttributeModifier<ProgressAttribute> {
  applyNormalAttribute(instance: ProgressAttribute): void {
    instance
      .color(Color.Red)
  }
}
class MyIndicatorComponentModifier2 implements AttributeModifier<ProgressAttribute> {
  applyNormalAttribute(instance: ProgressAttribute): void {
    instance
      .color(0xffff0000)
  }
}
class MyIndicatorComponentModifier3 implements AttributeModifier<ProgressAttribute> {
  applyNormalAttribute(instance: ProgressAttribute): void {
    instance
      .color('#FFFF7B14')
  }
}
class MyIndicatorComponentModifier4 implements AttributeModifier<ProgressAttribute> {
  applyNormalAttribute(instance: ProgressAttribute): void {
    instance
      .color($r('app.color.orange'))
  }
}
class MyIndicatorComponentModifier5 implements AttributeModifier<ProgressAttribute> {
  private gradientColor1: LinearGradient = new LinearGradient([{ color: Color.Orange, offset: 0.5 },
    { color: Color.Orange, offset: 1.0 }])
  applyNormalAttribute(instance: ProgressAttribute): void {
    instance
      .color(this.gradientColor1)
  }
}
class MyIndicatorComponentModifier6 implements AttributeModifier<ProgressAttribute> {
  private gradientColor2: LinearGradient = new LinearGradient([{ color: 0xffff0000, offset: 0.5 },
    { color: 0xffff0000, offset: 1.0 }])
  applyNormalAttribute(instance: ProgressAttribute): void {
    instance
      .color(this.gradientColor2)
  }
}
class MyIndicatorComponentModifier7 implements AttributeModifier<ProgressAttribute> {
  private gradientColor3: LinearGradient = new LinearGradient([{ color: '#FFFF7B14', offset: 0.5 },
    { color: '#FFFF7B14', offset: 1.0 }])
  applyNormalAttribute(instance: ProgressAttribute): void {
    instance
      .color(this.gradientColor3)
  }
}
class MyIndicatorComponentModifier8 implements AttributeModifier<ProgressAttribute> {
  private gradientColor4: LinearGradient = new LinearGradient([{ color: $r('app.color.start_blue'), offset: 0.5 },
    { color: $r('app.color.start_blue'), offset: 1.0 }])
  applyNormalAttribute(instance: ProgressAttribute): void {
    instance
      .color(this.gradientColor4)
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
  @State modifier6:myIndicatorComponentModifier6 = new MyIndicatorComponentModifier6()
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
        Text('LoadingProgress组件')
          .fontColor('#182431')
          .fontSize(30)
          .fontWeight(500)
          .lineHeight(14)
          .margin(20)
        Text('color-加载进度条前景色')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
        Text('color（color）：color.red')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(5)
        Progress({ value: 10, type: ProgressType.Linear })
          .width(200)
          .margin(5)
          .attributeModifier(this.modifier1)
          .borderWidth(14)
        Text('color（number）：0xffff0000')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(5)
        Progress({ value: 10, type: ProgressType.Linear })
          .width(200)
          .margin(5)
          .attributeModifier(this.modifier2)
          .borderWidth(14)
        Text('color（string）："#FFFF7B14"')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(5)
        Progress({ value: 10, type: ProgressType.Linear })
          .width(200)
          .margin(5)
          .attributeModifier(this.modifier3)
          .borderWidth(14)
        Text('color（Resource）：$r("app.color.orange")')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(5)
        Progress({ value: 10, type: ProgressType.Linear })
          .width(200)
          .margin(5)
          .attributeModifier(this.modifier4)
          .borderWidth(14)
        Text('color-LinearGradient（color）：Color.Orange')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(5)
        Progress({ value: 10, type: ProgressType.Linear })
          .width(200)
          .margin(5)
          .attributeModifier(this.modifier5)
          .borderWidth(14)
        Text('color-LinearGradient（number）：0xffff0000')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(5)
        Progress({ value: 10, type: ProgressType.Linear })
          .width(200)
          .margin(5)
          .attributeModifier(this.modifier6)
          .borderWidth(14)
        Text('color-LinearGradient（string）："#FFFF7B14"')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(5)
        Progress({ value: 10, type: ProgressType.Linear })
          .width(200)
          .margin(5)
          .attributeModifier(this.modifier7)
          .borderWidth(14)
        Text('color-LinearGradient（Resource）：$r("app.color.orange")')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(5)
        Progress({ value: 10, type: ProgressType.Linear })
          .width(200)
          .margin(5)
          .attributeModifier(this.modifier8)
          .borderWidth(14)
      }.width('100%')
    }
  }
}