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
import { TextPickerDialogBootcamp } from './TextPickerDialogBootcamp';
import { TimePickerDialogBootcamp } from './TimePickerDialogBootcamp';
import { DatePickerDialogBootcamp } from './DatePickerDialogBootcamp';
import { CalendarPickerDialogBootcamp } from './CalendarPickerDialogBootcamp';
import { ListItemGroupBootcamp } from './ListItemGroupBootcamp';

export const containersRoute: RouteGroup = {
  name: 'containers',
  label: '容器类',
  children: [
    { name: 'text-picker-dialog', label: '文本选择器弹窗/TextpickerDialog' },
    { name: 'time-picker-dialog', label: '时间选择器弹窗/TimepickerDialog' },
    { name: 'date-picker-dialog', label: '日期选择器弹窗/DatepickerDialog' },
    { name: 'calendar-picker-dialog', label: '日历选择器弹窗/CalendarPickerDialog' },
    { name: 'list-item-group', label: '分组列表/ListItemGroup'},
  ]
};

@Builder
export function ContainersDestination(name: string, route: Route) {
  if (name === 'containers/text-picker-dialog') {
    TextPickerDialogBootcamp({ title: route.label })
  } else if (name === 'containers/time-picker-dialog') {
    TimePickerDialogBootcamp({ title: route.label })
  } else if (name === 'containers/date-picker-dialog') {
    DatePickerDialogBootcamp({ title: route.label })
  } else if (name === 'containers/calendar-picker-dialog') {
    CalendarPickerDialogBootcamp({ title: route.label })
  } else if (name === 'containers/list-item-group') {
    ListItemGroupBootcamp({ title: route.label })
  }
}
