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

class MyDataPanelModifier1 implements AttributeModifier<DataPanelAttribute> {
  public color1: Color = Color.Red
  public color11: LinearGradient =
    new LinearGradient([{ color: Color.Red, offset: 0 }, { color: Color.Green, offset: 1 }])
  public colorArray1: Array<LinearGradient | ResourceColor> = [this.color1, this.color11]

  applyNormalAttribute(instance: DataPanelAttribute): void {
    instance
      .valueColors(this.colorArray1)
  }
}

class MyDataPanelModifier2 implements AttributeModifier<DataPanelAttribute> {
  public color2: number = 0xffff0000
  public color22: LinearGradient =
    new LinearGradient([{ color: 0xffff0000, offset: 0 }, { color: 0xffff3400, offset: 1 }])
  public colorArray2: Array<LinearGradient | ResourceColor> = [this.color2, this.color22]

  applyNormalAttribute(instance: DataPanelAttribute): void {
    instance
      .valueColors(this.colorArray2)
  }
}

class MyDataPanelModifier3 implements AttributeModifier<DataPanelAttribute> {
  public color3: string = '#FFFF7B14'
  public color33: LinearGradient =
    new LinearGradient([{ color: '#FF67F9D4', offset: 0 }, { color: '#FFFF9554', offset: 1 }])
  public colorArray3: Array<LinearGradient | ResourceColor> = [this.color3, this.color33]

  applyNormalAttribute(instance: DataPanelAttribute): void {
    instance
      .valueColors(this.colorArray3)
  }
}

class MyDataPanelModifier4 implements AttributeModifier<DataPanelAttribute> {
  public color3: Resource = $r('app.color.start_green')
  public color33: LinearGradient =
    new LinearGradient([{ color: $r('app.color.start_green'), offset: 0 },
      { color: $r('app.color.start_yellow'), offset: 1 }])
  public colorArray4: Array<LinearGradient | ResourceColor> = [this.color3, this.color33]

  applyNormalAttribute(instance: DataPanelAttribute): void {
    instance
      .valueColors(this.colorArray4) //设置底板颜色
  }
}

class MyDataPanelModifier5 implements AttributeModifier<DataPanelAttribute> {
  public color1: Color = Color.Red
  public color11: LinearGradient =
    new LinearGradient([{ color: Color.Red, offset: 0 }, { color: Color.Green, offset: 1 }])
  public colorArray1: Array<LinearGradient | ResourceColor> = [this.color1, this.color11]
  public color2: number = 0xffff0000
  public color22: LinearGradient =
    new LinearGradient([{ color: 0xffff0000, offset: 0 }, { color: 0xffff3400, offset: 1 }])
  public colorArray2: Array<LinearGradient | ResourceColor> = [this.color2, this.color22]
  public color3: string = '#FFFF7B14'
  public color33: LinearGradient =
    new LinearGradient([{ color: '#FF67F9D4', offset: 0 }, { color: '#FFFF9554', offset: 1 }])
  public colorArray3: Array<LinearGradient | ResourceColor> = [this.color3, this.color33]
  public color4: Resource = $r('app.color.start_green')
  public color44: LinearGradient =
    new LinearGradient([{ color: $r('app.color.start_green'), offset: 0 },
      { color: $r('app.color.start_yellow'), offset: 1 }])
  public colorArray4: Array<LinearGradient | ResourceColor> = [this.color4, this.color44]
  public arrayarr: Array<LinearGradient | ResourceColor> = []
  public arrnum: number = 0

  applyNormalAttribute(instance: DataPanelAttribute): void {
    instance
      .valueColors(this.arrayarr) //设置底板颜色
  }
}

@Entry
@Component
struct BadgeExample6 {
  @State modifier1: MyDataPanelModifier1 = new MyDataPanelModifier1()
  @State modifier2: MyDataPanelModifier2 = new MyDataPanelModifier2()
  @State modifier3: MyDataPanelModifier3 = new MyDataPanelModifier3()
  @State modifier4: MyDataPanelModifier4 = new MyDataPanelModifier4()
  @State modifier5: MyDataPanelModifier5 = new MyDataPanelModifier5()
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
    [this.colorShadow1, $r('app.string.FeiFaZhi'), $r('app.color.pink'), $r('app.string.string_value_10'),
      this.colorShadow2, this.colorShadow3, this.colorShadow4]
  @State value: number = 0;
  @State offsetX: number = 15
  @State offsetY: number = 15
  @State radius: number = 5

