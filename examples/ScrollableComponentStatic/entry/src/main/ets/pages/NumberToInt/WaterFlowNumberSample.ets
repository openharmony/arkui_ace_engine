'use static'
/**
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

import {
  DataReloadOperation,
  DataOperationType,
  Entry,
  Text,
  TextAttribute,
  Column,
  Component,
  Stack,
  WaterFlow,
  LazyForEach,
  FlowItem,
  DataOperation,
  Color,
  TextAlign,
  DataChangeListener,
  IDataSource,
  Button,
  ButtonAttribute,
  ClickEvent,

  Image,
  Search,
  Row,WaterFlowLayoutMode,
  Column,Repeat,RepeatItem,$r,FlexAlign,
  SearchController,ComponentV2,ForEach,
  ColumnOptions,WaterFlowSections,Scroller,SectionOptions
} from '@ohos.arkui.component'
import { State, Link, Prop , Local ,ObservedV2,Trace } from '@ohos.arkui.stateManagement'
import { AppStorage } from '@ohos.arkui.stateManagement';
import { UIContext, Router } from '@ohos.arkui.UIContext';
import common from '@ohos.app.ability.common';
import inspector from '@ohos.arkui.inspector'

@Entry
@ComponentV2
struct RepeatWaterFlowBoolean {
  @Local simpleList1: Array<boolean> = [];
  @Local simpleList2: Array<boolean> = [];
  @Local tmp1: number = 0;
  @Local tmp2: number = 0;
  scroller: Scroller = new Scroller();
  scroller1: Scroller = new Scroller();

  aboutToAppear(): void {
    for (let i = 0; i < 30; i++) {
      this.simpleList1.push(i % 2 === 0);
      this.simpleList2.push(i % 2 === 0);
    }
  }

  build() {
    Column({ space: 10 } as ColumnOptions) {
      WaterFlow({ scroller: this.scroller }) {
        Repeat<boolean>(this.simpleList1)
          .each((ri) => {
            FlowItem() {
              Text(ri.item.toString() + ' index:' + ri.index.toString() + ':' + this.tmp2.toString())
                .id('Text1_WB' + ri.index.toString())
                .fontSize(20)
                .height('20%')
            }
            .width('100%')
            .border({ width: 1 })
          })
          .key((service: boolean, index: int): string => index + service.toString())
      }
      .columnsTemplate('1fr')
      .columnsGap(10)
      .rowsGap(5)
      .cachedCount(3)
      .onScrollIndex((first: int, last: int) => {
        console.log("first"+ first + 'last'+ last)
      })
      .width('100%')
      .height('30%')
      .border({ width: 1 })

    }
    .width('100%')
    .height('70%')
    .justifyContent(FlexAlign.Center)
  }
}