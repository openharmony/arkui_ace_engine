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

@ComponentV2
export struct ImageGeneratorDialog {
  stack: NavPathStack = new NavPathStack();
  @Param @Require options?: imageGeneration.GeneratorDialogOptions;
  @Local width_: Dimension = 650;
  @Local height_: Dimension = 560;
  private MAX_IMAGE_COUNT: number = 4;
  @Local imageInfoArr: Array<imageGeneration.ImageItem> = [];
  @Local stylesArr: Array<imageGeneration.ImageStyle> = [];

  @Builder
  pageMap(name: string) {
    if (name === 'home') {
      CanvasHome({ imageInfoArr: this.imageInfoArr, styles: this.options?.imageGenerationModel?.getModelSupportStyles()})
      // CanvasHome({ imageInfoArr: this.imageInfoArr, styles: this.stylesArr})
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
  aboutToAppear(): void {
    this.initImageInfoArr();
    for (let i = 0; i < this.MAX_IMAGE_COUNT; ++i) {
      this.stylesArr.push({ name: '' + i, icon: $r('sys.symbol.style')})
    }
    this.stack.pushPath({name: 'home'})
  }

  build() {
    Scroll() {
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
      .expandSafeArea([SafeAreaType.SYSTEM, SafeAreaType.CUTOUT])
    }
    .width('100%')
    .height('100%')
    .scrollable(ScrollDirection.FREE)
  }
}
