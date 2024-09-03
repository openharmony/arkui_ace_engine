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

import { Route, RouteGroup } from '../../common/route';
import { CalendarPickerDialogBootcamp } from './CalendarPickerDialogBootcamp';

export const containersRoute: RouteGroup = {
  name: 'containers',
  label: '容器类',
  children: [
    { name: 'calendar-picker-dialog', label: '日历选择器弹窗/CalendarPickerDialog' },
  ]
};

@Builder
export function ContainersDestination(name: string, route: Route) {
  if (name === 'containers/calendar-picker-dialog') {
    CalendarPickerDialogBootcamp({ title: route.label })
  }
}