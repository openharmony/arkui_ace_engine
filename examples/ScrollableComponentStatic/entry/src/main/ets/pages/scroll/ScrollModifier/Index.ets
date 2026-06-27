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
  List,
  ListItem,
  Column,
  Button,
  ResourceStr,
  $r,
  BlurStyle,
  BarStyle,
  ListOptions,
  UIContext
} from '@kit.ArkUI';
import router from '@ohos.router';
import { CompletedRoutableCard } from '../../../common/Card';
import resource from '../../../common/resource';

class TestList {
  title: string = ''
  url: string = ''
  key: string = ''
  description?: ResourceStr;
}

export const Scroll_ROUTE_PREFIX: string = 'scroll';

const routes: TestList[] = [
  {
    url: 'pages/scroll/ScrollModifier/List/ListIndex',
    title: resource.resourceToString($r('app.string.Support_ScrollSnapList_Hand_Event')),
    key: 'ListIndex'
  },
  {
    url: 'pages/scroll/ScrollModifier/Grid/GridIndex',
    title: resource.resourceToString($r('app.string.Support_ScrollSnapGrid_Hand_Event')),
    key: 'GridIndex'
  },
  {
    url: 'pages/scroll/ScrollModifier/WaterFlow/WaterFlowIndex',
    title: resource.resourceToString($r('app.string.Support_ScrollSnapWaterFlow_Hand_Event')),
    key: 'WaterFlowIndex'
  },
  {
    url: 'pages/scroll/ScrollModifier/Scroll/ScrollIndex',
    title: resource.resourceToString($r('app.string.Support_ScrollSnapScroll_Hand_Event')),
    key: 'ScrollIndex'
  }
];

@Builder
export function ScrollModifierDestination(): void {
  ScrollModifierExample();
}

@Entry
@Component
export struct ScrollModifierExample {
  @Consume pathStack: NavPathStack;

  build(): void {
    NavDestination() {
      List({ space: 12 } as ListOptions) {
        ForEach(routes, (route: TestList) => {
          ListItem() {
            CompletedRoutableCard({ title: route.title, description: route.description })
          }
          .width('100%')
          .onClick(() => {
            this.getUIContext().getRouter().pushUrl({
              url: route.url,
            }, router.RouterMode.Single);
          }).key(route.key)
        })
      }
      .contentStartOffset(56)
      .padding({ left: 16, right: 16 })
    }
    .backgroundColor('#f1f3f5')
    .title('ScrollModifier', {
      backgroundBlurStyle: BlurStyle.COMPONENT_THICK,
      barStyle: BarStyle.STACK
    })
  }
}
