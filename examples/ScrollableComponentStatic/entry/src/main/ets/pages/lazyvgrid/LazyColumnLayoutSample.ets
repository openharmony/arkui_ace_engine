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
  LazyColumnLayout,
  ForEach,
  Text,
  TextAlign,
  LengthMetrics,
  HorizontalAlign,
  ScrollDirection
} from '@kit.ArkUI';

@Entry
@Component
export struct LazyColumnLayoutSample {
  @State numbers: Array<int> = new Array<int>();

  aboutToAppear(): void {
    for (let i = 0; i < 3; i++) {
      this.numbers.push(i);
    }
  }

  build(): void {
    NavDestination() {
      Column({ space: 12 } as ColumnOptions) {
        // 请将$r('app.string.lazyColumnLayout_space_alignItemsStart')替换为实际资源文件
        // 在本示例中该资源文件的value值为"设置行间距和水平起始位置对齐方式示例"
        ComponentCard({ title: $r('app.string.lazyColumnLayout_space_alignItemsStart') }) {
          // [Start create_lazy_column]
          Scroll() {
            // [Start lazy_column_align_items]
            LazyColumnLayout() {
              // 子组件
              // [StartExclude create_lazy_column]
              // [StartExclude lazy_column_align_items]
              ForEach(this.numbers, (item: int) => {
                Text()
                  .height(64)
                  .width('50%')
                  .borderRadius(5)
                  .backgroundColor('#ffe0e2e4')
                  .textAlign(TextAlign.Center)
              }, (item: int) => item.toString())
              // [EndExclude lazy_column_align_items]
              // [EndExclude create_lazy_column]
            }
            // [StartExclude create_lazy_column]
            // [StartExclude lazy_column_align_items]
            .space(LengthMetrics.vp(10))
            // [EndExclude lazy_column_align_items]
            .alignItems(HorizontalAlign.Start)
            // [End lazy_column_align_items]
            // [EndExclude create_lazy_column]
          }
          .scrollable(ScrollDirection.Vertical)
          // [End create_lazy_column]
          .layoutWeight(1)
        }

        // 请将$r('app.string.lazyColumnLayout_space_alignItemsCenter')替换为实际资源文件
        // 在本示例中该资源文件的value值为"设置行间距和水平居中对齐方式示例"
        ComponentCard({ title: $r('app.string.lazyColumnLayout_space_alignItemsCenter') }) {
          Scroll() {
            // [Start lazy_column_space]
            LazyColumnLayout() {
              // 子组件
              // [StartExclude lazy_column_space]
              ForEach(this.numbers, (item: int) => {
                Text()
                  .height(64)
                  .width('50%')
                  .borderRadius(5)
                  .backgroundColor('#ffe0e2e4')
                  .textAlign(TextAlign.Center)
              }, (item: int) => item.toString())
              // [EndExclude lazy_column_space]
            }
            .space(LengthMetrics.vp(10))
            // [End lazy_column_space]
            .alignItems(HorizontalAlign.Center)
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
    // 请将$r('app.string.lazyColumnLayout_title')替换为实际资源文件
    // 在本示例中该资源文件的value值为"懒加载线性布局/LazyColumnLayout"
    .title($r('app.string.lazyColumnLayout_title'))
  }
}