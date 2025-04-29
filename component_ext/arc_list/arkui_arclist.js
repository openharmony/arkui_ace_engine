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

const __ArcList__ = requireInternal('arkui.ArcList');
const ModifierMap = requireNapi('arkui.modifier').ModifierMap;
const ModifierUtils = requireNapi('arkui.modifier').ModifierUtils;
const LengthUnit = requireNapi('arkui.node').LengthUnit;

class ArcListChildrenMainSizeModifier extends ModifierWithKey {
    static identity = Symbol('childrenMainSize');
    constructor(value) {
        super(value);
    }
    applyPeer(node, reset) {
        if (reset || !this.value) {
            __ArcList__.modifier.resetChildrenMainSize(node);
        }
        else {
            __ArcList__.modifier.setChildrenMainSize(node, this.value.defaultMainSize, this.value.sizeArray);
        }
    }
    checkObjectDiff() {
        if (!this.stageValue && !this.value) {
            return false;
        } else if (this.stageValue && this.value) {
            if (this.stageValue.defaultMainSize !== this.value.defaultMainSize ||
                this.stageValue.sizeArray.length !== this.value.sizeArray.length ||
                !this.stageValue.sizeArray.every((v, i) => v === this.value.sizeArray[i])) {
                return true;
            }
            return false;
        }
        return true;
    }
}

