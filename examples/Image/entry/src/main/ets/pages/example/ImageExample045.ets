/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Entry
@Component
struct ChangeWidth {
  @State wh: number = 200

  build() {
    Column({ space: 10 }) {
      Image("https://cp1.douguo.com/upload/caiku/d/e/b/600_de930a0bd7492906df26a297856dde1b.jpeg")
        .height(200)
        .width(this.wh)
        .alt($r("app.media.startIcon")) // 图片加载失败时显示的替代资源
        .contentTransition(ContentTransitionEffect.OPACITY) // 宽度变化时淡入淡出过渡

      Button("ChangeW")
        .onClick(() => {
          animateTo({ duration: 500 }, () => {
            this.wh += 100 // 修改宽度状态变量，触发动画
          })
        })
    }
  }
};