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

import { LengthMetrics, LengthUnit  } from '@kit.ArkUI'

// 定义 safeAreaPadding 的 Modifier 类
@Observed
class MyModifier2 implements AttributeModifier<CommonAttribute> {
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
struct SizeExample12 {
  // 创建 Modifier 实例
  @State private Modifier1: MyModifier2 = new MyModifier2({
    top: LengthMetrics.px(5),
    bottom: LengthMetrics.px(15),
    start: LengthMetrics.px(10),
    end: LengthMetrics.px(20)
  });
  @State private Modifier2: MyModifier2 = new MyModifier2({
    top: LengthMetrics.vp(5),
    bottom: LengthMetrics.vp(15),
    start: LengthMetrics.vp(10),
    end: LengthMetrics.vp(20)
  });
  @State private Modifier3: MyModifier2 = new MyModifier2({
    top: LengthMetrics.fp(5),
    bottom: LengthMetrics.fp(15),
    start: LengthMetrics.fp(10),
    end: LengthMetrics.fp(20)
  });
  @State private Modifier4: MyModifier2 = new MyModifier2({
    top: LengthMetrics.lpx(5),
    bottom: LengthMetrics.lpx(15),
    start: LengthMetrics.lpx(10),
    end: LengthMetrics.lpx(20)
  });
  @State private Modifier5: MyModifier2 = new MyModifier2({
    top: LengthMetrics.percent(0.02),
    bottom: LengthMetrics.percent(0.04),
    start: LengthMetrics.percent(0.06),
    end: LengthMetrics.percent(0.08)
  });
  @State private Modifier6: MyModifier2 = new MyModifier2({
    top: new LengthMetrics(5, LengthUnit.VP),
    bottom: new LengthMetrics(10, LengthUnit.PX),
    start: new LengthMetrics(15, LengthUnit.FP),
    end: new LengthMetrics(20, LengthUnit.LPX),
  });
  @State private Modifier7: MyModifier2 = new MyModifier2({
    top: LengthMetrics.resource($r('app.string.size1')),
    bottom: LengthMetrics.resource($r('app.string.size1')),
    start: LengthMetrics.resource($r('app.string.string')),
    end: LengthMetrics.resource($r('app.string.string'))
  });

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
        Text('safeAreaPadding设置组件级安全区 LocalizedPadding类型场景')
          .fontSize(20).fontWeight(FontWeight.Bold)

        Row(){
          this.SizeWithExample({
            top: LengthMetrics.px(5),
            bottom: LengthMetrics.px(15),
            start: LengthMetrics.px(10),
            end: LengthMetrics.px(20)
          }, '5px,10px,15px,20px')
          this.SizeWithExample({
            top: LengthMetrics.vp(5),
            bottom: LengthMetrics.vp(15),
            start: LengthMetrics.vp(10),
            end: LengthMetrics.vp(20)
          }, '5vp,10vp,15vp,20vp')
        }
        Divider()

        Row(){
          this.SizeWithExample({
            top: LengthMetrics.fp(5),
            bottom: LengthMetrics.fp(15),
            start: LengthMetrics.fp(10),
            end: LengthMetrics.fp(20)
          }, '5fp,10fp,15fp,20fp')
          this.SizeWithExample({
            top: LengthMetrics.lpx(5),
            bottom: LengthMetrics.lpx(15),
            start: LengthMetrics.lpx(10),
            end: LengthMetrics.lpx(20)
          }, '5lpx,10lpx,15lpx,20lpx')
        }
        Divider()

        Row(){
          this.SizeWithExample({
            top: LengthMetrics.percent(0.02),
            bottom: LengthMetrics.percent(0.04),
            start: LengthMetrics.percent(0.06),
            end: LengthMetrics.percent(0.08)
          }, '2%,4%,6%,8%')
          this.SizeWithExample({
            top: new LengthMetrics(5, LengthUnit.VP),
            bottom: new LengthMetrics(10, LengthUnit.PX),
            start: new LengthMetrics(15, LengthUnit.FP),
            end: new LengthMetrics(20, LengthUnit.LPX),
          }, '5vp,10px,15fp,20lpx')
        }
        this.SizeWithExample({
          top: LengthMetrics.resource($r('app.string.size1')),
          bottom: LengthMetrics.resource($r('app.string.size1')),
          start: LengthMetrics.resource($r('app.string.string')),
          end: LengthMetrics.resource($r('app.string.string'))
        }, '正常和异常资源值')

        Text('safeAreaPadding设置组件级安全区 Padding类型Modifier场景')
          .fontSize(20).fontWeight(FontWeight.Bold)

        Row(){
          this.SizeModifierWithExample(this.Modifier1, '5px,10px,15px,20px')
          this.SizeModifierWithExample(this.Modifier2, '5vp,10vp,15vp,20vp')
        }
        Divider()

        Row(){
          this.SizeModifierWithExample(this.Modifier3, '5fp,10fp,15fp,20fp')
          this.SizeModifierWithExample(this.Modifier4, '5lpx,10lpx,15lpx,20lpx')
        }
        Divider()

        Row(){
          this.SizeModifierWithExample(this.Modifier5, '2%,4%,6%,8%')
          this.SizeModifierWithExample(this.Modifier6, '5vp,10px,15fp,20lpx')
        }
        this.SizeModifierWithExample(this.Modifier7, '正常和异常资源值')
      }
      .padding(16)
    }
    .width('100%')
    .height('100%')
  }
}