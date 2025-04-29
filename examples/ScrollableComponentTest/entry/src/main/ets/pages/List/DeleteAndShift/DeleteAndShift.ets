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
 * This demo demonstrates how to achieve the effect of deleting padding 
 * through animation and the swipeAction property. Make deleting items look smoother.
 */

export class LazyDataSource<T> implements IDataSource {
  private elements: T[]
  private listeners: Set<DataChangeListener>
  constructor(elements: T[] = []) {
    this.elements = elements
    this.listeners = new Set()
  }
  public totalCount(): number {
    return this.elements.length
  }
  public getData(index: number): T {
    return this.elements[index]
  }
  public indexOf(item: T): number {
    return this.elements.indexOf(item)
  }
  public pinItem(item: T, index: number): void {
    this.elements.splice(index, 1)
    this.elements.unshift(item)
    this.listeners.forEach(listener => listener.onDataReloaded())
  }
  public addItem(item: T) {
    this.elements.unshift(item)
    this.listeners.forEach(listener => listener.onDataAdd(0))
  }
  public pushItem(item: T) {
    this.elements.push(item)
    this.listeners.forEach(listener => listener.onDataAdd(this.elements.length - 1))
  }
  public insertItem(item: T, index: number) {
    this.elements.splice(index, 0, item)
    this.listeners.forEach(listener => listener.onDataAdd(index))
  }
  public deleteItem(item: T): void {
    const index = this.elements.indexOf(item)
    if (index < 0) {
      return
    }
    this.elements.splice(index, 1)
    this.listeners.forEach(listener => listener.onDataDelete(index))
  }
  public deleteItemByIndex(index: number): void {
    this.elements.splice(index, 1)
    this.listeners.forEach(listener => listener.onDataDelete(index))
  }
  public registerDataChangeListener(listener: DataChangeListener): void {
    this.listeners.add(listener)
  }
  public unregisterDataChangeListener(listener: DataChangeListener): void {
    this.listeners.delete(listener)
  }
}

@Observed
export class Item {
  constructor(data: string
  ) {
    this.data = data
  }
  public data: string
  public offsetY: number = 0
  public scale: number = 1
  public opacity: number = 1
}
@Extend(Button)
function circleStyle(background: ResourceColor) {
  .type(ButtonType.Circle)
  .backgroundColor(background)
}
@Component
export struct CardItem {
  @ObjectLink item: Item
  build() {
    Row() {
      Text(this.item.data)
        .fontSize(16)
        .width('100%')
        .height('100%')
        .textAlign(TextAlign.Center)
        .borderRadius(12)
    }
    .translate({ y: this.item.offsetY })
    .borderRadius(12)
    .height(108)
    .justifyContent(FlexAlign.Center)
    .width('100%')
    .backgroundColor('#fff')
  }
}
@Entry
@Component
export struct ListPinAnimation {
  @State dataSource: LazyDataSource<Item> = new LazyDataSource()
  @State currentIndex: string = 'undefined'
  private scrollerForList: Scroller = new Scroller()
  @State endOffset:number = 0
  @Builder
  renderSwipeAction(item: Item) {
    Row({ space: 12 }) {
      Stack().flexGrow(6)
      Button().circleStyle('rgb(63, 196, 63)')
      Stack().flexGrow(6)
      Button().circleStyle('rgb(0, 157, 227)')
      Stack().flexGrow(6)
      Button().circleStyle('rgb(239, 29, 31)').onClick(() => {
        this.currentIndex = item.data
        const index = this.dataSource.indexOf(item)
        this.endOffset = 0
        animateTo({ duration: 0 }, () => {
          this.dataSource.deleteItem(item)
        })
        for (let i = 0; i < this.dataSource.totalCount(); ++i) {
          const element = this.dataSource.getData(i)
          if (i < index) {
            element.offsetY = this.endOffset
          } else {
            element.offsetY = 120 + this.endOffset
          }
        }
        for (let i = 0; i < this.dataSource.totalCount(); ++i) {
          const element = this.dataSource.getData(i)
          animateTo({
            curve: Curve.Friction,
            duration: 350,
            delay: Math.abs(index - i) * 16.67,
          }, () => {
            element.offsetY = 0
          })
        }
      })
      Stack().flexGrow(1)
    }.padding(12)
  }
  build() {
    Column() {
      List({ space: 12, scroller: this.scrollerForList }) {
        LazyForEach(this.dataSource, (item: Item) => {
          ListItem() {
            CardItem({ item:item })
          }
          .transition(
            // 只需要删除动效，所以使用不对成的过度效果
            TransitionEffect.asymmetric(// 入场动效：无
              TransitionEffect.IDENTITY,
              // 退场动效：尺寸缩放变化+透明度变化
              TransitionEffect.scale({ x: 0.75, y: 0.75 })
                .animation({ curve: Curve.Friction, duration: 300 })
                .combine(
                  TransitionEffect.OPACITY.animation({ curve: Curve.Sharp, duration: 300 })
                )
            )
          )
          .clip(false)
          .zIndex(this.currentIndex == item.data ? 1 : 2)
          .swipeAction({ end: this.renderSwipeAction(item) })
          .width('100%')
        }, (item: Item) => item.data)
      }
      .height('100%')
      .scrollBar(BarState.Off)
    }
    .backgroundColor('#f1f2f3')
    .height('100%')
    .padding(24)
    .width('100%')
  }
  aboutToAppear() {
    for (let i = 0; i < 50; i++) {
      this.dataSource.pushItem(new Item(i.toString()))
    }
  }
}