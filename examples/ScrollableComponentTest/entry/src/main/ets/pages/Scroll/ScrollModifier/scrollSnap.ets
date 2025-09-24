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

import { common } from '@kit.AbilityKit';

class CustomModifier1 implements AttributeModifier<ScrollAttribute> {
  public changeIndex: number = 0;
  public changeList: (number | Resource | undefined | null)[] = [
    200, 330, undefined, 200, null,
    200, 60, 200, -900
  ];

  applyNormalAttribute(instance: ScrollAttribute): void {
    instance.scrollSnap({
      snapAlign: ScrollSnapAlign.START,
      snapPagination: this.changeList[this.changeIndex],
      enableSnapToStart: true,
      enableSnapToEnd: true
    });
  }
}

@Entry
@Component
struct NestedScroll11 {
  @State listPosition: number = 0; // 0代表滚动到List顶部，1代表中间值，2代表滚动到List底部。
  private arr: number[] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18];
  private scrollerForScroll: Scroller = new Scroller();
  private scrollerForList: Scroller = new Scroller();
  @State isDark: boolean = false;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext;
  @State vOutSetValueTwo: number = 40;
  @State modifier1: CustomModifier1 = new CustomModifier1();
  scroller: Scroller = new Scroller;

  build() {
    Scroll(this.scroller) {

      Column() {
        Column() {
          Button('切换数值')
            .onClick(() => {
              this.modifier1.changeIndex++
              if (this.modifier1.changeIndex > this.modifier1.changeList.length - 1) {
                this.modifier1.changeIndex = 0
              }
            })
          Text('Index' + this.modifier1.changeIndex + '数值' + this.modifier1.changeList[this.modifier1.changeIndex])
            .fontColor(Color.Blue)
        }

        ForEach(this.arr, (item: number) => {
          Text(item.toString())
            .width('90%')
            .height(200)
            .backgroundColor(0xFFFFFF)
            .borderWidth(1)
            .borderColor(Color.Black)
            .borderRadius(15)
            .fontSize(16)
            .textAlign(TextAlign.Center)
        }, (item: string) => item)
      }.width('100%').backgroundColor(0xDCDCDC)
    }
    .backgroundColor(Color.Yellow)
    .height('100%')
    .edgeEffect(EdgeEffect.Spring)
    .attributeModifier(this.modifier1 as CustomModifier1)
  }
}
