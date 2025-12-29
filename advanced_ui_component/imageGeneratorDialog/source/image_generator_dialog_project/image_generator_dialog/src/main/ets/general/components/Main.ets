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
import { Constants } from '../common/CommonConstants';
import { CanvasHome } from "./CanvasFramework";
import { TextTouchUpComponent } from "./TextTouchUp"
import { window } from '@kit.ArkUI';
import { CanvasLayoutDirection, CanvasMode, LogTag } from '../types/Declaration';
import { WinSizeChangeCallbackManager } from '../utils/CallbackManagers';

@ComponentV2
export struct ImageGeneratorDialog {
  stack: NavPathStack = new NavPathStack();
  @Param @Require options?: imageGeneration.GeneratorDialogOptions;
  @Local width_: Dimension = 650;
  @Local height_: Dimension = 560;
  private MAX_IMAGE_COUNT: number = 4;
  @Local imageInfoArr: Array<imageGeneration.ImageItem> = [];
  @Local stylesArr: Array<imageGeneration.ImageStyle> = [];
  @Local userPrompt: string = '';
  // var for layout
  private curWindow?: window.Window = undefined;
  @Provider('globalCanvasMode') curCanvasMode: CanvasMode = CanvasMode.DEFAULT;
  @Provider('globalSheetType') curSheetType: SheetType = SheetType.CONTENT_COVER;
  @Provider('globalLayoutDirection') curLayoutDirection: CanvasLayoutDirection = CanvasLayoutDirection.DEFAULT;
  updateCanvasLayoutProperties: (size: Size) => void = (size: Size) => {
    let breakpointPX = this.getUIContext().vp2px(Constants.CONTENT_COVER_DISPLAY_MIN_WIDTH);
    this.curSheetType = size.width >= breakpointPX ? SheetType.CONTENT_COVER : SheetType.BOTTOM;
    this.curLayoutDirection = size.width >= size.height ? CanvasLayoutDirection.HORIZONTAL : CanvasLayoutDirection.VERTICAL;

    if (this.curSheetType === SheetType.BOTTOM) {
      this.width_ = '100%';
      this.height_ = '100%';
    } else {
      // should be SheetType.CONTENT_COVER
      this.width_ = this.curLayoutDirection === CanvasLayoutDirection.HORIZONTAL ? 650 : 480;
      this.height_ = 560;
    }
  }
  onWinSizeChangForAll: (size: Size) => void = (size: Size) => {
    WinSizeChangeCallbackManager.getOrCreateInstance().executeCallback(size);
  }
  // var for layout above

  private initWinSizeChangeCallback() {
    try {
      this.curWindow = window.findWindow(this.getUIContext().getWindowName());
      this.curWindow.on('windowSizeChange', this.onWinSizeChangForAll);
      WinSizeChangeCallbackManager.getOrCreateInstance().addCallback(this.updateCanvasLayoutProperties);0
    } catch (err) {
      console.info(LogTag, `get window failed, err: ${JSON.stringify(err)}`);
    }
  }

  private initLayoutProperties() {
    try {
      if (this.curWindow) {
        let winRect = this.curWindow?.getWindowProperties().windowRect;
        this.updateCanvasLayoutProperties({ width: winRect.width, height: winRect.height })
      }
    } catch (e) {
      console.warn(LogTag, `init layout properties failed, err: ${JSON.stringify(e)}`)
    }
  }

  @Builder
  pageMap(name: string) {
    if (name === 'home') {
      CanvasHome({
        imageInfoArr: this.imageInfoArr,
        styles: this.options?.imageGenerationModel?.getModelSupportStyles(),
        userPrompt: this.userPrompt
      })
    } else if (name === 'textTouchUp') {
      TextTouchUpComponent()
    }
  }

  private initImageInfoArr(): void {
    if (this.options && this.options.images) {
      let initZIndex: number = 1;
      for (let index = 0; index < this.options.images.length && index < this.MAX_IMAGE_COUNT; index++) {
        if (this.options.images[index].zIndex === undefined) {
          this.options.images[index].zIndex = initZIndex;
          initZIndex++;
        }
        this.imageInfoArr.push(this.options.images[index]);
      }
      this.imageInfoArr.sort((a, b) => {
        return (a.zIndex ?? 0) - (b.zIndex ?? 0);
      })
    }

    while (this.imageInfoArr.length < this.MAX_IMAGE_COUNT) {
      this.imageInfoArr.push({ image: undefined, url: Constants.NOT_SELECTED_NAME })
    }
  }

  private initUserPrompt(): void {
    if (this.options && this.options.content) {
      this.userPrompt = this.options.content.toString();
    }
  }

  aboutToAppear(): void {
    this.initImageInfoArr();
    this.initUserPrompt();
    for (let i = 0; i < this.MAX_IMAGE_COUNT; ++i) {
      this.stylesArr.push({ name: '' + i, icon: $r('sys.symbol.style')})
    }
    // register win size change callback below
    this.initWinSizeChangeCallback();
    this.initLayoutProperties();
    // register win size change callback above
    this.stack.pushPath({name: 'home'})
  }

  aboutToDisappear(): void {
    this.curWindow?.off('windowSizeChange', this.onWinSizeChangForAll);
    WinSizeChangeCallbackManager.getOrCreateInstance().destroy();
  }

  build() {
      Navigation(this.stack) {

      }
      .navDestination(this.pageMap)
      .hideNavBar(true)
      .height(this.height_)
      .width(this.width_)
      .borderRadius(32)
      .mode(NavigationMode.Stack)
      .clip(true)
      .alignSelf(ItemAlign.Center)
  }
}
