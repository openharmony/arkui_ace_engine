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

import {
  Entry,
  Component,
  Builder,
  Consume,
  ForEach,
  NavDestination,
  NavPathStack,
  NavPathInfo,
  List,
  ListItem,
  Column,
  Row,
  Button,
  Scroll,
  Text,
  ResourceStr,
  ResourceColor,
  $r,
  BlurStyle,
  BarStyle,
  ListOptions
} from '@kit.ArkUI';

import { CompletedRoutableCard } from '../../common/Card';
import { ScrollModifierDestination } from './ScrollModifier/Index';
import { ScrollSnapDestination } from './ScrollSnap/Index';
import { Route } from '../../common/Route';
import resource from '../../common/resource';

export const ScrollSnap_ROUTE_PREFIX: string = 'ScrollSnap';
export const ScrollModifier_ROUTE_PREFIX: string = 'ScrollModifier';
export const Scroll_ROUTE_PREFIX: string = 'scroll';

const routes: Route[] = [
  new Route('scroll/ScrollSnap/Index', resource.resourceToString($r('app.string.Scroll_Title'))),
  new Route('scroll/ScrollModifier/Index', resource.resourceToString($r('app.string.ScrollModifier_Title')))
];

@Builder
export function scrollDestination(name: string): void {
  if (name === Scroll_ROUTE_PREFIX) {
    ScrollExample();
  } else if (name === routes[0].name) {
    ScrollSnapDestination();
  } else if (name.startsWith(routes[1].name)) {
    ScrollModifierDestination();
  }
}

@Entry
@Component
struct ScrollExample {
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
            console.log(route.name + '点击滑动离手事件')
          })
        })
      }
      .contentStartOffset(56)
      .padding({ left: 16, right: 16 })
    }
    .backgroundColor('#f1f3f5')
    .title('Scroll', {
      backgroundBlurStyle: BlurStyle.COMPONENT_THICK,
      barStyle: BarStyle.STACK
    })
  }
}
