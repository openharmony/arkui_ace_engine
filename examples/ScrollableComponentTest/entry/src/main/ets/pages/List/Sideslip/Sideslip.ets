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
 * This demo demonstrates how to use the swinpeAction property and
 * animation to achieve the List horizontal sliding delete icon animation effect.
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
class Item {
  constructor(data: string
  ) {
    this.data = data
  }

  public data: string
  public inDeleteArea: boolean = false
  public offsetY: number = 0
}

@Component
struct CardItem {
  @ObjectLink item: Item

  build() {
    Text('item' + this.item.data)
      .fontSize(16)
      .width('100%')
      .height(74)
      .fontSize(16)
      .textAlign(TextAlign.Center)
      .borderRadius(10)
      .backgroundColor(0xFFFFFF)
      .translate({ y: this.item.offsetY })
  }
}

@Component
struct MySwipeActionItem2 {
  @ObjectLink item: Item
  @State angle: number = 0
  @State angle2: number = 0
  @State scaleDelItem: number = 1
  private selfSize: SizeResult = { width: 0, height: 0 }
  private ITEM_SIZE: number = 40
  private ITEM_SPACE: number = 8
  private SELF_HEIGHT: number = 74
  private SELF_PADDING: number = 12
  onDelete: () => void = () => {
  }

  @Styles
  buttonStyle() {
    .borderRadius(this.ITEM_SIZE / 2)
    .height(this.ITEM_SIZE)
    .width(this.ITEM_SIZE)
  }

  @Builder
  builder() {
    Stack(){
      Image($r('sys.media.ohos_ic_public_share'))
        .width('70%')
        .height('70%')
        .fillColor($r('sys.color.ohos_id_color_primary_contrary'))
    }
    .buttonStyle()
    .backgroundColor($r('sys.color.ohos_id_color_palette11'))
    .flexGrow(this.item.inDeleteArea ? 0 : 1)
    .visibility(this.item.inDeleteArea ? Visibility.Hidden : Visibility.Visible)
    Stack() {
      Image($r('app.media.ic_public_delete_top'))
        .width('70%')
        .height('70%')
        .rotate({
          x: 0,
          y: 0,
          z: 1,
          centerX: 20,
          centerY: 4,
          angle: this.angle
        })
        .animation({ curve: Curve.Friction, duration: 200 })
      Image($r('app.media.ic_public_delete_bottom'))
        .width('70%')
        .height('70%')
        .rotate({
          x: 0,
          y: 0,
          z: 1,
          centerX: 30,
          centerY: 13,
          angle: -this.angle2
        })
        .animation({ curve: Curve.Friction, duration: 200 })
    }
    .buttonStyle()
    .backgroundColor($r('sys.color.ohos_id_color_warning'))
    .scale({ x: this.scaleDelItem, y: this.scaleDelItem })
    .animation({ curve: Curve.Friction, duration: 200 })
    .onClick(() => {
      if (this.onDelete) {
        this.onDelete()
      }
    })
}


build() {
  this.builder()
}

onMeasureSize(selfLayoutInfo: GeometryInfo, children: Array<Measurable>,
  constraint: ConstraintSizeOptions): SizeResult {
  children.forEach((value) => {
    value.measure({ maxWidth: this.ITEM_SIZE, maxHeight: this.ITEM_SIZE, minWidth: 0, minHeight: 0 })
  })
  let width: number = (this.ITEM_SIZE + this.ITEM_SPACE) * children.length + this.SELF_PADDING * 2
  width = Math.max(width, constraint.minWidth as number)
  width = Math.min(width, constraint.maxWidth as number)
  this.selfSize = { height: this.SELF_HEIGHT, width: width }
  return this.selfSize
}

onPlaceChildren(selfLayoutInfo: GeometryInfo, children:Array<Layoutable>, constraint: ConstraintSizeOptions): void {
  let a = 0
  let y = (this.selfSize.height - this.ITEM_SIZE) / 2
  let w = this.selfSize.width - this.SELF_PADDING * 2 - (this.ITEM_SIZE + this.ITEM_SPACE) * children.length
  if (!this.item.inDeleteArea) {
    let dw = w * 5 / 6 / children.length;
    let x0 = this.SELF_PADDING + this.ITEM_SPACE / 2 + dw
    let k = this.ITEM_SIZE + this.ITEM_SPACE + dw
    children.forEach((value, index) => {
      value.layout({ x: x0 + index * k, y: y })
      a = x0 + index * k
    })
    this.angle = (this.selfSize.width - 120) / 56 * 12
    this.angle2 = 0;
    this.scaleDelItem = 1 + ((this.selfSize.width - 120) / 56) / 20
  } else if (children.length > 1) {
    let k = ((this.selfSize.width - this.ITEM_SIZE - this.ITEM_SPACE) / 2 - this.SELF_PADDING) / (children.length - 1);
    let x0 = this.SELF_PADDING + (k - this.ITEM_SIZE) / 2
    children.forEach((value, index) => {
      value.layout({ x: x0 + index * k, y: y })
    })
    this.angle = 17
    this.angle2 = 10
    this.scaleDelItem = 1.10
  } else {
    children.forEach((value, index) => {
      value.layout({ x: (this.selfSize.width - this.ITEM_SIZE) / 2, y: y })
    })
    this.angle = 17
    this.angle2 = 10
    this.scaleDelItem = 1.10
  }
}
}

