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
import { StepperBootcamp } from './StepperBootcamp';
import { NavDestinationBootcamp } from './NavDestinationBootcamp';
import { NavigationBootcamp } from './NavigationBootcamp';
import { SwiperBootcamp } from './SwiperBootcamp';
import { TabContentBootcamp } from './TabContentBootcamp'
import { TabsBootcamp } from './TabsBootcamp'

export const navigatesRoute: RouteGroup = {
  name: 'navigates',
  label: '导航类',
  children: [
    { name: 'swiper', label: '轮播/Swiper' },
    { name: 'tabContent', label: '页签内容/TabContent' },
    { name: 'tabs', label: '页签容器/Tabs' },
    { name: 'toolbar', label: '工具栏/ToolBar' },
    { name: 'stepper', label: '步骤导航/Stepper' }
    { name: 'navDestination', label: '导航/NavDestination' },
    { name: 'navigation', label: '导航/Navigation' },
  ]
};


@Builder
export function NavigatesDestination(name: string, route: Route) {
  if (name === 'navigates/swiper') {
    SwiperBootcamp({ title: route.label });
  } else if (name == 'navigates/tabContent') {
    TabContentBootcamp({ title: route.label })
  } else if (name === 'navigates/tabs') {
    TabsBootcamp({ title: route.label })
  } else if (name === 'navigates/navDestination') {
    NavDestinationBootcamp({ title: route.label })
  } else if (name === 'navigates/navigation') {
    NavigationBootcamp({ title: route.label })
  } else if (name === 'navigates/toolbar') {
    ToolBarBootcamp({ title: route.label })
  } else if (name === 'navigates/stepper') {
    StepperBootcamp({ title: route.label })
  }
}