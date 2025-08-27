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

class CounterModifier1 implements AttributeModifier<CounterAttribute> {
  applyNormalAttribute(instance: CounterAttribute): void {
    instance.width($r('app.string.number_120'))
  }
}

class CounterModifier2 implements AttributeModifier<CounterAttribute> {
  applyNormalAttribute(instance: CounterAttribute): void {
    instance
      .size({
        width: '100',
        height: (25),
      })
  }
}

class CounterModifier3 implements AttributeModifier<CounterAttribute> {
  applyNormalAttribute(instance: CounterAttribute): void {
    instance
      .size({
        width: (90),
        height: (25),
      })
  }
}

class CounterModifier4 implements AttributeModifier<CounterAttribute> {
  applyNormalAttribute(instance: CounterAttribute): void {
    instance
      .size({
        width: (undefined),
        height: (25),
      })
  }
}

class CounterModifier5 implements AttributeModifier<CounterAttribute> {
  applyNormalAttribute(instance: CounterAttribute): void {
    instance
      .size({
        width: (null),
        height: (25),
      })
  }
}

class CounterModifier6 implements AttributeModifier<CounterAttribute> {
  applyNormalAttribute(instance: CounterAttribute): void {
    instance.height($r('app.string.number_50'))
  }
}

class CounterModifier7 implements AttributeModifier<CounterAttribute> {
  applyNormalAttribute(instance: CounterAttribute): void {
    instance
      .size({
        width: (120),
        height: ('20'),

      })
  }
}

class CounterModifier8 implements AttributeModifier<CounterAttribute> {
  applyNormalAttribute(instance: CounterAttribute): void {
    instance
      .size({
        width: (120),
        height: (70),
      })
  }
}

class CounterModifier9 implements AttributeModifier<CounterAttribute> {
  applyNormalAttribute(instance: CounterAttribute): void {
    instance
      .size({
        width: (120),
        height: (undefined),
      })
  }
}

class CounterModifier10 implements AttributeModifier<CounterAttribute> {
  applyNormalAttribute(instance: CounterAttribute): void {
    instance
      .size({
        width: (120),
        height: (null),
      })
  }
}

class CounterModifier11 implements AttributeModifier<CounterAttribute> {
  applyNormalAttribute(instance: CounterAttribute): void {
    instance
      .size(undefined)
  }
}

class CounterModifier12 implements AttributeModifier<CounterAttribute> {
  applyNormalAttribute(instance: CounterAttribute): void {
    instance
      .size(null)
  }
}

class CounterModifier13 implements AttributeModifier<CounterAttribute> {
  public sizeIndex: number = 0;
  public sizeIndex1: number = 0;
  public sizeList: (Resource | number | null | undefined)[] = [
    120, $r('app.string.FeiFaZhi'), $r('app.color.pink'), $r('app.string.number_120'), $r('app.string.number_120'),
    undefined, $r('app.string.format'), $r('app.string.number_120'), null, $r('app.string.number_120')
  ]
  public sizeListStr: string[] = [
    '120',
    '$r("app.string.FeiFaZhi")-￥%123abc',
    '$r("app.color.pink")-#FFF38FEA',
    '$r("app.string.number_120")-L120-D320',
    '$r("app.string.number_120")-L120-D320',
    'undefined',
    '$r("app.string.format")-yyyy-mm-dd',
    '$r("app.string.number_120")-L120-D320',
    'null',
    '$r("app.string.number_120")-L120-D320'
  ]
  public sizeList1: (Resource | number | null | undefined)[] = [
    30, $r('app.string.FeiFaZhi'), $r('app.color.pink'), $r('app.string.number_30'), $r('app.string.number_30'),
    undefined, $r('app.string.number_30'), null, $r('app.string.number_30')
  ]
  public sizeList1Str: string[] = [
    '30',
    '$r("app.string.FeiFaZhi")-￥%123abc',
    '$r("app.color.pink")-#FFF38FEA',
    '$r("app.string.number_30")-L30-D100',
    '$r("app.string.number_30")-L30-D100',
    'undefined',
    '$r("app.string.number_30")-L30-D100',
    'null',
    '$r("app.string.number_30")-L30-D100'
  ]

  applyNormalAttribute(instance: CounterAttribute): void {
    instance
      .size({
        width: this.sizeList[this.sizeIndex],
        height: this.sizeList1[this.sizeIndex1],
      })
  }
}

@Entry
@Component
struct Page {
  @State message: string = 'Hello World';
  @State value: number = 0;
  @State isDark: boolean = false;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext
  @State modifier1: CounterModifier1 = new CounterModifier1()
  @State modifier2: CounterModifier2 = new CounterModifier2()
  @State modifier3: CounterModifier3 = new CounterModifier3()
  @State modifier4: CounterModifier4 = new CounterModifier4()
  @State modifier5: CounterModifier5 = new CounterModifier5()
  @State modifier6: CounterModifier6 = new CounterModifier6()
  @State modifier7: CounterModifier7 = new CounterModifier7()
  @State modifier8: CounterModifier8 = new CounterModifier8()
  @State modifier9: CounterModifier9 = new CounterModifier9()
  @State modifier10: CounterModifier10 = new CounterModifier10()
  @State modifier11: CounterModifier11 = new CounterModifier11()
  @State modifier12: CounterModifier12 = new CounterModifier12()
  @State modifier13: CounterModifier13 = new CounterModifier13()

