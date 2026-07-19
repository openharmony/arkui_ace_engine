'use static';
/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

// [Start uiExtensionProvider_start]
import UIExtensionAbility from '@ohos.app.ability.UIExtensionAbility';
import UIExtensionContentSession from '@ohos.app.ability.UIExtensionContentSession';
import Want from '@ohos.app.ability.Want';
import hilog from '@ohos.hilog';
import { LocalStorage } from '@ohos.arkui.stateManagement';

const TAG: string = '[UIExtensionProvider]'
export default class UIExtensionProvider extends UIExtensionAbility {

  onCreate(): void {
    hilog.info(0x0000, TAG, `UIExtensionProvider onCreate`)
  }

  onForeground(): void {
    hilog.info(0x0000, TAG, `UIExtensionProvider onForeground`)
  }

  onBackground(): void {
    hilog.info(0x0000, TAG, `UIExtensionProvider onBackground`)
  }

  async onDestroy(): Promise<void> {
    hilog.info(0x0000, TAG, `UIExtensionProvider onDestroy`)
  }

  onSessionCreate(want: Want, session: UIExtensionContentSession): void {
    hilog.info(0x0000, TAG, `UIExtensionProvider onSessionCreate, want: ${JSON.stringify(want)}`)
    let param: Record<string, UIExtensionContentSession> = {
      'session': session
    };
    let storage: LocalStorage = new LocalStorage(param);
    session.loadContent('pages/UIExtensionComponent/Extension', storage);
  }

  onSessionDestroy(session: UIExtensionContentSession): void {
    hilog.info(0x0000, TAG, `UIExtensionProvider onSessionDestroy`)
  }
}
// [End uiExtensionProvider_start]
