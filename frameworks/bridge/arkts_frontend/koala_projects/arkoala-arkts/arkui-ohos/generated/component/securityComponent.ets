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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer } from "@koalaui/interop"
import { Resource_serializer } from "./../framework/resource"
import { Position_serializer, Edges_serializer, LocalizedEdges_serializer, BorderRadiuses_serializer, Padding_serializer, SizeOptions_serializer, ConstraintSizeOptions_serializer, Dimension, Position, Edges, LocalizedEdges, ResourceColor, BorderRadiuses, Padding, Length, SizeOptions, ConstraintSizeOptions, Bias } from "./units"
import { AlignRuleOption_serializer, LocalizedAlignRuleOptions_serializer, AlignRuleOption, LocalizedAlignRuleOptions, ChainStyle, HorizontalAlignParam, VerticalAlignParam, LocalizedHorizontalAlignParam, LocalizedVerticalAlignParam } from "./common"
import { FocusBoxStyle_serializer, FocusBoxStyle } from "./focus"
import { int32, int64, float32 } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { Resource } from "global.resource"
import { FontStyle, FontWeight, Color, BorderStyle, Alignment, Axis, TextHeightAdaptivePolicy } from "./enums"
import { extractors, hookSecurityComponentMethodAttributeModifier, AttributeModifier, AttributeUpdater } from "#handwritten"
import { ModifierStateManager } from '../CommonModifier';
import { LengthMetrics, ColorMetrics } from "arkui.Graphics"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { SecurityComponentMethodModifier } from "./../SecurityComponentMethodModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkSecurityComponentMethodPeer extends PeerNode {
    attributeSet?: SecurityComponentMethodModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkSecurityComponentMethodPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._SecurityComponentMethod_construct(peerId, flags)
        const _peer  = new ArkSecurityComponentMethodPeer(_peerPtr, peerId, 'SecurityComponentMethod', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setIconSizeAttribute(value: Dimension | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setIconSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLayoutDirectionAttribute(value: SecurityComponentLayoutDirection | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as SecurityComponentLayoutDirection)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setLayoutDirection(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPositionAttribute(value: Position | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            Position_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setPosition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMarkAnchorAttribute(value: Position | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            Position_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setMarkAnchor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOffsetAttribute(value: Position | Edges | LocalizedEdges | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Position) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Position
                Position_serializer.write(thisSerializer, valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Edges) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as Edges
                Edges_serializer.write(thisSerializer, valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof LocalizedEdges) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as LocalizedEdges
                LocalizedEdges_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontSizeAttribute(value: Dimension | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontStyleAttribute(value: FontStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as FontStyle)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setFontStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontWeightAttribute(value: int32 | FontWeight | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof FontWeight) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as FontWeight
                thisSerializer.writeInt32(valueTmpValueForIdx1.valueOf())
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setFontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontFamilyAttribute(value: string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setFontFamily(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setIconColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setIconColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBackgroundColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBorderStyleAttribute(value: BorderStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as BorderStyle)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setBorderStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBorderWidthAttribute(value: Dimension | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setBorderWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBorderColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setBorderColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBorderRadiusAttribute(radius: Dimension | BorderRadiuses | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (radius !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const radiusTmpValue  = radius!
            if (radiusTmpValue instanceof Dimension) {
                thisSerializer.writeInt8((0).toByte())
                const radiusTmpValueForIdx0  = radiusTmpValue as Dimension
                if (radiusTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((0).toByte())
                    const radiusTmpValueForIdx0ForIdx0  = radiusTmpValueForIdx0 as string
                    thisSerializer.writeString(radiusTmpValueForIdx0ForIdx0)
                } else if (radiusTmpValueForIdx0 instanceof number) {
                    thisSerializer.writeInt8((1).toByte())
                    const radiusTmpValueForIdx0ForIdx1  = radiusTmpValueForIdx0 as number
                    thisSerializer.writeNumber(radiusTmpValueForIdx0ForIdx1)
                } else if (radiusTmpValueForIdx0 instanceof Resource) {
                    thisSerializer.writeInt8((2).toByte())
                    const radiusTmpValueForIdx0ForIdx2  = radiusTmpValueForIdx0 as Resource
                    Resource_serializer.write(thisSerializer, radiusTmpValueForIdx0ForIdx2)
                }
            } else if (radiusTmpValue instanceof BorderRadiuses) {
                thisSerializer.writeInt8((1).toByte())
                const radiusTmpValueForIdx1  = radiusTmpValue as BorderRadiuses
                BorderRadiuses_serializer.write(thisSerializer, radiusTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setBorderRadius(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPaddingAttribute(value: Padding | Dimension | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof Padding) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Padding
                Padding_serializer.write(thisSerializer, valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof Dimension) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as Dimension
                if (valueTmpValueForIdx1 instanceof string) {
                    thisSerializer.writeInt8((0).toByte())
                    const valueTmpValueForIdx1ForIdx0  = valueTmpValueForIdx1 as string
                    thisSerializer.writeString(valueTmpValueForIdx1ForIdx0)
                } else if (valueTmpValueForIdx1 instanceof number) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueForIdx1ForIdx1  = valueTmpValueForIdx1 as number
                    thisSerializer.writeNumber(valueTmpValueForIdx1ForIdx1)
                } else if (valueTmpValueForIdx1 instanceof Resource) {
                    thisSerializer.writeInt8((2).toByte())
                    const valueTmpValueForIdx1ForIdx2  = valueTmpValueForIdx1 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueForIdx1ForIdx2)
                }
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setPadding(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTextIconSpaceAttribute(value: Dimension | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setTextIconSpace(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setKeyAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setKey(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setWidthAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setHeightAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setHeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSizeAttribute(value: SizeOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            SizeOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setConstraintSizeAttribute(value: ConstraintSizeOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            ConstraintSizeOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setConstraintSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAlignAttribute(alignType: Alignment | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (alignType !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const alignTypeTmpValue  = (alignType as Alignment)
            thisSerializer.writeInt32(alignTypeTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setAlign(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAlignRulesAttribute(alignRule: AlignRuleOption | LocalizedAlignRuleOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (alignRule !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const alignRuleTmpValue  = alignRule!
            if (alignRuleTmpValue instanceof AlignRuleOption) {
                thisSerializer.writeInt8((0).toByte())
                const alignRuleTmpValueForIdx0  = alignRuleTmpValue as AlignRuleOption
                AlignRuleOption_serializer.write(thisSerializer, alignRuleTmpValueForIdx0)
            } else if (alignRuleTmpValue instanceof LocalizedAlignRuleOptions) {
                thisSerializer.writeInt8((1).toByte())
                const alignRuleTmpValueForIdx1  = alignRuleTmpValue as LocalizedAlignRuleOptions
                LocalizedAlignRuleOptions_serializer.write(thisSerializer, alignRuleTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setAlignRules(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setIdAttribute(description: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (description !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const descriptionTmpValue  = description!
            thisSerializer.writeString(descriptionTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setId(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setChainModeAttribute(direction: Axis | undefined, style: ChainStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (direction !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const directionTmpValue  = (direction as Axis)
            thisSerializer.writeInt32(directionTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (style !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const styleTmpValue  = (style as ChainStyle)
            thisSerializer.writeInt32(styleTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setChainMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinFontScaleAttribute(scale: double | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (scale !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const scaleTmpValue  = scale!
            if (scaleTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const scaleTmpValueForIdx0  = scaleTmpValue as double
                thisSerializer.writeFloat64(scaleTmpValueForIdx0)
            } else if (scaleTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toByte())
                const scaleTmpValueForIdx1  = scaleTmpValue as Resource
                Resource_serializer.write(thisSerializer, scaleTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setMinFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxFontScaleAttribute(scale: double | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (scale !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const scaleTmpValue  = scale!
            if (scaleTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const scaleTmpValueForIdx0  = scaleTmpValue as double
                thisSerializer.writeFloat64(scaleTmpValueForIdx0)
            } else if (scaleTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toByte())
                const scaleTmpValueForIdx1  = scaleTmpValue as Resource
                Resource_serializer.write(thisSerializer, scaleTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setMaxFontScale(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxLinesAttribute(line: int32 | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (line !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const lineTmpValue  = line!
            if (lineTmpValue instanceof int32) {
                thisSerializer.writeInt8((0).toByte())
                const lineTmpValueForIdx0  = lineTmpValue as int32
                thisSerializer.writeInt32(lineTmpValueForIdx0)
            } else if (lineTmpValue instanceof Resource) {
                thisSerializer.writeInt8((1).toByte())
                const lineTmpValueForIdx1  = lineTmpValue as Resource
                Resource_serializer.write(thisSerializer, lineTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setMaxLines(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinFontSizeAttribute(minSize: double | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (minSize !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const minSizeTmpValue  = minSize!
            if (minSizeTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const minSizeTmpValueForIdx0  = minSizeTmpValue as double
                thisSerializer.writeFloat64(minSizeTmpValueForIdx0)
            } else if (minSizeTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toByte())
                const minSizeTmpValueForIdx1  = minSizeTmpValue as string
                thisSerializer.writeString(minSizeTmpValueForIdx1)
            } else if (minSizeTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const minSizeTmpValueForIdx2  = minSizeTmpValue as Resource
                Resource_serializer.write(thisSerializer, minSizeTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setMinFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxFontSizeAttribute(maxSize: double | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (maxSize !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const maxSizeTmpValue  = maxSize!
            if (maxSizeTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const maxSizeTmpValueForIdx0  = maxSizeTmpValue as double
                thisSerializer.writeFloat64(maxSizeTmpValueForIdx0)
            } else if (maxSizeTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toByte())
                const maxSizeTmpValueForIdx1  = maxSizeTmpValue as string
                thisSerializer.writeString(maxSizeTmpValueForIdx1)
            } else if (maxSizeTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const maxSizeTmpValueForIdx2  = maxSizeTmpValue as Resource
                Resource_serializer.write(thisSerializer, maxSizeTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setMaxFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setHeightAdaptivePolicyAttribute(policy: TextHeightAdaptivePolicy | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (policy !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const policyTmpValue  = (policy as TextHeightAdaptivePolicy)
            thisSerializer.writeInt32(policyTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setHeightAdaptivePolicy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnabledAttribute(respond: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (respond !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const respondTmpValue  = respond!
            thisSerializer.writeBoolean(respondTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setEnabled(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFocusBoxAttribute(style: FocusBoxStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (style !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const styleTmpValue  = style!
            FocusBoxStyle_serializer.write(thisSerializer, styleTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._SecurityComponentMethod_setFocusBox(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum SecurityComponentLayoutDirection {
    HORIZONTAL = 0,
    VERTICAL = 1
}
export interface SecurityComponentMethod {
    iconSize(value: Dimension | undefined): this {
        throw new Error("Unimplemented method iconSize")
    }
    layoutDirection(value: SecurityComponentLayoutDirection | undefined): this {
        throw new Error("Unimplemented method layoutDirection")
    }
    position(value: Position | undefined): this {
        throw new Error("Unimplemented method position")
    }
    markAnchor(value: Position | undefined): this {
        throw new Error("Unimplemented method markAnchor")
    }
    offset(value: Position | Edges | LocalizedEdges | undefined): this {
        throw new Error("Unimplemented method offset")
    }
    fontSize(value: Dimension | undefined): this {
        throw new Error("Unimplemented method fontSize")
    }
    fontStyle(value: FontStyle | undefined): this {
        throw new Error("Unimplemented method fontStyle")
    }
    fontWeight(value: int32 | FontWeight | string | Resource | undefined): this {
        throw new Error("Unimplemented method fontWeight")
    }
    fontFamily(value: string | Resource | undefined): this {
        throw new Error("Unimplemented method fontFamily")
    }
    fontColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method fontColor")
    }
    iconColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method iconColor")
    }
    backgroundColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method backgroundColor")
    }
    borderStyle(value: BorderStyle | undefined): this {
        throw new Error("Unimplemented method borderStyle")
    }
    borderWidth(value: Dimension | undefined): this {
        throw new Error("Unimplemented method borderWidth")
    }
    borderColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method borderColor")
    }
    borderRadius(radius: Dimension | BorderRadiuses | undefined): this {
        throw new Error("Unimplemented method borderRadius")
    }
    padding(value: Padding | Dimension | undefined): this {
        throw new Error("Unimplemented method padding")
    }
    textIconSpace(value: Dimension | undefined): this {
        throw new Error("Unimplemented method textIconSpace")
    }
    key(value: string | undefined): this {
        throw new Error("Unimplemented method key")
    }
    width(value: Length | undefined): this {
        throw new Error("Unimplemented method width")
    }
    height(value: Length | undefined): this {
        throw new Error("Unimplemented method height")
    }
    size(value: SizeOptions | undefined): this {
        throw new Error("Unimplemented method size")
    }
    constraintSize(value: ConstraintSizeOptions | undefined): this {
        throw new Error("Unimplemented method constraintSize")
    }
    align(alignType: Alignment | undefined): this {
        throw new Error("Unimplemented method align")
    }
    alignRules(alignRule: AlignRuleOption | LocalizedAlignRuleOptions | undefined): this {
        throw new Error("Unimplemented method alignRules")
    }
    id(description: string | undefined): this {
        throw new Error("Unimplemented method id")
    }
    chainMode(direction: Axis | undefined, style: ChainStyle | undefined): this {
        throw new Error("Unimplemented method chainMode")
    }
    minFontScale(scale: double | Resource | undefined): this {
        throw new Error("Unimplemented method minFontScale")
    }
    maxFontScale(scale: double | Resource | undefined): this {
        throw new Error("Unimplemented method maxFontScale")
    }
    maxLines(line: int32 | Resource | undefined): this {
        throw new Error("Unimplemented method maxLines")
    }
    minFontSize(minSize: double | string | Resource | undefined): this {
        throw new Error("Unimplemented method minFontSize")
    }
    maxFontSize(maxSize: double | string | Resource | undefined): this {
        throw new Error("Unimplemented method maxFontSize")
    }
    heightAdaptivePolicy(policy: TextHeightAdaptivePolicy | undefined): this {
        throw new Error("Unimplemented method heightAdaptivePolicy")
    }
    enabled(respond: boolean | undefined): this {
        throw new Error("Unimplemented method enabled")
    }
    focusBox(style: FocusBoxStyle | undefined): this {
        throw new Error("Unimplemented method focusBox")
    }
    attributeModifier(value: AttributeModifier<SecurityComponentMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkSecurityComponentMethodStyle implements SecurityComponentMethod {
    iconSize(value: Dimension | undefined): this {
        return this
    }
    layoutDirection(value: SecurityComponentLayoutDirection | undefined): this {
        return this
    }
    position(value: Position | undefined): this {
        return this
    }
    markAnchor(value: Position | undefined): this {
        return this
    }
    offset(value: Position | Edges | LocalizedEdges | undefined): this {
        return this
    }
    fontSize(value: Dimension | undefined): this {
        return this
    }
    fontStyle(value: FontStyle | undefined): this {
        return this
    }
    fontWeight(value: int32 | FontWeight | string | Resource | undefined): this {
        return this
    }
    fontFamily(value: string | Resource | undefined): this {
        return this
    }
    fontColor(value: ResourceColor | undefined): this {
        return this
    }
    iconColor(value: ResourceColor | undefined): this {
        return this
    }
    backgroundColor(value: ResourceColor | undefined): this {
        return this
    }
    borderStyle(value: BorderStyle | undefined): this {
        return this
    }
    borderWidth(value: Dimension | undefined): this {
        return this
    }
    borderColor(value: ResourceColor | undefined): this {
        return this
    }
    borderRadius(radius: Dimension | BorderRadiuses | undefined): this {
        return this
    }
    padding(value: Padding | Dimension | undefined): this {
        return this
    }
    textIconSpace(value: Dimension | undefined): this {
        return this
    }
    key(value: string | undefined): this {
        return this
    }
    width(value: Length | undefined): this {
        return this
    }
    height(value: Length | undefined): this {
        return this
    }
    size(value: SizeOptions | undefined): this {
        return this
    }
    constraintSize(value: ConstraintSizeOptions | undefined): this {
        return this
    }
    align(alignType: Alignment | undefined): this {
        return this
    }
    alignRules(alignRule: AlignRuleOption | LocalizedAlignRuleOptions | undefined): this {
        return this
    }
    id(description: string | undefined): this {
        return this
    }
    chainMode(direction: Axis | undefined, style: ChainStyle | undefined): this {
        return this
    }
    minFontScale(scale: double | Resource | undefined): this {
        return this
    }
    maxFontScale(scale: double | Resource | undefined): this {
        return this
    }
    maxLines(line: int32 | Resource | undefined): this {
        return this
    }
    minFontSize(minSize: double | string | Resource | undefined): this {
        return this
    }
    maxFontSize(maxSize: double | string | Resource | undefined): this {
        return this
    }
    heightAdaptivePolicy(policy: TextHeightAdaptivePolicy | undefined): this {
        return this
    }
    enabled(respond: boolean | undefined): this {
        return this
    }
    focusBox(style: FocusBoxStyle | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<SecurityComponentMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class ArkSecurityComponentMethodComponent extends ComponentBase implements SecurityComponentMethod {
    getPeer(): ArkSecurityComponentMethodPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkSecurityComponentMethodPeer)
    }
    public iconSize(value: Dimension | undefined): this {
        if (this.checkPriority("iconSize")) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.setIconSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public layoutDirection(value: SecurityComponentLayoutDirection | undefined): this {
        if (this.checkPriority("layoutDirection")) {
            const value_casted = value as (SecurityComponentLayoutDirection | undefined)
            this.getPeer()?.setLayoutDirectionAttribute(value_casted)
            return this
        }
        return this
    }
    public position(value: Position | undefined): this {
        if (this.checkPriority("position")) {
            const value_casted = value as (Position | undefined)
            this.getPeer()?.setPositionAttribute(value_casted)
            return this
        }
        return this
    }
    public markAnchor(value: Position | undefined): this {
        if (this.checkPriority("markAnchor")) {
            const value_casted = value as (Position | undefined)
            this.getPeer()?.setMarkAnchorAttribute(value_casted)
            return this
        }
        return this
    }
    public offset(value: Position | Edges | LocalizedEdges | undefined): this {
        if (this.checkPriority("offset")) {
            const value_casted = value as (Position | Edges | LocalizedEdges | undefined)
            this.getPeer()?.setOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    public fontSize(value: Dimension | undefined): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.setFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public fontStyle(value: FontStyle | undefined): this {
        if (this.checkPriority("fontStyle")) {
            const value_casted = value as (FontStyle | undefined)
            this.getPeer()?.setFontStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public fontWeight(value: int32 | FontWeight | string | Resource | undefined): this {
        if (this.checkPriority("fontWeight")) {
            const value_casted = value as (int32 | FontWeight | string | Resource | undefined)
            this.getPeer()?.setFontWeightAttribute(value_casted)
            return this
        }
        return this
    }
    public fontFamily(value: string | Resource | undefined): this {
        if (this.checkPriority("fontFamily")) {
            const value_casted = value as (string | Resource | undefined)
            this.getPeer()?.setFontFamilyAttribute(value_casted)
            return this
        }
        return this
    }
    public fontColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("fontColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public iconColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("iconColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setIconColorAttribute(value_casted)
            return this
        }
        return this
    }
    public backgroundColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("backgroundColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    public borderStyle(value: BorderStyle | undefined): this {
        if (this.checkPriority("borderStyle")) {
            const value_casted = value as (BorderStyle | undefined)
            this.getPeer()?.setBorderStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public borderWidth(value: Dimension | undefined): this {
        if (this.checkPriority("borderWidth")) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.setBorderWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public borderColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("borderColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setBorderColorAttribute(value_casted)
            return this
        }
        return this
    }
    public borderRadius(radius: Dimension | BorderRadiuses | undefined): this {
        if (this.checkPriority("borderRadius")) {
            const radius_casted = radius as (Dimension | BorderRadiuses | undefined)
            this.getPeer()?.setBorderRadiusAttribute(radius_casted)
            return this
        }
        return this
    }
    public padding(value: Padding | Dimension | undefined): this {
        if (this.checkPriority("padding")) {
            const value_casted = value as (Padding | Dimension | undefined)
            this.getPeer()?.setPaddingAttribute(value_casted)
            return this
        }
        return this
    }
    public textIconSpace(value: Dimension | undefined): this {
        if (this.checkPriority("textIconSpace")) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.setTextIconSpaceAttribute(value_casted)
            return this
        }
        return this
    }
    public key(value: string | undefined): this {
        if (this.checkPriority("key")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setKeyAttribute(value_casted)
            return this
        }
        return this
    }
    public width(value: Length | undefined): this {
        if (this.checkPriority("width")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public height(value: Length | undefined): this {
        if (this.checkPriority("height")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setHeightAttribute(value_casted)
            return this
        }
        return this
    }
    public size(value: SizeOptions | undefined): this {
        if (this.checkPriority("size")) {
            const value_casted = value as (SizeOptions | undefined)
            this.getPeer()?.setSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public constraintSize(value: ConstraintSizeOptions | undefined): this {
        if (this.checkPriority("constraintSize")) {
            const value_casted = value as (ConstraintSizeOptions | undefined)
            this.getPeer()?.setConstraintSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public align(alignType: Alignment | undefined): this {
        if (this.checkPriority("align")) {
            const alignType_casted = alignType as (Alignment | undefined)
            this.getPeer()?.setAlignAttribute(alignType_casted)
            return this
        }
        return this
    }
    public alignRules(alignRule: AlignRuleOption | LocalizedAlignRuleOptions | undefined): this {
        if (this.checkPriority("alignRules")) {
            const alignRule_casted = alignRule as (AlignRuleOption | LocalizedAlignRuleOptions | undefined)
            this.getPeer()?.setAlignRulesAttribute(alignRule_casted)
            return this
        }
        return this
    }
    public id(description: string | undefined): this {
        if (this.checkPriority("id")) {
            const description_casted = description as (string | undefined)
            this.getPeer()?.setIdAttribute(description_casted)
            return this
        }
        return this
    }
    public chainMode(direction: Axis | undefined, style: ChainStyle | undefined): this {
        if (this.checkPriority("chainMode")) {
            const direction_casted = direction as (Axis | undefined)
            const style_casted = style as (ChainStyle | undefined)
            this.getPeer()?.setChainModeAttribute(direction_casted, style_casted)
            return this
        }
        return this
    }
    public minFontScale(scale: double | Resource | undefined): this {
        if (this.checkPriority("minFontScale")) {
            const scale_casted = scale as (double | Resource | undefined)
            this.getPeer()?.setMinFontScaleAttribute(scale_casted)
            return this
        }
        return this
    }
    public maxFontScale(scale: double | Resource | undefined): this {
        if (this.checkPriority("maxFontScale")) {
            const scale_casted = scale as (double | Resource | undefined)
            this.getPeer()?.setMaxFontScaleAttribute(scale_casted)
            return this
        }
        return this
    }
    public maxLines(line: int32 | Resource | undefined): this {
        if (this.checkPriority("maxLines")) {
            const line_casted = line as (int32 | Resource | undefined)
            this.getPeer()?.setMaxLinesAttribute(line_casted)
            return this
        }
        return this
    }
    public minFontSize(minSize: double | string | Resource | undefined): this {
        if (this.checkPriority("minFontSize")) {
            const minSize_casted = minSize as (double | string | Resource | undefined)
            this.getPeer()?.setMinFontSizeAttribute(minSize_casted)
            return this
        }
        return this
    }
    public maxFontSize(maxSize: double | string | Resource | undefined): this {
        if (this.checkPriority("maxFontSize")) {
            const maxSize_casted = maxSize as (double | string | Resource | undefined)
            this.getPeer()?.setMaxFontSizeAttribute(maxSize_casted)
            return this
        }
        return this
    }
    public heightAdaptivePolicy(policy: TextHeightAdaptivePolicy | undefined): this {
        if (this.checkPriority("heightAdaptivePolicy")) {
            const policy_casted = policy as (TextHeightAdaptivePolicy | undefined)
            this.getPeer()?.setHeightAdaptivePolicyAttribute(policy_casted)
            return this
        }
        return this
    }
    public enabled(respond: boolean | undefined): this {
        if (this.checkPriority("enabled")) {
            const respond_casted = respond as (boolean | undefined)
            this.getPeer()?.setEnabledAttribute(respond_casted)
            return this
        }
        return this
    }
    public focusBox(style: FocusBoxStyle | undefined): this {
        if (this.checkPriority("focusBox")) {
            const style_casted = style as (FocusBoxStyle | undefined)
            this.getPeer()?.setFocusBoxAttribute(style_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SecurityComponentMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => { 
          hookSecurityComponentMethodAttributeModifier(this, value);
        })
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
    public applyOptionsFinish(traceName: string): void {
        super.applyOptionsFinish(traceName)
    }
}
