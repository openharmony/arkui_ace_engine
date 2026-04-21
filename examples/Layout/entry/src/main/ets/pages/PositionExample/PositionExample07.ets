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

// 定义 direction 的 Modifier 类
@Observed
class DirectionModifier implements AttributeModifier<CommonAttribute> {
  private directionValue: Direction | undefined | null;
  constructor(value: Direction | undefined | null ) {
    this.directionValue = value;
  }
  applyNormalAttribute(instance: CommonAttribute): void {
    instance.direction(this.directionValue);
  }
}

@Entry
@Component
struct PositionExample7 {
  // 创建 Modifier 实例
  @State private DirectionModifier1: DirectionModifier = new DirectionModifier(Direction.Ltr);
  @State private DirectionModifier2: DirectionModifier = new DirectionModifier(Direction.Rtl);
  @State private DirectionModifier3: DirectionModifier = new DirectionModifier(Direction.Auto);
  @State private DirectionModifier4: DirectionModifier = new DirectionModifier(undefined);
  @State private DirectionModifier5: DirectionModifier = new DirectionModifier(null);

  @Builder
  private DirectionWithExample(direction: Direction | undefined | null, tip: string) {
    Column() {
      Text(tip).fontSize(14).fontColor(Color.Gray)
      Row() {
        Text('1').height(50).width('25%').fontSize(16).backgroundColor(0xF5DEB3)
        Text('2').height(50).width('25%').fontSize(16).backgroundColor(0xD2B48C)
        Text('3').height(50).width('25%').fontSize(16).backgroundColor(0xF5DEB3)
        Text('4').height(50).width('25%').fontSize(16).backgroundColor(0xD2B48C)
      }
      .width('90%')
      .direction(direction)
    }
    .margin(10)
    .alignItems(HorizontalAlign.Start)
  }

  @Builder
  private DirectionModifierWithExample(modifier: AttributeModifier<CommonAttribute>, tip: string) {
    Column() {
      Text(tip).fontSize(14).fontColor(Color.Gray)
      Row() {
        Text('1').height(50).width('25%').fontSize(16).backgroundColor(0xF5DEB3)
        Text('2').height(50).width('25%').fontSize(16).backgroundColor(0xD2B48C)
        Text('3').height(50).width('25%').fontSize(16).backgroundColor(0xF5DEB3)
        Text('4').height(50).width('25%').fontSize(16).backgroundColor(0xD2B48C)
      }
      .width('90%')
      .attributeModifier(modifier)
    }
    .margin(10)
    .alignItems(HorizontalAlign.Start)
  }

  build() {
    Scroll() {
      Column({ space: 10 }) {
        Text('direction 容器元素内主轴方向上的布局')
        this.DirectionWithExample(Direction.Ltr, 'Ltr')
        this.DirectionWithExample(Direction.Rtl, 'Rtl')
        this.DirectionWithExample(Direction.Auto, 'Auto')
        this.DirectionWithExample(undefined, 'undefined')
        this.DirectionWithExample(null, 'null')

        Text('direction Modifier 容器元素内主轴方向上的布局')
        this.DirectionModifierWithExample(this.DirectionModifier1, 'Ltr')
        this.DirectionModifierWithExample(this.DirectionModifier2, 'Rtl')
        this.DirectionModifierWithExample(this.DirectionModifier3, 'Auto')
        this.DirectionModifierWithExample(this.DirectionModifier4, 'undefined')
        this.DirectionModifierWithExample(this.DirectionModifier5, 'null')

      }.width('100%').margin({ top: 5 })
    }
  }
}