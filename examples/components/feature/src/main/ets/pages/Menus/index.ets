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
import { MenuBootcamp } from './MenuBootcamp';
import { MenuItemGroupBootcamp } from './MenuItemGroupBootcamp';


export const menusRoute: RouteGroup = {
  name: 'Menus',
  label: '菜单',
  children: [
    { name: 'Menu', label: '菜单/Menu' },
    { name: 'MenuItemGroup', label: '菜单分组/MenuItemGroup' }

  ]
};

@Builder
export function menusDestination(name: string, route: Route) {
  if (name === 'Menus/Menu') {
    MenuBootcamp({ title: route.label })
  } else if (name === 'Menus/MenuItemGroup') {
    MenuItemGroupBootcamp({ title: route.label })
  }
}
