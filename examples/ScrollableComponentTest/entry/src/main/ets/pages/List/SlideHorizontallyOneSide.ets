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
struct SwipeItem {
  swipeState: SwipeActionState = SwipeActionState.COLLAPSED

  @Builder itemEnd() {
    Row() {
      Button('Delete')
        .margin('4vp')
      Button('Set')
        .margin('4vp')
    }
    .padding('4vp')
    .justifyContent(FlexAlign.SpaceEvenly)
  }

  build() {
    ListItem() {
      Text('item')
        .width('100%')
        .height(100)
        .fontSize(16)
        .textAlign(TextAlign.Center)
        .borderRadius(10)
        .backgroundColor(0xFFFFFF)
    }
    .onGestureRecognizerJudgeBegin((event: BaseGestureEvent, current: GestureRecognizer,
        recognizers: Array<GestureRecognizer>) => {
      if (this.swipeState == SwipeActionState.COLLAPSED) {
        let panEvent = event as PanGestureEvent;
        if (panEvent.offsetX > 0) {
          return GestureJudgeResult.REJECT;
        }
      }
      return GestureJudgeResult.CONTINUE;
    })
    .transition({ type: TransitionType.Delete, opacity: 0 })
    .swipeAction({
      end: {
        builder: () => { this.itemEnd() },
        onStateChange: (state: SwipeActionState) => {
          this.swipeState = state;
        }
      }
    })
  }
}

// xxx.ets
@Entry
@Component
struct SlideHorizontallyOneSide {
  @State arr: number[] = [0, 1, 2, 3, 4]
  @State enterEndDeleteAreaString: string = 'not enterEndDeleteArea'
  @State exitEndDeleteAreaString: string = 'not exitEndDeleteArea'
  private scroller: ListScroller = new ListScroller()


  build() {
    Column() {
      List({ space: 10, scroller: this.scroller }) {
        ForEach(this.arr, (item: number) => {
          SwipeItem()
        }, (item: string) => item)
      }
      Text(this.enterEndDeleteAreaString)
        .fontSize(20)
      Text(this.exitEndDeleteAreaString)
        .fontSize(20)
    }
    .padding(10)
    .backgroundColor(0xDCDCDC)
    .width('100%')
    .height('100%')
  }
}