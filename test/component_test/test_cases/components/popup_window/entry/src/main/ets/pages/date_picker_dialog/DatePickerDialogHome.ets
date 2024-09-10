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
struct DatePickerDialogHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('DatePickerDialogHome')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)

        CommonButton({
          buttonName: 'DatePickerDialogAlignment',
          buttonUrl: 'pages/date_picker_dialog/DatePickerDialogAlignmentSample'
        });
        CommonButton({
          buttonName: 'DatePickerDialogBackgroundBlurStyle',
          buttonUrl: 'pages/date_picker_dialog/DatePickerDialogBackgroundBlurStyleSample'
        });
        CommonButton({
          buttonName: 'DatePickerDialogBackgroundColor',
          buttonUrl: 'pages/date_picker_dialog/DatePickerDialogBackgroundColorSample'
        });
        CommonButton({
          buttonName: 'DatePickerDialogDisappearTextStyle',
          buttonUrl: 'pages/date_picker_dialog/DatePickerDialogDisappearTextStyleSample'
        });
        CommonButton({
          buttonName: 'DatePickerDialogLunar',
          buttonUrl: 'pages/date_picker_dialog/DatePickerDialogLunarSample'
        });
        CommonButton({
          buttonName: 'DatePickerDialogLunarSwitch',
          buttonUrl: 'pages/date_picker_dialog/DatePickerDialogLunarSwitchSample'
        });
        CommonButton({
          buttonName: 'DatePickerDialogMaskRect',
          buttonUrl: 'pages/date_picker_dialog/DatePickerDialogMaskRectSample'
        });
        CommonButton({
          buttonName: 'DatePickerDialogOffset',
          buttonUrl: 'pages/date_picker_dialog/DatePickerDialogOffsetSample'
        });
        CommonButton({
          buttonName: 'DatePickerDialogOnCancel',
          buttonUrl: 'pages/date_picker_dialog/DatePickerDialogOnCancelSample'
        });
        CommonButton({
          buttonName: 'DatePickerDialogOnDateAccept',
          buttonUrl: 'pages/date_picker_dialog/DatePickerDialogOnDateAcceptSample'
        });
        CommonButton({
          buttonName: 'DatePickerDialogOnDateChange',
          buttonUrl: 'pages/date_picker_dialog/DatePickerDialogOnDateChangeSample'
        });
        CommonButton({
          buttonName: 'DatePickerDialogSelectedTextStyle',
          buttonUrl: 'pages/date_picker_dialog/DatePickerDialogSelectedTextStyleSample'
        });
        CommonButton({
          buttonName: 'DatePickerDialogShowTime',
          buttonUrl: 'pages/date_picker_dialog/DatePickerDialogShowTimeSample'
        });
        CommonButton({
          buttonName: 'DatePickerDialogTextStyle',
          buttonUrl: 'pages/date_picker_dialog/DatePickerDialogTextStyleSample'
        });
        CommonButton({
          buttonName: 'DatePickerDialogUseMilitaryTime',
          buttonUrl: 'pages/date_picker_dialog/DatePickerDialogUseMilitaryTimeSample'
        });
      }
      .padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}