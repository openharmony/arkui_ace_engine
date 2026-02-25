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
 * Image component lattice property examples
 */
import { drawing } from '@kit.ArkGraphics2D';

@Entry
@Component
struct ImageLatticeExample {
  private lattice1: DrawingLattice = DrawingLattice.createImageLattice([1, 370, 760], [160], 3, 1)
  private lattice2: DrawingLattice = DrawingLattice.createImageLattice([0, 180, 540], [120], 2, 0)
  private lattice3: DrawingLattice = DrawingLattice.createImageLattice([100, 440, 280], [80], 1, 1)

  @State currentLattice: number = 1

  build() {
    Column({ space: 20 }) {
      Text('Lattice 属性示例')
        .fontSize(20)
        .fontColor(Color.Gray)

      // Lattice 1 - 九宫格切片
      Column({ space: 15 }) {
        Text('九宫格切片 (lattice1)')
          .fontSize(16)
        Image($r('app.media.app_icon'))
            .width(300)
            .height(300)
            .lattice(this.lattice1)
            .border({ width: 2, color: this.currentLattice === 1 ? Color.Green : Color.Transparent })
            .onClick(() => {
              this.currentLattice = 1
            })
      }

      // Lattice 2 - 4列2行切片
      Column({ space: 15 }) {
        Text('4列2行切片 (lattice2)')
          .fontSize(16)
        Image($r('app.media.app_icon'))
            .width(300)
            .height(300)
            .lattice(this.lattice2)
            .border({ width: 2, color: this.currentLattice === 2 ? Color.Green : Color.Transparent })
            .onClick(() => {
              this.currentLattice = 2
            })
      }

      // Lattice 3 - 水平3列切片
      Column({ space: 15 }) {
        Text('水平3列切片 (lattice3)')
          .fontSize(16)
        Image($r('app.media.app_icon'))
            .width(300)
            .height(300)
            .lattice(this.lattice3)
            .border({ width: 2, color: this.currentLattice === 3 ? Color.Green : Color.Transparent })
            .onClick(() => {
              this.currentLattice = 3
            })
      }

      Divider().strokeWidth(2)

      Text('当前选择的切片: ' + this.currentLattice)
        .fontSize(18)
        .fontWeight(FontWeight.Medium)

      Text('lattice 属性用于将一张大图分割成多个小图块并平铺显示')
        .fontSize(14)
        .fontColor(Color.Blue)
        .margin({ top: 10 })
    }
    .width('100%')
    .height('100%')
    .padding(20)
    .backgroundColor(Color.White)
  }
}
