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


class CounterModifier11 implements AttributeModifier<CounterAttribute> {
  applyNormalAttribute(instance: CounterAttribute): void {
    instance
      .backgroundColor($r('app.color.pink'))
  }
}

class CounterModifier12 implements AttributeModifier<CounterAttribute> {
  applyNormalAttribute(instance: CounterAttribute): void {
    instance
      .backgroundColor('rgb(255, 100, 255)')
  }
}

class CounterModifier13 implements AttributeModifier<CounterAttribute> {
  applyNormalAttribute(instance: CounterAttribute): void {
    instance
      .backgroundColor(0xffc0cb)
  }
}

class CounterModifier14 implements AttributeModifier<CounterAttribute> {
  applyNormalAttribute(instance: CounterAttribute): void {
    instance
      .backgroundColor(0xffafff)
  }
}

class CounterModifier15 implements AttributeModifier<CounterAttribute> {
  applyNormalAttribute(instance: CounterAttribute): void {
    instance
      .backgroundColor(null)
  }
}

class CounterModifier16 implements AttributeModifier<CounterAttribute> {
  applyNormalAttribute(instance: CounterAttribute): void {
    instance
      .backgroundColor(undefined)
  }
}

class CounterModifier17 implements AttributeModifier<CounterAttribute> {
  public backgroundColorIndex: number = 0;
  public backgroundColorList: (ResourceColor | null | undefined)[] = [
    'rgba(61, 94, 252, 1.00)', $r('app.string.FeiFaZhi'), $r('app.color.pink'), $r('app.string.string_value_10'),
    111122333333222211122, $r('app.color.pink'), $r('app.color.ColorRed'), 0xffc0cb, $r('app.color.ColorGreen'),
    0xffafff, $r('app.color.pink'), undefined, $r('app.color.pink'), null, $r('app.color.pink')
  ]
  public backgroundColorListStr: string[] = [
    'rgba(61, 94, 252, 1.00)',
    '$r("app.string.FeiFaZhi")-￥%123abc',
    '$r("app.color.pink")-#FFF38FEA',
    '$r("app.string.string_value_10")-L10-D1',
    '111122333333222211122',
    '$r("app.color.pink")-#FFF38FEA',
    '$r("app.color.ColorRed")-L(#FF0000)-D(#00FFFF)',
    '0xffc0cb',
    '$r("app.color.ColorGreen")-L(#008000)-D(#FF7F7F)',
    '0xffafff',
    '$r("app.color.pink")-#FFF38FEA',
    'undefined',
    '$r("app.color.pink")-#FFF38FEA',
    'null',
    '$r("app.color.pink")-#FFF38FEA',
  ]

  applyNormalAttribute(instance: CounterAttribute): void {
    instance
      .backgroundColor(this.backgroundColorList[this.backgroundColorIndex])
  }
}

@Entry
@Component
struct Page {
  @State message: string = 'Hello World';
  @State value: number = 0;
  @State isDark: boolean = false;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext
  @State modifier1: CounterModifier11 = new CounterModifier11()
  @State modifier2: CounterModifier12 = new CounterModifier12()
  @State modifier3: CounterModifier13 = new CounterModifier13()
  @State modifier4: CounterModifier14 = new CounterModifier14()
  @State modifier5: CounterModifier15 = new CounterModifier15()
  @State modifier6: CounterModifier16 = new CounterModifier16()
  @State modifier7: CounterModifier17 = new CounterModifier17()

  build() {
    Column() {
      Row() {
        Text('Counter-backgroundColor背景颜色-Modifier').fontSize(14).fontColor(0x000020).fontWeight(FontWeight.Bold)
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

      Text('当前backgroundColor: ' + this.modifier7.backgroundColorListStr[this.modifier7.backgroundColorIndex])
        .fontSize(12)
        .fontColor(0x696969)
        .margin({ top: 20, bottom: 20 })

      Button('动态切换backgroundColor')
        .onClick(() => {
          this.modifier7.backgroundColorIndex =
            (this.modifier7.backgroundColorIndex + 1) % this.modifier7.backgroundColorListStr.length;
        })

      Counter() {
        Text(this.value.toString())
      }
      .margin(10)
      .attributeModifier(this.modifier7)
      .size({
        width: (100),
        height: (25),
      })
      .onInc(() => {
        this.value++;
      })
      .onDec(() => {
        this.value--;
      })


      Column() {
        Text('原生counter').fontSize(16).fontColor(0x696969).width('95%')
        Counter() {
          Text(this.value.toString())
        }

        Text('backgroundColor：resource-pink').fontSize(16).fontColor(0x696969).width('95%')
        Counter() {
          Text(this.value.toString())
        }
        .margin(10)

        .attributeModifier(this.modifier1)
        .size({
          width: (100),
          height: (25),
        })
        .onInc(() => {
          this.value++;
        })
        .onDec(() => {
          this.value--;
        })
        .margin(5)

        Text('backgroundColor：string-"rgb(255, 100, 255)"').fontSize(16).fontColor(0x696969).width('95%')
        Counter() {
          Text(this.value.toString())
        }
        .attributeModifier(this.modifier2)
        .size({
          width: (100),
          height: (25),
        })
        .margin(10)
        .onInc(() => {
          this.value++;
        })
        .onDec(() => {
          this.value--;
        })
      }

      Text('backgroundColor：color-0xffc0cb').fontSize(16).fontColor(0x696969).width('95%')
      Counter() {
        Text(this.value.toString())
      }

      .attributeModifier(this.modifier3)
      .size({
        width: (100),
        height: (25),
      })
      .onInc(() => {
        this.value++;
      })
      .onDec(() => {
        this.value--;
      })

      Text('backgroundColor：number-0xffafff').fontSize(16).fontColor(0x696969).width('95%')
      Counter() {
        Text(this.value.toString())
      }
      .margin(10)

      .attributeModifier(this.modifier4)
      .size({
        width: (100),
        height: (25),
      })
      .onInc(() => {
        this.value++;
      })
      .onDec(() => {
        this.value--;
      })

      Text('backgroundColor：null').fontSize(16).fontColor(0x696969).width('95%')
      Counter() {
        Text(this.value.toString())
      }
      .margin(10)
      .attributeModifier(this.modifier5)
      .size({
        width: (100),
        height: (25),
      })
      .onInc(() => {
        this.value++;
      })
      .onDec(() => {
        this.value--;
      })

      Text('backgroundColor：undefined').fontSize(16).fontColor(0x696969).width('95%')
      Counter() {
        Text(this.value.toString())
      }
      .margin(10)
      .attributeModifier(this.modifier6)
      .size({
        width: (100),
        height: (25),
      })
      .onInc(() => {
        this.value++;
      })
      .onDec(() => {
        this.value--;
      })
    }
    .height('100%')
    .width('100%')
  }
}