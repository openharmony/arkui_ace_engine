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
import { LengthUnit } from '@kit.ArkUI';

@Component
export struct TextBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State text: string = '这是一段文本。This is a text.';
  @State textLength: number = this.text.length;
  @State enableTextAlign: boolean = false;
  @State textAlign: TextAlign = TextAlign.Start;
  @State enableTextOverflow: boolean = false;
  @State textOverflow: TextOverflow = TextOverflow.Clip;
  @State enableMaxLines: boolean = false;
  @State maxLines: number | undefined = undefined;
  @State enableLineHeight: boolean = false; //文本行高
  @State lineHeight: number | undefined = undefined;
  @State enableTextDecorationType: boolean = false;
  @State textDecorationType: TextDecorationType = TextDecorationType.None;
  @State enableTextDecorationColor: boolean = false;
  @State textDecorationColor: ResourceColor = Color.Black;
  @State enableTextDecorationStyle: boolean = false;
  @State textDecorationStyle: TextDecorationStyle = TextDecorationStyle.SOLID;
  @State enableBaselineOffset: boolean = false;
  @State baselineOffset: number = 0;
  @State enableLetterSpacing: boolean = false;
  @State letterSpacing: number | undefined = undefined;
  @State enableMinFontSize: boolean = false;
  @State minFontSize: number | undefined = undefined;
  @State enableMaxFontSize: boolean = false;
  @State maxFontSize: number | undefined = undefined;
  @State enableTextCase: boolean = false;
  @State textCase: TextCase = TextCase.Normal;
  @State enableFontColor: boolean = false;
  @State fontColor: ResourceColor | undefined = undefined;
  @State enableFontSize: boolean = false;
  @State fontSize: number = 16; //16fp
  @State enableFontStyle: boolean = false;
  @State fontStyle: FontStyle = FontStyle.Normal;
  @State enableFontWeight: boolean = false;
  @State fontWeight: number | FontWeight | string = FontWeight.Normal;
  @State enableCopyOption: boolean = false;
  @State copyOption: CopyOptions = CopyOptions.None;
  @State enableDraggable: boolean = false;
  @State eDraggable: boolean = false;
  @State enableTextShadowRadius: boolean = false;
  @State textShadowRadius: number = 0;
  @State enableTextShadowType: boolean = false;
  @State textShadowType: ShadowType = ShadowType.COLOR;
  @State enableTextShadowColor: boolean = false;
  @State textShadowColor: Color | string | Resource | ColoringStrategy = Color.Black;
  @State enableTextShadowOffsetX: boolean = false;
  @State textShadowOffsetX: number = 0;
  @State enableTextShadowOffsetY: boolean = false;
  @State textShadowOffsetY: number = 0;
  @State enableTextShadowFill: boolean = false;
  @State textShadowFill: boolean = false;
  @State enableHeightAdaptivePolicy: boolean = false;
  @State heightAdaptivePolicy: TextHeightAdaptivePolicy = TextHeightAdaptivePolicy.MAX_LINES_FIRST
  @State enableTextIndent: boolean = false;
  @State textIndent: number = 0;
  @State enableWordBreak: boolean = false;
  @State wordBreak: WordBreak = WordBreak.BREAK_WORD;
  @State enableSelectionStart: boolean = false;
  @State selectionStart: number = -1;
  @State enableSelectionEnd: boolean = false;
  @State selectionEnd: number = -1;
  @State enableEllipsisMode: boolean = false;
  @State ellipsisMode: EllipsisMode = EllipsisMode.END;
  @State enableEnableDataDetector: boolean = false
  @State enableDataDetector: boolean = false;
  @State enableTextDataDetectorConfigTypes: boolean = false;
  @State textDataDetectorConfigTypes: TextDataDetectorType[] = [];
  // @State enableTextDataDetectorConfigColor: boolean = false;
  // @State textDataDetectorConfigColor: ResourceColor = '#ff0a59f7';
  // @State enableTextDataDetectorConfigDecorationType: boolean = false;
  // @State textDataDetectorConfigDecorationType: TextDecorationType = TextDecorationType.Underline
  // @State enableTextDataDetectorConfigDecorationColor: boolean = false;
  // @State textDataDetectorConfigDecorationColor: ResourceColor = '#ff0a59f7';
  // @State enableTextDataDetectorConfigDecorationStyle: boolean = false;
  // @State textDataDetectorConfigDecorationStyle: TextDecorationStyle = TextDecorationStyle.SOLID
  @State enableBindSelectionMenuSpanType: boolean = false;
  @State bindSelectionMenuSpanType: TextSpanType = TextSpanType.TEXT;
  // @State enableBindSelectionMenuContent: boolean = false;
  // @State bindSelectionMenuContent: CustomBuilder = () => any | void
  @State enableBindSelectionMenuResponseType: boolean = false;
  @State bindSelectionMenuResponseType: TextResponseType = TextResponseType.LONG_PRESS;
  @State enableFontFeature: boolean = false;
  @State fontFeature: string = 'normal | <feature-tag-value>';
  @State enableLineSpacingValue: boolean = false;
  @State lineSpacingValue: number = 0;
  @State enableLineSpacingUnit: boolean = false;
  @State lineSpacingUnit: LengthUnit = LengthUnit.VP;
  @State enablePrivacySensitive: boolean = false;
  @State privacySensitive: boolean = false;
  @State enableLineBreakStrategy: boolean = false;
  @State lineBreakStrategy: LineBreakStrategy = LineBreakStrategy.GREEDY
  @State enableTextSelectable: boolean = false;
  @State textSelectable: TextSelectableMode = TextSelectableMode.SELECTABLE_UNFOCUSABLE
  // @State enableEditMenuOptionsContent: boolean = false; //EditMenuOption
  // @State editMenuOptionsContent: ResourceStr = 'MenuName'
  // @State enableEditMenuOptionsIcon: boolean = false;
  // @State editMenuOptionsIcon: ResourceStr = 'MenuIcon'
  // @State enableEditMenuOptionsId: boolean = false;
  // @State editMenuOptionsId: TextMenuItemId =
  @State enableMinFontScale: boolean = false;
  @State minFontScale: number | undefined = undefined;
  @State enableMaxFontScale: boolean = false;
  @State maxFontScale: number | undefined = undefined;
  @State enableHalfLeading: boolean = false;
  @State halfLeading: boolean = false;
  @State enableFontValueSize: boolean = false;
  @State fontValueSize: number = 16.0;
  @State enableFontValueWeight: boolean = false;
  @State fontValueWeight: FontWeight | number = 400 | FontWeight.Normal;
  @State enableFontValueStyle: boolean = false;
  @State fontValueStyle: FontStyle = FontStyle.Normal;
  @State enableFontOptions: boolean = false;
  @State fontOptions: boolean = false;
  @State enableFontWeightWeight: boolean = false;
  @State fontWeightWeight: number | FontWeight | string = FontWeight.Normal;
  @State enableCaretColor: boolean = false;
  @State caretColor: ResourceColor = '#007DFF';
  @State enableSelectedBackgroundColor: boolean = false;
  @State selectedBackgroundColor: ResourceColor = '#007DFF'

  // @State enableTextSpanType: boolean = false;
  // @State textSpanType: TextSpanType = TextSpanType.TEXT;
  // @State enableTextResponseType: boolean = false;
  // @State textResponseType: TextResponseType = TextResponseType.RIGHT_CLICK

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
      Text(this.text)
        .textAlign(useEnabled(this.enableTextAlign, this.textAlign))
        .textOverflow({ overflow: useEnabled(this.enableTextOverflow, this.textOverflow) })
        .maxLines(useEnabled(this.enableMaxLines, this.maxLines))
        .lineHeight(useEnabled(this.enableLineHeight, this.lineHeight))
        .decoration({
          type: useEnabled(this.enableTextDecorationType, this.textDecorationType),
          color: useEnabled(this.enableTextDecorationColor, this.textDecorationColor),
          style: useEnabled(this.enableTextDecorationStyle, this.textDecorationStyle),
        })
        .baselineOffset(useEnabled(this.enableBaselineOffset, this.baselineOffset))
        .letterSpacing(useEnabled(this.enableLetterSpacing, this.letterSpacing))
        .minFontSize(useEnabled(this.enableMinFontSize, this.minFontSize))
        .maxFontSize(useEnabled(this.enableMaxFontSize, this.maxFontSize))
        .textCase(useEnabled(this.enableTextCase, this.textCase))
        .fontColor(useEnabled(this.enableFontColor, this.fontColor))
        .fontSize(useEnabled(this.enableFontSize, this.fontSize))
        .fontStyle(useEnabled(this.enableFontStyle, this.fontStyle))
        .fontWeight(useEnabled(this.enableFontWeight, this.fontWeight))
        .copyOption(useEnabled(this.enableCopyOption, this.copyOption))
        .draggable(useEnabled(this.enableDraggable, this.eDraggable))
        .shadow({
          radius: useEnabled(this.enableTextShadowRadius, this.textShadowRadius),
          type: useEnabled(this.enableTextShadowType, this.textShadowType),
          color: useEnabled(this.enableTextShadowColor, this.textShadowColor),
          offsetX: useEnabled(this.enableTextShadowOffsetX, this.textShadowOffsetX),
          offsetY: useEnabled(this.enableTextShadowOffsetY, this.textShadowOffsetY),
          fill: useEnabled(this.enableTextShadowFill, this.textShadowFill)
        })
        .heightAdaptivePolicy(useEnabled(this.enableHeightAdaptivePolicy, this.heightAdaptivePolicy))
        .textIndent(useEnabled(this.enableTextIndent, this.textIndent))
        .wordBreak(useEnabled(this.enableWordBreak, this.wordBreak))
        .selection(useEnabled(this.enableSelectionStart, this.selectionStart),
          useEnabled(this.enableSelectionEnd, this.selectionEnd))
        .ellipsisMode(useEnabled(this.enableEllipsisMode, this.ellipsisMode))
        .enableDataDetector(useEnabled(this.enableEnableDataDetector, this.enableDataDetector))
        .dataDetectorConfig({
          types: useEnabled(this.enableTextDataDetectorConfigTypes, this.textDataDetectorConfigTypes),
          onDetectResultUpdate: (result: string) => {
          },
        })
          // .bindSelectionMenu({TextSpanType:useEnabled(this.enableBindSelectionMenuSpanType,
          // this.bindSelectionMenuSpanType),
          // this.Content: (result: string)=>{},
          // ResponseType:useEnabled(this.enableBindSelectionMenuResponseType,this.bindSelectionMenuResponseType)})
        .fontFeature(useEnabled(this.enableFontFeature, this.fontFeature))
        .lineSpacing({
          value: useEnabled(this.enableLineSpacingValue, this.lineSpacingValue),
          unit: useEnabled(this.enableLineSpacingUnit, this.lineSpacingUnit)
        })
        .privacySensitive(useEnabled(this.enablePrivacySensitive, this.privacySensitive))
        .lineBreakStrategy(useEnabled(this.enableLineBreakStrategy, this.lineBreakStrategy))
        .textSelectable(useEnabled(this.enableTextSelectable, this.textSelectable))
        .minFontScale(useEnabled(this.enableMinFontScale, this.minFontScale))
        .maxFontScale(useEnabled(this.enableMaxFontScale,
          this.maxFontScale))// .halfLeading(useEnabled(this.enableHalfLeading,this.halfLeading))
          //   .font(fontValue:{size:useEnabled(this.enableFontValueSize,this.fontValueSize),
          // weight:useEnable(this.enableFontValueWeight,this.fontValueWeight),
          // style:useEnable(this.enableFontValueStyle,this.fontValueStyle)},
          // options:useEnabled(this.enableFontOptions,this.fontOptions))
        .fontWeight(useEnabled(this.enableFontWeightWeight, this.fontWeightWeight))
    }.justifyContent(FlexAlign.Start)
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {

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
          title: 'maxLines',
          isEnabled: this.enableMaxLines,
          value: this.maxLines,
          min: 0,
          max: 20
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
          isEnabled: this.enableTextDecorationType,
          value: this.textDecorationType,
          dataSource: [
            { label: 'None', value: TextDecorationType.None },
            { label: 'Underline', value: TextDecorationType.Underline },
            { label: 'Overline', value: TextDecorationType.Overline },
            { label: 'LineThrough', value: TextDecorationType.LineThrough },
          ]
        })

        ColorBlock({
          title: 'decoration.color',
          isEnabled: this.enableTextDecorationColor,
          color: this.textDecorationColor
        })

        RadioBlock({
          title: 'decoration.style',
          isEnabled: this.enableTextDecorationStyle,
          value: this.textDecorationStyle,
          dataSource: [
            { label: 'SOLID', value: TextDecorationStyle.SOLID },
            { label: 'DOUBLE', value: TextDecorationStyle.DOUBLE },
            { label: 'DOTTED', value: TextDecorationStyle.DOTTED },
            { label: 'DASHED', value: TextDecorationStyle.DASHED },
            { label: 'WAVY', value: TextDecorationStyle.WAVY },
          ]
        })

        SliderBlock({
          title: 'baseLineOffSet',
          isEnabled: this.enableBaselineOffset,
          value: this.baselineOffset,
          min: 0,
          max: 20
        })

        SliderBlock({
          title: 'letterSpacing',
          isEnabled: this.enableLetterSpacing,
          value: this.letterSpacing,
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
          title: 'textCase',
          isEnabled: this.enableTextCase,
          value: this.textCase,
          dataSource: [
            { label: 'Normal', value: TextCase.Normal },
            { label: 'LowerCase', value: TextCase.LowerCase },
            { label: 'UpperCase', value: TextCase.UpperCase },
          ]
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
          isEnabled: this.enableCopyOption,
          value: this.copyOption,
          dataSource: [
            { label: 'None', value: CopyOptions.None },
            { label: 'InApp', value: CopyOptions.InApp },
            { label: 'LocalDevice', value: CopyOptions.LocalDevice },
          ]
        })

        RadioBlock({
          title: 'draggable',
          isEnabled: this.enableDraggable,
          value: this.eDraggable,
          dataSource: [
            { label: 'false', value: false },
            { label: 'true', value: true },
          ]
        })

        SliderBlock({
          title: 'textShadow.radius',
          isEnabled: this.enableTextShadowRadius,
          value: this.textShadowRadius,
          min: 0,
          max: 360
        })

        RadioBlock({
          title: 'textShadow.type',
          isEnabled: this.enableTextShadowType,
          value: this.textShadowType,
          dataSource: [
            { label: 'COLOR', value: ShadowType.COLOR },
            { label: 'BLUR', value: ShadowType.BLUR },
          ]
        })

        ColorBlock({
          title: 'textShadow.color',
          isEnabled: this.enableTextShadowColor,
          color: this.textShadowColor
        })

        //XY
        SliderBlock({
          title: 'textShadow.OffsetX',
          isEnabled: this.enableTextShadowOffsetX,
          value: this.textShadowOffsetX,
          min: 0,
          max: 200
        })

        SliderBlock({
          title: 'textShadow.OffsetY',
          isEnabled: this.enableTextShadowOffsetY,
          value: this.textShadowOffsetY,
          min: 0,
          max: 200
        })

        RadioBlock({
          title: 'textShadow.fill',
          isEnabled: this.enableTextShadowFill,
          value: this.textShadowFill,
          dataSource: [
            { label: 'false', value: false },
            { label: 'true', value: true },
          ]
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

        SliderBlock({
          title: 'textIndent',
          isEnabled: this.enableTextIndent,
          value: this.textIndent,
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

        SliderBlock({
          title: 'selection.start',
          isEnabled: this.enableSelectionStart,
          value: this.selectionStart,
          min: -1,
          max: this.textLength
        })

        SliderBlock({
          title: 'selection.end',
          isEnabled: this.enableSelectionEnd,
          value: this.selectionEnd,
          min: -1,
          max: this.textLength
        })

        RadioBlock({
          title: 'ellipsisMode',
          isEnabled: this.enableEllipsisMode,
          value: this.ellipsisMode,
          dataSource: [
            { label: 'START', value: EllipsisMode.START },
            { label: 'CENTER', value: EllipsisMode.CENTER },
            { label: 'END', value: EllipsisMode.END },
          ]
        })

        RadioBlock({
          title: 'enableDataDetector',
          isEnabled: this.enableEnableDataDetector,
          value: this.enableDataDetector,
          dataSource: [
            { label: 'false', value: false },
            { label: 'true', value: true },
          ]
        })

        RadioBlock({
          title: 'textDataDetectorConfig.types',
          isEnabled: this.enableTextDataDetectorConfigTypes,
          value: this.textDataDetectorConfigTypes,
          dataSource: [
            { label: 'NULL', value: [] },
            { label: 'PHONE_NUMBER', value: TextDataDetectorType.PHONE_NUMBER },
            { label: 'URL', value: TextDataDetectorType.URL },
            { label: 'EMAIL', value: TextDataDetectorType.EMAIL },
            { label: 'ADDRESS', value: TextDataDetectorType.ADDRESS },
            { label: 'DATE_TIME', value: TextDataDetectorType.DATE_TIME },
          ]
        })

        // ColorBlock({
        //   title: 'textDataDetectorConfig.color',
        //   isEnabled: this.enableTextDataDetectorConfigColor,
        //   color: this.textDataDetectorConfigColor
        // })
        //
        // RadioBlock({
        //   title:'textDataDetectorConfig.decorationTypes',
        //   isEnabled: this.enableTextDataDetectorConfigDecorationType,
        //   value: this.textDataDetectorConfigDecorationType,
        //   dataSource: [
        //     {label: 'None', value: TextDecorationType.None },
        //     {label: 'Underline', value: TextDecorationType.Underline },
        //     {label: 'Overline', value: TextDecorationType.Overline },
        //     {label: 'LineThrough', value: TextDecorationType.LineThrough },
        //   ]
        // })
        //
        // ColorBlock({
        //   title: 'textDataDetectorConfig.decorationColor',
        //   isEnabled: this.enableTextDataDetectorConfigDecorationColor,
        //   color: this.textDataDetectorConfigDecorationColor
        // })
        // //
        // RadioBlock({
        //   title:'TextDataDetectorConfig.decorationStyle',
        //   isEnabled: this.enableTextDataDetectorConfigDecorationStyle,
        //   value: this.textDataDetectorConfigDecorationStyle,
        //   dataSource: [
        //     {label: 'SOLID', value: TextDecorationStyle.SOLID },
        //     {label: 'DOUBLE', value: TextDecorationStyle.DOUBLE },
        //     {label: 'DOTTED', value: TextDecorationStyle.DOTTED },
        //     {label: 'DASHED', value: TextDecorationStyle.DASHED },
        //     {label: 'WAVY', value: TextDecorationStyle.WAVY },
        //   ]
        // })

        RadioBlock({
          title: 'bindSelectionMenu.spanType',
          isEnabled: this.enableBindSelectionMenuSpanType,
          value: this.bindSelectionMenuSpanType,
          dataSource: [
            { label: 'TEXT', value: TextSpanType.TEXT },
            { label: 'IMAGE', value: TextSpanType.IMAGE },
            { label: 'MIXED', value: TextSpanType.MIXED },
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
          title: 'lineSpacing.unit',
          isEnabled: this.enableLineSpacingUnit,
          value: this.lineSpacingUnit,
          dataSource: [
            { label: 'PX', value: LengthUnit.PX },
            { label: 'VP', value: LengthUnit.VP },
            { label: 'FP', value: LengthUnit.FP },
            { label: 'PERCENT', value: LengthUnit.PERCENT },
            { label: 'LPX', value: LengthUnit.LPX },
          ]
        })

        RadioBlock({
          title: 'privacySensitive',
          isEnabled: this.enablePrivacySensitive,
          value: this.privacySensitive,
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
          title: 'textSelectable',
          isEnabled: this.enableTextSelectable,
          value: this.textSelectable,
          dataSource: [
            { label: 'SELECTABLE_UNFOCUSABLE', value: TextSelectableMode.SELECTABLE_UNFOCUSABLE },
            { label: 'SELECTABLE_FOCUSABLE', value: TextSelectableMode.SELECTABLE_FOCUSABLE },
            { label: 'UNSELECTABLE', value: TextSelectableMode.UNSELECTABLE },
          ]
        })

        SliderBlock({
          title: 'minFontScale',
          isEnabled: this.enableMinFontScale,
          value: this.minFontScale,
          min: 0,
          max: 1
        })

        SliderBlock({
          title: 'maxFontScale',
          isEnabled: this.enableMaxFontScale,
          value: this.maxFontScale,
          min: 1,
          max: 200
        })

        RadioBlock({
          title: 'halfLeading',
          isEnabled: this.enableHalfLeading,
          value: this.halfLeading,
          dataSource: [
            { label: 'false', value: false },
            { label: 'true', value: true },
          ]
        })

        SliderBlock({
          title: 'fontValue.size',
          isEnabled: this.enableFontValueSize,
          value: this.fontValueSize,
          min: 1,
          max: 200
        })

        RadioBlock({
          title: 'fontValue.weight',
          isEnabled: this.enableFontValueWeight,
          value: this.fontValueWeight,
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
          title: 'fontValue.style',
          isEnabled: this.enableFontValueStyle,
          value: this.fontValueStyle,
          dataSource: [
            { label: 'Normal', value: FontStyle.Normal },
            { label: 'Italic', value: FontStyle.Italic },
          ]
        })

        RadioBlock({
          title: 'fontOptions',
          isEnabled: this.enableFontOptions,
          value: this.fontOptions,
          dataSource: [
            { label: 'false', value: false },
            { label: 'true', value: true },
          ]
        })

        RadioBlock({
          title: 'fontWeight.weight',
          isEnabled: this.enableFontWeightWeight,
          value: this.fontWeightWeight,
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

        ColorBlock({
          title: 'CaretColor',
          isEnabled: this.enableCaretColor,
          color: this.caretColor
        })

        ColorBlock({
          title: 'SelectedBackgroundColor',
          isEnabled: this.enableSelectedBackgroundColor,
          color: this.selectedBackgroundColor
        })
      }
    }
  }
}

@Preview
@Component
struct TextBootcampPreviewer {
  build() {
    TextBootcamp({
      title: '文本显示/Text'
    })
  }
}

