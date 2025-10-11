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

import { LengthMetrics, ScrollModifier } from '@kit.ArkUI';
import { common, ConfigurationConstant } from '@kit.AbilityKit';

class CustomModifier1 implements AttributeModifier<ScrollAttribute> {
  public changeIndex: number = 0;
  public changeList: (Color | number | string | undefined | null)[] = [
    Color.Blue, 0xFFFF00FF, 'rgb(255, 100, 255)', '#FFFF00FF', undefined, null
  ];

  applyNormalAttribute(instance: ScrollAttribute): void {
    instance.scrollBarColor(this.changeList[this.changeIndex])
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
  scroller: Scroller = new Scroller();

  build() {
    Scroll(this.scroller) {

      Column() {
        Column() {
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
              this.modifier1.changeIndex++;
              if (this.modifier1.changeIndex > this.modifier1.changeList.length - 1) {
                this.modifier1.changeIndex = 0;
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
    .scrollBar(BarState.On) // 滚动条常驻显示
    .attributeModifier(this.modifier1 as CustomModifier1)
  }
}
