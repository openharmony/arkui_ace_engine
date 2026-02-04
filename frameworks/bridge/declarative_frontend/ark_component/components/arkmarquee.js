/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
function loadComponent() {
  if (globalThis.__ArkComponent__ !== undefined && loadComponent.componentObj === undefined) {
    class ArkMarqueeComponent extends globalThis.__ArkComponent__ {
      constructor(nativePtr, classType) {
        super(nativePtr, classType);
      }
      allowChildCount() {
        return 0;
      }
      initialize(value) {
        if (value.length === 1 && isObject(value[0])) {
          modifierWithKey(this._modifiersWithKeys, MarqueeInitializeModifier.identity, MarqueeInitializeModifier, value[0]);
        } else {
          modifierWithKey(this._modifiersWithKeys, MarqueeInitializeModifier.identity, MarqueeInitializeModifier, undefined);
        }
        return this;
      }
      fontSize(value) {
        modifierWithKey(this._modifiersWithKeys, MarqueeFontSizeModifier.identity, MarqueeFontSizeModifier, value);
        return this;
      }
      fontColor(value) {
        modifierWithKey(this._modifiersWithKeys, MarqueeFontColorModifier.identity, MarqueeFontColorModifier, value);
        return this;
      }
      allowScale(value) {
        modifierWithKey(this._modifiersWithKeys, MarqueeAllowScaleModifier.identity, MarqueeAllowScaleModifier, value);
        return this;
      }
      fontWeight(value) {
        modifierWithKey(this._modifiersWithKeys, MarqueeFontWeightModifier.identity, MarqueeFontWeightModifier, value);
        return this;
      }
      fontFamily(value) {
        modifierWithKey(this._modifiersWithKeys, MarqueeFontFamilyModifier.identity, MarqueeFontFamilyModifier, value);
        return this;
      }
      onStart(event) {
        modifierWithKey(this._modifiersWithKeys, MarqueeOnStartModifier.identity, MarqueeOnStartModifier, event);
        return this;
      }
      onBounce(event) {
        modifierWithKey(this._modifiersWithKeys, MarqueeOnBounceModifier.identity, MarqueeOnBounceModifier, event);
        return this;
      }
      onFinish(event) {
        modifierWithKey(this._modifiersWithKeys, MarqueeOnFinishModifier.identity, MarqueeOnFinishModifier, event);
        return this;
      }
      marqueeUpdateStrategy(value) {
        modifierWithKey(this._modifiersWithKeys, MarqueeUpdateStrategyModifier.identity, MarqueeUpdateStrategyModifier, value);
        return this;
      }
    }
    class MarqueeInitializeModifier extends ModifierWithKey {
      constructor(value) {
        super(value);
      }
      applyPeer(node, reset) {
        let _a;
        let _b;
        let _c;
        let _d;
        let _e;
        let _f;
        let _g;
        if (reset) {
          getUINativeModule().marquee.setInitialize(node, undefined, undefined, undefined, undefined, undefined, undefined, undefined);
        }
        else {
          getUINativeModule().marquee.setInitialize(node, (_a = this.value) === null || _a === void 0 ? void 0 : _a.start,
            (_b = this.value) === null || _b === void 0 ? void 0 : _b.step, (_c = this.value) === null || _c === void 0 ? void 0 : _c.loop,
            (_d = this.value) === null || _d === void 0 ? void 0 : _d.fromStart, (_e = this.value) === null || _e === void 0 ? void 0 : _e.src,
            (_f = this.value) === null || _f === void 0 ? void 0 : _f.spacing, (_g = this.value) === null || _g === void 0 ? void 0 : _g.delay);
        }
      }
    
      checkObjectDiff() {
        let _a;
        let _b;
        let _c;
        let _d;
        let _e;
        let _f;
        let _g;
        let _h;
        let _j;
        let _k;
        let _l;
        let _m;
        let _n;
        let _o;
        return !isBaseOrResourceEqual((_a = this.stageValue) === null || _a === void 0 ? void 0 : _a.start, (_b = this.value) === null ||
            _b === void 0 ? void 0 : _b.start) ||
            !isBaseOrResourceEqual((_c = this.stageValue) === null || _c === void 0 ? void 0 : _c.step, (_d = this.value) === null ||
            _d === void 0 ? void 0 : _d.step) ||
            !isBaseOrResourceEqual((_e = this.stageValue) === null || _e === void 0 ? void 0 : _e.loop, (_f = this.value) === null ||
            _f === void 0 ? void 0 : _f.loop) ||
            !isBaseOrResourceEqual((_g = this.stageValue) === null || _g === void 0 ? void 0 : _g.fromStart, (_h = this.value) === null ||
            _h === void 0 ? void 0 : _h.fromStart) ||
            !isBaseOrResourceEqual((_j = this.stageValue) === null || _j === void 0 ? void 0 : _j.src, (_k = this.value) === null ||
            _k === void 0 ? void 0 : _k.src ||
            !isBaseOrResourceEqual((_l = this.stageValue) === null || _l === void 0 ? void 0 : _l.spacing, (_m = this.value) === null ||
            _m === void 0 ? void 0 : _m.spacing) ||
            !isBaseOrResourceEqual((_n = this.stageValue) === null || _n === void 0 ? void 0 : _n.delay, (_o = this.value) === null ||
            _o === void 0 ? void 0 : _o.delay));
      }
    }
    MarqueeInitializeModifier.identity = Symbol('marqueeInitialize');
    class MarqueeFontColorModifier extends ModifierWithKey {
      constructor(value) {
        super(value);
      }
      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().marquee.resetFontColor(node);
        }
        else {
          getUINativeModule().marquee.setFontColor(node, this.value);
        }
      }
      checkObjectDiff() {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    MarqueeFontColorModifier.identity = Symbol('fontColor');
    class MarqueeFontSizeModifier extends ModifierWithKey {
      constructor(value) {
        super(value);
      }
      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().marquee.resetFontSize(node);
        }
        else {
          getUINativeModule().marquee.setFontSize(node, this.value);
        }
      }
      checkObjectDiff() {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    MarqueeFontSizeModifier.identity = Symbol('fontSize');
    class MarqueeAllowScaleModifier extends ModifierWithKey {
      constructor(value) {
        super(value);
      }
      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().marquee.resetAllowScale(node);
        }
        else {
          getUINativeModule().marquee.setAllowScale(node, this.value);
        }
      }
    }
    MarqueeAllowScaleModifier.identity = Symbol('allowScale');
    class MarqueeFontWeightModifier extends ModifierWithKey {
      constructor(value) {
        super(value);
      }
      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().marquee.resetFontWeight(node);
        }
        else {
          getUINativeModule().marquee.setFontWeight(node, this.value);
        }
      }
      checkObjectDiff() {
        return this.stageValue !== this.value;
      }
    }
    MarqueeFontWeightModifier.identity = Symbol('fontWeight');
    class MarqueeFontFamilyModifier extends ModifierWithKey {
      constructor(value) {
        super(value);
      }
      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().marquee.resetFontFamily(node);
        }
        else {
          getUINativeModule().marquee.setFontFamily(node, this.value);
        }
      }
    }
    MarqueeFontFamilyModifier.identity = Symbol('fontFamily');
    class MarqueeUpdateStrategyModifier extends ModifierWithKey {
        constructor(value) {
            super(value);
        }
        applyPeer(node, reset) {
            if (reset) {
                getUINativeModule().marquee.resetMarqueeUpdateStrategy(node);
            }
            else {
                getUINativeModule().marquee.setMarqueeUpdateStrategy(node, this.value);
            }
        }
    }
    MarqueeUpdateStrategyModifier.identity = Symbol('marqueeUpdateStrategy');
    class MarqueeOnStartModifier extends ModifierWithKey {
      constructor(value) {
        super(value);
      }
      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().marquee.resetMarqueeOnStart(node);
        } else {
          getUINativeModule().marquee.setMarqueeOnStart(node, this.value);
        }
      }
    }
    MarqueeOnStartModifier.identity = Symbol('marqueeOnStart');
    class MarqueeOnBounceModifier extends ModifierWithKey {
      constructor(value) {
        super(value);
      }
      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().marquee.resetMarqueeOnBounce(node);
        } else {
          getUINativeModule().marquee.setMarqueeOnBounce(node, this.value);
        }
      }
    }
    MarqueeOnBounceModifier.identity = Symbol('marqueeOnBounce');
    class MarqueeOnFinishModifier extends ModifierWithKey {
      constructor(value) {
        super(value);
      }
      applyPeer(node, reset) {
        if (reset) {
          getUINativeModule().marquee.resetMarqueeOnFinish(node);
        } else {
          getUINativeModule().marquee.setMarqueeOnFinish(node, this.value);
        }
      }
    }
    MarqueeOnFinishModifier.identity = Symbol('marqueeOnFinish');
    loadComponent.componentObj = {'component' : ArkMarqueeComponent };
  }
 return loadComponent.componentObj;
}
class JSMarquee extends JSViewAbstract {
    static create(params) {
        getUINativeModule().marquee.create(params);
    }

