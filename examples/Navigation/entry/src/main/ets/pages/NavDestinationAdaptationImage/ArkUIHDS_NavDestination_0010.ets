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

import { PageOneTmp } from './PageOne'
import { PageTwoTmp } from './PageTwo'
import window from '@ohos.window';
import { TitleBar } from '../common/TitleBar'

@Entry
@Component
struct ArkUIHDS_NavDestination_0010 {
  @Provide('pageInfo') pageInfo: NavPathStack = new NavPathStack()
  @State hide: boolean = false;

  @Builder
  PageMap(name: string) {
    if (name === 'pageOne') {
      PageOneTmp()
    } else if (name === 'pageTwo') {
      PageTwoTmp()
    }
  }

  build() {
    Navigation(this.pageInfo) {
      Column() {
        TitleBar({ name: 'NavDestination_0010' })

        Button('STANDARD模式', { stateEffect: true, type: ButtonType.Capsule })
          .width('40%')
          .height(50)
          .margin(10)
          .onClick(() => {
            this.pageInfo.pushPath({ name: 'pageOne' });
          })
        Button('DIALOG模式', { stateEffect: true, type: ButtonType.Capsule })
          .width('40%')
          .height(50)
          .margin(10)
          .onClick(() => {
            this.pageInfo.pushPath({ name: 'pageTwo' });
          })
        Button("销毁当前窗口")
          .backgroundColor('red')
          .width('40%')
          .height(50)
          .margin(10)
          .onClick(() => {
            let win = window.findWindow('testWindow');
            win.destroyWindow();
          })
      }
    }.title('NavIndex API12').navDestination(this.PageMap)
  }
}
