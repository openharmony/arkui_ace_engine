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
struct ListExample6 {
  @State text: number = 0
  @State arr: number[] = []
  private scroller: ListScroller = new ListScroller()
  @State listSpace: number = 10
  @State listChildrenSize: ChildrenMainSize = new ChildrenMainSize(100)
  @State item1: number = 0
  // 记录当前选中的项索引（用于删除指定项）
  @State selectedIndex: number = -1

  // 拖拽过程样式
  @Builder pixelMapBuilder() {
    Column() {
      Text(`${this.text}`)
        .fontSize(16)
        .backgroundColor(0xF9CF93)
        .width(80)
        .height(80)
        .textAlign(TextAlign.Center)
    }
  }

  aboutToAppear() {
    // 初始化数据源
    for (let i = 0; i < 10; i++) {
      this.arr.push(i)
    }
    // 前5个item设置自定义高度300
    this.listChildrenSize.splice(0, 5, [300, 300, 300, 300, 300])
  }

  // 拖拽插入逻辑
  moveItem(fromIndex: number, toIndex: number) {
    if (fromIndex === toIndex || fromIndex < 0 || toIndex < 0 ||
        fromIndex >= this.arr.length || toIndex >= this.arr.length) {
      console.info('pengliangbubangwoceshi')
      return
    }
    console.info('pengliangbushishenmehaoren')
    const item = this.arr.splice(fromIndex, 1)[0]
    this.arr.splice(toIndex, 0, item)
  }

  // ========== 新增：添加列表项方法 ==========
  /**
   * 添加列表项
   * @param position 插入位置（默认-1表示末尾）
   * @param value 新增项的值（默认自动生成唯一数字）
   */
  addListItem(position: number = -1, value?: number) {
    // 生成唯一值（避免重复）
    const newItem = value ?? Math.max(...this.arr, 0) + 1
    // 校验插入位置
    const insertIndex = position < 0 || position > this.arr.length
      ? this.arr.length
      : position

    // 插入新项到数组
    this.arr.splice(insertIndex, 0, newItem)

    console.log(`添加项成功：位置${insertIndex}，值${newItem}，当前数组：${this.arr}`)
  }

  // ========== 新增：删除列表项方法 ==========
  /**
   * 删除列表项
   * @param index 要删除的索引（默认-1表示最后一项）
   */
  deleteListItem(index: number = -1) {
    // 数组为空时直接返回
    if (this.arr.length === 0) {
      console.log('列表为空，无法删除')
      return
    }

    // 校验删除索引
    const deleteIndex = index < 0 || index >= this.arr.length
      ? this.arr.length - 1
      : index

    // 删除数组项
    const deletedItem = this.arr.splice(deleteIndex, 1)[0]
    console.log(`删除项成功：位置${deleteIndex}，值${deletedItem}，当前数组：${this.arr}`)

    // 重置选中索引（若删除的是当前选中项）
    if (this.selectedIndex === deleteIndex) {
      this.selectedIndex = -1
    }
  }

  build() {
    Column() {
      List({ space: this.listSpace, initialIndex: 4, scroller: this.scroller }) {
        ForEach(
          this.arr,
          (item: number, index: number) => {
            ListItemGroup() {
              ListItem() {
                Text(`item-${item}`)
                  .height(item < 5 ? 200 : this.listChildrenSize.childDefaultSize)
                  .width('90%')
                  .fontSize(16)
                  .textAlign(TextAlign.Center)
                  .borderRadius(10)
                  .backgroundColor(this.selectedIndex === index ? 0xE6F7FF : 0xFFFFFF)
                  // 点击项选中索引（方便删除指定项）
                  .onClick(() => {
                    this.selectedIndex = index
                    console.log(`选中项：索引${index}，值${item}`)
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
        if (!isSuccess || insertIndex >= this.arr.length) {
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

      // 原有功能按钮 + 新增增删按钮
      Column() {
        Row() {
          Button('item size + 50')
            .onClick(() => {
              this.listChildrenSize.childDefaultSize += 50
            })
            .height('50%')
            .width('30%')
          Button('item size - 50')
            .onClick(() => {
              if (this.listChildrenSize.childDefaultSize <= 50) {
                return
              }
              this.listChildrenSize.childDefaultSize -= 50
            })
            .height('50%')
            .width('30%')
          Button('scrollTo (0, 310)')
            .onClick(() => {
              this.scroller.scrollTo({ xOffset: 0, yOffset: 310 })
            })
            .height('50%')
            .width('30%')
        }
        .height('40%')
        .margin(5)

        // 新增增删按钮行
        Row() {
          Button('添加末尾项')
            .onClick(() => {
              this.addListItem() // 默认添加到末尾
            })
            .height('80%')
            .width('23%')
            .backgroundColor(0x90EE90)

          Button('添加到索引2')
            .onClick(() => {
              this.addListItem(2) // 插入到索引2的位置
            })
            .height('80%')
            .width('23%')
            .backgroundColor(0x90EE90)

          Button('删除选中项')
            .onClick(() => {
              this.deleteListItem(this.selectedIndex) // 删除选中项
            })
            .height('80%')
            .width('23%')
            .backgroundColor(0xFFB6C1)
            .enabled(this.selectedIndex !== -1) // 未选中时禁用

          Button('删除最后项')
            .onClick(() => {
              this.deleteListItem() // 默认删除最后一项
            })
            .height('80%')
            .width('23%')
            .backgroundColor(0xFFB6C1)
            .enabled(this.arr.length > 0) // 列表为空时禁用
        }
        .height('50%')
        .margin(5)
      }
      .height('20%')
      .width('100%')
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xF5F5F5)
  }
}