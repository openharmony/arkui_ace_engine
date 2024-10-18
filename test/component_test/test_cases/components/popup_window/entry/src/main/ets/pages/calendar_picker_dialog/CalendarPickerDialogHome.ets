/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import { CommonButton } from '../../util/CommonButton';

@Entry
@Component
struct CalendarPickerDialogHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('CalendarPickerDialogHome')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)

        CommonButton({
          buttonName: 'CalendarPickerDialogOnAccept',
          buttonUrl: 'pages/calendar_picker_dialog/CalendarPickerDialogOnAcceptSample'
        });
        CommonButton({
          buttonName: 'CalendarPickerDialogOnCancel',
          buttonUrl: 'pages/calendar_picker_dialog/CalendarPickerDialogOnCancelSample'
        });
        CommonButton({
          buttonName: 'CalendarPickerDialogOnChange',
          buttonUrl: 'pages/calendar_picker_dialog/CalendarPickerDialogOnChangeSample'
        });
        CommonButton({
          buttonName: 'CalendarPickerDialogBackgroundColor',
          buttonUrl: 'pages/calendar_picker_dialog/CalendarPickerDialogBackgroundColorSample'
        });
        CommonButton({
          buttonName: 'CalendarPickerDialogBackgroundBlurStyle',
          buttonUrl: 'pages/calendar_picker_dialog/CalendarPickerDialogBackgroundBlurStyleSample'
        });
      }
      .padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}