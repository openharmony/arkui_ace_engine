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
struct Index_SymbolGlyph {
  build() {
    Scroll() {
      Column() {
        Column() {
          Column() {
            Text(' 测试点 SymbolGlyph create ')
            SymbolGlyph($r('sys.symbol.ohos_folder_badge_plus'))
              .backgroundColor(Color.White)
          }.borderWidth(1)

          Blank().borderWidth(5).height(1)

          Column() {
            Text(' 测试点 SymbolGlyph fontSize ')
            SymbolGlyph($r('sys.symbol.ohos_folder_badge_plus'))
              .fontSize($r('app.float.ModeNumber20_50'))
              .backgroundColor(Color.White)
          }.borderWidth(1)

          Blank().borderWidth(5).height(1)

          Column() {
            Text(' 测试点 SymbolGlyph fontColor ')
            SymbolGlyph($r('sys.symbol.ohos_folder_badge_plus'))
              .fontSize(50)
              .renderingStrategy(SymbolRenderingStrategy.MULTIPLE_COLOR)
              .fontColor([$r('app.color.ModeColor'), $r('app.color.ModeColorYellow_Pink')])
          }.borderWidth(1)

          Blank().borderWidth(5).height(1)

          Column() {
            Text(' 用来对比 Min ')
            Text('浅色 minFontScale 1.0，深色 minFontScale 1.0，原本字体大小是 50 ')
              .borderWidth(2)
              .borderColor(Color.Blue)
            SymbolGlyph($r('sys.symbol.ohos_folder_badge_plus'))
              .backgroundColor(Color.White)
              .fontSize(50)
              .minFontScale(1)
          }.borderWidth(1)

          Column() {
            Text(' 测试点 Text SetMinFontScale minFontScale ')
            Text(' 浅色 minFontScale 0，深色 minFontScale 1.0，原本字体大小是 50 ').borderWidth(2).borderColor(Color.Red)
            SymbolGlyph($r('sys.symbol.ohos_folder_badge_plus'))
              .backgroundColor(Color.White)
              .fontSize(50)
              .minFontScale($r('app.float.TextMinFontScale'))
          }.borderWidth(1)

          Blank().borderWidth(5).height(1)

          Column() {
            Text(' 用来对比 Max ')
            Text('浅色 maxFontScale 1.0，深色 maxFontScale 1.0，原本字体大小是 50').borderWidth(2).borderColor(Color.Blue)
            SymbolGlyph($r('sys.symbol.ohos_folder_badge_plus'))
              .backgroundColor(Color.White)
              .fontSize(50)
              .maxFontScale(1)
          }.borderWidth(1)

          Column() {
            Text(' 测试点 Text SetMaxFontScale maxFontScale ')
            Text(' 浅色 maxFontScale 3.2，深色 maxFontScale 1.0，原本字体大小是 16 ')
              .borderWidth(2)
              .borderColor(Color.Red)
            SymbolGlyph($r('sys.symbol.ohos_folder_badge_plus'))
              .backgroundColor(Color.White)
              .fontSize(50)
              .maxFontScale($r('app.float.TextMaxFontScale'))
          }.borderWidth(1)

          Blank().borderWidth(5).height(1)
        }
      }
    }
  }
}