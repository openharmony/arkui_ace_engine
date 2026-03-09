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

@Entry
@Component
struct Index {
  build() {
    Column({ space: 20 }) {
      // 标题
      Text('Picker 主题测试应用')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .textAlign(TextAlign.Center)
        .width('100%')
        .margin({ top: 50, bottom: 30 });

      // 应用说明
      Text('选择要测试的Picker组件')
        .fontSize(18)
        .fontColor('#333333')
        .textAlign(TextAlign.Center)
        .width('100%')
        .margin({ bottom: 40 });

      // 测试选项按钮
      Column({ space: 20 }) {
        Button('测试DatePicker')
          .width('80%')
          .height(50)
          .fontSize(18)
          .backgroundColor('#007DFF')
          .onClick(() => {
            router.pushUrl({
              url: 'pages/DatePickerPage'
            });
          });

        Button('测试TimePicker')
          .width('80%')
          .height(50)
          .fontSize(18)
          .backgroundColor('#34A853')
          .onClick(() => {
            router.pushUrl({
              url: 'pages/TimePickerPage'
            });
          });

        Button('测试TextPicker')
          .width('80%')
          .height(50)
          .fontSize(18)
          .backgroundColor('#9C27B0')
          .onClick(() => {
            router.pushUrl({
              url: 'pages/TextPickerPage'
            });
          });

        Button('测试CalendarPicker')
          .width('80%')
          .height(50)
          .fontSize(18)
          .backgroundColor('#FF9800')
          .onClick(() => {
            router.pushUrl({
              url: 'pages/CalendarPickerPage'
            });
          });
      }
      .width('100%')
      .alignItems(HorizontalAlign.Center);

      // 底部说明
      Text('选择不同的Picker组件，体验主题切换效果')
        .fontSize(14)
        .fontColor('#666666')
        .textAlign(TextAlign.Center)
        .width('100%')
        .margin({ top: 50 });
    }
    .width('100%')
    .height('100%')
    .padding(20)
    .backgroundColor('#F5F5F5');
  }
}