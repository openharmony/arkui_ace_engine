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
struct AlertDialogHome {
  build() {
    Scroll() {
      Flex({ direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {
        Text('AlertDialogHome')
          .padding('10vp')
          .width('100%')
          .fontSize('25fp')
          .textAlign(TextAlign.Center)
        CommonButton({
          buttonName: 'AlertDialogPrimaryButton',
          buttonUrl: 'pages/alert_dialog/AlertDialogPrimaryButtonSample'
        });
        CommonButton({
          buttonName: 'AlertDialogSecondaryButton',
          buttonUrl: 'pages/alert_dialog/AlertDialogSecondaryButtonSample'
        });
        CommonButton({ buttonName: 'AlertDialogConfirm', buttonUrl: 'pages/alert_dialog/AlertDialogConfirmSample' });
        CommonButton({ buttonName: 'AlertDialogButtons', buttonUrl: 'pages/alert_dialog/AlertDialogButtonsSample' });
        CommonButton({
          buttonName: 'AlertDialogButtonsDirection',
          buttonUrl: 'pages/alert_dialog/AlertDialogButtonDirectionSample'
        });
        CommonButton({
          buttonName: 'AlertDialogAlertDialogParam',
          buttonUrl: 'pages/alert_dialog/AlertDialogAlertDialogParamSample'
        });
      }
      .padding('10vp')
      .width('100%')
    }.margin({ bottom: 60 })
    .width('100%')
  }
}