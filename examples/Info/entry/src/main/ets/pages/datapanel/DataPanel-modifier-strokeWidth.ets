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

class DataPanelModifier1 implements AttributeModifier<DataPanelAttribute> {
  applyNormalAttribute(instance: DataPanelAttribute): void {
    instance
      .strokeWidth('40vp')
  }
}

class DataPanelModifier2 implements AttributeModifier<DataPanelAttribute> {
  applyNormalAttribute(instance: DataPanelAttribute): void {
    instance
      .strokeWidth(30)
  }
}

class DataPanelModifier3 implements AttributeModifier<DataPanelAttribute> {
  applyNormalAttribute(instance: DataPanelAttribute): void {
    instance
      .strokeWidth($r('app.string.number_30'))
  }
}

class DataPanelModifier5 implements AttributeModifier<DataPanelAttribute> {
  public badgeColorIndex: number = 0;
  public badgeColorList: (Resource | number | string | null | undefined)[] = [
    $r('app.string.number_30'), $r('app.string.format'), $r('app.string.FeiFaZhi'), $r('app.color.pink'), '60vp',
    $r('app.string.number_30'), 10, $r('app.string.number_30'), $r('app.string.format')
  ]

  applyNormalAttribute(instance: DataPanelAttribute): void {
    instance
      .strokeWidth(this.badgeColorList[this.badgeColorIndex])
  }
}

@Entry
@Component
struct DataPanelExample {
  @State modifier1: DataPanelModifier1 = new DataPanelModifier1()
  @State modifier2: DataPanelModifier2 = new DataPanelModifier2()
  @State modifier3: DataPanelModifier3 = new DataPanelModifier3()
  @State modifier5: DataPanelModifier5 = new DataPanelModifier5()
  @State isDark: boolean = false;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext
  @State color3: string = '#00FF00'
  @State color4: string = '#20FF0000'
  public values1: number[] = [20, 20, 20, 20]
  public color1: LinearGradient =
    new LinearGradient([{ color: '#65EEC9A3', offset: 0 }, { color: '#FFEF629F', offset: 1 }])
  public color2: LinearGradient =
    new LinearGradient([{ color: '#FF67F9D4', offset: 0 }, { color: '#FFFF9554', offset: 1 }])
  public colorShadow1: LinearGradient =
    new LinearGradient([{ color: '#65EEC9A3', offset: 0 }, { color: '#65EF629F', offset: 1 }])
  public colorShadow2: LinearGradient =
    new LinearGradient([{ color: '#65e26709', offset: 0 }, { color: '#65efbd08', offset: 1 }])
  public colorShadow3: LinearGradient =
    new LinearGradient([{ color: '#6572B513', offset: 0 }, { color: '#6508efa6', offset: 1 }])
  public colorShadow4: LinearGradient =
    new LinearGradient([{ color: '#65ed08f5', offset: 0 }, { color: '#65ef0849', offset: 1 }])
  @State colorArray: Array<LinearGradient | ResourceColor> = [this.color1, this.color2, this.color3, this.color4]
  @State shadowColorArray: Array<LinearGradient | ResourceColor> =
    [this.colorShadow1, this.colorShadow2, this.colorShadow3, this.colorShadow4]
  @State value: number = 0;
  @State offsetX: number = 15
  @State offsetY: number = 15
  @State radius: number = 5

  build() {
    Scroll() {
      Column() {
        Row() {

          Text('Current Index: ' + this.modifier5.badgeColorIndex + '/' + (this.modifier5.badgeColorList.length - 1))
            .fontSize(12)
            .fontColor(0x696969)
          Button('动态切:' + this.modifier5.badgeColorList[this.modifier5.badgeColorIndex])
            .onClick(() => {
              this.modifier5.badgeColorIndex =
                (this.modifier5.badgeColorIndex + 1) % this.modifier5.badgeColorList.length;
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

        Text('DataPanel组件')
          .fontColor('#182431')
          .fontSize(30)
          .fontWeight(500)
          .lineHeight(14)
          .margin(5)
        Text('strokeWidth-圆环粗细-M')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
        Text('strokeWidth（string）：30vp')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)

        DataPanel({ values: this.values1, max: 100, type: DataPanelType.Circle })
          .width(120)
          .height(120)
          .valueColors(this.colorArray)
          .closeEffect(true)
          .attributeModifier(this.modifier1)
          .trackShadow({
            radius: this.radius,
            colors: this.shadowColorArray,
            offsetX: this.offsetX,
            offsetY: this.offsetY
          })
          .margin({ bottom: 5 })

        Text('strokeWidth（number）：30')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)

        DataPanel({ values: this.values1, max: 100, type: DataPanelType.Circle })
          .width(120)
          .height(120)
          .valueColors(this.colorArray)
          .closeEffect(true)
          .attributeModifier(this.modifier2)
          .trackShadow({
            radius: this.radius,
            colors: this.shadowColorArray,
            offsetX: this.offsetX,
            offsetY: this.offsetY
          })
          .margin({ bottom: 5 })

        Text('strokeWidth（Resource）：$r(app.string.number_30)')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)

        DataPanel({ values: this.values1, max: 100, type: DataPanelType.Circle })
          .width(120)
          .height(120)
          .valueColors(this.colorArray)
          .closeEffect(true)
          .attributeModifier(this.modifier3)
          .trackShadow({
            radius: this.radius,
            colors: this.shadowColorArray,
            offsetX: this.offsetX,
            offsetY: this.offsetY
          })
          .margin({ bottom: 5 })

        Text('动态切')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)

        DataPanel({ values: this.values1, max: 100, type: DataPanelType.Circle })
          .width(120)
          .height(120)
          .valueColors(this.colorArray)
          .closeEffect(true)
          .attributeModifier(this.modifier5)
          .trackShadow({
            radius: this.radius,
            colors: this.shadowColorArray,
            offsetX: this.offsetX,
            offsetY: this.offsetY
          })
          .margin({ bottom: 5 })
      }.width('100%')
    }
  }
}