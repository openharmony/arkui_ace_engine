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

import { CommonButton } from '../../util/CommonButton';

@Entry
@Component
struct TextHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('textHome')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)

        CommonButton({ buttonName: 'TextTextAlign', buttonUrl: 'pages/text/TextTextAlignSample' });
        CommonButton({ buttonName: 'TextBaselineOffset', buttonUrl: 'pages/text/TextBaselineOffsetSample' });
        CommonButton({ buttonName: 'TextBindSelectionMenu', buttonUrl: 'pages/text/TextBindSelectionMenuSample' });
        CommonButton({ buttonName: 'TextCopyOption', buttonUrl: 'pages/text/TextCopyOptionSample' });
        CommonButton({ buttonName: 'TextDataDetectorConfig', buttonUrl: 'pages/text/TextDataDetectorConfigSample' });
        CommonButton({ buttonName: 'TextDecoration', buttonUrl: 'pages/text/TextDecorationSample' });
        CommonButton({ buttonName: 'TextDraggable', buttonUrl: 'pages/text/TextDraggableSample' });
        CommonButton({ buttonName: 'TextEllipsisMode', buttonUrl: 'pages/text/TextEllipsisModeSample' });
        CommonButton({ buttonName: 'TextEnableDataDetector', buttonUrl: 'pages/text/TextEnableDataDetectorSample' });
        CommonButton({ buttonName: 'TextFontColor', buttonUrl: 'pages/text/TextFontColorSample' });
        CommonButton({ buttonName: 'TextFontFamily', buttonUrl: 'pages/text/TextFontFamilySample' });
        CommonButton({ buttonName: 'TextFont', buttonUrl: 'pages/text/TextFontSample' });
        CommonButton({ buttonName: 'TextFontSize', buttonUrl: 'pages/text/TextFontSizeSample' });
        CommonButton({ buttonName: 'TextFontStyle', buttonUrl: 'pages/text/TextFontStyleSample' });
        CommonButton({ buttonName: 'TextFontWeight', buttonUrl: 'pages/text/TextFontWeightSample' });
        CommonButton({
          buttonName: 'TextHeightAdaptivePolicy',
          buttonUrl: 'pages/text/TextHeightAdaptivePolicySample'
        });
        CommonButton({ buttonName: 'TextIndent', buttonUrl: 'pages/text/TextTextIndentSample' });
        CommonButton({ buttonName: 'TextLetterSpacing', buttonUrl: 'pages/text/TextLetterSpacingSample' });
        CommonButton({ buttonName: 'TextMaxFontSize', buttonUrl: 'pages/text/TextMaxFontSizeSample' });
        CommonButton({ buttonName: 'TextMaxLines', buttonUrl: 'pages/text/TextMaxLinesSample' });
        CommonButton({ buttonName: 'TextMinFontSize', buttonUrl: 'pages/text/TextMinFontSizeSample' });
        CommonButton({ buttonName: 'TextSelection', buttonUrl: 'pages/text/TextSelectionSample' });
        CommonButton({ buttonName: 'TextTextCase', buttonUrl: 'pages/text/TextTextCaseSample' });
        CommonButton({ buttonName: 'TextTextOverflow', buttonUrl: 'pages/text/TextTextOverflowSample' });
        CommonButton({ buttonName: 'TextTextShadow', buttonUrl: 'pages/text/TextTextShadowSample' });
        CommonButton({ buttonName: 'TextWordBreak', buttonUrl: 'pages/text/TextWordBreakSample' });
        CommonButton({ buttonName: 'TextLineHeight', buttonUrl: 'pages/text/TextLineHeightSample' });
      }
      .padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}