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
 * Description: List组件限位滚动支持设置动画速度档位
 * Writer: renxiaowen
 */

import common from '@ohos.app.ability.common';
import window from '@ohos.window';
import { LengthMetrics } from '@kit.ArkUI';

interface Speed {
  scrollSnapAnimationSpeed: string;
}

interface InspectorInfo {
  $attrs: Speed;
}

@Entry
@Component
struct ListOriExample {
  @State arr: number[] =
    [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
      31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46]
  @State arrIndex: number = 46;
  @State groupArr: number[] = []
  private repeatArr: Array<string> = []; // 数据源
  @State repeatArrIndex: number = 10;
  private scrollerForList: Scroller = new Scroller();
  @State speedIndex: number = 0;
  @State editFlag: boolean = false
  @State speedList: ( /*ScrollSnapAnimationSpeed |*/  undefined | null | ScrollSnapAnimationSpeed)[] = [

    ScrollSnapAnimationSpeed.SLOW,
    ScrollSnapAnimationSpeed.NORMAL,
    null,
    undefined,
    -1,
    999999999,
    -0.5,
  ]
  @State listDirectionIndex: number = 0;
  @State listDirection: Axis[] = [Axis.Vertical, Axis.Horizontal];
  @State itemHeight: Length = 40;
  @State itemWidth: Length = '100%';

  private changeOrientation(isLandscape: boolean) {
    let context = getContext(this) as common.UIAbilityContext;
    window.getLastWindow(context).then((lastWindow) => {
      lastWindow.setPreferredOrientation(isLandscape ? window.Orientation.LANDSCAPE : window.Orientation.PORTRAIT)
    });
  }

  build() {
    Column() {
      List({ space: 20, initialIndex: 0 }) {
        ForEach(this.arr, (item: number, index?: number) => {
          ListItemGroup() {
            ListItem() {
              Flex({ direction: FlexDirection.Row, alignItems: ItemAlign.Center }) {
                Text('' + item)
                  .width(this.itemWidth)
                  .height(this.itemHeight)
                  .fontSize(16)
                  .textAlign(TextAlign.Center)
                  .borderRadius(10)
                  .backgroundColor(0xFFFFFF)
                if (this.editFlag) {
                  Button() {
                    Text('delete').fontSize(16)
                  }.width('30%').height(40)
                  .onClick(() => {
                    if (index != undefined) {
                      this.arr.splice(index, 1);
                      this.editFlag = false;
                    }
                  }).stateEffect(true)
                }
              }
            }.backgroundColor(Color.Blue)

            ListItem() {
              Flex({ direction: FlexDirection.Row, alignItems: ItemAlign.Center }) {
                Text('' + item)
                  .width(this.itemWidth)
                  .height(this.itemHeight)
                  .fontSize(16)
                  .textAlign(TextAlign.Center)
                  .borderRadius(10)
                  .backgroundColor(0xFFFFFF)
                if (this.editFlag) {
                  Button() {
                    Text('delete').fontSize(16)
                  }.width('30%').height(40)
                  .onClick(() => {
                    if (index != undefined) {
                      this.arr.splice(index, 1);
                      this.editFlag = false;
                    }
                  }).stateEffect(true)
                }
              }
            }.backgroundColor(Color.Blue)
          }
        }, (item: string) => item)

      }
      .id('list')
      .scrollSnapAnimationSpeed(this.speedList[this.speedIndex])
      .scrollSnapAlign(ScrollSnapAlign.CENTER)
      .stackFromEnd(true)
      .listDirection(this.listDirection[this.listDirectionIndex]) // 排列方向
      .scrollBar(BarState.Off)
      .friction(0.6)
      .divider({
        strokeWidth: 2,
        color: 0xFFFFFF,
        startMargin: 20,
        endMargin: 20
      }) // 每行之间的分界线
      .edgeEffect(EdgeEffect.Spring)
      .width('90%')
      .height('30%')

      Flex({ wrap: FlexWrap.Wrap, space: { main: new LengthMetrics(10), cross: new LengthMetrics(10) } }) {

        Button(`更改Speed${this.speedIndex + 1}/${this.speedList.length}`).onClick(() => {
          this.speedIndex = this.speedIndex + 1;
          if (this.speedIndex >= this.speedList.length) {
            this.speedIndex = 0;
          }
        })
        Row({ space: 10 }) {
          Button('getInspectorByKey')
            .onClick(() => {
              let msg = getInspectorByKey('list');
              let a: InspectorInfo = JSON.parse(msg) as InspectorInfo;
              console.log('CXN ', a?.$attrs?.scrollSnapAnimationSpeed);
            })
        }.alignItems(VerticalAlign.Center)

        Button(`更改排列方向`).onClick(() => {
          this.listDirectionIndex = this.listDirectionIndex + 1;
          if (this.listDirectionIndex >= this.listDirection.length) {
            this.listDirectionIndex = 0;
          }

          if (this.listDirection[this.listDirectionIndex] == Axis.Vertical) {
            let val: Length = this.itemHeight;
            this.itemHeight = this.itemWidth;
            this.itemWidth = val;
          }

          if (this.listDirection[this.listDirectionIndex] == Axis.Horizontal) {
            let val: Length = this.itemHeight;
            this.itemHeight = this.itemWidth;
            this.itemWidth = val;
          }
        })

        Button(`添加ListItem`).onClick(() => {
          this.arrIndex++;
          this.arr.push(this.arrIndex);
        })

        Button('删除ListItem')
          .onClick(() => {
            this.editFlag = !this.editFlag;
          }).margin({ top: 5, left: 20 })
      }
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xDCDCDC)
    .padding({ top: 5 })
  }
}
