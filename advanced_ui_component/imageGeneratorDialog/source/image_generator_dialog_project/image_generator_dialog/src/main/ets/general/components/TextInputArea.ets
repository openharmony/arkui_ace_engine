/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

@ComponentV2
export struct TextInputArea {
  build() {
    Row() {
      Column()
        .height(40)
        .width(510)
        .margin({ top: 3, bottom: 2, left: 16, right: 12 })
        .borderRadius(31.11)
        .borderWidth(0.5)

      Column()
        .borderRadius(31.11)
        .borderWidth(0.5)
        .height(40)
        .width(96)
        .margin({ top: 3, bottom: 2, right: 16 })
    }
    .width('100%')
    .height(45)
  }
}