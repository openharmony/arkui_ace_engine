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
struct DatePickerDialogExample {
  selectedDate: Date = new Date('2010-1-1');

  build() {
    Column() {
      Button('DatePickerDialog')
        .margin(20)
        .onClick(() => {
          DatePickerDialog.show({ // 建议使用 this.getUIContext().showDatePickerDialog()接口
            start: new Date('2000-1-1'),
            end: new Date('2100-12-31'),
            selected: this.selectedDate,
            showTime: true,
            useMilitaryTime: false,
            disappearTextStyle: { color: Color.Pink, font: { size: '22fp', weight: FontWeight.Bold }},
            textStyle: { color: '#ff00ff00', font: { size: '18fp', weight: FontWeight.Normal }},
            selectedTextStyle: { color: '#ff182431', font: { size: '14fp', weight: FontWeight.Regular }},
            onDateAccept: (value: Date) => {
              // 通过Date的setFullYear方法设置按下确定按钮时的日期，这样当弹窗再次弹出时显示选中的是上一次确定的日期
              this.selectedDate = value;
              console.info('DatePickerDialog:onDateAccept()' + value.toString());
            },
            onCancel: () => {
              console.info('DatePickerDialog:onCancel()');
            },
            onDateChange: (value: Date) => {
              console.info('DatePickerDialog:onDateChange()' + value.toString());
            },
            onDidAppear: () => {
              console.info('DatePickerDialog:onDidAppear()');
            },
            onDidDisappear: () => {
              console.info('DatePickerDialog:onDidDisappear()');
            },
            onWillAppear: () => {
              console.info('DatePickerDialog:onWillAppear()');
            },
            onWillDisappear: () => {
              console.info('DatePickerDialog:onWillDisappear()');
            },
            enableHoverMode: true,
            hoverModeArea: HoverModeAreaType.TOP_SCREEN
          })
        })
    }.width('100%')
  }
}
