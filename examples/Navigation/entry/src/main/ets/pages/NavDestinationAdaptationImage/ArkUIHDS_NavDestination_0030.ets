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

import { TitleBar } from '../common/TitleBar'

@Entry
@Component
struct ArkUIHDS_NavDestination_0030 {
  @State isActiveWLAN: boolean = false
  @State isActiveBluetooth: boolean = false
  @State hide: boolean = false;

  build() {
    Column() {
      TitleBar({ name: 'NavDestination_0030' })

      NavDestination() {
        Button('隐藏标题(是/否)', { stateEffect: true, type: ButtonType.Capsule })
          .backgroundColor('black')
          .width('30%')
          .height(50)
          .margin(20)
          .onClick(() => {
            try {
              if (this.hide == false) {
                this.hide = true;
              } else {
                this.hide = false;
              }
            } catch (error) {
              console.error(`call hide failed`);
            }
          })
      }
      .title('自定义动效')
      .hideTitleBar(this.hide)
    }.height('100%')
  }

  pageTransition() {
    PageTransitionEnter({ duration: 1200 })
      .slide(SlideEffect.Left)
    PageTransitionExit({ delay: 100 })
      .translate({ x: 100.0, y: 100.0 })
      .opacity(0)
  }
}