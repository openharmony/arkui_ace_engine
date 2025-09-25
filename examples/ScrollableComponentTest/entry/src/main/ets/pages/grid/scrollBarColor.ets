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

import { common, ConfigurationConstant } from '@kit.AbilityKit';

@Entry
@Component
struct GridExample1 {
  @State colors: number[] = [0xFFC0CB, 0xDA70D6, 0x6B8E23, 0x6A5ACD, 0x00FFFF, 0x00FF7F];
  @State numbers: number[] = [];
  @State translateY: number = 0;
  private scroller: Scroller = new Scroller();
  private gridScroller: Scroller = new Scroller();
  private touchDown: boolean = false;
  private listTouchDown: boolean = false;
  private scrolling: boolean = false;
  @State changeIndex: number = 0;
  @State changeList: (Color | number | string | undefined | null)[] = [
    Color.Blue, 0xFFFF00FF, 'rgb(255, 100, 255)', '#FFFF00FF', undefined, null
  ];

  aboutToAppear() {
    for (let i = 0; i < 100; i++) {
      this.numbers.push(i);
    }
  }

  @State isDark: boolean = false;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext;
  @State vOutSetValueTwo: number = 40;

  build() {
    Stack() {
      Column() {
        Row() {
          Text('Head')
        }

        Button('深浅色')
          .onClick(() => {
            if (this.isDark) {
              this.isDark = false;
              this.context.getApplicationContext().setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_LIGHT);
            } else {
              this.isDark = true;
              this.context.getApplicationContext().setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_DARK);
            }
          })
        Button('切换数值')
          .onClick(() => {
            this.changeIndex++;
            if (this.changeIndex > this.changeList.length - 1) {
              this.changeIndex = 0;
            }
          })
        Text('切换数值' + this.changeList[this.changeIndex])
        Column() {
          Grid(this.scroller) {
            GridItem() {
              Text('GoodsTypeList1')
            }
            .backgroundColor(this.colors[0])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList2')
            }
            .backgroundColor(this.colors[1])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList3')
            }
            .backgroundColor(this.colors[2])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList4')
            }
            .backgroundColor(this.colors[3])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList5')
            }
            .backgroundColor(this.colors[4])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList1')
            }
            .backgroundColor(this.colors[0])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList2')
            }
            .backgroundColor(this.colors[1])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList3')
            }
            .backgroundColor(this.colors[2])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList4')
            }
            .backgroundColor(this.colors[3])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList5')
            }
            .backgroundColor(this.colors[4])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList1')
            }
            .backgroundColor(this.colors[0])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList2')
            }
            .backgroundColor(this.colors[1])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList3')
            }
            .backgroundColor(this.colors[2])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList4')
            }
            .backgroundColor(this.colors[3])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList5')
            }
            .backgroundColor(this.colors[4])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList1')
            }
            .backgroundColor(this.colors[0])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList2')
            }
            .backgroundColor(this.colors[1])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList3')
            }
            .backgroundColor(this.colors[2])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList4')
            }
            .backgroundColor(this.colors[3])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList5')
            }
            .backgroundColor(this.colors[4])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList1')
            }
            .backgroundColor(this.colors[0])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList2')
            }
            .backgroundColor(this.colors[1])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList3')
            }
            .backgroundColor(this.colors[2])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList4')
            }
            .backgroundColor(this.colors[3])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList5')
            }
            .backgroundColor(this.colors[4])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList1')
            }
            .backgroundColor(this.colors[0])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList2')
            }
            .backgroundColor(this.colors[1])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList3')
            }
            .backgroundColor(this.colors[2])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList4')
            }
            .backgroundColor(this.colors[3])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList5')
            }
            .backgroundColor(this.colors[4])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList1')
            }
            .backgroundColor(this.colors[0])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList2')
            }
            .backgroundColor(this.colors[1])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList3')
            }
            .backgroundColor(this.colors[2])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList4')
            }
            .backgroundColor(this.colors[3])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList5')
            }
            .backgroundColor(this.colors[4])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList5')
            }
            .backgroundColor(this.colors[4])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList5')
            }
            .backgroundColor(this.colors[4])
            .columnStart(0)
            .columnEnd(1)

            GridItem() {
              Text('GoodsTypeList5')
            }
            .backgroundColor(this.colors[4])
            .columnStart(0)
            .columnEnd(1)
          }
          .columnsTemplate('1fr 1fr 1fr 1fr 1fr 1fr 1fr 1fr 1fr 1fr 1fr 1fr 1fr 1fr 1fr 1fr 1fr 1fr 1fr 1fr 1fr 1fr 1fr 1fr 1fr')
          .columnsGap(10)
          .rowsGap(10)
          .scrollBarWidth(4)
          .scrollBar(BarState.On)
          .scrollBarColor(this.changeList[this.changeIndex])
        }
        .width('100%')
        .height('100%')
        .padding({ left: 10, right: 10 })
      }

      Row() {
        Text('Top')
          .width(30)
          .height(30)
          .borderRadius(50)
      }
      .padding(5)
      .borderRadius(50)
      .backgroundColor('#ffffff')
      .shadow({
        radius: 10,
        color: '#909399',
        offsetX: 1,
        offsetY: 1
      })
      .margin({ right: 22, bottom: 15 })
      .onClick(() => {
        this.scroller.scrollTo({ xOffset: 0, yOffset: 0 });
        this.gridScroller.scrollTo({ xOffset: 0, yOffset: 0 });
      })
    }
    .align(Alignment.BottomEnd)
  }
}
