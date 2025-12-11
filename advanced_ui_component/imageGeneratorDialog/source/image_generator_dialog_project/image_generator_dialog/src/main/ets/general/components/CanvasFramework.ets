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

import { CanvasMode } from "../types/Declaration";
import { DoodleBoardArea } from "./DoodleBoardArea";
import { TextInputArea } from "./TextInputArea";
import { HomeTitle } from "./TitleArea";
import { LandscapeSelectFuncArea } from "./UserInteractiveArea";

@ComponentV2
export struct CanvasHome {
  @Local titleName: string = '灵感画布'
  @Local currentCanvasMode: CanvasMode = CanvasMode.GENERAL_MODE;

  @Builder
  homeTitleBuilder() {
    HomeTitle({ titleName: this.titleName })
  }

  build() {
    NavDestination() {
      if (this.currentCanvasMode === CanvasMode.GENERAL_MODE) {
        LandscapeLayout()
      } else if (this.currentCanvasMode === CanvasMode.DOODLE_MODE) {

      }
    }
    .hideBackButton(true)
    .title(this.homeTitleBuilder)
  }
}

@ComponentV2
struct LandscapeLayout {
  build() {
    Column() {
      // doodle area
      Row() {
        DoodleBoardArea()
          .margin({ left: 69, right: 54 })
        LandscapeSelectFuncArea()
          .margin({ right: 16 })
      }
      .margin({ top: 21, bottom: 28 })
      // text input area
      TextInputArea()
        .margin({ bottom: 14 })
    }
    .height('100%')
    .width('100%')
  }
}