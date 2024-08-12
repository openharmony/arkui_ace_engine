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
import { CalendarPickerBootcamp } from './CalendarPickerBootcamp';
import { RatingBootcamp } from '../pickers/RatingBootcamp';

export const pickersRoute: RouteGroup = {
  name: 'pickers',
  label: '选择类',
  children: [
    { name: 'calendar', label: '日历选择器/calendar' },
    { name: 'rating', label: '评分条/Rating' },
  ]
};

@Builder
export function PickersDestination(name: string, route: Route) {
  if (name === 'pickers/calendar') {
    CalendarPickerBootcamp({ title: route.label })
  } else if (name === 'pickers/rating') {
    RatingBootcamp({ title: route.label })
  }
}
