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
struct TimePickerExample {
  scroller: Scroller = new Scroller()
  private selectedTime: Date = new Date('2025-07-22T08:01:01')
  @State isEnabled: boolean = true
  @State isMilitaryTime: boolean = true

  build() {
    Scroll(this.scroller) {
      Column() {
        Text('基础 TimePicker')
          .fontSize(30)
          .backgroundColor(Color.Pink)
          .fontWeight(FontWeight.Bold)
          .width('100%')
          .textAlign(TextAlign.Center)

        Row() {
          TimePicker({
            start: new Date('2000-07-22T07:01:01'),
            end: new Date('2030-07-22T20:10:01'),
            selected: this.selectedTime,
            format: TimePickerFormat.HOUR_MINUTE
          })
            .disappearTextStyle({ color: '#004aaf', font: { size: 24, weight: FontWeight.Lighter } })
            .textStyle({ color: Color.Black, font: { size: 26, weight: FontWeight.Normal } })
            .selectedTextStyle({ color: Color.Blue, font: { size: 45, weight: FontWeight.Bolder } })
            .onChange((value: TimePickerResult) => {
              if (value.hour >= 0) {
                this.selectedTime.setHours(value.hour, value.minute)
                console.log('onChange() select : ' + JSON.stringify(value))
              }
            })
            .width('50%')
            .loop(true)
            .dateTimeOptions({ hour: '2-digit', minute: '2-digit', second: '2-digit' })
            .enableHapticFeedback(true)
            .enabled(this.isEnabled)
            .useMilitaryTime(this.isMilitaryTime)
            .enableCascade(true)

          TimePicker({
            start: new Date('2000-07-22T07:01:01'),
            end: new Date('2030-07-22T20:10:01'),
            selected: this.selectedTime,
            format: TimePickerFormat.HOUR_MINUTE
          })
            .disappearTextStyle({ color: '#004aaf', font: { size: 24, weight: FontWeight.Lighter } })
            .textStyle({ color: Color.Black, font: { size: 26, weight: FontWeight.Normal } })
            .selectedTextStyle({ color: Color.Blue, font: { size: 45, weight: FontWeight.Bolder } })
            .onChange((value: TimePickerResult) => {
              if (value.hour >= 0) {
                this.selectedTime.setHours(value.hour, value.minute)
                console.info('select current date is: ' + JSON.stringify(value))
              }
            })
            .width('50%')
            .loop(true)
            .dateTimeOptions({ hour: '2-digit', minute: '2-digit', second: '2-digit' })
            .enableHapticFeedback(true)
            .enabled(this.isEnabled)
            .useMilitaryTime(this.isMilitaryTime)
            .enableCascade(false)
        }

        Row({ space: 10 }) {
          Button('Enabled: ' + this.isEnabled)
            .margin({ top: 30, bottom: 30 })
            .onClick(() => {
              this.isEnabled = !this.isEnabled
            })

          Button('Military: ' + this.isMilitaryTime)
            .margin({ top: 30, bottom: 30 })
            .onClick(() => {
              this.isMilitaryTime = !this.isMilitaryTime
            })
        }
      }
      .backgroundColor('#90EE90')
      .width('100%')
      .height('100%')
    }
    .height('100%')
    .scrollable(ScrollDirection.Vertical)
    .scrollBar(BarState.On)
    .scrollBarColor(Color.Gray)
    .scrollBarWidth(3)
    .friction(0.6)
    .edgeEffect(EdgeEffect.Fade)
  }
}
