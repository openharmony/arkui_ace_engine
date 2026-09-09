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

import { hilog } from '@kit.PerformanceAnalysisKit';

const TAG = 'SnapStartBottomDemo';

/**
 * Issue: When a horizontal List with snap=START is scrolled to the bottom and a
 * child item is touched (triggering animateTo), GetSnapStartIndexAndPos used
 * !canOverScrollStart_ which fired even when canOverScrollEnd_ was true (at the
 * bottom). This caused items to snap to position 0 without currentOffset_
 * adjustment, resulting in an instant left jump followed by a spring bounce.
 *
 * Fix: Use !(canOverScrollStart_ || canOverScrollEnd_) to match the original
 * bilateral canOverScroll_ semantics, ensuring consistency with LayoutForward's
 * !canOverScrollEnd_ check.
 */
@Entry
@Component
struct HorizontalListSnapStartBottomDemo {
  private scroller: Scroller = new Scroller();
  @State itemScales: number[] = [1.0, 1.0, 1.0];

  build() {
    Column({ space: 12 }) {
      Text('横向List snap=START 底部点击不跳')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .width('100%')
        .padding({ left: 16, top: 16, bottom: 8 })

      Button('滚动到底部')
        .margin({ bottom: 8 })
        .onClick(() => {
          hilog.info(0x3900, TAG, 'scrollEdge End clicked');
          this.scroller.scrollEdge(Edge.End);
        })

      List({ space: 16, scroller: this.scroller }) {
        ForEach([1, 2, 3], (i: number) => {
          ListItem() {
            Stack() {
              Column() {
                Text('Item ' + i)
                  .fontSize(20)
                  .fontColor(Color.White)
              }
              .width('100%')
              .aspectRatio(1)
              .justifyContent(FlexAlign.Center)
            }
            .backgroundColor(i === 1 ? '#E84026' : i === 2 ? '#2BA85A' : '#3A6EE0')
            .borderRadius(12)
            .scale({ x: this.itemScales[i - 1], y: this.itemScales[i - 1] })
            .onTouch((event: TouchEvent) => {
              if (event.type === TouchType.Down) {
                hilog.info(0x3900, TAG, `Item ${i} touch down`);
                animateTo({ duration: 200, curve: Curve.EaseInOut }, () => {
                  this.itemScales[i - 1] = 0.95;
                });
              } else if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                hilog.info(0x3900, TAG, `Item ${i} touch up`);
                animateTo({ duration: 200, curve: Curve.EaseInOut }, () => {
                  this.itemScales[i - 1] = 1.0;
                });
              }
            })
          }
          .width('calc((100% - 16vp) / 2.5)')
        }, (i: number) => i.toString())
      }
      .listDirection(Axis.Horizontal)
      .scrollSnapAlign(ScrollSnapAlign.START)
      .width('100%')
      .layoutWeight(1)
      .backgroundColor('#F5F5F5')
    }
    .width('100%')
    .height('100%')
  }
}
