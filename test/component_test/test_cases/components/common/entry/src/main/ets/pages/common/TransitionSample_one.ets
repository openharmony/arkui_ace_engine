/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import transitionTest_one from '../MyTest/TransitionTest_one'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct TransitionSample_one {
  @State flag: boolean = true;

  aboutToAppear(): void {
    loadComponentTestEntry(transitionTest_one)
  }

  build() {
    Column() {
      Button('ButtonTransition')
        .onClick(() => {
          this.flag = !this.flag;
        })
      if (this.flag) {
        Image($r('app.media.app_icon')).width(200).height(200)
          .transition({
            opacity: 1,
            translate: { x: 10, y: 10, z: 10 },
            scale: {
              x: 1,
              y: 1,
              z: 1,
              centerX: 1,
              centerY: 1
            },
            rotate: {
              x: 1,
              y: 1,
              z: 1,
              angle: 90,
              centerX: 1,
              centerY: 1,
              centerZ: 1,
              perspective: 1
            }
          })
          .id('imageTransition1')
      }
    }
  }
}