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

/**
 * 通过lattice拉伸图片
 */
import { drawing } from '@kit.ArkGraphics2D';

@Entry
@Component
struct drawingLatticeTest {
  private xDivs: Array<number> = [1, 2, 200];
  private yDivs: Array<number> = [1, 2, 200];
  private fXCount: number = 3;
  private fYCount: number = 3;
  private DrawingLatticeFirst: DrawingLattice =
    drawing.Lattice.createImageLattice(this.xDivs, this.yDivs, this.fXCount, this.fYCount);

  build() {
    Scroll() {
      Column({ space: 10 }) {
        Text('Original Image').fontSize(20).fontWeight(700)
        Column({ space: 10 }) {
          Image($r('app.media.mountain'))
            .width(260).height(260)
        }.width('100%')

        Text('Resize by lattice').fontSize(20).fontWeight(700)
        Column({ space: 10 }) {
          Image($r('app.media.mountain'))
            .objectRepeat(ImageRepeat.X)
            .width(260)
            .height(260)
            .resizable({
              lattice: this.DrawingLatticeFirst
            })
        }.width('100%')
      }.width('100%')
    }
  }
}