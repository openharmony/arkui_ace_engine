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

// 定义 color 的 Modifier 类
@Observed
class MyModifier implements AttributeModifier<BlankAttribute> {
  private colorValue: ResourceColor | undefined | null;
  constructor(color: ResourceColor | undefined | null) {
    this.colorValue = color;
  }

  applyNormalAttribute(instance: BlankAttribute): void {
    instance.color(this.colorValue);
  }
}

@Entry
@Component
struct BlankExample3 {
  // 创建 Modifier 实例
  @State private Modifier1: MyModifier = new MyModifier(0x00FF00);
  @State private Modifier2: MyModifier = new MyModifier(Color.Pink);
  @State private Modifier3: MyModifier = new MyModifier('#0000ff');
  @State private Modifier4: MyModifier = new MyModifier('rgb(255, 100, 255)');
  @State private Modifier5: MyModifier = new MyModifier(undefined);
  @State private Modifier6: MyModifier = new MyModifier(null);
  @State private Modifier7: MyModifier = new MyModifier($r('app.color.Gray'));

  @Builder
  private ColorWithExample(color: ResourceColor | undefined | null, tip: string) {
    Column() {
      Text(tip).fontSize(14).fontColor(Color.Gray)
      Row() {
        Text('Bluetooth')
        Blank()
          .color(color)
        Toggle({ type: ToggleType.Switch })
          .margin({ top: 14, bottom: 14, left: 6, right: 6 })
      }
      .width('100%')
      .backgroundColor(0xFFFFFF)
      .borderRadius(15)
      .padding({ left: 12 })
    }
    .margin(10)
    .alignItems(HorizontalAlign.Start)
  }

  @Builder
  private ColorModifierWithExample(modifier: AttributeModifier<BlankAttribute>, tip: string) {
    Column() {
      Text(tip).fontSize(14).fontColor(Color.Gray)
      Row() {
        Text('Bluetooth')
        Blank()
          .attributeModifier(modifier)
        Toggle({ type: ToggleType.Switch })
          .margin({ top: 14, bottom: 14, left: 6, right: 6 })
      }
      .width('100%')
      .backgroundColor(0xFFFFFF)
      .borderRadius(15)
      .padding({ left: 12 })
    }
    .margin(10)
    .alignItems(HorizontalAlign.Start)
  }
  build() {
    Scroll(){
      Column() {
        this.ColorWithExample(0x00FF00, 'number')
        this.ColorWithExample(Color.Pink, 'Color')
        this.ColorWithExample('#0000ff', 'string')
        this.ColorWithExample('rgb(255, 100, 255)', 'stringRgb')
        this.ColorWithExample(undefined, 'undefined')
        this.ColorWithExample(null, 'null')
        this.ColorWithExample($r('app.color.Gray'), '$r')

        Text('Modifier')
          .fontSize(20).fontWeight(FontWeight.Bold)
        this.ColorModifierWithExample(this.Modifier1, 'number')
        this.ColorModifierWithExample(this.Modifier2, 'Color')
        this.ColorModifierWithExample(this.Modifier3, 'string')
        this.ColorModifierWithExample(this.Modifier4, 'stringRgb')
        this.ColorModifierWithExample(this.Modifier5, 'undefined')
        this.ColorModifierWithExample(this.Modifier6, 'null')
        this.ColorModifierWithExample(this.Modifier7, '$r')
      }
      .backgroundColor(0xEFEFEF)
      .padding(20)
    }

  }
}