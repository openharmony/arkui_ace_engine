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

import router from '@ohos.router';

@Entry
@Component
struct PickerExample {
  @State message: string = 'Picker TestCases';
  private fontSize: number = 20;
  private buttonHeight: number = 30;

  aboutToAppear(): void {
    console.log(`${new Date('2025/01/01')}`);
  }

  build() {
    Column({ space: 2 }) {
      Text(this.message)
        .fontSize(30)
        .backgroundColor(Color.Pink)
        .fontWeight(FontWeight.Bold)
        .width('100%')
        .textAlign(TextAlign.Center)

      Button('音振测试').onClick(() => {
        router.pushUrl({
          url: 'pages/HapticTest'
        })
      })
        .fontSize(this.fontSize)
        .height(this.buttonHeight)

      Button('CalendarPicker').onClick(() => {
        router.pushUrl({
          url: 'pages/CalendarPicker'
        })
      })
        .fontSize(this.fontSize)
        .height(this.buttonHeight)

      Button('PickerDialog').onClick(() => {
        router.pushUrl({
          url: 'pages/PickerDialog'
        })
      })
        .fontSize(this.fontSize)
        .height(this.buttonHeight)

      Button('TextPicker').onClick(() => {
        router.pushUrl({
          url: 'pages/TextPicker'
        })
      })
        .fontSize(this.fontSize)
        .height(this.buttonHeight)

      Button('TextPicker-HeavyData').onClick(() => {
        router.pushUrl({
          url: 'pages/HeavyDataTextPicker'
        })
      })
        .fontSize(this.fontSize)
        .height(this.buttonHeight)

      Button('DatePicker').onClick(() => {
        router.pushUrl({
          url: 'pages/DatePicker'
        })
      })
        .fontSize(this.fontSize)
        .height(this.buttonHeight)

      Button('TimePicker').onClick(() => {
        router.pushUrl({
          url: 'pages/TimePicker'
        })
      })
        .fontSize(this.fontSize)
        .height(this.buttonHeight)

      Button('TextPicker-LongPage').onClick(() => {
        router.pushUrl({
          url: 'pages/PickerLongPage'
        })
      })
        .fontSize(this.fontSize)
        .height(this.buttonHeight)

      Button('TextPicker-Age').onClick(() => {
        router.pushUrl({
          url: 'pages/TextPickerAge'
        })
      })
        .fontSize(this.fontSize)
        .height(this.buttonHeight)

      Button('TextPicker-RangeTest').onClick(() => {
        router.pushUrl({
          url: 'pages/TextPickerRangeTest'
        })
      })
        .fontSize(this.fontSize)
        .height(this.buttonHeight)

      Button('TextPicker-Sport').onClick(() => {
        router.pushUrl({
          url: 'pages/TextPickerSports'
        })
      })
        .fontSize(this.fontSize)
        .height(this.buttonHeight)

      Button('TimePicker-Dirty').onClick(() => {
        router.pushUrl({
          url: 'pages/TimePickerBindSheet'
        })
      })
        .fontSize(this.fontSize)
        .height(this.buttonHeight)

      Button('Mechanical Picker').onClick(() => {
        router.pushUrl({
          url: 'pages/TextPickerSlideDemo'
        })
      })
        .fontSize(this.fontSize)
        .height(this.buttonHeight)

      Button('TextPicker MatchParent').onClick(() => {
        router.pushUrl({
          url: 'pages/TextPickerMatchParent'
        })
      })
        .fontSize(this.fontSize)
        .height(this.buttonHeight)

      Button('TextPicker Three').onClick(() => {
        router.pushUrl({
          url: 'pages/TextPickerThree'
        })
      })
        .fontSize(this.fontSize)
        .height(this.buttonHeight)

      Button('ComponentV2').onClick(() => {
        router.pushUrl({
          url: 'pages/ComponentV2Test'
        })
      })
        .fontSize(this.fontSize)
        .height(this.buttonHeight)

      Button('CalendarPickerDialog Memory Test').onClick(() => {
        router.pushUrl({
          url: 'pages/CalendarPickerDialogMemTest'
        })
      })
        .fontSize(this.fontSize)
        .height(this.buttonHeight)

      Button('Multi TextPicker').onClick(() => {
        router.pushUrl({
          url: 'pages/MultiTextPicker'
        })
      })
        .fontSize(this.fontSize)
        .height(this.buttonHeight)

      Text(`${new Date()}`)
        .backgroundColor(Color.Pink)
        .fontWeight(FontWeight.Normal)
        .width('100%')
        .textAlign(TextAlign.Center)
        .align(Alignment.Bottom)

      Text(`100vp = ${vp2px(100)}px`)
    }
    .justifyContent(FlexAlign.SpaceBetween)
    .width('100%')
    .height('100%')
    .backgroundColor('#A0EEA0')
  }
}
