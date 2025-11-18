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

 /*
  * Description: 滚动组件布局约束范围提升
  * Writer: renxiaowen
  */

@Entry
@Component
struct ListItemMoveWidth {
  
  /* 
   * 用例描述：List组件中ListItem组件的width属性设置不同值，ListItem组件可拖动
   * 关键结构：
   * |-> List
   *    |-> ListItem
   *       |-> Text
   */

  @State realName: string[][] = [];
  @State changeIndex: number = 0;
  @State changeList: (Length | undefined | null)[] = [
    '18000000px', '9999500px', '1100000px', '16776716px', undefined, null, -1800000000, 1000000
  ];
  @State _Direction: Direction = Direction.Ltr;
  @State chain: boolean = false;
  @State direction_list: Axis = Axis.Vertical;
  @State alignListItem: ListItemAlign = ListItemAlign.Start;
  @State open_scroll: boolean = true;
  listScroller: Scroller = new Scroller();
  @State arr: string[] = [];
  @State press3: number = 0;
  @State drop3: number = 0;
  @State start3: number = 0;
  @State from3: number = 0;
  @State to3: number = 0;

  aboutToAppear(): void {
    for (let i = 0; i < 10; i++) {
      this.arr.push(i.toString());
    }
  }

  build() {
    Column() {
      Button('切换数值')
        .onClick(() => {
          this.changeIndex++;
          if (this.changeIndex > this.changeList.length - 1) {
            this.changeIndex = 0;
          }
        })
      Text('Index' + this.changeIndex + '数值' + this.changeList[this.changeIndex]).fontColor(Color.Blue)
      List({ space: 10, scroller: this.listScroller }) {
        ForEach(this.arr, (item3: number, index3: number) => {
          ListItem() {
            Flex({ direction: FlexDirection.Row, alignItems: ItemAlign.Center }) {
              Column() {
                Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
              }
              .borderRadius(1000)
              .borderColor(Color.Black)
              // 测试点：ListItem组件的width属性设置不同值，ListItem组件是否可拖拽。
              // 预期结果：width属性设置在一定范围内，ListItem组件可拖拽
              .width(this.changeList[this.changeIndex])
              .backgroundColor(Color.Yellow)
              .height('80%')
            }
          }
        }, (item: string) => item)
        //测试点：当元素被移动时触发，记录拖拽元素的原始位置索引和目标位置索引。
          .onMove((from1: number, to1: number) => {
            let temp = this.arr.splice(from1, 1);
            this.arr.splice(to1, 0, temp[0]);
          },
            {
              // 测试点：当元素被长按时触发，记录被长按元素的索引。
              onLongPress: (index: number) => {
                this.press3 = index;
              },
              // 测试点：放下触发，记录放下的目标位置索引
              onDrop: (index: number) => {
                this.drop3 = index;
              },
              // 测试点：开始拖拽时触发，记录起始位置
              onDragStart: (index: number) => {
                this.start3 = index;
              },
              // 测试点：拖拽经过其他元素时触发，记录当前位置和经过的位置索引。
              onMoveThrough: (from: number, Through: number) => {
                this.from3 = from;
                this.to3 = Through;
              }
            }
          )
      }
      .chainAnimation(true)
      .edgeEffect(EdgeEffect.Spring)
      .listDirection(Axis.Horizontal)
      .height('80%')
      .width('100%')
      .borderRadius(10)
      .backgroundColor(0xDCDCDC)
      .height('80%')
    }
  }
}