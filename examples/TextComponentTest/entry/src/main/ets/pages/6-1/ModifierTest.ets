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

import font from '@ohos.font';
import { HyperlinkModifier } from '@ohos.arkui.modifier'
import { ImageSpanModifier } from '@ohos.arkui.modifier'
import { MarqueeModifier } from '@ohos.arkui.modifier'
import { RichEditorModifier } from '@ohos.arkui.modifier'
import { SearchModifier } from '@ohos.arkui.modifier'
import { SpanModifier } from '@ohos.arkui.modifier'
import { TextAreaModifier } from '@ohos.arkui.modifier'
import { TextModifier } from '@ohos.arkui.modifier'
import { TextInputModifier } from '@ohos.arkui.modifier'

interface PageItem {
  color?: number | null | Color | string | Resource,
  objectFit?: number | ImageFit,
  verticalAlign?: ImageSpanAlignment,

}

const testCase1: PageItem[] = [
  {
    color: Color.Pink
  },
  {
    color: 0x008000
  },
  {
    color: 'rgb(255,0,0)'
  },
  {
    color: $r('app.color.blue')
  },
  {
    color: 'rgb(0,0,255)'
  },
  {
    color: -1
  },
  {
    color: null
  }

]

const objectFit1: PageItem[] = [
  {
    objectFit: ImageFit.Contain
  },
  {
    objectFit: ImageFit.Cover
  },
  {
    objectFit: ImageFit.Auto
  },
  {
    objectFit: ImageFit.Fill
  },
  {
    objectFit: ImageFit.ScaleDown
  },
  {
    objectFit: ImageFit.None
  },
  {
    objectFit: 99
  },
  {
    objectFit: 0.5
  },
  {
    objectFit: -99
  },
  {
    objectFit: -0.5
  }
]

const verticalAlign1: PageItem[] = [
  {
    verticalAlign: ImageSpanAlignment.BOTTOM
  },
  {
    verticalAlign: ImageSpanAlignment.TOP
  },
  {
    verticalAlign: ImageSpanAlignment.CENTER
  },
  {
    verticalAlign: ImageSpanAlignment.BASELINE
  }
]

class HyperlinkModifierTest extends HyperlinkModifier{
  isNum: number = 0
  applyNormalAttribute(instance: HyperlinkAttribute): void {
    super.applyNormalAttribute?.(instance);
  }

  public setGroup1(): void {
    this.color(testCase1[this.isNum].color)
  }
}

class ImageSpanModifierTest extends ImageSpanModifier{
  objectFitNum: number = 0
  verticalAlignNum: number = 0
  applyNormalAttribute(instance: ImageSpanAttribute): void {
    super.applyNormalAttribute?.(instance);
  }

  public setGroup1(): void {
    this.objectFit(objectFit1[this.objectFitNum].objectFit)
    this.verticalAlign(verticalAlign1[this.verticalAlignNum].verticalAlign)
  }
}

class MarqueeModifierTest extends MarqueeModifier{
  fontColorNum: number = 0
  applyNormalAttribute(instance: MarqueeAttribute): void {
    super.applyNormalAttribute?.(instance);
  }

  public setGroup1(a?:number | string | Resource,b?:boolean,c?:FontWeight | number | string, d?:Resource | string): void {
    this.fontColor(testCase1[this.fontColorNum].color)
    this.fontSize(a)
    this.allowScale(b)
    this.fontWeight(c)
    this.fontFamily(d)
  }
}

class RichEditorModifierTest extends RichEditorModifier{
  applyNormalAttribute(instance: RichEditorAttribute): void {
    super.applyNormalAttribute?.(instance);
  }

  public setGroup1(a?:CopyOptions): void {
    this.copyOptions(a)
  }
}

class SearchModifierTest extends SearchModifier{
  applyNormalAttribute(instance: SearchAttribute): void {
    super.applyNormalAttribute?.(instance);
  }

  public setGroup1(a?:boolean, b?: string,
                   c?:number | string | Resource,
                   d?:number | null | Color | string | Resource,
                   e?:number | string | Resource,
                   f?:number | null | Color | string | Resource,
                   g?:CancelButtonStyle,
                   h?:number | null | Color | string | Resource,
                   i?:number | string | Resource,
                   j?:number | null | Color | string | Resource,
                   k?:ResourceStr,
                   l?:boolean,
                   m?:number | null | Color | string | Resource,
                   n?:Font,
                   o?:Font,
                   p?:CopyOptions,
                   q?:TextAlign,

  ): void {
    this.selectionMenuHidden(a)
    this.searchButton(b, {
      fontSize: c,
      fontColor: d
    })
    this.caretStyle({
      width: e,
      color: f
    })
    this.cancelButton({
      style: g,
      icon:{
        color: h
      }
    })
    this.searchIcon({
      size: i,
      color: j,
      src: k
    })
    this.enableKeyboardOnFocus(l)
    this.fontColor(m)
    this.placeholderColor(m)
    this.placeholderFont(n)
    this.textFont(o)
    this.copyOption(p)
    this.textAlign(q)
  }
}

class SpanModifierTest extends SpanModifier{
  applyNormalAttribute(instance: SpanAttribute): void {
    super.applyNormalAttribute?.(instance);
  }

  public setGroup1(
    a?:number | string,
    b?:TextCase,
    c?:number | string,
    d?:TextDecorationType,
    e?:number | null | Color | string | Resource,
    f?:number | FontWeight,
    g?:FontStyle,
    h?:number | string | Resource,
    i?:number | null | Color | string | Resource,
    j?:Font,


  ): void {
    this.lineHeight(a)
    this.textCase(b)
    this.letterSpacing(c)
    this.decoration({
      type: d,
      color: e
    })
    this.fontFamily('HarmonyOS Sans')
    this.fontWeight(f)
    this.fontStyle(g)
    this.fontSize(h)
    this.fontColor(i)
    this.font(j)

  }
}

class TextAreaModifierTest extends TextAreaModifier{
  applyNormalAttribute(instance: TextAreaAttribute): void {
    super.applyNormalAttribute?.(instance);
  }

