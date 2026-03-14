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
import router from '@ohos.router'

@Entry
@Component
struct Index {
  build() {
    Row() {
      Column({ space: 20 }) {
        Button("NavDestination支持隐藏返回图标基础场景")
          .onClick(() => {
            router.pushUrl({ url: 'pages/NavDestinationHideBackButton/navdes' })
          }).fontSize(20).width("90%")
        // Button("navdestiantion子页_modifier")
        //   .onClick(() => {
        //     router.pushUrl({ url: 'pages/navdes_modifier' })
        //   }).fontSize(30).width("90%")
      }
      .width('100%')
      .height('100%')
      .alignItems(HorizontalAlign.Center)
    }
  }
}






