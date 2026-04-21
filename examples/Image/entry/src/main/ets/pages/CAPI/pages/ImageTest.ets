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

import { SelfImage } from '../component/SelfImage'
import matrix4 from '@ohos.matrix4'
import { AttributeUpdater } from  '@kit.ArkUI'


class SelfImageModifier extends AttributeUpdater<ImageAttribute, ImageInterface> {}


@Entry
@Component
struct ImageTest {
  matrix: Array<number> = [1,0,0,0,0,1,0,0,0,0,1,0,200,100,0,1]

  modifier: SelfImageModifier = new SelfImageModifier()


  build() {
    Column() {
      SelfImage({
        resource: $r('app.media.startIcon'),
        translateOptions: { x: 200, y: 100 }
      })
        .width(300)
        .height(300)
        .borderColor(Color.Red)
        .borderWidth(1)

      SelfImage({
        resource: $r('app.media.startIcon'),
        matrix: this.matrix
      })
        .width(300)
        .height(300)
        .borderColor(Color.Red)
        .borderWidth(1)

      Image($r('app.media.startIcon'))
        .attributeModifier(this.modifier)
    }
    .height('100%')
    .width('100%')
  }
}