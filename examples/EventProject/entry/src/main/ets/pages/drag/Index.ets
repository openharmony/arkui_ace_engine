/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
import { DefaultDrag } from './DefaultDrag';
import { MoreDrag } from './MoreDrag';
import resource from '../../common/resource';

export const Drag_ROUTE_PREFIX: string = 'Drag_ROUTE_PREFIX';

// $r('app.string.xxx')需要替换为开发者所需的资源文件
const routes: Route[] = [
  {
    name: `${Drag_ROUTE_PREFIX}/Defaultdrag`,
    title: resource.resourceToString($r('app.string.Drag_Index_DefaultDrag_title')),
    description: resource.resourceToString($r('app.string.Drag_Index_DefaultDrag_description')),
  },
  {
    name: `${Drag_ROUTE_PREFIX}/MoreDrag`,
    title: resource.resourceToString($r('app.string.Drag_Index_MoreDrag_title')),
    description: resource.resourceToString($r('app.string.Drag_Index_MoreDrag_description')),
  }
];

@Builder
export function DragGestureDestination(name: string) {
  if (name === Drag_ROUTE_PREFIX) {
    DragGestureExample();
  } else if (name === routes[0].name) {
    DefaultDrag();
  } else if (name === routes[1].name) {
    MoreDrag();
  }
}

@Entry
@Component
struct DragGestureExample {
  @Consume pathStack: NavPathStack;

  build() {
    NavDestination() {
      List({ space: 12 }) {
        ForEach(routes, (route: Route) => {
          ListItem() {
            CompletedRoutableCard({ title: route.title, description: route.description })
          }
          .width('100%')
          .onClick(() => {
            this.pathStack.pushPath({ name: route.name });
          })
        })
      }
      .contentStartOffset(20)
      .padding({ left: 16, right: 16 })
    }
    .backgroundColor('#f1f3f5')
    .title('', {
      backgroundBlurStyle: BlurStyle.COMPONENT_THICK,
      barStyle: BarStyle.STACK
    })
    // 请将$r('app.string.Drag_Index_DefaultDrag_title')替换为实际资源文件，在本示例中该资源文件的value值为"拖拽事件"
    .title($r('app.string.Drag_Index_title'))
  }
}