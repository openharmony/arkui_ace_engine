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
struct SymbolShadow {
  @State isActive: boolean = true;

  options: ShadowOptions = {
    radius: 10.0,
    color: Color.Blue,
    offsetX: 10,
    offsetY: 10,
  };

  build() {
    Column() {
      Text('阴影能力')
      SymbolGlyph($r('sys.symbol.ohos_wifi'))
        .fontSize(96)
        .symbolEffect(new HierarchicalSymbolEffect(EffectFillStyle.ITERATIVE), !this.isActive)
        .symbolShadow(this.options)
      Button(!this.isActive ? '关闭' : '播放').onClick(() => {
        this.isActive = !this.isActive;
      })
    }
  }
}