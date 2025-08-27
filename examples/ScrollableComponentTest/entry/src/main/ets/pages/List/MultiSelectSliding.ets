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


import { JSON } from '@kit.ArkTS';

interface MyData {
  data: number;
  selected: boolean;
}

@Entry
@Component
struct MultiSelectSliding {
  @State arr: MyData[] = [];
  private scroller: ListScroller = new ListScroller();
  private selectStart: number = -1;
  private selectEnd: number = -1;
  private listWidth: number = 0;

  aboutToAppear(): void {
    for (let i = 0; i < 50; i++) {
      this.arr.push({ data: i, selected: false})
    }
  }

  build() {
    Column() {
      List({ space: 10, scroller: this.scroller }) {
        ForEach(this.arr, (item: MyData) => {
          ListItem() {
            Row() {
              Text('item' + item.data.toString())
              Blank()
              Checkbox()
                .select(item.selected)
                .onChange((value: boolean) => {
                  item.selected = value
                })
            }
            .width('100%')
            .height(64)
            .backgroundColor(Color.White)
            .borderRadius(10)
            .padding(8)
          }
          .padding({ left: 12, right: 12 })
        }, (item: MyData) => JSON.stringify(item))
      }
      .gesture(
        PanGesture({ direction: PanDirection.Vertical })
          .onActionStart((event: GestureEvent) => {
            if (event.fingerList[0] != undefined && event.fingerList[0].localX != undefined &&
              event.fingerList[0].localY != undefined) {
              let index = this.scroller.getItemIndex(event.fingerList[0].localX, event.fingerList[0].localY)
              if (index >= 0 && index < this.arr.length) {
                this.selectStart = index
              }
            }
          })
          .onActionUpdate((event: GestureEvent) => {
            if (event.fingerList[0] != undefined && event.fingerList[0].localX != undefined &&
              event.fingerList[0].localY != undefined) {
              let index = this.scroller.getItemIndex(event.fingerList[0].localX, event.fingerList[0].localY)
              if (index >= 0 && index < this.arr.length) {
                if (this.selectEnd != index) {
                  if (index >= this.selectStart) {
                    for (let i = this.selectStart; i <= index; i++) {
                      this.arr[i] = { data: this.arr[i].data, selected: true }
                    }
                    if (this.selectEnd >= 0 && this.selectEnd > index) {
                      for (let i = index + 1; i <= this.selectEnd; i++) {
                        this.arr[i] = { data: this.arr[i].data, selected: false }
                      }
                    }
                    if (this.selectEnd >= 0 && this.selectEnd < this.selectStart) {
                      for (let i = this.selectEnd; i < this.selectStart; i++) {
                        this.arr[i] = { data: this.arr[i].data, selected: false }
                      }
                    }
                  } else {
                    for (let i = index; i <= this.selectStart; i++) {
                      this.arr[i] = { data: this.arr[i].data, selected: true }
                    }
                    if (this.selectEnd >= 0 && this.selectEnd < index) {
                      for (let i = this.selectEnd; i < index; i++) {
                        this.arr[i] = { data: this.arr[i].data, selected: false }
                      }
                    }
                  }
                  this.selectEnd = index
                }
              }
            }
          })
      )
      .onSizeChange((oldValue: SizeOptions, newValue: SizeOptions) => {
        this.listWidth = newValue.width as number
      })
      .onGestureRecognizerJudgeBegin((event: BaseGestureEvent, current: GestureRecognizer,
        recognizers: Array<GestureRecognizer>) => {
        if (current.isBuiltIn() && current.getType() == GestureControl.GestureType.PAN_GESTURE &&
          event.fingerList[0].localX > this.listWidth - 48) {
          return GestureJudgeResult.REJECT;
        }
        return GestureJudgeResult.CONTINUE;
      })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xDCDCDC)
  }
}