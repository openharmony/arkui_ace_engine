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

// 定义 position 的 Modifier 类
@Observed
class PositionModifier implements AttributeModifier<CommonAttribute> {
  private positionValue: Position | Edges | LocalizedEdges | undefined;
  constructor(value: Position | Edges | LocalizedEdges | undefined) {
    this.positionValue = value;
  }
  applyNormalAttribute(instance: CommonAttribute): void {
    instance.position(this.positionValue);
  }
}

// 定义 markAnchor 的 Modifier 类
@Observed
class MarkAnchorModifier implements AttributeModifier<CommonAttribute> {
  private markAnchorValue: Position | LocalizedPosition | undefined;
  constructor(value: Position | LocalizedPosition | undefined) {
    this.markAnchorValue = value;
  }
  applyNormalAttribute(instance: CommonAttribute): void {
    instance.markAnchor(this.markAnchorValue);
  }
}

// 定义 offset 的 Modifier 类
@Observed
class OffsetModifier implements AttributeModifier<CommonAttribute> {
  private offsetValue: Position | Edges | LocalizedEdges | undefined;
  constructor(value: Position | Edges | LocalizedEdges | undefined) {
    this.offsetValue = value;
  }
  applyNormalAttribute(instance: CommonAttribute): void {
    instance.offset(this.offsetValue);
  }
}

@Entry
@Component
struct PositionExample2 {
  @State private PositionModifier1: PositionModifier = new PositionModifier({ x: 30, y: 10 });
  @State private PositionModifier2: PositionModifier = new PositionModifier({ x: '50%', y: '70%' });
  @State private MarkAnchorModifier1: MarkAnchorModifier = new MarkAnchorModifier({ x: 25, y: 25 });
  @State private MarkAnchorModifier2: MarkAnchorModifier = new MarkAnchorModifier({ x: -100, y: -25 });
  @State private MarkAnchorModifier3: MarkAnchorModifier = new MarkAnchorModifier({ x: 25, y: -25 });
  @State private OffsetModifier1: OffsetModifier = new OffsetModifier({ x: 15, y: 30 });
  @State private OffsetModifier2: OffsetModifier = new OffsetModifier({ x: '-5%', y: '20%' });

