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

import imageGeneration from '@ohos.arkui.intelligence.imageGeneration';
import { CanvasMode, ImageGenerateState } from "../types/Declaration";
import { DoodleBoardArea } from "./DoodleBoardArea";
import { TextInputArea } from "./TextInputArea";
import { HomeTitle } from "./TitleArea";
import { LandscapeSelectFuncArea } from "./UserInteractiveArea";
import { GeneratingArea } from './CanvasGenerate';
import { image } from "@kit.ImageKit";
import { calcAABB } from './ImageOperate';

export class styleItem {
  name: ResourceStr = 'NA'
  resourceAddr?: image.PixelMap | ResourceStr
}

@ComponentV2
export struct CanvasHome {
  @Local titleName: string = '灵感画布'
  @Local currentCanvasMode: CanvasMode = CanvasMode.GENERAL_MODE;
  @Local currentGenerateState: ImageGenerateState = ImageGenerateState.CONFIGURATION;
  @Param @Require imageInfoArr: Array<imageGeneration.ImageItem>;
  @Param @Require styles?: Array<imageGeneration.ImageStyle>;
  @Param userPrompt: string = '';

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
          currentGenerateState: this.currentGenerateState!!,
          imageInfoArr: this.imageInfoArr,
          styles: this.styles,
          userPrompt: this.userPrompt
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
  @Param @Require styles?: Array<imageGeneration.ImageStyle>;
  @Param currentGenerateState: ImageGenerateState = ImageGenerateState.CONFIGURATION;
  @Event $currentGenerateState: (state: ImageGenerateState) => void = (state: ImageGenerateState) => {
  };
  @Param @Require imageInfoArr: Array<imageGeneration.ImageItem>;
  @Local imageMatrixArr: number[][] =
    [[
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1
    ], [
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1
    ], [
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1
    ], [
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1
    ]]

  @Local imgCounts: number = 0;
  @Param userPrompt: string = '';
  @Local resultList: string[] = [];

  private initImageMatrix(): void {
    let input: imageGeneration.ImageItem[] = [];
    for (let i = 0; i < this.imageInfoArr.length; i++) {
      if (this.imageInfoArr[i].rect) {
        input.push(this.imageInfoArr[i]);
      }
    }

    let res: number[][] = calcAABB(input, this.getUIContext().vp2px(386),
      this.getUIContext().vp2px(386));
    for (let i = 0; i < res.length; i++) {
      this.imageMatrixArr[i] = res[i];
    }
  }

  aboutToAppear(): void {
    this.initImageMatrix();
  }

  build() {
    Scroll() {
      Column() {
        // doodle area
        Row() {
          DoodleBoardArea({
            imageInfoArr: this.imageInfoArr,
            imageMatrixArr: this.imageMatrixArr
          })
            .margin({ left: 69, right: 54 })
          if (this.currentGenerateState === ImageGenerateState.CONFIGURATION) {
            LandscapeSelectFuncArea({
              imageInfoArr: this.imageInfoArr,
              imageMatrixArr: this.imageMatrixArr,
              styles: this.styles,
              setImgCounts: (count: number) => {
                this.imgCounts = count;
              }
            })
              .margin({ right: 16 })
          }
          if (this.currentGenerateState === ImageGenerateState.GENERATED) {
            HistoryArea({ resultList: this.resultList })
              .margin({ right: 16 })
          }
        }
        .margin({ top: 21, bottom: 28 })
        // text input area
        if (this.currentGenerateState === ImageGenerateState.CONFIGURATION) {
          TextInputArea({
            changeGenerateState: (state: ImageGenerateState) => {
              this.$currentGenerateState(state);
            },
            imgCounts: this.imgCounts,
            userPrompt: this.userPrompt
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
        if (this.currentGenerateState === ImageGenerateState.GENERATED) {
          ContinueOperateArea({
            currentGenerateState: this.currentGenerateState,
            changeGenerateState: (state: ImageGenerateState) => {
              this.$currentGenerateState(state);
            }
          })
            .margin({ bottom: 14 })
        }
      }
    }
    .scrollBar(BarState.Off)
    .height('100%')
    .width('100%')
  }
}