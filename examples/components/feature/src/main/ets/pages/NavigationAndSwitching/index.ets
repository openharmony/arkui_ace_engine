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
import { NavDestinationBootcamp } from './NavDestinationBootcamp';
import { NavigationBootcamp } from './NavigationBootcamp';
import { StepperBootcamp } from './StepperBootcamp';
import { TabContentBootcamp } from './TabContentBootcamp';
import { TabsBootcamp } from './TabsBootcamp';
import { StepperItemBootcamp } from './StepperItemBootcamp';


export const navigationAndSwitchingRoute: RouteGroup = {
  name: 'NavigationAndSwitching',
  label: '导航与切换',
  children: [
    { name: 'Navigation', label: '导航/Navigation' },
    { name: 'NavDestination', label: '导航/NavDestination' },
    { name: 'Stepper', label: '步骤导航/Stepper' },
    { name: 'StepperItem', label: '步骤导航项/StepperItem' },
    { name: 'TabContent', label: '页签内容/TabContent' },
    { name: 'Tabs', label: '页签容器/Tabs' }
  ]
};

@Builder
export function navigationAndSwitchingDestination(name: string, route: Route) {
  if (name === 'NavigationAndSwitching/Navigation') {
    NavigationBootcamp({title: route.label})
  }else if (name === 'NavigationAndSwitching/NavDestination'){
    NavDestinationBootcamp({title: route.label})
  }else if (name === 'NavigationAndSwitching/Stepper'){
    StepperBootcamp({title: route.label})
  }else if (name === 'NavigationAndSwitching/TabContent'){
    TabContentBootcamp({title: route.label})
  }else if (name === 'NavigationAndSwitching/Tabs'){
    TabsBootcamp({title: route.label})
  }else if (name == 'NavigationAndSwitching/StepperItem') {
    StepperItemBootcamp({ title: route.label })
  }

}
