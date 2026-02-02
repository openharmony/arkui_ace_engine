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

import { BusinessError } from '@kit.BasicServicesKit';

@Entry
@Component
struct UecPage {
  @State message: string = 'Hello World';

  build() {
    RelativeContainer() {
      UIExtensionComponent({
        bundleName: "com.example.testuea",
        moduleName: "entry",
        abilityName: "EmptyUIExtensionAbility",
        parameters: {
          "ability.want.params.uiExtensionType": "sys/commonUI"
        }
      })
        .onRemoteReady((proxy) => {
        })
        .onReceive((data) => {
          this.message = JSON.stringify(data);
          console.log('testTag this.message', this.message)
        })
        .onTerminated((terminateInfo: TerminationInfo) => {
          this.message = `terminate code: ${terminateInfo.code}, want: ${terminateInfo.want}`;
          console.log('testTag this.message onTerminated', this.message)
        })
        .onError((error: BusinessError) => {
          this.message = `error code: ${error.code}, error msg: ${error.message}`;
          console.log('testTag this.message error', this.message)
        })
        .offset({ x: 0, y: 30 })
        .size({ width: 400, height: 700 })
        .border({
          width: 5,
          color: 0x317AF7,
          radius: 10,
          style: BorderStyle.Dotted
        })
        .margin(10)

    }
    .height('100%')
    .width('100%')
  }
}