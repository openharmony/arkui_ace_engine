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

import { LengthMetrics } from '@kit.ArkUI';

// 定义 safeAreaPadding 的 Modifier 类
@Observed
class MyModifier implements AttributeModifier<CommonAttribute> {
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
struct SizeExample10 {
  // 创建 Modifier 实例
  @State private Modifier1: MyModifier = new MyModifier({ top: 5, left: 10, bottom: 15, right: 20 });
  @State private Modifier2: MyModifier = new MyModifier({ top: '5', left: '10', bottom: '15', right: '20' });
  @State private Modifier3: MyModifier = new MyModifier({ top: '5px', left: '10px', bottom: '15px', right: '20px' });
  @State private Modifier4: MyModifier = new MyModifier({ top: '5vp', left: '10vp', bottom: '15vp', right: '20vp' });
  @State private Modifier5: MyModifier = new MyModifier({ top: '5fp', left: '10fp', bottom: '15fp', right: '20fp' });
  @State private Modifier6: MyModifier = new MyModifier({
    top: '5lpx',
    left: '10lpx',
    bottom: '15lpx',
    right: '20lpx'
  });
  @State private Modifier7: MyModifier = new MyModifier({ top: '2%', left: '4%', bottom: '6%', right: '8%' });
  @State private Modifier8: MyModifier = new MyModifier({ top: '', left: '', bottom: '', right: '' });
  @State private Modifier9: MyModifier = new MyModifier({
    top: $r('app.string.size1'),
    left: $r('app.string.size1'),
    bottom: $r('app.string.string'),
    right: $r('app.string.string')
  });
  @State private Modifier10: MyModifier = new MyModifier({
    top: '$%&^^&FG',
    left: '$%&^^&FG',
    bottom: '$%&^^&FG',
    right: '$%&^^&FG'
  });
  @State private Modifier11: MyModifier = new MyModifier({ top: undefined, left: undefined, bottom: 10, right: 10 });
  @State private Modifier12: MyModifier = new MyModifier(undefined);

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
        Text('safeAreaPadding设置组件级安全区 Padding类型场景')
          .fontSize(20).fontWeight(FontWeight.Bold)
        Row(){
          this.SizeWithExample({ top: 5, left: 10, bottom: 15, right: 20 }, 'number:5,10,15,20')
          this.SizeWithExample({ top: '5', left: '10', bottom: '15', right: '20' }, 'string:5,10,15,20')
        }
        Divider()

        Row(){
          this.SizeWithExample({ top: '5px', left: '10px', bottom: '15px', right: '20px' }, '5px,10px,15px,20px')
          this.SizeWithExample({ top: '5vp', left: '10vp', bottom: '15vp', right: '20vp' }, '5vp,10vp,15vp,20vp')
        }
        Divider()

        Row(){
          this.SizeWithExample({ top: '5fp', left: '10fp', bottom: '15fp', right: '20fp' }, '5fp,10fp,15fp,20fp')
          this.SizeWithExample({
            top: '5lpx',
            left: '10lpx',
            bottom: '15lpx',
            right: '20lpx'
          }, '5lpx,10lpx,15lpx,20lpx')
        }
        Divider()

        Row(){
          this.SizeWithExample({ top: '2%', left: '4%', bottom: '6%', right: '8%' }, '2%,4%,6%,8%')
          this.SizeWithExample({ top: '', left: '', bottom: '', right: '' }, '空字符串')
        }
        Divider()

        Row(){
          this.SizeWithExample({
            top: $r('app.string.size1'),
            left: $r('app.string.size1'),
            bottom: $r('app.string.string'),
            right: $r('app.string.string')
          }, '正常和异常资源值')
          this.SizeWithExample({
            top: '$%&^^&FG',
            left: '$%&^^&FG',
            bottom: '$%&^^&FG',
            right: '$%&^^&FG'
          }, '$%&^^&FG')
        }
        Row(){
          this.SizeWithExample({ top: undefined, left: undefined, bottom: 10, right: 10 }, 'undefined,undefined,10,10')
          this.SizeWithExample(undefined, 'undefined')
        }
        Divider()

        Text('safeAreaPadding设置组件级安全区 Padding类型Modifier场景')
          .fontSize(20).fontWeight(FontWeight.Bold)
        Row(){
          this.SizeModifierWithExample(this.Modifier1, 'number:5,10,15,20')
          this.SizeModifierWithExample(this.Modifier2, 'string:5,10,15,20')
        }
        Divider()

        Row(){
          this.SizeModifierWithExample(this.Modifier3, '5px,10px,15px,20px')
          this.SizeModifierWithExample(this.Modifier4, '5vp,10vp,15vp,20vp')
        }
        Divider()

        Row(){
          this.SizeModifierWithExample(this.Modifier5, '5fp,10fp,15fp,20fp')
          this.SizeModifierWithExample(this.Modifier6, '5lpx,10lpx,15lpx,20lpx')
        }
        Divider()

        Row(){
          this.SizeModifierWithExample(this.Modifier7, '2%,4%,6%,8%')
          this.SizeModifierWithExample(this.Modifier8, '空字符串')
        }
        Divider()

        Row(){
          this.SizeModifierWithExample(this.Modifier9, '正常和异常资源值')
          this.SizeModifierWithExample(this.Modifier10, '$%&^^&FG')
        }
        Row(){
          this.SizeModifierWithExample(this.Modifier11, 'undefined,undefined,10,10')
          this.SizeModifierWithExample(this.Modifier12, 'undefined')
        }

      }
      .padding(16)
    }
    .width('100%')
    .height('100%')
  }
}