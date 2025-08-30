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

import { intl } from '@kit.LocalizationKit';

@Entry
@Component
struct DatePickerDialogDST {
  @State dateOfBirth: string = '';
  @State selectedDate: Date = new Date()

  build() {
    Column() {
      TextInput({
        text: $$this.dateOfBirth
      })
        .fontColor(Color.Black)
        .enabled(false)

      Button('选择')
        .type(ButtonType.Normal)
        .onClick(() => {
          this.getUIContext().showDatePickerDialog({
            selected: this.selectedDate,
            lunar: false,
            showTime: true,
            useMilitaryTime: true,
            lunarSwitch: true,
            alignment: DialogAlignment.Center,
            offset: { dx: 0, dy: 0 },
            onDateAccept: (value: Date) => {
              console.log('onDateAccept(): ' + value.toString());
              if (value > new Date) {
                console.log('value > new Date')
              } else {
                this.selectedDate = value
                console.log('value <= new Date')
                let shortFormat: intl.DateTimeFormat =
                  new intl.DateTimeFormat('zh-CN', { dateStyle: 'short', timeStyle: 'short' })
                this.dateOfBirth = shortFormat.format(value)
              }
            }
          })
        })
    }
  }
}
