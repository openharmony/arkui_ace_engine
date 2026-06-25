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

import { ComponentCard } from '../../common/Card';
import {
  Entry,
  Component,
  State,
  NavDestination,
  Column,
  ColumnOptions,
  $r,
  Scroll,
  LazyVGridLayout,
  ForEach,
  Text,
  TextAlign,
  LengthMetrics,
  ScrollDirection
} from '@kit.ArkUI';

@Entry
@Component
export struct LazyVGridLayoutSample {
  @State arr1: Array<int> = new Array<int>();
  @State arr2: Array<int> = new Array<int>();

  aboutToAppear(): void {
    for (let i = 0; i < 9; i++) {
      this.arr1.push(i);
    }
    for (let i = 0; i < 6; i++) {
      this.arr2.push(i);
    }
  }

  build(): void {
    NavDestination() {
      Column({ space: 12 } as ColumnOptions) {
        // 请将$r('app.string.lazyVGridLayout_columns_equal')替换为实际资源文件
        // 在本示例中该资源文件的value值为"设置多列等宽的网格示例"
        ComponentCard({ title: $r('app.string.lazyVGridLayout_columns_equal') }) {
          // [Start create_lazy_grid]
          Scroll() {
            // [Start lazy_grid_columns_template]
            LazyVGridLayout() {
              // 子组件
              // [StartExclude create_lazy_grid]
              // [StartExclude lazy_grid_columns_template]
              ForEach(this.arr1, (item: int) => {
                Text()
                  .height(64)
                  .width('100%')
                  .borderRadius(5)
                  .backgroundColor('#ffe0e2e4')
                  .textAlign(TextAlign.Center)
              }, (item: int) => item.toString())
              // [EndExclude lazy_grid_columns_template]
              // [EndExclude create_lazy_grid]
            }
            // [StartExclude create_lazy_grid]
            .columnsTemplate('1fr 1fr 1fr') // 设置为3列，每列等宽
            // [StartExclude lazy_grid_columns_template]
            .rowsGap(LengthMetrics.vp(10))
            .columnsGap(LengthMetrics.vp(10))

            // [EndExclude create_lazy_grid]
          }
          .scrollable(ScrollDirection.Vertical)
          // [End create_lazy_grid]
          .layoutWeight(1)
        }

        // 请将$r('app.string.lazyVGridLayout_columns_unequal')替换为实际资源文件
        // 在本示例中该资源文件的value值为"设置多列不等宽的网格示例"
        ComponentCard({ title: $r('app.string.lazyVGridLayout_columns_unequal') }) {
          Scroll() {
            // [EndExclude lazy_grid_columns_template]
            // [Start lazy_grid_gap]
            LazyVGridLayout() {
              // 子组件
              // [StartExclude lazy_grid_columns_template]
              // [StartExclude lazy_grid_gap]
              ForEach(this.arr2, (item: int) => {
                Text()
                  .height(64)
                  .width('100%')
                  .borderRadius(5)
                  .backgroundColor('#ffe0e2e4')
                  .textAlign(TextAlign.Center)
              }, (item: int) => item.toString())
              // [EndExclude lazy_grid_gap]
              // [EndExclude lazy_grid_columns_template]
            }
            // [StartExclude lazy_grid_gap]
            .columnsTemplate('1fr 2fr') // 设置为2列，第一列占1份，第二列占2份
            // [EndExclude lazy_grid_gap]
            // [End lazy_grid_columns_template]
            .rowsGap(LengthMetrics.vp(10))
            .columnsGap(LengthMetrics.vp(10))

            // [End lazy_grid_gap]
          }
          .scrollable(ScrollDirection.Vertical)
          .layoutWeight(1)
        }
      }
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
    }
    .backgroundColor('#f1f2f3')
    // 请将$r('app.string.lazyVGridLayout_title')替换为实际资源文件
    // 在本示例中该资源文件的value值为"懒加载网格布局/LazyVGridLayout"
    .title($r('app.string.lazyVGridLayout_title'))
  }
}