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


@Component
struct SwiperNestList {
  @State item: number = 0
  private scroller: Scroller = new Scroller()

  aboutToAppear() {
    console.info('item: ' + this.item)
  }

  build() {
    List({ scroller: this.scroller }) {
      ForEach([0, 1, 2], (item2: number) => {
        ListItem() {
          Text(this.item.toString() + item2.toString())
            .width('70%')
            .height('100%')
            .backgroundColor(0xAFEEEE)
            .textAlign(TextAlign.Center)
            .fontSize(30)
        }
      })
    }
    .onGestureRecognizerJudgeBegin((event: BaseGestureEvent, current: GestureRecognizer) => {
      if (current.isBuiltIn() && current.getType() == GestureControl.GestureType.PAN_GESTURE) {
        let panEvent = event as PanGestureEvent;
        if (this.scroller.currentOffset().yOffset <= 0) {
          if (panEvent.velocityY > 0) {
            return GestureJudgeResult.REJECT
          }
        } else if (this.scroller.isAtEnd()) {
          if (panEvent.velocityY < 0) {
            return GestureJudgeResult.REJECT
          }
        }
      }

      return GestureJudgeResult.CONTINUE
    })
  }
}


@Entry
@Component
struct SwiperNestListExample {
  private controller: SwiperController = new SwiperController()

  build() {
    Column({ space: 5 }) {
      Swiper(this.controller) {
        ForEach([0, 1, 2], (item: number) => {
          Stack() {
            SwiperNestList({ item: item })
          }
          .height(220)
        })
      }
      .loop(false)
      .indicator(false)
      .backgroundColor(0xAFEE00)
      .cachedCount(2)
      .vertical(true)
    }
    .width('100%')
    .margin({ top: 5 })
  }
}
