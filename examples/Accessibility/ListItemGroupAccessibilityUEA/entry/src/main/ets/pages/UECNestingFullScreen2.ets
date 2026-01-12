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

import { InnerFullScreenLaunchComponent, LaunchController } from '@kit.ArkUI';

@Entry
@Component
struct Index {
  appId1: string = '5765880207853275505';
  appId2: string = '5765880207854372375';

  @Builder
  ColumChild() {
    Column() {
      Text('FullScreenLaunchComponent').fontSize(16).margin({ top: 100 })
      Button('start 日出日落')
        .onClick(() => {
          let appId2: string = '5765880207854372375';
          this.controller.launchAtomicService(appId2, {})
        }).height(30).width('50%').margin({ top: 50 })
      Button('start 充值')
        .onClick(() => {
          let appId2: string = '5765880207853275489';
          this.controller.launchAtomicService(appId2, {})
        }).height(30).width('50%').margin({ top: 50 })
    }.backgroundColor(Color.Pink).height('100%').width('100%')
  }

  controller: LaunchController = new LaunchController();

  build() {
    Column() {
      InnerFullScreenLaunchComponent({
        content: this.ColumChild,
        controller: this.controller,
      })
    }
    .width('100%').height('100%')
  }
}

