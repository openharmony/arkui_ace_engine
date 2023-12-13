/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

import { LayeredDrawableDescriptor } from '@ohos.arkui.drawableDescriptor';
import { BusinessError } from '@ohos.base';
import image from '@ohos.multimedia.image';

const TITLE_ICON_SIZE: string = '20vp'
const TITLE_PADDING_START: string = '20vp'
const TITLE_ELEMENT_MARGIN_HORIZONTAL: string = '12vp'
const TITLE_TEXT_FONT_SIZE: string = '16fp'
const TITLE_TEXT_FONT_WEIGHT: string = '500px'
const TITLE_ROW_HEIGHT: string = '37vp'

@Entry
@Component
struct Index {
  @State appLabel: string = '';
  @State appTitle: string = '';
  @State appLabelColor: Color = 0xff000000;
  @State appIcon: LayeredDrawableDescriptor = new LayeredDrawableDescriptor();
  @State pixelMap：image.PixelMap = undefined;

  aboutToAppear() {
    const context = getContext(this);
    try {
      this.appLabel = context.resourceManager.getStringSync(context.applicationInfo.labelId);
    } catch (error) {
      let code = (error as BusinessError).code;
      let message = (error as BusinessError).message;
      console.error(`get appLabel failed, error code: ${code}, message: ${message}.`);
    }
    try {
      this.appIcon = (context.resourceManager.getDrawableDescriptor(context.applicationInfo.iconId) as LayeredDrawableDescriptor);
    } catch (error) {
      let code = (error as BusinessError).code;
      let message = (error as BusinessError).message;
      console.error(`get appIcon failed, error code: ${code}, message: ${message}.`);
    }
  }

  onWindowFocused() {
    this.appLabelColor = 0xff000000;
  }

  onWindowUnfocused() {
    this.appLabelColor = 0x66000000;
  }

  setAppTitle(content: string ) {
    this.appTitle = content;
  }

  setAppIcon(pixelMap: image.PixelMap) {
    this.pixelMap = pixelMap;
  }

  build() {
    Row() {
      Image(this.pixelMap ? this.pixelMap : this.appIcon)
        .id("enhanceAppIcon")
        .height(TITLE_ICON_SIZE)
        .width(TITLE_ICON_SIZE)
        .interpolation(ImageInterpolation.Medium)
        .focusable(false)
        .margin({ left: TITLE_PADDING_START, right: TITLE_ELEMENT_MARGIN_HORIZONTAL })

      Text(this.appTitle ? this.appTitle : this.appLabel)
        .id("enhanceAppLabel")
        .fontSize(TITLE_TEXT_FONT_SIZE)
        .fontColor(this.appLabelColor)
        .fontWeight(TITLE_TEXT_FONT_WEIGHT)
        .maxLines(1)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
        .textAlign(TextAlign.Start)
        .layoutWeight(1.0)
    }
    .width('100%')
    .height(TITLE_ROW_HEIGHT)
    .justifyContent(FlexAlign.Start)
    .alignItems(VerticalAlign.Center)
    .padding({ top: 6, bottom: 6 })
   }
}