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
struct HapticTest {
  private selectedTime: Date = new Date('2022-07-22T08:00:00')
  @State isLunar: boolean = false
  private selectedDate: Date = new Date('2021-08-08')
  @State isShow: boolean = false
  @State isLoop: boolean = true
  @State isMilitaryTime: boolean = true
  @State selected: number[] = []
  private cascade: TextCascadePickerRangeContent[] = [
    {
      text: '辽宁省',
      children: [{ text: '沈阳市', children: [{ text: '沈河区' }, { text: '和平区' }, { text: '浑南区' }] },
        { text: '大连市', children: [{ text: '中山区' }, { text: '金州区' }, { text: '长海县' }] }]
    },
    {
      text: '吉林省',
      children: [{ text: '长春市', children: [{ text: '南关区' }, { text: '宽城区' }, { text: '朝阳区' }] },
        { text: '四平市', children: [{ text: '铁西区' }, { text: '铁东区' }, { text: '梨树县' }] }]
    },
    {
      text: '黑龙江省',
      children: [{ text: '哈尔滨市', children: [{ text: '道里区' }, { text: '道外区' }, { text: '南岗区' }] },
        { text: '牡丹江市', children: [{ text: '东安区' }, { text: '西安区' }, { text: '爱民区' }] }]
    }
  ]

  build() {
    Column() {
      Text('DatePicker')
        .fontSize(20)
        .backgroundColor(Color.Orange)
        .fontWeight(FontWeight.Bold)
        .alignRules({
          center: { anchor: '__container__', align: VerticalAlign.Center },
          middle: { anchor: '__container__', align: HorizontalAlign.Center }
        })

      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2100-1-1'),
        selected: this.selectedDate
      })
        .lunar(this.isLunar)
        .onDateChange((value: Date) => {
          this.selectedDate = value
          console.info('select current date is: ' + value.toString())
        })
        .margin(0)

      Text('TimePicker')
        .fontSize(20)
        .backgroundColor(Color.Orange)
        .fontWeight(FontWeight.Bold)
        .alignRules({
          center: { anchor: '__container__', align: VerticalAlign.Center },
          middle: { anchor: '__container__', align: HorizontalAlign.Center }
        })

      TimePicker({
        selected: this.selectedTime
      })
        .disappearTextStyle({ color: '#004aaf', font: { size: 24, weight: FontWeight.Lighter } })
        .textStyle({ color: Color.Black, font: { size: 26, weight: FontWeight.Normal } })
        .selectedTextStyle({ color: Color.Blue, font: { size: 30, weight: FontWeight.Bolder } })
        .loop(this.isLoop)
        .useMilitaryTime(this.isMilitaryTime)
        .onChange((value: TimePickerResult) => {
          if (value.hour >= 0) {
            this.selectedTime.setHours(value.hour, value.minute)
            console.info('select current date is: ' + JSON.stringify(value))
          }
        })
        .margin(0)

      Text('TextPicker')
        .fontSize(20)
        .backgroundColor(Color.Orange)
        .fontWeight(FontWeight.Bold)
        .alignRules({
          center: { anchor: '__container__', align: VerticalAlign.Center },
          middle: { anchor: '__container__', align: HorizontalAlign.Center }
        })

      TextPicker({ range: this.cascade, selected: this.selected[0] })
        .selectedIndex(undefined)
        .onChange((value: string | string[], index: number | number[]) => {
          this.selected[0] = index as number
          console.info('Picker item changed, value: ' + value + ', index: ' + index)
        })
        .height('50%')
        .canLoop(true)
        .disappearTextStyle({ color: Color.Red, font: { size: 15, weight: FontWeight.Lighter } })
        .selectedTextStyle({ color: $r('sys.color.alert'), font: { size: 25, family: 'HarmonyHeiTi' } })
        .textStyle({ color: Color.Black, font: { size: 20, weight: FontWeight.Normal, family: 'HarmonyHeiTi' } })
        .defaultTextStyle({ minFontSize: 35, maxFontSize: 28, overflow: TextOverflow.Ellipsis })

      Row({ space: 20 }) {
        Button('循环 : ' + this.isLoop)
          .margin({ top: 30, bottom: 30 })
          .onClick(() => {
            this.isLoop = !this.isLoop
          })

        Button('24小时 : ' + this.isMilitaryTime)
          .margin({ top: 30, bottom: 30 })
          .onClick(() => {
            this.isMilitaryTime = !this.isMilitaryTime
          })
      }
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#A0EEA0')
  }
}