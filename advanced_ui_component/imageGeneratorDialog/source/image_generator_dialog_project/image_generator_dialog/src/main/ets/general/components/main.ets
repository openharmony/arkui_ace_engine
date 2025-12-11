/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import arkuiNamespaces from "@kit.ArkUI"
import { CanvasHome } from "./canvasPages/CanvasHome";
import { CanvasMode } from "../types/Declaration";

@ComponentV2
export struct ImageGeneratorDialog {
  options?: arkuiNamespaces.imageGeneration.GeneratorDialogOptions;
  @Local width_: Dimension = 650;
  @Local height_: Dimension = 560;
  @Local currentCanvasMode: CanvasMode = CanvasMode.COMMON_MODE

  build() {
    Scroll() {
      Column() {
        if (this.currentCanvasMode === CanvasMode.COMMON_MODE) {
          CanvasHome()
        }
      }
      .height(this.height_)
      .width(this.width_)
      .borderRadius(32)
      .clip(true)
      .alignSelf(ItemAlign.Center)
    }
    .width('100%')
    .height('100%')
    .scrollable(ScrollDirection.FREE)
  }
}
