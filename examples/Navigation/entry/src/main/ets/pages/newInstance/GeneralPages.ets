/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { MyButton } from './Index'
import observer from '@ohos.arkui.observer';

@Component
export struct GeneralPageOne {
  stack: NavPathStack = new NavPathStack()

  func (info: NavDestinationInfo) {
    if (info.state == observer.NavDestinationState.ON_APPEAR) {
      console.log('this is test [1730]')
    }
  }

  aboutToAppear(): void {
    observer.on('navDestinationUpdate', this.func.bind(this))
  }

  aboutToDisappear(): void {
    observer.off('navDestinationUpdate', this.func)
  }

  build() {
    NavDestination() {
      MyButton({
        text: 'to page two',
        onClickFunction: () => {

        }
      })
    }.title('General Page One')
    .onReady((ctx) => {
      this.stack = ctx.pathStack
    })
  }
}