    static allowScale(value) {
        getUINativeModule().marquee.setAllowScale(true, value);
    }
    static fontColor(value) {
        getUINativeModule().marquee.setFontColor(true, value);
    }
    static fontSize(value) {
        getUINativeModule().marquee.setFontSize(true, value);
    }
    static fontWeight(value) {
        getUINativeModule().marquee.setFontWeight(true, value);
    }
    static fontFamily(value) {
        getUINativeModule().marquee.setFontFamily(true, value);
    }
    static marqueeUpdateStrategy(value) {
        getUINativeModule().marquee.setMarqueeUpdateStrategy(true, value);
    }
    static onStart(value) {
        getUINativeModule().marquee.setMarqueeOnStart(true, value);
    }
    static onBounce(value) {
        getUINativeModule().marquee.setMarqueeOnBounce(true, value);
    }
    static onFinish(value) {
        getUINativeModule().marquee.setMarqueeOnFinish(true, value);
    }
    static attributeModifier(modifier) {
        attributeModifierFunc.call(this, modifier, (nativePtr) => {
            return createComponent(nativePtr);
        }, (nativePtr, classType, modifierJS) => {
            return new modifierJS.MarqueeModifier(nativePtr, classType);
        });
    }

    static onClick(value) {
        __Common__.onClick(value);
    }
    static onKeyEvent(value) {
        __Common__.onKeyEvent(value);
    }
    static onDeleteEvent(value) {
        __Common__.onDeleteEvent(value);
    }
    static onAttach(value) {
        __Common__.onAttach(value);
    }
    static onAppear(value) {
        __Common__.onAppear(value);
    }
    static onDetach(value) {
        __Common__.onAttach(value);
    }
    static onDisAppear(value) {
        __Common__.onDisAppear(value);
    }

    static onTouch(value) {
        __Common__.onTouch(value);
    }

}

function createComponent(nativePtr, classType) {
 	if (loadComponent.componentObj !== undefined) {
 	    return new loadComponent.componentObj.component(nativePtr, classType);
 	}
    return undefined;
}

function exportComponent() {
	globalThis.ArkMarqueeComponent = ArkMarqueeComponent;
}

function exportView() {
	globalThis.Marquee = JSMarquee;
}

export default { loadComponent, createComponent, exportComponent, exportView };