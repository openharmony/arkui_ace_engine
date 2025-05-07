/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { IndexImmersive } from './16-navigationIndexImmersive';
import { SearchIndex } from './15-navigationSearchIndex';

@Entry
@Component
struct Navigation_Main {
  @Provide('pageInfos') pageInfos: NavPathStack = new NavPathStack();

  aboutToAppear(): void {
    this.pageInfos.disableAnimation(true)
    this.pageInfos.pushPath({ name: 'IndexImmersive' })
  }

  @Builder
  PageMap(name: string) {
    if (name === 'IndexImmersive') {
      IndexImmersive()
    } else if (name == 'searchIndex') {
      SearchIndex()
    }
  }

  build() {
    Navigation(this.pageInfos) {
      Column() {
        Button('pushPath', { stateEffect: true, type: ButtonType.Capsule })
          .width('80%')
          .height(40)
          .margin(20)
          .onClick(() => {
            this.pageInfos.pushPath({ name: 'IndexImmersive' })
          })
      }
    }
    .navDestination(this.PageMap)
    .hideToolBar(true)
    .hideTitleBar(true)
    .hideBackButton(true)
    .hideNavBar(true)
  }
}