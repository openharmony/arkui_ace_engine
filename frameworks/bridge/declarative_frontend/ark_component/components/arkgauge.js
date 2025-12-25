/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
class ArkGaugeComponent extends ArkComponent {
    constructor(nativePtr, classType) {
        super(nativePtr, classType);
    }
    value(value) {
        modifierWithKey(this._modifiersWithKeys, GaugeVauleModifier.identity, GaugeVauleModifier, value);
        return this;
    }
    startAngle(angle) {
        modifierWithKey(this._modifiersWithKeys, GaugeStartAngleModifier.identity, GaugeStartAngleModifier, angle);
        return this;
    }
    endAngle(angle) {
        modifierWithKey(this._modifiersWithKeys, GaugeEndAngleModifier.identity, GaugeEndAngleModifier, angle);
        return this;
    }
    colors(colors) {
        modifierWithKey(this._modifiersWithKeys, GaugeColorsModifier.identity, GaugeColorsModifier, colors);
        return this;
    }
    strokeWidth(length) {
        modifierWithKey(this._modifiersWithKeys, GaugeStrokeWidthModifier.identity, GaugeStrokeWidthModifier, length);
        return this;
    }
    description(value) {
        throw new Error('Method not implemented.');
    }
    trackShadow(value) {
        modifierWithKey(this._modifiersWithKeys, GaugeTrackShadowModifier.identity, GaugeTrackShadowModifier, value);
        return this;
    }
    indicator(value) {
        modifierWithKey(this._modifiersWithKeys, GaugeIndicatorModifier.identity, GaugeIndicatorModifier, value);
        return this;
    }
    contentModifier(value) {
        modifierWithKey(this._modifiersWithKeys, GaugeContentModifier.identity, GaugeContentModifier, value);
        return this;
    }
    setContentModifier(modifier) {
        if (modifier === undefined || modifier === null) {
            getUINativeModule().gauge.setContentModifierBuilder(this.nativePtr, false);
            return;
        }
        this.needRebuild = false;
        if (this.builder !== modifier.applyContent()) {
            this.needRebuild = true;
        }
        this.builder = modifier.applyContent();
        this.modifier = modifier;
        getUINativeModule().gauge.setContentModifierBuilder(this.nativePtr, this);
    }
    makeContentModifierNode(context, gaugeConfiguration) {
        gaugeConfiguration.contentModifier = this.modifier;
        if (isUndefined(this.gaugeNode) || this.needRebuild) {
            let xNode = globalThis.requireNapi('arkui.node');
            this.gaugeNode = new xNode.BuilderNode(context);
            this.gaugeNode.build(this.builder, gaugeConfiguration);
            this.needRebuild = false;
        } else {
            this.gaugeNode.update(gaugeConfiguration);
        }
        return this.gaugeNode.getFrameNode();
    }
    privacySensitive(value) {
        modifierWithKey(this._modifiersWithKeys, GaugePrivacySensitiveModifier.identity, GaugePrivacySensitiveModifier, value);
        return this;
    }
}

