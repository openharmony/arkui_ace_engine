/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { CommonMethodModifier } from "./CommonMethodModifier"
import { AttributeModifier, extractors } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkSymbolGlyphPeer, SymbolEffectStrategy, SymbolRenderingStrategy, SymbolEffect, SymbolGlyphAttribute } from "./component/symbolglyph"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { CommonMethod } from "./component/common"
import { Resource } from "global.resource"
import { ResourceColor } from "./component/units"
import { Color, FontWeight } from "./component/enums"
import { SymbolGlyphModifier } from "arkui.SymbolGlyphModifier"
import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./CallbackTransformer"
import { ModifierState } from "./CommonModifier"
export class SymbolGlyphModifier extends CommonMethodModifier implements SymbolGlyphAttribute,AttributeModifier<SymbolGlyphAttribute> {
    constructor(src?: Resource) {
        super()
        let src_type: int32 = RuntimeType.UNDEFINED
        src_type = runtimeType(src)
        if (RuntimeType.UNDEFINED != src_type) {
            this.setSymbolGlyphOptions(src)
        }
    }
    _instanceId: number = -1;
     _state: ModifierState = new ModifierState
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: SymbolGlyphAttribute): void { }
    applyPressedAttribute(instance: SymbolGlyphAttribute): void { }
    applyFocusedAttribute(instance: SymbolGlyphAttribute): void { }
    applyDisabledAttribute(instance: SymbolGlyphAttribute): void { }
    applySelectedAttribute(instance: SymbolGlyphAttribute): void { }

    _setSymbolGlyphOptions_flag:  AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _setSymbolGlyphOptions0_value?: Resource | undefined
    _fontSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontSize_0_0value?: double | string | Resource | undefined
    _fontColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontColor_0_0value?: Array<ResourceColor> | undefined
    _fontWeight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fontWeight_0_0value?: int32 | FontWeight | string | undefined
    _effectStrategy_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _effectStrategy_0_0value?: SymbolEffectStrategy | undefined
    _renderingStrategy_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _renderingStrategy_0_0value?: SymbolRenderingStrategy | undefined
    _symbolEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _symbolEffect_0_0value?: SymbolEffect | undefined
    _minFontScale_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _minFontScale_0_0value?: double | Resource | undefined
    _maxFontScale_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maxFontScale_0_0value?: double | Resource | undefined
    _symbolEffect_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _symbolEffect_1_0value?: SymbolEffect | undefined
    _symbolEffect_1_1value?: boolean | undefined
    _symbolEffect_2_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _symbolEffect_2_0value?: SymbolEffect | undefined
    _symbolEffect_2_1value?: int32 | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkSymbolGlyphPeer;
        if (this._setSymbolGlyphOptions_flag !== AttributeUpdaterFlag.INITIAL) {
            switch (this._setSymbolGlyphOptions_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSymbolGlyphOptionsAttribute((this._setSymbolGlyphOptions0_value as Resource | undefined))
                    this._setSymbolGlyphOptions_flag = AttributeUpdaterFlag.RESET
                    break
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._setSymbolGlyphOptions_flag = AttributeUpdaterFlag.RESET
                    break
                }
                default: {
                    this._setSymbolGlyphOptions_flag = AttributeUpdaterFlag.INITIAL
                    peer.setSymbolGlyphOptionsAttribute(undefined)
                }
            }
        }
        if (this._fontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontSizeAttribute((this._fontSize_0_0value as double | string | Resource | undefined));
                    this._fontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontSizeAttribute((undefined as double | string | Resource | undefined));
                }
            }
        }
        if (this._fontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontColorAttribute((this._fontColor_0_0value as Array<ResourceColor> | undefined));
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontColorAttribute((undefined as Array<ResourceColor> | undefined));
                }
            }
        }
        if (this._fontWeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fontWeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFontWeightAttribute((this._fontWeight_0_0value as int32 | FontWeight | string | undefined));
                    this._fontWeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fontWeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fontWeight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFontWeightAttribute((undefined as int32 | FontWeight | string | undefined));
                }
            }
        }
        if (this._effectStrategy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._effectStrategy_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEffectStrategyAttribute((this._effectStrategy_0_0value as SymbolEffectStrategy | undefined));
                    this._effectStrategy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._effectStrategy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._effectStrategy_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEffectStrategyAttribute((undefined as SymbolEffectStrategy | undefined));
                }
            }
        }
        if (this._renderingStrategy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._renderingStrategy_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRenderingStrategyAttribute((this._renderingStrategy_0_0value as SymbolRenderingStrategy | undefined));
                    this._renderingStrategy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._renderingStrategy_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._renderingStrategy_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRenderingStrategyAttribute((undefined as SymbolRenderingStrategy | undefined));
                }
            }
        }
        if (this._symbolEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._symbolEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSymbolEffect0Attribute((this._symbolEffect_0_0value as SymbolEffect | undefined));
                    this._symbolEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._symbolEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._symbolEffect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSymbolEffect0Attribute((undefined as SymbolEffect | undefined));
                }
            }
        }
        if (this._minFontScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._minFontScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMinFontScaleAttribute((this._minFontScale_0_0value as double | Resource | undefined));
                    this._minFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._minFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._minFontScale_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMinFontScaleAttribute((undefined as double | Resource | undefined));
                }
            }
        }
        if (this._maxFontScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maxFontScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMaxFontScaleAttribute((this._maxFontScale_0_0value as double | Resource | undefined));
                    this._maxFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maxFontScale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maxFontScale_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMaxFontScaleAttribute((undefined as double | Resource | undefined));
                }
            }
        }
        if (this._symbolEffect_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._symbolEffect_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSymbolEffect1Attribute((this._symbolEffect_1_0value as SymbolEffect | undefined), (this._symbolEffect_1_1value as boolean | undefined));
                    this._symbolEffect_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._symbolEffect_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._symbolEffect_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSymbolEffect1Attribute((undefined as SymbolEffect | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (this._symbolEffect_2_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._symbolEffect_2_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSymbolEffect2Attribute((this._symbolEffect_2_0value as SymbolEffect | undefined), (this._symbolEffect_2_1value as int32 | undefined));
                    this._symbolEffect_2_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._symbolEffect_2_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._symbolEffect_2_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSymbolEffect2Attribute((undefined as SymbolEffect | undefined), (undefined as int32 | undefined));
                }
            }
        }
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
        const modifier = value as SymbolGlyphModifier;
        if (modifier._setSymbolGlyphOptions_flag !== AttributeUpdaterFlag.INITIAL) {
            switch (modifier._setSymbolGlyphOptions_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.setSymbolGlyphOptions(modifier._setSymbolGlyphOptions0_value)
                    break
                }
                default: {
                    this.setSymbolGlyphOptions(undefined)
                }
            }
        }
        if (modifier._fontSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontSize(modifier._fontSize_0_0value);
                    break;
                }
                default: {
                    this.fontSize((undefined as double | string | Resource | undefined));
                }
            }
        }
        if (modifier._fontColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontColor(modifier._fontColor_0_0value);
                    break;
                }
                default: {
                    this.fontColor((undefined as Array<ResourceColor> | undefined));
                }
            }
        }
        if (modifier._fontWeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fontWeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fontWeight(modifier._fontWeight_0_0value);
                    break;
                }
                default: {
                    this.fontWeight((undefined as int32 | FontWeight | string | undefined));
                }
            }
        }
        if (modifier._effectStrategy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._effectStrategy_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.effectStrategy(modifier._effectStrategy_0_0value);
                    break;
                }
                default: {
                    this.effectStrategy((undefined as SymbolEffectStrategy | undefined));
                }
            }
        }
        if (modifier._renderingStrategy_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._renderingStrategy_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.renderingStrategy(modifier._renderingStrategy_0_0value);
                    break;
                }
                default: {
                    this.renderingStrategy((undefined as SymbolRenderingStrategy | undefined));
                }
            }
        }
        if (modifier._symbolEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._symbolEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.symbolEffect(modifier._symbolEffect_0_0value);
                    break;
                }
                default: {
                    this.symbolEffect((undefined as SymbolEffect | undefined));
                }
            }
        }
        if (modifier._minFontScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._minFontScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.minFontScale(modifier._minFontScale_0_0value);
                    break;
                }
                default: {
                    this.minFontScale((undefined as double | Resource | undefined));
                }
            }
        }
        if (modifier._maxFontScale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._maxFontScale_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maxFontScale(modifier._maxFontScale_0_0value);
                    break;
                }
                default: {
                    this.maxFontScale((undefined as double | Resource | undefined));
                }
            }
        }
        if (modifier._symbolEffect_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._symbolEffect_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.symbolEffect(modifier._symbolEffect_1_0value, modifier._symbolEffect_1_1value);
                    break;
                }
                default: {
                    this.symbolEffect((undefined as SymbolEffect | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (modifier._symbolEffect_2_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._symbolEffect_2_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.symbolEffect(modifier._symbolEffect_2_0value, modifier._symbolEffect_2_1value);
                    break;
                }
                default: {
                    this.symbolEffect((undefined as SymbolEffect | undefined), (undefined as int32 | undefined));
                }
            }
        }
    }
    setSymbolGlyphOptions(value: Resource | undefined): this {
        if (this._setSymbolGlyphOptions_flag === AttributeUpdaterFlag.INITIAL ||
            this._setSymbolGlyphOptions0_value !== value || !Type.of(value).isPrimitive()) {
            this._setSymbolGlyphOptions0_value = value
            this._setSymbolGlyphOptions_flag = AttributeUpdaterFlag.UPDATE
        } else {
            this._setSymbolGlyphOptions_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontSize(value: double | string | Resource | undefined): this {
        if (((this._fontSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontSize_0_0value = value
        } else
        {
            this._fontSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontColor(value: Array<ResourceColor> | undefined): this {
        if (((this._fontColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontColor_0_0value = value
        } else
        {
            this._fontColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fontWeight(value: int32 | FontWeight | string | undefined): this {
        if (((this._fontWeight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fontWeight_0_flag = AttributeUpdaterFlag.UPDATE
            this._fontWeight_0_0value = value
        } else
        {
            this._fontWeight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    effectStrategy(value: SymbolEffectStrategy | undefined): this {
        if (((this._effectStrategy_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._effectStrategy_0_flag = AttributeUpdaterFlag.UPDATE
            this._effectStrategy_0_0value = value
        } else
        {
            this._effectStrategy_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    renderingStrategy(value: SymbolRenderingStrategy | undefined): this {
        if (((this._renderingStrategy_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._renderingStrategy_0_flag = AttributeUpdaterFlag.UPDATE
            this._renderingStrategy_0_0value = value
        } else
        {
            this._renderingStrategy_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    symbolEffect(value: SymbolEffect | undefined): this {
        if (((this._symbolEffect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._symbolEffect_0_flag = AttributeUpdaterFlag.UPDATE
            this._symbolEffect_0_0value = value
        } else
        {
            this._symbolEffect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    minFontScale(value: double | Resource | undefined): this {
        if (((this._minFontScale_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._minFontScale_0_flag = AttributeUpdaterFlag.UPDATE
            this._minFontScale_0_0value = value
        } else
        {
            this._minFontScale_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    maxFontScale(value: double | Resource | undefined): this {
        if (((this._maxFontScale_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._maxFontScale_0_flag = AttributeUpdaterFlag.UPDATE
            this._maxFontScale_0_0value = value
        } else
        {
            this._maxFontScale_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    symbolEffect(symbolEffect: SymbolEffect | undefined, isActive: boolean | undefined): this {
        if (((this._symbolEffect_1_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || ((this._symbolEffect_1_1value) !== (isActive)))
        {
            this._symbolEffect_1_flag = AttributeUpdaterFlag.UPDATE
            this._symbolEffect_1_0value = symbolEffect
            this._symbolEffect_1_1value = isActive
        } else
        {
            this._symbolEffect_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    symbolEffect(symbolEffect: SymbolEffect | undefined, triggerValue: int32 | undefined): this {
        if (((this._symbolEffect_2_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || ((this._symbolEffect_2_1value) !== (triggerValue)))
        {
            this._symbolEffect_2_flag = AttributeUpdaterFlag.UPDATE
            this._symbolEffect_2_0value = symbolEffect
            this._symbolEffect_2_1value = triggerValue
        } else
        {
            this._symbolEffect_2_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SymbolGlyphAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class SymbolGlyphModifier_serializer {
    public static write(buffer: SerializerBase, value: SymbolGlyphModifier): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(extractors.toSymbolGlyphModifierPtr(value))
    }
    public static read(buffer: DeserializerBase): SymbolGlyphModifier {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return extractors.fromSymbolGlyphModifierPtr(ptr)
    }
}