  public setGroup1(
    a?:boolean, b?:number, c?:boolean, d?:number,
    f?:TextContentStyle,
    g?:boolean, h?:BarState, i?:number,
    j?:boolean, k?:CopyOptions,
    l?:number | FontWeight,
    m?:FontStyle,
    n?:number | string | Resource,
    o?:number | null | Color | string | Resource,
    p?:number | null | Color | string | Resource,
    q?:TextAlign,
    r?:Font,
    s?:number | null | Color | string | Resource,
  ): void {
    this.showCounter(a,{
      thresholdPercentage: b,
      highlightBorder: c
    })
    this.maxLines(d)
    this.style(f)
    this.selectionMenuHidden(g)
    this.barState(h)
    this.maxLength(i)
    this.enableKeyboardOnFocus(j)
    this.copyOption(k)
    this.fontFamily('HarmonyOS Sans')
    this.fontWeight(l)
    this.fontStyle(m)
    this.fontSize(n)
    this.fontColor(o)
    this.caretColor(p)
    this.textAlign(q)
    this.placeholderFont(r)
    this.placeholderColor(s)
  }
}

class TextModifierTest extends TextModifier{
  applyNormalAttribute(instance: TextAttribute): void {
    super.applyNormalAttribute?.(instance);
  }

  public setGroup1(
    a?:boolean,
    b?:WordBreak,
    c?:number | string | Resource,
    d?:number,
    e?:number,
    f?:TextHeightAdaptivePolicy,
    g?:number,
    h?:number | null | Color | string | Resource,
    i?:number,
    j?:number,
    k?:CopyOptions,
    l?:number | string,
    m?:TextCase,
    n?:number,
    o?:TextDecorationType,
    p?:number | null | Color | string | Resource,
    q?:number,
    r?:number | FontWeight,
    s?:FontStyle,
    t?:number | string | Resource,
    u?:number | null | Color | string | Resource,
    v?:TextAlign,
    w?:number,
    x?:TextOverflow,
    y?:Font,
  ): void {
    this.draggable(a)
    this.wordBreak(b)
    this.textIndent(c)
    this.maxFontSize(d)
    this.maxLines(e)
    this.heightAdaptivePolicy(f)
    this.shadow({
      radius: g,
      color: h,
      offsetX: i,
      offsetY: j
    })
    this.copyOption(k)
    this.baselineOffset(l)
    this.textCase(m)
    this.letterSpacing(n)
    this.decoration({
      type: o,
      color: p
    })
    this.maxLines(q)
    this.fontFamily('HarmonyOS Sans')
    this.fontWeight(r)
    this.fontStyle(s)
    this.fontSize(t)
    this.fontColor(u)
    this.textAlign(v)
    this.lineHeight(w)
    this.textOverflow({ overflow: x })
    this.font(y)
  }
}

class TextInputModifierTest extends TextInputModifier{
  applyNormalAttribute(instance: TextInputAttribute): void {
    super.applyNormalAttribute?.(instance);
  }

  public setGroup1(
    a?:InputType,b?:EnterKeyType,
    c?:number | FontWeight,
    d?:FontStyle,
    e?:number | string | Resource,
    f?:number | null | Color | string | Resource,
    g?:Font,
    h?:ResourceColor,
    i?:number,
    j?:boolean,
    k?:TextInputStyle,
    l?:boolean,
    m?:BarState,
    n?:boolean,
    o?:number | string,
    p?:number | null | Color | string | Resource,
    q?:number,
    r?:number | null | Color | string | Resource,
    s?:number,
    t?:TextAlign,
    x?:CopyOptions,
    y?:boolean,


  ): void {
    this.type(a)
    this.enterKeyType(b)
    this.fontWeight(c)
    this.fontStyle(d)
    this.fontSize(e)
    this.fontColor(f)
    // this.placeholderFont(g)
    this.placeholderColor(h)
    this.maxLines(i)
    this.showUnderline(j)
    this.showError('Error')
    this.passwordIcon({
      onIconSrc:$r('app.media.no0'),
      offIconSrc: $r('app.media.no1')
    })
    this.style(k)
    this.selectionMenuHidden(l)
    this.barState(m)
    this.enableKeyboardOnFocus(n)
    this.caretStyle({ width:o })
    this.selectedBackgroundColor(p)
    this.caretPosition(q)
    this.caretColor(r)
    this.maxLength(s)
    this.fontFamily('HarmonyOS Sans')
    this.textAlign(t)
    this.copyOption(x)
    this.showPasswordIcon(y)
  }
}


@Entry
@Component
struct ModifierTest11 {
  @State HyperlinkModifierTest: HyperlinkModifier = new HyperlinkModifierTest().color(undefined)
  @State index: number = 0
  private setParam(): void {
    (this.HyperlinkModifierTest as HyperlinkModifierTest).isNum = this.index;
    (this.HyperlinkModifierTest as HyperlinkModifierTest).setGroup1()
  }

  @State ImageSpanModifierTest: ImageSpanModifier = new ImageSpanModifierTest().objectFit(undefined).verticalAlign(undefined)
  @State objectFitIndex: number = 0
  @State verticalAlignIndex: number = 0
  private setParamImageSpan(): void {
    (this.ImageSpanModifierTest as ImageSpanModifierTest).objectFitNum = this.objectFitIndex;
    (this.ImageSpanModifierTest as ImageSpanModifierTest).verticalAlignNum = this.verticalAlignIndex;
    (this.ImageSpanModifierTest as ImageSpanModifierTest).setGroup1()
  }

  @State sizeAll: (number | string | Resource)[] = [16, 10,'20fp','30%',-1,'10abc',$r('app.string.size')]
  @State fontWeight: (FontWeight | number)[] = [100,200,300,400,500,600,700,800,900,0,1000,FontWeight.Lighter,FontWeight.Normal,FontWeight.Regular,FontWeight.Medium,FontWeight.Bold,FontWeight.Bolder]
  @State MarqueeModifierTest: MarqueeModifier = new MarqueeModifierTest().fontColor(undefined).fontSize(undefined).allowScale(undefined)
  @State fontFamily: (Resource | string)[] = ['HarmonyOS Sans','registerFont']
  @State fontColorIndex: number = 0
  @State fontSizeIndex: number = 0
  @State fontWeightIndex: number = 0
  @State fontFamilyIndex: number = 0
  @State allowScale: boolean = false
  private setParamMarquee(): void {
    (this.MarqueeModifierTest as MarqueeModifierTest).fontColorNum = this.fontColorIndex;
    (this.MarqueeModifierTest as MarqueeModifierTest).setGroup1(this.sizeAll[this.fontSizeIndex], this.allowScale, this.fontWeight[this.fontWeightIndex], this.fontFamily[this.fontFamilyIndex])
  }

