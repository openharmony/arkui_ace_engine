/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
const TITLE_TEXT_FONT_SIZE: string = '16vp'
const TITLE_TEXT_FONT_WEIGHT: string = '500px'
const TITLE_ROW_HEIGHT: string = '37vp'

@Entry
@Component
struct Index {
  @State appLabel: string = '';
  @State appTitle: string = '';
  @State appLabelColor: Color = 0x66000000;
  @State pixelMap：image.PixelMap = undefined;
  @State iconOpacity: number = 0.4;

  onWindowFocused() {
    this.appLabelColor = 0xff000000;
    this.iconOpacity = 1;
  }

  onWindowUnfocused() {
    this.appLabelColor = 0x66000000;
    this.iconOpacity = 0.4;
  }

  setAppTitle(content: string ) {
    this.appTitle = content;
  }

  setAppIcon(pixelMap: image.PixelMap) {
    this.pixelMap = pixelMap;
  }

  build() {
    Row() {
      Image(this.pixelMap)
        .id("enhanceAppIcon")
        .height(TITLE_ICON_SIZE)
        .width(TITLE_ICON_SIZE)
        .interpolation(ImageInterpolation.Medium)
        .focusable(false)
        .margin({ left: TITLE_ELEMENT_MARGIN_HORIZONTAL, right: TITLE_ELEMENT_MARGIN_HORIZONTAL })
        .opacity(this.iconOpacity)
        .draggable(false)
      Text(this.appTitle ? this.appTitle : this.appLabel)
        .id("enhanceAppLabel")
        .fontSize(TITLE_TEXT_FONT_SIZE)
        .fontColor(this.appLabelColor)
        .fontWeight(TITLE_TEXT_FONT_WEIGHT)
        .maxLines(1)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
        .textAlign(TextAlign.Start)
        .opacity(this.iconOpacity)
        .flexShrink(1)
    }
    .width('100%')
    .height(TITLE_ROW_HEIGHT)
    .justifyContent(FlexAlign.Start)
    .alignItems(VerticalAlign.Center)
    .padding({ top: 6, bottom: 6, left: 8, right: 8 })
   }
}