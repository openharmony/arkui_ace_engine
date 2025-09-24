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
      .style({
        borderColor: Color.Blue,
      })
  }
}

class ProgressModifier2 implements AttributeModifier<ProgressAttribute> {
  applyNormalAttribute(instance: ProgressAttribute): void {
    instance
      .style({
        borderColor: 0xffff0000,
      })
  }
}

class ProgressModifier3 implements AttributeModifier<ProgressAttribute> {
  applyNormalAttribute(instance: ProgressAttribute): void {
    instance
      .style({
        borderColor: '#FFFF7B14',
      })
  }
}

class ProgressModifier4 implements AttributeModifier<ProgressAttribute> {
  applyNormalAttribute(instance: ProgressAttribute): void {
    instance
      .style({
        borderColor: $r('app.color.orange'),
      })
  }
}

class ProgressModifier5 implements AttributeModifier<ProgressAttribute> {
  public colorIndex: number = 0;
  public colorList: (ResourceColor | null | undefined)[] = [
    Color.Red, $r('app.string.FeiFaZhi'), $r('app.color.pink'), $r('app.string.string_value_10'),
    $r('app.color.orange'), null, $r('app.color.orange'), undefined, $r('app.color.orange'), 0xffff0000,
    $r('app.color.pink'), '#FFFF7B14', $r('app.color.pink'), 'rgb(255, 100, 255)', $r('app.color.pink'),
    $r('app.color.pink')
  ]

  applyNormalAttribute(instance: ProgressAttribute): void {
    instance
      .style({
        borderColor: this.colorList[this.colorIndex],
      })
  }
}

@Entry
@Component
struct ProgressModifierExample2 {
  @State modifier1: ProgressModifier1 = new ProgressModifier1()
  @State modifier2: ProgressModifier2 = new ProgressModifier2()
  @State modifier3: ProgressModifier3 = new ProgressModifier3()
  @State modifier4: ProgressModifier4 = new ProgressModifier4()
  @State modifier5: ProgressModifier5 = new ProgressModifier5()
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
        Row() {
          Text('Current Index: ' + this.modifier5.colorIndex + '/' + (this.modifier5.colorList.length - 1))
            .fontSize(12)
            .fontColor(0x696969)
          Button('动态切:' + this.modifier5.colorList[this.modifier5.colorIndex])
            .onClick(() => {
              this.modifier5.colorIndex = (this.modifier5.colorIndex + 1) % this.modifier5.colorList.length;
            })
          Progress({ value: 10, type: ProgressType.Capsule })
            .attributeModifier(this.modifier5)
        }

        Text('borderColor-内描边颜色')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
        Text('borderColor（color）：color.red')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(5)
        Progress({ value: 10, type: ProgressType.Capsule })
          .width(200)
          .margin(5)
          .attributeModifier(this.modifier1)

        Text('borderColor（number）：0xffff0000')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(5)
        Progress({ value: 10, type: ProgressType.Capsule })
          .width(200)
          .margin(5)
          .attributeModifier(this.modifier2)
        Text('borderColor（string）："#FFFF7B14"')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(5)
        Progress({ value: 10, type: ProgressType.Capsule })
          .width(200)
          .margin(5)
          .attributeModifier(this.modifier3)
        Text('borderColor（Resource）：$r("app.color.orange")')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(5)
        Progress({ value: 10, type: ProgressType.Capsule })
          .width(200)
          .margin(5)
          .attributeModifier(this.modifier4)
      }.width('100%')
    }
  }
}