  controller: RichEditorController = new RichEditorController();
  options: RichEditorOptions = { controller: this.controller };
  @State RichEditorModifierTest: RichEditorModifier = new RichEditorModifierTest()
  @State copyOptions: CopyOptions[] = [CopyOptions.LocalDevice, CopyOptions.None, CopyOptions.InApp, CopyOptions.CROSS_DEVICE]
  @State copyOptionsIndex: number = 0
  private setParamRichEditor(): void {
    (this.RichEditorModifierTest as RichEditorModifierTest).setGroup1(this.copyOptions[this.copyOptionsIndex])
  }

  @State colorAll: (number | null | Color | string | Resource)[] = [Color.Pink, 0x008000,'rgb(255,0,0)',$r('app.color.blue'),-1,null]
  @State widthAll: (number | string)[] = [10, '20fp', -1, '20%']
  @State cancelButton: CancelButtonStyle[] = [CancelButtonStyle.INPUT, CancelButtonStyle.CONSTANT, CancelButtonStyle.INVISIBLE]
  @State textAlign: TextAlign[] = [TextAlign.Center, TextAlign.Start, TextAlign.End, TextAlign.JUSTIFY]
  @State colorIndex: number = 0
  @State fontSizeIndex1: number = 0
  @State widthIndex: number = 0
  @State caretIndex: number = 0
  @State cancelIndex: number = 0
  @State iconSizeIndex: number = 0
  @State iconColorIndex: number = 0
  @State iconSrcIndex: ResourceStr = ''
  @State cancelButtonIndex: number = 0
  @State placeholderColorIndex: number = 0
  @State selectionMenuHidden: boolean = false
  @State enableKeyboardOnFocus: boolean = true
  @State placeholderFont: Font[] = [
    {
      size: 10,
      weight:100,
      family:'HarmonyOS Sans',
      style: FontStyle.Italic
    },{
    size: -1,
    weight: 900,
    family:'HarmonyOS Sans',
    style: FontStyle.Normal
  }
  ]
  @State placeholderFontIndex: number = 0
  @State textFontIndex: number = 0
  @State searchCopyIndex: number = 0
  @State textAlignIndex: number = 1
  @State value: string = 'search'
  @State SearchModifierTest: SearchModifier = new SearchModifierTest()
  private setParamSearch(): void {
    (this.SearchModifierTest as SearchModifierTest).setGroup1(this.selectionMenuHidden, this.value,
      this.sizeAll[this.fontSizeIndex1], this.colorAll[this.colorIndex],
      this.widthAll[this.widthIndex], this.colorAll[this.caretIndex],
      this.cancelButton[this.cancelButtonIndex], this.colorAll[this.cancelIndex],
      this.sizeAll[this.iconSizeIndex], this.colorAll[this.iconColorIndex],
      this.iconSrcIndex, this.enableKeyboardOnFocus,
      this.placeholderColorIndex,
      this.placeholderFont[this.placeholderFontIndex],
      this.placeholderFont[this.textFontIndex],
      this.copyOptions[this.searchCopyIndex],
      this.textAlign[this.textAlignIndex]
    )
  }

  @State SpanModifierTest: SpanModifier = new SpanModifierTest()
  @State textCase: TextCase[] = [TextCase.Normal, TextCase.LowerCase, TextCase.UpperCase]
  @State letterSpacing: (number | string)[] = [-5,0,5,'10fp', '10abc', '20%']
  @State textDecorationType: TextDecorationType[] = [TextDecorationType.Overline, TextDecorationType.LineThrough,TextDecorationType.Underline,TextDecorationType.None,]
  @State lineHeightIndex: number = 0
  @State textCaseIndex: number = 0
  @State letterSpacingIndex: number = 0
  @State textDecorationTypeIndex: number = 0
  @State textDecorationColorIndex: number = 0
  @State spanWeightIndex: number = 0
  @State spanStyle: FontStyle = FontStyle.Normal
  @State spanSizeIndex: number = 0
  @State spanColorIndex: number = 0
  @State spanFontIndex: number = 0
  private setParamSpan(): void {
    (this.SpanModifierTest as SpanModifierTest).setGroup1(
      this.widthAll[this.lineHeightIndex],
      this.textCase[this.textCaseIndex],
      this.letterSpacing[this.letterSpacingIndex],
      this.textDecorationType[this.textDecorationTypeIndex],
      this.colorAll[this.textDecorationColorIndex],
      this.fontWeight[this.spanWeightIndex],
      this.spanStyle,
      this.sizeAll[this.spanSizeIndex],
      this.colorAll[this.spanColorIndex],
      this.placeholderFont[this.spanFontIndex],

    )
  }

  @State TextAreaModifierTest: TextAreaModifier = new TextAreaModifierTest()
  @State showCounter: boolean = false
  @State thresholdPercentage: number = 50
  @State highlightBorder: boolean = true
  @State maxLines: number = 3
  @State textAreaStyle: TextContentStyle = TextContentStyle.DEFAULT
  @State selectionMenu: boolean = false
  @State barState: BarState = BarState.Auto
  @State maxLength: number = 10
  @State enableKeyboard: boolean = true
  @State textAreaCopy: number = 0
  @State textAreaWeight: number = 0
  @State textAreaFontStyle: FontStyle = FontStyle.Normal
  @State textAreaSize: number = 0
  @State textAreaColor: number = 0
  @State textAreaCaret: number = 0
  @State textAreaAlign: number = 0
  @State textAreaPlaFont: number = 0
  @State textAreaPlaColor: number = 0
  private setParamTextArea(): void {
    (this.TextAreaModifierTest as TextAreaModifierTest).setGroup1(
      this.showCounter,
      this.thresholdPercentage,
      this.highlightBorder,
      this.maxLines,
      this.textAreaStyle,
      this.selectionMenu,
      this.barState,
      this.maxLength,
      this.enableKeyboard,
      this.copyOptions[this.textAreaCopy],
      this.fontWeight[this.textAreaWeight],
      this.textAreaFontStyle,
      this.sizeAll[this.textAreaSize],
      this.colorAll[this.textAreaColor],
      this.colorAll[this.textAreaCaret],
      this.textAlign[this.textAreaAlign],
      this.placeholderFont[this.textAreaPlaFont],
      this.colorAll[this.textAreaPlaColor],
    )
  }

