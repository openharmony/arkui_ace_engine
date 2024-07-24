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

import sharedTransitionTest from '../MyTest/SharedTransitionTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SharedTransitionSample {
  aboutToAppear(): void {
    loadComponentTestEntry(sharedTransitionTest)
  }

  build() {
    Navigator({ target: 'pages/MyTest/SharedTransitionTargetPage' }) {
      Rect({ width: '90%', height: 50 })
        .width(50)
        .height(50)
        .fill(Color.Pink)
        .id('rectSharedTransition1')
        .sharedTransition('sharedTransitionRect', {
          duration: 800,
          curve: Curve.Linear,
          delay: 10,
          motionPath: {
            path: 'Mstart.x start.y L300 200 L300 500 Lend.x end.y',
            from: 0.0,
            to: 1.0,
            rotatable: true
          },
          zIndex: 10,
          type: SharedTransitionEffectType.Static
        })
    }
    .padding({ left: 20, top: 20 })
  }
}