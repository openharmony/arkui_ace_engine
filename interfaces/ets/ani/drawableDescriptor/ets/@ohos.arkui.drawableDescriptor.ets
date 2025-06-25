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


export class DrawableDescriptor {
  protected pixelMap?: image.PixelMap = undefined
  protected nativeObj: long = 0

  constructor() {}

  getPixelMap(): image.PixelMap | undefined {
    return this.pixelMap
  }
}

export class PixelMapDrawableDescriptor extends DrawableDescriptor {
  constructor(src?: image.PixelMap) {
    super()
    this.pixelMap = src
    DrawableDescriptorInner.createPixelMapDrawable(this, src)
  }

  getPixelMap(): image.PixelMap | undefined {
    if (this.pixelMap) {
      return this.pixelMap
    }
    DrawableDescriptorInner.createPixelMap(this)
    return this.pixelMap
  }
}

export class LayeredDrawableDescriptor extends DrawableDescriptor {
  private foreground?: DrawableDescriptor = undefined
  private background?: DrawableDescriptor = undefined
  private mask?: DrawableDescriptor = undefined

  constructor(
    foreground?: DrawableDescriptor,
    background?: DrawableDescriptor,
    mask?: DrawableDescriptor) {
    super();
    this.foreground = foreground
    this.background = background
    this.mask = mask
    DrawableDescriptorInner.createLayeredDrawable(
      this,
      foreground?.getPixelMap(),
      background?.getPixelMap(),
      mask?.getPixelMap())
  }

  getPixelMap(): image.PixelMap | undefined {
    if (this.pixelMap != undefined) {
      return this.pixelMap
    }
    DrawableDescriptorInner.composePixelMap(this)
    return this.pixelMap
  }

  getForeground(): DrawableDescriptor | undefined {
    if (this.foreground) {
      return this.foreground
    }
    DrawableDescriptorInner.createForeground(this)
    return this.foreground
  }

  getBackground(): DrawableDescriptor | undefined {
    if (this.background) {
      return this.background
    }
    DrawableDescriptorInner.createBackground(this)
    return this.background
  }

  getMask(): DrawableDescriptor | undefined {
    if (this.mask) {
      return this.mask
    }
    DrawableDescriptorInner.createMask(this)
    return this.mask
  }

  static getMaskClipPath(): string {
    return DrawableDescriptorInner.getMaskClipPath()
  }
}

export interface AnimationOptions {
  duration?: number;
  iterations?: number;
}

export class AnimatedDrawableDescriptor extends DrawableDescriptor {
  private pixelMaps: Array<image.PixelMap>
  private options: AnimationOptions | undefined = undefined
  constructor(pixelMaps: Array<image.PixelMap>, options?: AnimationOptions) {
    super()
    if (pixelMaps.length > 0) {
      this.pixelMap = pixelMaps[0]
    }
    this.pixelMaps = pixelMaps
    this.options = options
    DrawableDescriptorInner.createAnimatedDrawable(this, pixelMaps, options)
  }
}

export class DrawableDescriptorInner {
  static { loadLibrary("drawable_descriptor_ani") }
  native static createPixelMapDrawable(
    value: PixelMapDrawableDescriptor,
    pixelmap?: image.PixelMap): void;
  native static createLayeredDrawable(
    value: LayeredDrawableDescriptor,
    foreground?: image.PixelMap,
    background?: image.PixelMap,
    mask?: image.PixelMap): void;
  native static createAnimatedDrawable(
    value: AnimatedDrawableDescriptor,
    pixelMaps: Array<image.PixelMap>,
    options?: AnimationOptions): void;
  native static createPixelMap(value: PixelMapDrawableDescriptor): void
  native static composePixelMap(value: LayeredDrawableDescriptor): void;
  native static createForeground(value: LayeredDrawableDescriptor): void
  native static createBackground(value: LayeredDrawableDescriptor): void
  native static createMask(value: LayeredDrawableDescriptor): void
  native static getMaskClipPath(): string;
}
