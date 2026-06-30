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
  @State datePickerComponentExamples: ExampleItem[] = [
    { title: 'DatePickerComponent Basic', pagePath: 'pages/advanced_datepickercomponent/DatePickerComponentExample001', description: 'Basic DatePickerComponent with interactive controls' },
    { title: 'DatePickerComponent Lunar', pagePath: 'pages/advanced_datepickercomponent/DatePickerComponentExample002', description: 'Lunar calendar support' },
    { title: 'DatePickerComponent DateMode', pagePath: 'pages/advanced_datepickercomponent/DatePickerComponentExample003', description: 'Different date picker modes' },
    { title: 'DatePickerComponent DisplayMode', pagePath: 'pages/advanced_datepickercomponent/DatePickerComponentExample004', description: 'Date, time and date-time display modes' },
    { title: 'DatePickerComponent TimeFormat', pagePath: 'pages/advanced_datepickercomponent/DatePickerComponentExample005', description: 'Time format and military time' },
    { title: 'DatePickerComponent Date Range', pagePath: 'pages/advanced_datepickercomponent/DatePickerComponentExample006', description: 'Dynamic date range configuration' },
    { title: 'DatePickerComponent Locale', pagePath: 'pages/advanced_datepickercomponent/DatePickerComponentExample007', description: 'Multi-language and localization support' },
    { title: 'DatePickerComponent Interactive Demo', pagePath: 'pages/advanced_datepickercomponent/DatePickerComponentExample008', description: 'Full-featured interactive control panel' },
  ];

  build() {
    Scroll() {
      Column({ space: 12 }) {
        Text('DatePickerComponent Examples')
          .fontSize(28)
          .fontWeight(FontWeight.Bold)
          .width('100%')
          .padding(16)
          .backgroundColor('#F5F5F5')

        Text('Advanced DatePickerComponent (@ohos.arkui.advanced)')
          .fontSize(20)
          .fontWeight(FontWeight.Medium)
          .width('100%')
          .padding({ left: 16, right: 16, top: 12, bottom: 8 })

        ForEach(this.datePickerComponentExamples, (item: ExampleItem) => {
          this.ExampleItemComponent(item)
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
