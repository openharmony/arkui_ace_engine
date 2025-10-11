/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import ConfigurationConstant from '@ohos.app.ability.ConfigurationConstant';
import common from '@ohos.app.ability.common';

class ProgressModifier1 implements AttributeModifier<ProgressAttribute> {
  applyNormalAttribute(instance: ProgressAttribute): void {
    instance
      .color(Color.Red)
  }
}

class ProgressModifier2 implements AttributeModifier<ProgressAttribute> {
  applyNormalAttribute(instance: ProgressAttribute): void {
    instance
      .color(0xffff0000)
  }
}

class ProgressModifier3 implements AttributeModifier<ProgressAttribute> {
  applyNormalAttribute(instance: ProgressAttribute): void {
    instance
      .color('#FFFF7B14')
  }
}

class ProgressModifier4 implements AttributeModifier<ProgressAttribute> {
  applyNormalAttribute(instance: ProgressAttribute): void {
    instance
      .color($r('app.color.orange'))
  }
}

class ProgressModifier5 implements AttributeModifier<ProgressAttribute> {
  private gradientColor1: LinearGradient = new LinearGradient([{ color: Color.Orange, offset: 0.5 },
    { color: Color.Orange, offset: 1.0 }])

  applyNormalAttribute(instance: ProgressAttribute): void {
    instance
      .color(this.gradientColor1)
  }
}

class ProgressModifier6 implements AttributeModifier<ProgressAttribute> {
  private gradientColor2: LinearGradient = new LinearGradient([{ color: 0xffff0000, offset: 0.5 },
    { color: 0xffff0000, offset: 1.0 }])

  applyNormalAttribute(instance: ProgressAttribute): void {
    instance
      .color(this.gradientColor2)
  }
}

class ProgressModifier7 implements AttributeModifier<ProgressAttribute> {
  private gradientColor3: LinearGradient = new LinearGradient([{ color: '#FFFF7B14', offset: 0.5 },
    { color: '#FFFF7B14', offset: 1.0 }])

  applyNormalAttribute(instance: ProgressAttribute): void {
    instance
      .color(this.gradientColor3)
  }
}

class ProgressModifier8 implements AttributeModifier<ProgressAttribute> {
  private gradientColor4: LinearGradient = new LinearGradient([{ color: $r('app.color.start_blue'), offset: 0.5 },
    { color: $r('app.color.start_blue'), offset: 1.0 }])

  applyNormalAttribute(instance: ProgressAttribute): void {
    instance
      .color(this.gradientColor4)
  }
}

class ProgressModifier9 implements AttributeModifier<ProgressAttribute> {
  public colorIndex: number = 0;
  public colorList: (ResourceColor | null | undefined)[] = [
    Color.Red, $r('app.string.FeiFaZhi'), $r('app.color.pink'), $r('app.string.string_value_10'),
    $r('app.color.orange'), null, $r('app.color.orange'), undefined, $r('app.color.orange'), 0xffff0000,
    $r('app.color.pink'), '#FFFF7B14', $r('app.color.pink'), 'rgb(255, 100, 255)', $r('app.color.pink'),
    $r('app.color.pink')
  ]

  applyNormalAttribute(instance: ProgressAttribute): void {
    instance
      .color(this.colorList[this.colorIndex])
  }
}

@Entry
@Component
struct ProgressModifierExample3 {
  @State modifier1: ProgressModifier1 = new ProgressModifier1()
  @State modifier2: ProgressModifier2 = new ProgressModifier2()
  @State modifier3: ProgressModifier3 = new ProgressModifier3()
  @State modifier4: ProgressModifier4 = new ProgressModifier4()
  @State modifier5: ProgressModifier5 = new ProgressModifier5()
  @State modifier6: ProgressModifier6 = new ProgressModifier6()
  @State modifier7: ProgressModifier7 = new ProgressModifier7()
  @State modifier8: ProgressModifier8 = new ProgressModifier8()
  @State modifier9: ProgressModifier9 = new ProgressModifier9()
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
        Text('Progress组件')
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
        Row() {
          Text('Current Index: ' + this.modifier9.colorIndex + '/' + (this.modifier9.colorList.length - 1))
            .fontSize(12)
            .fontColor(0x696969)
          Button('动态切:' + this.modifier9.colorList[this.modifier9.colorIndex])
            .onClick(() => {
              this.modifier9.colorIndex = (this.modifier9.colorIndex + 1) % this.modifier9.colorList.length;
            })
          Progress({ value: 10, type: ProgressType.Capsule })
            .attributeModifier(this.modifier9)
        }
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