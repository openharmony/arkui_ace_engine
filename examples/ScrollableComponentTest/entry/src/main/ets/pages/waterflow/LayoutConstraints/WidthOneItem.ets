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
struct WaterflowWidthOneItem {

  /*
   * 用例描述：WaterFlow组件内设置FlowItem的width为不同值，验证FlowItem的布局是否正确
   * 关键结构：
   * |-> WaterFlow
   *    |-> FlowItem
   *       |-> Text
   */

  @State realName: string[][] = [];
  @State changeIndex: number = 0;
  @State changeList: (Length | undefined | null)[] = [
    '18000000px', '1000000px', '16777216px', undefined, null, -1800000000, 1000000
  ];
  scroller: Scroller = new Scroller;

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
      WaterFlow() {
        FlowItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .height('50%')
          .backgroundColor(Color.Yellow)
          // 测试点：FlowItem组件的width属性设置不同值。验证FlowItem的布局是否正确
          // 预期结果：width属性设置在一定范围内，FlowItem组件的布局正常
          .width(this.changeList[this.changeIndex])
        }

        FlowItem() {
          Button()
        }
      }
      .height(500)
      .layoutDirection(FlexDirection.Row)
      .scrollBar(BarState.On)
    }
  }
}