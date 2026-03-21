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
@Entry
@Component
struct GridScrollNoToIndexSample {
  numbers: GridDataSource = new GridDataSource([]);
  scroller: Scroller = new Scroller();
  aboutToAppear(): void {
    let list: string[] = [];
    for (let i = 0; i < 11; i++) {
      // for (let j = 0; j < 10; j++) {
        list.push((i * 5   + 1).toString());
      // }
    }
    this.numbers =  new GridDataSource(list);
  }

  build() {
    Column({ space: 5 }) {
      Row(){
        Button('滚动To到End')
          .onClick(()=> {
            this.scroller.scrollTo({ xOffset: 0, yOffset: 3000 });
          })
        Button('滚动To到Top')
          .onClick(()=> {
            this.scroller.scrollTo({ xOffset: 0, yOffset: -3000 });
          })
      }
      Row(){
        Button('滚动By到End')
          .onClick(()=> {
            this.scroller.scrollBy(0,1000);
          })
        Button('滚动By到Top')
          .onClick(()=> {
            this.scroller.scrollBy(0,-1000);
          })
      }
      Row(){
        Button('索引到End')
          .onClick(()=> {
            this.scroller.scrollToIndex(54);
          })
        Button('索引到Top')
          .onClick(()=> {
            this.scroller.scrollToIndex(0);
          })
      }
      Grid(this.scroller) {
        LazyForEach(this.numbers, (day: string) => {
          GridItem() {
            Text(day)
              .fontSize(16)
              .backgroundColor(0xF9CF93)
              .width('100%')
              .height(80)
              .textAlign(TextAlign.Center)
          }
        }, (index: number) => index.toString())
      }
      .columnsTemplate('1fr 1fr 1fr 1fr 1fr')
      // .rowsTemplate('1fr 1fr 1fr 1fr 1fr')
      .columnsGap(10)
      .rowsGap(10)
      .friction(0.6)
      .enableScrollInteraction(true)
      .supportAnimation(false)
      .multiSelectable(false)
      .edgeEffect(EdgeEffect.Spring)
      .scrollBar(BarState.On)
      .scrollBarColor(Color.Grey)
      .scrollBarWidth(4)
      .width('90%')
      .backgroundColor(0xFAEEE0)
      .height(300)
    }.width('100%').margin({ top: 5 })
  }
}