  build() {
    Scroll(){
      Column({ space: 20 }) {
        // 设置子组件左上角相对于父组件左上角的偏移位置
        Text('position').fontSize(12).fontColor(0xCCCCCC).width('90%')
        Row() {
          Text('1').size({ width: '30%', height: '50' }).backgroundColor(0xdeb887).border({ width: 1 }).fontSize(16)
            .textAlign(TextAlign.Center)
          Text('2 position(30, 10)')
            .size({ width: '60%', height: '30' })
            .backgroundColor(0xbbb2cb)
            .border({ width: 1 })
            .fontSize(16)
            .align(Alignment.Start)
            .position({ x: 30, y: 10 })
          Text('3').size({ width: '45%', height: '50' }).backgroundColor(0xdeb887).border({ width: 1 }).fontSize(16)
            .textAlign(TextAlign.Center)
          Text('4 position(50%, 70%)')
            .size({ width: '50%', height: '50' })
            .backgroundColor(0xbbb2cb)
            .border({ width: 1 })
            .fontSize(16)
            .position({ x: '50%', y: '70%' })
        }.width('90%').height(100).border({ width: 1, style: BorderStyle.Dashed })

        Text('position Modifier').fontSize(12).fontColor(0xCCCCCC).width('90%')
        Row() {
          Text('1').size({ width: '30%', height: '50' }).backgroundColor(0xdeb887).border({ width: 1 }).fontSize(16)
            .textAlign(TextAlign.Center)
          Text('2 position(30, 10)')
            .size({ width: '60%', height: '30' })
            .backgroundColor(0xbbb2cb)
            .border({ width: 1 })
            .fontSize(16)
            .align(Alignment.Start)
            .attributeModifier(this.PositionModifier1)
          Text('3').size({ width: '45%', height: '50' }).backgroundColor(0xdeb887).border({ width: 1 }).fontSize(16)
            .textAlign(TextAlign.Center)
          Text('4 position(50%, 70%)')
            .size({ width: '50%', height: '50' })
            .backgroundColor(0xbbb2cb)
            .border({ width: 1 })
            .fontSize(16)
            .attributeModifier(this.PositionModifier2)
        }.width('90%').height(100).border({ width: 1, style: BorderStyle.Dashed })

        // 相对于起点偏移，其中x为最终定位点距离起点水平方向间距，x>0往左，反之向右。
        // y为最终定位点距离起点垂直方向间距，y>0向上，反之向下
        Text('markAnchor').fontSize(12).fontColor(0xCCCCCC).width('90%')
        Stack({ alignContent: Alignment.TopStart }) {
          Row()
            .size({ width: '100', height: '100' })
            .backgroundColor(0xdeb887)
          Text('text')
            .fontSize('30px')
            .textAlign(TextAlign.Center)
            .size({ width: 25, height: 25 })
            .backgroundColor(Color.Green)
            .markAnchor({ x: 25, y: 25 })
          Text('text')
            .fontSize('30px')
            .textAlign(TextAlign.Center)
            .size({ width: 25, height: 25 })
            .backgroundColor(Color.Green)
            .markAnchor({ x: -100, y: -25 })
          Text('text')
            .fontSize('30px')
            .textAlign(TextAlign.Center)
            .size({ width: 25, height: 25 })
            .backgroundColor(Color.Green)
            .markAnchor({ x: 25, y: -25 })
        }.margin({ top: 25 }).border({ width: 1, style: BorderStyle.Dashed })

        Text('markAnchor Modifier').fontSize(12).fontColor(0xCCCCCC).width('90%')
        Stack({ alignContent: Alignment.TopStart }) {
          Row()
            .size({ width: '100', height: '100' })
            .backgroundColor(0xdeb887)
          Text('text')
            .fontSize('30px')
            .textAlign(TextAlign.Center)
            .size({ width: 25, height: 25 })
            .backgroundColor(Color.Green)
            .attributeModifier(this.MarkAnchorModifier1)
          Text('text')
            .fontSize('30px')
            .textAlign(TextAlign.Center)
            .size({ width: 25, height: 25 })
            .backgroundColor(Color.Green)
            .attributeModifier(this.MarkAnchorModifier2)
          Text('text')
            .fontSize('30px')
            .textAlign(TextAlign.Center)
            .size({ width: 25, height: 25 })
            .backgroundColor(Color.Green)
            .attributeModifier(this.MarkAnchorModifier3)
        }.margin({ top: 25 }).border({ width: 1, style: BorderStyle.Dashed })

        // 相对定位，x>0向右偏移，反之向左，y>0向下偏移，反之向上
        Text('offset').fontSize(12).fontColor(0xCCCCCC).width('90%')
        Row() {
          Text('1').size({ width: '15%', height: '50' }).backgroundColor(0xdeb887).border({ width: 1 }).fontSize(16)
            .textAlign(TextAlign.Center)
          Text('2  offset(15, 30)')
            .size({ width: 120, height: '50' })
            .backgroundColor(0xbbb2cb)
            .border({ width: 1 })
            .fontSize(16)
            .align(Alignment.Start)
            .offset({ x: 15, y: 30 })
          Text('3').size({ width: '15%', height: '50' }).backgroundColor(0xdeb887).border({ width: 1 }).fontSize(16)
            .textAlign(TextAlign.Center)
          Text('4 offset(-5%, 20%)')
            .size({ width: 100, height: '50' })
            .backgroundColor(0xbbb2cb)
            .border({ width: 1 })
            .fontSize(16)
            .offset({ x: '-5%', y: '20%' })
        }.width('90%').height(100).border({ width: 1, style: BorderStyle.Dashed })

        Text('offset Modifier').fontSize(12).fontColor(0xCCCCCC).width('90%')
        Row() {
          Text('1').size({ width: '15%', height: '50' }).backgroundColor(0xdeb887).border({ width: 1 }).fontSize(16)
            .textAlign(TextAlign.Center)
          Text('2  offset(15, 30)')
            .size({ width: 120, height: '50' })
            .backgroundColor(0xbbb2cb)
            .border({ width: 1 })
            .fontSize(16)
            .align(Alignment.Start)
            .attributeModifier(this.OffsetModifier1)
          Text('3').size({ width: '15%', height: '50' }).backgroundColor(0xdeb887).border({ width: 1 }).fontSize(16)
            .textAlign(TextAlign.Center)
          Text('4 offset(-5%, 20%)')
            .size({ width: 100, height: '50' })
            .backgroundColor(0xbbb2cb)
            .border({ width: 1 })
            .fontSize(16)
            .attributeModifier(this.OffsetModifier2)
        }.width('90%').height(100).border({ width: 1, style: BorderStyle.Dashed })
      }
      .width('100%').margin({ top: 25 })
    }
  }
}