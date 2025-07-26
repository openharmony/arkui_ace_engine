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

//import { ArkLinearGradient } from "../../../../external/arkoala/arkui/src/ArkLinearGradient"

@Entry
@Component
struct DataPanelTest {
  build() {
      DataPanel(
        {
          values: [11, 22, 33, 44, 55],
          max: 77,
          type: DataPanelType.Circle
        }
      )
      .closeEffect(true)
      .trackBackgroundColor("0xabcdef")
      .strokeWidth("5px")
      .valueColors(["0x123456", "0x654321"])
      .trackShadow({radius: 77, offsetX: 88, offsetY: 99,
                   colors: [
                    new LinearGradient([{color: "0x111111", offset: 3}, {color: "0x222222", offset: 5}]),
                    new LinearGradient([{color: "0x333333", offset: 7}, {color: "0x555555", offset: 8}])]
                   })
  }
}
