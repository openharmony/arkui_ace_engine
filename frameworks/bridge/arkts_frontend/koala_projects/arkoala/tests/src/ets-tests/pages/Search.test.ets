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
struct SearchTest {
    build() {
        Column() {
            Text("SearchTest")
            Search({value: "value", placeholder: "placeholder", icon: "icon"})
            .searchButton("search", {fontSize: 14, fontColor: 0xffabcd})
            .fontColor(0xabcdef)
            .searchIcon({size: "33px", color: "#aaaaaa", src: "path/to/search/icon"})
            .cancelButton({ style: CancelButtonStyle.INPUT,
                icon: {size: "22px", color: "#bbbbbb", src: "path/to/cancel/icon"} })
            .caretStyle({width: 5, color: "#cccccc"})
            .placeholderColor("#bababa")
            .placeholderFont({size: "10px", weight: FontWeight.Normal, family: "Serif, Monospace", style: FontStyle.Normal})
            .textFont({size: "20px", weight: FontWeight.Regular, family: "Arial, Times", style: FontStyle.Italic})
            .copyOption(CopyOptions.LocalDevice)
            .textAlign(TextAlign.End)
            .enableKeyboardOnFocus(true)
            .selectionMenuHidden(true)
        }
    }
}
