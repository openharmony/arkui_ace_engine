/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import uiMaterial from "@ohos.arkui.uiMaterial";
@Entry
@Component
struct PageTextInput {
  @State message: string = 'Hello World';
  @State material: uiMaterial.Material | undefined = undefined;

  build() {
    Column() {
      Column({space: 10}) {
        Stack() {
          Text("back text")
          TextInput({ placeholder: "input some words" })
            .width(200)
            .height(100)
        }
        Stack() {
          Text("back text")
          TextInput({ placeholder: "input some words" })
            .width(200)
            .height(100)
            .backgroundColor("#F2F1F3F5")
        }
        Stack() {
          Text("back text")
          TextInput({ placeholder: "input some words" })
            .width(200)
            .height(100)
            .systemMaterial(this.material)
        }
      }
      .width('100%')
      Button("type NONE")
        .onClick(() => {
          this.material = new uiMaterial.Material({ type: uiMaterial.MaterialType.NONE });
          console.info("material type none click");
        })
      Button("type SEMI_TRANSPARENT")
        .onClick(() => {
          this.material = new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT });
          console.info("material type SEMI_TRANSPARENT click");
        })
    }
    .height('100%')
  }
}