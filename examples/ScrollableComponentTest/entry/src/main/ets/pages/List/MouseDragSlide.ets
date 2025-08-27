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

// slide the List through mouse button.
@Entry
@Component
struct MouseDragSlide {

  private panOption: PanGestureOptions = new PanGestureOptions({ direction: PanDirection.Vertical });
  private arr: number[] = [];
  private scroller: Scroller = new Scroller();
  private offsetY: number = 0;
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
              .height(60)
              .fontSize(60)
              .textAlign(TextAlign.Center)
              .borderRadius(10)
              .backgroundColor(0xFFFFFF)
              .focusable(true)
          }
        }, (item: string) => item)
      }
      .gesture(
        PanGesture(this.panOption)
          .onActionStart((event: GestureEvent) => {
            this.offsetY = event.offsetY;
          })
          .onActionUpdate((event: GestureEvent) => {
            this.scroller.scrollBy(0, this.offsetY - event.offsetY);
            this.offsetY = event.offsetY;
          })
          .onActionEnd((event: GestureEvent) => {
            this.scroller.fling(event.velocityY);
          })
      )
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xDCDCDC)
    .padding({ top: 5 })
  }
}