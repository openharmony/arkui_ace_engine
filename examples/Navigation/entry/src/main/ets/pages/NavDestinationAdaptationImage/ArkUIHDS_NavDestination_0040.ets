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
import { TitleBar } from '../common/TitleBar'

@Entry
@Component
struct ArkUIHDS_NavDestination_0040 {
  @Provide('pageInfo') pageInfo: NavPathStack = new NavPathStack()
  @State hide: boolean = false;

  @Builder NavigationTitle() {
    Row() {
      Column() {
        Text('自定义标题')
          .fontColor('red')
          .fontSize(30)
          .lineHeight(41)
          .fontWeight(700)
        Text('自定义副标题')
          .fontColor('red')
          .fontSize(14)
          .lineHeight(19)
          .opacity(0.4)
          .margin({ top: 2, bottom: 20 })
      }.alignItems(HorizontalAlign.Start)
    }
  }

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
        TitleBar({ name: 'NavDestination_0040' })

        Button('STANDARD模式', { stateEffect: true, type: ButtonType.Capsule })
          .width('40%')
          .height(40)
          .margin(10)
          .onClick(() => {
            this.pageInfo.pushPath({ name: 'pageOne' });
          })
        Button('DIALOG模式', { stateEffect: true, type: ButtonType.Capsule })
          .width('40%')
          .height(40)
          .margin(5)
          .onClick(() => {
            this.pageInfo.pushPath({ name: 'pageTwo' });
          })
      }
    }.title('NavDestination40').navDestination(this.PageMap)
  }
}
