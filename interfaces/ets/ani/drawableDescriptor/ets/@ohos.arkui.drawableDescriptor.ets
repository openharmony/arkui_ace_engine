/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import image from '@ohos.multimedia.image';
import drawing from '@ohos.graphics.drawing';

class NativeDestructor {
  private ptr: long = 0
  constructor(ptr: long) {
    this.ptr = ptr
  }

  clean(): void {
    DrawableDescriptorInner.destructDrawable(this.ptr)
  }
}

let destroyRegister = new FinalizationRegistry<NativeDestructor>((destructor: NativeDestructor) => {
  destructor.clean()
})

function finalizerRegister(target: Object, thunk: NativeDestructor) {
  destroyRegister.register(target, thunk)
}

function finalizerUnregister(target: Object) {
  destroyRegister.unregister(target)
}

export class DrawableDescriptor {
  @JSONStringifyIgnore protected pixelMap?: image.PixelMap = undefined
  @JSONStringifyIgnore protected nativeObj: long = 0

  constructor() { }

  getPixelMap(): image.PixelMap | undefined {
    return this.pixelMap
  }

  static transferStatic(input: Any): Object {
    if (typeof (input) !== 'object' || input === null) {
      return new Object();
    }
    let inputVal = ESValue.wrap(input) as ESValue;
    let typeNameProperty = inputVal.getProperty("typeName");
    if (!typeNameProperty.isString()) {
      return new Object();
    }
    let typeName = typeNameProperty.toString();
    return DrawableDescriptorInner.nativeTransferStatic(inputVal, typeName);
  }

  static transferDynamic(input: Object): Any {
    if (input == null) {
      return undefined;
    }
    let drawableDescriptor = input as DrawableDescriptor;
    if (drawableDescriptor) {
      let module = ESValue.load("@ohos.arkui.drawableDescriptor");
      let initFunc = module.getProperty("__createTransfer__");
      if (initFunc) {
        let drawableRet = initFunc.invoke(ESObject.wrap(drawableDescriptor.nativeObj));
        return drawableRet;
      }
    }
    return undefined;
  }
}

export class PixelMapDrawableDescriptor extends DrawableDescriptor {
  @JSONStringifyIgnore private finalization: NativeDestructor

  constructor(src?: image.PixelMap) {
    super()
    this.pixelMap = src
    DrawableDescriptorInner.createPixelMapDrawable(this, src)
    this.finalization = new NativeDestructor(this.nativeObj)
    finalizerRegister(this, this.finalization)
  }

  getPixelMap(): image.PixelMap | undefined {
    if (this.pixelMap) {
      return this.pixelMap
    }
    this.pixelMap = DrawableDescriptorInner.createPixelMap(this)
    return this.pixelMap
  }
}

export class LayeredDrawableDescriptor extends DrawableDescriptor {
  @JSONStringifyIgnore private foreground?: DrawableDescriptor = undefined
  @JSONStringifyIgnore private background?: DrawableDescriptor = undefined
  @JSONStringifyIgnore private mask?: DrawableDescriptor = undefined
  @JSONStringifyIgnore private finalization: NativeDestructor

  constructor(foreground?: DrawableDescriptor, background?: DrawableDescriptor, mask?: DrawableDescriptor) {
    super();
    this.foreground = foreground
    this.background = background
    this.mask = mask
    DrawableDescriptorInner.createLayeredDrawable(
      this, foreground?.getPixelMap(), background?.getPixelMap(), mask?.getPixelMap())
    this.finalization = new NativeDestructor(this.nativeObj)
    finalizerRegister(this, this.finalization)
  }

  getPixelMap(): image.PixelMap | undefined {
    if (this.pixelMap != undefined) {
      return this.pixelMap
    }
    this.pixelMap = DrawableDescriptorInner.composePixelMap(this)
    return this.pixelMap
  }

  getForeground(): DrawableDescriptor | undefined {
    if (this.foreground != undefined) {
      return this.foreground
    }
    this.foreground = DrawableDescriptorInner.createForeground(this)
    return this.foreground
  }

  getBackground(): DrawableDescriptor | undefined {
    if (this.background != undefined) {
      return this.background
    }
    this.background = DrawableDescriptorInner.createBackground(this)
    return this.background
  }

  getMask(): DrawableDescriptor | undefined {
    if (this.mask != undefined) {
      return this.mask
    }
    this.mask = DrawableDescriptorInner.createMask(this)
    return this.mask
  }

  static getMaskClipPath(): string {
    return DrawableDescriptorInner.getMaskClipPath()
  }

  setBlendMode(mode: drawing.BlendMode | undefined): void {
    if (mode != undefined) {
      DrawableDescriptorInner.setBlendMode(this, mode)
    }
  }
}

export interface AnimationOptions {
  duration?: int;
  iterations?: int;
}

class AnimationOptionsImpl implements AnimationOptions {
  duration?: int;
  iterations?: int;
  constructor() { }
}

export class AnimatedDrawableDescriptor extends DrawableDescriptor {
  @JSONStringifyIgnore private pixelMaps: Array<image.PixelMap>
  @JSONStringifyIgnore private options: AnimationOptions | undefined = undefined
  @JSONStringifyIgnore private finalization: NativeDestructor
  constructor(pixelMaps: Array<image.PixelMap>, options?: AnimationOptions) {
    super()
    if (pixelMaps.length > 0) {
      this.pixelMap = pixelMaps[0]
    }
    this.pixelMaps = pixelMaps
    this.options = options
    DrawableDescriptorInner.createAnimatedDrawable(this, pixelMaps, options)
    this.finalization = new NativeDestructor(this.nativeObj)
    finalizerRegister(this, this.finalization)
  }
}

class DrawableDescriptorInner {
  static { loadLibrary("drawable_descriptor_ani") }
  native static createPixelMapDrawable(value: PixelMapDrawableDescriptor, pixelmap?: image.PixelMap): void;
  native static createLayeredDrawable(value: LayeredDrawableDescriptor, foreground?: image.PixelMap,
    background?: image.PixelMap, mask?: image.PixelMap): void;
  native static createAnimatedDrawable(value: AnimatedDrawableDescriptor,
      pixelMaps: Array<image.PixelMap>, options?: AnimationOptions): void;
  native static createPixelMap(value: PixelMapDrawableDescriptor): image.PixelMap;
  native static composePixelMap(value: LayeredDrawableDescriptor): image.PixelMap;
  native static createForeground(value: LayeredDrawableDescriptor): DrawableDescriptor;
  native static createBackground(value: LayeredDrawableDescriptor): DrawableDescriptor;
  native static createMask(value: LayeredDrawableDescriptor): DrawableDescriptor;
  native static getMaskClipPath(): string;
  native static setBlendMode(value: LayeredDrawableDescriptor, mode: drawing.BlendMode): void;
  native static nativeTransferStatic(input: ESValue, typeName: string): DrawableDescriptor;
  native static destructDrawable(ptr: long): void;
}
