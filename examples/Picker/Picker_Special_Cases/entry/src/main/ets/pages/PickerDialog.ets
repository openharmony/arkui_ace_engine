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
struct PickerDialogExample {
  private selectTime: Date = new Date('1991-08-04T23:30:01')
  @State selectedDate: Date = new Date('2025-08-22T16:30:51')
  private select: number | number[] = [0, 0, 0]
  private startDate: Date = new Date('2025-01-05')
  private endDate: Date = new Date('2025-01-25')
  @State isLunar: boolean = false
  @State isLunarSwitch: boolean = true
  private fruits1: string[] = ['apple1', 'apple2', 'apple3', 'apple4']
  private fruits2: string[] = ['orange1', 'orange2', 'orange3', 'orange4']
  private fruits3: string[] = ['peach1', 'peach2', 'peach3', 'peach4']
  private multi: string[][] = [this.fruits1, this.fruits2, this.fruits3]
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
    },
    {
      text: 'A1驾驶证',
      children: [
        { text: '科目三' },
      ]
    },
    {
      text: 'Bus',
      children: [
        { text: '科目一' },
      ]
    }
  ]

  aboutToAppear(): void {
    let date: Date = new Date('1989-08-04T23:30:01')
    console.log('toString()...' + date.toString())
    console.log('toISOString()...' + date.toISOString());
    console.log('toLocaleString()...' + date.toLocaleString());
    console.log('getTimezoneOffset()...' + date.getTimezoneOffset());

    const formatter1 = new Intl.DateTimeFormat('zh-CN');
    console.log('formatter1: ' + formatter1.format(new Date('1989-08-04T23:30:01')));

    const formatter2 = new Intl.DateTimeFormat('zh-CN',
      {
        timeZone: 'Asia/Shanghai',
        dateStyle: 'full',
        timeStyle: 'long'
      }
    );
    console.log('formatter2: ' + formatter2.format(new Date('1989-08-04T23:30:01+08:00')));
  }

  build() {
    Column({ space: 20 }) {
      Text('基础 PickerDialog')
        .fontSize(30)
        .backgroundColor(Color.Pink)
        .fontWeight(FontWeight.Bold)
        .width('100%')
        .textAlign(TextAlign.Center)

      Button('CalendarPickerDialog', { type: ButtonType.Capsule, stateEffect: true })
        .onClick(() => {
          CalendarPickerDialog.show({
            markToday: true,
            start: this.startDate,
            end: this.endDate,
            selected: this.selectedDate,
            acceptButtonStyle: {
              type: ButtonType.Normal,
              style: ButtonStyleMode.NORMAL,
              role: ButtonRole.NORMAL,
              fontColor: $r('app.color.button_font_color'),
              fontSize: $r('app.string.font_size'),
              fontWeight: FontWeight.Normal,
              fontStyle: FontStyle.Normal,
              fontFamily: $r('app.string.font_family'),
              backgroundColor: $r('app.color.background_color'),
              borderRadius: $r('app.string.border_radius'),
            },
            cancelButtonStyle: {
              type: ButtonType.Normal,
              style: ButtonStyleMode.NORMAL,
              role: ButtonRole.NORMAL,
              fontColor: $r('app.color.button_font_color'),
              fontSize: $r('app.string.font_size'),
              fontWeight: FontWeight.Normal,
              fontStyle: FontStyle.Normal,
              fontFamily: $r('app.string.font_family'),
              backgroundColor: $r('app.color.background_color'),
              borderRadius: $r('app.string.border_radius'),
              primary: true
            },
            onChange: (value) => {
              console.info('calendar onChange(): ' + JSON.stringify(value));
              this.selectedDate = value
            },
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
        .key('CalendarPickerDialog')
        .fontSize(30)

      Button('DatePickerDialog', { type: ButtonType.Capsule, stateEffect: true })
        .onClick(() => {
          this.getUIContext().showDatePickerDialog({
            start: new Date('2025-08-22T15:28:51'),
            end: new Date('2025-08-23T15:25:51'),
            mode: DatePickerMode.DATE,
            selected: this.selectedDate,
            alignment: DialogAlignment.Default,
            showTime: true,
            useMilitaryTime: true,
            lunar: this.isLunar,
            lunarSwitch: this.isLunarSwitch,
            lunarSwitchStyle: { selectedColor: Color.Blue, unselectedColor: '#FFE6BA0B', strokeColor: Color.Red },
            disappearTextStyle: { color: '#E5000000', font: { size: '14fp', weight: FontWeight.Regular } },
            textStyle: { color: '#E5000000', font: { size: '16fp', weight: FontWeight.Regular } },
            selectedTextStyle: { color: '#FFE6BA0B', font: { size: '20fp', weight: FontWeight.Medium } },
            acceptButtonStyle: {
              type: ButtonType.Normal,
              style: ButtonStyleMode.NORMAL,
              role: ButtonRole.NORMAL,
              fontColor: '#FFE6BA0B',
              fontSize: '16fp',
              fontWeight: FontWeight.Normal,
              fontStyle: FontStyle.Normal,
              fontFamily: 'sans-serif',
              backgroundColor: '#00000000',
              borderRadius: 20
            },
            cancelButtonStyle: {
              type: ButtonType.Normal,
              style: ButtonStyleMode.NORMAL,
              role: ButtonRole.NORMAL,
              fontColor: '#FFE6BA0B',
              fontSize: '16fp',
              fontWeight: FontWeight.Normal,
              fontStyle: FontStyle.Italic,
              fontFamily: 'sans-serif',
              backgroundColor: '#00000000',
              borderRadius: 10
            },
            onDateAccept: (value: Date) => {
              console.log('DatePickerDialog onDateAccept() ' + value.toString());
              this.selectedDate = value
            },
            onAccept: (value: DatePickerResult) => {
              console.log('DatePickerDialog onAccept() ' + JSON.stringify(value));
            },
            onCancel: () => {
              console.log('onCancel()');
            },
            onDidDisappear: () => {
              console.log('onDidDisappear()');
            },
            onChange: (value: DatePickerResult) => {
              console.log('onChange() ' + value);
            },
            onDateChange: (value: Date) => {
              console.log('onDateChange() ' + value.toString());
            },
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
            range: this.multi,
            selected: this.select,
            alignment: 1,
            disappearTextStyle: { color: Color.Red, font: { size: 15, weight: FontWeight.Bold } },
            textStyle: { color: Color.Black, font: { size: 20, weight: FontWeight.Bold } },
            selectedTextStyle: { color: Color.Blue, font: { size: 30, weight: FontWeight.Bolder } },
            canLoop: false,
            onAccept: (value: TextPickerResult) => {
              this.select = value.index
              console.log('TextPickerDialog:onAccept(): ' + this.select + ' ')
            },
            onScrollStop: (value: TextPickerResult) => {
              console.info('TextPickerDialog:onScrollStop()' + JSON.stringify(value))
            },
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

      Button('TimePickerDialog', { type: ButtonType.Capsule, stateEffect: true })
        .onClick(() => {
          TimePickerDialog.show({
            selected: this.selectTime,
            format: TimePickerFormat.HOUR_MINUTE,
            useMilitaryTime: true,
            alignment: 10,
            disappearTextStyle: { color: Color.Red, font: { size: 15, weight: FontWeight.Lighter } },
            textStyle: { color: Color.Black, font: { size: 20, weight: FontWeight.Bold } },
            selectedTextStyle: { color: Color.Blue, font: { size: 30, weight: FontWeight.Bolder } },
            onAccept: (value: TimePickerResult) => {
              if (value.hour != undefined && value.minute != undefined) {
                this.selectTime.setHours(value.hour, value.minute)
                console.log('TimePickerDialog:onAccept()' + JSON.stringify(value))
              }
            },
            onChange: (value: TimePickerResult) => {
              console.log('TimePickerDialog:onChange()' + JSON.stringify(value))
            },
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
