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

import nativeNode from 'libentry.so';
import { NodeContent } from '@kit.ArkUI';

const APP_TITLE_FONT_SIZE = 22;
const APP_DESC_FONT_SIZE = 13;
const APP_BUTTON_FONT_SIZE = 16;
const APP_BUTTON_HEIGHT = 44;
const APP_CONTENT_RADIUS = 8;
const APP_BOTTOM_FONT_SIZE = 11;

@Entry
@Component
struct Index {
  private rootSlot = new NodeContent();
  @State @Watch('onNativeFlagChange') showNative: boolean = false;

  onNativeFlagChange(): void {
    if (this.showNative) {
      nativeNode.createNativeRoot(this.rootSlot);
    } else {
      nativeNode.destroyNativeRoot();
    }
  }

  build() {
    Column() {
      Text('Picker CAPI Demo')
        .fontSize(APP_TITLE_FONT_SIZE)
        .fontWeight(FontWeight.Bold)
        .fontColor('#1A73E8')
        .margin({ top: 16, bottom: 8 })

      Text('Demonstrates all Picker CAPI components:')
        .fontSize(APP_DESC_FONT_SIZE)
        .fontColor('#666666')
        .margin({ bottom: 16 })
        .width('90%')

      Button(this.showNative ? 'Hide Native Picker' : 'Show Native Picker')
        .width('80%')
        .height(APP_BUTTON_HEIGHT)
        .fontSize(APP_BUTTON_FONT_SIZE)
        .backgroundColor(this.showNative ? '#FF4444' : '#007DFF')
        .onClick(() => {
          this.showNative = !this.showNative;
        })
        .margin({ bottom: 12 })

      Row() {
        ContentSlot(this.rootSlot)
      }
      .layoutWeight(1)
      .width('100%')
      .backgroundColor('#F5F5F5')
      .borderRadius(APP_CONTENT_RADIUS)

      Text('Powered by ArkUI NDK (C API)')
        .fontSize(APP_BOTTOM_FONT_SIZE)
        .fontColor('#999999')
        .margin({ top: 8, bottom: 8 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#FFFFFF')
  }
}