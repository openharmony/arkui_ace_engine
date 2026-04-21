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

import { LengthMetrics, LengthUnit } from '@kit.ArkUI';

// 定义 safeAreaPadding 的 Modifier 类
@Observed
class MyModifier1 implements AttributeModifier<CommonAttribute> {
  private safeAreaPaddingValue: Padding | LengthMetrics | LocalizedPadding | undefined;
  constructor(color: Padding | LengthMetrics | LocalizedPadding | undefined) {
    this.safeAreaPaddingValue = color;
  }

  applyNormalAttribute(instance: CommonAttribute): void {
    instance.safeAreaPadding(this.safeAreaPaddingValue);
  }
}

@Entry
@Component
struct SizeExample11 {
  // 创建 Modifier 实例
  @State private Modifier1: MyModifier1 = new MyModifier1(LengthMetrics.vp(20));
  @State private Modifier2: MyModifier1 = new MyModifier1(LengthMetrics.px(20));
  @State private Modifier3: MyModifier1 = new MyModifier1(LengthMetrics.fp(20));
  @State private Modifier4: MyModifier1 = new MyModifier1(LengthMetrics.lpx(20));
  @State private Modifier5: MyModifier1 = new MyModifier1(LengthMetrics.percent(0.1));
  @State private Modifier6: MyModifier1 = new MyModifier1(new LengthMetrics(20, LengthUnit.VP));
  @State private Modifier7: MyModifier1 = new MyModifier1(LengthMetrics.resource($r('app.string.size1')));
  @State private Modifier8: MyModifier1 = new MyModifier1(LengthMetrics.resource($r('app.string.string')));
  @State private Modifier9: MyModifier1 = new MyModifier1(undefined);

  @Builder
  private SizeWithExample(safeAreaPadding: Padding | LengthMetrics | LocalizedPadding | undefined, tip: string) {
    Column() {
      Text(tip).fontSize(14).fontColor(Color.Gray)
      Column() {
        Column()
          .width('100%')
          .height('100%')
          .backgroundColor(Color.Pink)
      }
      .width(100)
      .height(100)
      .backgroundColor(Color.Yellow)
      .borderWidth(10)
      .padding(10)
      .safeAreaPadding(safeAreaPadding)
    }
    .margin(10)
    .alignItems(HorizontalAlign.Start)
  }

  @Builder
  private SizeModifierWithExample(modifier: AttributeModifier<CommonAttribute>, tip: string) {
    Column() {
      Text(tip).fontSize(14).fontColor(Color.Gray)
      Column() {
        Column()
          .width('100%')
          .height('100%')
          .backgroundColor(Color.Pink)
      }
      .width(100)
      .height(100)
      .backgroundColor(Color.Yellow)
      .borderWidth(10)
      .padding(10)
      .attributeModifier(modifier)
    }
    .margin(10)
    .alignItems(HorizontalAlign.Start)
  }

  build() {
    Scroll() {
      Column() {
        Text('safeAreaPadding设置组件级安全区 LengthMetrics类型场景')
          .fontSize(20).fontWeight(FontWeight.Bold)

        Row(){
          this.SizeWithExample(LengthMetrics.vp(20), '20vp')
          this.SizeWithExample(LengthMetrics.px(20), '20px')
        }
        Divider()

        Row(){
          this.SizeWithExample(LengthMetrics.fp(20), '20fp')
          this.SizeWithExample(LengthMetrics.lpx(20), '20lpx')
        }
        Divider()

        Row(){
          this.SizeWithExample(LengthMetrics.percent(0.1), '10%')
          this.SizeWithExample(new LengthMetrics(20, LengthUnit.VP), 'new 20vp')
        }
        Divider()

        Row(){
          this.SizeWithExample(LengthMetrics.resource($r('app.string.size1')), '正常资源值')
          this.SizeWithExample(LengthMetrics.resource($r('app.string.string')), '异常资源值')
        }
        this.SizeWithExample(undefined, 'undefined')

        Text('safeAreaPadding设置组件级安全区 LengthMetrics类型Modifier场景')
          .fontSize(20).fontWeight(FontWeight.Bold)
        Row(){
          this.SizeModifierWithExample(this.Modifier1, '20vp')
          this.SizeModifierWithExample(this.Modifier2, '20px')
        }
        Divider()

        Row(){
          this.SizeModifierWithExample(this.Modifier3, '20fp')
          this.SizeModifierWithExample(this.Modifier4, '20lpx')
        }
        Divider()

        Row(){
          this.SizeModifierWithExample(this.Modifier5, '10%')
          this.SizeModifierWithExample(this.Modifier6, 'new 20vp')
        }
        Divider()

        Row(){
          this.SizeModifierWithExample(this.Modifier7, '正常资源值')
          this.SizeModifierWithExample(this.Modifier8, '异常资源值')
        }
        this.SizeModifierWithExample(this.Modifier9, 'undefined')
      }
      .padding(16)
    }
    .width('100%')
    .height('100%')
  }
}