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
import { BindContextMenuBootcamp } from './BindContextMenuBootcamp';
import { BindMenuBootcamp } from './BindMenuBootcamp';
import { ButtonBootcamp } from './ButtonBootcamp';
import { ChipBootcamp } from './ChipBootcamp';
import { SelectBootcamp } from './SelectBootcamp';
import { MenuBootcamp } from './MenuBootcamp';
import { BindSheetBootcamp } from './BindSheetBootcamp';
import { MenuItemGroupBootcamp } from './MenuItemGroupBootcamp';
import { ActionDialogBootcamp } from './ActionDialogBootcamp';

export const operatesRoute: RouteGroup = {
  name: 'operates',
  label: '操作类',
  children: [
    { name: 'button', label: '按钮/Button' },
    { name: 'Menu', label: '菜单/Menu' },
    { name: 'BindContextMenu', label: '上下文菜单/BindContextMenu' },
    { name: 'chip', label: '操作块/Chip' },
    { name: 'select', label: '下拉按钮/Select' },
    { name: 'menu', label: '菜单/menu' },
    { name: 'bindsheet', label: '半模态/BindSheet' },
    { name: 'MenuItemGroup', label: '菜单分组/MenuItemGroup' },
    { name: 'ActionSheet', label: '列表选择弹窗/ActionSheet' },
  ]
};

@Builder
export function OperatesDestination(name: string, route: Route) {
  if (name === 'operates/button') {
    ButtonBootcamp({ title: route.label })
  } else if (name === 'operates/Menu') {
    BindMenuBootcamp({ title: route.label })
  } else if (name === 'operates/BindContextMenu') {
    BindContextMenuBootcamp({ title: route.label })
  } else if (name === 'operates/chip') {
    ChipBootcamp({ title: route.label })
  } else if (name === 'operates/select') {
    SelectBootcamp({ title: route.label })
  } else if (name === 'operates/menu') {
    MenuBootcamp({ title: route.label })
  } else if (name === 'operates/bindsheet') {
    BindSheetBootcamp({ title: route.label })
  } else if (name === 'operates/MenuItemGroup') {
    MenuItemGroupBootcamp({ title: route.label })
  } else if (name === 'operates/ActionSheet') {
    ActionDialogBootcamp({ title: route.label })
  }
}

