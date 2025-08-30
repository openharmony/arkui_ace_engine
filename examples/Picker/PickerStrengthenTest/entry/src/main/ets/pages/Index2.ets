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

class CustomModifier implements AttributeModifier<TimePickerAttribute> {
  public isMilitaryTime: boolean | null | undefined = false

  applyNormalAttribute(instance: TimePickerAttribute): void {
    instance.useMilitaryTime(this.isMilitaryTime)
    instance.loop(false)
    instance.disappearTextStyle({ color: Color.Red, font: { size: 15, weight: FontWeight.Bolder } })
    instance.textStyle({ color: Color.Blue, font: { size: 20, weight: FontWeight.Bolder } })
    instance.selectedTextStyle({
      color: Color.Pink,
      font: {
        size: 30,
        weight: FontWeight.Bolder,
        family: 'serif',
        style: FontStyle.Italic
      }
    })
    instance.margin(30)
  }
}

// xxx.ets
@Entry
@Component
struct Index {
  @State myModifier: CustomModifier = new CustomModifier()
  @State isMilitaryTime: boolean | undefined | null = false
  private selectedTime: Date = new Date('2022-07-22T17:00:00')
  @State flag: number = 1

  build() {
    Column() {
      Button('切换12小时制上午下午随小时联动/不随小时联动 isMilitaryTime:' + this.isMilitaryTime + this.flag)
        .onClick(() => {
          if (this.flag == 1) {
            this.flag = 2;
            this.isMilitaryTime = true;
            this.myModifier.isMilitaryTime = true
            console.log('Modifier', 'isMilitaryTimeTrue')
          } else if (this.flag == 2) {
            this.flag = 3;
            this.isMilitaryTime = false;
            this.myModifier.isMilitaryTime = false
            console.log('Modifier', 'isMilitaryTimeFalse')
          } else if (this.flag == 3) {
            this.flag = 4;
            this.isMilitaryTime = null;
            this.myModifier.isMilitaryTime = null
            console.log('Modifier', 'isMilitaryTimeNull')
          } else if (this.flag == 4) {
            this.flag = 1;
            this.isMilitaryTime = undefined;
            this.myModifier.isMilitaryTime = undefined
            console.log('Modifier', 'isMilitaryTimeundefined')
          }
        })
      TimePicker({
        selected: this.selectedTime,
      })
        .useMilitaryTime(this.isMilitaryTime)
        .onChange((value: TimePickerResult) => {
          if (value.hour >= 0) {
            this.selectedTime.setHours(value.hour, value.minute)
            console.info('select current date is: ' + JSON.stringify(value))
          }
        })
        .disappearTextStyle({ color: Color.Red, font: { size: 15, weight: FontWeight.Lighter } })
        .textStyle({ color: Color.Black, font: { size: 20, weight: FontWeight.Normal } })
        .selectedTextStyle({ color: Color.Blue, font: { size: 30, weight: FontWeight.Bolder } })
        .margin(30)
        .overlay('常规')

      TimePicker({
        selected: this.selectedTime,
      })
        .attributeModifier(this.myModifier)
    }.width('100%')
  }
}
