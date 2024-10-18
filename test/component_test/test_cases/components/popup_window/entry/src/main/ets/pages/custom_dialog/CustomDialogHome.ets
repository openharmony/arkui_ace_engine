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
struct CustomDialogHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('CustomDialogHome')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)
        CommonButton({ buttonName: 'CustomDialogBuilder', buttonUrl: 'pages/custom_dialog/CustomDialogBuilderSample' });
        CommonButton({ buttonName: 'CustomDialogCancel', buttonUrl: 'pages/custom_dialog/CustomDialogCancelSample' });
        CommonButton({
          buttonName: 'CustomDialogAutoCancel',
          buttonUrl: 'pages/custom_dialog/CustomDialogAutoCancelSample'
        });
        CommonButton({
          buttonName: 'CustomDialogAlignment',
          buttonUrl: 'pages/custom_dialog/CustomDialogAlignmentSample'
        });
        CommonButton({ buttonName: 'CustomDialogOffset', buttonUrl: 'pages/custom_dialog/CustomDialogOffsetSample' });
        CommonButton({
          buttonName: 'CustomDialogCustomStyle',
          buttonUrl: 'pages/custom_dialog/CustomDialogCustomStyleSample'
        });
        CommonButton({
          buttonName: 'CustomDialogGridCount',
          buttonUrl: 'pages/custom_dialog/CustomDialogGridCountSample'
        });
        CommonButton({
          buttonName: 'CustomDialogMaskColor',
          buttonUrl: 'pages/custom_dialog/CustomDialogMaskColorSample'
        });
        CommonButton({
          buttonName: 'CustomDialogMaskRect',
          buttonUrl: 'pages/custom_dialog/CustomDialogMaskRectSample'
        });
        CommonButton({
          buttonName: 'CustomDialogOpenAnimation',
          buttonUrl: 'pages/custom_dialog/CustomDialogOpenAnimationSample'
        });
        CommonButton({
          buttonName: 'CustomDialogCloseAnimation',
          buttonUrl: 'pages/custom_dialog/CustomDialogCloseAnimationSample'
        });
        CommonButton({
          buttonName: 'CustomDialogShowInSubWindow',
          buttonUrl: 'pages/custom_dialog/CustomDialogShowInSubWindowSample'
        });
        CommonButton({
          buttonName: 'CustomDialogBackgroundColor',
          buttonUrl: 'pages/custom_dialog/CustomDialogBackgroundColorSample'
        });
        CommonButton({
          buttonName: 'CustomDialogCornerRadius',
          buttonUrl: 'pages/custom_dialog/CustomDialogCornerRadiusSample'
        });
        CommonButton({ buttonName: 'CustomDialogIsModal', buttonUrl: 'pages/custom_dialog/CustomDialogIsModalSample' });
      }
      .padding('20vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}