class ArcListScrollBarWidthModifier extends ModifierWithKey {
    static identity = Symbol('scrollBarWidth');
    constructor(value) {
        super(value);
    }
    applyPeer(node, reset) {
        if (reset || !this.value) {
            getUINativeModule().list.resetListScrollBarWidth(node);
        }
        else {
            let width = `${this.value.value}${LengthUnit[this.value.unit]}`;
            getUINativeModule().list.setListScrollBarWidth(node, width);
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

class ArcListScrollBarColorModifier extends ModifierWithKey {
    static identity = Symbol('scrollBarColor');
    constructor(value) {
        super(value);
    }
    applyPeer(node, reset) {
        if (reset || !this.value) {
            getUINativeModule().list.resetListScrollBarColor(node);
        }
        else {
            getUINativeModule().list.setListScrollBarColor(node, this.value.color);
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

class ArcListSpaceModifier extends ModifierWithKey {
    static identity = Symbol('space');
    constructor(value) {
        super(value);
    }
    applyPeer(node, reset) {
        if (reset || !this.value) {
            __ArcList__.modifier.resetSpace(node);
        }
        else {
            __ArcList__.modifier.setSpace(node, this.value);
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
  
class ArcListDigitalCrownSensitivityModifier extends ModifierWithKey {
    static identity = Symbol('digitalCrownSensitivity');
    constructor(value) {
        super(value);
    }
    applyPeer(node, reset) {
        if (reset || this.value === undefined) {
            __ArcList__.modifier.resetDigitalCrownSensitivity(node);
        }
        else {
            __ArcList__.modifier.setDigitalCrownSensitivity(node, this.value);
        }
    }
}

class ArcListComponent extends ArkListComponent {
    constructor(nativePtr, classType) {
        super(nativePtr, classType);
    }
    digitalCrownSensitivity(sensitivity) {
        modifierWithKey(this._modifiersWithKeys, ArcListDigitalCrownSensitivityModifier.identity, ArcListDigitalCrownSensitivityModifier, sensitivity);
        return this;
    }
    space(space) {
        modifierWithKey(this._modifiersWithKeys, ArcListSpaceModifier.identity, ArcListSpaceModifier, space);
        return this;
    }
    scrollBarColor(color) {
        modifierWithKey(this._modifiersWithKeys, ArcListScrollBarColorModifier.identity, ArcListScrollBarColorModifier, color);
        return this;
    }
    scrollBarWidth(width) {
        modifierWithKey(this._modifiersWithKeys, ArcListScrollBarWidthModifier.identity, ArcListScrollBarWidthModifier, width);
        return this;
    }
    childrenMainSize(size) {
        modifierWithKey(this._modifiersWithKeys, ArcListChildrenMainSizeModifier.identity, ArcListChildrenMainSizeModifier, size);
        return this;
    }
}

class ArcListModifier extends ArcListComponent {
    constructor(nativePtr, classType) {
        super(nativePtr, classType);
        this._modifiersWithKeys = new ModifierMap();
    }
    applyNormalAttribute(instance) {
        ModifierUtils.applySetOnChange(this);
        ModifierUtils.applyAndMergeModifier(instance, this);
    }
}

class ArcList extends List {
    static attributeModifier(modifier) {
        attributeModifierFunc.call(this, modifier, (nativePtr) => {
            return new ArcListComponent(nativePtr);
        }, (nativePtr, classType, modifierJS) => {
            return new ArcListModifier(nativePtr, classType);
        });
    }

    static create(value) {
        __ArcList__.create(value);
    }

    static space(value) {
        __ArcList__.space(value);
    }

    static scrollBarWidth(value) {
        if (value) {
            value = `${value.value}${LengthUnit[value.unit]}`;
        }
        List.scrollBarWidth(value);
    }

    static scrollBarColor(value) {
        if (value) {
            value = value.color;
        }
        List.scrollBarColor(value);
    }

    static digitalCrownSensitivity(value) {
        __ArcList__.digitalCrownSensitivity(value);
    }
}

class ArcListItemAutoScaleModifier extends ModifierWithKey {
    static identity = Symbol('autoScale');
    constructor(value) {
        super(value);
    }
    applyPeer(node, reset) {
        if (reset || this.value === undefined) {
            __ArcList__.item.modifier.resetAutoScale(node);
        } else {
            __ArcList__.item.modifier.setAutoScale(node, this.value);
        }
    }
}

class ArcListItemComponent extends ArkListItemComponent {
    constructor(nativePtr, classType) {
        super(nativePtr, classType);
    }
    autoScale(enable) {
        modifierWithKey(this._modifiersWithKeys, ArcListItemAutoScaleModifier.identity, ArcListItemAutoScaleModifier, enable);
        return this;
    }
}

class ArcListItemModifier extends ArcListItemComponent {
    constructor(nativePtr, classType) {
        super(nativePtr, classType);
        this._modifiersWithKeys = new ModifierMap();
    }
    applyNormalAttribute(instance) {
        ModifierUtils.applySetOnChange(this);
        ModifierUtils.applyAndMergeModifier(instance, this);
    }
}

class ArcListItem extends ListItem {
    static attributeModifier(modifier) {
        attributeModifierFunc.call(this, modifier, (nativePtr) => {
            return new ArcListItemComponent(nativePtr);
        }, (nativePtr, classType, modifierJS) => {
            return new ArcListItemModifier(nativePtr, classType);
        });
    }

    static create(deepRenderFunction, isLazy, options) {
        if (isLazy === false) {
            __ArcList__.item.createInternal(deepRenderFunction, isLazy, options);
            return;
        }
        const listItemElmtId = ViewStackProcessor.GetElmtIdToAccountFor();
        const themeScope = ArkThemeScopeManager.getInstance().scopeForElmtId(listItemElmtId);
        if (themeScope === undefined) {
            __ArcList__.item.createInternal(deepRenderFunction, isLazy, options);
            return;
        }
        const deepRenderFunctionWrapper = (elmtId, isInitialRender) => {
            const result = ArkThemeScopeManager.getInstance().onDeepRenderScopeEnter(themeScope);
            deepRenderFunction(elmtId, isInitialRender);
            if (result === true) {
                ArkThemeScopeManager.getInstance().onDeepRenderScopeExit();
            }
        };
        __ArcList__.item.createInternal(deepRenderFunctionWrapper, isLazy, options);
    }

    static autoScale(value) {
        __ArcList__.item.autoScale(value);
    }
}

export default {
    ArcList,
    ArcListItem,
};
