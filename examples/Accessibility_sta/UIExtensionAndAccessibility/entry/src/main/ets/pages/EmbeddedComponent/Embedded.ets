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

// [Start embedded_start]
import { Entry, Component, Row, Column, Text, EmbeddedComponent, EmbeddedType, NavDestination, $r } from '@ohos.arkui.component';
import { State } from '@ohos.arkui.stateManagement';
import Want from '@ohos.app.ability.Want';

@Entry
@Component
export struct Embedded {
  @State message: string = 'Message: ';
  private want: Want = {
    bundleName: 'com.samples.uiextensionandaccessibility',
    abilityName: 'ExampleEmbeddedAbility',
  };
  build(): void {
    // [StartExclude embedded_start]
    NavDestination() {
      // [EndExclude embedded_start]
      Row() {
        Column() {
          Text(this.message).fontSize(30)
          EmbeddedComponent(this.want, EmbeddedType.EMBEDDED_UI_EXTENSION)
            .width('100%')
            .height('90%')
            .onTerminated((info) => {
              this.message = `Termination: code = ${info.code} , want = ${JSON.stringify(info.want)}`;
            })
            .onError((error) => {
              this.message = `Error: code = ${error.code}`;
            })
        }
        .width('100%')
      }
      .height('100%')
      // [StartExclude embedded_start]
    }
    .backgroundColor('#f1f2f3')
    .title($r('app.string.Embedded_Component_title'))
    // [EndExclude embedded_start]
  }
}
// [End embedded_start]
