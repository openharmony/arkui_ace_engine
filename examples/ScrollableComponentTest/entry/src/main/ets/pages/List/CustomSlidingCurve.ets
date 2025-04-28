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

import Curves from '@ohos.curves';

class SpeedCalculator {
  private timestamp: number = 0
  private offset: number = 0
  private speed: number = 0
  setOffset(offset: number) : void {
    let date = new Date();
    if (this.timestamp === 0) {
      this.timestamp = date.getTime();
      this.offset = offset;
    }
    if (this.timestamp !== date.getTime()) {
      this.speed = (offset - this.offset) / (date.getTime() - this.timestamp);
      this.timestamp = date.getTime();
      this.offset = offset;
    }
  }
  getSpeed(): number {
    return this.speed * 1000;
  }
}
@Entry
@Component
struct CustomSlidingCurve {
  private arr: number[] = [];
  private scroller: Scroller = new Scroller();
  private speedCalculator: SpeedCalculator = new SpeedCalculator();
  private currentOffset = 0;


  aboutToAppear(): void {
    for (let i = 0; i < 100; i++) {
      this.arr.push(i);
    }
  }

  build() {
    Column() {
      List({ space: 20, initialIndex: 0, scroller: this.scroller }) {
        ForEach(this.arr, (item: number) => {
          ListItem() {
            Text('' + item)
              .width('100%')
              .height(100)
              .fontSize(16)
              .textAlign(TextAlign.Center)
              .borderRadius(10)
              .backgroundColor(0xFFFFFF)
          }
        }, (item: string) => item)
      }
      .width('90%')
      .scrollBar(BarState.Off)
      .onWillScroll((scrollOffset: number, scrollState: ScrollState, scrollSource: ScrollSource) => {
        this.currentOffset = this.scroller.currentOffset().yOffset + scrollOffset;
        this.speedCalculator.setOffset(this.currentOffset);
      })
      .onTouch((event: TouchEvent) => {
        let speed = this.speedCalculator.getSpeed();
        if (event.type === TouchType.Up && Math.abs(speed) > 10) {
          let distance = speed * 0.5;
          let v0 = speed / distance;
          this.scroller.scrollTo({ xOffset:0, yOffset: this.currentOffset + speed / 2,
            animation: {
              curve: Curves.interpolatingSpring(v0, 1, 100, 20),
              canOverScroll: true
            }});
        }
      })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xDCDCDC)
    .padding({ top: 5 })
  }
}