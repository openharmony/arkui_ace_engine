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

/**
 * 设置图片是否跟随系统语言方向
 */
@Entry
@Component
struct Index {
  build() {
    Column() {
      Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Start }) {
        Row() {
          // 图片不跟随系统语言方向
          Image($r('app.media.ocean'))
            .width(110).height(110).margin(15)
            .matchTextDirection(false)
        }
        Row() {
          // 图片跟随系统语言方向
          Image($r('app.media.ocean'))
            .width(110).height(110).margin(15)
            .matchTextDirection(true)
        }
      }
    }.height(320).width(360).padding({ right: 10, top: 10 })
  }
}