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

// [Start extension_start]
import UIExtensionContentSession from '@ohos.app.ability.UIExtensionContentSession';
import { Entry, Component, Column, Text, FontWeight, Button, ClickEvent } from '@ohos.arkui.component';
import { LocalStorage, State } from '@ohos.arkui.stateManagement';

@Entry()
@Component
struct Extension {
  @State message: string = 'EmbeddedUIExtensionAbility Index';
  private storage: LocalStorage | undefined = this.getUIContext().getSharedLocalStorage();
  private session: UIExtensionContentSession | undefined = this.storage?.get<UIExtensionContentSession>('session');

  build(): void {
    Column() {
      Text(this.message)
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
      Button('terminateSelfWithResult').fontSize(20).onClick((event: ClickEvent) => {
        if (this.session != undefined) {
          this.session?.terminateSelfWithResult({
            resultCode: 1,
            want: {
              bundleName: 'com.samples.uiextensionandaccessibility',
              abilityName: 'ExampleEmbeddedAbility',
            }
          });
        }
      })
    }.width('100%').height('100%')
  }
}
// [End extension_start]
