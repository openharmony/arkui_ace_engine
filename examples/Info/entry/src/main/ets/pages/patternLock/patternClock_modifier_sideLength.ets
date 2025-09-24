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

class PatternLockModifier1 implements AttributeModifier<PatternLockAttribute> {
  applyNormalAttribute(instance: PatternLockAttribute): void {
    instance
      .sideLength('100px')
  }
}

class PatternLockModifier2 implements AttributeModifier<PatternLockAttribute> {
  applyNormalAttribute(instance: PatternLockAttribute): void {
    instance
      .sideLength(70)
  }
}

class PatternLockModifier3 implements AttributeModifier<PatternLockAttribute> {
  applyNormalAttribute(instance: PatternLockAttribute): void {
    instance
      .sideLength($r('app.string.number_120'))
  }
}

class PatternLockModifier5 implements AttributeModifier<PatternLockAttribute> {
  public colorIndex: number = 0;
  public colorList: (Resource | number | string | null | undefined)[] = [
    $r('app.string.number_120'), $r('app.string.FeiFaZhi'), $r('app.color.pink'), $r('app.string.string_value_10'),
    $r('app.string.format'), '100px', $r('app.string.number_120'), 70, $r('app.string.number_120'), null,
    $r('app.string.number_120'), undefined, $r('app.string.number_120'),
  ]

  applyNormalAttribute(instance: PatternLockAttribute): void {
    instance
      .sideLength(this.colorList[this.colorIndex])
  }
}

@Entry
@Component
struct PatternLockExample6 {
  @State modifier1: PatternLockModifier1 = new PatternLockModifier1()
  @State modifier2: PatternLockModifier2 = new PatternLockModifier2()
  @State modifier3: PatternLockModifier3 = new PatternLockModifier3()
  @State modifier5: PatternLockModifier5 = new PatternLockModifier5()
  private patternLockController: PatternLockController = new PatternLockController()
  @State isDark: boolean = false;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext

  build() {
    Scroll() {
      Column() {
        Row() {
          Text('Current Index: ' + this.modifier5.colorIndex + '/' + (this.modifier5.colorList.length - 1))
            .fontSize(12)
            .fontColor(0x696969)
          Button('动态切:' + this.modifier5.colorList[this.modifier5.colorIndex])
            .onClick(() => {
              this.modifier5.colorIndex =
                (this.modifier5.colorIndex + 1) % this.modifier5.colorList.length;
            })
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
        }

        Text('PatternLock组件')
          .fontColor('#182431')
          .fontSize(30)
          .fontWeight(500)
          .lineHeight(14)
          .margin(20)
        Text('sideLength-组件的宽度和高度')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
        Text('sideLength（string）：100px')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(5)
        PatternLock(this.patternLockController)
          .pathStrokeWidth(5)
          .attributeModifier(this.modifier1)
          .autoReset(true)
          .onDotConnect((index: number) => {
            console.log('onDotConnect index: ' + index)
          })
          .margin({ bottom: 15 })

        Text('sideLength（number）：70')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(5)
        PatternLock(this.patternLockController)
          .pathStrokeWidth(5)
          .attributeModifier(this.modifier2)
          .autoReset(true)
          .onDotConnect((index: number) => {
            console.log('onDotConnect index: ' + index)
          })
          .margin({ bottom: 15 })

        Text('sideLength（Resource）：$r("app.string.number_120")')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(5)
        PatternLock(this.patternLockController)
          .pathStrokeWidth(5)
          .attributeModifier(this.modifier3)
          .autoReset(true)
          .onDotConnect((index: number) => {
            console.log('onDotConnect index: ' + index)
          })
          .margin({ bottom: 15 })
        
        Text('动态切')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
          .margin(5)
        PatternLock(this.patternLockController)
          .pathStrokeWidth(5)
          .attributeModifier(this.modifier5)
          .autoReset(true)
          .onDotConnect((index: number) => {
            console.log('onDotConnect index: ' + index)
          })
          .margin({ bottom: 15 })

      }.width('100%')
    }
  }
}