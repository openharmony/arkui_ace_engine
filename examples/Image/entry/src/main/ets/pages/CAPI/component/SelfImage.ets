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

import { NodeContent } from "@ohos.arkui.node"
import nativeNode from 'libentry.so';
import { matrix4 } from "@kit.ArkUI";

interface TransformOptions {
  translate?: matrix4.TranslateOption,
  scale?: matrix4.RotateOption,
  rotate?: matrix4.RotateOption
}

// 单位px
export interface Slice {
  left: number,
  top: number,
  right: number,
  bottom: number,
}

export interface Lattice {
  xDivs: Array<number>,
  yDivs: Array<number>
}

interface Resizable {
  slice?: Slice,
  lattice?: Lattice
}

@Component
export struct SelfImage {
  private rootSlot = new NodeContent()
  private isSrc: boolean = false
  @Prop resource?: Resource = undefined
  @Prop src: string = ""
  @Prop translateOptions?: matrix4.TranslateOption = undefined
  @Prop scaleOptions?: matrix4.ScaleOption = undefined
  @Prop rotateOptions?: matrix4.RotateOption = undefined
  @Prop matrix?: Array<number> = undefined
  @Prop slice?: Slice = undefined
  @Prop lattice?: Lattice = undefined

  aboutToAppear(): void {
    this.setSrc(this.resource, this.src)
    this.setTransform(this.translateOptions, this.scaleOptions, this.rotateOptions)
    this.setMatrix(this.matrix)
    this.setResizable(this.slice, this.lattice)
  }

  aboutToDisappear(): void {
    nativeNode.disposeImageNode(this.rootSlot)
  }

  setSrc(resource?: Resource, src?: string): void {
    if (resource == undefined && src == undefined) {
      this.isSrc = false
      return;
    }
    this.isSrc = true
    if (this.resource) {
      nativeNode.createImageNodeWithResource(this.rootSlot, this.resource)
    }
    if (this.src.length != 0) {
      nativeNode.createImageNodeWithString(this.rootSlot, this.src)
    }
  }

  setTransform(translate?: matrix4.TranslateOption, scale?: matrix4.ScaleOption, rotate?: matrix4.RotateOption): void {
    if (!this.isSrc || (translate === undefined && scale === undefined && rotate === undefined)) {
      return
    }
    nativeNode.setImageNodeWithTransformOptions(this.rootSlot, {
      translate: this.translateOptions,
      scale: this.scaleOptions,
      rotate: this.rotateOptions
    })
  }

  setMatrix(matrix?: Array<number>): void {
    if (!this.isSrc || this.matrix === undefined || this.matrix.length < 16) {
      return
    }
    console.info(`matrix length is ${matrix?.length}`)
    nativeNode.setImageNodeWithMatrix(this.rootSlot, this.matrix)
  }

  setResizable(slice?: Slice, lattice?: Lattice) {
    if (!this.isSrc || (this.slice === undefined && this.lattice === undefined)) {
      return
    }
    let newSlice: Slice | undefined = undefined
    if (slice !== undefined) {
      newSlice = {
        left: this.getUIContext().px2vp(slice.left),
        top: this.getUIContext().px2vp(slice.top),
        right: this.getUIContext().px2vp(slice.right),
        bottom: this.getUIContext().px2vp(slice.bottom),
      }
    }

    nativeNode.setImageNodeWithResizable(this.rootSlot, { slice: newSlice, lattice: lattice})
  }

  build() {
    ContentSlot(this.rootSlot)
  }
}