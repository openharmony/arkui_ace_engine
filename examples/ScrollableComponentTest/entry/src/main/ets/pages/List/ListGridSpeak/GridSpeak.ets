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
struct SimpleGridCRUD {
  // 网格数据源（存储数字字符串）
  @State numbers: string[] = []
  // 记录当前选中的GridItem索引（用于删除指定项）
  @State selectedIndex: number = -1
  scroller: Scroller = new Scroller()
  @State text: string = 'drag'

  @Builder pixelMapBuilder() { //拖拽过程样式
    Column() {
      Text(this.text)
        .fontSize(16)
        .backgroundColor(0xF9CF93)
        .width(80)
        .height(80)
        .textAlign(TextAlign.Center)
    }
  }
  changeIndex(index1: number, index2: number) { //交换数组位置
    let temp: string;
    temp = this.numbers[index1];
    this.numbers[index1] = this.numbers[index2];
    this.numbers[index2] = temp;
  }
  // 页面加载时初始化数据（1-6）
  aboutToAppear() {
    for (let i = 1; i <= 15; i++) {
      this.numbers.push(i + '')
    }
  }
  // ========== 核心增删方法 ==========
  // 1. 添加GridItem（默认添加到末尾，自动生成唯一值）
  addGridItem() {
    // 生成唯一值：数组最大值 + 1
    const maxNum = this.numbers.length > 0
      ? Math.max(...this.numbers.map(item => parseInt(item)))
      : 0
    const newItem = (maxNum + 1).toString()
    this.numbers.push(newItem) // 添加到数组末尾
  }

  // 2. 删除GridItem（删除选中项，无选中则删除最后一项）
  deleteGridItem() {
    if (this.numbers.length === 0) {
      return // 空数组直接返回
    }

    // 确定删除索引：优先删除选中项，否则删除最后一项
    const deleteIndex = this.selectedIndex >= 0 ? this.selectedIndex : this.numbers.length - 1
    this.numbers.splice(deleteIndex, 1) // 删除指定索引项

    // 重置选中状态（避免删除后选中索引错位）
    this.selectedIndex = -1
  }

  // 3. 清空所有GridItem
  clearGrid() {
    this.numbers = []
    this.selectedIndex = -1
  }

  // ========== UI 构建 ==========
  build() {
    Column({ space: 15 }) {
      // 1. Grid 主体（3列布局）
      Grid(this.scroller) {
        ForEach(
          this.numbers,
          // 渲染每个GridItem
          (item: string, index: number) => {
            GridItem() {
              Text(item)
                .fontSize(20)
                // 选中项高亮背景色（区分选中状态）
                .backgroundColor(this.selectedIndex === index ? 0xE6F7FF : 0xF9CF93)
                .width(100)
                .height(100)
                .textAlign(TextAlign.Center)
                .borderRadius(8)
                // 点击选中当前GridItem
                .onClick(() => {
                  this.selectedIndex = index
                })
            }
          },
          // 唯一标识（避免渲染异常）
          (item: string, index: number) => `grid-item-${index}-${item}`
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
      .onItemDragStart((event: ItemDragInfo, itemIndex: number) => {
        this.text = this.numbers[itemIndex]
        return this.pixelMapBuilder() //设置拖拽过程中显示的图片。
      })
      //绑定此事件的组件可作为拖拽释放目标，当在本组件范围内停止拖拽行为时，触发回调。
      .onItemDrop((event: ItemDragInfo, itemIndex: number, insertIndex: number, isSuccess: boolean) => {
        // isSuccess=false时，说明drop的位置在grid外部；insertIndex > length时，说明有新增元素的事件发生
        if (!isSuccess || insertIndex >= this.numbers.length) {
          return
        }
        //itemIndex拖拽起始位置，insertIndex拖拽插入位置
        console.info('beixiang' + itemIndex + '', insertIndex + '')
        this.changeIndex(itemIndex, insertIndex)
      })
      Button('next page')
        .onClick(() => { // 点击后滑到下一页
          this.scroller.scrollToIndex(13, true)
        })

      // 2. 增删操作按钮组
      Row({ space: 10 }) {
        // 添加按钮
        Button('添加项')
          .onClick(() => this.addGridItem())
          .width('30%')
          .backgroundColor(0x90EE90) // 浅绿色

        // 删除按钮（无数据时禁用）
        Button('删除项')
          .onClick(() => this.deleteGridItem())
          .width('30%')
          .backgroundColor(0xFFB6C1) // 浅粉色
          .enabled(this.numbers.length > 0)

        // 清空按钮（无数据时禁用）
        Button('清空')
          .onClick(() => this.clearGrid())
          .width('30%')
          .backgroundColor(0xFF6347) // 番茄色
          .enabled(this.numbers.length > 0)
      }
      .width('90%')
    }
    .width('100%')
    .height('100%')
    .padding(10)
    .backgroundColor(0xF5F5F5)
  }
}