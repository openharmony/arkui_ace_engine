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
  Margin, Text, Button, $r, FontWeight, Resource
} from '@ohos.arkui.component';
import { State, Observed } from '@ohos.arkui.stateManagement'

@Observed
class ButtonModifier implements AttributeModifier<ButtonAttribute> {
  flag7: boolean = true;
  applyNormalAttribute(instance: ButtonAttribute): void {
    instance.accessibilityStateDescription(this.flag7 ? "hello modifier" : "welcome modifier");
  }
}

@Entry
@Component
struct Index1 {
  @State modifier: ButtonModifier = new ButtonModifier();
  @State flag: boolean = true;
  @State flag1: boolean = true;
  @State flag2: boolean = true;
  @State flag3: boolean = true;
  @State flag4: boolean = true;
  @State flag5: boolean = true;
  @State flag6: boolean = true;
  @State flag7: boolean = true;
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
          Text('button-普通英文').margin(10)
          Button(this.flag ? 'hello1' : 'welcome2')
            .fontWeight(FontWeight.Bold)
            .accessibilityStateDescription(this.flag ? 'hello point1' : 'welcome point2')
            // .accessibilityStateDescription(this.flag ? 'hello point' : $r('app.float.page_text_font_size'))
            // .accessibilityStateDescription(this.flag ? 'hello point' : undefined))

            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            .onClick((event: ClickEvent) => {
              this.flag = !this.flag;
            })
            .margin(10)
        }.margin(10)
        Row() {
          Text('button-特殊字符S%￥').margin(10)
          Button(this.flag1 ? 'hello1' : 'welcome2')
            .fontWeight(FontWeight.Bold)
            .accessibilityStateDescription(this.flag1 ? 'hello point' : 'S%￥')
            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            // .accessibilityStateDescription(this.flag ? 'hello point' : $r('app.float.page_text_font_size'))
            // .accessibilityStateDescription(this.flag ? 'hello point' : undefined))
            .onClick((event: ClickEvent) => {
              this.flag1 = !this.flag1;
            })
            .margin(10)
        }.margin(10)
        Row() {
          Text('button-超长字符').margin(10)
          Button(this.flag2 ? 'hello1' : 'welcome2')
            .fontWeight(FontWeight.Bold)
            .accessibilityStateDescription(this.flag2 ? 'hello point' : 'aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa111111111111111112222222222222222222333333333333333444444444444444444444444444555555555555555555555555555555555555666666666666666666666666666666666667777777777777777777777777777777777777777777777888888888888888888888888888888888888888888888889999999999999999999999999999999999999999999999900000000000000000000000000000000000000000000000000000')
            // .accessibilityStateDescription(this.flag ? 'hello point' : $r('app.float.page_text_font_size'))
            // .accessibilityStateDescription(this.flag ? 'hello point' : undefined))
            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            .onClick((event: ClickEvent) => {
              this.flag2 = !this.flag2;
            })
            .margin(10)
        }.margin(10)

        Row() {
          Text('button-空值').margin(10)
          Button(this.flag3 ? 'hello1' : 'welcome2')
            .fontWeight(FontWeight.Bold)
            .accessibilityStateDescription(this.flag3 ? 'hello point' : '')
            // .accessibilityStateDescription(this.flag ? 'hello point' : $r('app.float.page_text_font_size'))
            // .accessibilityStateDescription(this.flag ? 'hello point' : undefined))
            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            .onClick((event: ClickEvent) => {
              this.flag3 = !this.flag3;
            })
            .margin(10)
        }.margin(10)

        Row() {
          Text('button-Resource').margin(10)
          Button(this.flag4 ? 'hello1' : 'welcome2')
            .fontWeight(FontWeight.Bold)
            // .accessibilityStateDescription(this.flag ? 'hello point' : 'welcome point')
            .accessibilityStateDescription(this.flag4 ? 'hello point' : $r('app.string.ziYuan'))
            // .accessibilityStateDescription(this.flag ? 'hello point' : undefined))
            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            .onClick((event: ClickEvent) => {
              this.flag4 = !this.flag4;
            })
            .margin(10)
        }.margin(10)

        Row() {
          Text('button-undefined').margin(10)
          Button(this.flag5 ? 'hello1' : 'welcome2')
            .fontWeight(FontWeight.Bold)
            // .accessibilityStateDescription(this.flag ? 'hello point' : 'welcome point')
            .accessibilityStateDescription(this.flag5 ? 'hello point' : undefined)
            // .accessibilityStateDescription(this.flag ? 'hello point' : undefined))
            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            .onClick((event: ClickEvent) => {
              this.flag5 = !this.flag5;
            })
            .margin(10)
        }.margin(10)

        Row() {
          Text('button-modifier形式').margin(10)
          Button(this.modifier.flag7 ? 'hello modifier' : 'welcome modifier')
            .fontWeight(FontWeight.Bold)
            .attributeModifier(this.modifier)
            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            .onClick((event: ClickEvent) => {
              this.modifier.flag7 = !this.modifier.flag7;
            })
            .margin(10)
        }.margin(10)

      }
      .height('100%')
      .width('100%')
    }
  }
}

