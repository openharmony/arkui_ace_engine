/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

@Entry
@Component
struct GridWidthTwoItem {
  @State realName: string[][] = [];
  @State changeIndex: number = 0;
  @State changeList: (Length | undefined | null)[] = [
    '180px'
  ]
  scroller: Scroller = new Scroller;

  build() {
    Column() {
      Grid(this.scroller) {
        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .height('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Yellow)
          .width(this.changeList[this.changeIndex])
        }

        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .height('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Orange)
          .width(this.changeList[this.changeIndex])
        }

        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .height('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Red)
          .width(this.changeList[this.changeIndex])
        }

        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .height('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Pink)
          .width(this.changeList[this.changeIndex])
        }

        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .height('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Blue)
          .width(this.changeList[this.changeIndex])
        }

        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .height('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Black)
          .width(this.changeList[this.changeIndex])
        }

        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .height('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Brown)
          .width(this.changeList[this.changeIndex])
        }

        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .height('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Gray)
          .width(this.changeList[this.changeIndex])
        }

        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(1000)
          .borderColor(Color.Black)
          .height('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Green)
          .width(this.changeList[this.changeIndex])
        }

        GridItem() {
          Column() {
            Text('数值' + this.changeList[this.changeIndex]).fontColor(Color.Red)
          }
          .borderRadius(5000)
          .borderColor(Color.Black)
          .height('100%') //TODO 疑问：子组件像素是否需要width也设置
          .backgroundColor(Color.Grey)
          .width(this.changeList[this.changeIndex])
        }

        GridItem() {
          Button()
        }
      }
      .friction(0.1)
      .width('100%')
      .height('80%')
      .rowsTemplate('10fr')
      .rowsGap(20)
      .edgeEffect(EdgeEffect.Spring, { alwaysEnabled: true, effectEdge: EffectEdge.START })
    }
  }
}