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
import router from '@ohos.router';

interface ExampleItem {
  title: string;
  pagePath: string;
  description: string;
}

@Entry
@Component
struct Index {
  @State datePickerExamples: ExampleItem[] = [
    { title: 'DatePicker Basic', pagePath: 'pages/datepicker/DatePickerExample001', description: 'Basic DatePicker with lunar support' },
    { title: 'DatePicker TextStyle', pagePath: 'pages/datepicker/DatePickerExample002', description: 'Custom text styles' },
    { title: 'DatePicker Mode', pagePath: 'pages/datepicker/DatePickerExample003', description: 'Different picker modes' },
    { title: 'DatePicker AttributeModifier', pagePath: 'pages/datepicker/DatePickerExample004', description: 'AttributeModifier usage' },
    { title: 'DatePicker DateOrder', pagePath: 'pages/datepicker/DatePickerExample005', description: 'SDK22 dateOrder property' },
    { title: 'DatePicker HapticFeedback', pagePath: 'pages/datepicker/DatePickerExample006', description: 'SDK22 haptic feedback' },
  ];

  @State datePickerDialogExamples: ExampleItem[] = [
    { title: 'DatePickerDialog Basic', pagePath: 'pages/datepicker_dialog/DatePickerDialogExample001', description: 'Basic dialog usage' },
    { title: 'DatePickerDialog TextStyle', pagePath: 'pages/datepicker_dialog/DatePickerDialogExample002', description: 'Custom text styles' },
    { title: 'DatePickerDialog Lunar', pagePath: 'pages/datepicker_dialog/DatePickerDialogExample003', description: 'Lunar calendar support' },
    { title: 'DatePickerDialog HoverMode', pagePath: 'pages/datepicker_dialog/DatePickerDialogExample004', description: 'SDK14 hover mode' },
    { title: 'DatePickerDialog AreaOverlap', pagePath: 'pages/datepicker_dialog/DatePickerDialogExample005', description: 'SDK22 area overlap' },
    { title: 'DatePickerDialog HapticFeedback', pagePath: 'pages/datepicker_dialog/DatePickerDialogExample006', description: 'SDK16 haptic feedback' },
  ];

  build() {
    Scroll() {
      Column({ space: 12 }) {
        Text('DatePicker SDK22 Examples')
          .fontSize(28)
          .fontWeight(FontWeight.Bold)
          .width('100%')
          .padding(16)
          .backgroundColor('#F5F5F5')

        Text('DatePicker Component')
          .fontSize(20)
          .fontWeight(FontWeight.Medium)
          .width('100%')
          .padding({ left: 16, right: 16, top: 12, bottom: 8 })

        ForEach(this.datePickerExamples, (item: ExampleItem) => {
          this ExampleItemComponent(item)
        })

        Text('DatePickerDialog Component')
          .fontSize(20)
          .fontWeight(FontWeight.Medium)
          .width('100%')
          .padding({ left: 16, right: 16, top: 12, bottom: 8 })

        ForEach(this.datePickerDialogExamples, (item: ExampleItem) => {
          this ExampleItemComponent(item)
        })
      }
      .padding(16)
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#FFFFFF')
  }

  @Builder
  ExampleItemComponent(item: ExampleItem) {
    Row() {
      Column() {
        Text(item.title)
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .textAlign(TextAlign.Start)
        Text(item.description)
          .fontSize(12)
          .fontColor('#666666')
          .textAlign(TextAlign.Start)
          .margin({ top: 4 })
      }
      .alignItems(HorizontalAlign.Start)
      .width('80%')

      Text('>')
        .fontSize(20)
        .fontColor('#999999')
    }
    .width('100%')
    .padding(16)
    .backgroundColor('#FAFAFA')
    .borderRadius(8)
    .onClick(() => {
      router.pushUrl({ url: item.pagePath });
    })
  }
}
