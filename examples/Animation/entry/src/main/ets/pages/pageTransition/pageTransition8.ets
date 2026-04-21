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
import { router } from '@kit.ArkUI'

@Entry
@Component
struct PageTransitionExample8 {
  @State scale1: number = 1
  @State opacity1: number = 1

  build() {
    Column() {
      Button("页面2").onClick(()=>{
        router.back()
      })
        .width(200)
        .height(60)
        .fontSize(36)
    }.scale({ x: this.scale1 }).opacity(this.opacity1).height("100%").width("100%").justifyContent(FlexAlign.Center)
  }
}