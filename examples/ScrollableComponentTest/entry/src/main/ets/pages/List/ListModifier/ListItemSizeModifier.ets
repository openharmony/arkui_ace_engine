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

/*
 * Description: 通过动态属性修改item样式来修改原本长按浮起的Item的宽高
 * Writer: dailihuan
 */

import curves from '@ohos.curves';//

class ListItemModify implements AttributeModifier<ListItemAttribute> {
  public hasShadow: boolean = false;
  public scale: number = 1;
  public offsetY: number = 0;
  h: number = 30;

  applyNormalAttribute(instance: ListItemAttribute): void {
    if (this.hasShadow) {
      instance.shadow({
        radius: 70,
        color: '#15000000',
        offsetX: 0,
        offsetY: 0
      });
      instance.zIndex(1);
    }
    instance.height(this.h);
    instance.scale({ x: this.scale, y: this.scale });
    instance.translate({ y: this.offsetY });
  }
}

enum DragSortState {
  IDLE,
  PRESSING,
  MOVING,
  DROPPING,
};

@Observed
class DragSortCtrl<T> {
  private arr: Array<T>;
  private modify: Array<ListItemModify>;
  private dragRefOffset: number = 0;
  offsetY: number = 0;
  state: DragSortState = DragSortState.IDLE;
  private ITEM_INTV: number = 120;

  constructor(arr: Array<T>, intv: number) {
    this.arr = arr;
    this.modify = new Array<ListItemModify>();
    this.ITEM_INTV = intv;
    arr.forEach(() => {
      this.modify.push(new ListItemModify());
    })
  }

  itemMove(index: number, newIndex: number): void { // 移动时两个Item对换
    let tmp = this.arr.splice(index, 1);
    this.arr.splice(newIndex, 0, tmp[0]);
    let tmp2 = this.modify.splice(index, 1);
    this.modify.splice(newIndex, 0, tmp2[0]);
  }

  onLongPress(item: T): void { //长按修改ListItem样式
    let index = this.arr.indexOf(item);
    this.dragRefOffset = 0;
    animateTo({ curve: Curve.Friction, duration: 300 }, () => {
      this.state = DragSortState.PRESSING;
      this.modify[index].hasShadow = true;
      this.modify[index].h = 60;
      this.modify[index].scale = 1.05;
    })
  }

  onDrop(item: T): void {
    let index = this.arr.indexOf(item);
    this.dragRefOffset = 0;
    this.offsetY = 0;
    animateTo({ curve: curves.interpolatingSpring(0, 1, 400, 38) }, () => {
      this.state = DragSortState.DROPPING;
      this.modify[index].hasShadow = false;
      this.modify[index].offsetY = 0;
      if (index < this.modify.length - 1) {
        this.modify[index + 1].scale = 1;;
      }
      if (index > 0) {
        this.modify[index - 1].scale = 1;
      }
    })
    animateTo({ curve: curves.interpolatingSpring(14, 1, 170, 17), delay: 150 }, () => {
      this.state = DragSortState.IDLE;
      this.modify[index].scale = 1;
    });
  }

  onMove(item: T, offset: number) {
    this.state = DragSortState.MOVING;
    this.offsetY = offset - this.dragRefOffset;
    let index = this.arr.indexOf(item);
    this.modify[index].offsetY = this.offsetY;
    let curveValue = curves.initCurve(Curve.Sharp);
    if (this.offsetY < 0) {
      let value = curveValue.interpolate(-this.offsetY / this.ITEM_INTV);
      if (index < this.modify.length - 1) {
        this.modify[index + 1].scale = 1;
      }
      if (index > 0) {
        this.modify[index - 1].scale = 1 - value / 20;
      }
    } else if (this.offsetY > 0) {
      let value = curveValue.interpolate(this.offsetY / this.ITEM_INTV);
      if (index < this.modify.length - 1) {
        this.modify[index + 1].scale = 1 - value / 20;
      }
      if (index > 0) {
        this.modify[index - 1].scale = 1;
      }
    }
    if (this.offsetY > this.ITEM_INTV / 2) {
      animateTo({ curve: curves.interpolatingSpring(0, 1, 400, 38) }, () => {
        this.offsetY -= this.ITEM_INTV;
        this.dragRefOffset += this.ITEM_INTV;
        this.modify[index].offsetY = this.offsetY;
        this.itemMove(index, index + 1);
      });
    } else if (this.offsetY < -this.ITEM_INTV / 2) {
      animateTo({ curve: curves.interpolatingSpring(0, 1, 400, 38) }, () => {
        this.offsetY += this.ITEM_INTV;
        this.dragRefOffset -= this.ITEM_INTV;
        this.modify[index].offsetY = this.offsetY;
        this.itemMove(index, index - 1);
      });
    }
  }

  getModify(item: T): ListItemModify {
    let index = this.arr.indexOf(item);
    return this.modify[index];
  }
}

@Entry
@Component
struct ListItemExample {
  @State private arr: Array<number> = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9];
  @State dragSortCtrl: DragSortCtrl<number> = new DragSortCtrl<number>(this.arr, 120);

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

            GestureGroup(GestureMode.Sequence,
              LongPressGesture({ repeat: false })
                .onAction((event?: GestureEvent) => {
                  this.dragSortCtrl.onLongPress(item);
                }),
              PanGesture({ fingers: 1, direction: null, distance: 0 })
                .onActionUpdate((event: GestureEvent) => {
                  this.dragSortCtrl.onMove(item, event.offsetY);
                })
                .onActionEnd((event: GestureEvent) => {
                  this.dragSortCtrl.onDrop(item);
                })
            )
              .onCancel(() => {
                this.dragSortCtrl.onDrop(item);
              })
          )
        }, (item: number) => item.toString())
      }
    }.width('100%').height('100%').backgroundColor(0xDCDCDC).padding({ top: 5 })
  }
}