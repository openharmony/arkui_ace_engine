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
import { Route } from '../../common/Route';
import { WaterFlowInfiniteScrolling } from './WaterFlowInfiniteScrolling';
import { WaterFlowInfiniteScrollingEarly } from './WaterFlowInfiniteScrollingEarly';
import { WaterFlowGroupingMixing } from './WaterFlowGroupingMixing';
import { WaterFlowDynamicSwitchover } from './WaterFlowDynamicSwitchover';
import resource from '../../common/resource';
import {
  Builder,
  Entry,
  Component,
  Consume,
  NavDestination,
  List,
  ListOptions,
  ListItem,
  ForEach,
  $r,
  NavPathStack,
  NavPathInfo,
  BlurStyle,
  BarStyle
} from '@kit.ArkUI';

export const WATERFLOW_ROUTE_PREFIX: string = 'waterFlow';

// 直接使用字符串字面量，避免在 const 初始化中使用模板字符串引用 export const
const routes: Route[] = [
  new Route('waterFlow/WaterFlowInfiniteScrolling',
    resource.resourceToString($r('app.string.WaterFlowInfiniteScrolling_title')),
    $r('app.string.WaterFlowInfiniteScrolling_description')),
  new Route('waterFlow/WaterFlowInfiniteScrollingEarly',
    resource.resourceToString($r('app.string.WaterFlowInfiniteScrollingEarly_title')),
    $r('app.string.WaterFlowInfiniteScrollingEarly_description')),
  new Route('waterFlow/WaterFlowGroupingMixing',
    resource.resourceToString($r('app.string.WaterFlowGroupingMixing_title')),
    $r('app.string.WaterFlowGroupingMixing_description')),
  new Route('waterFlow/WaterFlowDynamicSwitchover',
    resource.resourceToString($r('app.string.WaterFlowDynamicSwitchover_title')),
    $r('app.string.WaterFlowDynamicSwitchover_description'))
];

@Builder
export function waterFlowDestination(name: string): void {
  if (name === WATERFLOW_ROUTE_PREFIX) {
    WaterFlowExample();
  } else if (name === routes[0].name) {
    WaterFlowInfiniteScrolling();
  } else if (name === routes[1].name) {
    WaterFlowInfiniteScrollingEarly();
  } else if (name === routes[2].name) {
    WaterFlowGroupingMixing();
  } else if (name === routes[3].name) {
    WaterFlowDynamicSwitchover();
  }
}

@Entry
@Component
struct WaterFlowExample {
  @Consume pathStack: NavPathStack;

  build(): void {
    NavDestination() {
      List({ space: 12 } as ListOptions) {
        ForEach(routes, (route: Route) => {
          ListItem() {
            CompletedRoutableCard({ title: route.title, description: route.description })
          }
          .width('100%')
          .onClick(() => {
            this.pathStack.pushPath(new NavPathInfo(route.name, undefined));
          })
        }, (route: Route, index: int) => index.toString())
      }
      .contentStartOffset(56)
      .padding({ left: 16, right: 16 })
    }
    .backgroundColor('#f1f3f5')
    .title('WaterFlow', {
      backgroundBlurStyle: BlurStyle.COMPONENT_THICK,
      barStyle: BarStyle.STACK
    })
  }
}
