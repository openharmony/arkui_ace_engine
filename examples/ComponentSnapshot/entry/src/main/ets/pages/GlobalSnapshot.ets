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

import { GlobalStaticSnapshot, Params } from '../view/GlobalScreenshot';
import { image } from '@kit.ImageKit';

@Entry
@Component
struct Index {
  idx: number = 0; // 索引值，默认值为0
  items: Params[] = [];
  @State pixmap: image.PixelMap | undefined = undefined;

  aboutToAppear(): void {
    for (let i = 0; i < 10; i++) {
      this.items.push(new Params(`item${i}`));
    }
  }

  build() {
    Column({ space: 10 }) {
      // 请将$r('app.media.startIcon')替换为实际资源文件
      Image(this.pixmap ? this.pixmap : $r('app.media.startIcon')).width(300).height(300).objectFit(ImageFit.Auto);
      Button('click to get snapshot')
        .onClick(async () => {
          this.pixmap = await GlobalStaticSnapshot.getAwardSnapshot(this.getUIContext(), this.items[this.idx]);
          this.idx = (this.idx + 1) % 10;
        });
    }
    .height('100%')
    .width('100%')
  }
}