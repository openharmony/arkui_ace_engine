/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

// @Entry
@Component
struct MyPage {
    build() {
        Button("My page")
    }
    pageTransition() {
        console.log("page page transition")
        /* todo
        PageTransitionEnter({ duration: 1200 })
          .slide(SlideEffect.Left)
        PageTransitionExit({ delay: 100 })
          .translate({ x: 100.0, y: 100.0 })
          .opacity(0)
        */
    }
}
