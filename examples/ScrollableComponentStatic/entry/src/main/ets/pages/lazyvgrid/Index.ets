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
  Builder,
  Entry,
  Component,
  Consume,
  NavPathStack,
  NavDestination,
  List,
  ForEach,
  ListItem,
  ResourceStr,
  NavPathInfo,
  ListOptions,
  $r,
  BlurStyle,
  BarStyle
} from '@kit.ArkUI';
import { CompletedRoutableCard } from '../../common/Card';
import { Route } from '../../common/Route';
import resource from '../../common/resource';
import { LazyVGridLayoutSample } from './LazyVGridLayoutSample';
import { LazyVWaterFlowLayoutSample } from './LazyVWaterFlowLayoutSample';
import { LazyColumnLayoutSample } from './LazyColumnLayoutSample';
import { ListNestedLazyLayout } from './ListNestedLazyLayout';
import { LazyColumnLayoutNestedLazyLayout } from './LazyColumnLayoutNestedLazyLayout';

export const LAZY_LAYOUT_ROUTE_PREFIX: string = 'lazyLayout';

const routes: Route[] = [
  new Route(
    'lazyLayout/LazyVGridLayoutSample',
    // 请将$r('app.string.LazyVGridLayout_title')替换为实际资源文件，在本示例中该资源文件的value值为"懒加载网格布局/LazyVGridLayout"
    resource.resourceToString($r('app.string.lazyVGridLayout_title')),
    // 请将$r('app.string.LazyVGridLayout_description')替换为实际资源文件，在本示例中该资源文件的value值为"示例设置了网格中子组件列数占比和行列间距。"
    $r('app.string.lazyVGridLayout_description')
  ),
  new Route(
    'lazyLayout/LazyVWaterFlowLayoutSample',
    // 请将$r('app.string.LazyVWaterFlowLayout_title')替换为实际资源文件，在本示例中该资源文件的value值为"懒加载瀑布流布局/LazyVWaterFlowLayout"
    resource.resourceToString($r('app.string.lazyVWaterFlowLayout_title')),
    // 请将$r('app.string.LazyVWaterFlowLayout_description')替换为实际资源文件，在本示例中该资源文件的value值为"示例设置了瀑布流中子组件列数占比和行列间距。"
    $r('app.string.lazyVWaterFlowLayout_description')
  ),
  new Route(
    'lazyLayout/LazyColumnLayoutSample',
    // 请将$r('app.string.LazyColumnLayout_title')替换为实际资源文件，在本示例中该资源文件的value值为"懒加载线性布局/LazyColumnLayout"
    resource.resourceToString($r('app.string.lazyColumnLayout_title')),
    // 请将$r('app.string.LazyColumnLayout_description')替换为实际资源文件，在本示例中该资源文件的value值为"示例设置了行间距和水平对齐方式。"
    $r('app.string.lazyColumnLayout_description')
  ),
  new Route(
    'lazyLayout/ListNestedLazyLayout',
    // 请将$r('app.string.list_nested_lazyLayout_title')替换为实际资源文件，在本示例中该资源文件的value值为"List嵌套懒加载布局容器"
    resource.resourceToString($r('app.string.list_nested_lazyLayout_title')),
    // 请将$r('app.string.list_nested_lazyLayout_description')替换为实际资源文件
    // 在本示例中该资源文件的value值为"在List组件中嵌套多个不同的懒加载布局容器，分别为每个容器内容配置独立的列数和行列间距，实现多种布局方式的混合展示。"
    $r('app.string.list_nested_lazyLayout_description')
  ),
  new Route(
    'lazyLayout/LazyColumnLayoutNestedLazyLayout',
    // 请将$r('app.string.lazyColumnLayout_nested_lazyLayout_title')替换为实际资源文件，在本示例中该资源文件的value值为"LazyColumnLayout嵌套懒加载布局容器"
    resource.resourceToString($r('app.string.lazyColumnLayout_nested_lazyLayout_title')),
    // 请将$r('app.string.lazyColumnLayout_nested_lazyLayout_description')替换为实际资源文件
    // 在本示例中该资源文件的value值为"在Scroll组件中使用LazyColumnLayout作为主布局容器，其内部嵌套多个不同的懒加载布局容器，实现多种布局方式的混合展示。"
    $r('app.string.lazyColumnLayout_nested_lazyLayout_description')
  )
];

@Builder
export function lazyLayoutDestination(name: string): void {
  if (name === 'lazyLayout') {
    LazyLayoutExample();
  } else if (name === routes[0].name) {
    LazyVGridLayoutSample();
  } else if (name === routes[1].name) {
    LazyVWaterFlowLayoutSample();
  } else if (name === routes[2].name) {
    LazyColumnLayoutSample();
  } else if (name === routes[3].name) {
    ListNestedLazyLayout();
  } else if (name === routes[4].name) {
    LazyColumnLayoutNestedLazyLayout();
  }
}

@Entry
@Component
struct LazyLayoutExample {
  @Consume pathStack: NavPathStack;

  build(): void {
    NavDestination() {
      List({ space: 12 } as ListOptions) {
        ForEach(routes, (route: Route) => {
          ListItem() {
            CompletedRoutableCard({ title: route.title, description: route.description as ResourceStr })
          }
          .width('100%')
          .onClick(() => {
            this.pathStack.pushPath(new NavPathInfo(route.name, undefined));
          })
        })
      }
      .contentStartOffset(56)
      .padding({ left: 16, right: 16 })
    }
    .backgroundColor('#f1f3f5')
    // 请将$r('app.string.lazyLayout_Title')替换为实际资源文件
    // 在本示例中该资源文件的value值为"懒加载布局"
    .title($r('app.string.lazyLayout_Title'), {
      backgroundBlurStyle: BlurStyle.COMPONENT_THICK,
      barStyle: BarStyle.STACK
    })
  }
}