  @State colorAll1: (number| Color | string | Resource)[] = [Color.Pink, 0x008000,'rgb(255,0,0)',$r('app.color.blue'),-1]
  @State TextModifierTest : TextModifier = new TextModifierTest ()
  @State draggable1: boolean = false
  @State wordBreak: WordBreak[] = [WordBreak.NORMAL, WordBreak.BREAK_ALL, WordBreak.BREAK_WORD]
  @State wordBreakIndex: number = 2
  @State textIndent: (number | string | Resource)[] = [2, '5vp', '10%', $r('app.string.size')]
  @State textIndentIndex: number = 0
  @State maxFontSize: number = 10
  @State maxLinesText: number = 3
  @State heightAdaptivePolicy: TextHeightAdaptivePolicy[] = [TextHeightAdaptivePolicy.MAX_LINES_FIRST, TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST, TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST]
  @State heightAdaptiveIndex: number = 0
  @State radius: number = 10
  @State textColor: number = 0
  @State offsetX: number = 0
  @State offsetY: number = 0
  @State textCopy: number = 0
  @State baselineOffset: (number | string)[] = [0, 10, -10, '10vp', '10abc']
  @State baselineOffsetIndex: number = 0
  @State textCaseIndex1: number = 0
  @State letterSpacingText: number = 0
  @State decorationType: number = 0
  @State decorationColor: number = 0
  @State maxLinesText1: number = 3
  @State fontWeightText: number = 0
  @State fontStyleText: FontStyle = FontStyle.Normal
  @State fontSizeText: number = 0
  @State fontColorText: number = 0
  @State textAlignIndex1: number = 0
  @State textLineHeight: number = 20
  @State textOverflow: TextOverflow[] = [TextOverflow.None, TextOverflow.Clip, TextOverflow.Ellipsis, TextOverflow.MARQUEE]
  @State textOverflowIndex: number = 0
  @State textFont: number = 0

  private setParamText(): void {
    (this.TextModifierTest as TextModifierTest).setGroup1(
      this.draggable1,
      this.wordBreak[this.wordBreakIndex],
      this.textIndent[this.textIndentIndex],
      this.maxFontSize,
      this.maxLinesText,
      this.heightAdaptivePolicy[this.heightAdaptiveIndex],
      this.radius,
      this.colorAll[this.textColor],
      this.offsetX,
      this.offsetY,
      this.copyOptions[this.textCopy],
      this.baselineOffset[this.baselineOffsetIndex],
      this.textCase[this.textCaseIndex1],
      this.letterSpacingText,
      this.textDecorationType[this.decorationType],
      this.colorAll[this.decorationColor],
      this.maxLinesText1,
      this.fontWeight[this.fontWeightText],
      this.fontStyleText,
      this.sizeAll[this.fontSizeText],
      this.colorAll[this.fontColorText],
      this.textAlign[this.textAlignIndex1],
      this.textLineHeight,
      this.textOverflow[this.textOverflowIndex],
      this.placeholderFont[this.textFont]


    )
  }


  @State TextInputModifierTest: TextInputModifier = new TextInputModifierTest()
  @State type: InputType[] = [InputType.Normal, InputType.Number, InputType.PhoneNumber, InputType.Email, InputType.Password, InputType.NUMBER_PASSWORD, InputType.USER_NAME, InputType.NEW_PASSWORD, InputType.NUMBER_DECIMAL]
  @State typeIndex: number = 0
  @State enterKeyType: EnterKeyType[] = [ EnterKeyType.Go, EnterKeyType.Search, EnterKeyType.Send, EnterKeyType.Next, EnterKeyType.Done, EnterKeyType.PREVIOUS, EnterKeyType.NEW_LINE ]
  @State enterKeyTypeIndex: number = 0
  @State inputWeightIndex: number = 0
  @State inputStyle: FontStyle = FontStyle.Normal
  @State inputSizeIndex: number = 0
  @State inputColorIndex: number = 0
  @State inputPlaFontIndex: number = 0
  @State inputPlaColorIndex: number = 0
  @State inputMaxLines: number = 3
  @State showUnderline: boolean = false
  @State inputStyle1: TextInputStyle = TextInputStyle.Default
  @State selectionMenuHidden1: boolean = false
  @State inputBarState: BarState = BarState.Auto
  @State inputEnableKey: boolean = true
  @State caretWidth: (number | string)[] = [10, '20fp', -1, '20%']
  @State caretWidthIndex: number = 0
  @State selectedBackgroundColor: number = 0

  private setParamTextInput(): void {
    (this.TextInputModifierTest as TextInputModifierTest).setGroup1(
      this.type[this.typeIndex],
      this.enterKeyType[this.enterKeyTypeIndex],
      this.fontWeight[this.inputWeightIndex],
      this.inputStyle,
      this.sizeAll[this.inputSizeIndex],
      this.colorAll[this.inputColorIndex],
      this.placeholderFont[this.inputPlaFontIndex],
      this.colorAll1[this.inputPlaColorIndex],
      this.inputMaxLines,
      this.showUnderline,
      this.inputStyle1,
      this.selectionMenuHidden1,
      this.inputBarState,
      this.inputEnableKey,
      this.caretWidth[this.caretWidthIndex],
      this.selectedBackgroundColor,
    )
  }


  aboutToAppear() {
    font.registerFont({
      familyName: 'registerFont',
      familySrc: $r('app.string.EntryAbility_label')
    })
  }


