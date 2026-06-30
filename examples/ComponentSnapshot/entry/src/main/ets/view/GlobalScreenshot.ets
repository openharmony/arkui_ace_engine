/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// [Start global_snapshot]
import { image } from '@kit.ImageKit';
import { ComponentContent } from '@kit.ArkUI';

export class Params {
  public text: string | undefined | null = '';

  constructor(text: string | undefined | null) {
    this.text = text;
  }
}

@Builder
function awardBuilder(params: Params) {
  Column() {
    Text(params.text)
      .fontSize(90)
      .fontWeight(FontWeight.Bold)
      .margin({ bottom: 36 })
      .width('100%')
      .height('100%')
  }.backgroundColor('#FFF0F0F0')
}

export class GlobalStaticSnapshot {
  /**
   * 一个可以获取固定对象截图的静态方法
   */
  static async getAwardSnapshot(uiContext: UIContext, textParam: Params): Promise<image.PixelMap | undefined> {
    let resultPixmap: image.PixelMap | undefined = undefined
    let contentNode = new ComponentContent(uiContext, wrapBuilder(awardBuilder), textParam);
    await uiContext.getComponentSnapshot()
      .createFromComponent(contentNode, 320, true, { scale: 1, waitUntilRenderFinished: true })
      .then((pixmap: image.PixelMap) => {
        resultPixmap = pixmap;
      })
      .catch((err: Error) => {
        console.error(`error: ${err}`);
      })
    return resultPixmap;
  }
}
// [End global_snapshot]
