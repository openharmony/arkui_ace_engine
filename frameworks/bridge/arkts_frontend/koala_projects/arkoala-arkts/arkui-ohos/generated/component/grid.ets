/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

import { ArkThemeScopeManager } from '#arktheme'
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr, resourceFinalizerRegister, Finalizable, MaterializedBaseTag } from '@koalaui/interop'
import { Scroller_serializer, OnScrollFrameBeginCallback, Scroller } from './scroll'
import { ItemFillPolicy_serializer, ItemFillPolicy, Length, Resource as arkui_component_units_Resource } from './units'
import { global_resource_Resource_serializer } from './../framework/resource'
import { NestedScrollOptions_serializer, EditModeOptions_serializer, EdgeEffectOptions_serializer, ArkScrollableCommonMethodPeer, ScrollableCommonMethod, OnItemDragStartCallback, ItemDragInfo, NestedScrollOptions, EditModeOptions, OnWillScrollCallback, OnScrollCallback, CommonMethod, EdgeEffectOptions, ArkScrollableCommonMethodComponent, ArkCommonMethodComponent, UIScrollableCommonEvent, UIScrollableCommonEventInternal } from './common'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { Resource as global_resource_Resource } from 'global.resource'
import { Color as arkui_component_enums_Color, BarState, FocusWrapMode, ScrollSource, EdgeEffect } from './enums'
import { ScrollState } from './list'
import { AttributeModifier, hookGridAttributeModifier, AttributeUpdater } from '#handwritten'
import { CustomBuilder } from './builder'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { GridModifier } from './../GridModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
export class ArkGridPeer extends ArkScrollableCommonMethodPeer {
    attributeSet?: GridModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkGridPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIGeneratedNativeModule._Grid_construct(peerId, flags)
        const _peer = new ArkGridPeer(_peerPtr, peerId, 'Grid', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setGridOptionsAttribute(scroller?: Scroller, layoutOptions?: GridLayoutOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (scroller !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const scrollerTmpValue = scroller!
            Scroller_serializer.write(thisSerializer, scrollerTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (layoutOptions !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const layoutOptionsTmpValue = layoutOptions!
            GridLayoutOptions_serializer.write(thisSerializer, layoutOptionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridInterface_setGridOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setColumnsTemplateAttribute(value: string | ItemFillPolicy | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0 = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof ItemFillPolicy) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1 = valueTmpValue as ItemFillPolicy
                ItemFillPolicy_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setColumnsTemplate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRowsTemplateAttribute(value: string | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setRowsTemplate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setColumnsGapAttribute(value: Length | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0 = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1 = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2 = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setColumnsGap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRowsGapAttribute(value: Length | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0 = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1 = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2 = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setRowsGap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setScrollBarWidthAttribute(value: double | string | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0 = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1 = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setScrollBarWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setScrollBarColorAttribute(value: arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            if (valueTmpValue instanceof arkui_component_enums_Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0 = valueTmpValue as arkui_component_enums_Color
                thisSerializer.writeInt32((valueTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1 = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2 = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3 = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setScrollBarColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setScrollBarAttribute(value: BarState | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = (value as BarState)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setScrollBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScrollBarUpdateAttribute(value: ((index: int32,offset: double) => ComputedBarAttribute) | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setOnScrollBarUpdate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScrollIndexAttribute(value: ((first: int32,last: int32) => void) | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setOnScrollIndex(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCachedCount0Attribute(value: int32 | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeInt32(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setCachedCount0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEditModeAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setEditMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMultiSelectableAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setMultiSelectable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMaxCountAttribute(value: int32 | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeInt32(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setMaxCount(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setMinCountAttribute(value: int32 | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeInt32(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setMinCount(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCellLengthAttribute(value: double | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeFloat64(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setCellLength(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLayoutDirectionAttribute(value: GridDirection | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = (value as GridDirection)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setLayoutDirection(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSupportAnimationAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setSupportAnimation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSupportEmptyBranchInLazyLoadingAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setSupportEmptyBranchInLazyLoading(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnItemDragStartAttribute(value: OnItemDragStartCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setOnItemDragStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnItemDragEnterAttribute(value: ((event: ItemDragInfo) => void) | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setOnItemDragEnter(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnItemDragMoveAttribute(value: ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32) => void) | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setOnItemDragMove(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnItemDragLeaveAttribute(value: ((event: ItemDragInfo,itemIndex: int32) => void) | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setOnItemDragLeave(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnItemDropAttribute(value: ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32,isSuccess: boolean) => void) | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setOnItemDrop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setNestedScrollAttribute(value: NestedScrollOptions | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            NestedScrollOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setNestedScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableScrollInteractionAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setEnableScrollInteraction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFrictionAttribute(value: double | arkui_component_units_Resource | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0 = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1 = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setFriction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setAlignItemsAttribute(value: GridItemAlignment | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = (value as GridItemAlignment)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setAlignItems(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEditModeOptionsAttribute(value: EditModeOptions): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        EditModeOptions_serializer.write(thisSerializer, value)
        ArkUIGeneratedNativeModule._GridAttribute_setEditModeOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFocusWrapModeAttribute(value: FocusWrapMode | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = (value as FocusWrapMode)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setFocusWrapMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setSyncLoadAttribute(value: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setSyncLoad(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScrollFrameBeginAttribute(value: OnScrollFrameBeginCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setOnScrollFrameBegin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWillScrollAttribute(value: OnWillScrollCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setOnWillScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDidScrollAttribute(value: OnScrollCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setOnDidScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCachedCount1Attribute(count: int32 | undefined, show: boolean | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (count !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const countTmpValue = count!
            thisSerializer.writeInt32(countTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (show !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const showTmpValue = show!
            thisSerializer.writeBoolean(showTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setCachedCount1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEdgeEffectAttribute(value: EdgeEffect | undefined, options?: EdgeEffectOptions): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = (value as EdgeEffect)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue = options!
            EdgeEffectOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GridAttribute_setEdgeEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface StartLineInfo {
    startIndex: int32;
    startLine: int32;
    startOffset: double;
    totalOffset: double;
}
export type OnGetStartIndexByOffsetCallback = (totalOffset: double) => StartLineInfo;
export type OnGetStartIndexByIndexCallback = (targetIndex: int32) => StartLineInfo;
export interface GridLayoutOptions {
    regularSize: [ int32, int32 ];
    irregularIndexes?: Array<int32>;
    onGetIrregularSizeByIndex?: ((index: int32) => [ int32, int32 ]);
    onGetRectByIndex?: ((index: int32) => [ int32, int32, int32, int32 ]);
    onGetStartIndexByOffset?: OnGetStartIndexByOffsetCallback;
    onGetStartIndexByIndex?: OnGetStartIndexByIndexCallback;
}
export enum GridDirection {
    Row = 0,
    Column = 1,
    RowReverse = 2,
    ColumnReverse = 3
}
export enum GridItemAlignment {
    DEFAULT = 0,
    STRETCH = 1
}
export interface ComputedBarAttribute {
    totalOffset: double;
    totalLength: double;
}
export type OnGridScrollIndexCallback = (first: int32, last: int32) => void;
export interface GridAttribute extends ScrollableCommonMethod {
    setGridOptions(scroller?: Scroller, layoutOptions?: GridLayoutOptions): this {
        throw new Error('Unimplemented method setGridOptions')
    }
    columnsTemplate(value: string | ItemFillPolicy | undefined): this {
        throw new Error('Unimplemented method columnsTemplate')
    }
    rowsTemplate(value: string | undefined): this {
        throw new Error('Unimplemented method rowsTemplate')
    }
    columnsGap(value: Length | undefined): this {
        throw new Error('Unimplemented method columnsGap')
    }
    rowsGap(value: Length | undefined): this {
        throw new Error('Unimplemented method rowsGap')
    }
    scrollBarWidth(value: double | string | undefined): this
    scrollBarColor(value: arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined): this
    scrollBar(value: BarState | undefined): this
    onScrollBarUpdate(value: ((index: int32,offset: double) => ComputedBarAttribute) | undefined): this {
        throw new Error('Unimplemented method onScrollBarUpdate')
    }
    onScrollIndex(value: ((first: int32,last: int32) => void) | undefined): this {
        throw new Error('Unimplemented method onScrollIndex')
    }
    cachedCount(value: int32 | undefined): this {
        throw new Error('Unimplemented method cachedCount')
    }
    editMode(value: boolean | undefined): this {
        throw new Error('Unimplemented method editMode')
    }
    multiSelectable(value: boolean | undefined): this {
        throw new Error('Unimplemented method multiSelectable')
    }
    maxCount(value: int32 | undefined): this {
        throw new Error('Unimplemented method maxCount')
    }
    minCount(value: int32 | undefined): this {
        throw new Error('Unimplemented method minCount')
    }
    cellLength(value: double | undefined): this {
        throw new Error('Unimplemented method cellLength')
    }
    layoutDirection(value: GridDirection | undefined): this {
        throw new Error('Unimplemented method layoutDirection')
    }
    supportAnimation(value: boolean | undefined): this {
        throw new Error('Unimplemented method supportAnimation')
    }
    supportEmptyBranchInLazyLoading(value: boolean | undefined): this {
        throw new Error('Unimplemented method supportEmptyBranchInLazyLoading')
    }
    onItemDragStart(value: OnItemDragStartCallback | undefined): this {
        throw new Error('Unimplemented method onItemDragStart')
    }
    onItemDragEnter(value: ((event: ItemDragInfo) => void) | undefined): this {
        throw new Error('Unimplemented method onItemDragEnter')
    }
    onItemDragMove(value: ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32) => void) | undefined): this {
        throw new Error('Unimplemented method onItemDragMove')
    }
    onItemDragLeave(value: ((event: ItemDragInfo,itemIndex: int32) => void) | undefined): this {
        throw new Error('Unimplemented method onItemDragLeave')
    }
    onItemDrop(value: ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32,isSuccess: boolean) => void) | undefined): this {
        throw new Error('Unimplemented method onItemDrop')
    }
    nestedScroll(value: NestedScrollOptions | undefined): this
    enableScrollInteraction(value: boolean | undefined): this
    friction(value: double | arkui_component_units_Resource | undefined): this
    alignItems(value: GridItemAlignment | undefined): this {
        throw new Error('Unimplemented method alignItems')
    }
    editModeOptions(value: EditModeOptions): this {
        throw new Error('Unimplemented method editModeOptions')
    }
    focusWrapMode(value: FocusWrapMode | undefined): this {
        throw new Error('Unimplemented method focusWrapMode')
    }
    syncLoad(value: boolean | undefined): this {
        throw new Error('Unimplemented method syncLoad')
    }
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        throw new Error('Unimplemented method onScrollFrameBegin')
    }
    onWillScroll(value: OnWillScrollCallback | undefined): this {
        throw new Error('Unimplemented method onWillScroll')
    }
    onDidScroll(value: OnScrollCallback | undefined): this {
        throw new Error('Unimplemented method onDidScroll')
    }
    cachedCount(count: int32 | undefined, show: boolean | undefined): this {
        throw new Error('Unimplemented method cachedCount')
    }
    edgeEffect(value: EdgeEffect | undefined, options?: EdgeEffectOptions): this {
        throw new Error('Unimplemented method edgeEffect')
    }
    attributeModifier(value: AttributeModifier<GridAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkGridComponent extends ArkScrollableCommonMethodComponent implements GridAttribute {
    getPeer(): ArkGridPeer {
        return (this.peer as ArkGridPeer)
    }
    public setGridOptions(scroller?: Scroller, layoutOptions?: GridLayoutOptions): this {
        const scroller_casted = scroller as (Scroller | undefined)
        const layoutOptions_casted = layoutOptions as (GridLayoutOptions | undefined)
        this.getPeer()?.setGridOptionsAttribute(scroller_casted, layoutOptions_casted)
        this.applyOptionsFinish('GridAttribute');
        return this
    }
    public columnsTemplate(value: string | ItemFillPolicy | undefined): this {
        const value_casted = value as (string | ItemFillPolicy | undefined)
        this.getPeer()?.setColumnsTemplateAttribute(value_casted)
        return this
    }
    public rowsTemplate(value: string | undefined): this {
        const value_casted = value as (string | undefined)
        this.getPeer()?.setRowsTemplateAttribute(value_casted)
        return this
    }
    public columnsGap(value: Length | undefined): this {
        const value_casted = value as (Length | undefined)
        this.getPeer()?.setColumnsGapAttribute(value_casted)
        return this
    }
    public rowsGap(value: Length | undefined): this {
        const value_casted = value as (Length | undefined)
        this.getPeer()?.setRowsGapAttribute(value_casted)
        return this
    }
    public scrollBarWidth(value: double | string | undefined): this {
        const value_casted = value as (double | string | undefined)
        this.getPeer()?.setScrollBarWidthAttribute(value_casted)
        return this
    }
    public scrollBarColor(value: arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined): this {
        const value_casted = value as (arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined)
        this.getPeer()?.setScrollBarColorAttribute(value_casted)
        return this
    }
    public scrollBar(value: BarState | undefined): this {
        const value_casted = value as (BarState | undefined)
        this.getPeer()?.setScrollBarAttribute(value_casted)
        return this
    }
    public onScrollBarUpdate(value: ((index: int32,offset: double) => ComputedBarAttribute) | undefined): this {
        const value_casted = value as (((index: int32,offset: double) => ComputedBarAttribute) | undefined)
        this.getPeer()?.setOnScrollBarUpdateAttribute(value_casted)
        return this
    }
    public onScrollIndex(value: ((first: int32,last: int32) => void) | undefined): this {
        const value_casted = value as (((first: int32,last: int32) => void) | undefined)
        this.getPeer()?.setOnScrollIndexAttribute(value_casted)
        return this
    }
    public cachedCount(value: int32 | undefined): this {
        const value_casted = value as (int32 | undefined)
        this.getPeer()?.setCachedCount0Attribute(value_casted)
        return this
    }
    public editMode(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setEditModeAttribute(value_casted)
        return this
    }
    public multiSelectable(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setMultiSelectableAttribute(value_casted)
        return this
    }
    public maxCount(value: int32 | undefined): this {
        const value_casted = value as (int32 | undefined)
        this.getPeer()?.setMaxCountAttribute(value_casted)
        return this
    }
    public minCount(value: int32 | undefined): this {
        const value_casted = value as (int32 | undefined)
        this.getPeer()?.setMinCountAttribute(value_casted)
        return this
    }
    public cellLength(value: double | undefined): this {
        const value_casted = value as (double | undefined)
        this.getPeer()?.setCellLengthAttribute(value_casted)
        return this
    }
    public layoutDirection(value: GridDirection | undefined): this {
        const value_casted = value as (GridDirection | undefined)
        this.getPeer()?.setLayoutDirectionAttribute(value_casted)
        return this
    }
    public supportAnimation(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setSupportAnimationAttribute(value_casted)
        return this
    }
    public supportEmptyBranchInLazyLoading(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setSupportEmptyBranchInLazyLoadingAttribute(value_casted)
        return this
    }
    public onItemDragStart(value: OnItemDragStartCallback | undefined): this {
        const value_casted = value as (OnItemDragStartCallback | undefined)
        this.getPeer()?.setOnItemDragStartAttribute(value_casted)
        return this
    }
    public onItemDragEnter(value: ((event: ItemDragInfo) => void) | undefined): this {
        const value_casted = value as (((event: ItemDragInfo) => void) | undefined)
        this.getPeer()?.setOnItemDragEnterAttribute(value_casted)
        return this
    }
    public onItemDragMove(value: ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32) => void) | undefined): this {
        const value_casted = value as (((event: ItemDragInfo,itemIndex: int32,insertIndex: int32) => void) | undefined)
        this.getPeer()?.setOnItemDragMoveAttribute(value_casted)
        return this
    }
    public onItemDragLeave(value: ((event: ItemDragInfo,itemIndex: int32) => void) | undefined): this {
        const value_casted = value as (((event: ItemDragInfo,itemIndex: int32) => void) | undefined)
        this.getPeer()?.setOnItemDragLeaveAttribute(value_casted)
        return this
    }
    public onItemDrop(value: ((event: ItemDragInfo,itemIndex: int32,insertIndex: int32,isSuccess: boolean) => void) | undefined): this {
        const value_casted = value as (((event: ItemDragInfo,itemIndex: int32,insertIndex: int32,isSuccess: boolean) => void) | undefined)
        this.getPeer()?.setOnItemDropAttribute(value_casted)
        return this
    }
    public nestedScroll(value: NestedScrollOptions | undefined): this {
        const value_casted = value as (NestedScrollOptions | undefined)
        this.getPeer()?.setNestedScrollAttribute(value_casted)
        return this
    }
    public enableScrollInteraction(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setEnableScrollInteractionAttribute(value_casted)
        return this
    }
    public friction(value: double | arkui_component_units_Resource | undefined): this {
        const value_casted = value as (double | arkui_component_units_Resource | undefined)
        this.getPeer()?.setFrictionAttribute(value_casted)
        return this
    }
    public alignItems(value: GridItemAlignment | undefined): this {
        const value_casted = value as (GridItemAlignment | undefined)
        this.getPeer()?.setAlignItemsAttribute(value_casted)
        return this
    }
    public editModeOptions(value: EditModeOptions): this {
        const value_casted = value as (EditModeOptions)
        this.getPeer()?.setEditModeOptionsAttribute(value_casted)
        return this
    }
    public focusWrapMode(value: FocusWrapMode | undefined): this {
        const value_casted = value as (FocusWrapMode | undefined)
        this.getPeer()?.setFocusWrapModeAttribute(value_casted)
        return this
    }
    public syncLoad(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setSyncLoadAttribute(value_casted)
        return this
    }
    public onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        const value_casted = value as (OnScrollFrameBeginCallback | undefined)
        this.getPeer()?.setOnScrollFrameBeginAttribute(value_casted)
        return this
    }
    public onWillScroll(value: OnWillScrollCallback | undefined): this {
        const value_casted = value as (OnWillScrollCallback | undefined)
        this.getPeer()?.setOnWillScrollAttribute(value_casted)
        return this
    }
    public onDidScroll(value: OnScrollCallback | undefined): this {
        const value_casted = value as (OnScrollCallback | undefined)
        this.getPeer()?.setOnDidScrollAttribute(value_casted)
        return this
    }
    public cachedCount(count: int32 | undefined, show: boolean | undefined): this {
        const count_casted = count as (int32 | undefined)
        const show_casted = show as (boolean | undefined)
        this.getPeer()?.setCachedCount1Attribute(count_casted, show_casted)
        return this
    }
    public edgeEffect(value: EdgeEffect | undefined, options?: EdgeEffectOptions): this {
        const value_casted = value as (EdgeEffect | undefined)
        const options_casted = options as (EdgeEffectOptions | undefined)
        this.getPeer()?.setEdgeEffectAttribute(value_casted, options_casted)
        return this
    }
    public attributeModifier(value: AttributeModifier<GridAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookGridAttributeModifier(this, value);
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

@memo
export function GridImpl(
    @memo @memo_skip
    style: ((attributes: GridAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkGridComponent>((): ArkGridComponent => {
        return new ArkGridComponent()
    })
    NodeAttach<ArkGridPeer>((): ArkGridPeer => ArkGridPeer.create(receiver), (_: ArkGridPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class StartLineInfo_serializer {
    public static write(buffer: SerializerBase, value: StartLineInfo): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForStartIndex = value.startIndex
        valueSerializer.writeInt32(valueHolderForStartIndex)
        const valueHolderForStartLine = value.startLine
        valueSerializer.writeInt32(valueHolderForStartLine)
        const valueHolderForStartOffset = value.startOffset
        valueSerializer.writeFloat64(valueHolderForStartOffset)
        const valueHolderForTotalOffset = value.totalOffset
        valueSerializer.writeFloat64(valueHolderForTotalOffset)
    }
    public static read(buffer: DeserializerBase): StartLineInfo {
        let valueDeserializer: DeserializerBase = buffer
        const startIndexTmpResult: int32 = valueDeserializer.readInt32()
        const startLineTmpResult: int32 = valueDeserializer.readInt32()
        const startOffsetTmpResult: double = valueDeserializer.readFloat64()
        const totalOffsetTmpResult: double = valueDeserializer.readFloat64()
        let value: StartLineInfo = ({startIndex: startIndexTmpResult, startLine: startLineTmpResult, startOffset: startOffsetTmpResult, totalOffset: totalOffsetTmpResult} as StartLineInfo)
        return value
    }
}
export class UIGridEvent_serializer {
    public static write(buffer: SerializerBase, value: UIGridEvent): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): UIGridEvent {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return UIGridEventInternal.fromPtr(ptr)
    }
}
export class ComputedBarAttribute_serializer {
    public static write(buffer: SerializerBase, value: ComputedBarAttribute): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForTotalOffset = value.totalOffset
        valueSerializer.writeFloat64(valueHolderForTotalOffset)
        const valueHolderForTotalLength = value.totalLength
        valueSerializer.writeFloat64(valueHolderForTotalLength)
    }
    public static read(buffer: DeserializerBase): ComputedBarAttribute {
        let valueDeserializer: DeserializerBase = buffer
        const totalOffsetTmpResult: double = valueDeserializer.readFloat64()
        const totalLengthTmpResult: double = valueDeserializer.readFloat64()
        let value: ComputedBarAttribute = ({totalOffset: totalOffsetTmpResult, totalLength: totalLengthTmpResult} as ComputedBarAttribute)
        return value
    }
}
export class GridLayoutOptions_serializer {
    public static write(buffer: SerializerBase, value: GridLayoutOptions): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForRegularSize = value.regularSize
        const valueHolderForRegularSize_0 = valueHolderForRegularSize[0]
        valueSerializer.writeInt32(valueHolderForRegularSize_0)
        const valueHolderForRegularSize_1 = valueHolderForRegularSize[1]
        valueSerializer.writeInt32(valueHolderForRegularSize_1)
        const valueHolderForIrregularIndexes = value.irregularIndexes
        if (valueHolderForIrregularIndexes !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIrregularIndexesTmpValue = valueHolderForIrregularIndexes!
            valueSerializer.writeInt32((valueHolderForIrregularIndexesTmpValue.length).toInt())
            for (let valueHolderForIrregularIndexesTmpValueCounterI = 0; valueHolderForIrregularIndexesTmpValueCounterI < valueHolderForIrregularIndexesTmpValue.length; valueHolderForIrregularIndexesTmpValueCounterI++) {
                const valueHolderForIrregularIndexesTmpValueTmpElement: int32 = valueHolderForIrregularIndexesTmpValue[valueHolderForIrregularIndexesTmpValueCounterI]
                valueSerializer.writeInt32(valueHolderForIrregularIndexesTmpValueTmpElement)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnGetIrregularSizeByIndex = value.onGetIrregularSizeByIndex
        if (valueHolderForOnGetIrregularSizeByIndex !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnGetIrregularSizeByIndexTmpValue = valueHolderForOnGetIrregularSizeByIndex!
            valueSerializer.holdAndWriteCallback(valueHolderForOnGetIrregularSizeByIndexTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnGetRectByIndex = value.onGetRectByIndex
        if (valueHolderForOnGetRectByIndex !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnGetRectByIndexTmpValue = valueHolderForOnGetRectByIndex!
            valueSerializer.holdAndWriteCallback(valueHolderForOnGetRectByIndexTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnGetStartIndexByOffset = value.onGetStartIndexByOffset
        if (valueHolderForOnGetStartIndexByOffset !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnGetStartIndexByOffsetTmpValue = valueHolderForOnGetStartIndexByOffset!
            valueSerializer.holdAndWriteCallback(valueHolderForOnGetStartIndexByOffsetTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnGetStartIndexByIndex = value.onGetStartIndexByIndex
        if (valueHolderForOnGetStartIndexByIndex !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnGetStartIndexByIndexTmpValue = valueHolderForOnGetStartIndexByIndex!
            valueSerializer.holdAndWriteCallback(valueHolderForOnGetStartIndexByIndexTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): GridLayoutOptions {
        let valueDeserializer: DeserializerBase = buffer
        const regularSizeTmpBufValue0: int32 = valueDeserializer.readInt32()
        const regularSizeTmpBufValue1: int32 = valueDeserializer.readInt32()
        const regularSizeTmpResult: [ int32, int32 ] = ([regularSizeTmpBufValue0, regularSizeTmpBufValue1] as [ int32, int32 ])
        const irregularIndexesTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let irregularIndexesTmpBuf: Array<int32> | undefined = undefined
        if ((irregularIndexesTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const irregularIndexesTmpBufOptLength: int32 = valueDeserializer.readInt32()
            let irregularIndexesTmpBufOpt: Array<int32> = new Array<int32>(irregularIndexesTmpBufOptLength)
            for (let irregularIndexesTmpBufOptBufCounterI = 0; irregularIndexesTmpBufOptBufCounterI < irregularIndexesTmpBufOptLength; irregularIndexesTmpBufOptBufCounterI++) {
                irregularIndexesTmpBufOpt[irregularIndexesTmpBufOptBufCounterI] = valueDeserializer.readInt32()
            }
            irregularIndexesTmpBuf = irregularIndexesTmpBufOpt
        }
        const irregularIndexesTmpResult: Array<int32> | undefined = irregularIndexesTmpBuf
        const onGetIrregularSizeByIndexTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let onGetIrregularSizeByIndexTmpBuf: ((index: int32) => [ int32, int32 ]) | undefined = undefined
        if ((onGetIrregularSizeByIndexTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onGetIrregularSizeByIndexTmpBufOptBufResource: CallbackResource = valueDeserializer.readCallbackResource()
            const onGetIrregularSizeByIndexTmpBufOptBufCall: KPointer = valueDeserializer.readPointer()
            const onGetIrregularSizeByIndexTmpBufOptBufCallSync: KPointer = valueDeserializer.readPointer()
            const onGetIrregularSizeByIndexTmpBufOptClosure = (index: int32):[ int32, int32 ] => {
                const onGetIrregularSizeByIndexTmpBufOptBufArgsSerializer: SerializerBase = SerializerBase.hold();
                onGetIrregularSizeByIndexTmpBufOptBufArgsSerializer.writeInt32(onGetIrregularSizeByIndexTmpBufOptBufResource.resourceId);
                onGetIrregularSizeByIndexTmpBufOptBufArgsSerializer.writePointer(onGetIrregularSizeByIndexTmpBufOptBufCall);
                onGetIrregularSizeByIndexTmpBufOptBufArgsSerializer.writePointer(onGetIrregularSizeByIndexTmpBufOptBufCallSync);
                onGetIrregularSizeByIndexTmpBufOptBufArgsSerializer.writeInt32(index);
                let onGetIrregularSizeByIndexTmpBufOptBufContinuationValue: [ int32, int32 ] | undefined;
                const onGetIrregularSizeByIndexTmpBufOptBufContinuationCallback: ((value: [ int32, int32 ]) => void) = (value: [ int32, int32 ]):void => {
                onGetIrregularSizeByIndexTmpBufOptBufContinuationValue = value;
            }
                onGetIrregularSizeByIndexTmpBufOptBufArgsSerializer.holdAndWriteCallback(onGetIrregularSizeByIndexTmpBufOptBufContinuationCallback);
                InteropNativeModule._CallCallbackSync(10, -1469165237, onGetIrregularSizeByIndexTmpBufOptBufArgsSerializer.asBuffer(), onGetIrregularSizeByIndexTmpBufOptBufArgsSerializer.length());
                onGetIrregularSizeByIndexTmpBufOptBufArgsSerializer.release();
                return (onGetIrregularSizeByIndexTmpBufOptBufContinuationValue as [ int32, int32 ]);
            }
            resourceFinalizerRegister(onGetIrregularSizeByIndexTmpBufOptClosure, onGetIrregularSizeByIndexTmpBufOptBufResource)
            onGetIrregularSizeByIndexTmpBuf = onGetIrregularSizeByIndexTmpBufOptClosure
        }
        const onGetIrregularSizeByIndexTmpResult: ((index: int32) => [ int32, int32 ]) | undefined = onGetIrregularSizeByIndexTmpBuf
        const onGetRectByIndexTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let onGetRectByIndexTmpBuf: ((index: int32) => [ int32, int32, int32, int32 ]) | undefined = undefined
        if ((onGetRectByIndexTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onGetRectByIndexTmpBufOptBufResource: CallbackResource = valueDeserializer.readCallbackResource()
            const onGetRectByIndexTmpBufOptBufCall: KPointer = valueDeserializer.readPointer()
            const onGetRectByIndexTmpBufOptBufCallSync: KPointer = valueDeserializer.readPointer()
            const onGetRectByIndexTmpBufOptClosure = (index: int32):[ int32, int32, int32, int32 ] => {
                const onGetRectByIndexTmpBufOptBufArgsSerializer: SerializerBase = SerializerBase.hold();
                onGetRectByIndexTmpBufOptBufArgsSerializer.writeInt32(onGetRectByIndexTmpBufOptBufResource.resourceId);
                onGetRectByIndexTmpBufOptBufArgsSerializer.writePointer(onGetRectByIndexTmpBufOptBufCall);
                onGetRectByIndexTmpBufOptBufArgsSerializer.writePointer(onGetRectByIndexTmpBufOptBufCallSync);
                onGetRectByIndexTmpBufOptBufArgsSerializer.writeInt32(index);
                let onGetRectByIndexTmpBufOptBufContinuationValue: [ int32, int32, int32, int32 ] | undefined;
                const onGetRectByIndexTmpBufOptBufContinuationCallback: ((value: [ int32, int32, int32, int32 ]) => void) = (value: [ int32, int32, int32, int32 ]):void => {
                onGetRectByIndexTmpBufOptBufContinuationValue = value;
            }
                onGetRectByIndexTmpBufOptBufArgsSerializer.holdAndWriteCallback(onGetRectByIndexTmpBufOptBufContinuationCallback);
                InteropNativeModule._CallCallbackSync(10, -1306551541, onGetRectByIndexTmpBufOptBufArgsSerializer.asBuffer(), onGetRectByIndexTmpBufOptBufArgsSerializer.length());
                onGetRectByIndexTmpBufOptBufArgsSerializer.release();
                return (onGetRectByIndexTmpBufOptBufContinuationValue as [ int32, int32, int32, int32 ]);
            }
            resourceFinalizerRegister(onGetRectByIndexTmpBufOptClosure, onGetRectByIndexTmpBufOptBufResource)
            onGetRectByIndexTmpBuf = onGetRectByIndexTmpBufOptClosure
        }
        const onGetRectByIndexTmpResult: ((index: int32) => [ int32, int32, int32, int32 ]) | undefined = onGetRectByIndexTmpBuf
        const onGetStartIndexByOffsetTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let onGetStartIndexByOffsetTmpBuf: OnGetStartIndexByOffsetCallback | undefined = undefined
        if ((onGetStartIndexByOffsetTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onGetStartIndexByOffsetTmpBufOptBufResource: CallbackResource = valueDeserializer.readCallbackResource()
            const onGetStartIndexByOffsetTmpBufOptBufCall: KPointer = valueDeserializer.readPointer()
            const onGetStartIndexByOffsetTmpBufOptBufCallSync: KPointer = valueDeserializer.readPointer()
            const onGetStartIndexByOffsetTmpBufOptClosure = (totalOffset: double):StartLineInfo => {
                const onGetStartIndexByOffsetTmpBufOptBufArgsSerializer: SerializerBase = SerializerBase.hold();
                onGetStartIndexByOffsetTmpBufOptBufArgsSerializer.writeInt32(onGetStartIndexByOffsetTmpBufOptBufResource.resourceId);
                onGetStartIndexByOffsetTmpBufOptBufArgsSerializer.writePointer(onGetStartIndexByOffsetTmpBufOptBufCall);
                onGetStartIndexByOffsetTmpBufOptBufArgsSerializer.writePointer(onGetStartIndexByOffsetTmpBufOptBufCallSync);
                onGetStartIndexByOffsetTmpBufOptBufArgsSerializer.writeFloat64(totalOffset);
                let onGetStartIndexByOffsetTmpBufOptBufContinuationValue: StartLineInfo | undefined;
                const onGetStartIndexByOffsetTmpBufOptBufContinuationCallback: ((value: StartLineInfo) => void) = (value: StartLineInfo):void => {
                onGetStartIndexByOffsetTmpBufOptBufContinuationValue = value;
            }
                onGetStartIndexByOffsetTmpBufOptBufArgsSerializer.holdAndWriteCallback(onGetStartIndexByOffsetTmpBufOptBufContinuationCallback);
                InteropNativeModule._CallCallbackSync(10, 1845491332, onGetStartIndexByOffsetTmpBufOptBufArgsSerializer.asBuffer(), onGetStartIndexByOffsetTmpBufOptBufArgsSerializer.length());
                onGetStartIndexByOffsetTmpBufOptBufArgsSerializer.release();
                return (onGetStartIndexByOffsetTmpBufOptBufContinuationValue as StartLineInfo);
            }
            resourceFinalizerRegister(onGetStartIndexByOffsetTmpBufOptClosure, onGetStartIndexByOffsetTmpBufOptBufResource)
            onGetStartIndexByOffsetTmpBuf = onGetStartIndexByOffsetTmpBufOptClosure
        }
        const onGetStartIndexByOffsetTmpResult: OnGetStartIndexByOffsetCallback | undefined = onGetStartIndexByOffsetTmpBuf
        const onGetStartIndexByIndexTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let onGetStartIndexByIndexTmpBuf: OnGetStartIndexByIndexCallback | undefined = undefined
        if ((onGetStartIndexByIndexTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onGetStartIndexByIndexTmpBufOptBufResource: CallbackResource = valueDeserializer.readCallbackResource()
            const onGetStartIndexByIndexTmpBufOptBufCall: KPointer = valueDeserializer.readPointer()
            const onGetStartIndexByIndexTmpBufOptBufCallSync: KPointer = valueDeserializer.readPointer()
            const onGetStartIndexByIndexTmpBufOptClosure = (targetIndex: int32):StartLineInfo => {
                const onGetStartIndexByIndexTmpBufOptBufArgsSerializer: SerializerBase = SerializerBase.hold();
                onGetStartIndexByIndexTmpBufOptBufArgsSerializer.writeInt32(onGetStartIndexByIndexTmpBufOptBufResource.resourceId);
                onGetStartIndexByIndexTmpBufOptBufArgsSerializer.writePointer(onGetStartIndexByIndexTmpBufOptBufCall);
                onGetStartIndexByIndexTmpBufOptBufArgsSerializer.writePointer(onGetStartIndexByIndexTmpBufOptBufCallSync);
                onGetStartIndexByIndexTmpBufOptBufArgsSerializer.writeInt32(targetIndex);
                let onGetStartIndexByIndexTmpBufOptBufContinuationValue: StartLineInfo | undefined;
                const onGetStartIndexByIndexTmpBufOptBufContinuationCallback: ((value: StartLineInfo) => void) = (value: StartLineInfo):void => {
                onGetStartIndexByIndexTmpBufOptBufContinuationValue = value;
            }
                onGetStartIndexByIndexTmpBufOptBufArgsSerializer.holdAndWriteCallback(onGetStartIndexByIndexTmpBufOptBufContinuationCallback);
                InteropNativeModule._CallCallbackSync(10, 1211287927, onGetStartIndexByIndexTmpBufOptBufArgsSerializer.asBuffer(), onGetStartIndexByIndexTmpBufOptBufArgsSerializer.length());
                onGetStartIndexByIndexTmpBufOptBufArgsSerializer.release();
                return (onGetStartIndexByIndexTmpBufOptBufContinuationValue as StartLineInfo);
            }
            resourceFinalizerRegister(onGetStartIndexByIndexTmpBufOptClosure, onGetStartIndexByIndexTmpBufOptBufResource)
            onGetStartIndexByIndexTmpBuf = onGetStartIndexByIndexTmpBufOptClosure
        }
        const onGetStartIndexByIndexTmpResult: OnGetStartIndexByIndexCallback | undefined = onGetStartIndexByIndexTmpBuf
        let value: GridLayoutOptions = ({regularSize: regularSizeTmpResult, irregularIndexes: irregularIndexesTmpResult, onGetIrregularSizeByIndex: onGetIrregularSizeByIndexTmpResult, onGetRectByIndex: onGetRectByIndexTmpResult, onGetStartIndexByOffset: onGetStartIndexByOffsetTmpResult, onGetStartIndexByIndex: onGetStartIndexByIndexTmpResult} as GridLayoutOptions)
        return value
    }
}
export interface UIGridEvent extends UIScrollableCommonEvent {
    setOnWillScroll(callback_: OnWillScrollCallback | undefined): void
    setOnDidScroll(callback_: OnScrollCallback | undefined): void
    setOnScrollIndex(callback_: OnGridScrollIndexCallback | undefined): void
}
export class UIGridEventInternal extends UIScrollableCommonEventInternal implements MaterializedBase,UIGridEvent {
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        super(tag, peerPtr)
    }
    constructor() {
        this(MaterializedBaseTag.NOP, UIGridEventInternal.construct())
    }
    static construct(): KPointer {
        const retval = ArkUIGeneratedNativeModule._UIGridEvent_construct()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._UIGridEvent_getFinalizer()
    }
    public static fromPtr(ptr: KPointer): UIGridEventInternal {
        return new UIGridEventInternal(MaterializedBaseTag.NOP, ptr)
    }
    public setOnWillScroll(callback_: OnWillScrollCallback | undefined): void {
        const callback__casted = callback_ as (OnWillScrollCallback | undefined)
        this.setOnWillScroll_serialize(callback__casted)
        return
    }
    public setOnDidScroll(callback_: OnScrollCallback | undefined): void {
        const callback__casted = callback_ as (OnScrollCallback | undefined)
        this.setOnDidScroll_serialize(callback__casted)
        return
    }
    public setOnScrollIndex(callback_: OnGridScrollIndexCallback | undefined): void {
        const callback__casted = callback_ as (OnGridScrollIndexCallback | undefined)
        this.setOnScrollIndex_serialize(callback__casted)
        return
    }
    private setOnWillScroll_serialize(callback_: OnWillScrollCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (callback_ !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const callback_TmpValue = callback_!
            thisSerializer.holdAndWriteCallback(callback_TmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._UIGridEvent_setOnWillScroll(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOnDidScroll_serialize(callback_: OnScrollCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (callback_ !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const callback_TmpValue = callback_!
            thisSerializer.holdAndWriteCallback(callback_TmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._UIGridEvent_setOnDidScroll(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private setOnScrollIndex_serialize(callback_: OnGridScrollIndexCallback | undefined): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (callback_ !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const callback_TmpValue = callback_!
            thisSerializer.holdAndWriteCallback(callback_TmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._UIGridEvent_setOnScrollIndex(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