  build() {
    Scroll() {
      Column({space:10}) {

        Text('Hyperlink color: ' + testCase1[this.index].color)
        Hyperlink('https://example.com/')
          .attributeModifier(this.HyperlinkModifierTest as HyperlinkModifierTest)

        Row() {
          Button('color')
            .width('100%')
            .onClick((event: ClickEvent) => {
              this.setParam()
              // 控制循环
              this.index++
              if (this.index == testCase1.length) {
                this.index = 0
              }
            })
        }.width('80%')

        Divider()

        Text('ImageSpan objectFit: ' + objectFit1[this.objectFitIndex].objectFit + ' verticalAlign: ' + verticalAlign1[this.verticalAlignIndex].verticalAlign)
        Text() {
          Span('测试文字')
          ImageSpan($r('app.media.icon'))
            .width('200px')
            .height('200px')
            .attributeModifier(this.ImageSpanModifierTest as ImageSpanModifierTest)
          Span('测试文字')
        }


        Row() {
          Button('objectFit')
            .width('50%')
            .onClick(() => {
              this.setParamImageSpan()
              // 控制循环
              this.objectFitIndex++
              if (this.objectFitIndex == objectFit1.length) {
                this.objectFitIndex = 0
              }
            })
          Button('verticalAlign')
            .width('50%')
            .onClick(() => {
              this.setParamImageSpan()
              // 控制循环
              this.verticalAlignIndex++
              if (this.verticalAlignIndex == verticalAlign1.length) {
                this.verticalAlignIndex = 0
              }
            })
        }.width('80%')

        Divider()

        Text('Marquee fontColor: ' + testCase1[this.fontColorIndex].color + '\nfontSize: ' + this.sizeAll[this.fontSizeIndex] + '\nallowScale:' + this.allowScale + '\nfontWeight: ' + this.fontWeight[this.fontWeightIndex] + '\nfontFamily: ' + this.fontFamily[this.fontFamilyIndex])
        Marquee({ start: true, src:'蜀道难难难难难难难难难难难难难难难难难难难难难！！！！！！'})
          .attributeModifier(this.MarqueeModifierTest as MarqueeModifierTest)

        Row() {
          Button('fontColor')
            .width('50%')
            .onClick(() => {
              this.setParamMarquee()
              // 控制循环
              this.fontColorIndex = (this.fontColorIndex + 1) % testCase1.length
            })
          Button('fontSize')
            .width('50%')
            .onClick(() => {
              this.setParamMarquee()
              // 控制循环
              this.fontSizeIndex = (this.fontSizeIndex + 1) % this.sizeAll.length
            })
        }.width('80%')

        Row() {
          Button('allowScale')
            .width('50%')
            .onClick(() => {
              this.allowScale = !this.allowScale
              this.setParamMarquee()

            })
          Button('fontWeight')
            .width('50%')
            .onClick(() => {
              this.setParamMarquee()
              // 控制循环
              this.fontWeightIndex = (this.fontWeightIndex + 1) % this.fontWeight.length
            })
        }.width('80%')

        Row() {
          Button('fontFamily')
            .width('100%')
            .onClick(() => {
              this.setParamMarquee()
              // 控制循环
              this.fontFamilyIndex = (this.fontFamilyIndex + 1) % this.fontFamily.length

            })
        }.width('80%')

        Divider()

        Text('RichEditor copyOptions: ' + this.copyOptions[this.copyOptionsIndex])
        RichEditor(this.options).borderWidth(1).height(50)
          .attributeModifier(this.RichEditorModifierTest as RichEditorModifierTest)

        Row() {
          Button('copyOptions')
            .width('100%')
            .onClick(() => {
              this.setParamRichEditor()
              // 控制循环
              this.copyOptionsIndex = (this.copyOptionsIndex + 1) % this.copyOptions.length

            })
        }.width('80%')

        Divider()

        Text('Search fontSize: ' + this.sizeAll[this.fontSizeIndex1] +
          '\nsearchButtonColor' + this.colorAll[this.colorIndex] +
          '\ncaretWidth' + this.widthAll[this.widthIndex] +
          '\ncaretColor' + this.colorAll[this.caretIndex] +
          '\nCancelButtonStyle' + this.cancelButton[this.cancelButtonIndex] +
          '\nCancelColor' + this.colorAll[this.cancelIndex] +
          '\niconSize' + this.sizeAll[this.iconSizeIndex] +
          '\niconColor' + this.colorAll[this.iconColorIndex] +
          '\ncopyOptions' + this.copyOptions[this.searchCopyIndex] +
          '\ntextAlign' + this.textAlign[this.textAlignIndex]
        )
        Search({placeholder:'in your word...'})
          .attributeModifier(this.SearchModifierTest as SearchModifierTest)

        Row() {
          Button('selectionMenuHidden' + this.selectionMenuHidden)
            .width('100%')
            .onClick(() => {
              this.selectionMenuHidden = !this.selectionMenuHidden
              this.setParamSearch()

            })
        }.width('80%')

        Row() {
          Button('value: search')
            .width('50%')
            .onClick(() => {
              this.value = 'search'
              this.setParamSearch()
            })
          Button('value: 搜索')
            .width('50%')
            .onClick(() => {
              this.value = '搜索'
              this.setParamSearch()
            })
        }.width('80%')

        Row() {
          Button('fontSize')
            .width('50%')
            .onClick(() => {
              this.setParamSearch()
              this.fontSizeIndex1 = (this.fontSizeIndex1 + 1) % this.sizeAll.length
            })

          Button('searchButtonColor')
            .width('50%')
            .onClick(() => {
              this.setParamSearch()
              this.colorIndex = (this.colorIndex + 1) % this.colorAll.length
            })
        }.width('80%')

        Row() {
          Button('caretWidth')
            .width('50%')
            .onClick(() => {
              this.setParamSearch()
              this.widthIndex = (this.widthIndex + 1) % this.widthAll.length
            })

          Button('caretColor')
            .width('50%')
            .onClick(() => {
              this.setParamSearch()
              this.caretIndex = (this.caretIndex + 1) % this.colorAll.length
            })
        }.width('80%')

        Row() {
          Button('CancelButtonStyle')
            .width('50%')
            .onClick(() => {
              this.setParamSearch()
              this.cancelButtonIndex = (this.cancelButtonIndex + 1) % this.cancelButton.length
            })

          Button('cancelColor')
            .width('50%')
            .onClick(() => {
              this.setParamSearch()
              this.cancelIndex = (this.cancelIndex + 1) % this.colorAll.length
            })
        }.width('80%')

        Row() {
          Button('iconSize')
            .width('50%')
            .onClick(() => {
              this.setParamSearch()
              this.iconSizeIndex = (this.iconSizeIndex + 1) % this.sizeAll.length
            })

          Button('iconColor')
            .width('50%')
            .onClick(() => {
              this.setParamSearch()
              this.iconColorIndex = (this.iconColorIndex + 1) % this.colorAll.length
            })
        }.width('80%')

        Row() {
          Button('iconSrc: ""')
            .width('50%')
            .onClick(() => {
              this.iconSrcIndex = ''
              this.setParamSearch()
            })

          Button('iconSrc: Res')
            .width('50%')
            .onClick(() => {
              this.iconSrcIndex = $r('app.media.app_icon')
              this.setParamSearch()
            })
        }.width('80%')

        Row() {
          Button('enableKeyboardOnFocus: ' + this.enableKeyboardOnFocus)
            .width('100%')
            .onClick(() => {
              this.enableKeyboardOnFocus = !this.enableKeyboardOnFocus
              this.setParamSearch()
            })

        }.width('80%')

        Row() {
          Button('fontColor/placeholderColor:' + this.placeholderColorIndex)
            .width('100%')
            .onClick(() => {
              this.setParamSearch()
              this.placeholderColorIndex = (this.placeholderColorIndex + 1) % this.colorAll.length
            })
        }.width('80%')

        Row() {
          Button('placeholderFont' + this.placeholderFontIndex)
            .width('100%')
            .onClick(() => {
              this.setParamSearch()
              this.placeholderFontIndex = (this.placeholderFontIndex + 1) % this.placeholderFont.length
            })
        }.width('80%')

        Row() {
          Button('textFont' + this.textFontIndex)
            .width('50%')
            .onClick(() => {
              this.setParamSearch()
              this.textFontIndex = (this.textFontIndex + 1) % this.placeholderFont.length
            })
          Button('copyOptions: ' + this.copyOptions[this.searchCopyIndex])
            .width('50%')
            .onClick(() => {
              this.setParamSearch()
              this.searchCopyIndex = (this.searchCopyIndex + 1) % this.copyOptions.length
            })
        }.width('80%')

        Row() {
          Button('textAlign')
            .width('100%')
            .onClick(() => {
              this.setParamSearch()
              this.textAlignIndex = (this.textAlignIndex + 1) % this.textAlign.length
            })
        }.width('80%')

        Divider()

        Text(
          'span lineHeight: ' + this.widthAll[this.lineHeightIndex] +
            '\ntextCase' + this.textCase[this.textCaseIndex] +
            '\nLetterSpacing' + this.letterSpacing[this.letterSpacingIndex] +
            '\nDecorationType' + this.textDecorationType[this.textDecorationTypeIndex] +
            '\nDecorationColor' + this.colorAll[this.textDecorationColorIndex] +
            '\nfontWeight' + this.fontWeight[this.spanWeightIndex] +
            '\nfontSize' + this.sizeAll[this.spanSizeIndex] +
            '\nfontColor' + this.colorAll[this.spanColorIndex]
        )
        Text() {
          Span('测试文字')
            .attributeModifier(this.SpanModifierTest as SpanModifierTest)
        }

        Row() {
          Button('lineHeight')
            .width('50%')
            .onClick(() => {
              this.setParamSpan()
              this.lineHeightIndex = (this.lineHeightIndex + 1) % this.widthAll.length
            })

          Button('textCase')
            .width('50%')
            .onClick(() => {
              this.setParamSpan()
              this.textCaseIndex = (this.textCaseIndex + 1) % this.textCase.length
            })
        }.width('80%')

        Row() {
          Button('LetterSpacing')
            .width('50%')
            .onClick(() => {
              this.setParamSpan()
              this.letterSpacingIndex = (this.letterSpacingIndex + 1) % this.letterSpacing.length
            })

          Button('fontWeight')
            .width('50%')
            .onClick(() => {
              this.setParamSpan()
              this.spanWeightIndex = (this.spanWeightIndex + 1) % this.fontWeight.length
            })

        }.width('80%')

        Row() {
          Button('DecorationType')
            .width('50%')
            .onClick(() => {
              this.setParamSpan()
              this.textDecorationTypeIndex = (this.textDecorationTypeIndex + 1) % this.textDecorationType.length
            })

          Button('DecorationColor')
            .width('50%')
            .onClick(() => {
              this.setParamSpan()
              this.textDecorationColorIndex = (this.textDecorationColorIndex + 1) % this.colorAll.length
            })

        }.width('80%')

        Row() {
          Button('fontStyle Normal')
            .width('50%')
            .onClick(() => {
              this.spanStyle = FontStyle.Normal
              this.setParamSpan()
            })

          Button('fontStyle Italic')
            .width('50%')
            .onClick(() => {
              this.spanStyle = FontStyle.Italic
              this.setParamSpan()
            })

        }.width('80%')

        Row() {
          Button('fontSize')
            .width('50%')
            .onClick(() => {
              this.setParamSpan()
              this.spanSizeIndex = (this.spanSizeIndex + 1) % this.sizeAll.length
            })

          Button('fontColor')
            .width('50%')
            .onClick(() => {
              this.setParamSpan()
              this.spanColorIndex = (this.spanColorIndex + 1) % this.colorAll.length
            })
        }.width('80%')

        Row() {
          Button('font')
            .width('100%')
            .onClick(() => {
              this.setParamSearch()
              this.spanFontIndex = (this.spanFontIndex + 1) % this.placeholderFont.length
            })
        }.width('80%')

        Divider()

        Text(
          'TextArea showCounter: ' + this.showCounter +
            'thresholdPercentage: ' + this.thresholdPercentage
        )
        TextArea({placeholder:'in your word...'})
          .attributeModifier(this.TextAreaModifierTest as TextAreaModifierTest)

        Row() {
          Button('showCounter')
            .width('50%')
            .onClick(() => {
              this.showCounter = !this.showCounter
              this.setParamTextArea()
            })
          Button('thresholdPercentage:10')
            .width('50%')
            .onClick(() => {
              this.thresholdPercentage = 10
              this.setParamTextArea()
            })
        }.width('80%')

        Row() {
          Button('thresholdPercentage:50')
            .width('50%')
            .onClick(() => {
              this.thresholdPercentage = 50
              this.setParamTextArea()
            })
          Button('thresholdPercentage:-10')
            .width('50%')
            .onClick(() => {
              this.thresholdPercentage = -10
              this.setParamTextArea()
            })
        }.width('80%')

        Row() {
          Button('highlightBorder')
            .width('100%')
            .onClick(() => {
              this.highlightBorder = !this.highlightBorder
              this.setParamTextArea()
            })

        }.width('80%')

        Row() {
          Button('maxLines: 3')
            .width('50%')
            .onClick(() => {
              this.maxLines = 3
              this.setParamTextArea()
            })

          Button('maxLines: -1')
            .width('50%')
            .onClick(() => {
              this.maxLines = -1
              this.setParamTextArea()
            })
        }.width('80%')

        Row() {
          Button('style: DEFAULT')
            .width('50%')
            .onClick(() => {
              this.textAreaStyle = TextContentStyle.DEFAULT
              this.setParamTextArea()
            })

          Button('style: INLINE')
            .width('50%')
            .onClick(() => {
              this.textAreaStyle = TextContentStyle.INLINE
              this.setParamTextArea()
            })
        }.width('80%')

        Row() {
          Button('selectionMenuHidden: ' + this.selectionMenu)
            .width('100%')
            .onClick(() => {
              this.selectionMenu = !this.selectionMenu
              this.setParamTextArea()
            })
        }.width('80%')

        Row() {
          Button('BarState:Auto')
            .width('30%')
            .onClick(() => {
              this.barState = BarState.Auto
              this.setParamTextArea()
            })
          Button('BarState:Off')
            .width('30%')
            .onClick(() => {
              this.barState = BarState.Off
              this.setParamTextArea()
            })
          Button('BarState:On')
            .width('30%')
            .onClick(() => {
              this.barState = BarState.On
              this.setParamTextArea()
            })
        }.width('80%')

        Row() {
          Button('maxLength:10')
            .width('50%')
            .onClick(() => {
              this.maxLength = 10
              this.setParamTextArea()
            })
          Button('maxLength:-1')
            .width('50%')
            .onClick(() => {
              this.maxLength = -1
              this.setParamTextArea()
            })
        }.width('80%')

        Row() {
          Button('enableKeyboardOnFocus: ' + this.enableKeyboard)
            .width('100%')
            .onClick(() => {
              this.enableKeyboard = !this.enableKeyboard
              this.setParamTextArea()
            })
        }.width('80%')

        Row() {
          Button('copyOptions')
            .width('50%')
            .onClick(() => {
              this.setParamTextArea()
              this.textAreaCopy = (this.textAreaCopy + 1) % this.copyOptions.length
            })
          Button('fontWeight')
            .width('50%')
            .onClick(() => {
              this.setParamTextArea()
              this.textAreaWeight = (this.textAreaWeight + 1) % this.fontWeight.length
            })
        }.width('80%')

        Row() {
          Button('fontStyle Normal')
            .width('50%')
            .onClick(() => {
              this.textAreaFontStyle = FontStyle.Normal
              this.setParamTextArea()
            })
          Button('fontStyle Italic')
            .width('50%')
            .onClick(() => {
              this.textAreaFontStyle = FontStyle.Italic
              this.setParamTextArea()
            })
        }.width('80%')

        Row() {
          Button('fontSize')
            .width('50%')
            .onClick(() => {
              this.setParamTextArea()
              this.textAreaSize = (this.textAreaSize + 1) % this.sizeAll.length
            })
          Button('fontColor')
            .width('50%')
            .onClick(() => {
              this.setParamTextArea()
              this.textAreaColor = (this.textAreaColor + 1) % this.colorAll.length
            })
        }.width('80%')

        Row() {
          Button('caretColor')
            .width('50%')
            .onClick(() => {
              this.setParamTextArea()
              this.textAreaCaret = (this.textAreaCaret + 1) % this.colorAll.length
            })
          Button('textAlign')
            .width('50%')
            .onClick(() => {
              this.setParamTextArea()
              this.textAreaAlign = (this.textAreaAlign + 1) % this.textAlign.length
            })
        }.width('80%')

        Row() {
          Button('placeholderFont')
            .width('50%')
            .onClick(() => {
              this.setParamTextArea()
              this.textAreaPlaFont = (this.textAreaPlaFont + 1) % this.placeholderFont.length
            })
          Button('placeholderColor')
            .width('50%')
            .onClick(() => {
              this.setParamTextArea()
              this.textAreaPlaColor = (this.textAreaPlaColor + 1) % this.colorAll.length
            })
        }.width('80%')

        Divider()

        Text()
        Text('蜀道难难难难难难难难难难难难难难难难难难难难难！！！！！！').borderWidth(1)
          .attributeModifier(this.TextModifierTest as TextModifierTest)

        Row() {
          Button('draggable: ' + this.draggable1)
            .width('50%')
            .onClick(() => {
              this.draggable1 = !this.draggable1
              this.setParamText()
            })
          Button('wordBreak: ' + this.wordBreak[this.wordBreakIndex])
            .width('50%')
            .onClick(() => {
              this.wordBreakIndex = (this.wordBreakIndex + 1) % this.wordBreak.length
              this.setParamText()
            })
        }.width('80%')

        Row() {
          Button('textIndent: ' + this.textIndent[this.textIndentIndex])
            .width('50%')
            .onClick(() => {
              this.textIndentIndex = (this.textIndentIndex + 1) % this.textIndent.length
              this.setParamText()
            })
        }.width('80%')

        Row() {
          Button('maxFontSize: 30')
            .width('50%')
            .onClick(() => {
              this.maxFontSize = 30
              this.setParamText()
            })
          Button('maxFontSize: 10')
            .width('50%')
            .onClick(() => {
              this.maxFontSize = 10
              this.setParamText()
            })
        }.width('80%')

        Row() {
          Button('heightAdaptivePolicy: ' + this.heightAdaptivePolicy[this.heightAdaptiveIndex])
            .width('100%')
            .onClick(() => {
              this.heightAdaptiveIndex = (this.heightAdaptiveIndex + 1) % this.heightAdaptivePolicy.length
              this.setParamText()
            })
        }.width('80%')

        Row() {
          Button('radius:10')
            .width('33%')
            .onClick(() => {
              this.radius = 10
              this.setParamText()
            })
          Button('radius:0')
            .width('33%')
            .onClick(() => {
              this.radius = 0
              this.setParamText()
            })
          Button('radius:-1')
            .width('33%')
            .onClick(() => {
              this.radius = -1
              this.setParamText()
            })
        }.width('80%')

        Row() {
          Button('shadowColor: ' + this.colorAll[this.textColor])
            .width('50%')
            .onClick(() => {
              this.textColor = (this.textColor + 1) % this.colorAll.length
              this.setParamText()
            })

          Button('copyOptions: ' + this.copyOptions[this.textCopy])
            .width('50%')
            .onClick(() => {
              this.textCopy = (this.textCopy + 1) % this.copyOptions.length
              this.setParamText()
            })
        }.width('80%')

        Row() {
          Button('offsetXY:10')
            .width('33%')
            .onClick(() => {
              this.offsetX = 10
              this.offsetY = 10
              this.setParamText()
            })
          Button('offsetXY:0')
            .width('33%')
            .onClick(() => {
              this.offsetX = 0
              this.offsetY = 0
              this.setParamText()
            })
          Button('offsetXY:-10')
            .width('33%')
            .onClick(() => {
              this.offsetX = -10
              this.offsetY = -10
              this.setParamText()
            })
        }.width('80%')

        Row() {
          Button('baselineOffset: ' + this.baselineOffset[this.baselineOffsetIndex])
            .width('50%')
            .onClick(() => {
              this.baselineOffsetIndex = (this.baselineOffsetIndex + 1) % this.baselineOffset.length
              this.setParamText()
            })

          Button('textCase: ' + this.textCase[this.textCaseIndex1])
            .width('50%')
            .onClick(() => {
              this.textCaseIndex1 = (this.textCaseIndex1 + 1) % this.textCase.length
              this.setParamText()
            })
        }.width('80%')

        Row() {
          Button('letterSpacing:-5')
            .width('33%')
            .onClick(() => {
              this.letterSpacingText = -5
              this.setParamText()
            })

          Button('letterSpacing:0')
            .width('33%')
            .onClick(() => {
              this.letterSpacingText = 0
              this.setParamText()
            })

          Button('letterSpacing:2')
            .width('33%')
            .onClick(() => {
              this.letterSpacingText = 2
              this.setParamText()
            })

        }.width('80%')

        Row() {
          Button('decorationType: ' + this.textDecorationType[this.decorationType])
            .width('100%')
            .onClick(() => {
              this.decorationType = (this.decorationType + 1) % this.textDecorationType.length
              this.setParamText()
            })
        }.width('80%')

        Row() {
          Button('decorationColor: ' + this.colorAll[this.decorationColor])
            .width('100%')
            .onClick(() => {
              this.decorationColor = (this.decorationColor + 1) % this.colorAll.length
              this.setParamText()
            })
        }.width('80%')

        Row() {
          Button('maxLines:-1')
            .width('50%')
            .onClick(() => {
              this.maxLinesText1 = -1
              this.setParamText()
            })
          Button('maxLines:0')
            .width('50%')
            .onClick(() => {
              this.maxLinesText1 = 0
              this.setParamText()
            })
        }.width('80%')

        Row() {
          Button('maxLines:3')
            .width('50%')
            .onClick(() => {
              this.maxLinesText1 = 3
              this.setParamText()
            })
          Button('maxLines:5')
            .width('50%')
            .onClick(() => {
              this.maxLinesText1 = 5
              this.setParamText()
            })
        }.width('80%')

        Row() {
          Button('fontWeight: ' + this.fontWeight[this.fontWeightText])
            .width('100%')
            .onClick(() => {
              this.fontWeightText = (this.fontWeightText + 1) % this.fontWeight.length
              this.setParamText()
            })
        }.width('80%')

        Row() {
          Button('fontStyle: Normal')
            .width('50%')
            .onClick(() => {
              this.fontStyleText = FontStyle.Normal
              this.setParamText()
            })
          Button('fontStyle: Italic')
            .width('50%')
            .onClick(() => {
              this.fontStyleText = FontStyle.Italic
              this.setParamText()
            })
        }.width('80%')

        Row() {
          Button('fontSize: ' + this.sizeAll[this.fontSizeText])
            .width('50%')
            .onClick(() => {
              this.fontSizeText = (this.fontSizeText + 1) % this.sizeAll.length
              this.setParamText()
            })

          Button('fontColor: ' + this.colorAll[this.fontColorText])
            .width('50%')
            .onClick(() => {
              this.fontColorText = (this.fontColorText + 1) % this.colorAll.length
              this.setParamText()
            })
        }.width('80%')

        Row() {
          Button('textAlign: ' + this.textAlign[this.textAlignIndex1])
            .width('50%')
            .onClick(() => {
              this.textAlignIndex1 = (this.textAlignIndex1 + 1) % this.textAlign.length
              this.setParamText()
            })

          Button('fontColor: ' + this.colorAll[this.fontColorText])
            .width('50%')
            .onClick(() => {
              this.fontColorText = (this.fontColorText + 1) % this.colorAll.length
              this.setParamText()
            })
        }.width('80%')

        Row() {
          Button('lineHeight: 10')
            .width('33%')
            .onClick(() => {
              this.textLineHeight = 10
              this.setParamText()
            })
          Button('lineHeight: -1')
            .width('33%')
            .onClick(() => {
              this.textLineHeight = -1
              this.setParamText()
            })
          Button('lineHeight: 20')
            .width('33%')
            .onClick(() => {
              this.textLineHeight = 20
              this.setParamText()
            })
        }.width('80%')

        Row() {
          Button('textOverflow: ' + this.textOverflow[this.textOverflowIndex])
            .width('50%')
            .onClick(() => {
              this.textOverflowIndex = (this.textOverflowIndex + 1) % this.textOverflow.length
              this.setParamText()
            })
          Button('placeholderFont: ' + this.placeholderFont[this.textFont])
            .width('50%')
            .onClick(() => {
              this.textFont = (this.textFont + 1) % this.placeholderFont.length
              this.setParamText()
            })
        }.width('80%')



        Divider()

        Text('TextInput')
        TextInput({placeholder:'in your word...'})
          .attributeModifier(this.TextInputModifierTest as TextInputModifierTest)

        Row() {
          Button('type: ' + InputType[this.typeIndex])
            .width('100%')
            .onClick(() => {
              this.typeIndex = (this.typeIndex + 1) % this.type.length
              this.setParamTextInput()
            })
        }.width('80%')

        Row() {
          Button('enterKeyType: ' + EnterKeyType[this.enterKeyTypeIndex])
            .width('100%')
            .onClick(() => {
              this.enterKeyTypeIndex = (this.enterKeyTypeIndex + 1) % this.enterKeyType.length
              this.setParamTextInput()
            })
        }.width('80%')

        Row() {
          Button('fontWeight: ' + this.fontWeight[this.inputWeightIndex])
            .width('50%')
            .onClick(() => {
              this.inputWeightIndex = (this.inputWeightIndex + 1) % this.fontWeight.length
              this.setParamTextInput()
            })

          Button('fontSize: ' + this.sizeAll[this.inputSizeIndex])
            .width('50%')
            .onClick(() => {
              this.inputSizeIndex = (this.inputSizeIndex + 1) % this.sizeAll.length
              this.setParamTextInput()
            })
        }.width('80%')

        Row() {
          Button('fontStyle: Normal')
            .width('50%')
            .onClick(() => {
              this.inputStyle = FontStyle.Normal
              this.setParamTextInput()
            })

          Button('fontStyle: Italic')
            .width('50%')
            .onClick(() => {
              this.inputStyle = FontStyle.Italic
              this.setParamTextInput()
            })
        }.width('80%')

        Row() {
          Button('fontColor: ' + this.colorAll[this.inputColorIndex])
            .width('50%')
            .onClick(() => {
              this.inputColorIndex = (this.inputColorIndex + 1) % this.colorAll.length
              this.setParamTextInput()
            })

          Button('placeholderFont')
            .width('50%')
            .onClick(() => {
              this.inputPlaFontIndex = (this.inputPlaFontIndex + 1) % this.placeholderFont.length
              this.setParamTextInput()
            })
        }.width('80%')

        Row() {

          Button('placeholderColor: ' + this.colorAll[this.inputPlaColorIndex])
            .width('100%')
            .onClick(() => {
              this.inputPlaColorIndex = (this.inputPlaColorIndex + 1) % this.colorAll1.length
              this.setParamTextInput()
            })
        }.width('80%')









      }
    }
    .width('100%')
    .height('100%')

  }
}