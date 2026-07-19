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


import { LengthMetrics } from '@kit.ArkUI';
import { RoutableCard } from '../common/Card';
import { Route } from '../common/Route';
import { DeviceDestination, Device_ROUTE_PREFIX } from './device/Index';
import { DragGestureDestination, Drag_ROUTE_PREFIX } from './drag/Index';
import { FocusDestination, Focus_ROUTE_PREFIX } from './focus/Index';
import { GestureJudgeDestination, GestureJudge_ROUTE_PREFIX } from './gesturejudge/Index';
import { GroupGestureDestination, GroupGesture_ROUTE_PREFIX } from './groupgesture/Index';
import { Gesture_ROUTE_PREFIX, GestureDestination } from './singlegesture/Index';
import { TouchDestination, Touch_ROUTE_PREFIX } from './Touch/Index';
import { DropAnimationExample, dropAnimationRoutePrefix} from './drop/DropAnimationExample';
import resource from '../common/resource';
import { GridEts, gridRoutePrefix } from './grid/GridEts';
import { springLoadingRoutePrefix, SpringLoadingPage} from './springloading/SpringLoading';

// [Start route_push]
const routes: Route[] = [
  // $r('app.string.xxx')需要替换为开发者所需的资源文件
  {
    title: resource.resourceToString($r('app.string.Pages_Index_gesture')),
    name: Gesture_ROUTE_PREFIX
  },
  {
    title: resource.resourceToString($r('app.string.Pages_Index_GroupGesture')),
    name: GroupGesture_ROUTE_PREFIX
  },
  {
    title: resource.resourceToString($r('app.string.Pages_Index_GestureJudge')),
    name: GestureJudge_ROUTE_PREFIX
  },
  {
    title: resource.resourceToString($r('app.string.Pages_Index_TouchEvent')),
    name: Touch_ROUTE_PREFIX
  },
  {
    title: resource.resourceToString($r('app.string.Pages_Index_DeviceEvent')),
    name: Device_ROUTE_PREFIX
  },
  {
    title: resource.resourceToString($r('app.string.Pages_Index_FocusEvent')),
    name: Focus_ROUTE_PREFIX
  },
  {
    title: resource.resourceToString($r('app.string.Pages_Index_DragEvent')),
    name: Drag_ROUTE_PREFIX
  },
  {
    title: resource.resourceToString($r('app.string.Pages_Index_DropAnimation')),
    name: dropAnimationRoutePrefix
  },
  {
    title: resource.resourceToString($r('app.string.Pages_Index_GridExample')),
    name: gridRoutePrefix
  },
  {
    title: resource.resourceToString($r('app.string.Pages_Index_SpringLoading')), // 需添加字符串资源
    name: springLoadingRoutePrefix
  }
];
// [End route_push]

@Builder
function Destination(name: string) {
  if (name.startsWith(Gesture_ROUTE_PREFIX)) {
    GestureDestination(name);
  } else if (name.startsWith(GroupGesture_ROUTE_PREFIX)) {
    GroupGestureDestination(name);
  } else if (name.startsWith(GestureJudge_ROUTE_PREFIX)) {
    GestureJudgeDestination(name);
  } else if (name.startsWith(Touch_ROUTE_PREFIX)) {
    TouchDestination(name);
  } else if (name.startsWith(Device_ROUTE_PREFIX)) {
    DeviceDestination(name);
  } else if (name.startsWith(Focus_ROUTE_PREFIX)) {
    FocusDestination(name);
  } else if (name.startsWith(Drag_ROUTE_PREFIX)) {
    DragGestureDestination(name);
  } else if (name.startsWith(dropAnimationRoutePrefix)) {
    DropAnimationExample();
  } else if (name.startsWith(gridRoutePrefix)) {
    GridEts();
  } else if (name.startsWith(springLoadingRoutePrefix)) {
    SpringLoadingPage();
  }
}

@Entry
@Component
struct Index {
  @State condition: string = '';
  @Provide pathStack: NavPathStack = new NavPathStack();

  getFilteredRoutes(): Route[] {
    if (!this.condition) {
      return routes;
    }
    return routes.filter((route: Route) => {
      return route.title.includes(this.condition);
    });
  }

  @LocalBuilder
  Title() {
    Column() {
      Search({ value: this.condition })
        .onChange(value => {
          this.condition = value;
        })
        .margin({ start: LengthMetrics.vp(16), end: LengthMetrics.vp(16) })
    }
    .justifyContent(FlexAlign.Center)
    .height('100%')
  }

  build() {
    Navigation(this.pathStack) {
      List({ space: 12 }) {
        ForEach(this.getFilteredRoutes(), (route: Route) => {
          ListItem() {
            RoutableCard({ title: route.title })
          }
          .width('100%')
          .onClick(() => {
            this.pathStack.pushPath({ name: route.name });
          })
        })
      }
      .padding({ start: LengthMetrics.vp(16), end: LengthMetrics.vp(16) })
      .contentStartOffset(56)
      .height('100%')
      .width('100%')
    }
    .backgroundColor('#f1f3f5')
    .title({ builder: this.Title, height: 56 }, {
      backgroundBlurStyle: BlurStyle.COMPONENT_THICK,
      barStyle: BarStyle.STACK
    })
    .navDestination(Destination)
  }
}