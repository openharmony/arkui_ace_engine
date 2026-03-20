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

import router from '@ohos.router';
// xxx.ets
@Entry
@Component
struct MotionPathExample {
  @State toggle: boolean = true
  @State rotatable: boolean = true

  build() {
    Column() {
      Column() {
        Button("返回")
          .onClick(() => {
            router.back()
          })
      }
      .width('100%')
      .height('10%')
      .backgroundColor(Color.Orange)
      .justifyContent(FlexAlign.Center)
      Button('click me').margin(50)
        // 执行动画：从起点移动到(300,200)，再到(300,500)，再到终点
        .motionPath({ path: 'Mstart.x start.y L300 320 L300 600 Lend.x end.y', from: 0.0, to: 1.0, rotatable: this.rotatable })
        .onClick(() => {
          animateTo({ duration: 4000, curve: Curve.Linear,
          onFinish : () => {
            this.rotatable = false
          }}, () => {
            this.toggle = !this.toggle // 通过this.toggle变化组件的位置
          })
        })
    }.width('100%').height('100%').alignItems(this.toggle ? HorizontalAlign.Start : HorizontalAlign.Center)
  }
}