  build() {
    Scroll() {
      Column() {
        Row() {
          Text('Current Index: ' + this.modifier5.arrnum + '/' + (this.modifier5.arrayarr.length - 1))
            .fontSize(12)
            .fontColor(0x696969)
          Button('动态切:' + this.modifier5.arrnum)
            .onClick(() => {
              this.modifier5.arrnum++

              // 使用取模运算实现循环
              this.modifier5.arrnum = this.modifier5.arrnum % 7

              switch (this.modifier5.arrnum) {
                case 0:
                  this.modifier5.arrayarr = this.modifier5.colorArray4
                  break
                case 1:
                  this.modifier5.arrayarr = this.modifier5.colorArray3
                  break
                case 2:
                  this.modifier5.arrayarr = this.modifier5.colorArray4
                  break
                case 3:
                  this.modifier5.arrayarr = this.modifier5.colorArray2
                  break
                case 4:
                  this.modifier5.arrayarr = this.modifier5.colorArray4
                  break
                case 5:
                  this.modifier5.arrayarr = this.modifier5.colorArray1
                  break
                case 6:
                  this.modifier5.arrayarr = this.modifier5.colorArray4
                  break
              }
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
        Text('valueColors-各数据段颜色-M')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)
        Text('valueColors（color）：color.red')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)

        DataPanel({ values: this.values1, max: 100, type: DataPanelType.Circle })
          .width(120)
          .height(120)
          .closeEffect(true)
          .attributeModifier(this.modifier1)
          .trackShadow({
            radius: this.radius,
            colors: this.shadowColorArray,
            offsetX: this.offsetX,
            offsetY: this.offsetY
          })
          .margin({ bottom: 5 })


        Text('valueColors（number）：0xffff0000')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)

        DataPanel({ values: this.values1, max: 100, type: DataPanelType.Circle })
          .width(120)
          .height(120)
          .closeEffect(true)
          .attributeModifier(this.modifier2)
          .trackShadow({
            radius: this.radius,
            colors: this.shadowColorArray,
            offsetX: this.offsetX,
            offsetY: this.offsetY
          })
          .margin({ bottom: 5 })

        Text('valueColors（string）："#FFFF7B14"')
          .fontColor('#182431')
          .fontSize(18)
          .fontWeight(400)
          .lineHeight(14)

        DataPanel({ values: this.values1, max: 100, type: DataPanelType.Circle })
          .width(120)
          .height(120)
          .closeEffect(true)
          .attributeModifier(this.modifier3)
          .trackShadow({
            radius: this.radius,
            colors: this.shadowColorArray,
            offsetX: this.offsetX,
            offsetY: this.offsetY
          })
          .margin({ bottom: 5 })


        Row() {
          Text('valueColors（Resource）：$r("app.color.orange")')
            .fontColor('#182431')
            .fontSize(18)
            .fontWeight(400)
            .lineHeight(14)
          Text('+动态切')
            .fontColor('#182431')
            .fontSize(18)
            .fontWeight(400)
            .lineHeight(14)
        }

        Row() {
          DataPanel({ values: this.values1, max: 100, type: DataPanelType.Circle })
            .width(120)
            .height(120)
            .closeEffect(true)
            .attributeModifier(this.modifier4)
            .trackShadow({
              radius: this.radius,
              colors: this.shadowColorArray,
              offsetX: this.offsetX,
              offsetY: this.offsetY
            })
            .margin({ bottom: 5 })
          DataPanel({ values: this.values1, max: 100, type: DataPanelType.Circle })
            .width(120)
            .height(120)
            .closeEffect(true)
            .attributeModifier(this.modifier5)
            .trackShadow({
              radius: this.radius,
              colors: this.shadowColorArray,
              offsetX: this.offsetX,
              offsetY: this.offsetY
            })
            .margin({ bottom: 5 })

        }
      }.width('100%')
    }
  }
}