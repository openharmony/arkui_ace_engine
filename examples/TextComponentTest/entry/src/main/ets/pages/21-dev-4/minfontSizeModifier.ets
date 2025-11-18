/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import {CommonModifier} from "@ohos.arkui.modifier"
// xxx.ets

class TextModifier1 implements AttributeModifier<TextAttribute> {

  applyNormalAttribute(instance: TextAttribute): void {
    instance
      .width('80%')
      .height(90)
      .fontSize(20)
      .borderWidth(1)
      .minFontSize(10)
      .maxFontSize(30)
      .maxLines(2)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .heightAdaptivePolicy(TextHeightAdaptivePolicy.MAX_LINES_FIRST)
  }
}
class TextModifier2 implements AttributeModifier<TextAttribute> {

  applyNormalAttribute(instance: TextAttribute): void {
    instance
      .width('80%')
      .height(90)
      .borderWidth(1)
      .fontSize(20)
      .minFontSize(10)
      .maxFontSize(30)
      .maxLines(2)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST)
  }
}
class TextModifier3 implements AttributeModifier<TextAttribute> {

  applyNormalAttribute(instance: TextAttribute): void {
    instance
      .width('80%')
      .height(90)
      .borderWidth(1)
      .fontSize(20)
      .minFontSize(30)
      .maxFontSize(50)
      .maxLines(5)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .heightAdaptivePolicy(TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST)
      .margin({bottom:10})
  }
}


@Entry
@Component
struct attributeDemo {
  @State modifier1: TextModifier1 = new TextModifier1()
  @State modifier2: TextModifier2 = new TextModifier2()
  @State modifier3: TextModifier3 = new TextModifier3()

  build() {
    Scroll(){
    Column() {
      Text('多个span组件，部分设置字体大小').fontColor(Color.Green)
      Text(){
        SymbolSpan($r('sys.symbol.ohos_trash'))
        Span('This is the text with the height adaptive policy set.')
        Span('Hello').fontSize(30)
        SymbolSpan($r('sys.symbol.ohos_trash'))
      }
      .attributeModifier(this.modifier1)

      Text(){
        SymbolSpan($r('sys.symbol.ohos_trash'))
        Span('This is the text with the height adaptive policy set.')
        Span('Hello').fontSize(30)
        SymbolSpan($r('sys.symbol.ohos_trash'))
      }
      .attributeModifier(this.modifier2)

      Text(){
        SymbolSpan($r('sys.symbol.ohos_trash'))
        Span('This is the text with the height adaptive policy set.')
        Span('Hello').fontSize(20)
        SymbolSpan($r('sys.symbol.ohos_trash'))
      }
      .attributeModifier(this.modifier3)



    }
  }
  }
}
