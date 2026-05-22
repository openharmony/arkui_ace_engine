/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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
struct SecondInterfaceBindMenu {
  build() {
    Row(){
      Column() {
        Text('单击展示菜单')
          .fontSize(30)
          .fontWeight(FontWeight.Bold)
      }
      .bindMenu([
        {
          value: '跳转Index',
          action: () => {
            router.pushUrl({
              url: 'pages/Index',
            })
            console.info('handle Menu select')
          }
        }

      ])
    }
    .width('100%')
    .height('100%')
  }
}