'use static'

/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { CompletedRoutableCard } from '../../common/Card';
import { DataInGrid } from './DataInGrid';
import { GridLayout } from './GridLayout';
import { Route } from '../../common/Route';
import { ScrollableGrid } from './ScrollableGrid';
import { ScrollPosition } from './ScrollPositionGrid';
import { GridSideToSide } from './GridSideToSide';
import { GridScrollbar } from './GridScrollbar';
import { LongGrid } from './LongGrid';
import { GridCalculator } from './GridCalculator';
import resource from '../../common/resource';
import {
  Entry,
  Component,
  Consume,
  NavDestination,
  List,
  ListItem,
  ForEach,
  Builder,
  NavPathStack,
  NavPathInfo,
  ListOptions,
  BlurStyle,
  BarStyle,
  $r
} from '@kit.ArkUI';

export const GRID_ROUTE_PREFIX: string = 'grid';

const routes: Route[] = [
  new Route(
    'grid/GridLayout',
    // 请将$r('app.string.GridLayout_title')替换为实际资源文件，在本示例中该资源文件的value值为"网格开发布局"
    resource.resourceToString($r('app.string.GridLayout_title')),
    // 请将$r('app.string.GridLayout_description')替换为实际资源文件，在本示例中该资源文件的value值为"示例设置了网格中子组件行列数量占比、行列间距和主轴方向。"
    $r('app.string.GridLayout_description')
  ),
  new Route(
    'grid/DataInGrid',
    // 请将$r('app.string.DataInGrid_title')替换为实际资源文件，在本示例中该资源文件的value值为"网格显示数据"
    resource.resourceToString($r('app.string.DataInGrid_title')),
    // 请将$r('app.string.DataInGrid_description')替换为实际资源文件，在本示例中该资源文件的value值为"示例采用二维布局的方式组织其内部元素，显示通用办公服务网格。"
    $r('app.string.DataInGrid_description')
  ),
  new Route(
    'grid/ScrollableGrid',
    // 请将$r('app.string.ScrollableGrid_title')替换为实际资源文件，在本示例中该资源文件的value值为"可滚动的网格布局"
    resource.resourceToString($r('app.string.ScrollableGrid_title')),
    // 请将$r('app.string.ScrollableGrid_description')替换为实际资源文件，在本示例中该资源文件的value值为"示例通过仅设置行、列数量与占比中的一个实现横向可滚动网格布局。"
    $r('app.string.ScrollableGrid_description')
  ),
  new Route(
    'grid/ScrollPosition',
    // 请将$r('app.string.ScrollPosition_title')替换为实际资源文件，在本示例中该资源文件的value值为"控制滚动位置的网格布局"
    resource.resourceToString($r('app.string.ScrollPosition_title')),
    // 实现滚动网格布局翻页滚动的功能。
    // 请将$r('app.string.ScrollPosition_description')替换为实际资源文件，在本示例中该资源文件的value值为"示例通过添加Scroller对象的scrollPage方法"

    $r('app.string.ScrollPosition_description')
  ),
  new Route(
    'grid/GridSideToSide',
    // 请将$r('app.string.GridSideToSide')替换为实际资源文件，在本示例中该资源文件的value值为"控制滚动位置"
    resource.resourceToString($r('app.string.GridSideToSide_title')),
    // app.string.GridSideToSide_description资源文件中的value值为'与新闻列表的返回顶部场景类似，控制滚动位置功能在网格布局中也很常用，
    // 例如下图所示日历的翻页功能。'
    $r('app.string.GridSideToSide_description')
  ),
  new Route(
    'grid/GridScrollbar',
    // 请将$r('app.string.GridScrollbar')替换为实际资源文件，在本示例中该资源文件的value值为"添加外置滚动条"
    resource.resourceToString($r('app.string.GridScrollbar_title')),
    // 请将$r('app.string.GridScrollbar')替换为实际资源文件，在本示例中该资源文件的value值为"网格组件Grid可与ScrollBar组件配合使用，为网格添加外置滚动条。"
    $r('app.string.GridScrollbar_description')
  ),
  new Route(
    'grid/LongGrid',
    // 请将$r('app.string.LongGrid')替换为实际资源文件，在本示例中该资源文件的value值为"性能优化"
    resource.resourceToString($r('app.string.LongGrid_title')),
    // app.string.LongGrid_description资源文件中的value值为'与长列表的处理类似，循环渲染适用于数据量较小的布局场景，
    // 当构建具有大量网格项的可滚动网格布局时，推荐使用数据懒加载方式实现按需迭代加载数据，从而提升列表性能。'
    $r('app.string.LongGrid_description')
  ),
  new Route(
    'grid/GridCalculator',
    // 请将$r('app.string.GridCalculator')替换为实际资源文件，在本示例中该资源文件的value值为"计算器的按键布局"
    resource.resourceToString($r('app.string.GridCalculator_title')),
    // 请将$r('app.string.GridCalculator')替换为实际资源文件，在本示例中该资源文件的value值为"实现不同大小的网格组成不均匀分布的网格布局场景"
    $r('app.string.GridCalculator_description')
  )
];

@Builder
export function gridDestination(name: string): void {
  if (name === GRID_ROUTE_PREFIX) {
    GridExample();
  } else if (name === routes[0].name) {
    GridLayout();
  } else if (name === routes[1].name) {
    DataInGrid();
  } else if (name === routes[2].name) {
    ScrollableGrid();
  } else if (name === routes[3].name) {
    ScrollPosition();
  } else if (name === routes[4].name) {
    GridSideToSide();
  } else if (name === routes[5].name) {
    GridScrollbar();
  } else if (name === routes[6].name) {
    LongGrid();
  } else if (name === routes[7].name) {
    GridCalculator();
  }
}

@Entry
@Component
export struct GridExample {
  @Consume
  pathStack: NavPathStack;

  build(): void {
    NavDestination() {
      List({ space: 12 } as ListOptions) {
        ForEach(routes, (route: Route, index: int) => {
          ListItem() {
            CompletedRoutableCard({ title: route.title, description: route.description })
          }
          .width('100%')
          .onClick(() => {
            this.pathStack.pushPath(new NavPathInfo(route.name, undefined));
          })
        }, (route: Route, index: int): string => index.toString())
      }
      .contentStartOffset(56)
      .padding({ left: 16, right: 16 })
    }
    .backgroundColor('#f1f3f5')
    .title('Grid', {
      backgroundBlurStyle: BlurStyle.COMPONENT_THICK,
      barStyle: BarStyle.STACK
    })
  }
}
