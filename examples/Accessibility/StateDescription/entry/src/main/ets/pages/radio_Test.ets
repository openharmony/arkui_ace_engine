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

class Radio1Modifier implements AttributeModifier<RadioAttribute> {
  flag: boolean = true;
  applyNormalAttribute(instance: RadioAttribute): void {
    instance.accessibilityStateDescription(this.flag ? 'radio1 selected modifier' : 'radio1 not selected modifier')
  }
}

class Radio2Modifier implements AttributeModifier<RadioAttribute> {
  flag: boolean = true;
  applyNormalAttribute(instance: RadioAttribute): void {
    instance.accessibilityStateDescription(this.flag ? 'radio2 selected modifier' : 'radio2 not selected modifier')
  }
}


@Entry
@Component
struct Index3 {
  @State radio1Modifier: Radio1Modifier = new Radio1Modifier()
  @State radio2Modifier: Radio2Modifier = new Radio2Modifier()
  @State radio1Flag: boolean = true;
  @State radio2Flag: boolean = true;
  @State radio3Flag: boolean = true;
  @State radio4Flag: boolean = true;
  @State radio5Flag: boolean = true;
  @State radio6Flag: boolean = true;
  @State badgeColorIndex: number = 0;
  @State badgeColorList: (string | Resource | undefined)[] = [
    'welcome point2','S%￥','aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa111111111111111112222222222222222222333333333333333444444444444444444444444444555555555555555555555555555555555555666666666666666666666666666666666667777777777777777777777777777777777777777777777888888888888888888888888888888888888888888888889999999999999999999999999999999999999999999999900000000000000000000000000000000000000000000000000000aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa111111111111111112222222222222222222333333333333333444444444444444444444444444555555555555555555555555555555555555666666666666666666666666666666666667777777777777777777777777777777777777777777777888888888888888888888888888888888888888888888889999999999999999999999999999999999999999999999900000000000000000000000000000000000000000000000000000aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa11111111111111111222222222222222222233333333333333344444444444444444444444444455555555555555555555555555555555555566666666666666一千66666666666666666667777777777777777777777777777777777777777777777888888888888888888888888888888888888888888888889999999999999999999999999999999999999999999999900000000000000000000000000000000000000000000000000000',
    '',$r('app.string.ziyuan'),undefined
  ]
  @State badgeColorListStr:Array<string> =[
    'welcome point2','S%￥','aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa111111111111111112222222222222222222333333333333333444444444444444444444444444555555555555555555555555555555555555666666666666666666666666666666666667777777777777777777777777777777777777777777777888888888888888888888888888888888888888888888889999999999999999999999999999999999999999999999900000000000000000000000000000000000000000000000000000aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa111111111111111112222222222222222222333333333333333444444444444444444444444444555555555555555555555555555555555555666666666666666666666666666666666667777777777777777777777777777777777777777777777888888888888888888888888888888888888888888888889999999999999999999999999999999999999999999999900000000000000000000000000000000000000000000000000000aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa11111111111111111222222222222222222233333333333333344444444444444444444444444455555555555555555555555555555555555566666666666666一千66666666666666666667777777777777777777777777777777777777777777777888888888888888888888888888888888888888888888889999999999999999999999999999999999999999999999900000000000000000000000000000000000000000000000000000',
    "空值‘’","$r('app.string.ziyuan')",'undefined'
  ]
  build() {
    Scroll(){
      Column() {

        Column() {
          Text('Radio1 point普通英文')
          Radio({ value: 'Radio1', group: 'radioGroup' }).checked(this.radio1Flag)
            .radioStyle({
              checkedBackgroundColor: Color.Pink
            })
            .height(50)
            .width(50)
            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            .accessibilityStateDescription(this.radio1Flag ? 'hello radio1Flag point' : 'welcome radio1Flag point')
            .onChange((isChecked: boolean) => {
              this.radio1Flag = isChecked;
              console.info('Radio1 status is ' + isChecked);
            })

          Text('Radio2 特殊字符S%￥')
          Radio({ value: 'Radio2', group: 'radioGroup' }).checked(this.radio2Flag)
            .radioStyle({
              checkedBackgroundColor: Color.Pink
            })
            .height(50)
            .width(50)
            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            .accessibilityStateDescription(this.radio2Flag ? 'hello point' : 'S%￥')
            .onChange((isChecked: boolean) => {
              this.radio2Flag = isChecked;
              console.info('Radio2 status is ' + isChecked);
            })
          Text('Radio2 超长字符')
          Radio({ value: 'Radio3', group: 'radioGroup' }).checked(this.radio3Flag)
            .radioStyle({
              checkedBackgroundColor: Color.Pink
            })
            .height(50)
            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            .width(50)
            .accessibilityStateDescription(this.radio3Flag ? 'hello point' : 'aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa111111111111111112222222222222222222333333333333333444444444444444444444444444555555555555555555555555555555555555666666666666666666666666666666666667777777777777777777777777777777777777777777777888888888888888888888888888888888888888888888889999999999999999999999999999999999999999999999900000000000000000000000000000000000000000000000000000')
            .onChange((isChecked: boolean) => {
              this.radio3Flag = isChecked;
              console.info('Radio2 status is ' + isChecked);
            })
          Text('Radio2 空值')
          Radio({ value: 'Radio4', group: 'radioGroup' }).checked(this.radio4Flag)
            .radioStyle({
              checkedBackgroundColor: Color.Pink
            })
            .height(50)
            .width(50)
            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            .accessibilityStateDescription(this.radio4Flag ? 'hello radio2Flag point' : '')
            .onChange((isChecked: boolean) => {
              this.radio4Flag = isChecked;
              console.info('Radio2 status is ' + isChecked);
            })
          Text('Radio2 Resource')
          Radio({ value: 'Radio2', group: 'radioGroup' }).checked(this.radio5Flag)
            .radioStyle({
              checkedBackgroundColor: Color.Pink
            })
            .height(50)
            .width(50)
            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            .accessibilityStateDescription(this.radio5Flag ? 'hello radio2Flag point' : $r('app.string.ziyuan'))
            .onChange((isChecked: boolean) => {
              this.radio5Flag = isChecked;
              console.info('Radio2 status is ' + isChecked);
            })
          Text('Radio2 undefined')
          Radio({ value: 'Radio2', group: 'radioGroup' }).checked(this.radio6Flag)
            .radioStyle({
              checkedBackgroundColor: Color.Pink
            })
            .height(50)
            .width(50)
            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            .accessibilityStateDescription(this.radio6Flag ? 'hello radio2Flag point' : undefined)
            .onChange((isChecked: boolean) => {
              this.radio6Flag = isChecked;
              console.info('Radio2 status is ' + isChecked);
            })
        }

        Column() {
          Text('Radio1 modifier')
          Radio({ value: 'Radio1', group: 'radioGroup' }).checked(this.radio1Modifier.flag)
            .radioStyle({
              checkedBackgroundColor: Color.Pink
            })
            .height(50)
            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            .width(50)
            .attributeModifier(this.radio1Modifier)
            .onChange((isChecked: boolean) => {
              this.radio1Modifier.flag = isChecked;
              console.info('Radio1 status is ' + isChecked);
            })
        }

        Column() {
          Text('Radio2 modifier')
          Radio({ value: 'Radio2', group: 'radioGroup' }).checked(this.radio2Modifier.flag)
            .radioStyle({
              checkedBackgroundColor: Color.Pink
            })
            .height(50)
            .width(50)
            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            .attributeModifier(this.radio2Modifier)
            .onChange((isChecked: boolean) => {
              this.radio2Modifier.flag = isChecked;
              console.info('Radio2 status is ' + isChecked);
            })
        }

      }
      .height('100%')
      .width('100%')
    }
  }
}
