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
import { CommonButton } from '../../util/CommonButton'

@Entry
@Component
struct ActionSheetHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('ActionSheet')
          .padding('15vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)

        CommonButton({
          buttonName: 'ActionSheetAlignmentSample',
          buttonUrl: 'pages/action_sheet/ActionSheetAlignmentSample'
        });
        CommonButton({
          buttonName: 'ActionSheetAutoCancelSample',
          buttonUrl: 'pages/action_sheet/ActionSheetAutoCancelSample'
        });
        CommonButton({
          buttonName: 'ActionSheetBackgroundBlurStyleSample',
          buttonUrl: 'pages/action_sheet/ActionSheetBackgroundBlurStyleSample'
        });
        CommonButton({
          buttonName: 'ActionSheetBackgroundColorSample',
          buttonUrl: 'pages/action_sheet/ActionSheetBackgroundColorSample'
        });
        CommonButton({
          buttonName: 'ActionSheetCancelSample',
          buttonUrl: 'pages/action_sheet/ActionSheetCancelSample'
        });
        CommonButton({
          buttonName: 'ActionSheetConfirmSample',
          buttonUrl: 'pages/action_sheet/ActionSheetConfirmSample'
        });
        CommonButton({
          buttonName: 'ActionSheetIsModalSample',
          buttonUrl: 'pages/action_sheet/ActionSheetIsModalSample'
        });
        CommonButton({
          buttonName: 'ActionSheetMaskRectSample',
          buttonUrl: 'pages/action_sheet/ActionSheetMaskRectSample'
        });
        CommonButton({
          buttonName: 'ActionSheetMessageSample',
          buttonUrl: 'pages/action_sheet/ActionSheetMessageSample'
        });
        CommonButton({
          buttonName: 'ActionSheetOffsetSample',
          buttonUrl: 'pages/action_sheet/ActionSheetOffsetSample'
        });
        CommonButton({
          buttonName: 'ActionSheetSheetsSample',
          buttonUrl: 'pages/action_sheet/ActionSheetSheetsSample'
        });
        CommonButton({
          buttonName: 'ActionSheetShowInSubWindowSample',
          buttonUrl: 'pages/action_sheet/ActionSheetShowInSubWindowSample'
        });
        CommonButton({
          buttonName: 'ActionSheetSubtitleSample',
          buttonUrl: 'pages/action_sheet/ActionSheetSubtitleSample'
        });
        CommonButton({ buttonName: 'ActionSheetTitleSample', buttonUrl: 'pages/action_sheet/ActionSheetTitleSample' });
      }
      .padding('5vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}