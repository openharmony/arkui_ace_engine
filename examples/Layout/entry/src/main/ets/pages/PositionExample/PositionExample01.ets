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

// 定义 align 的 Modifier 类
@Observed
class AlignModifier implements AttributeModifier<CommonAttribute> {
  private alignValue: Alignment | LocalizedAlignment | undefined | null;
  constructor(value: Alignment | LocalizedAlignment | undefined | null) {
    this.alignValue = value;
  }
  applyNormalAttribute(instance: CommonAttribute): void {
    instance.align(this.alignValue);
  }
}

@Entry
@Component
struct PositionExample1 {
  // 创建 Modifier 实例
  @State private AlignModifier1: AlignModifier = new AlignModifier(Alignment.TopStart);
  @State private AlignModifier2: AlignModifier = new AlignModifier(Alignment.Top);
  @State private AlignModifier3: AlignModifier = new AlignModifier(Alignment.TopEnd);
  @State private AlignModifier4: AlignModifier = new AlignModifier(Alignment.Start);
  @State private AlignModifier5: AlignModifier = new AlignModifier(Alignment.Center);
  @State private AlignModifier6: AlignModifier = new AlignModifier(Alignment.End);
  @State private AlignModifier7: AlignModifier = new AlignModifier(Alignment.BottomStart);
  @State private AlignModifier8: AlignModifier = new AlignModifier(Alignment.Bottom);
  @State private AlignModifier9: AlignModifier = new AlignModifier(Alignment.BottomEnd);
  @State private AlignModifier10: AlignModifier = new AlignModifier(undefined);
  @State private AlignModifier11: AlignModifier = new AlignModifier(null);

  @Builder
  private AlignWithExample(align: Alignment | LocalizedAlignment | undefined | null, tip: string) {
    Column() {
      Text(tip).fontSize(14).fontColor(Color.Gray)
      Stack() {
        Text('This is a text').height('65%').backgroundColor(0xD2B48C)
      }.width('90%').height(50).margin({ top: 5 }).backgroundColor(0xFFE4C4)
      .align(align)
    }
    .margin(10)
    .alignItems(HorizontalAlign.Start)
  }

  @Builder
  private AlignModifierWithExample(modifier: AttributeModifier<CommonAttribute>, tip: string) {
    Column() {
      Text(tip).fontSize(14).fontColor(Color.Gray)
      Stack() {
        Text('This is a text').height('65%').backgroundColor(0xD2B48C)
      }.width('90%').height(50).margin({ top: 5 }).backgroundColor(0xFFE4C4)
      .attributeModifier(modifier)
    }
    .margin(10)
    .alignItems(HorizontalAlign.Start)
  }

  build() {
    Scroll() {
      Column({ space: 10 }) {
        // 元素内容<元素宽高，设置内容在与元素内的对齐方式
        Text('align 对齐方式')
        this.AlignWithExample(Alignment.TopStart, 'Alignment.TopStart')
        this.AlignWithExample(Alignment.Top, 'Alignment.Top')
        this.AlignWithExample(Alignment.TopEnd, 'Alignment.TopEnd')
        this.AlignWithExample(Alignment.Start, 'Alignment.Start')
        this.AlignWithExample(Alignment.Center, 'Alignment.Center')
        this.AlignWithExample(Alignment.End, 'Alignment.End')
        this.AlignWithExample(Alignment.BottomStart, 'Alignment.BottomStart')
        this.AlignWithExample(Alignment.Bottom, 'Alignment.Bottom')
        this.AlignWithExample(Alignment.BottomEnd, 'Alignment.BottomEnd')
        this.AlignWithExample(undefined, 'undefined')
        this.AlignWithExample(null, 'null')

        Text('align Modifier 对齐方式')
        this.AlignModifierWithExample(this.AlignModifier1, 'TopStart')
        this.AlignModifierWithExample(this.AlignModifier2, 'Top')
        this.AlignModifierWithExample(this.AlignModifier3, 'TopEnd')
        this.AlignModifierWithExample(this.AlignModifier4, 'Start')
        this.AlignModifierWithExample(this.AlignModifier5, 'Center')
        this.AlignModifierWithExample(this.AlignModifier6, 'End')
        this.AlignModifierWithExample(this.AlignModifier7, 'TopStart')
        this.AlignModifierWithExample(this.AlignModifier8, 'TopStart')
        this.AlignModifierWithExample(this.AlignModifier9, 'TopStart')
        this.AlignModifierWithExample(this.AlignModifier10, 'undefined')
        this.AlignModifierWithExample(this.AlignModifier11, 'null')

      }.width('100%').margin({ top: 5 })
    }
  }
}
