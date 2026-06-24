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

import { GridDataSource } from './GridDataSource';
import { ComponentCard } from '../../common/Card';
import {
  Entry,
  Component,
  State,
  NavDestination,
  Column,
  Row,
  Grid,
  GridItem,
  Text,
  Scroller,
  ScrollBar,
  LazyForEach,
  ColumnOptions,
  RowOptions,
  TextAlign,
  EdgeEffect,
  EffectEdge,
  BarState,
  Color,
  $r
} from '@kit.ArkUI';

@Entry
@Component
export struct GridScrollbar {
  numbers: GridDataSource = new GridDataSource([]);
  // [Start Add_external_scrollbar_gridScroller]
  private gridScroller: Scroller = new Scroller();
  // [End Add_external_scrollbar_gridScroller]

  @State
  gridPosition: int = 0; // 0代表滚动到grid顶部，1代表中间值，2代表滚动到grid底部。

  aboutToAppear(): void {
    let list: string[] = [];
    for (let i: int = 0; i < 5; i++) {
      for (let j: int = 0; j < 5; j++) {
        list.push(j.toString());
      }
    }
    this.numbers = new GridDataSource(list);
  }
  build(): void {
    NavDestination() {
      Column({ space: 12 } as ColumnOptions) {
        // 请将$r('app.string.GridScrollbar_title')替换为实际资源文件，在本示例中该资源文件的value值为"添加外置滚动条"
        ComponentCard({ title: $r('app.string.GridScrollbar_title') }) {
          Row({ space: 5 } as RowOptions) {
            // [Start Add_external_scrollbar1]
            // gridScroller初始化Grid组件的scroller参数，绑定gridScroller与网格。
            Grid(this.gridScroller) {
              // [StartExclude Add_external_scrollbar1]
              LazyForEach(this.numbers, (day: string) => {
                GridItem() {
                  Text()
                    .fontSize(16)
                    .backgroundColor(0xF9CF93)
                    .width('100%')
                    .height(80)
                    .textAlign(TextAlign.Center)
                }
              }, (item: string, index: int) => index.toString())
              // [EndExclude Add_external_scrollbar1]
            }
            // [End Add_external_scrollbar1]
            .columnsTemplate('1fr 1fr 1fr 1fr 1fr')
            .columnsGap(10)
            .rowsGap(10)
            .friction(0.6)
            .enableScrollInteraction(true)
            .supportAnimation(false)
            .multiSelectable(false)
            .edgeEffect(EdgeEffect.Spring, { alwaysEnabled: true, effectEdge: EffectEdge.START })
            .scrollBar(BarState.Off)
            .scrollBarColor(Color.Grey)
            .scrollBarWidth(4)
            .width('90%')
            .backgroundColor(0xFAEEE0)
            .height(300)
            .margin({left:10})
            // [Start Add_external_scrollbar2]
            // gridScroller初始化ScrollBar组件的scroller参数，绑定gridScroller与滚动条。
            ScrollBar({ scroller: this.gridScroller })
            // [End Add_external_scrollbar2]
              .height(300)
          }.width('100%').margin({ top: 5 })
        }
      }
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
    }
    .backgroundColor('#f1f2f3')
    // 请将$r('app.string.GridScrollbar_title')替换为实际资源文件，在本示例中该资源文件的value值为"添加外置滚动条"
    .title($r('app.string.GridScrollbar_title'))
  }
}
