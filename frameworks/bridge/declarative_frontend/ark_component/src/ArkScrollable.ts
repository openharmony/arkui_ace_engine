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

class ClipContentModifier extends ModifierWithKey<ContentClipMode | RectShape> {
    constructor(value: ContentClipMode | RectShape) {
        super(value);
    }
    static identity: Symbol = Symbol('clipContent');
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            getUINativeModule().scrollable.resetContentClip(node);
        } else {
            getUINativeModule().scrollable.setContentClip(node, this.value);
        }
    }
}

/**
 * base class of Grid, Scroll, List, and WaterFlow.
 */
export class ArkScrollable<T> extends ArkComponent implements ScrollableCommonMethod<T> {
    constructor(nativePtr: KNode, classType?: ModifierType) {
      super(nativePtr, classType);
    }
    clipContent(clip: ContentClipMode | RectShape): T {
        modifierWithKey(this._modifiersWithKeys, ClipContentModifier.identity, ClipContentModifier, clip);
        return this;
    }
}