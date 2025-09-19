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
struct ReplaceSymbolEffect {
  @State triggerValueReplace: number = 0;
  @State renderMode: number = 1;
  replaceFlag: boolean = true;

  build() {
    Column() {
      Text('禁用动效')
      SymbolGlyph(this.replaceFlag ? $r('sys.symbol.eye_slash') : $r('sys.symbol.eye'))
        .fontSize(96)
        .renderingStrategy(this.renderMode)
        .symbolEffect(new ReplaceSymbolEffect(EffectScope.LAYER,
          ReplaceEffectType.SLASH_OVERLAY), this.triggerValueReplace)
      Button('trigger').onClick(() => {
        this.replaceFlag = !this.replaceFlag;
        this.triggerValueReplace = this.triggerValueReplace + 1;
      })
    }
  }
}