class GaugeIndicatorModifier extends ModifierWithKey {
    applyPeer(node, reset) {
        if (reset) {
            getUINativeModule().gauge.resetGaugeIndicator(node, this.value);
        }
        else {
            getUINativeModule().gauge.setGaugeIndicator(node, this.value.icon, this.value.space);
        }
    }
    checkObjectDiff() {
        return !isBaseOrResourceEqual(this.stageValue.icon, this.value.icon) ||
            !isBaseOrResourceEqual(this.stageValue.space, this.value.space);
    }
}
GaugeIndicatorModifier.identity = Symbol('gaugeIndicator');
class GaugeContentModifier extends ModifierWithKey {
    constructor(value) {
        super(value);
    }
    applyPeer(node, reset, component) {
        let gaugeComponent = component;
        gaugeComponent.setContentModifier(this.value);
    }
}
GaugeContentModifier.identity = Symbol('gaugeContentModifier');
class GaugeColorsModifier extends ModifierWithKey {
    applyPeer(node, reset) {
        if (reset) {
            getUINativeModule().gauge.resetGaugeColors(node);
        }
        else {
            getUINativeModule().gauge.setGaugeColors(node, this.value);
        }
    }
    checkObjectDiff() {
        return true;
    }
}
GaugeColorsModifier.identity = Symbol('gaugeColors');
class GaugeVauleModifier extends ModifierWithKey {
    applyPeer(node, reset) {
        if (reset) {
            getUINativeModule().gauge.resetGaugeVaule(node);
        }
        else {
            getUINativeModule().gauge.setGaugeVaule(node, this.value);
        }
    }
    checkObjectDiff() {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
    }
}
GaugeVauleModifier.identity = Symbol('gaugeVaule');
class GaugeStartAngleModifier extends ModifierWithKey {
    applyPeer(node, reset) {
        if (reset) {
            getUINativeModule().gauge.resetGaugeStartAngle(node);
        }
        else {
            getUINativeModule().gauge.setGaugeStartAngle(node, this.value);
        }
    }
    checkObjectDiff() {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
    }
}
GaugeStartAngleModifier.identity = Symbol('gaugeStartAngle');
class GaugeEndAngleModifier extends ModifierWithKey {
    applyPeer(node, reset) {
        if (reset) {
            getUINativeModule().gauge.resetGaugeEndAngle(node);
        }
        else {
            getUINativeModule().gauge.setGaugeEndAngle(node, this.value);
        }
    }
    checkObjectDiff() {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
    }
}
GaugeEndAngleModifier.identity = Symbol('gaugeEndAngle');
class GaugeStrokeWidthModifier extends ModifierWithKey {
    applyPeer(node, reset) {
        if (reset) {
            getUINativeModule().gauge.resetGaugeStrokeWidth(node);
        }
        else {
            getUINativeModule().gauge.setGaugeStrokeWidth(node, this.value);
        }
    }
    checkObjectDiff() {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
    }
}
GaugeStrokeWidthModifier.identity = Symbol('gaugeStrokeWidth');
class GaugeTrackShadowModifier extends ModifierWithKey {
    applyPeer(node, reset) {
        if (reset) {
            getUINativeModule().gauge.resetGaugeTrackShadow(node);
        }
        else {
            getUINativeModule().gauge.setGaugeTrackShadow(node, this.value, this.value.radius, this.value.offsetX, this.value.offsetY);
        }
    }
    checkObjectDiff() {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
    }
}
GaugeTrackShadowModifier.identity = Symbol('gaugeTrackShadow');
class GaugePrivacySensitiveModifier extends ModifierWithKey {
    constructor(value) {
        super(value);
    }
    applyPeer(node, reset) {
        if (reset) {
            getUINativeModule().gauge.resetGaugePrivacySensitive(node);
        } else {
            getUINativeModule().gauge.setGaugePrivacySensitive(node, this.value);
        }
    }
}
GaugePrivacySensitiveModifier.identity = Symbol('gaugePrivacySensitive');

class JSGauge extends JSViewAbstract {
    static create(params) {
        console.log('JSGauge create nativeModule');
        if (params !== undefined) {
            getUINativeModule().gauge.create(params.value ?? 0, params.min ?? 0, params.max ?? 100);
        } else {
            getUINativeModule().gauge.create(0, 0, 100);
        }
    }

    static value(value) {
        getUINativeModule().gauge.setGaugeVaule(true, value);
    }
    static startAngle(angle) {
        getUINativeModule().gauge.setGaugeStartAngle(true, angle);
    }
    static endAngle(angle) {
        getUINativeModule().gauge.setGaugeEndAngle(true, angle);
    }
    static colors(colors) {
        getUINativeModule().gauge.setGaugeColors(true, colors);
    }
    static strokeWidth(length) {
        getUINativeModule().gauge.setGaugeStrokeWidth(true, length);
    }
    static description(value) {
        getUINativeModule().gauge.setDescription(value);
    }
    static trackShadow(value) {
        getUINativeModule().gauge.setGaugeTrackShadow(true, value);
    }
    static indicator(value) {
        getUINativeModule().gauge.setGaugeIndicator(true, value);
    }
    static attributeModifier(modifier) {
        attributeModifierFunc.call(this, modifier, (nativePtr) => {
            return new ArkGaugeComponent(nativePtr);
        }, (nativePtr, classType, modifierJS) => {
            return new modifierJS.GaugeModifier(nativePtr, classType);
        });
    }
    static contentModifier(modifier) {
        const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
        let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
        let component = this.createOrGetNode(elmtId, () => {
            return createComponent(nativeNode, 'gauge');
        });
        component.setContentModifier(modifier);
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
    static onHover(value) {
        __Common__.onHover(value);
    }
}

function createComponent(nativePtr, classType) {
    return new ArkGaugeComponent(nativePtr, classType);
}

function exportComponent() {
    globalThis.ArkGaugeComponent = ArkGaugeComponent;
}

function exportView() {
    globalThis.Gauge = JSGauge;
}

export default { ArkGaugeComponent, createComponent, exportComponent, exportView };
