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
struct TextPickerExample {
  @State message: string = ' ';
  private items: ListCategories[] = [
    {title: 'TextPickerExample001', url: 'pages/TextPicker_safe_area/TextPicker001'},
    {title: 'TextPickerExample002', url: 'pages/TextPicker_safe_area/TextPicker002'},
    {title: 'TextPickerExample003', url: 'pages/TextPicker_safe_area/TextPicker003'},
    {title: 'TextPickerExample004', url: 'pages/TextPicker_safe_area/TextPicker004'},
    {title: 'TextPickerExample005', url: 'pages/TextPicker_safe_area/TextPicker005'},
    {title: 'TextPickerExample006', url: 'pages/TextPicker_safe_area/TextPicker006'},
    {title: 'TextPickerExample007', url: 'pages/TextPicker_safe_area/TextPicker007'},
    {title: 'TextPickerExample008', url: 'pages/TextPicker_safe_area/TextPicker008'},
    {title: 'TextPickerExample009', url: 'pages/TextPicker_safe_area/TextPicker009'},
    {title: 'TextPickerExample010', url: 'pages/TextPicker_safe_area/TextPicker010'},
    {title: 'TextPickerExample011', url: 'pages/TextPicker_safe_area/TextPicker011'},
    {title: 'TextPickerExample012', url: 'pages/TextPicker_safe_area/TextPicker012'},
    {title: 'TextPickerExample013', url: 'pages/TextPicker_safe_area/TextPicker013'},
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
