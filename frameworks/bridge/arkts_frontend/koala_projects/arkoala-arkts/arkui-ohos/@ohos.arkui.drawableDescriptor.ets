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
import { AnimationStatus, ResourceStr, Resource } from '@ohos.arkui.component';
import { SystemOps } from "#generated"
import { ArkUIAniModule } from 'arkui.ani';

class NativeDestructor {
  private ptr: long = 0
  constructor(ptr: long) {
    this.ptr = ptr
  }

  clean(): void {
    ArkUIAniModule._Drawable_DestructDrawable(this.ptr)
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

export interface DrawableDescriptorLoadedResult {
  imageWidth: int;
  imageHeight: int;
}

class DrawableDescriptorLoadedResultImpl implements DrawableDescriptorLoadedResult {
  imageWidth: int;
  imageHeight: int;
}

export class DrawableDescriptor {
  @JSONStringifyIgnore protected pixelMap?: image.PixelMap = undefined
  @JSONStringifyIgnore protected nativeObj: long = 0

  constructor() { }

  getPixelMap(): image.PixelMap | undefined {
    return this.pixelMap
  }

  loadSync(): DrawableDescriptorLoadedResult {
    return ArkUIAniModule._Drawable_LoadSync(this)
  }

  load(): Promise<DrawableDescriptorLoadedResult> {
    return ArkUIAniModule._Drawable_Load(this)
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
    return ArkUIAniModule._Drawable_NativeTransferStatic(inputVal, typeName);
  }

  static transferDynamic(input: Object): Any {
    if (input == null) {
      return undefined;
    }
    let drawableDescriptor = input as DrawableDescriptor;
    if (drawableDescriptor) {
      let module = ESValue.load("@ohos.arkui.drawableDescriptor").getProperty('default');
      let initFunc = module.getProperty("__createTransfer__");
      if (!initFunc.isUndefined()) {
        let drawableRet = initFunc.invoke(ESValue.wrap(drawableDescriptor.nativeObj));
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
    ArkUIAniModule._Drawable_CreatePixelMapDrawable(this, src)
    this.finalization = new NativeDestructor(this.nativeObj)
    finalizerRegister(this, this.finalization)
  }

  getPixelMap(): image.PixelMap | undefined {
    if (this.pixelMap) {
      return this.pixelMap
    }
    this.pixelMap = ArkUIAniModule._Drawable_CreatePixelMap(this)
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
    ArkUIAniModule._Drawable_CreateLayeredDrawable(
      this, foreground?.getPixelMap(), background?.getPixelMap(), mask?.getPixelMap())
    this.finalization = new NativeDestructor(this.nativeObj)
    finalizerRegister(this, this.finalization)
  }

  getPixelMap(): image.PixelMap | undefined {
    if (this.pixelMap != undefined) {
      return this.pixelMap
    }
    this.pixelMap = ArkUIAniModule._Drawable_CreatePixelMap(this)
    return this.pixelMap
  }

  getForeground(): DrawableDescriptor | undefined {
    if (this.foreground != undefined) {
      return this.foreground
    }
    this.foreground = ArkUIAniModule._Drawable_CreateForeground(this)
    return this.foreground
  }

  getBackground(): DrawableDescriptor | undefined {
    if (this.background != undefined) {
      return this.background
    }
    this.background = ArkUIAniModule._Drawable_CreateBackground(this)
    return this.background
  }

  getMask(): DrawableDescriptor | undefined {
    if (this.mask != undefined) {
      return this.mask
    }
    this.mask = ArkUIAniModule._Drawable_CreateMask(this)
    return this.mask
  }

  static getMaskClipPath(): string {
    return ArkUIAniModule._Drawable_GetMaskClipPath()
  }

  setBlendMode(mode: drawing.BlendMode | undefined): void {
    if (mode != undefined) {
      ArkUIAniModule._Drawable_SetBlendMode(this, mode)
    }
  }
}

export interface AnimationOptions {
  duration?: int;
  iterations?: int;
  frameDurations?: Array<int>;
  autoPlay?: boolean;
}

class AnimationOptionsImpl implements AnimationOptions {
  duration?: int;
  iterations?: int;
  frameDurations?: Array<int>;
  autoPlay?: boolean;
  constructor() { }
}

export interface AnimationController {
  start(): void;
  stop(): void;
  pause(): void;
  resume(): void;
  getStatus(): AnimationStatus;
}

class AnimationControllerInner implements AnimationController {
    @JSONStringifyIgnore private nativeObj: long = 0;
    constructor(nativeObj: long) {
      if (this.nativeObj === 0){
          this.nativeObj = nativeObj;
      }
    }
    public start(): void {
      ArkUIAniModule._Drawable_AnimationControllerStart(this)
    }
    public stop(): void {
      ArkUIAniModule._Drawable_AnimationControllerStop(this)
    }
    public pause(): void {
      ArkUIAniModule._Drawable_AnimationControllerPause(this)
    }
    public resume(): void {
      ArkUIAniModule._Drawable_AnimationControllerResume(this)
    }
    public getStatus(): AnimationStatus {
      return ArkUIAniModule._Drawable_AnimationControllerGetStatus(this)
    }
}

export class AnimatedDrawableDescriptor extends DrawableDescriptor {
  @JSONStringifyIgnore private pixelMaps!: Array<image.PixelMap>
  @JSONStringifyIgnore private options: AnimationOptions | undefined = undefined
  @JSONStringifyIgnore private finalization: NativeDestructor
  constructor(pixelMaps: Array<image.PixelMap>, options?: AnimationOptions) {
    super()
    if (pixelMaps.length > 0) {
      this.pixelMap = pixelMaps[0]
    }
    this.pixelMaps = pixelMaps
    this.options = options
    ArkUIAniModule._Drawable_CreateAnimatedDrawable(this, pixelMaps, options)
    this.finalization = new NativeDestructor(this.nativeObj)
    finalizerRegister(this, this.finalization)
  }

  constructor(src: ResourceStr | Array<image.PixelMap>, options?: AnimationOptions) {
    super()
    this.options = options
    if (src instanceof ResourceStr) {
      if (src instanceof string) {
        ArkUIAniModule._Drawable_CreateAnimatedDrawableByString(this, src as string, options)
      }
      else if (src instanceof Resource) {
        let resourceObjectKPointer = SystemOps.createResourceObject(src as Resource)
        ArkUIAniModule._Drawable_CreateAnimatedDrawableByResource(this, resourceObjectKPointer, options)
      }
    } else {
      let pixelMapsParm: Array<image.PixelMap> = src as Array<image.PixelMap>
      if (pixelMapsParm.length > 0) {
        this.pixelMap = pixelMapsParm[0]
      }
      this.pixelMaps = pixelMapsParm
      ArkUIAniModule._Drawable_CreateAnimatedDrawable(this, pixelMapsParm, options)
    }
    
    this.finalization = new NativeDestructor(this.nativeObj)
    finalizerRegister(this, this.finalization)
  }

  getPixelMap(): image.PixelMap | undefined {
    if (this.pixelMap) {
      return this.pixelMap
    }
    this.pixelMap = ArkUIAniModule._Drawable_CreatePixelMap(this)
    return this.pixelMap
  }

  getAnimationController(id?: string): AnimationController | undefined {
    return ArkUIAniModule._Drawable_GetAnimationController(this, id)
  }
}