  build() {
    Column() {
      Row() {
        Text('Counter-Size尺寸-Modifier').fontSize(12).fontColor(0x000020).fontWeight(FontWeight.Bold)
      }
      .height('6%')
      .width('95%')
      .borderRadius(15)
      .backgroundColor('#ffa9cbd6',)
      .justifyContent(FlexAlign.Center)

      Row() {
        Button('Change')
          .onClick(() => {
            if (this.isDark) {
              this.isDark = false;
              this.context.getApplicationContext().setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_LIGHT);
            } else {
              this.isDark = true;
              this.context.getApplicationContext().setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_DARK);
            }
          }).height(40).fontSize(12)

        Button('动态切width')
          .onClick(() => {
            this.modifier13.sizeIndex =
              (this.modifier13.sizeIndex + 1) % this.modifier13.sizeList.length;
          }).height(40).fontSize(12)

        Button('动态切height')
          .onClick(() => {
            this.modifier13.sizeIndex1 =
              (this.modifier13.sizeIndex1 + 1) % this.modifier13.sizeList1.length;
          }).height(40).fontSize(12)
      }

      Text('当前width: ' + this.modifier13.sizeListStr[this.modifier13.sizeIndex])
        .fontSize(12)
        .fontColor(0x696969)
        .margin({ top: 10, bottom: 10 })

      Text('当前height: ' + this.modifier13.sizeList1Str[this.modifier13.sizeIndex1])
        .fontSize(12)
        .fontColor(0x696969)
        .margin({ bottom: 10 })

      Counter() {
        Text(this.value.toString())
      }
      .attributeModifier(this.modifier13)
      .onInc(() => {
        this.value++;
      })
      .onDec(() => {
        this.value--;
      })

      Row() {
        Column() {
          Text('原生counter').fontSize(16).fontColor(0x696969).width('95%')
          Counter() {
            Text(this.value.toString())
          }

          Text('Size width：Resource-120').fontSize(16).fontColor(0x696969).width('95%')
          Counter() {
            Text(this.value.toString())
          }

          .attributeModifier(this.modifier1)
          .onInc(() => {
            this.value++;
          })
          .onDec(() => {
            this.value--;
          })

          Text('Size width：string-\'120\'').fontSize(16).fontColor(0x696969).width('95%')
          Counter() {
            Text(this.value.toString())
          }

          .attributeModifier(this.modifier2)
          .onInc(() => {
            this.value++;
          })
          .onDec(() => {
            this.value--;
          })

          Text('Size width：number-120').fontSize(16).fontColor(0x696969).width('95%')
          Counter() {
            Text(this.value.toString())
          }

          .attributeModifier(this.modifier3)
          .onInc(() => {
            this.value++;
          })
          .onDec(() => {
            this.value--;
          })

          Text('Size width：undefined').fontSize(16).fontColor(0x696969).width('95%')
          Counter() {
            Text(this.value.toString())
          }
          .attributeModifier(this.modifier4)
          .onInc(() => {
            this.value++;
          })
          .onDec(() => {
            this.value--;
          })

          Text('Size width：null').fontSize(16).fontColor(0x696969).width('95%')
          Counter() {
            Text(this.value.toString())
          }
          .attributeModifier(this.modifier5)
          .onInc(() => {
            this.value++;
          })
          .onDec(() => {
            this.value--;
          })
        }
      }

      Text('Size height：Resource-30').fontSize(16).fontColor(0x696969).width('95%')
      Counter() {
        Text(this.value.toString())
      }
      .attributeModifier(this.modifier6)
      .onInc(() => {
        this.value++;
      })
      .onDec(() => {
        this.value--;
      })

      Text('Size height：string：\'30\'').fontSize(16).fontColor(0x696969).width('95%')
      Counter() {
        Text(this.value.toString())
      }
      .attributeModifier(this.modifier7)
      .onInc(() => {
        this.value++;
      })
      .onDec(() => {
        this.value--;
      })

      Text('Size height：number：30').fontSize(16).fontColor(0x696969).width('95%')
      Counter() {
        Text(this.value.toString())
      }
      .attributeModifier(this.modifier8)
      .onInc(() => {
        this.value++;
      })
      .onDec(() => {
        this.value--;
      })

      Text('Size height：undefined').fontSize(16).fontColor(0x696969).width('95%')
      Counter() {
        Text(this.value.toString())
      }
      .attributeModifier(this.modifier9)
      .onInc(() => {
        this.value++;
      })
      .onDec(() => {
        this.value--;
      })

      Text('Size height：null').fontSize(16).fontColor(0x696969).width('95%')
      Counter() {
        Text(this.value.toString())
      }
      .attributeModifier(this.modifier10)
      .onInc(() => {
        this.value++;
      })
      .onDec(() => {
        this.value--;
      })

      Text('Size：undefined').fontSize(16).fontColor(0x696969).width('95%')
      Counter() {
        Text(this.value.toString())
      }
      .attributeModifier(this.modifier11)
      .onInc(() => {
        this.value++;
      })
      .onDec(() => {
        this.value--;
      })

      Text('Size：null').fontSize(16).fontColor(0x696969).width('55%')
      Counter() {
        Text(this.value.toString())
      }
      .attributeModifier(this.modifier12)
      .onInc(() => {
        this.value++;
      })
      .onDec(() => {
        this.value--;
      })
    }
  }
}