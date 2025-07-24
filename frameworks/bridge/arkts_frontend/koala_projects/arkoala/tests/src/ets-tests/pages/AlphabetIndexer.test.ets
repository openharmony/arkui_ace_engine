/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Entry
@Component
struct AlphabetIndexerTest {

  build() {
    AlphabetIndexer({arrayValue : ["A", "B", "C"], selected : 1})
    .color("0xaaaaaa")
    .selectedColor("0xbbbbbb")
    .popupColor("0xcccccc")
    .selectedBackgroundColor("0xdddddd")
    .popupBackground("0xeeeeee")
    .popupSelectedColor("0xffffff")
    .popupUnselectedColor("0xabcdef")
    .popupItemBackgroundColor("0xfedcba")
    .usingPopup(true)
    .selectedFont({size: "10px", weight: FontWeight.Regular, family: "Arial", style: FontStyle.Normal})
    .popupFont({size: "20px", weight: FontWeight.Bold, family: "Times", style: FontStyle.Italic})
    .font({size: "30px", weight: FontWeight.Medium, family: "Serif", style: FontStyle.Normal})
    .popupItemFont({size: "10px", weight: FontWeight.Lighter, family: "Monospace", style: FontStyle.Italic})
    .itemSize("55px")
    .alignStyle(IndexerAlign.Right, "8fp")
    .selected(5)
    .popupPosition({x: "55px", y: "77fp"})
    .autoCollapse(true)
  }
}
