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
 *
 * SR: SR20250724533130
 * Description: Improved scroll component layout constraints
 * Writer: renxiaowen
 */
 
@Entry
@Component
struct WaterflowTwoItem {

  /*
   * 用例描述：WaterFlow组件内设置多个FlowItem的height为不同值，验证FlowItem的布局是否正确
   * 关键结构：WaterFlow、FlowItem、height
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
      WaterFlow() {
        FlowItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .width('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Yellow)
          .height(this.changeList[this.changeIndex])
        }

        FlowItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .width('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Orange)
          .height(this.changeList[this.changeIndex])
        }

        FlowItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .width('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Pink)
          .height(this.changeList[this.changeIndex])
        }

        FlowItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .width('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Gray)
          .height(this.changeList[this.changeIndex])
        }

        FlowItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .width('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Green)
          .height(this.changeList[this.changeIndex])
        }

        FlowItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .width('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Blue)
          .height(this.changeList[this.changeIndex])
        }

        FlowItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .width('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Brown)
          .height(this.changeList[this.changeIndex])
        }

        FlowItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .width('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Red)
          .height(this.changeList[this.changeIndex])
        }

        FlowItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .width('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Black)
          .height(this.changeList[this.changeIndex])
        }

        FlowItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .width('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Grey)
          .height(this.changeList[this.changeIndex])
        }

        FlowItem() {
          Button()
        }
      }
      .height('80%')
      .scrollBar(BarState.On)
    }
  }
}