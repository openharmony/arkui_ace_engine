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
struct ReplaceSymbolEffectCROSS_FADE {
  @State triggerValueReplace: number = 0;
  replaceFlag: boolean = true;

  build() {
    Column() {
      Text('快速替换动效')
      SymbolGlyph(this.replaceFlag ? $r('sys.symbol.checkmark_circle') : $r('sys.symbol.repeat_1'))
        .fontSize(96)
        .symbolEffect(new ReplaceSymbolEffect(EffectScope.WHOLE,
          ReplaceEffectType.CROSS_FADE), this.triggerValueReplace)
      Button('trigger').onClick(() => {
        this.replaceFlag = !this.replaceFlag;
        this.triggerValueReplace = this.triggerValueReplace + 1;
      })
    }
  }
}