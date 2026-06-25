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
import { GridDataSource } from './GridDataSource';
import {
  Entry,
  Component,
  NavDestination,
  Column,
  Grid,
  GridItem,
  LazyForEach,
  Scroller,
  ColumnOptions,
  EdgeEffect,
  EffectEdge,
  $r
} from '@kit.ArkUI';

@Entry
@Component
export struct LongGrid {
  dataSource: GridDataSource = new GridDataSource([]);
  scroller: Scroller = new Scroller();

  aboutToAppear(): void {
    let list: string[] = [];
    for (let i: int = 0; i <= 10; i++) {
      for (let j: int = 0; j < 5; j++) {
        list.push(j.toString());
      }
    }
    this.dataSource = new GridDataSource(list);
  }

  build(): void {
    NavDestination() {
      Column({ space: 12 } as ColumnOptions) {
        // 请将$r('app.string.LongGrid_title')替换为实际资源文件，在本示例中该资源文件的value值为"性能优化"
        ComponentCard({ title: $r('app.string.LongGrid_title') }) {
          Column({ space: 5 } as ColumnOptions) {
            // [Start long_list]
            Grid() {
              LazyForEach(this.dataSource, () => {
                GridItem() {
                }
              })
            }
            .cachedCount(3)
            // [End long_list]
            .columnsTemplate('1fr 1fr 1fr 1fr 1fr')
            .columnsGap(10)
            .rowsGap(20)
            .edgeEffect(EdgeEffect.Spring, { alwaysEnabled: true, effectEdge: EffectEdge.START })
            .width('90%')
            .backgroundColor(0xDCDCDC)
            .height('80%')

          }.width('100%').margin({ top: 5 })
        }
      }
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
    }
    .backgroundColor('#f1f2f3')
    // 请将$r('app.string.LongGrid_title')替换为实际资源文件，在本示例中该资源文件的value值为"性能优化"
    .title($r('app.string.LongGrid_title'))
  }
}
