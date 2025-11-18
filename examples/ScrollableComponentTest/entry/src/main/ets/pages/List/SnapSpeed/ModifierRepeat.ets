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

class CustomModifier1 implements AttributeModifier<ListAttribute> {
  speedIndex: number = 0;
  speedList: ( /*ScrollSnapAnimationSpeed |*/  undefined | null | ScrollSnapAnimationSpeed)[] = [
    ScrollSnapAnimationSpeed.SLOW,
    ScrollSnapAnimationSpeed.NORMAL,
    null,
    undefined,
    -1,
    999999999,
    -0.5,
  ]

  applyNormalAttribute(instance: ListAttribute): void {
    console.log('CXN speedIndex222', this.speedIndex)
    instance.scrollSnapAnimationSpeed(this.speedList[this.speedIndex])
  }
}

interface Speed {
  scrollSnapAnimationSpeed: string;
}

interface InspectorInfo {
  $attrs: Speed;
}

@Entry
@Component
struct ListOriExample {
  @State snapSpeedModifier: CustomModifier1 = new CustomModifier1();
  @State arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
  @State arrIndex: number = 10;
  private repeatArr: Array<string> = ['1', '2', '3', '4', '5', '6', '7', '8', '9', '10']; // 数据源
  @State repeatArrIndex: number = 10;
  @State editFlag: boolean = false
  @State listDirectionIndex: number = 0;
  @State listDirection: Axis[] = [Axis.Vertical, Axis.Horizontal];
  @State itemHeight: Length = 40;
  @State itemWidth: Length = '100%';
  @State stackFromEndIndex: number = 0;
  @State stackFromEndChangeList: (boolean | undefined | null)[] = [
    true, false, undefined, null
  ]
  @State modifier1: CustomModifier1 = new CustomModifier1()

  private changeOrientation(isLandscape: boolean) {
    let context = getContext(this) as common.UIAbilityContext;
    window.getLastWindow(context).then((lastWindow) => {
      lastWindow.setPreferredOrientation(isLandscape ? window.Orientation.LANDSCAPE : window.Orientation.PORTRAIT)
    });
  }

  build() {
    Column() {
      List({ space: 20, initialIndex: 0 }) {
        Repeat<string>(this.repeatArr)
          .each((ri: RepeatItem<string>) => {
            ListItemGroup() {
              ListItem() {
                Flex({ direction: FlexDirection.Row, alignItems: ItemAlign.Center }) {
                  Text('' + ri.item)
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
                      if (ri.index != undefined) {
                        this.repeatArr.splice(ri.index, 1);
                        this.editFlag = false;
                      }
                    }).stateEffect(true)
                  }
                }
              }

              ListItem() {
                Flex({ direction: FlexDirection.Row, alignItems: ItemAlign.Center }) {
                  Text('' + ri.item)
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
                      if (ri.index != undefined) {
                        this.repeatArr.splice(ri.index, 1);
                        this.editFlag = false;
                      }
                    }).stateEffect(true)
                  }
                }
              }
            }
          })
          .virtualScroll({ totalCount: this.arr.length }) // 打开懒加载，totalCount为期望加载的数据长度
      }
      .id('list')
      .attributeModifier(this.snapSpeedModifier)
      .scrollSnapAlign(ScrollSnapAlign.CENTER)
      .stackFromEnd(false)
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
      .height('70%')

      Flex({ wrap: FlexWrap.Wrap, space: { main: new LengthMetrics(10), cross: new LengthMetrics(10) } }) {

        Button(`更改Speed${this.snapSpeedModifier.speedIndex + 1}/${this.snapSpeedModifier.speedList.length}`)
          .onClick(() => {
            this.snapSpeedModifier.speedIndex = this.snapSpeedModifier.speedIndex + 1;
            if (this.snapSpeedModifier.speedIndex >= this.snapSpeedModifier.speedList.length) {
              this.snapSpeedModifier.speedIndex = 0;
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
      }
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xDCDCDC)
    .padding({ top: 5 })
  }
}
