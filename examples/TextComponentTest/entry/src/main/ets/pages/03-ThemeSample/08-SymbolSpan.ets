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
struct Index_SymbolSpan {
  build() {
    Scroll() {
      Column() {
        Column() {
          Column() {
            Text(' 测试点 SymbolSpan create ')
            Text() {
              SymbolSpan($r('sys.symbol.ohos_folder_badge_plus'))
            }
            .backgroundColor(Color.White)
          }.borderWidth(1)

          Blank().borderWidth(5).height(1)

          Column()
          Text(' 测试点 SymbolSpan fontSize ')
          Text() {
            SymbolSpan($r('sys.symbol.ohos_folder_badge_plus'))
              .fontSize($r('app.float.ModeNumber20_50'))
          }
          .backgroundColor(Color.White)
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 SymbolSpan fontColor ')
          Text() {
            SymbolSpan($r('sys.symbol.ohos_folder_badge_plus'))
              .fontSize(50)
              .renderingStrategy(SymbolRenderingStrategy.MULTIPLE_COLOR)
              .fontColor([$r('app.color.ModeColor'), $r('app.color.ModeColorYellow_Pink')])
          }
        }.borderWidth(1)
        Blank().borderWidth(5).height(1)
      }

    }
  }
}