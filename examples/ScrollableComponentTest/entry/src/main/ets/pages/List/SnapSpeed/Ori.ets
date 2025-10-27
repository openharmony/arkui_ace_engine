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

// xxx.ets
import { ListDataSource } from './ListDataSource';

class SnapSpeedModifier implements AttributeModifier<ListAttribute> {
  snapSpeed: ScrollSnapAnimationSpeed | null | undefined;

  applyNormalAttribute(instance: ListAttribute): void {
    instance.scrollSnapAnimationSpeed(this.snapSpeed);
  }
}

@Entry
@Component
struct ListExample {
  private arr: ListDataSource = new ListDataSource([]);
  private scrollerForList: Scroller = new Scroller();
  @State snapSpeedModifier: SnapSpeedModifier = new SnapSpeedModifier();
  scrollSnap: (ScrollSnapAnimationSpeed | null | undefined)[] = [
    ScrollSnapAnimationSpeed.SLOW,
    ScrollSnapAnimationSpeed.NORMAL,
    null,
    undefined,
    -1,
    999999999,
    -0.5,
  ]
  @State jsIndex: number = 0;
  @State modifierIndex: number = 0;

  aboutToAppear() {
    let list: number[] = [];
    for (let i = 0; i < 60; i++) {
      list.push(i);
    }
    this.arr = new ListDataSource(list);
  }

  build() {
    Column() {
      Row() {
        List({ space: 4, initialIndex: 3, scroller: this.scrollerForList }) {
          LazyForEach(this.arr, (item: number) => {
            ListItem() {
              Text('' + item)
                .width('100%').height('100%').fontSize(16)
                .textAlign(TextAlign.Center)
            }
            .backgroundColor(0xFFFFFF)
            .width(30)
            .height('80%')
            .borderWidth(2)
            .borderColor(Color.Green)
          }, (item: number) => JSON.stringify(item))
        }
        .borderWidth(2)
        .borderColor(Color.Red)
        .edgeEffect(EdgeEffect.Spring)
        .listDirection(Axis.Horizontal)
        .height(100)
        .width('100%')
        .scrollSnapAlign(ScrollSnapAlign.CENTER)
        .scrollSnapAnimationSpeed(this.scrollSnap[this.jsIndex])
        .backgroundColor(0xDCDCDC)
        .alignListItem(ListItemAlign.Center)
      }
      .width('100%')
      .backgroundColor(0xDCDCDC)
      .padding({ top: 10 })

      Row() {
        List({ space: 4, initialIndex: 3, scroller: this.scrollerForList }) {
          LazyForEach(this.arr, (item: number) => {
            ListItem() {
              Text('' + item)
                .width('100%').height('100%').fontSize(16)
                .textAlign(TextAlign.Center)
            }
            .backgroundColor(0xFFFFFF)
            .width(30)
            .height('80%')
            .borderWidth(2)
            .borderColor(Color.Green)
          }, (item: number) => JSON.stringify(item))
        }
        .borderWidth(2)
        .borderColor(Color.Red)
        .edgeEffect(EdgeEffect.Spring)
        .listDirection(Axis.Horizontal)
        .height(100)
        .width('100%')
        .scrollSnapAlign(ScrollSnapAlign.CENTER)
        .attributeModifier(this.snapSpeedModifier)
        .backgroundColor(0xDCDCDC)
        .alignListItem(ListItemAlign.Center)
      }
      .width('100%')
      .backgroundColor(0xDCDCDC)
      .padding({ top: 10 })

      Column({ space: 10 }) {
        Row({ space: 10 }) {
          Button('change js')
            .onClick(() => {
              this.jsIndex = (this.jsIndex + 1) % this.scrollSnap.length;
            })
          Text('current js: ' + this.scrollSnap[this.jsIndex])
        }.alignItems(VerticalAlign.Center)

        Row({ space: 10 }) {
          Button('change modifier')
            .onClick(() => {
              this.modifierIndex = (this.modifierIndex + 1) % this.scrollSnap.length;
              this.snapSpeedModifier.snapSpeed = this.scrollSnap[this.modifierIndex];
            })
          Text('current modifier:' + this.scrollSnap[this.modifierIndex])
        }.alignItems(VerticalAlign.Center)
      }
    }
  }
}

