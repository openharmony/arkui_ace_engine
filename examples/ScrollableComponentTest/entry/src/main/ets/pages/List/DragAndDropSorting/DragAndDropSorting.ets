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

/**
 * This demo demonstrates how to achieve drag and drop sorting effects
 * through animation and Pan gesture events.
 */

import curves from '@ohos.curves';

class ListItemModify implements AttributeModifier<ListItemAttribute> {
  public hasShadow: boolean = false
  public scale: number = 1
  public offsetY: number = 0
  applyNormalAttribute(instance: ListItemAttribute): void {
    if (this.hasShadow) {
      instance.shadow({ radius: 70, color: '#15000000', offsetX: 0, offsetY: 0 })
      instance.zIndex(1)
    }
    instance.scale({ x: this.scale, y: this.scale })
    instance.translate({ y: this.offsetY })
  }
}
enum DragSortState {
  IDLE,
  PRESSING,
  MOVING,
  DROPPING,
}
@Observed
class DragSortCtrl {
  private arr: Array<number>
  private modify: Array<ListItemModify>
  private dragRefOffset: number = 0
  private offsetY: number = 0
  private state:DragSortState = DragSortState.IDLE
  private ITEM_INTV: number = 120
  constructor(arr: Array<number>, intv:number) {
    this.arr = arr;
    this.modify = []
    this.ITEM_INTV = intv
    arr.forEach(()=>{
      this.modify.push(new ListItemModify())
    })
  }
  itemMove(index: number, newIndex: number): void {
    let tmp = this.arr.splice(index, 1)
    this.arr.splice(newIndex, 0, tmp[0])
    let tmp2 = this.modify.splice(index, 1)
    this.modify.splice(newIndex, 0, tmp2[0])
  }
  onLongPress(item: number): void {
    let index = this.arr.indexOf(item)
    this.dragRefOffset = 0
    animateTo({ curve: Curve.Friction, duration: 300 }, () => {
      this.state = DragSortState.PRESSING
      this.modify[index].hasShadow = true
      this.modify[index].scale = 1.05
    })
  }
  onDrop(item: number):void {
    let index = this.arr.indexOf(item)
    this.dragRefOffset = 0
    this.offsetY = 0
    animateTo({ curve: curves.interpolatingSpring(0, 1, 400, 38) }, () => {
      this.state = DragSortState.DROPPING
      this.modify[index].hasShadow = false
      this.modify[index].offsetY = 0
      if (index < this.modify.length - 1) {
        this.modify[index + 1].scale = 1;
      }
      if (index > 0) {
        this.modify[index - 1].scale = 1;
      }
    })
    animateTo({curve: curves.interpolatingSpring(14, 1, 170, 17), delay: 150}, ()=>{
      this.state = DragSortState.IDLE
      this.modify[index].scale = 1
    })
  }
  onMove(item: number, offset: number) {
    this.state = DragSortState.MOVING
    this.offsetY = offset - this.dragRefOffset
    let index = this.arr.indexOf(item)
    this.modify[index].offsetY = this.offsetY
    let curveValue = curves.initCurve(Curve.Sharp)
    if (this.offsetY < 0) {
      let value = curveValue.interpolate(-this.offsetY / this.ITEM_INTV)
      if (index < this.modify.length - 1) {
        this.modify[index + 1].scale = 1;
      }
      if (index > 0) {
        this.modify[index - 1].scale = 1 - value / 20;
      }
    } else if (this.offsetY > 0) {
      let value = curveValue.interpolate(this.offsetY / this.ITEM_INTV)
      if (index < this.modify.length - 1) {
        this.modify[index + 1].scale = 1 - value / 20;
      }
      if (index > 0) {
        this.modify[index - 1].scale = 1;
      }
    }
    if (this.offsetY > this.ITEM_INTV / 2) {
      animateTo({ curve: curves.interpolatingSpring(0, 1, 400, 38) }, () => {
        this.offsetY -= this.ITEM_INTV
        this.dragRefOffset += this.ITEM_INTV
        this.modify[index].offsetY = this.offsetY
        this.itemMove(index, index + 1)
      })
    } else if (this.offsetY < -this.ITEM_INTV / 2) {
      animateTo({ curve: curves.interpolatingSpring(0, 1, 400, 38) }, () => {
        this.offsetY += this.ITEM_INTV
        this.dragRefOffset -= this.ITEM_INTV
        this.modify[index].offsetY = this.offsetY
        this.itemMove(index, index - 1)
      })
    }
  }
  getModify(item: number):ListItemModify {
    let index = this.arr.indexOf(item)
    return this.modify[index]
  }
}
// xxx.ets
@Entry
@Component
struct ListItemExample {
  @State private arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
  @State dragSortCtrl: DragSortCtrl = new DragSortCtrl(this.arr, 120)
  build() {
    Stack() {
      List({ space: 20, initialIndex: 0 }) {
        ForEach(this.arr, (item: number) => {
          ListItem() {
            Text('' + item)
              .width('100%')
              .height(100)
              .fontSize(16)
              .textAlign(TextAlign.Center)
              .backgroundColor(0xFFFFFF)
          }
          .clip(true)
          .attributeModifier(this.dragSortCtrl.getModify(item))
          .borderRadius(10)
          .margin({ left: 12, right: 12 })
          .gesture(
            // 以下组合手势为顺序识别，当长按手势事件未正常触发时则不会触发拖动手势事件
            GestureGroup(GestureMode.Sequence,
              LongPressGesture({ repeat: false })
                .onAction((event?: GestureEvent) => {
                  this.dragSortCtrl.onLongPress(item)
                }),
              PanGesture({ fingers: 1, direction: null, distance: 0 })
                .onActionUpdate((event: GestureEvent) => {
                  this.dragSortCtrl.onMove(item, event.offsetY)
                })
                .onActionEnd((event: GestureEvent) => {
                  this.dragSortCtrl.onDrop(item)
                })
            )
              .onCancel(() => {
                this.dragSortCtrl.onDrop(item)
              })
          )
        }, (item: number) => item.toString())
      }
    }.width('100%').height('100%').backgroundColor(0xDCDCDC).padding({ top: 5 })
  }
}