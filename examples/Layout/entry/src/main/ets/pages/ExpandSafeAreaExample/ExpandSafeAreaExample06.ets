/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { LengthMetrics } from '@kit.ArkUI'

@Entry
@Component
struct SafeAreaExample6 {
  build() {
    Column() {
      Stack() {
        Row()
          .backgroundColor('rgb(39, 135, 217)')
          .width(75)  // 固定宽度
          .height(75) // 固定高度
          .ignoreLayoutSafeArea([LayoutSafeAreaType.SYSTEM], [LayoutSafeAreaEdge.START, LayoutSafeAreaEdge.TOP])  // 设置布局区域延伸取左和上方向，至系统避让区SYSTEM

        Row()
          .backgroundColor('rgb(0, 74, 175)')
          .width(75)
          .height(75)

      }
      .width(200)
      .height(200)
      .backgroundColor(Color.Gray)
      .align(Alignment.TopStart)  // 子组件相对于Stack容器左上对齐
      .padding({
        left: 10  // 设置左侧10vp普通内边距
      })
      .safeAreaPadding(LengthMetrics.vp(10))  // 设置10vp安全区内边距（即组件级安全区）
    }
    .width('100%')
  }
}