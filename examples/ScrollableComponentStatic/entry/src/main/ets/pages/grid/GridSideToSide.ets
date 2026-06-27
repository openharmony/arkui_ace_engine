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
  Button,
  Scroller,
  LazyForEach,
  ColumnOptions,
  RowOptions,
  BarState,
  TextAlign,
  $r
} from '@kit.ArkUI';

@Entry
@Component
export struct GridSideToSide {
  numbers: GridDataSource = new GridDataSource([]);
  scroller: Scroller = new Scroller();
  @State
  gridPosition: int = 0; // 0代表滚动到grid顶部，1代表中间值，2代表滚动到grid底部。
  @State
  data: int = 1;

  aboutToAppear(): void {
    let list: string[] = [];
    for (let i: int = 0; i < 7; i++) {
      for (let j: int = 0; j < 10; j++) {
        list.push(this.data.toString());
        this.data += 1;
        if(this.data == 32) {
          this.data = 0;
        }
      }
    }
    this.numbers = new GridDataSource(list);
  }

  build(): void {
    NavDestination() {
      Column({ space: 5 } as ColumnOptions) {
        // 请将$r('app.string.GridSideToSide_title')替换为实际资源文件，在本示例中该资源文件的value值为"控制滚动位置"
        ComponentCard({ title: $r('app.string.GridSideToSide_title') }) {
          // [Start Control_scrolling_position]
          Column({ space: 5 } as ColumnOptions){
            Grid(this.scroller) {
              // [StartExclude Control_scrolling_position]
              LazyForEach(this.numbers, (day: string) => {
                GridItem() {
                  Text(day)
                    .fontSize(16)
                    .backgroundColor(0xF9CF93)
                    .width('100%')
                    .height(50)
                    .textAlign(TextAlign.Center)
                }
              }, (item: string, index: int) => index.toString())
              // [EndExclude Control_scrolling_position]
            }
            .columnsTemplate('1fr 1fr 1fr 1fr 1fr 1fr 1fr')
            // [StartExclude Control_scrolling_position]
            .columnsGap(10)
            .rowsGap(10)
            .width('90%')
            .height(300)
            .scrollBar(BarState.Off)
            // [EndExclude Control_scrolling_position]
            Row({ space: 20 } as RowOptions) {
              // 请将$r('app.string.Previous_Page')替换为实际资源文件，在本示例中该资源文件的value值为"上一页"
              Button($r('app.string.Previous_Page'))
                .onClick(() => {
                  this.scroller.scrollPage({
                    next: false
                  });
                })
              // 请将$r('app.string.Next_page')替换为实际资源文件，在本示例中该资源文件的value值为"下一页"
              Button($r('app.string.Next_page'))
                .onClick(() => {
                  this.scroller.scrollPage({
                    next: true
                  });
                })
            }
          }
          // [End Control_scrolling_position]
        }
      }
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
    }
    .backgroundColor('#f1f2f3')
    // 请将$r('app.string.GridSideToSide_title')替换为实际资源文件，在本示例中该资源文件的value值为"控制滚动位置"
    .title($r('app.string.GridSideToSide_title'))
  }
}
