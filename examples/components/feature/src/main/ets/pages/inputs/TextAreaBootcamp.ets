/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
import { Drawer } from 'common/src/main/ets/components/Drawer';
import { RadioBlock, ColorBlock, useEnabled } from 'common';
import { LengthMetrics } from '@kit.ArkUI';
import UTD from '@ohos.data.uniformTypeDescriptor';

@Component
export struct TextAreaBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false
  @State isShow: boolean = false
  @State text: string = ''
  @State positionInfo: CaretOffset = { index: 0, x: 0, y: 0 }
  controller: TextAreaController = new TextAreaController()
  @State enablePlaceholderColor: boolean = false;
  @State placeholderColor: ResourceColor | undefined = undefined;
  @State enablePlaceholderFontSize: boolean = false;
  @State placeholderFontSize: number = 16;
  @State enablePlaceholderFontWeight: boolean = false;
  @State placeholderFontWeight: FontWeight |number = 400|FontWeight.Normal;
  @State enablePlaceholderFontStyle: boolean = false;
  @State placeholderFontStyle: FontStyle = FontStyle.Normal;
  @State enableTextAlign: boolean = false;
  @State textAlign: TextAlign = TextAlign.Start;
  @State enableCaretColor: boolean = false;
  @State caretColor: ResourceColor = '#007DFF';
  @State enableFontColor: boolean = false;
  @State fontColor: ResourceColor | undefined = undefined;
  @State enableFontSize: boolean = false;
  @State fontSize: number = 16; //16fp
  @State enableFontStyle: boolean = false;
  @State fontStyle: FontStyle = FontStyle.Normal;
  @State enableFontWeight: boolean = false;
  @State fontWeight: number | FontWeight | string = FontWeight.Normal
  @State enableCopyOption: boolean = false;
  @State copyOption: CopyOptions = CopyOptions.LocalDevice;
  @State enableMaxLength: boolean = false;
  @State maxLength: number | undefined = undefined;
  @State enableShowCounterValue: boolean = false;
  @State showCounterValue: boolean | undefined = undefined;
  @State enableShowCounterOptionsThresholdPercentage: boolean = false;
  @State showCounterOptionsThresholdPercentage : number | undefined = undefined;
  @State enableShowCounterOptionsHighlightBorder: boolean = false;
  @State showCounterOptionsHighlightBorder: boolean = false;
  @State enableStyle: boolean = false;
  @State style: TextContentStyle = TextContentStyle.DEFAULT;
  @State enableEnableKeyboardOnFocus: boolean = false;
  @State enableKeyboardOnFocus: boolean = true;
  @State enableSelectionMenuHidden: boolean = false;
  @State selectionMenuHidden: boolean = false;
  @State enableBarState: boolean = false;
  @State barState: BarState = BarState.Auto;
  @State enableMaxLines: boolean = false;
  @State maxLines: number = 3;
  @State enableCustomKeyboardOptions: boolean = false;
  @State customKeyboardOptions: boolean = false;
  @State enableType: boolean = false;
  @State type: TextAreaType = TextAreaType.NORMAL
  @State enableEnterKeyType: boolean = false;
  @State enterKeyType: EnterKeyType = EnterKeyType.NEW_LINE;
  @State enableEnableAutoFill: boolean = false;
  @State enableAutoFill: boolean = true;
  @State enableContentType: boolean = false;
  @State contentType: ContentType | undefined = undefined;
  @State enableLineHeight: boolean = false;
  @State lineHeight: number | undefined = undefined;
  @State enableDecorationType: boolean = false;
  @State decorationType:TextDecorationType = TextDecorationType.None;
  @State enableDecorationColor: boolean = false;
  @State decorationColor: ResourceColor = Color.Black;
  @State enableDecorationStyle: boolean = false;
  @State decorationStyle: TextDecorationStyle = TextDecorationStyle.SOLID;
  @State enableLetterSpacing: boolean = false;
  @State letterSpacing: number | undefined = undefined;
  @State enableFontFeature: boolean = false;
  @State fontFeature: string = 'normal | <feature-tag-value>';
  @State enableWordBreak: boolean = false;
  @State wordBreak: WordBreak = WordBreak.BREAK_WORD;
  @State enableSelectedBackgroundColor: boolean = false;
  @State selectedBackgroundColor: ResourceColor | undefined = undefined;
  @State enableCaretStyleWidth: boolean = false;
  @State caretStyleWidth: number | undefined = undefined;
  @State enableCaretStyleColor: boolean = false;
  @State caretStyleColor: ResourceColor | undefined = undefined;
  @State enableTextIndent: boolean = false;
  @State textIndent: number = 0;
  @State enableTextOverflow: boolean = false;
  @State textOverflow: TextOverflow = TextOverflow.Clip;
  @State enableMinFontSize: boolean = false;
  @State minFontSize: number | undefined = undefined;
  @State enableMaxFontSize: boolean = false;
  @State maxFontSize: number | undefined = undefined;
  @State enableHeightAdaptivePolicy: boolean = false;
  @State heightAdaptivePolicy: TextHeightAdaptivePolicy = TextHeightAdaptivePolicy.MAX_LINES_FIRST;
  @State enableLineSpacingValue: boolean = false;
  @State lineSpacingValue: number = 0;
  @State enableLineSpacingUnit: boolean = false;
  @State lineSpacingUnit: LengthUnit = LengthUnit.VP;
  @State enableLineBreakStrategy: boolean = false;
  @State lineBreakStrategy: LineBreakStrategy = LineBreakStrategy.GREEDY
  @State enableEnablePreviewText: boolean = false;
  @State enablePreviewText: boolean = true;
  @State enableHapticFeedback: boolean = false;
  @State hapticFeedback: boolean = true;


  build() {
    NavDestination() {
      Drawer({
        title: this.title,
        showParameters: $showParameters,
        content: () => {
          this.Content()
        },
        parameters: () => {
          this.Parameters()
        }
      })
    }
    .backgroundColor('#f1f3f5')
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Row() {
      TextArea({ text: this.message1 })
        .onChange((value: string) => {
          this.message1 = value
        })
        .caretColor(useEnabled(this.enableCaretColor, this.caretColor))
        .selectedBackgroundColor(useEnabled(this.enableBackgroundColor, this.compBackgroundColor))
        .textAlign(useEnabled(this.enableTextAlign, this.textAlign))
        .style(useEnabled(this.enableTextStyle, this.textStyle))
        .type(useEnabled(this.enableTextareaType, this.textareaType))
        .allowDrop([UTD.UniformDataType.TEXT, UTD.UniformDataType.PLAIN_TEXT])
        .draggable(true)
        .margin({
          start: LengthMetrics.vp(24),
          end: LengthMetrics.vp(24)
        })
        .textAlign(useEnabled(this.enableTextAlign,this.textAlign))
        .caretColor(useEnabled(this.enableCaretColor,this.caretColor))
        .fontColor(useEnabled(this.enableFontColor,this.fontColor))
        .fontSize(useEnabled(this.enableFontSize,this.fontSize))
        .fontStyle(useEnabled(this.enableFontStyle,this.fontStyle))
        .fontWeight(useEnabled(this.enableFontWeight,this.fontWeight))
        .copyOption(useEnabled(this.enableCopyOption,this.copyOption))
        .maxLength(useEnabled(this.enableMaxLength,this.maxLength))
        .showCounter(useEnabled(this.enableShowCounterValue,this.showCounterValue))
        .style(useEnabled(this.enableStyle,this.style))
        .enableKeyboardOnFocus(useEnabled(this.enableEnableKeyboardOnFocus,this.enableKeyboardOnFocus))
        .selectionMenuHidden(useEnabled(this.enableSelectionMenuHidden,this.selectionMenuHidden))
        .barState(useEnabled(this.enableBarState,this.barState))
        .maxLines(useEnabled(this.enableMaxLines,this.maxLines))
        .type(useEnabled(this.enableType,this.type))
        .enterKeyType(useEnabled(this.enableEnterKeyType,this.enterKeyType))
        .enableAutoFill(useEnabled(this.enableAutoFill,this.enableAutoFill))
        .contentType(useEnabled(this.enableContentType,this.contentType))
        .lineHeight(useEnabled(this.enableLineHeight,this.lineHeight))
        .decoration({
          type: useEnabled(this.enableDecorationType,this.decorationType),
          color: useEnabled(this.enableDecorationColor,this.decorationColor),
          style: useEnabled(this.enableDecorationStyle,this.decorationStyle),
        })
        .letterSpacing(useEnabled(this.enableLetterSpacing,this.letterSpacing))
        .fontFeature(useEnabled(this.enableFontFeature,this.fontFeature))
        .wordBreak(useEnabled(this.enableWordBreak,this.wordBreak))
        .selectedBackgroundColor(useEnabled(this.enableSelectedBackgroundColor,this.selectedBackgroundColor))
        .caretStyle({
          width: useEnabled(this.enableCaretStyleWidth, this.caretStyleWidth),
          color: useEnabled(this.enableCaretStyleColor, this.caretStyleColor)
        })
        .textIndent(useEnabled(this.enableTextIndent,this.textIndent))
        .textOverflow(useEnabled(this.enableTextOverflow,this.textOverflow))
        .minFontSize(useEnabled(this.enableMinFontSize,this.minFontSize))
        .maxFontSize(useEnabled(this.enableMaxFontSize,this.maxFontSize))
        .heightAdaptivePolicy(useEnabled(this.enableHeightAdaptivePolicy,this.heightAdaptivePolicy))
        .lineSpacing({
          value: useEnabled(this.enableLineSpacingValue, this.lineSpacingValue),
          unit: useEnabled(this.enableLineSpacingUnit, this.lineSpacingUnit)
        })
        .lineBreakStrategy(useEnabled(this.enableLineBreakStrategy,this.lineBreakStrategy))
        .enablePreviewText(useEnabled(this.enableEnablePreviewText,this.enablePreviewText))
    }.justifyContent(FlexAlign.Start)
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        ColorBlock({
          title: 'placeholderColor',
          isEnabled: this.enablePlaceholderColor,
          color: this.placeholderColor
        })

        SliderBlock({
          title: 'placeholderFont.size',
          isEnabled: this.enablePlaceholderFontSize,
          value: this.placeholderFontSize,
          min: 0,
          max: 200
        })

        RadioBlock({
          title:'placeholderFont.weight',
          isEnabled: this.enablePlaceholderFontWeight,
          value: this.placeholderFontWeight,
          dataSource: [
            {label: '100', value: 100},
            {label: '200', value: 200},
            {label: '300', value: 300},
            {label: '400', value: 400},
            {label: '500', value: 500},
            {label: '600', value: 600},
            {label: '700', value: 700},
            {label: '800', value: 800},
            {label: '900', value: 900},
            {label: 'Lighter', value: FontWeight.Lighter },
            {label: 'Normal', value: FontWeight.Normal },
            {label: 'Regular', value: FontWeight.Regular },
            {label: 'Medium', value: FontWeight.Medium },
            {label: 'Bold', value: FontWeight.Bold },
            {label: 'Bolder', value: FontWeight.Bolder },
          ]
        })

        RadioBlock({
          title: 'placeholderFont.style',
          isEnabled: this.enablePlaceholderFontStyle,
          value: this.placeholderFontStyle,
          dataSource: [
            { label: 'Normal', value: FontStyle.Normal },
            { label: 'Italic', value: FontStyle.Italic },
          ]
        })

        RadioBlock({
          title: 'textAlign',
          isEnabled: this.enableTextAlign,
          value: this.textAlign,
          dataSource: [
            { label: 'Start', value: TextAlign.Start },
            { label: 'Center', value: TextAlign.Center },
            { label: 'End', value: TextAlign.End },
            { label: 'JUSTIFY', value: TextAlign.JUSTIFY },
          ]
        })

        ColorBlock({
          title: 'caretColor',
          isEnabled: this.enableCaretColor,
          color: this.caretColor
        })

        ColorBlock({
          title: 'fontColor',
          isEnabled: this.enableFontColor,
          color: this.fontColor
        })

        SliderBlock({
          title: 'fontSize',
          isEnabled: this.enableFontSize,
          value: this.fontSize,
          min: 0,
          max: 200
        })

        RadioBlock({
          title:'fontStyle',
          isEnabled: this.enableFontStyle,
          value: this.fontStyle,
          dataSource: [
            {label: 'Normal', value: FontStyle.Normal },
            {label: 'Italic', value: FontStyle.Italic },
          ]
        })

        RadioBlock({
          title:'fontWeight',
          isEnabled: this.enableFontWeight,
          value: this.fontWeight,
          dataSource: [
            {label: '100', value: 100},
            {label: '200', value: 200},
            {label: '300', value: 300},
            {label: '400', value: 400},
            {label: '500', value: 500},
            {label: '600', value: 600},
            {label: '700', value: 700},
            {label: '800', value: 800},
            {label: '900', value: 900},
            {label: 'Lighter', value: FontWeight.Lighter },
            {label: 'Normal', value: FontWeight.Normal },
            {label: 'Regular', value: FontWeight.Regular },
            {label: 'Medium', value: FontWeight.Medium },
            {label: 'Bold', value: FontWeight.Bold },
            {label: 'Bolder', value: FontWeight.Bolder },
          ]
        })

        RadioBlock({
          title: 'copyOptions',
          isEnabled: this.enableCopyOption,
          value: this.copyOption,
          dataSource: [
            { label: 'None', value: CopyOptions.None },
            { label: 'InApp', value: CopyOptions.InApp },
            { label: 'LocalDevice', value: CopyOptions.LocalDevice },
          ]
        })

        SliderBlock({
          title: 'maxLength',
          isEnabled: this.enableMaxLength,
          value: this.maxLength,
          min: 0,
          max: 200
        })

        RadioBlock({
          title: 'showCounter.value',
          isEnabled: this.enableShowCounterValue,
          value: this.showCounterValue,
          dataSource: [
            { label: 'false', value: false },
            { label: 'true', value: true },
          ]
        })

        SliderBlock({
          title: 'showCounter.options.thresholdPercentage',
          isEnabled: this.enableShowCounterOptionsThresholdPercentage,
          value: this.showCounterOptionsThresholdPercentage,
          min: 0,
          max: 100
        })

        RadioBlock({
          title: 'style',
          isEnabled: this.enableStyle,
          value: this.style,
          dataSource: [
            { label: 'DEFAULT', value: TextContentStyle.DEFAULT },
            { label: 'INLINE', value: TextContentStyle.INLINE },
          ]
        })

        RadioBlock({
          title: 'enableKeyboardOnFocus',
          isEnabled: this.enableEnableKeyboardOnFocus,
          value: this.enableKeyboardOnFocus,
          dataSource: [
            { label: 'false', value: false },
            { label: 'true', value: true },
          ]
        })

        RadioBlock({
          title: 'selectionMenuHidden',
          isEnabled: this.enableSelectionMenuHidden,
          value: this.selectionMenuHidden,
          dataSource: [
            { label: 'false', value: false },
            { label: 'true', value: true },
          ]
        })

        RadioBlock({
          title: 'barState',
          isEnabled: this.enableBarState,
          value: this.barState,
          dataSource: [
            { label: 'Off', value: BarState.Off },
            { label: 'Auto', value: BarState.Auto },
            { label: 'On', value: BarState.On },
          ]
        })

        SliderBlock({
          title: 'maxLines',
          isEnabled: this.enableMaxLines,
          value: this.maxLines,
          min: 0,
          max:10
        })

        RadioBlock({
          title: 'customKeyboard.options',
          isEnabled: this.enableCustomKeyboardOptions,
          value: this.customKeyboardOptions,
          dataSource: [
            { label: 'false', value: false },
            { label: 'true', value: true },
          ]
        })

        RadioBlock({
          title: 'type',
          isEnabled: this.enableType,
          value: this.type,
          dataSource: [
            { label: 'NORMAL', value: TextAreaType.NORMAL },
            { label: 'NUMBER', value: TextAreaType.NUMBER },
            { label: 'PHONE_NUMBER', value: TextAreaType.PHONE_NUMBER },
            { label: 'EMAIL', value: TextAreaType.EMAIL },
            { label: 'NUMBER_DECIMAL', value: TextAreaType.NUMBER_DECIMAL },
            { label: 'URL', value: TextAreaType.URL },
          ]
        })

        RadioBlock({
          title: 'enterKeyType',
          isEnabled: this.enableEnterKeyType,
          value: this.enterKeyType,
          dataSource: [
            { label: 'Go', value: EnterKeyType.Go },
            { label: 'Search', value: EnterKeyType.Search },
            { label: 'Send', value: EnterKeyType.Send },
            { label: 'Next', value: EnterKeyType.Next },
            { label: 'Done', value: EnterKeyType.Done },
            { label: 'PREVIOUS', value: EnterKeyType.PREVIOUS },
            { label: 'NEW_LINE', value: EnterKeyType.NEW_LINE },
          ]
        })

        RadioBlock({
          title: 'enableAutoFill',
          isEnabled: this.enableEnableAutoFill,
          value: this.enableAutoFill,
          dataSource: [
            { label: 'false', value: false },
            { label: 'true', value: true },
          ]
        })

        RadioBlock({
          title: 'contentType',
          isEnabled: this.enableContentType,
          value: this.contentType,
          dataSource: [
            { label: 'USER_NAME', value: ContentType.USER_NAME },
            { label: 'PASSWORD', value: ContentType.PASSWORD },
            { label: 'NEW_PASSWORD', value: ContentType.NEW_PASSWORD },
            { label: 'FULL_STREET_ADDRESS', value: ContentType.FULL_STREET_ADDRESS },
            { label: 'HOUSE_NUMBER', value: ContentType.HOUSE_NUMBER },
            { label: 'DISTRICT_ADDRESS', value: ContentType.DISTRICT_ADDRESS },
            { label: 'CITY_ADDRESS', value: ContentType.CITY_ADDRESS },
            { label: 'PROVINCE_ADDRESS', value: ContentType.PROVINCE_ADDRESS },
            { label: 'COUNTRY_ADDRESS', value: ContentType.COUNTRY_ADDRESS },
            { label: 'PERSON_FULL_NAME', value: ContentType.PERSON_FULL_NAME },
            { label: 'PERSON_LAST_NAME', value: ContentType.PERSON_LAST_NAME },
            { label: 'PERSON_FIRST_NAME', value: ContentType.PERSON_FIRST_NAME },
            { label: 'PHONE_NUMBER', value: ContentType.PHONE_NUMBER },
            { label: 'PHONE_COUNTRY_CODE', value: ContentType.PHONE_COUNTRY_CODE },
            { label: 'FULL_PHONE_NUMBER', value: ContentType.FULL_PHONE_NUMBER },
            { label: 'EMAIL_ADDRESS', value: ContentType.EMAIL_ADDRESS },
            { label: 'BANK_CARD_NUMBER', value: ContentType.BANK_CARD_NUMBER },
            { label: 'ID_CARD_NUMBER', value: ContentType.ID_CARD_NUMBER },
            { label: 'NICKNAME', value: ContentType.NICKNAME },
            { label: 'DETAIL_INFO_WITHOUT_STREET', value: ContentType.DETAIL_INFO_WITHOUT_STREET },
            { label: 'FORMAT_ADDRESS', value: ContentType.FORMAT_ADDRESS },
          ]
        })

        SliderBlock({
          title: 'lineHeight',
          isEnabled: this.enableLineHeight,
          value: this.lineHeight,
          min: 0,
          max: 10
        })

        RadioBlock({
          title:'decoration.type',
          isEnabled: this.enableDecorationType,
          value: this.decorationType,
          dataSource: [
            {label: 'None', value: TextDecorationType.None },
            {label: 'Underline', value: TextDecorationType.Underline },
            {label: 'Overline', value: TextDecorationType.Overline },
            {label: 'LineThrough', value: TextDecorationType.LineThrough },
          ]
        })

        ColorBlock({
          title: 'decoration.color',
          isEnabled: this.enableDecorationColor,
          color: this.decorationColor
        })

        RadioBlock({
          title:'decoration.style',
          isEnabled: this.enableDecorationStyle,
          value: this.decorationStyle,
          dataSource: [
            {label: 'SOLID', value: TextDecorationStyle.SOLID },
            {label: 'DOUBLE', value: TextDecorationStyle.DOUBLE },
            {label: 'DOTTED', value: TextDecorationStyle.DOTTED },
            {label: 'DASHED', value: TextDecorationStyle.DASHED },
            {label: 'WAVY', value: TextDecorationStyle.WAVY },
          ]
        })

        SliderBlock({
          title: 'letterSpacing',
          isEnabled: this.enableLetterSpacing,
          value: this.letterSpacing,
          min: 0,
          max: 20
        })


        RadioBlock({
          title:'wordBreak',
          isEnabled: this.enableWordBreak,
          value: this.wordBreak,
          dataSource: [
            {label: 'NORMAL', value: WordBreak.NORMAL },
            {label: 'BREAK_ALL', value: WordBreak.BREAK_ALL },
            {label: 'BREAK_WORD', value: WordBreak.BREAK_WORD },
          ]
        })

        ColorBlock({
          title: 'SelectedBackgroundColor',
          isEnabled: this.enableSelectedBackgroundColor,
          color: this.selectedBackgroundColor
        })

        SliderBlock({
          title: 'caretStyle.width',
          isEnabled: this.enableCaretStyleWidth,
          value: this.caretStyleWidth,
          min: 0,
          max: 100
        })

        ColorBlock({
          title: 'caretStyle.color',
          isEnabled: this.enableCaretStyleColor,
          color: this.caretStyleColor
        })

        SliderBlock({
          title: 'textIndent',
          isEnabled: this.enableTextIndent,
          value: this.textIndent,
          min: 0,
          max: 20
        })

        RadioBlock({
          title:'textOverFlow',
          isEnabled: this.enableTextOverflow,
          value: this.textOverflow,
          dataSource: [
            {label: 'None', value: TextOverflow.None},
            {label: 'Clip', value: TextOverflow.Clip},
            {label: 'Ellipsis', value: TextOverflow.Ellipsis},
            {label: 'MARQUEE', value: TextOverflow.MARQUEE},
          ]
        })

        SliderBlock({
          title: 'minFontSize',
          isEnabled: this.enableMinFontSize,
          value: this.minFontSize,
          min: 0,
          max: 1
        })

        SliderBlock({
          title: 'maxFontSize',
          isEnabled: this.enableMaxFontSize,
          value: this.maxFontSize,
          min: 0,
          max: 200
        })

        RadioBlock({
          title:'heightAdaptivePolicy',
          isEnabled: this.enableHeightAdaptivePolicy,
          value: this.heightAdaptivePolicy,
          dataSource: [
            {label: 'MAX_LINES_FIRST', value: TextHeightAdaptivePolicy.MAX_LINES_FIRST},
            {label: 'MIN_FONT_SIZE_FIRST', value: TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST},
            {label: 'LAYOUT_CONSTRAINT_FIRST', value: TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST},
          ]
        })

        SliderBlock({
          title: 'lineSpacing.value',
          isEnabled: this.enableLineSpacingValue,
          value: this.lineSpacingValue,
          min: 0,
          max: 20
        })

        RadioBlock({
          title:'lineSpacing.unit',
          isEnabled: this.enableLineSpacingUnit,
          value: this.lineSpacingUnit,
          dataSource: [
            {label: 'PX', value: LengthUnit.PX },
            {label: 'VP', value: LengthUnit.VP },
            {label: 'FP', value: LengthUnit.FP },
            {label: 'PERCENT', value: LengthUnit.PERCENT },
            {label: 'LPX', value: LengthUnit.LPX },
          ]
        })

        RadioBlock({
          title:'lineBreakStrategy',
          isEnabled: this.enableLineBreakStrategy,
          value: this.lineBreakStrategy,
          dataSource: [
            {label: 'GREEDY', value: LineBreakStrategy.GREEDY },
            {label: 'HIGH_QUALITY', value: LineBreakStrategy.HIGH_QUALITY },
            {label: 'BALANCED', value: LineBreakStrategy.BALANCED },
          ]
        })

        //editMenuOption

        RadioBlock({
          title: 'enablePreviewText',
          isEnabled: this.enableEnablePreviewText,
          value: this.enablePreviewText,
          dataSource: [
            { label: 'false', value: false },
            { label: 'true', value: true },
          ]
        })
      }
    }
  }
}

@Preview
@Component
struct TextAreaBootcampPreviewer {
  build() {
    TextAreaBootcamp({
      title: '多行文本框/TextArea'
    })
  }
}