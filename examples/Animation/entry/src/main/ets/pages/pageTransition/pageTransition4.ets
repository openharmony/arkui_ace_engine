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

// page1.ets
@Entry
@Component
struct PageTransitionExample4 {
  build() {
    Column() {
      Navigator({ target: 'pages/pageTransition/pageTransition3', type: NavigationType.Push }) {
        Image($r('app.media.ddd')).width('100%').height('100%')    // 图片存放在media文件夹下
      }
    }
  }

  // 自定义方式2：使用系统提供的多种默认效果(平移、缩放、透明度等)
  pageTransition() {
    // 该页面进入动画时长为1000ms，尽量与另一页面的退出动画时长匹配
    PageTransitionEnter({ duration: 1000 })
      .slide(SlideEffect.Left)
    // 该页面退出动画时长为1200ms，尽量与另一页面的进入动画时长匹配
    PageTransitionExit({ duration: 1200 })
      .translate({ x: 100.0, y: 100.0 })
      .opacity(0)
  }
}