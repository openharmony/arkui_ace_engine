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
import { RadioBlock, SliderBlock, ColorBlock, useEnabled } from 'common';

@Component
export struct SearchBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State changeValue: string = ''
  @State submitValue: string = ''
  @State enableSearchButtonValue: boolean = false;
  @State searchButtonValue: string | undefined = undefined;
  @State enableSearchButtonOptionFontSize: boolean = false;
  @State searchButtonOptionFontSize: Length = '16fp';
  @State enableSearchButtonOptionFontColor: boolean = false;
  @State searchButtonOptionFontColor: ResourceColor = '#ff3f97e9';
  @State enablePlaceholderColor: boolean = false;
  @State placeholderColor: ResourceColor = '#99182431';
  @State enablePlaceholderFontSize: boolean = false;
  @State placeholderFontSize: number = 16; ///length
  @State enablePlaceholderFontWeight: boolean = false;
  @State placeholderFontWeight: FontWeight | number | string = 400|FontWeight.Normal;
  @State enablePlaceholderFontStyle: boolean = false;
  @State placeholderFontStyle: FontStyle = FontStyle.Normal;
  @State enableTextFontSize: boolean = false;
  @State textFontSize: number = 16; //length
  @State enableTextFontWeight: boolean = false;
  @State textFontWeight: FontWeight | number | string = 400|FontWeight.Normal;
  @State enableTextFontStyle: boolean = false;
  @State textFontStyle: FontStyle = FontStyle.Normal;
  @State enableTextAlign: boolean = false;
  @State textAlign : TextAlign = TextAlign.Start;
  @State enableCopyOption: boolean =false;
  @State copyOption: CopyOptions = CopyOptions.LocalDevice;
  @State enableSearchIconSize: boolean = false;
  @State searchIconSize: number = 16; //length
  @State enableSearchIconColorLight: boolean = false;
  @State searchIconColorLight: ResourceColor = '#99182431';
  @State enableSearchIconColorDark: boolean = false;
  @State searchIconColorDark: ResourceColor = '#99ffffff'; ////深色模式
  @State enableSearchIconSrc: boolean = false;
  @State searchIconSrc: ResourceStr = '';
  @State enableCancelButtonStyle: boolean = false;
  @State cancelButtonStyle: CancelButtonStyle = CancelButtonStyle.INPUT;
  @State enableCancelButtonIconSize: boolean = false;
  @State cancelButtonIconSize: number = 16; //length
  @State enableCancelButtonIconColor: boolean = false;
  @State cancelButtonIconColor: ResourceColor = '#99ffffff';
  @State enableCancelButtonIconSrc: boolean = false;
  @State cancelButtonIconSrc: ResourceStr = '';
  @State enableFontColor: boolean = false;
  @State fontColor: ResourceColor = '#FF182431';
  @State enableCaretStyleWidth: boolean = false;
  @State caretStyleWidth: number = 1.5; //length
  @State enableCaretStyleColor: boolean = false;
  @State caretStyleColor: ResourceColor =  '#007DFF';
  @State enableEnableKeyboardOnFocus: boolean = false;
  @State enableKeyboardOnFocus: boolean = true;
  @State enableSelectionMenuHidden: boolean = false;
  @State selectionMenuHidden: boolean = false;
  @State enableCustomKeyboardOption: boolean = false;
  @State customKeyboardOption: boolean = false;
  @State enableType: boolean = false;
  @State type: SearchType = SearchType.NORMAL;
  @State enableMaxLength: boolean = false;
  @State maxLength: number | undefined = undefined;
  @State enableEnterKeyType: boolean = false;
  @State enterKeyType: EnterKeyType = EnterKeyType.Search;
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
  @State fontFeature: string = '<string> [ <integer> | on | off ]';
  @State enableSelectedBackgroundColor: boolean = false;
  @State selectedBackgroundColor: ResourceColor | undefined = undefined;
  @State enableTextIndent: boolean = false;
  @State textIndent: number = 0; //dimension
  @State enableMinFontSize: boolean = false;
  @State minFontSize: number | undefined = undefined;
  @State enableMaxFontSize: boolean = false;
  @State maxFontSize: number | undefined = undefined;
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
      Search({ value: this.changeValue, placeholder: 'Type to search...' })
        .searchButton(useEnabled(this.enableSearchButtonValue, this.searchButtonValue), {
          fontSize: useEnabled(this.enableSearchButtonOptionFontSize, this.searchButtonOptionFontSize),
          fontColor: useEnabled(this.enableSearchButtonOptionFontColor, this.searchButtonOptionFontColor)
        })
        .placeholderFont({
          size: useEnabled(this.enablePlaceholderFontSize, this.placeholderFontSize),
          weight: useEnabled(this.enablePlaceholderFontWeight, this.placeholderFontWeight),
          style: useEnabled(this.enablePlaceholderFontStyle, this.placeholderFontStyle)
        })
        .textFont({
          size: useEnabled(this.enableTextFontSize, this.textFontSize),
          weight: useEnabled(this.enableTextFontWeight, this.textFontWeight),
          style: useEnabled(this.enableTextFontStyle, this.textFontStyle)
        })
        .textAlign(useEnabled(this.enableTextAlign,this.textAlign))
        .copyOption(useEnabled(this.enableCopyOption,this.copyOption))
        .searchIcon({
          size:useEnabled(this.enableSearchIconSize,this.searchIconSize),
          color:useEnabled(this.enableSearchIconColorLight,this.searchIconColorLight),
          src: useEnabled(this.enableSearchIconSrc,this.searchIconSrc)
        })
        .cancelButton({
          style: useEnabled(this.enableCancelButtonStyle,this.cancelButtonStyle),
          icon: {
            size: useEnabled(this.enableCancelButtonIconSize,this.cancelButtonIconSize),
            color: useEnabled(this.enableCancelButtonIconColor,this.cancelButtonIconColor),
            src: useEnabled(this.enableCancelButtonIconSrc,this.cancelButtonIconSrc)
          }
        })
        .fontColor(useEnabled(this.enableFontColor,this.fontColor))
        .caretStyle({
          width: useEnabled(this.enableCaretStyleWidth, this.caretStyleWidth),
          color: useEnabled(this.enableCaretStyleColor, this.caretStyleColor)
        })
        .enableKeyboardOnFocus(useEnabled(this.enableEnableKeyboardOnFocus,this.enableKeyboardOnFocus))
        .selectionMenuHidden(useEnabled(this.enableSelectionMenuHidden,this.selectionMenuHidden))
        .customKeyboard((result:void) => {},
          { supportAvoidance: useEnabled(this.enableCustomKeyboardOption, this.customKeyboardOption) })
        .type(useEnabled(this.enableType,this.type))
        .maxLength(useEnabled(this.enableMaxLength,this.maxLength))
        .enterKeyType(useEnabled(this.enableEnterKeyType,this.enterKeyType))
        .lineHeight(useEnabled(this.enableLineHeight,this.lineHeight))
        .decoration({
          type: useEnabled(this.enableDecorationType, this.decorationType),
          color: useEnabled(this.enableDecorationColor, this.decorationColor),
          style: useEnabled(this.enableDecorationStyle, this.decorationStyle)
        })
        .letterSpacing(useEnabled(this.enableLetterSpacing,this.letterSpacing))
        .fontFeature(useEnabled(this.enableFontFeature,this.fontFeature))
        .selectedBackgroundColor(useEnabled(this.enableSelectedBackgroundColor,this.selectedBackgroundColor))
        .textIndent(useEnabled(this.enableTextIndent,this.textIndent))
        .minFontSize(useEnabled(this.enableMinFontSize,this.minFontSize))
        .maxFontSize(useEnabled(this.enableMaxFontSize,this.maxFontSize))
        .enablePreviewText(useEnabled(this.enableEnablePreviewText,this.enablePreviewText))
        //.enableHapticFeedback
    }.justifyContent(FlexAlign.Start)
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        ColorBlock({
          title: 'searchButton.option.fontColor',
          isEnabled: this.enableSearchButtonOptionFontColor,
          color: this.searchButtonOptionFontColor
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

        SliderBlock({
          title: 'textFont.size',
          isEnabled: this.enableTextFontSize,
          value: this.textFontSize,
          min: 0,
          max: 200
        })

        RadioBlock({
          title:'textFont.weight',
          isEnabled: this.enableTextFontWeight,
          value: this.textFontWeight,
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
          title: 'textFont.style',
          isEnabled: this.enableTextFontStyle,
          value: this.textFontStyle,
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
          title: 'searchIcon.size',
          isEnabled: this.enableSearchIconSize,
          value: this.searchIconSize,
          min: 0,
          max: 200
        })

        ColorBlock({
          title: 'searchIcon.color',
          isEnabled: this.enableSearchIconColorLight,//无深色模式
          color: this.searchIconColorLight
        })

        //输入？(searchIconSrc)

        RadioBlock({
          title: 'cancelButton.style',
          isEnabled: this.enableCancelButtonStyle,
          value: this.cancelButtonStyle,
          dataSource: [
            { label: 'CONSTANT', value:CancelButtonStyle.CONSTANT },
            { label: 'INVISIBLE', value: CancelButtonStyle.INVISIBLE },
            { label: 'INPUT', value: CancelButtonStyle.INPUT },
          ]
        })

        SliderBlock({
          title: 'cancelButton.icon.size',
          isEnabled: this.enableCancelButtonIconSize,
          value: this.cancelButtonIconSize,
          min: 0,
          max: 200
        })

        ColorBlock({
          title: 'cancelButton.icon.color',
          isEnabled: this.enableCancelButtonIconColor,
          color: this.cancelButtonIconColor
        })

        //输入？(cancelButtonIcon.Src)

        ColorBlock({
          title: 'fontColor',
          isEnabled: this.enableFontColor,
          color: this.fontColor
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
          title: 'customKeyboard.option',
          isEnabled: this.enableCustomKeyboardOption,
          value: this.customKeyboardOption,
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
            { label: 'NORMAL', value: SearchType.NORMAL },
            { label: 'NUMBER', value: SearchType.NUMBER },
            { label: 'PHONE_NUMBER', value: SearchType.PHONE_NUMBER },
            { label: 'EMAIL', value: SearchType.EMAIL },
            { label: 'NUMBER_DECIMAL', value: SearchType.NUMBER_DECIMAL },
            { label: 'URL', value: SearchType.URL },
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

        //输入(fontFeature

        ColorBlock({
          title: 'selectedBackgroundColor',
          isEnabled: this.enableSelectedBackgroundColor,
          color: this.selectedBackgroundColor
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
          max: 200
        })

        SliderBlock({
          title: 'maxFontSize',
          isEnabled: this.enableMaxFontSize,
          value: this.maxFontSize,
          min: 0,
          max: 200
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
      }
    }
  }
}

@Preview
@Component
struct SearchBootcampPreviewer {
  build() {
    SearchBootcamp({
      title: '搜索框/Search'
    })
  }
}

