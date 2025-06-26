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

interface ListCategories {
  title:string,
  url:string
}

@Entry
@Component
struct CalendarPickerExample {
  @State message: string = ' ';
  private items: ListCategories[] = [
    {title: 'CalendarPickerExample001', url: 'pages/CalendarPicker_safe_area/CalendarPicker001'},
    {title: 'CalendarPickerExample002', url: 'pages/CalendarPicker_safe_area/CalendarPicker002'},
    {title: 'CalendarPickerExample003', url: 'pages/CalendarPicker_safe_area/CalendarPicker003'},
    {title: 'CalendarPickerExample004', url: 'pages/CalendarPicker_safe_area/CalendarPicker004'},
    {title: 'CalendarPickerExample005', url: 'pages/CalendarPicker_safe_area/CalendarPicker005'},
    {title: 'CalendarPickerExample006', url: 'pages/CalendarPicker_safe_area/CalendarPicker006'},
    {title: 'CalendarPickerExample007', url: 'pages/CalendarPicker_safe_area/CalendarPicker007'},
    {title: 'CalendarPickerExample008', url: 'pages/CalendarPicker_safe_area/CalendarPicker008'},
    {title: 'CalendarPickerExample009', url: 'pages/CalendarPicker_safe_area/CalendarPicker009'},
    {title: 'CalendarPickerExample010', url: 'pages/CalendarPicker_safe_area/CalendarPicker010'},
    {title: 'CalendarPickerExample011', url: 'pages/CalendarPicker_safe_area/CalendarPicker011'},
    {title: 'CalendarPickerExample012', url: 'pages/CalendarPicker_safe_area/CalendarPicker012'},
    {title: 'CalendarPickerExample013', url: 'pages/CalendarPicker_safe_area/CalendarPicker013'},
  ]

  build() {
    Column() {
      List({space: '10vp'}) {
        ForEach(this.items, (item: ListCategories) => {
          ListItem() {
            Text(item.title).fontSize(16).fontWeight(FontWeight.Bold).onClick(() => {
              router.pushUrl({url: item.url})
            })
            .padding(12)
          }
          .width('90%')
          .backgroundColor('#ff53ecd9')
          .borderRadius(10)
        })
      }
      .alignListItem(ListItemAlign.Center)
      .margin({top: '10vp'})
      .width('100%')
      .height('90%')
    }
    .width('100%')
    .height('100%')
  }
}
