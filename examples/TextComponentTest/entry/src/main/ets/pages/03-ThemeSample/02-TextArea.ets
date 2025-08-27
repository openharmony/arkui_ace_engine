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

@Entry
@Component
struct Index_TextArea {
  build() {
    Scroll() {
      Column() {
        Column() {
          Text(' 测试点 TextArea create placeholder ')
          TextArea({ placeholder: $r('app.string.TextInputPlaceholder') }).borderColor(Color.Red)
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 TextArea create text ')
          TextArea({ text: $r('app.string.TextInputPlaceholder') })
        }.borderWidth(1).borderColor(Color.Red)

        Blank().borderWidth(5).height(1)
      }
    }
  }
}