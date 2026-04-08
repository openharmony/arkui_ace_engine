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

import router from '@ohos.router'
@Entry
@Component
struct ScrollExample2 {
  @State arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
  scrollerForList: Scroller = new Scroller()
  @State arrIndex: number = 10;
  @State itemHeight:Length = 100;
  @State itemWidth:Length = 200;
  build() {
    Column() {
      Row(){
        Button('滚动To到End')
          .onClick(()=> {
            this.scrollerForList.scrollTo({ xOffset: 0, yOffset: 3000 });
          })
        Button('滚动To到Top')
          .onClick(()=> {
            this.scrollerForList.scrollTo({ xOffset: 0, yOffset: -3000 });
          })
      }
      Row(){
        Button('滚动By到End')
          .onClick(()=> {
            this.scrollerForList.scrollBy(0,1000);
          })
        Button('滚动By到Top')
          .onClick(()=> {
            this.scrollerForList.scrollBy(0,-1000);
          })
      }
      Row(){
        Button('索引到End')
          .onClick(()=> {
            this.scrollerForList.scrollToIndex(3);
          })
        Button('索引到Top')
          .onClick(()=> {
            this.scrollerForList.scrollToIndex(0);
          })
      }
      Scroll(this.scrollerForList) {
        Column(){
          ForEach(this.arr, (item: number, index?: number) => {
            Column() {
              Flex({ direction: FlexDirection.Row, alignItems: ItemAlign.Center }) {
                Text('' + item)
                  .width(this.itemWidth)
                  .height(this.itemHeight)
                  .fontSize(16)
                  .textAlign(TextAlign.Center)
                  .borderRadius(10)
                  .backgroundColor(0xFFFFFF)
              }
            }.backgroundColor(Color.Blue)
          }, (item: string) => item)
        }

      }
      // .scrollable(ScrollDirection.Horizontal)
      .scrollBar(BarState.On)
      .edgeEffect(EdgeEffect.Spring) // 边缘效果设置为Spring
      .padding({ top: 10,left:10 })//测试点：padding
      .initialOffset({xOffset:100,yOffset:100})
      .width('90%')
      .height('50%')
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xDCDCDC)
  }
}