/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@ComponentV2
struct AlignItemsDemo {
  bgColors: Color[] = [Color.Red, Color.Orange, Color.Yellow, Color.Green, Color.Pink];
  @Param alignment: ItemAlign = ItemAlign.Start; // 接收父组件传入的alignItems属性值

  ToString(alignment: ItemAlign): string {
    switch (alignment) {
      case ItemAlign.Start:
        return "ItemAlign.Start";
      case ItemAlign.Center:
        return "ItemAlign.Center";
      case ItemAlign.End:
        return "ItemAlign.End";
      case ItemAlign.Stretch:
        return "ItemAlign.Stretch";
      default:
        return "ItemAlign.Auto";
    }
  }

  build() {
    Column() {
      Text(this.ToString(this.alignment))
        .fontSize(9)
        .fontColor(0xCCCCCC)
        .width('90%')
        .alignSelf(ItemAlign.Start)
      GridRow({
        columns: 5,
        gutter: { x: 5, y: 10 },
      }) {
        ForEach(this.bgColors, (color: Color, index: number) => {
          GridCol({ span: 1 }) {
            Row() {
            }.width('100%').height(`${(index + 1) * 20}%`) // GridCol设置不同的高度，方便观察alignItems属性的效果
          }.borderColor(color).borderWidth(2)
        })
      }
      .border({ color: '#880606', width: 2 })
      .alignItems(this.alignment)
      .width('100%')
    }
    .height("20%")
  }
}

@Entry
@ComponentV2
struct GridRowExample2 {
  alignmentArray: ItemAlign[] = [ItemAlign.Start, ItemAlign.Center, ItemAlign.End, ItemAlign.Stretch];

  build() {
    Column({ space: 15 }) {
      ForEach(this.alignmentArray, (ele: ItemAlign) => {
        AlignItemsDemo({ alignment: ele })
      })
    }.width('80%').margin({ left: 10, top: 5, bottom: 5 }).height("100%")
  }
}