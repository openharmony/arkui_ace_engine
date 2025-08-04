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

/*用例描述
 1、本用例通过onDidScroll事件获取滚动偏移量，根据滚动偏移量更新子孙组件的translate属性值，
 从而实现滚动过程中子孙组件的显示位置不发生变化。
*/

import { AttributeUpdater, CommonModifier } from '@kit.ArkUI';

@Entry
@Component
struct OnDidScrollAndTranslateExample {
  private scroller: Scroller = new Scroller();
  private arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15];
  private translateOffset: number = 0;
  private myModifier: AttributeUpdater<CommonModifier> = new AttributeUpdater<CommonModifier>();

  build() {
    Scroll(this.scroller) {
      Column() {
        Image($r('app.media.startIcon'))
          .height(50)
          .width(50)
          .zIndex(1)
          .attributeModifier(this.myModifier)
        
        ForEach(this.arr, (item: number) => {
          Text(item.toString())
            .width('90%')
            .height(150)
            .backgroundColor(0xFFFFFF)
            .borderRadius(15)
            .fontSize(16)
            .textAlign(TextAlign.Center)
            .margin({ top: 10 })
        }, (item: number) => item.toString())
      }
      .width('100%')
    }
    .backgroundColor(0xDCDCDC)
    .scrollable(ScrollDirection.Vertical) // 滚动方向纵向
    .scrollBar(BarState.On) // 滚动条常驻显示
    .scrollBarColor(Color.Gray) // 滚动条颜色
    .scrollBarWidth(10) // 滚动条宽度
    .friction(0.6)
    .edgeEffect(EdgeEffect.None)
    .onDidScroll((xOffset: number, yOffset: number, scrollState: ScrollState) => {
      this.translateOffset += yOffset;
      this.myModifier.attribute?.translate({ y: this.translateOffset });
      console.info('yOffset: ' + yOffset + ', translateOffset: ' + this.translateOffset);
    })
  }
}
