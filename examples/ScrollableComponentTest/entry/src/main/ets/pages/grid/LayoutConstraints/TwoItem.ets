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
struct GridTwoItem {

  /*
   * 用例描述：Grid组件内设置多个GridItem的height为不同值，验证GridItem的布局是否正确
   * 关键结构：
   * |-> Grid
   *    |-> GridItem
   *       |-> Text
   */

  @State realName: string[][] = [];
  @State changeIndex: number = 0;
  @State changeList: (Length | undefined | null)[] = [
    '18000000px', '9999500px', '1100000px', '16776716px', undefined, null, -1800000000, 1000000
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
      Grid(this.scroller) {
        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .width('100%')
          .backgroundColor(Color.Yellow)
          // 测试点：GridItem组件的height属性设置不同值。验证GridItem的布局是否正确
          .height(this.changeList[this.changeIndex])
        }

        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .width('100%')
          .backgroundColor(Color.Orange)
          // 测试点：GridItem组件的height属性设置不同值。验证GridItem的布局是否正确
          .height(this.changeList[this.changeIndex])
        }

        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .width('100%')
          .backgroundColor(Color.Pink)
          // 测试点：GridItem组件的height属性设置不同值。验证GridItem的布局是否正确
          .height(this.changeList[this.changeIndex])
        }

        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .width('100%')
          .backgroundColor(Color.Green)
          // 测试点：GridItem组件的height属性设置不同值。验证GridItem的布局是否正确
          .height(this.changeList[this.changeIndex])
        }

        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .width('100%')
          .backgroundColor(Color.Blue)
          // 测试点：GridItem组件的height属性设置不同值。验证GridItem的布局是否正确
          .height(this.changeList[this.changeIndex])
        }

        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .width('100%')
          .backgroundColor(Color.Black)
          // 测试点：GridItem组件的height属性设置不同值。验证GridItem的布局是否正确
          .height(this.changeList[this.changeIndex])
        }

        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .width('100%')
          .backgroundColor(Color.Brown)
          // 测试点：GridItem组件的height属性设置不同值。验证GridItem的布局是否正确
          .height(this.changeList[this.changeIndex])
        }

        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .width('100%')
          .backgroundColor(Color.Gray)
          // 测试点：GridItem组件的height属性设置不同值。验证GridItem的布局是否正确
          .height(this.changeList[this.changeIndex])
        }

        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .width('100%')
          .backgroundColor(Color.Red)
          // 测试点：GridItem组件的height属性设置不同值。验证GridItem的布局是否正确
          .height(this.changeList[this.changeIndex])
        }

        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .width('100%')
          .backgroundColor(Color.Grey)
          // 测试点：GridItem组件的height属性设置不同值。验证GridItem的布局是否正确
          .height(this.changeList[this.changeIndex])
        }

        GridItem() {
          Button()
        }
      }
      .friction(0.1)
      .width('100%')
      .height('80%')
      .columnsTemplate('10fr')
      .columnsGap(10)
      .rowsGap(20)
      .edgeEffect(EdgeEffect.Spring, { alwaysEnabled: true, effectEdge: EffectEdge.START })
    }
  }
}