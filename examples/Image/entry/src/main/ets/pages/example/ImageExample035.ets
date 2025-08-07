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
 * Sets up resizability for Image components using a lattice grid.
 */
import { drawing } from '@kit.ArkGraphics2D';

@Entry
@Component
struct ImageExample035 {
  private drawingLatticeFirst: DrawingLattice = drawing.Lattice.createImageLattice([1, 370, 760], [160], 3,
    1)

  build() {
    Column() {
      Image($r('app.media.image_lattice'))
        .width(px2vp(1125))
        .height(px2vp(192))

      Image($r('app.media.image_lattice'))
        .width(px2vp(600))
        .height(px2vp(192))
        .draggable(true)
        .resizable({ lattice: this.drawingLatticeFirst })
    }
    .height('100%')
    .width('100%')
  }
}