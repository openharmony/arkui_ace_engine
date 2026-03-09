/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License")
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

@Entry
@Component
struct ListExample5 {
  @State text: number = 0
  @State arr: number[] = []
  private scroller: ListScroller = new ListScroller()
  @State listSpace: number = 10
  @State listChildrenSize: ChildrenMainSize = new ChildrenMainSize(100)
  @State item1: number = 0
  // 记录当前选中的项索引（用于删除指定项）
  @State selectedIndex: number = -1
  @State numbers: string[] = []
  // 记录当前选中的GridItem索引（用于删除指定项）
  @State selectedGridIndex: number = -1
  scrollerGrid: Scroller = new Scroller()
  @State textGrid: string = 'drag'

  // 拖拽过程样式
  @Builder pixelMapBuilder() {
    Column() {
      Text(`${this.text}`)
        .fontSize(16)
        .backgroundColor(0xF9CF93)
        .width('80vp')
        .height('80vp')
        .textAlign(TextAlign.Center)
    }
  }
  @Builder pixelMapGridBuilder() { //拖拽过程样式
    Column() {
      Text(this.textGrid)
        .fontSize(16)
        .backgroundColor(0xF9CF93)
        .width('80vp')
        .height('80vp')
        .textAlign(TextAlign.Center)
    }
  }
  changeIndex(index1: number, index2: number) { //交换数组位置
    let temp: string;
    temp = this.numbers[index1];
    this.numbers[index1] = this.numbers[index2];
    this.numbers[index2] = temp;
  }

  aboutToAppear() {
    // 初始化数据源
    for (let i = 0; i < 10; i++) {
      this.arr.push(i)
    }
    // 前5个item设置自定义高度300
    this.listChildrenSize.splice(0, 5, [300, 300, 300, 300, 300])
    for (let j = 1; j <= 15; j++) {
      this.numbers.push(j + '')
    }
  }

  // 拖拽插入逻辑
  moveItem(fromIndex: number, toIndex: number) {
    if (fromIndex === toIndex || fromIndex < 0 || toIndex < 0 ||
        fromIndex >= this.arr.length || toIndex >= this.arr.length) {
      return
    }
    const item = this.arr.splice(fromIndex, 1)[0]
    this.arr.splice(toIndex, 0, item)
  }

  build() {
    Column() {
      List({ space: this.listSpace, initialIndex: 4, scroller: this.scroller }) {
        ForEach(
          this.arr,
          (item: number, index: number) => {
            ListItemGroup() {
              ListItem() {
                Grid(this.scrollerGrid) {
                  ForEach(
                    this.numbers,
                    // 渲染每个GridItem
                    (itemGrid: string, indexGrid: number) => {
                      GridItem() {
                        Text(itemGrid)
                          .fontSize(20)
                          // 选中项高亮背景色（区分选中状态）
                          .backgroundColor(this.selectedGridIndex === indexGrid ? 0xE6F7FF : 0xF9CF93)
                          .width('100vp')
                          .height('100vp')
                          .textAlign(TextAlign.Center)
                          .borderRadius(8)
                          // 点击选中当前GridItem
                          .onClick(() => {
                            this.selectedGridIndex = indexGrid
                          })
                      }
                    },
                    // 唯一标识（避免渲染异常）
                    (itemGrid: string, indexGrid: number) => `grid-item-${indexGrid}-${itemGrid}`
                  )
                }
                .columnsTemplate('1fr 1fr 1fr')
                .columnsGap(10)
                .rowsGap(10)
                .width('90%')
                .backgroundColor(0xFAEEE0)
                .height(300)
                .editMode(true) //设置Grid是否进入编辑模式，进入编辑模式可以拖拽Grid组件内部GridItem
                //第一次拖拽此事件绑定的组件时，触发回调。
                .onItemDragStart((event: ItemDragInfo, itemGridIndex: number) => {
                  this.textGrid = this.numbers[itemGridIndex]
                  return this.pixelMapBuilder() //设置拖拽过程中显示的图片。
                })
                //绑定此事件的组件可作为拖拽释放目标，当在本组件范围内停止拖拽行为时，触发回调。
                .onItemDrop((event: ItemDragInfo, itemGridIndex: number, insertGridIndex: number,
                  isGridSuccess: boolean) => {
                  // isSuccess=false时，说明drop的位置在grid外部；insertIndex > length时，说明有新增元素的事件发生
                  if (!isGridSuccess || insertGridIndex >= this.numbers.length) {
                    return
                  }
                  //itemIndex拖拽起始位置，insertIndex拖拽插入位置
                  console.info('beixiang' + itemGridIndex + '', insertGridIndex + '')
                  this.changeIndex(itemGridIndex, insertGridIndex)
                })
              }
              .draggable(true)
            }
          },
          (item: number, index: number) => `list-item-${index}-${item}`
        )
      }
      .backgroundColor(Color.Gray)
      .layoutWeight(1)
      .scrollBar(BarState.On)
      .childrenMainSize(this.listChildrenSize)
      .alignListItem(ListItemAlign.Center)
      .multiSelectable(true)
      .onItemDragStart((event: ItemDragInfo, itemIndex: number) => {
        this.text = this.arr[itemIndex]
        console.log(`onItemDragStart: arr=${this.arr}, x=${event.x}, y=${event.y}`)
        return this.pixelMapBuilder()
      })
      .onReachStart(() => {
        console.log('---------------------- onReachStart ------------------------')
      })
      .onReachEnd(() => {
        console.log('---------------------- onReachEnd ------------------------')
      })
      .onItemDrop((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => {
        console.log(`onItemDrop: arr=${this.arr}, isSuccess=${isSuccess}`)
        if (!isSuccess || insertIndex < 0 || insertIndex > this.arr.length) {
          return
        }
        console.info(`拖拽源索引: ${itemIndex}, 插入索引: ${insertIndex}, x=${event.x}, y=${event.y}`)
        this.moveItem(itemIndex, insertIndex)
        console.log('---------------------- onItemDrop 完成 ------------------------')
      })
      .onItemMove((from: number, to: number) => {
        return true
      })
      .onScrollStop(() => {
        console.log('---------------------- onScrollStop ------------------------')
      })
      .onScrollIndex(() => {
        console.log('---------------------- onScrollIndex ------------------------')
      })
      .onScrollVisibleContentChange(() => {
        console.log('---------------------- onScrollVisibleContentChange --------')
      })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xF5F5F5)
  }
}