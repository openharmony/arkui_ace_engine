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
 1、本用例使用scroll组件实现了限位滚动效果，允许开发者自定义限位的动画曲线
*/
/* 关键结构
 |-> Scroll
  |-> Row
    | -> Stack
    | -> Stack
    | -> Stack
*/
import Curves from '@ohos.curves'

@Observed
class A {
  public data: number
  public flag: Boolean
  public delta: number

  constructor(c: number) {
    this.data = c;
    this.flag = false;
    this.delta = 0;
  }
}

abstract class BasicDataSource implements IDataSource {
  private listeners: DataChangeListener[] = [];

  public totalCount(): number {
    return 0;
  }

  abstract getData(index: number): A;

  registerDataChangeListener(listener: DataChangeListener): void {
    if (this.listeners.indexOf(listener) < 0) {
      console.info('add listener');
      this.listeners.push(listener);
    }
  }

  unregisterDataChangeListener(listener: DataChangeListener): void {
    const pos = this.listeners.indexOf(listener);
    if (pos >= 0) {
      console.info('remove listener');
      this.listeners.splice(pos, 1);
    }
  }

  notifyDataReload(): void {
    this.listeners.forEach(listener => {
      listener.onDataReloaded();
    })
  }

  notifyDataAdd(index: number): void {
    this.listeners.forEach(listener => {
      listener.onDataAdd(index);
    })
  }

  notifyDataChange(index: number): void {
    this.listeners.forEach(listener => {
      listener.onDataChange(index);
    })
  }

  notifyDataDelete(index: number): void {
    this.listeners.forEach(listener => {
      listener.onDataDelete(index);
    })
  }

  notifyDataMove(from: number, to: number): void {
    this.listeners.forEach(listener => {
      listener.onDataMove(from, to);
    })
  }
}

class MyDataSource extends BasicDataSource {
  private dataArray: Array<A> = [];

  public totalCount(): number {
    return this.dataArray.length;
  }

  public getData(index: number): A {
    return this.dataArray[index];
  }

  public setDelta(index: number, delta: number) {
    this.dataArray[index].delta = delta;
  }

  public addData(index: number, data: A): void {
    this.dataArray.splice(index, 0, data);
    this.notifyDataAdd(index);
  }

  public popData(): void {
    this.dataArray.pop();
    this.notifyDataDelete(this.dataArray.length);
  }

  public pushData(data: A): void {
    this.dataArray.push(data);
    this.notifyDataAdd(this.dataArray.length - 1);
  }
}

class CustomLayoutController {
  public onScroll?: (offset: number, delta: number) => void
  public getTargetOffset?: (speed: number) => number;
}

// 通过当前位置和移动速度计算动画起始速度
class SpeedCalculator {
  private timestamp: number = 0
  private offset: number = 0
  private speed: number = 0

  setOffset(offset: number): void {
    let date = new Date()
    if (this.timestamp === 0) {
      this.timestamp = date.getTime();
      this.offset = offset
    }
    if (this.timestamp !== date.getTime()) {
      this.speed = (offset - this.offset) / (date.getTime() - this.timestamp)
      this.timestamp = date.getTime();
      this.offset = offset
    }
  }

  getSpeed(): number {
    return this.speed * 1000;
  }
}

// 卡片
@Component
struct CardIndex {
  @Link touchIdx: number
  @ObjectLink index: A

  build() {
    Stack() {
      Text(this.index.data.toString()).fontSize(30)
    }
    .translate({ x: this.index.delta })
    .width(260)
    .height(520)
    .backgroundColor('#FFFFFF')
    .borderRadius(10)
    .onTouch((event: TouchEvent) => {
      if (event.type === TouchType.Down) {
        this.touchIdx = this.index.data
      }
    })
  }
}

@Entry
@Component
struct Index {
  @State currentDelta: number = 0
  @State arr: MyDataSource = new MyDataSource()
  private scroller = new Scroller()
  private controller = new CustomLayoutController()
  private speedCalculator = new SpeedCalculator()
  private currentOffset: number = 0
  private ITEM_COUNT: number = 20
  private ITEM_WIDTH: number = 260
  private ITEM_SPACE: number = 15
  private ITEM_INTV: number = this.ITEM_WIDTH + this.ITEM_SPACE
  private startIndex = 0
  private endIndex = 0
  @State startOffset: number = 0
  @State touchIdx: number = 0
  private contentWidth = 0
  inAdjustOffset: boolean = false;
  private scrollWidth = 0

  onScroll(offset: number, delta: number) {
    this.currentOffset = offset;
    this.startIndex = Math.max(Math.trunc((this.currentOffset - this.startOffset) / this.ITEM_INTV) - 1, 0)
    this.endIndex = Math.min(Math.ceil((this.currentOffset + this.scrollWidth - this.startOffset) / this.ITEM_INTV) + 1,
      this.ITEM_COUNT)
  }

  getTargetOffset(speed: number): number {
    let target = Math.round((this.currentOffset + speed / 2.5) / this.ITEM_INTV) * this.ITEM_INTV;
    return target = Math.max(Math.min(target, this.contentWidth - this.scrollWidth), 0)
  }

  build() {
    Row() {
      Scroll(this.scroller) {
        Row({ space: this.ITEM_SPACE }) {
          LazyForEach(this.arr, (index: A) => {
            CardIndex({ touchIdx: this.touchIdx, index: index })
          })
        }.margin({ left: this.startOffset, right: this.startOffset })
      }
      .scrollable(ScrollDirection.Horizontal)
      .edgeEffect(EdgeEffect.Spring)
      .onWillScroll((xOffset: number) => {
        if (this.inAdjustOffset) {
          return;
        }
        this.onScroll(this.scroller.currentOffset().xOffset, xOffset)
        this.currentOffset = this.scroller.currentOffset().xOffset
        this.speedCalculator.setOffset(this.currentOffset)
      })
      .onTouch((event: TouchEvent) => {
        if (event.type === TouchType.Up) {
          let speed = this.speedCalculator.getSpeed()
          // 计算目标卡片居中时的终点位置
          let target = this.getTargetOffset(speed)
          // 抬手时触发scrollTo，取代scroll自身的惯性动画，其中animation为自定义动画曲线
          this.scroller.scrollTo({ xOffset: target, yOffset: 0, animation: { curve: Curves.springMotion(0.8, 1.3) } })
        }
        if (event.type === TouchType.Down) {
          this.scroller.scrollBy(0, 0)
        }
      })
      .onAreaChange((oldValue: Area, newValue: Area) => {
        this.scrollWidth = newValue.width as number
        this.contentWidth = (this.ITEM_COUNT - 1) * this.ITEM_INTV + this.scrollWidth
        this.startOffset = (this.scrollWidth - this.ITEM_INTV) / 2
      })
    }.backgroundColor('#DCDCDC')
    .height('100%')
    .width('100%')
  }

  aboutToAppear() {
    this.controller.onScroll = (offset: number, delta: number) => {
      this.onScroll(offset, delta)
    }
    this.controller.getTargetOffset = (speed: number) => {
      return this.getTargetOffset(speed)
    }
    for (let i = 0; i < this.ITEM_COUNT; i++) {
      this.arr.pushData(new A(i))
    }
  }
}