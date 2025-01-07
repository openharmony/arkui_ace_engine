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

const __ArcScrollBar__ = requireInternal("arkui.ArcScrollBar");

class ArcScrollBarComponent extends ArkScrollBarComponent {
    constructor(nativePtr, classType) {
        super(nativePtr, classType);
    }
}

class ArcScrollBarModifier extends ArcScrollBarComponent {
    constructor(nativePtr, classType) {
        super(nativePtr, classType);
        this._modifiersWithKeys = new ModifierMap();
    }
    applyNormalAttribute(instance) {
        ModifierUtils.applySetOnChange(this);
        ModifierUtils.applyAndMergeModifier(instance, this);
    }
}

class ArcScrollBar extends ScrollBar {
    static attributeModifier(modifier) {
        attributeModifierFunc.call(this, modifier, (nativePtr) => {
            return new ArcScrollBarComponent(nativePtr);
        }, (nativePtr, classType, modifierJS) => {
            return new modifierJS.ArcScrollBarModifier(nativePtr, classType);
        });
    }

    static create(value) {
        __ArcScrollBar__.create(value);
    }
}

export default {
    ArcScrollBar,
};
