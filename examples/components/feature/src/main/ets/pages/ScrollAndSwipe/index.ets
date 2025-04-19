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
import { FlowItemBootcamp } from './FlowItemBootcamp';
import { GridBootcamp } from './GridBootcamp';
import { GridItemBootcamp } from './GridItemBootcamp';
import { ListBootcamp } from './ListBootcamp';
import { ListItemBootcamp } from './ListItemBootcamp';
import { ListItemGroupBootcamp } from './ListItemGroupBootcamp';
import { RefreshBootcamp } from './RefreshBootcamp';
import { ScrollBarBootcamp } from './ScrollBarBootcamp';
import { ScrollBootcamp } from './ScrollBootcamp';
import { SwiperBootcamp } from './SwiperBootcamp';
import { WaterFlowBootcamp } from './WaterFlowBootcamp';


export const scrollAndSwipeRoute: RouteGroup = {
  name: 'ScrollAndSwipe',
  label: '滚动与滑动',
  children: [
    { name: 'List', label: '列表/List' },
    { name: 'ListItem', label: '列表选项/ListItem' },
    { name: 'ListItemGroup', label: '分组列表/ListItemGroup' },
    { name: 'Grid', label: '网格/Grid' },
    { name: 'GridItem', label: '网格选项/GridItem' },
    { name: 'Scroll', label: '滚动容器/Scroll' },
    { name: 'Swiper', label: '轮播容器/Swiper' },
    { name: 'WaterFlow', label: '瀑布流容器/WaterFlow' },
    { name: 'FlowItem', label: '瀑布流选项/FlowItem' },
    { name: 'Scrollbar', label: '滚动条/Scrollbar' },
    { name: 'Refresh', label: '刷新容器/Refresh' }

  ]
};

@Builder
export function scrollAndSwipeDestination(name: string, route: Route) {
  if (name === 'ScrollAndSwipe/List') {
    ListBootcamp({title: route.label})
  }else if (name === 'ScrollAndSwipe/ListItem'){
    ListItemBootcamp({title: route.label})
  }else if (name === 'ScrollAndSwipe/ListItemGroup'){
    ListItemGroupBootcamp({title: route.label})
  }else if (name === 'ScrollAndSwipe/Grid'){
    GridBootcamp({title: route.label})
  }else if (name === 'ScrollAndSwipe/GridItem'){
    GridItemBootcamp({title: route.label})
  }else if (name === 'ScrollAndSwipe/Scroll'){
    ScrollBootcamp({title: route.label})
  }else if (name === 'ScrollAndSwipe/Swiper'){
    SwiperBootcamp({title: route.label})
  }else if (name === 'ScrollAndSwipe/WaterFlow'){
    WaterFlowBootcamp({title: route.label})
  }else  if (name === 'ScrollAndSwipe/FlowItem'){
    FlowItemBootcamp({title: route.label})
  }else if (name === 'ScrollAndSwipe/Scrollbar'){
    ScrollBarBootcamp({title: route.label})
  }else if (name === 'ScrollAndSwipe/Refresh'){
    RefreshBootcamp({title: route.label})
  }

}
