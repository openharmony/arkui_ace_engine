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
struct MenuItemTest {

  @Builder
  MyMenu(){
    Menu() {
      MenuItem({content: "content", labelInfo: "label"})
      .selected(true)
      .contentFont({size: "20px", weight: FontWeight.Regular, family: "Arial, Times", style: FontStyle.Italic})
      .contentFontColor("#abcdef")
      .labelFont({size: "10fp", weight: FontWeight.Regular, family: "Monospace", style: FontStyle.Normal})
      .labelFontColor("#fedcba")
      .selectIcon(true)
    }
  }

  build() {
      Column() {
        Text('MenuItem Test')
        this.MyMenu()
      }
  }
}
