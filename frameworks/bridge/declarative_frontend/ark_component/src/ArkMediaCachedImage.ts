/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 
/// <reference path='./import.ts' />
 
class MeidaCachedImageImageSrcModifier extends ModifierWithKey<PixelMap | ResourceStr | DrawableDescriptor | ASTCResource> {
  constructor(value: PixelMap | ResourceStr | DrawableDescriptor | ASTCResource) {
    super(value);
  }
  static identity: Symbol = Symbol('mediaCachedImageShowSrc');

  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().mediaCachedImage.setMediaCachedImageSrc(node, '');
    } else {
      if (isResource(this.value) || isString(this.value)) {
        getUINativeModule().mediaCachedImage.setMediaCachedImageSrc(node, 0, this.value);
      } else if (Array.isArray(this.value.sources)) {
        getUINativeModule().mediaCachedImage.setMediaCachedImageSrc(
          node, 1, this.value.sources, this.value.sources.length, this.value.column);
      } else {
        getUINativeModule().mediaCachedImage.setMediaCachedImageSrc(node, 0, this.value);
      }
    }
  }
}

class MediaCachedImageAltModifier extends ModifierWithKey<ResourceStr | PixelMap> {
  static identity: Symbol = Symbol('mediaCachedImageAlt');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().mediaCachedImage.resetAlt(node);
    } else {
      getUINativeModule().mediaCachedImage.setAlt(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return true;
  }
}

class ArkMeidaCachedImageComponent extends ArkImageComponent implements ImageAttribute
{
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  initialize(value: PixelMap | ResourceStr | DrawableDescriptor | ASTCResource): this {
    modifierWithKey(this._modifiersWithKeys, MeidaCachedImageImageSrcModifier.identity, MeidaCachedImageImageSrcModifier, value);
    return this;
  }
  alt(value: ResourceStr | PixelMap): this {
    modifierWithKey(this._modifiersWithKeys, MediaCachedImageAltModifier.identity, MediaCachedImageAltModifier, value);
    return this;
  }
}

// @ts-ignore
globalThis.MediaCachedImage.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkMeidaCachedImageComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJs) => {
    return new modifierJS.MediaCachedImageModifier(nativePtr, classType);
  });
};