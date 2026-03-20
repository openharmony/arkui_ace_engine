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

// xxx.ets
@Entry
@Component
struct SharedTransitionExample1 {
  @State active: boolean = false

  build() {
    Column() {
      Navigator({ target: 'pages/sharedTransition/sharedTransition2', type: NavigationType.Push }) {
        Image($r('app.media.startIcon')).width(50).height(50)
          .sharedTransition('sharedImage', { duration: 800, curve: Curve.Linear, delay: 100 })
      }.padding({ left: 20, top: 20 })
      .onClick(() => {
        this.active = true
      })
    }
  }
}