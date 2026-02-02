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

class ToggleModifier implements AttributeModifier<ToggleAttribute> {
  flag: boolean = true;
  applyNormalAttribute(instance: ToggleAttribute): void {
    instance.accessibilityStateDescription(this.flag ? 'toggle selected modifier' : 'toggle not selected modifier')
  }
}

@Entry
@Component
struct Index4 {

  @State toggleModifier: ToggleModifier = new ToggleModifier
  @State toggleFlag1: boolean = true;
  @State toggleFlag2: boolean = true;
  @State toggleFlag3: boolean = true;
  @State toggleFlag4: boolean = true;
  @State toggleFlag5: boolean = true;
  @State toggleFlag6: boolean = true;
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
          Text('Toggle普通英文').margin(10)
          Toggle({ type: ToggleType.Switch, isOn: this.toggleFlag1 })
            .selectedColor('#007DFF')
            .switchPointColor('#FFFFFF')
            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            .accessibilityStateDescription(this.toggleFlag1 ? 'hello toggle point' : 'welcome toggle point')
            .onChange((isOn: boolean) => {
              this.toggleFlag1 = isOn;
            })
        }.margin(10)

        Row() {
          Text('Toggle特殊字符S%￥').margin(10)
          Toggle({ type: ToggleType.Switch, isOn: this.toggleFlag2 })
            .selectedColor('#007DFF')
            .switchPointColor('#FFFFFF')
            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            .accessibilityStateDescription(this.toggleFlag2 ? 'hello point' : 'S%￥')
            .onChange((isOn: boolean) => {
              this.toggleFlag2 = isOn;
            })
        }.margin(10)

        Row() {
          Text('Toggle超长字符').margin(10)
          Toggle({ type: ToggleType.Switch, isOn: this.toggleFlag3 })
            .selectedColor('#007DFF')
            .switchPointColor('#FFFFFF')
            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            .accessibilityStateDescription(this.toggleFlag3 ? 'hello point' : 'aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa111111111111111112222222222222222222333333333333333444444444444444444444444444555555555555555555555555555555555555666666666666666666666666666666666667777777777777777777777777777777777777777777777888888888888888888888888888888888888888888888889999999999999999999999999999999999999999999999900000000000000000000000000000000000000000000000000000')
            .onChange((isOn: boolean) => {
              this.toggleFlag3 = isOn;
            })
        }.margin(10)

        Row() {
          Text('Toggle空值').margin(10)
          Toggle({ type: ToggleType.Switch, isOn: this.toggleFlag4 })
            .selectedColor('#007DFF')
            .switchPointColor('#FFFFFF')
            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            .accessibilityStateDescription(this.toggleFlag4 ? 'hello toggle point' : '')
            .onChange((isOn: boolean) => {
              this.toggleFlag4 = isOn;
            })
        }.margin(10)

        Row() {
          Text('Toggle-Resource').margin(10)
          Toggle({ type: ToggleType.Switch, isOn: this.toggleFlag5 })
            .selectedColor('#007DFF')
            .switchPointColor('#FFFFFF')
            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            .accessibilityStateDescription(this.toggleFlag5 ? 'hello point' : $r('app.string.ziyuan'))
            .onChange((isOn: boolean) => {
              this.toggleFlag5 = isOn;
            })
        }.margin(10)

        Row() {
          Text('Toggle-undefined').margin(10)
          Toggle({ type: ToggleType.Switch, isOn: this.toggleFlag6 })
            .selectedColor('#007DFF')
            .switchPointColor('#FFFFFF')
            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            .accessibilityStateDescription(this.toggleFlag6 ? 'hello toggle point' : undefined)
            .onChange((isOn: boolean) => {
              this.toggleFlag6 = isOn;
            })
        }.margin(10)

        Row() {
          Text('Toggle Modifier').margin(10)
          Toggle({ type: ToggleType.Switch, isOn: this.toggleModifier.flag })
            .selectedColor('#007DFF')
            .switchPointColor('#FFFFFF')
            .accessibilityText("accessibilityText内容")
            .accessibilityDescription("Description内容")
            .attributeModifier(this.toggleModifier)
            .onChange((isOn: boolean) => {
              this.toggleModifier.flag = isOn;
            })
        }.margin(10)
      }
      .height('100%')
      .width('100%')
    }
  }
}
