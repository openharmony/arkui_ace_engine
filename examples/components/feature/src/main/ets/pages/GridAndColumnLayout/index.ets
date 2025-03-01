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
import { ColumnSplitBootcamp } from './ColumnSplitBootcamp';
import { FoldSplitContainerBootcamp } from './FoldSplitContainerBootcamp';
import { GridColBootcamp } from './GridColBootcamp';
import { GridRowBootcamp } from './GridRowBootcamp';
import { RowSplitBootcamp } from './RowSplitBootcamp';
import { SideBarContainerBootcamp } from './SideBarContainerBootcamp';
import { ToolBarBootcamp } from './ToolBarBootcamp';


export const gridAndColumnLayoutRoute: RouteGroup = {
  name: 'GridAndColumnLayout',
  label: '栅格与分栏',
  children: [
    { name: 'GridRow', label: '栅格行/GridRow' },
    { name: 'GridCol', label: '栅格列/GridCol' },
    { name: 'ColumnSplit', label: '纵向分割容器/ColumnSplit' },
    { name: 'RowSplit', label: '横向分割容器/RowSplit' },
    { name: 'FoldSplitContainer', label: '折叠屏分栏组件/FoldSplitContainer' },
    { name: 'SideBarContainer', label: '侧边栏容器/SideBarContainer' },
    { name: 'ToolBar', label: '工具栏/ToolBar' }
  ]
};

@Builder
export function gridAndColumnLayoutDestination(name: string, route: Route) {
  if (name === 'GridAndColumnLayout/GridRow') {
      GridRowBootcamp({title: route.label})
  }else if (name === 'GridAndColumnLayout/GridCol'){
      GridColBootcamp({title: route.label})
  }else if (name === 'GridAndColumnLayout/ColumnSplit'){
      ColumnSplitBootcamp({title: route.label})
  }else if (name === 'GridAndColumnLayout/RowSplit'){
      RowSplitBootcamp({title: route.label})
  }else if (name === 'GridAndColumnLayout/FoldSplitContainer'){
      FoldSplitContainerBootcamp({title: route.label})
  }else if (name === 'GridAndColumnLayout/SideBarContainer'){
      SideBarContainerBootcamp({title: route.label})
  }else if (name === 'GridAndColumnLayout/ToolBar'){
    ToolBarBootcamp({title: route.label})
  }

}
