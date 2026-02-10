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

import {drawing} from '@kit.ArkGraphics2D'
import {SelfImage} from '../component/SelfImage'
import hidebug from '@ohos.hidebug'
import {display, ImageModifier} from "@kit.ArkUI"


class SelfImageModifier implements AttributeModifier<ImageAttribute> {
  applyNormalAttribute(instance: ImageAttribute): void {
    instance.resizable({
      lattice: drawing.Lattice.createImageLattice([30, 150], [40, 280], 2, 2)
    })
  }
}

@Entry
@Component
struct DrawingLatticeTest {
  @State lattice: drawing.Lattice = drawing.Lattice.createImageLattice([30, 150], [40, 280], 2, 2)
  modifier: AttributeModifier<ImageAttribute> = new SelfImageModifier()

  aboutToAppear(): void {
    try {
      let result = display.getDefaultDisplaySync()
      console.info(`Lee, result = ${JSON.stringify(result)}`)
    } catch (error) {
      // TODO: Implement error handing.
    }
  }

  build() {
    Column() {
      Image($r('app.media.1'))
        .width(150)
        .height(150)
        .resizable({lattice: this.lattice})
      Image($r('app.media.1'))
        .width(150)
        .height(150)
        .attributeModifier(this.modifier)
      Image($r('app.media.1'))
        .width(150)
        .height(150)
        .resizable({
          slice: {
            left: '30px',
            top: '150px',
            right: '40px',
            bottom: '280px'
          }
        })
      SelfImage({
        resource: $r('app.media.1'),
        lattice: {
          xDivs: [30, 150],
          yDivs: [40, 280]
        }
      })
        .width(150)
        .height(150)
      SelfImage({
        resource: $r('app.media.1'),
        slice: {
          left: 30,
          top: 150,
          right: 40,
          bottom: 280
        }
      })
        .width(150)
        .height(150)
    }
    .height('100%')
    .width('100%')
  }
}