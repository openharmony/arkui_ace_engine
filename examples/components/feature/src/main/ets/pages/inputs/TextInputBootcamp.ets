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
//单行文本框
import { Drawer } from 'common/src/main/ets/components/Drawer';
import { ColorBlock, useEnabled, RadioBlock, SliderBlock } from 'common';
import { LengthMetrics } from '@kit.ArkUI';
import UTD from '@ohos.data.uniformTypeDescriptor';


@Component
export struct TextInputBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false
  @State isShow: boolean = false
  @State text: string = ''
  @State enableType: boolean = false;
  @State type: InputType = InputType.Normal;
  @State enablePlaceholderColor: boolean = false;
  @State placeholderColor: ResourceColor = '#007DFF';
  @State enablePlaceholderFontSize: boolean = false;
  @State placeholderFontSize: number = 16.0;
  @State enablePlaceholderFontWeight: boolean = false;
  @State placeholderFontWeight: FontWeight | number | string = FontWeight.Normal;
  @State enablePlaceholderFontStyle: boolean = false;
  @State placeholderFontStyle: FontStyle = FontStyle.Normal;
  @State enableEnterKeyType: boolean = false;
  @State enterKeyType: EnterKeyType = EnterKeyType.Done;
  @State enableCaretColor: boolean = false;
  @State eCaretColor: ResourceColor = '#007DFF';
  @State enableMaxLength: boolean = false;
  @State maxLength: number = Infinity;
  @State enableFontColor: boolean = false;
  @State fontColor: ResourceColor = Color.Black;
  @State enableFontSize: boolean = false;
  @State fontSize: number = 16;
  @State enableFontStyle: boolean = false;
  @State fontStyle: FontStyle = FontStyle.Normal;
  @State enableFontWeight: boolean = false;
  @State fontWeight: number = FontWeight.Normal;
  // inputFilter
  @State enableCopyOptions: boolean = false;
  @State copyOptions: CopyOptions = CopyOptions.LocalDevice;
  @State enableShowPasswordIcon: boolean = false;
  @State showPasswordIcon: boolean = true;
  @State enableStyle: boolean = false;
  @State style: TextInputStyle = TextInputStyle.Default;
  @State enableTextAlign: boolean = false;
  @State textAlign: TextAlign = TextAlign.Start;
  @State enableSelectedBackgroundColor: boolean = false;
  @State selectedBackgroundColor: ResourceColor | undefined = undefined;
  @State enableCaretStyleWidth: boolean = false;
  @State caretStyleWidth: number | undefined = undefined;
  @State enableCaretStyleColor: boolean = false;
  @State caretStyleColor: ResourceColor | undefined = undefined;
  @State enableCaretPosition: boolean = false;
  @State caretPosition: number | undefined = undefined;
  @State enableShowError: boolean = false;
  @State showError: ResourceStr | undefined = undefined;
  @State enableShowUnderline: boolean = false;
  @State showUnderline: boolean = false;
  @State enablePasswordIconOnIconSrc: boolean = false;
  @State passwordIconOnIconSrc: ResourceStr | undefined = undefined;
  @State enablePasswordIconOffIconSrc: boolean = false;
  @State passwordIconOffIconSrc: ResourceStr | undefined = undefined;
  @State enableEnableKeyboardOnFocus: boolean = false;
  @State enableKeyboardOnFocus: boolean = true;
  @State enableSelectionMenuHidden: boolean = false;
  @State selectionMenuHidden: boolean = false;
  @State enableBarState: boolean = false;
  @State barState: BarState = BarState.Auto;
  @State enableMaxLines: boolean = false;
  @State maxLines: number = 3;
  // @State enableCustomKeyboardValue: boolean = false;
  // @State customKeyboardValue: CustomBuilder
  @State enableCustomKeyboardOptions: boolean = false;
  @State customKeyboardOptions: boolean = false;
  @State enableEnableAutoFill: boolean = false;
  @State enableAutoFill: boolean = true;
  @State enablePasswordRules: boolean = false;
  @State passwordRules: string | undefined = undefined;
  @State enableCancelButtonStyle: boolean = false;
  @State cancelButtonStyle: CancelButtonStyle = CancelButtonStyle.INPUT;
  // @State enableCancelButtonIcon: boolean = false;
  // @State cancelButtonIcon: IconOptions = '';
  @State enableSelectAll: boolean = false;
  @State selectAll: boolean = false;
  @State enableShowCounterValue: boolean = false;
  @State showCounterValue: boolean | undefined = undefined;
  @State enableShowCounterOptionsThresholdPercentage: boolean = false;
  @State showCounterOptionsThresholdPercentage: number | undefined = undefined;
  @State enableShowCounterOptionsHighlightBorder: boolean = false;
  @State showCounterOptionsHighlightBorder: boolean = false;
  @State enableContentType: boolean = false;
  @State contentType: ContentType | undefined = undefined;
  @State enableUnderlineColor: boolean = false;
  @State underlineColor: ResourceColor | undefined = undefined;
  @State enableLineHeight: boolean = false;
  @State lineHeight: number | undefined = undefined;
  @State enableDecorationType: boolean = false;
  @State decorationType: TextDecorationType = TextDecorationType.None;
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
  @State enableTextOverflow: boolean = false;
  @State textOverflow: TextOverflow = TextOverflow.Clip;
  @State enableTextIndent: boolean = false;
  @State textIndent: number = 0;
  @State enableMinFontSize: boolean = false;
  @State minFontSize: number | undefined = undefined;
  @State enableMaxFontSize: boolean = false;
  @State maxFontSize: number | undefined = undefined;
  @State enableHeightAdaptivePolicy: boolean = false;
  @State heightAdaptivePolicy: TextHeightAdaptivePolicy = TextHeightAdaptivePolicy.MAX_LINES_FIRST;
  @State enableShowPassword: boolean = false;
  @State showPassword: boolean = false;
  @State enableLineBreakStrategy: boolean = false;
  @State lineBreakStrategy: LineBreakStrategy = LineBreakStrategy.GREEDY
  //editMenuOptions
  @State enableEnablePreviewText: boolean = false;
  @State enablePreviewText: boolean = true;
  @State enableHapticFeedback: boolean = false;
  @State hapticFeedback: boolean = true;
  @State enableCancelButton: boolean = false;
  @State cancelButton: CancelButtonStyle = CancelButtonStyle.INPUT;

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
      TextInput({ text: this.text })
        .onChange((value: string) => {
          this.text = value
        })
        .type(useEnabled(this.enableType, this.type))
        .placeholderColor(useEnabled(this.enablePlaceholderColor, this.placeholderColor))
        .placeholderFont({
          size: useEnabled(this.enablePlaceholderFontSize, this.placeholderFontSize),
          weight: useEnabled(this.enablePlaceholderFontWeight, this.placeholderFontWeight),
          style: useEnabled(this.enablePlaceholderFontStyle, this.placeholderFontStyle)
        })
        .enterKeyType(useEnabled(this.enableEnterKeyType, this.enterKeyType))
        .caretColor(useEnabled(this.enableCaretColor, this.eCaretColor))
        .maxLength(useEnabled(this.enableMaxLength, this.maxLength))
        .fontColor(useEnabled(this.enableFontColor, this.fontColor))
        .fontSize(useEnabled(this.enableFontSize, this.fontSize))
        .fontStyle(useEnabled(this.enableFontStyle, this.fontStyle))
        .fontWeight(useEnabled(this.enableFontWeight, this.fontWeight))
        .copyOption(useEnabled(this.enableCopyOptions, this.copyOptions))
        .showPasswordIcon(useEnabled(this.enableShowPasswordIcon, this.showPasswordIcon))
        .style(useEnabled(this.enableStyle, this.style))
        .textAlign(useEnabled(this.enableTextAlign, this.textAlign))
        .selectedBackgroundColor(useEnabled(this.enableSelectedBackgroundColor, this.selectedBackgroundColor))
        .caretStyle({
          width: useEnabled(this.enableCaretStyleWidth, this.caretStyleWidth),
          color: useEnabled(this.enableCaretStyleColor, this.caretStyleColor)
        })
        .caretPosition(useEnabled(this.enableCaretPosition, this.caretPosition))
        .showError(useEnabled(this.enableShowError, this.showError))
        .showUnderline(useEnabled(this.enableShowUnderline, this.showUnderline))
        .enableKeyboardOnFocus(useEnabled(this.enableEnableKeyboardOnFocus, this.enableKeyboardOnFocus))
        .selectionMenuHidden(useEnabled(this.enableSelectionMenuHidden, this.selectionMenuHidden))
        .barState(useEnabled(this.enableBarState, this.barState))
        .maxLines(useEnabled(this.enableMaxLines, this.maxLines))//customKeyboard
        .enableAutoFill(useEnabled(this.enableEnableAutoFill, this.enableAutoFill))
        .passwordRules(useEnabled(this.enablePasswordRules, this.passwordRules))
        .cancelButton({ style: useEnabled(this.enableCancelButtonStyle, this.cancelButtonStyle) })
        .selectAll(useEnabled(this.enableSelectAll, this.selectAll))
        .showCounter(useEnabled(this.enableShowCounterValue, this.showCounterValue))
        .contentType(useEnabled(this.enableContentType, this.contentType))
        .underlineColor(useEnabled(this.enableUnderlineColor, this.underlineColor))
        .lineHeight(useEnabled(this.enableLineHeight, this.lineHeight))
        .decoration({
          type: useEnabled(this.enableDecorationType, this.decorationType),
          color: useEnabled(this.enableDecorationColor, this.decorationColor),
          style: useEnabled(this.enableDecorationStyle, this.decorationStyle),
        .allowDrop([UTD.UniformDataType.TEXT, UTD.UniformDataType.PLAIN_TEXT])
        .draggable(true)
        .margin({
          start: LengthMetrics.vp(24),
          end: LengthMetrics.vp(24)
        })
        .letterSpacing(useEnabled(this.enableLetterSpacing, this.letterSpacing))
        .fontFeature(useEnabled(this.enableFontFeature, this.fontFeature))
        .wordBreak(useEnabled(this.enableWordBreak, this.wordBreak))
        .textOverflow(useEnabled(this.enableTextOverflow, this.textOverflow))
        .textIndent(useEnabled(this.enableTextIndent, this.textIndent))
        .minFontSize(useEnabled(this.enableMinFontSize, this.minFontSize))
        .maxFontSize(useEnabled(this.enableMaxFontSize, this.maxFontSize))
        .heightAdaptivePolicy(useEnabled(this.enableHeightAdaptivePolicy, this.heightAdaptivePolicy))
        .showPassword(useEnabled(this.enableShowPassword, this.showPassword))
        .lineBreakStrategy(useEnabled(this.enableLineBreakStrategy, this.lineBreakStrategy))
        .enablePreviewText(useEnabled(this.enableEnablePreviewText, this.enablePreviewText))
    }.justifyContent(FlexAlign.Start)
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {

        RadioBlock({
          title: 'type',
          isEnabled: this.enableType,
          value: this.type,
          dataSource: [
            { label: 'Start', value: InputType.Normal },
            { label: 'Center', value: InputType.Number },
            { label: 'End', value: InputType.PhoneNumber },
            { label: 'JUSTIFY', value: InputType.Email },
          ]
        })

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
          title: 'placeholderFont.weight',
          isEnabled: this.enablePlaceholderFontWeight,
          value: this.placeholderFontWeight,
          dataSource: [
            { label: '100', value: 100 },
            { label: '200', value: 200 },
            { label: '300', value: 300 },
            { label: '400', value: 400 },
            { label: '500', value: 500 },
            { label: '600', value: 600 },
            { label: '700', value: 700 },
            { label: '800', value: 800 },
            { label: '900', value: 900 },
            { label: 'Lighter', value: FontWeight.Lighter },
            { label: 'Normal', value: FontWeight.Normal },
            { label: 'Regular', value: FontWeight.Regular },
            { label: 'Medium', value: FontWeight.Medium },
            { label: 'Bold', value: FontWeight.Bold },
            { label: 'Bolder', value: FontWeight.Bolder },
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

        ColorBlock({
          title: 'caretColor',
          isEnabled: this.enableCaretColor,
          color: this.eCaretColor
        })

        SliderBlock({
          title: 'maxLength',
          isEnabled: this.enableMaxLength,
          value: this.maxLength,
          min: 0,
          max: 200
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
          title: 'fontStyle',
          isEnabled: this.enableFontStyle,
          value: this.fontStyle,
          dataSource: [
            { label: 'Normal', value: FontStyle.Normal },
            { label: 'Italic', value: FontStyle.Italic },
          ]
        })

        RadioBlock({
          title: 'fontWeight',
          isEnabled: this.enableFontWeight,
          value: this.fontWeight,
          dataSource: [
            { label: '100', value: 100 },
            { label: '200', value: 200 },
            { label: '300', value: 300 },
            { label: '400', value: 400 },
            { label: '500', value: 500 },
            { label: '600', value: 600 },
            { label: '700', value: 700 },
            { label: '800', value: 800 },
            { label: '900', value: 900 },
            { label: 'Lighter', value: FontWeight.Lighter },
            { label: 'Normal', value: FontWeight.Normal },
            { label: 'Regular', value: FontWeight.Regular },
            { label: 'Medium', value: FontWeight.Medium },
            { label: 'Bold', value: FontWeight.Bold },
            { label: 'Bolder', value: FontWeight.Bolder },
          ]
        })

        RadioBlock({
          title: 'copyOptions',
          isEnabled: this.enableCopyOptions,
          value: this.copyOptions,
          dataSource: [
            { label: 'None', value: CopyOptions.None },
            { label: 'InApp', value: CopyOptions.InApp },
            { label: 'LocalDevice', value: CopyOptions.LocalDevice },
          ]
        })

        RadioBlock({
          title: 'showPasswordIcon',
          isEnabled: this.enableShowPasswordIcon,
          value: this.showPasswordIcon,
          dataSource: [
            { label: 'false', value: false },
            { label: 'true', value: true },
          ]
        })

        RadioBlock({
          title: 'style',
          isEnabled: this.enableStyle,
          value: this.style,
          dataSource: [
            { label: 'Default', value: TextInputStyle.Default },
            { label: 'Inline', value: TextInputStyle.Inline },
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
          title: 'SelectedBackgroundColor',
          isEnabled: this.enableSelectedBackgroundColor,
          color: this.selectedBackgroundColor
        })

        SliderBlock({
          title: 'caretStyle.width',
          isEnabled: this.enableCaretStyleWidth,
          value: this.caretStyleWidth,
          min: 0,
          max: 200
        })

        ColorBlock({
          title: 'caretStyle.color',
          isEnabled: this.enableCaretStyleColor,
          color: this.caretStyleColor
        })

        SliderBlock({
          title: 'caretPosition',
          isEnabled: this.enableCaretPosition,
          value: this.caretPosition,
          min: 0,
          max: 200
        })

        RadioBlock({
          title: 'showUnderline',
          isEnabled: this.enableShowUnderline,
          value: this.showUnderline,
          dataSource: [
            { label: 'false', value: false },
            { label: 'true', value: true },
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
          max: 20
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
          title: 'enableAutoFill',
          isEnabled: this.enableEnableAutoFill,
          value: this.enableAutoFill,
          dataSource: [
            { label: 'false', value: false },
            { label: 'true', value: true },
          ]
        })

        RadioBlock({
          title: 'cancelButton',
          isEnabled: this.enableCancelButton,
          value: this.cancelButton,
          dataSource: [
            { label: 'CONSTANT', value: CancelButtonStyle.CONSTANT },
            { label: 'INVISIBLE', value: CancelButtonStyle.INVISIBLE },
            { label: 'INPUT', value: CancelButtonStyle.INPUT },
          ]
        })

        RadioBlock({
          title: 'selectAll',
          isEnabled: this.enableSelectAll,
          value: this.selectAll,
          dataSource: [
            { label: 'false', value: false },
            { label: 'true', value: true },
          ]
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

        ColorBlock({
          title: 'underlineColor',
          isEnabled: this.enableUnderlineColor,
          color: this.underlineColor
        })

        SliderBlock({
          title: 'lineHeight',
          isEnabled: this.enableLineHeight,
          value: this.lineHeight,
          min: 0,
          max: 10
        })

        RadioBlock({
          title: 'decoration.type',
          isEnabled: this.enableDecorationType,
          value: this.decorationType,
          dataSource: [
            { label: 'None', value: TextDecorationType.None },
            { label: 'Underline', value: TextDecorationType.Underline },
            { label: 'Overline', value: TextDecorationType.Overline },
            { label: 'LineThrough', value: TextDecorationType.LineThrough },
          ]
        })

        ColorBlock({
          title: 'decoration.color',
          isEnabled: this.enableDecorationColor,
          color: this.decorationColor
        })

        RadioBlock({
          title: 'decoration.style',
          isEnabled: this.enableDecorationStyle,
          value: this.decorationStyle,
          dataSource: [
            { label: 'SOLID', value: TextDecorationStyle.SOLID },
            { label: 'DOUBLE', value: TextDecorationStyle.DOUBLE },
            { label: 'DOTTED', value: TextDecorationStyle.DOTTED },
            { label: 'DASHED', value: TextDecorationStyle.DASHED },
            { label: 'WAVY', value: TextDecorationStyle.WAVY },
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
          title: 'wordBreak',
          isEnabled: this.enableWordBreak,
          value: this.wordBreak,
          dataSource: [
            { label: 'NORMAL', value: WordBreak.NORMAL },
            { label: 'BREAK_ALL', value: WordBreak.BREAK_ALL },
            { label: 'BREAK_WORD', value: WordBreak.BREAK_WORD },
          ]
        })

        RadioBlock({
          title: 'textOverFlow',
          isEnabled: this.enableTextOverflow,
          value: this.textOverflow,
          dataSource: [
            { label: 'None', value: TextOverflow.None },
            { label: 'Clip', value: TextOverflow.Clip },
            { label: 'Ellipsis', value: TextOverflow.Ellipsis },
            { label: 'MARQUEE', value: TextOverflow.MARQUEE },
          ]
        })

        SliderBlock({
          title: 'textIndent',
          isEnabled: this.enableTextIndent,
          value: this.textIndent,
          min: 0,
          max: 20
        })

        SliderBlock({
          title: 'minFontSize',
          isEnabled: this.enableMinFontSize,
          value: this.minFontSize,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'maxFontSize',
          isEnabled: this.enableMaxFontSize,
          value: this.maxFontSize,
          min: 0,
          max: 100
        })

        RadioBlock({
          title: 'heightAdaptivePolicy',
          isEnabled: this.enableHeightAdaptivePolicy,
          value: this.heightAdaptivePolicy,
          dataSource: [
            { label: 'MAX_LINES_FIRST', value: TextHeightAdaptivePolicy.MAX_LINES_FIRST },
            { label: 'MIN_FONT_SIZE_FIRST', value: TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST },
            { label: 'LAYOUT_CONSTRAINT_FIRST', value: TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST },
          ]
        })

        RadioBlock({
          title: 'showPassword',
          isEnabled: this.enableShowPassword,
          value: this.showPassword,
          dataSource: [
            { label: 'false', value: false },
            { label: 'true', value: true },
          ]
        })

        RadioBlock({
          title: 'lineBreakStrategy',
          isEnabled: this.enableLineBreakStrategy,
          value: this.lineBreakStrategy,
          dataSource: [
            { label: 'GREEDY', value: LineBreakStrategy.GREEDY },
            { label: 'HIGH_QUALITY', value: LineBreakStrategy.HIGH_QUALITY },
            { label: 'BALANCED', value: LineBreakStrategy.BALANCED },
          ]
        })

        RadioBlock({
          title: 'enablePreviewText',
          isEnabled: this.enableEnablePreviewText,
          value: this.enablePreviewText,
          dataSource: [
            { label: 'false', value: false },
            { label: 'true', value: true },
          ]
        })

        RadioBlock({
          title: 'hapticFeedback',
          isEnabled: this.enableHapticFeedback,
          value: this.hapticFeedback,
          dataSource: [
            { label: 'false', value: false },
            { label: 'true', value: true },
          ]
        })

        RadioBlock({
          title: 'cancelButton.style',
          isEnabled: this.enableCancelButtonStyle,
          value: this.cancelButtonStyle,
          dataSource: [
            { label: 'CONSTANT', value: CancelButtonStyle.CONSTANT },
            { label: 'INVISIBLE', value: CancelButtonStyle.INVISIBLE },
            { label: 'INPUT', value: CancelButtonStyle.INPUT },
          ]
        })

      }
    }
  }
}

@Preview
@Component
struct TextInputBootcampPreviewer {
  build() {
    TextInputBootcamp({
      title: '单行文本框/TextInput'
    })
  }
}