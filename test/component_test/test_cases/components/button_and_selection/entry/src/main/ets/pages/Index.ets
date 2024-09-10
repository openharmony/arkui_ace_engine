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

import { CommonButton } from '../util/CommonButton';

@Entry
@Component
struct Index {
  aboutToAppear() {
  }

  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('BenchmarkSample')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)

        CommonButton({ buttonName: 'Button', buttonUrl: 'pages/button/ButtonHome' });
        CommonButton({ buttonName: 'CalendarPicker', buttonUrl: 'pages/calendar_picker/CalendarPickerHome' });
        CommonButton({ buttonName: 'Checkbox', buttonUrl: 'pages/checkbox/CheckboxHome' });
        CommonButton({ buttonName: 'CheckboxGroup', buttonUrl: 'pages/checkbox_group/CheckboxGroupHome' });
        CommonButton({ buttonName: 'Counter', buttonUrl: 'pages/counter/CounterHome' });
        CommonButton({ buttonName: 'DatePicker', buttonUrl: 'pages/date_picker/DatePickerHome' });
        CommonButton({ buttonName: 'Radio', buttonUrl: 'pages/radio/RadioHome' });
        CommonButton({ buttonName: 'Rating', buttonUrl: 'pages/rating/RatingHome' });
        CommonButton({ buttonName: 'Select', buttonUrl: 'pages/select/SelectHome' });
        CommonButton({ buttonName: 'Slider', buttonUrl: 'pages/slider/SliderHome' });
        CommonButton({ buttonName: 'TextPicker', buttonUrl: 'pages/text_picker/TextPickerHome' });
        CommonButton({ buttonName: 'TimePicker', buttonUrl: 'pages/time_picker/TimePickerHome' });
        CommonButton({ buttonName: 'Toggle', buttonUrl: 'pages/toggle/ToggleHome' });
      }
      .padding('20vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}