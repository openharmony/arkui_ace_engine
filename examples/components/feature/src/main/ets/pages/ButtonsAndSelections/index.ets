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

import { Route, RouteGroup } from 'common/src/main/ets/common/route';
import { ButtonBootcamp } from './ButtonBootcamp';
import { CalendarPickerBootcamp } from './CalendarPickerBootcamp';
import { CheckboxBootcamp } from './CheckboxBootcamp';
import { CheckboxGroupBootcamp } from './CheckboxGroupBootcamp';
import { DatePickerBootcamp } from './DatePickerBootcamp';
import { RadioBootcamp } from './RadioBootcamp';
import { RatingBootcamp } from './RatingBootcamp';
import { SelectBootcamp } from './SelectBootcamp';
import { SliderBootcamp } from './SliderBootcamp';
import { TextPickerBootcamp } from './TextPickerBootcamp';
import { TimePickerBootcamp } from './TimePickerBootcamp';
import { ToggleBootcamp } from './ToggleBootcamp';


export const buttonsAndSelectionsRoute: RouteGroup = {
  name: 'ButtonsAndSelections',
  label: '按钮与选择',
  children: [
    { name: 'Button', label: '按钮/Button' },
    { name: 'Toggle', label: '切换按钮/Toggle' },
    { name: 'Checkbox', label: '多选框/Checkbox' },
    { name: 'CheckboxGroup', label: '勾选文本/CheckboxGroup' },
    { name: 'CalendarPicker', label: '日历选择器/CalendarPicker' },
    { name: 'DatePicker', label: '日期选择器/DatePicker' },
    { name: 'TextPicker', label: '文本选择器/TextPicker' },
    { name: 'TimePicker', label: '时间选择器/TimePicker' },
    { name: 'Radio', label: '单选框/Radio' },
    { name: 'Rating', label: '评分条/Rating' },
    { name: 'Slider', label: '滑动条/Slider' },
    { name: 'Select', label: '下拉按钮/Select' }

  ]
};

@Builder
export function buttonsAndSelectionsDestination(name: string, route: Route) {
  if (name === 'ButtonsAndSelections/Button') {
    ButtonBootcamp({title: route.label})
  }else if (name === 'ButtonsAndSelections/Toggle'){
    ToggleBootcamp({title: route.label})
  }else if (name === 'ButtonsAndSelections/Checkbox'){
    CheckboxBootcamp({title: route.label})
  }else if (name === 'ButtonsAndSelections/CheckboxGroup'){
    CheckboxGroupBootcamp({title: route.label})
  }else if (name === 'ButtonsAndSelections/CalendarPicker'){
    CalendarPickerBootcamp({title: route.label})
  }else if (name === 'ButtonsAndSelections/DatePicker'){
    DatePickerBootcamp({title: route.label})
  }else if (name === 'ButtonsAndSelections/TextPicker'){
    TextPickerBootcamp({title: route.label})
  }else if (name === 'ButtonsAndSelections/TimePicker'){
    TimePickerBootcamp({title: route.label})
  }else if (name === 'ButtonsAndSelections/Radio'){
    RadioBootcamp({title: route.label})
  }else if (name === 'ButtonsAndSelections/Rating'){
    RatingBootcamp({title: route.label})
  }else if (name === 'ButtonsAndSelections/Slider'){
    SliderBootcamp({title: route.label})
  }else if (name === 'ButtonsAndSelections/Select'){
    SelectBootcamp({title: route.label})
  }

}
