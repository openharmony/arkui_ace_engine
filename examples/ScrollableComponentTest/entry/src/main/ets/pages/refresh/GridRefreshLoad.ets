/*
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

/*用例描述
  本用例使用Refresh组件与Grid组件组合实现下拉刷新上拉加载更多效果。
*/

@Entry
@Component
struct GridRefreshLoadExample {
  @State arr: Array<number> = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19]
  @State refreshing: boolean = false;
  @State refreshOffset: number = 0;
  @State refreshState: RefreshStatus = RefreshStatus.Inactive;

  @Builder
  refreshBuilder() {
    Stack({ alignContent: Alignment.Bottom }) {
      if (this.refreshState != RefreshStatus.Inactive && this.refreshState != RefreshStatus.Done) {
        Progress({ value: this.refreshOffset, total: 64, type: ProgressType.Ring })
          .width(32)
          .height(32)
          .style({ status: this.refreshing ? ProgressStatus.LOADING : ProgressStatus.PROGRESSING })
          .margin(10)
      }
    }
    .height('100%')
    .width('100%')
  }

  build() {
    Refresh({ refreshing: $$this.refreshing, builder: this.refreshBuilder() }) {
      Grid() {
        ForEach(this.arr, (item: number) => {
          GridItem() {
            Text('' + item)
              .width('100%')
              .height(100)
              .fontSize(16)
              .textAlign(TextAlign.Center)
              .borderRadius(10)
              .backgroundColor(0xFFFFFF)
          }
        }, (item: string) => item)
        GridItem() {
          Row() {
            LoadingProgress()
              .height(32)
              .width(48)
            Text('加载中')
          }
        }
        .width('100%')
        .height(64)
        .columnStart(0)
        .columnEnd(1)
      }
      .onScrollIndex((start: number, end: number) => {
        if (end >= this.arr.length) {
          setTimeout(() => {
            for (let i = 0; i < 6; i++) {
              this.arr.push(this.arr.length);
            }
          }, 1000)
        }
      })
      .columnsTemplate('1fr 1fr')
      .scrollBar(BarState.Off)
      .edgeEffect(EdgeEffect.Spring)
      .onAreaChange((oldValue: Area, newValue: Area) => {
        this.refreshOffset = newValue.position.y as number;
      })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xDCDCDC)
    .onStateChange((state: RefreshStatus) => {
      this.refreshState = state;
    })
    .onRefreshing(() => {
      setTimeout(() => {
        // 模拟数据刷新
        this.refreshing = false;
      }, 2000)
    })
  }
}