@Entry
@Component
struct ListItemExample2 {
  @State dataSource: LazyDataSource<Item> = new LazyDataSource()
  @State scaleItem: number = 0.75
  @State offsetY: number = 0
  @State endOffset: number = 0
  @State currentIndex: string = 'undefined'
  private scroller: Scroller = new Scroller()

  onDelete(item: Item) {
    this.endOffset = 0
    let index = this.dataSource.indexOf(item)
    animateTo({
      duration: 0,
    }, () => {
      this.scaleItem = 0.75
      this.dataSource.deleteItem(item)
    })
    for (let i = 0; i < this.dataSource.totalCount(); ++i) {
      const element = this.dataSource.getData(i)
      if (i < index) {
        element.offsetY = this.endOffset
      } else {
        element.offsetY = 60 + this.endOffset
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
  }

  @Builder
  itemEnd(item: Item) {
    MySwipeActionItem2({ item: item, onDelete: () => {
      this.onDelete(item)
    } })
  }

  build() {
    Column() {
      List({ space: 10, scroller: this.scroller }) {
        LazyForEach(this.dataSource, (item: Item) => {
          ListItem() {
            CardItem({ item: item })
          }
          // .clip(true)
          .zIndex(Number(item.data))
          .transition(TransitionEffect.asymmetric(
            TransitionEffect.IDENTITY,
            TransitionEffect.scale({ x: this.scaleItem, y: this.scaleItem })
              .animation({ duration: 400, curve: Curve.Friction })
              .combine(TransitionEffect.OPACITY.animation({ duration: 100, curve: Curve.Sharp, delay: 100 }))
          ))
          .swipeAction({
            end: {
              builder: this.itemEnd(item),
              onAction: () => {
                this.onDelete(item)
              },
              actionAreaDistance: 56,
              onEnterActionArea: () => {
                animateTo({ duration: 200, curve: Curve.Friction }, () => {
                  item.inDeleteArea = true;
                })
              },
              onExitActionArea: () => {
                animateTo({ duration: 200, curve: Curve.Friction }, () => {
                  item.inDeleteArea = false;
                })
              }
            }
          })
        }, (item: Item) => item.data)
      }
      .scrollBar(BarState.Off)
      .onDidScroll((scrollOffset: number, scrollState: ScrollState) => {
        this.endOffset = scrollOffset
      })
    }
    // .padding(10)
    .backgroundColor('#0D182431')
    .width('100%')
    .height('100%')
  }

  aboutToAppear() {
    for (let i = 0; i < 50; i++) {
      this.dataSource.pushItem(new Item(i.toString()))
    }
  }
}