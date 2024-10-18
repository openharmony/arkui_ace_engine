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
import transitionTest_two from '../MyTest/TransitionTest_two'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct TransitionSample_two {
  @State flag: boolean = true;

  aboutToAppear(): void {
    loadComponentTestEntry(transitionTest_two)
  }

  build() {
    Column() {
      Button('ButtonTransition')
        .onClick(() => {
          this.flag = !this.flag;
        })
      if (this.flag) {
        Image($r('app.media.app_icon'))
          .width(200)
          .height(200)
          .transition(TransitionEffect.asymmetric(TransitionEffect.move(TransitionEdge.START),
            TransitionEffect.move(TransitionEdge.END))
            .combine(TransitionEffect.translate({ x: 100 }).animation({ duration: 1000 })))
          .id('imageTransition2')
      }
    }
  }
}