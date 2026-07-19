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

import { FullScreenLaunchComponent } from '@ohos.arkui.advanced.FullScreenLaunchComponent';
import { Builder, Entry, Component, Column, Image, Text, $r } from '@ohos.arkui.component';
import { State } from '@ohos.arkui.stateManagement';

@Builder
function sampleColumnChild(): void {
  Column() {
    Image($r('app.media.app_icon'))
    Text('test')
  }
}

@Entry
@Component
export struct FullScreenLaunch {
  @State appId: string = '5765880207855083101';

  build(): void {
    Column() {
      FullScreenLaunchComponent({
        content: sampleColumnChild,
        appId: this.appId,
        options: {},
        onTerminated: (info) => {
          console.info('onTerminated code: ' + info.code.toString());
        },
        onError: (err) => {
          console.error('onError code: ' + err.code + ', message: ', err.message);
        }
      }).width('80vp').height('80vp')
    }
    .width('100%')
    .height('100%')
    .padding({ left: 12, right: 12 })
  }
}
