/*
* Copyright (c) 2026 Huawei Device Co., Ltd.
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

'use static'

import { Entry, Component, Column, Row, SliderStyle, Slider, Scroll, ClickEvent, ButtonAttribute, AttributeModifier,
  Margin, Text, Button, $r, FontWeight, Resource, CheckboxAttribute, CheckboxOptions, Checkbox
} from '@ohos.arkui.component';
import { State, Observed } from '@ohos.arkui.stateManagement'

@Observed
class Checkbox1Modifier implements AttributeModifier<CheckboxAttribute> {
  flag: boolean = true;
  applyNormalAttribute(instance: CheckboxAttribute): void {
    instance.accessibilityStateDescription(this.flag ? 'Checkbox1 selected modifier' : 'Checkbox1 not selected modifier')
  }
}

@Observed
class Checkbox2Modifier implements AttributeModifier<CheckboxAttribute> {
  flag: boolean = true;
  applyNormalAttribute(instance: CheckboxAttribute): void {
    instance.accessibilityStateDescription(this.flag ? 'Checkbox2 selected modifier' : 'Checkbox2 not selected modifier')
  }
}

@Entry
@Component
struct Index2 {

  @State checkbox1Modifier: Checkbox1Modifier = new Checkbox1Modifier()
  @State checkbox2Modifier: Checkbox2Modifier = new Checkbox2Modifier()

  @State checkbox1Flag: boolean = false;
  @State checkbox2Flag: boolean = false;
  @State checkbox3Flag: boolean = false;
  @State checkbox4Flag: boolean = false;
  @State checkbox5Flag: boolean = false;
  @State checkbox6Flag: boolean = false;
  @State badgeColorIndex: Int = 0;
  @State badgeColorList: (string | Resource | undefined)[] = [
    'welcome point2',
    'S%￥',
    'aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa111111111111111112222222222222222222333333333333333444444444444444444444444444555555555555555555555555555555555555666666666666666666666666666666666667777777777777777777777777777777777777777777777888888888888888888888888888888888888888888888889999999999999999999999999999999999999999999999900000000000000000000000000000000000000000000000000000',
    '',
    $r('app.string.ziYuan'),
    undefined
  ]
  @State badgeColorListStr:Array<string> =[
    'welcome point2',
    'S%￥',
    'aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa111111111111111112222222222222222222333333333333333444444444444444444444444444555555555555555555555555555555555555666666666666666666666666666666666667777777777777777777777777777777777777777777777888888888888888888888888888888888888888888888889999999999999999999999999999999999999999999999900000000000000000000000000000000000000000000000000000',
    "空值‘’",
    "$r('app.string.ziYuan')",
    'undefined'
  ]
  build() {
    Scroll(){
      Column() {

        Row() {
          Text('Checkbox普通英文').margin(10)
          Checkbox({ name: 'checkbox1', group: 'checkboxGroup' })
            .selectedColor('#007DFF')
            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            .accessibilityStateDescription(this.checkbox1Flag ? 'hello checkbox point' : 'welcome checkbox point')
            .onChange((isOn: boolean) => {
              this.checkbox1Flag = isOn;
            })
        }.margin(10)

        Row() {
          Text('Checkbox特殊字符S%￥').margin(10)
          Checkbox({ name: 'checkbox2', group: 'checkboxGroup' } as CheckboxOptions)
            .selectedColor('#007DFF')
            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            .accessibilityStateDescription(this.checkbox2Flag ? 'hello point' : 'S%￥')
            .onChange((isOn: boolean) => {
              this.checkbox2Flag = isOn;
            })
        }.margin(10)

        Row() {
          Text('Checkbox超长字符').margin(10)
          Checkbox({ name: 'checkbox3', group: 'checkboxGroup' } as CheckboxOptions)
            .selectedColor('#007DFF')
            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            .accessibilityStateDescription(this.checkbox3Flag ? 'hello point' : 'aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa111111111111111112222222222222222222333333333333333444444444444444444444444444555555555555555555555555555555555555666666666666666666666666666666666667777777777777777777777777777777777777777777777888888888888888888888888888888888888888888888889999999999999999999999999999999999999999999999900000000000000000000000000000000000000000000000000000')
            .onChange((isOn: boolean) => {
              this.checkbox3Flag = isOn;
            })
        }.margin(10)

        Row() {
          Text('Checkbox空值').margin(10)
          Checkbox({ name: 'checkbox4', group: 'checkboxGroup' } as CheckboxOptions)
            .selectedColor('#007DFF')
            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            .accessibilityStateDescription(this.checkbox4Flag ? 'hello checkbox point' : 'welcome checkbox point')
            .onChange((isOn: boolean) => {
              this.checkbox4Flag = isOn;
            })
        }.margin(10)

        Row() {
          Text('Checkbox-Resource').margin(10)
          Checkbox({ name: 'checkbox5', group: 'checkboxGroup' } as CheckboxOptions)
            .selectedColor('#007DFF')
            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            .accessibilityStateDescription(this.checkbox5Flag ? 'hello checkbox point' : $r('app.string.ziYuan'))
            .onChange((isOn: boolean) => {
              this.checkbox5Flag = isOn;
            })
        }.margin(10)

        Row() {
          Text('Checkbox-undefined').margin(10)
          Checkbox({ name: 'checkbox6', group: 'checkboxGroup' } as CheckboxOptions)
            .selectedColor('#007DFF')
            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            .accessibilityStateDescription(this.checkbox6Flag ? 'hello checkbox point' : undefined)
            .onChange((isOn: boolean) => {
              this.checkbox6Flag = isOn;
            })
        }.margin(10)

        Row() {
          Text('Checkbox Modifier').margin(10)
          Checkbox({ name: 'checkbox7', group: 'checkboxGroup' } as CheckboxOptions)
            .selectedColor('#007DFF')
            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            .attributeModifier(this.checkbox1Modifier)
            .onChange((isOn: boolean) => {
              this.checkbox1Modifier.flag = isOn;
            })
        }.margin(10)
      }
      .height('100%')
      .width('100%')
    }
  }
}
