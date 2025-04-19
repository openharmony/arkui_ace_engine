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
import { ColumnBootcamp } from './ColumnBootcamp';
import { FlexBootcamp } from './FlexBootcamp';
import { FolderStackBootcamp } from './FolderStackBootcamp';
import { RelativeContainerBootcamp } from './RelativeContainerBootcamp';
import { RowBootcamp } from './RowBootcamp';
import { StackBootcamp } from './StackBootcamp';


export const rowsColumnsAndStackingRoute: RouteGroup = {
  name: 'RowsColumnsAndStacking',
  label: '行列与堆叠',
  children: [
    { name: 'Column', label: '纵向布局/Column' },
    { name: 'Flex', label: '弹性布局/Flex' },
    { name: 'Row', label: '横向布局/Row' },
    { name: 'Stack', label: '层叠布局/Stack' },
    { name: 'RelativeContainer', label: '相对布局/RelativeContainer' },
    { name: 'FolderStack', label: '折叠布局/FolderStack' }
  ]
};

@Builder
export function rowsColumnsAndStackingDestination(name: string, route: Route) {
  if (name === 'RowsColumnsAndStacking/Column') {
    ColumnBootcamp({ title: route.label })
  } else if (name === 'RowsColumnsAndStacking/Flex') {
    FlexBootcamp({ title: route.label })
  } else if (name === 'RowsColumnsAndStacking/Row') {
    RowBootcamp({ title: route.label })
  } else if (name === 'RowsColumnsAndStacking/Stack') {
    StackBootcamp({ title: route.label })
  } else if (name === 'RowsColumnsAndStacking/RelativeContainer') {
    RelativeContainerBootcamp({ title: route.label })
  } else if (name === 'RowsColumnsAndStacking/FolderStack') {
    FolderStackBootcamp({ title: route.label })
  }

}
