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
  LazyVWaterFlowLayout,
  ForEach,
  Text,
  TextAlign,
  LengthMetrics,
  ScrollDirection
} from '@kit.ArkUI';

@Entry
@Component
export struct LazyVWaterFlowLayoutSample {
  @State arr1: Array<int> = new Array<int>();
  @State arr2: Array<int> = new Array<int>();

  private itemHeight(index: int): int {
    return 80 + (index * 37 % 60)
  }

  private itemColor(index: int): string {
    const colors: string[] = ['#FFE0B2', '#C8E6C9', '#BBDEFB', '#F8BBD0', '#D1C4E9', '#FFF9C4']
    return colors[index % colors.length]
  }

  aboutToAppear(): void {
    for (let i = 0; i < 6; i++) {
      this.arr1.push(i);
    }
    for (let i = 0; i < 5; i++) {
      this.arr2.push(i);
    }
  }

  build(): void {
    NavDestination() {
      Column({ space: 12 } as ColumnOptions) {
        // 请将$r('app.string.lazyVWaterFlowLayout_columns_equal')替换为实际资源文件
        // 在本示例中该资源文件的value值为"设置多列等宽的瀑布流示例"
        ComponentCard({ title: $r('app.string.lazyVWaterFlowLayout_columns_equal') }) {
          // [Start create_lazy_water_flow]
          Scroll() {
            // [Start lazy_water_flow_columns_template]
            LazyVWaterFlowLayout() {
              // 子组件
              // [StartExclude create_lazy_water_flow]
              // [StartExclude lazy_water_flow_columns_template]
              ForEach(this.arr1, (item: int) => {
                Text()
                  .height(this.itemHeight(item))
                  .width('100%')
                  .borderRadius(5)
                  .backgroundColor(this.itemColor(item))
                  .textAlign(TextAlign.Center)
              }, (item: int) => item.toString())
              // [EndExclude lazy_water_flow_columns_template]
              // [EndExclude create_lazy_water_flow]
            }
            // [StartExclude create_lazy_water_flow]
            .columnsTemplate('1fr 1fr 1fr') // 设置为3列，每列等宽
            // [StartExclude lazy_water_flow_columns_template]
            .rowsGap(LengthMetrics.vp(10))
            .columnsGap(LengthMetrics.vp(10))
            // [EndExclude create_lazy_water_flow]
          }
          .scrollable(ScrollDirection.Vertical)
          // [End create_lazy_water_flow]
          .layoutWeight(1)
        }

        // 请将$r('app.string.lazyVWaterFlowLayout_columns_unequal')替换为实际资源文件
        // 在本示例中该资源文件的value值为"设置多列不等宽的瀑布流示例"
        ComponentCard({ title: $r('app.string.lazyVWaterFlowLayout_columns_unequal') }) {
          Scroll() {
            // [EndExclude lazy_water_flow_columns_template]
            // [Start lazy_water_flow_gap]
            LazyVWaterFlowLayout() {
              // 子组件
              // [StartExclude lazy_water_flow_columns_template]
              // [StartExclude lazy_water_flow_gap]
              ForEach(this.arr2, (item: int) => {
                Text()
                  .height(this.itemHeight(item))
                  .width('100%')
                  .borderRadius(5)
                  .backgroundColor(this.itemColor(item))
                  .textAlign(TextAlign.Center)
              }, (item: int) => item.toString())
              // [EndExclude lazy_water_flow_gap]
              // [EndExclude lazy_water_flow_columns_template]
            }
            // [StartExclude lazy_water_flow_gap]
            .columnsTemplate('1fr 2fr') // 设置为2列，第一列占1份，第二列占2份
            // [EndExclude lazy_water_flow_gap]
            // [End lazy_water_flow_columns_template]
            .rowsGap(LengthMetrics.vp(10))
            .columnsGap(LengthMetrics.vp(10))
            // [End lazy_water_flow_gap]
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
    // 请将$r('app.string.lazyVWaterFlowLayout_title')替换为实际资源文件
    // 在本示例中该资源文件的value值为"懒加载瀑布流布局/LazyVWaterFlowLayout"
    .title($r('app.string.lazyVWaterFlowLayout_title'))
  }
}