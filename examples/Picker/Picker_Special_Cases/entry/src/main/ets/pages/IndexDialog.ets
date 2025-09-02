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

@Entry
@Component
struct PickerDialogAllExample {
  private selectTime: Date = new Date('2020-12-25T08:30:00')
  @State selectedDate: Date = new Date('2025年1月2日')
  private select: number | number[] = 2
  private startDate: Date = new Date('2025-01-05')
  private endDate: Date = new Date('2025-01-25')
  @State isLunar: boolean = false
  @State isLunarSwitch: boolean = false
  @State dataSource: TextCascadePickerRangeContent[] = [
    {
      text: 'C1驾驶证',
      children: [
        { text: 'c1A' },
        { text: 'c1B' },
        { text: 'c1C' }
      ]
    },
    {
      text: 'C2驾驶证',
      children: [
        { text: '科目一' },
        { text: '科目二' },
      ]
    },
    {
      text: 'Motor',
      children: [
        { text: '科目一' },
      ]
    }
  ]

  aboutToAppear(): void {
    console.log('aboutToAppear()')
  }

  build() {
    Column({ space: 2 }) {
      Text('基础 PickerDialog')
        .fontSize(30)
        .backgroundColor(Color.Pink)
        .fontWeight(FontWeight.Bold)
        .width('100%')
        .textAlign(TextAlign.Center)

      Button('CalendarPickerDialog', { type: ButtonType.Capsule, stateEffect: true })
        .onClick(() => {
          CalendarPickerDialog.show({
            start: this.startDate,
            end: this.endDate,
            selected: this.selectedDate,
          })

          console.log(this.getUIContext().getFrameNodeById('Dialog')?.getMeasuredSize().width + ' ' +
          this.getUIContext().getFrameNodeById('CalendarPickerDialog')?.getMeasuredSize().height)

        })
        .labelStyle({
          overflow: TextOverflow.Clip,
          maxLines: 2,
          minFontSize: 5,
          maxFontSize: 20,
          font: {
            size: 10,
            weight: FontWeight.Normal,
            family: 'cursive',
            style: FontStyle.Italic
          }
        })
        .key('CalendarPickerDialog')
        .fontSize(30)

      Button('DatePickerDialog show empty', { type: ButtonType.Capsule, stateEffect: true })
        .onClick(() => {
          DatePickerDialog.show()
        })
        .labelStyle({
          overflow: TextOverflow.Clip,
          maxLines: 2,
          minFontSize: 5,
          maxFontSize: 20,
          font: {
            size: 10,
            weight: FontWeight.Normal,
            family: 'cursive',
            style: FontStyle.Italic
          }
        })
        .fontSize(30)

      Button('DatePickerDialog', { type: ButtonType.Capsule, stateEffect: true })
        .onClick(() => {
          DatePickerDialog.show({
            start: new Date('2000-1-1'),
            end: new Date('2100-12-31'),
            alignment: DialogAlignment.Center,
            showTime: true,
            useMilitaryTime: false,
            lunar: this.isLunar,
            lunarSwitch: this.isLunarSwitch,
            lunarSwitchStyle: { selectedColor: Color.Blue, unselectedColor: Color.Green, strokeColor: Color.Red },
            disappearTextStyle: { color: Color.Pink, font: { size: '22fp', weight: FontWeight.Bold } },
            textStyle: { color: '#ff00ff00', font: { size: '18fp', weight: FontWeight.Bold } },
            selectedTextStyle: { color: '#ff182431', font: { size: '14fp', weight: FontWeight.Bolder } },
            onDateAccept: (value: Date) => {
              this.selectedDate = value
            },
            onAccept: () => {
            }
          })
        })
        .labelStyle({
          overflow: TextOverflow.Clip,
          maxLines: 2,
          minFontSize: 5,
          maxFontSize: 20,
          font: {
            size: 10,
            weight: FontWeight.Normal,
            family: 'cursive',
            style: FontStyle.Italic
          }
        })
        .fontSize(30)

      Button('TextPickerDialog', { type: ButtonType.Capsule, stateEffect: true })
        .onClick(() => {
          TextPickerDialog.show({
            range: this.dataSource,
            selected: this.select,
            disappearTextStyle: { color: Color.Red, font: { size: 15, weight: FontWeight.Bold } },
            textStyle: { color: Color.Black, font: { size: 20, weight: FontWeight.Bold } },
            selectedTextStyle: { color: Color.Blue, font: { size: 30, weight: FontWeight.Bolder } },
            canLoop: false,
            onAccept: (value: TextPickerResult) => {
              this.select = value.index
              console.log('onAccept(): ' + this.select)
            }
          })
        })
        .labelStyle({
          overflow: TextOverflow.Clip,
          maxLines: 2,
          minFontSize: 5,
          maxFontSize: 20,
          font: {
            size: 10,
            weight: FontWeight.Normal,
            family: 'cursive',
            style: FontStyle.Italic
          }
        })
        .fontSize(30)

      Button('TimePickerDialog show empty', { type: ButtonType.Capsule, stateEffect: true })
        .onClick(() => {
          TimePickerDialog.show();
        })
        .labelStyle({
          overflow: TextOverflow.Clip,
          maxLines: 2,
          minFontSize: 5,
          maxFontSize: 20,
          font: {
            size: 10,
            weight: FontWeight.Normal,
            family: 'cursive',
            style: FontStyle.Italic
          }
        })
        .fontSize(30)

      Button('TimePickerDialog', { type: ButtonType.Capsule, stateEffect: true })
        .onClick(() => {
          TimePickerDialog.show({
            selected: this.selectTime,
            useMilitaryTime: true,
            disappearTextStyle: { color: Color.Red, font: { size: 15, weight: FontWeight.Lighter } },
            textStyle: { color: Color.Black, font: { size: 20, weight: FontWeight.Bold } },
            selectedTextStyle: { color: Color.Blue, font: { size: 30, weight: FontWeight.Bolder } },
            onAccept: (value: TimePickerResult) => {
              if (value.hour != undefined && value.minute != undefined) {
                this.selectTime.setHours(value.hour, value.minute)
                console.info('TimePickerDialog:onAccept() ' + JSON.stringify(value))
              }
            }
          })
        })
        .labelStyle({
          overflow: TextOverflow.Clip,
          maxLines: 2,
          minFontSize: 5,
          maxFontSize: 20,
          font: {
            size: 10,
            weight: FontWeight.Normal,
            family: 'cursive',
            style: FontStyle.Italic
          }
        })
        .fontSize(30)

      Row({ space: 20 }) {
        Button(`Lunar Switch : ${this.isLunarSwitch}`)
          .onClick(() => {
            this.isLunar = !this.isLunar
            this.isLunarSwitch = !this.isLunarSwitch
          })
      }
    }
    .height('100%')
    .width('100%')
  }
}
