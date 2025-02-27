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
import { ListBootcamp } from './ListBootcamp';
import { GridBootcamp } from './GridBootcamp';
import { FlexBootcamp } from './FlexBootcamp';
import { ColumnBootcamp } from './ColumnBootcamp';
import { GridColBootcamp } from './GridColBootcamp';
import { FolderStackBootcamp } from './FolderStackBootcamp';
import { StackBootcamp } from './StackBootcamp';
import { RelativeContainerBootcamp } from './RelativeContainerBootcamp';
import { RowBootcamp } from './RowBootcamp';
import { ScrollBootcamp } from './ScrollBootcamp';
import { WaterFlowBootcamp } from './WaterFlowBootcamp';
import { SideBarContainerBootcamp } from './SideBarContainerBootcamp';
import { FlowItemBootcamp } from './FlowItemBootcamp';
import { SwiperBootcamp } from './SwiperBootcamp';
import { RefreshBootcamp } from './RefreshBootcamp';
import { ListItemBootcamp } from './ListItemBootcamp';
import { GridRowBootcamp } from './GridRowBootcamp';
import { ColumnSplitBootcamp } from './ColumnSplitBootcamp';
import { GridItemBootcamp } from './GridItemBootcamp';
import { RowSplitBootcamp } from './RowSplitBootcamp';
import { FoldSplitContainerBootcamp } from './FoldSplitContainerBootcamp';

export const containersRoute: RouteGroup = {
  name: 'containers',
  label: '容器类',
  children: [
    { name: 'text-picker-dialog', label: '文本选择器弹窗/TextpickerDialog' },
    { name: 'time-picker-dialog', label: '时间选择器弹窗/TimepickerDialog' },
    { name: 'date-picker-dialog', label: '日期选择器弹窗/DatepickerDialog' },
    { name: 'calendar-picker-dialog', label: '日历选择器弹窗/CalendarPickerDialog' },
    { name: 'list-item', label: '列表选项/ListItem'},
    { name: 'list-item-group', label: '分组列表/ListItemGroup' },
    { name: 'list', label: '列表/List' },
    { name: 'grid', label: '网格/Grid' },
    { name: 'flex', label: '弹性布局/Flex' },
    { name: 'column', label: '纵向布局/Column' },
    { name: 'grid-col', label: '栅格列/GridCol' },
    { name: 'stack', label: '层叠布局/Stack' },
    { name: 'relative-container', label: '相对布局/RelativeContainer' },
    { name: 'row', label: '横向布局/Row' },
    { name: 'scroll', label: '滚动容器/Scroll' },
    { name: 'waterFlow', label: '瀑布流容器/WaterFlow' },
    {name:'side-bar-container',label:'侧边栏/SideBarContainer'}
    { name: 'swiper', label: '轮播容器/Swiper' },
    { name: 'refresh', label: '刷新容器/Refresh' },
    { name: 'gridRow', label: '栅格容器/GridRow' }
    { name: 'gridRow', label: '栅格容器/GridRow' },
    { name: 'gridItem', label: '网格选项/GridItem' }
    { name: 'folder-stack', label: '折叠布局/FolderStack' },
    { name:'columnSplit', label:'纵向分割容器/ColumnSplit' },
    { name: 'flowItem', label: '瀑布流选项/FlowItem' },
    { name: 'gridRow', label: '栅格容器/GridRow' },
    { name: 'swiper', label: '轮播容器/Swiper' },
    { name: 'refresh', label: '刷新容器/Refresh' },
    { name: 'gridItem', label: '网格选项/GridItem' },
    { name: 'folder-stack', label: '折叠布局/FolderStack' },
    { name: 'rowSplit', label: '横向分割容器/RowSplit' },
    { name: 'fold-split-container', label: '折叠屏分栏组件/FoldSplitContainer' },
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
  } else if (name === 'containers/list') {
    ListBootcamp({ title: route.label })
  } else if (name === 'containers/list-item') {
    ListItemBootcamp({ title: route.label })
  } else if (name === 'containers/grid') {
    GridBootcamp({ title: route.label })
  } else if (name === 'containers/flex') {
    FlexBootcamp({ title: route.label })
  } else if (name === 'containers/column') {
    ColumnBootcamp({ title: route.label })
  } else if (name === 'containers/grid-col') {
    GridColBootcamp({ title: route.label })
  } else if (name === 'containers/stack') {
    StackBootcamp({ title: route.label })
  } else if (name === 'containers/relative-container') {
    RelativeContainerBootcamp({ title: route.label })
  } else if (name === 'containers/row') {
    RowBootcamp({ title: route.label })
  } else if (name === 'containers/scroll') {
    ScrollBootcamp({ title: route.label })
  } else if (name === 'containers/waterFlow') {
    WaterFlowBootcamp({ title: route.label })
  }else if (name==='containers/side-bar-container'){
    SideBarContainerBootcamp({title: route.label})
  } else if (name === 'containers/flowItem') {
    FlowItemBootcamp({ title: route.label })
  } else if (name === 'containers/swiper') {
    SwiperBootcamp({ title: route.label })
  } else if (name === 'containers/refresh') {
    RefreshBootcamp({ title: route.label })
  } else if (name === 'containers/gridRow') {
    GridRowBootcamp({ title: route.label })
  } else if (name === 'containers/gridItem') {
    GridItemBootcamp({ title: route.label })
  } else if (name === 'containers/folder-stack') {
    FolderStackBootcamp({ title: route.label })
  }else if(name === 'containers/columnSplit') {
    ColumnSplitBootcamp({title: route.label})
  } else if (name === 'containers/rowSplit') {
    RowSplitBootcamp({ title: route.label })
  } else if (name === 'containers/fold-split-container') {
    FoldSplitContainerBootcamp({ title: route.label })
  }
}
