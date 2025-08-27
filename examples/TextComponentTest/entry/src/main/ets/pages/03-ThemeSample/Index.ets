/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import router from '@ohos.router';


@Entry
@Component
struct Index_Text {
  @State msgTextContent: string = ''

  build() {
    Scroll() {
      Column() {

        Column({ space: 5 }) {
          Button(' Text ')
            .onClick(() => {
              router.pushUrl({
                url: 'pages/Text',
              })
            })

          Button(' TextInput ')
            .onClick(() => {
              router.pushUrl({
                url: 'pages/TextInput',
              })
            })

          Button(' TextArea ')
            .onClick(() => {
              router.pushUrl({
                url: 'pages/TextArea',
              })
            })

          Button(' Search ')
            .onClick(() => {
              router.pushUrl({
                url: 'pages/Search',
              })
            })

          Button(' ContainerSpan ')
            .onClick(() => {
              router.pushUrl({
                url: 'pages/ContainerSpan',
              })
            })

          Button(' ImageSpan ')
            .onClick(() => {
              router.pushUrl({
                url: 'pages/ImageSpan',
              })
            })

          Button(' Marquee ')
            .onClick(() => {
              router.pushUrl({
                url: 'pages/Marquee',
              })
            })

          Button(' Span ')
            .onClick(() => {
              router.pushUrl({
                url: 'pages/Span',
              })
            })

          Button(' SymbolSpan ')
            .onClick(() => {
              router.pushUrl({
                url: 'pages/SymbolSpan',
              })
            })

          Button(' SymbolGlyph ')
            .onClick(() => {
              router.pushUrl({
                url: 'pages/SymbolGlyph',
              })
            })

          Button(' Hyperlink ')
            .onClick(() => {
              router.pushUrl({
                url: 'pages/Hyperlink',
              })
            })

        }.borderWidth(1)

      }
    }
  }
}