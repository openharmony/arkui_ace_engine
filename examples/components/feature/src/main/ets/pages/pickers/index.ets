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
import { CalendarPickerBootcamp } from './CalendarPickerBootcamp';
import { DatePickerBootcamp } from './DatePickerBootcamp';
import { CheckboxGroupBootcamp } from './CheckboxGroupBootcamp';
import { CheckboxBootcamp } from './CheckboxBootcamp'
import { RatingBootcamp } from './RatingBootcamp';
import { ToggleBootcamp } from './ToggleBootcamp';
import { SliderBootcamp } from '../pickers/SliderBootcamp';
import { TextPickerBootcamp } from './TextPickerBootcamp';
import { RadioBootcamp } from './RadioBootcamp';
import { TimePickerBootcamp } from './TimePickerBootcamp';

export const pickersRoute: RouteGroup = {
  name: 'pickers',
  label: '选择类',
  children: [
    { name: 'calendar', label: '日历选择器/calendar' },
    { name: 'date', label: '日期选择器/Date' },
    { name: 'checkbox-group', label: '勾选文本/CheckboxGroup' },
    { name: 'checkbox', label: '多选框/Checkbox' },
    { name: 'rating', label: '评分条/Rating' },
    { name: 'toggle', label: '切换按钮/Toggle' },
    { name: 'Slider', label: '滑动条/Slider' },
    { name: 'text-picker', label: '文本选择器/TextPicker' },
    { name: 'Radio', label: '单选框/Radio' },
    { name: 'Timepicker', label: '时间选择器/Timepicker' },
  ]
};

@Builder
export function PickersDestination(name: string, route: Route) {
  if (name === 'pickers/calendar') {
    CalendarPickerBootcamp({ title: route.label })
  } else if (name === 'pickers/date') {
    DatePickerBootcamp({ title: route.label })
  } else if (name === 'pickers/checkbox-group') {
    CheckboxGroupBootcamp({ title: route.label })
  } else if (name === 'pickers/checkbox') {
    CheckboxBootcamp({ title: route.label })
  } else if (name === 'pickers/rating') {
    RatingBootcamp({ title: route.label })
  } else if (name === 'pickers/toggle') {
    ToggleBootcamp({ title: route.label })
  } else if (name === 'pickers/Radio') {
    RadioBootcamp({ title: route.label })
  } else if (name === 'pickers/Slider') {
    SliderBootcamp({ title: route.label })
  } else if (name==='pickers/text-picker'){
    TextPickerBootcamp({title: route.label})
  } else if (name === 'pickers/Timepicker') {
    TimePickerBootcamp({ title: route.label })
  }
}
