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
  List,
  ListOptions,
  ListItem,
  NavDestination,
  Entry,
  Component,
  Builder,
  ForEach,
  Consume,
  NavPathStack,
  BlurStyle,
  BarStyle,
  NavPathInfo,
  ResourceStr,
  $r
} from '@kit.ArkUI';
import { CompletedRoutableCard } from '../../common/Card';
import { Route } from '../../common/Route';
import { ArcListAcrScrollBar } from './ArcListAcrScrollBar';
import { ArcListArcIndexerBar } from './ArcListArcIndexerBar';
import { arcListBuiltInScrollerBar } from './arcListBuiltInScrollerBar';
import { ArcListContents } from './ArcListContents';
import { ArcListCrown } from './ArcListCrown';
import { ArcListShow } from './ArcListShow';
import { ArcListSideSlip } from './ArcListSideSlip';
import { ArcListStyles } from './ArcListStyles';
import { ArcLongList } from './ArcLongList';
import { ArcListCreate } from './ArcListCreate';

import resource from '../../common/resource';

export const ARCLIST_ROUTE_PREFIX: string = 'arcList';

const routes: Route[] = [
  new Route('arcList/ArcListShow', resource.resourceToString($r('app.string.ArcListShow_title')), $r('app.string.ArcListShow_description')),
  new Route('arcList/ArcListContents', resource.resourceToString($r('app.string.ArcListContents_title')), $r('app.string.ArcListContents_description')),
  new Route('arcList/ArcListStyles', resource.resourceToString($r('app.string.ArcListStyles_title')), $r('app.string.ArcListStyles_description')),
  new Route('arcList/arcListBuiltInScrollerBar', resource.resourceToString($r('app.string.arcListBuiltInScrollerBar_title')), $r('app.string.arcListBuiltInScrollerBar_description')),
  new Route('arcList/ArcListAcrScrollBar', resource.resourceToString($r('app.string.ArcListAcrScrollBar_title')), $r('app.string.ArcListAcrScrollBar_description')),
  new Route('arcList/ArcListArcIndexerBar', resource.resourceToString($r('app.string.ArcListArcIndexerBar_title')), $r('app.string.ArcListArcIndexerBar_description')),
  new Route('arcList/ArcListSideSlip', resource.resourceToString($r('app.string.ArcListSideSlip_title')), $r('app.string.ArcListSideSlip_description')),
  new Route('arcList/ArcLongList', resource.resourceToString($r('app.string.ArcLongList_title')), $r('app.string.ArcLongList_description')),
  new Route('arcList/ArcListCrown', resource.resourceToString($r('app.string.ArcListCrown_title')), $r('app.string.ArcListCrown_description')),
  new Route('arcList/ArcListCreate', resource.resourceToString($r('app.string.ArcListCreate_title')), $r('app.string.ArcListCreate_description'))
];

@Builder
export function arcListDestination(name: string): void {
  if (name === ARCLIST_ROUTE_PREFIX) {
    ArcListExample();
  } else if (name === routes[0].name) {
    ArcListShow();
  } else if (name === routes[1].name) {
    ArcListContents();
  } else if (name === routes[2].name) {
    ArcListStyles();
  } else if (name === routes[3].name) {
    arcListBuiltInScrollerBar();
  } else if (name === routes[4].name) {
    ArcListAcrScrollBar();
  } else if (name === routes[5].name) {
    ArcListArcIndexerBar();
  } else if (name === routes[6].name) {
    ArcListSideSlip();
  } else if (name === routes[7].name) {
    ArcLongList();
  } else if (name === routes[8].name) {
    ArcListCrown();
  } else if (name === routes[9].name) {
    ArcListCreate();
  }
}

@Entry
@Component
struct ArcListExample {
  @Consume
  pathStack: NavPathStack;

  build(): void {
    NavDestination() {
      List({ space: 12 } as ListOptions) {
        ForEach(routes, (route: Route) => {
          ListItem() {
            CompletedRoutableCard({ title: route.title, description: route.description })
          }
          .width('100%')
          .onClick((): void => {
            this.pathStack.pushPath(new NavPathInfo(route.name, undefined));
          })
        })
      }
      .contentStartOffset(56)
      .padding({ left: 16, right: 16 })
    }
    .backgroundColor('#f1f3f5')
    .title('ArcList', {
      backgroundBlurStyle: BlurStyle.COMPONENT_THICK,
      barStyle: BarStyle.STACK
    })
  }
}
