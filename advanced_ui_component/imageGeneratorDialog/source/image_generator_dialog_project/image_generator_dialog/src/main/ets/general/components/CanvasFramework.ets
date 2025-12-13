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

import { CanvasMode, ImageGenerateState } from "../types/Declaration";
import { DoodleBoardArea } from "./DoodleBoardArea";
import { TextInputArea } from "./TextInputArea";
import { HomeTitle } from "./TitleArea";
import { LandscapeSelectFuncArea } from "./UserInteractiveArea";
import { GeneratingArea } from './CanvasGenerate';

@ComponentV2
export struct CanvasHome {
  @Local titleName: string = '灵感画布'
  @Local currentCanvasMode: CanvasMode = CanvasMode.GENERAL_MODE;
  @Local currentGenerateState: ImageGenerateState = ImageGenerateState.CONFIGURATION;

  @Builder
  homeTitleBuilder() {
    HomeTitle({
      titleName: this.titleName,
      currentGenerateState: this.currentGenerateState
    })
  }

  build() {
    NavDestination() {
      if (this.currentCanvasMode === CanvasMode.GENERAL_MODE) {
        LandscapeLayout({
          currentGenerateState: this.currentGenerateState!!
        })
      } else if (this.currentCanvasMode === CanvasMode.DOODLE_MODE) {

      }
    }
    .hideBackButton(true)
    .title(this.homeTitleBuilder)
  }
}

@ComponentV2
struct LandscapeLayout {
  @Param currentGenerateState: ImageGenerateState = ImageGenerateState.CONFIGURATION;
  @Event $currentGenerateState: (state: ImageGenerateState) => void = (state: ImageGenerateState) => {};
  build() {
    Column() {
      // doodle area
      Row() {
        DoodleBoardArea()
          .margin({ left: 69, right: 54 })
        if (this.currentGenerateState === ImageGenerateState.CONFIGURATION) {
          LandscapeSelectFuncArea()
            .margin({ right: 16 })
        }

      }
      .margin({ top: 21, bottom: 28 })
      // text input area
      if (this.currentGenerateState === ImageGenerateState.CONFIGURATION) {
        TextInputArea({
          changeGenerateState: (state: ImageGenerateState) => {
            this.$currentGenerateState(state);
          }
        })
          .margin({ bottom: 14 })
      }
      if (this.currentGenerateState === ImageGenerateState.GENERATING ||
        this.currentGenerateState === ImageGenerateState.BEFORE_GENERATED) {
        GeneratingArea({
          currentGenerateState: this.currentGenerateState,
          changeGenerateState: (state: ImageGenerateState) => {
            this.$currentGenerateState(state);
          }
        })
      }
    }
    .height('100%')
    .width('100%')
  }
}