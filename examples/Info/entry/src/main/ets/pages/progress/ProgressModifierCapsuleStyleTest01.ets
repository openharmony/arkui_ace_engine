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
import { ProgressModifier } from '@ohos.arkui.modifier'

@Entry
@Component
struct ProgressModifierCapsuleStyleTest01 {
  @State isDark: boolean = false;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext
  @State modifier1: ProgressModifier = new ProgressModifier().style({ borderColor: Color.Blue })
  @State modifier2: ProgressModifier = new ProgressModifier().style({ borderColor: 0xffa500 })
  @State modifier3: ProgressModifier = new ProgressModifier().style({ borderColor: '#564af7' })
  @State modifier4: ProgressModifier = new ProgressModifier().style({ borderColor: 'rgb(255,165,0)' })
  @State modifier5: ProgressModifier = new ProgressModifier().style({ borderColor: 'rgba(255,165,0,0.8)' })
  @State modifier6: ProgressModifier = new ProgressModifier().style({ borderColor: $r('app.color.ColorBlue') })
  @State modifier7: ProgressModifier = new ProgressModifier().style({ borderColor: '#ff564af7' })
  @State modifier8: ProgressModifier = new ProgressModifier().style({ borderColor: undefined })
  @State modifier9: ProgressModifier = new ProgressModifier().style({ borderColor: null })

  build() {
    Column({ space: 15 }) {
      Row() {
        Text('CapsuleStyleOptions.borderColor属性测试')
          .fontSize(16)
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

      Text('borderColor不设置').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Text('borderColor ResourceColor:Color').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Row({ space: 40 }) {
        Progress({ value: 30, type: ProgressType.Capsule }).width(150).height(40)
          .color('#deb6fb')
        Progress({ value: 30, total: 150, type: ProgressType.Capsule }).width(150).height(40)
          .color(Color.Pink)
          .attributeModifier(this.modifier1)
      }

      Text('borderColor ResourceColor:Number').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Text('borderColor ResourceColor:#ffffff').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Row({ space: 40 }) {
        Progress({ value: 30, type: ProgressType.Capsule }).width(150).height(40)
          .color('#deb6fb')
          .attributeModifier(this.modifier2)
        Progress({ value: 30, total: 150, type: ProgressType.Capsule }).width(150).height(40)
          .color(Color.Pink)
          .attributeModifier(this.modifier3)
      }

      Text('borderColor ResourceColor:rgb').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Text('borderColor ResourceColor:rgba').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Row({ space: 40 }) {
        Progress({ value: 30, type: ProgressType.Capsule }).width(150).height(40)
          .color('#deb6fb')
          .attributeModifier(this.modifier4)
        Progress({ value: 30, total: 150, type: ProgressType.Capsule }).width(150).height(40)
          .color(Color.Pink)
          .attributeModifier(this.modifier5)
      }

      Text('borderColor ResourceColor:$r').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Text('borderColor ResourceColor:#ffffffff').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Row({ space: 40 }) {
        Progress({ value: 30, type: ProgressType.Capsule }).width(150).height(40)
          .color('#deb6fb')
          .attributeModifier(this.modifier6)
        Progress({ value: 30, total: 150, type: ProgressType.Capsule }).width(150).height(40)
          .color(Color.Pink)
          .attributeModifier(this.modifier7)
      }

      Text('borderColor undefined').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Text('borderColor null').fontSize(9).fontColor(0xCCCCCC).width('90%')
      Row({ space: 40 }) {
        Progress({ value: 30, type: ProgressType.Capsule }).width(150).height(40)
          .color('#deb6fb')
          .attributeModifier(this.modifier8)
        Progress({ value: 30, total: 150, type: ProgressType.Capsule }).width(150).height(40)
          .color(Color.Pink)
          .attributeModifier(this.modifier9)
      }
    }.width('100%').margin({ top: 30 })
  }
}