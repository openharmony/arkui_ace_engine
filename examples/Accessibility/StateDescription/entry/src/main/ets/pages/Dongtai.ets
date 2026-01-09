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

@Entry
@Component
struct Index8 {

  @State flag: boolean = true;
  @State flag1: boolean = true;
  @State flag2: boolean = true;
  @State flag3: boolean = true;
  @State flag4: boolean = true;
  @State flag5: boolean = true;
  @State flag6: boolean = true;
  @State flag7: boolean = true;
  @State toggleFlag: boolean = true;
  @State radio1Flag: boolean = true;
  @State radio2Flag: boolean = true;
  @State checkbox1Flag: boolean = true;
  @State checkbox2Flag: boolean = true;
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

        Row() {


          Button('动态切:' + this.badgeColorListStr[this.badgeColorIndex])
            .onClick(() => {
              this.badgeColorIndex = (this.badgeColorIndex + 1) % this.badgeColorList.length;
            })
        }
        Row() {
          Text('button-动态').margin(10)
          Button(this.flag1 ? 'hello1' : 'welcome2')
            .fontWeight(FontWeight.Bold)
            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            // .accessibilityStateDescription(this.flag ? 'hello point' : 'welcome point')
            .accessibilityStateDescription(this.flag1 ? 'hello point' : this.badgeColorList[this.badgeColorIndex])
            // .accessibilityStateDescription(this.flag ? 'hello point' : undefined))
            .onClick((event: ClickEvent) => {
              this.flag1 = !this.flag1;
            })
            .margin(10)
        }.margin(10)

        Row() {
          Text('Checkbox接口形式').margin(10)
          Checkbox({ name: 'checkbox1', group: 'checkboxGroup' })
            .selectedColor('#007DFF')
            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            .accessibilityStateDescription(this.checkbox1Flag ? 'hello point' : this.badgeColorList[this.badgeColorIndex])
            .onChange((isOn: boolean) => {
              this.checkbox1Flag = isOn;
            })
        }.margin(10)

        Radio({ value: 'Radio1', group: 'radioGroup' }).checked(this.radio1Flag)
          .radioStyle({
            checkedBackgroundColor: Color.Pink
          })
          .height(50)
          .accessibilityText("accessibilityText内容")
          .accessibilityDescription("Description内容")
          .width(50)
          .accessibilityStateDescription(this.radio1Flag ? 'hello point' : this.badgeColorList[this.badgeColorIndex])
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
        Toggle({ type: ToggleType.Switch, isOn: this.toggleFlag })
          .selectedColor('#007DFF')
          .accessibilityText("accessibilityText内容")
          .accessibilityDescription("Description内容")
          .switchPointColor('#FFFFFF')
          .accessibilityStateDescription(this.toggleFlag ? 'hello point' : this.badgeColorList[this.badgeColorIndex])
          .onChange((isOn: boolean) => {
            this.toggleFlag = isOn;
          })

      }
      .height('100%')
      .width('100%')
    }
  }
}

