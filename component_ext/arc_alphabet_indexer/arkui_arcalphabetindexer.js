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

const __ArcAlphabetIndexer__ = requireInternal("arkui.ArcAlphabetIndexer");
const LengthUnit = requireNapi('arkui.node').LengthUnit;

class ArcAlphabetIndexerColorModifier extends ModifierWithKey {
    static identity = Symbol('color');
    constructor(value) {
        super(value);
    }
    applyPeer(node, reset) {
        if (reset || !this.value) {
            getUINativeModule().alphabetIndexer.resetColor(node);
        }
        else {
            getUINativeModule().alphabetIndexer.setColor(node, this.value.color);
        }
    }
    checkObjectDiff() {
        if (!this.stageValue && !this.value) {
            return false;
        } else if (this.stageValue && this.value) {
            return this.stageValue.color !== this.value.color;
        }
        return true;
    }
}

class ArcAlphabetIndexerSelectedColorModifier extends ModifierWithKey {
    static identity = Symbol('selectedColor');
    constructor(value) {
        super(value);
    }
    applyPeer(node, reset) {
        if (reset || !this.value) {
            getUINativeModule().alphabetIndexer.resetSelectedColor(node);
        }
        else {
            getUINativeModule().alphabetIndexer.setSelectedColor(node, this.value.color);
        }
    }
    checkObjectDiff() {
        if (!this.stageValue && !this.value) {
            return false;
        } else if (this.stageValue && this.value) {
            return this.stageValue.color !== this.value.color;
        }
        return true;
    }
}

class ArcAlphabetIndexerPopupColorModifier extends ModifierWithKey {
    static identity = Symbol('popupColor');
    constructor(value) {
        super(value);
    }
    applyPeer(node, reset) {
        if (reset || !this.value) {
            getUINativeModule().alphabetIndexer.resetPopupColor(node);
        }
        else {
            getUINativeModule().alphabetIndexer.setPopupColor(node, this.value.color);
        }
    }
    checkObjectDiff() {
        if (!this.stageValue && !this.value) {
            return false;
        } else if (this.stageValue && this.value) {
            return this.stageValue.color !== this.value.color;
        }
        return true;
    }
}

class ArcAlphabetIndexerSelectedBackgroundColorModifier extends ModifierWithKey {
    static identity = Symbol('selectedBackgroundColor');
    constructor(value) {
        super(value);
    }
    applyPeer(node, reset) {
        if (reset || !this.value) {
            getUINativeModule().alphabetIndexer.resetSelectedBackgroundColor(node);
        }
        else {
            getUINativeModule().alphabetIndexer.setSelectedBackgroundColor(node, this.value.color);
        }
    }
    checkObjectDiff() {
        if (!this.stageValue && !this.value) {
            return false;
        } else if (this.stageValue && this.value) {
            return this.stageValue.color !== this.value.color;
        }
        return true;
    }
}

class ArcAlphabetIndexerPopupBackgroundModifier extends ModifierWithKey {
    static identity = Symbol('popupBackground');
    constructor(value) {
        super(value);
    }
    applyPeer(node, reset) {
        if (reset || !this.value) {
            getUINativeModule().alphabetIndexer.resetPopupBackground(node);
        }
        else {
            getUINativeModule().alphabetIndexer.setPopupBackground(node, this.value.color);
        }
    }
    checkObjectDiff() {
        if (!this.stageValue && !this.value) {
            return false;
        } else if (this.stageValue && this.value) {
            return this.stageValue.color !== this.value.color;
        }
        return true;
    }
}

class ArcAlphabetIndexerItemSizeModifier extends ModifierWithKey {
    static identity = Symbol('itemSize');
    constructor(value) {
        super(value);
    }
    applyPeer(node, reset) {
        if (reset || !this.value) {
            getUINativeModule().alphabetIndexer.resetItemSize(node);
        }
        else {
            let size = `${this.value.value}${LengthUnit[this.value.unit]}`;
            getUINativeModule().alphabetIndexer.setItemSize(node, size);
        }
    }
    checkObjectDiff() {
        if (!this.stageValue && !this.value) {
            return false;
        } else if (this.stageValue && this.value) {
            if (this.stageValue.value !== this.value.value ||
                this.stageValue.unit !== this.value.unit) {
                return true;
            }
            return false;
        }
        return true;
    }
}

class ArcAlphabetIndexerComponent extends ArkAlphabetIndexerComponent {
    constructor(nativePtr, classType) {
        super(nativePtr, classType);
    }
    color(color) {
        modifierWithKey(this._modifiersWithKeys, ArcAlphabetIndexerColorModifier.identity, ArcAlphabetIndexerColorModifier, color);
        return this;
    }
    selectedColor(color) {
        modifierWithKey(this._modifiersWithKeys, ArcAlphabetIndexerSelectedColorModifier.identity, ArcAlphabetIndexerSelectedColorModifier, color);
        return this;
    }
    popupColor(color) {
        modifierWithKey(this._modifiersWithKeys, ArcAlphabetIndexerPopupColorModifier.identity, ArcAlphabetIndexerPopupColorModifier, color);
        return this;
    }
    selectedBackgroundColor(color) {
        modifierWithKey(this._modifiersWithKeys, ArcAlphabetIndexerSelectedBackgroundColorModifier.identity, ArcAlphabetIndexerSelectedBackgroundColorModifier, color);
        return this;
    }
    popupBackground(color) {
        modifierWithKey(this._modifiersWithKeys, ArcAlphabetIndexerPopupBackgroundModifier.identity, ArcAlphabetIndexerPopupBackgroundModifier, color);
        return this;
    }
    itemSize(size) {
        modifierWithKey(this._modifiersWithKeys, ArcAlphabetIndexerItemSizeModifier.identity, ArcAlphabetIndexerItemSizeModifier, size);
        return this;
    }
}

class ArcAlphabetIndexerModifier extends ArcAlphabetIndexerComponent {
    constructor(nativePtr, classType) {
        super(nativePtr, classType);
        this._modifiersWithKeys = new ModifierMap();
    }
    applyNormalAttribute(instance) {
        ModifierUtils.applySetOnChange(this);
        ModifierUtils.applyAndMergeModifier(instance, this);
    }
}

class ArcAlphabetIndexer extends AlphabetIndexer {
    static attributeModifier(modifier) {
        attributeModifierFunc.call(this, modifier, (nativePtr) => {
            return new ArcAlphabetIndexerComponent(nativePtr);
        }, (nativePtr, classType, modifierJS) => {
            return new modifierJS.ArcAlphabetIndexerModifier(nativePtr, classType);
        });
    }

    static create(value) {
        AlphabetIndexer.createArc(value);
    }

    static color(value) {
        if (value) {
            value = value.color;
        }
        AlphabetIndexer.color(value);
    }

    static selectedColor(value) {
        if (value) {
            value = value.color;
        }
        AlphabetIndexer.selectedColor(value);
    }

    static popupColor(value) {
        if (value) {
            value = value.color;
        }
        AlphabetIndexer.popupColor(value);
    }

    static selectedBackgroundColor(value) {
        if (value) {
            value = value.color;
        }
        AlphabetIndexer.selectedBackgroundColor(value);
    }

    static popupBackground(value) {
        if (value) {
            value = value.color;
        }
        AlphabetIndexer.popupBackground(value);
    }

    static itemSize(value) {
        if (value) {
            value = `${value.value}${LengthUnit[value.unit]}`;
        }
        AlphabetIndexer.itemSize(value);
    }

    static usePopup(value) {
        AlphabetIndexer.usingPopup(value);
    }
}

export default {
    ArcAlphabetIndexer,
};
