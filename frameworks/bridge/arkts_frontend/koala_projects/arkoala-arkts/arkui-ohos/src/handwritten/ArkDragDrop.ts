/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { int32 } from "@koalaui/common"
import { PeerNode } from "arkui/PeerNode"
import { KPointer } from "@koalaui/interop"
import { ArkCommonMethodComponent, DragDropOps, DragEvent, CustomBuilder, DragItemInfo, PreviewConfiguration,
    OnDragEventCallback, DropOptions } from '../component'
import { InteropNativeModule, runtimeType, RuntimeType, toPeerPtr} from "@koalaui/interop"
import { ArkUIAniModule } from "arkui.ani"
import { createUiDetachedRoot } from "arkui/ArkUIEntry"
import { ArkComponentRootPeer } from "arkui/component"
import { PixelMap, UniformDataType, DataSyncOptions} from "#external"
export class HookDragInfo {
    pixelMap?: PixelMap;
    id?: string;
    onlyForLifting?: boolean;
    delayCreating?: boolean;

    parseConfig(config: PreviewConfiguration) {
        let info : HookDragInfo = this
        const value_onlyForLifting  = config.onlyForLifting
        let value_onlyForLifting_type : int32 = RuntimeType.UNDEFINED
        value_onlyForLifting_type = runtimeType(value_onlyForLifting)
        if ((RuntimeType.UNDEFINED) != (value_onlyForLifting_type)) {
            const value_onlyForLifting_value  = value_onlyForLifting!
            info.onlyForLifting = value_onlyForLifting_value
        }
        const value_delayCreating = config.delayCreating
        let value_delayCreating_type : int32 = RuntimeType.UNDEFINED
        value_delayCreating_type = runtimeType(value_delayCreating)
        if ((RuntimeType.UNDEFINED) != (value_delayCreating_type)) {
            const value_delayCreating_value  = value_delayCreating!
            info.delayCreating = value_delayCreating_value
        }
    }
}

export function hookRegisterOnDragStartImpl(node: ArkCommonMethodComponent, onDragStartCallback: (((event: DragEvent, extraParams?: string) => CustomBuilder | DragItemInfo) | undefined)): void {
    DragDropOps.registerOnDragStart(node.getPeer().getPeerPtr(), (node: KPointer, dragEvent: DragEvent, extraParam: string) => {
        if (onDragStartCallback === undefined) {
            return
        }
        const value_dragEvent = (dragEvent as DragEvent)
        const value_extraParam = (extraParam as string)
        let res: CustomBuilder | DragItemInfo = onDragStartCallback(value_dragEvent, value_extraParam)
        const value_type = runtimeType(res)
        if (RuntimeType.FUNCTION === value_type) {
            const value_builder = res as CustomBuilder
            const peerNode = createUiDetachedRoot((): PeerNode  => {
                return ArkComponentRootPeer.create(undefined)
            }, value_builder)
            const createBuilderNodeTree = () : KPointer => {
                return peerNode.peer.ptr
            }
            let customNode = createBuilderNodeTree();
            ArkUIAniModule._DragEvent_Set_CustomNode(toPeerPtr(dragEvent), customNode)
        } else if (RuntimeType.OBJECT === value_type) {
            const itemInfo = res as DragItemInfo
            const value_extraInfo = itemInfo.extraInfo
            let value_extraInfo_type: int32 = RuntimeType.UNDEFINED
            value_extraInfo_type = runtimeType(value_extraInfo)
            if ((RuntimeType.UNDEFINED) !== (value_extraInfo_type)) {
                const value_extraInfo_value = value_extraInfo!
                ArkUIAniModule._DragEvent_Set_ExtraInfo(toPeerPtr(dragEvent), value_extraInfo_value)
            }
            const value_builder = itemInfo.builder
            let value_builder_type: int32 = RuntimeType.UNDEFINED
            value_builder_type = runtimeType(value_builder)
            if ((RuntimeType.FUNCTION) === (value_builder_type)) {
                const value_builder_value = itemInfo.builder as CustomBuilder
                const peerNode = createUiDetachedRoot((): PeerNode  => {
                    return ArkComponentRootPeer.create(undefined)
                }, value_builder_value)
                const createBuilderNodeTree = () : KPointer => {
                    return peerNode.peer.ptr
                }
                let customNode = createBuilderNodeTree()
                ArkUIAniModule._DragEvent_Set_CustomNode(toPeerPtr(dragEvent), customNode)
            } 
            const value_pixelMap = itemInfo.pixelMap
            let value_pixelMap_type: int32 = RuntimeType.UNDEFINED
            value_pixelMap_type = runtimeType(value_pixelMap)
            if ((RuntimeType.UNDEFINED) !== (value_pixelMap_type)) {
                ArkUIAniModule._DragEvent_Set_PixelMap(toPeerPtr(dragEvent), value_pixelMap as PixelMap)
            }
        }
    })
}

export function hookAllowDropAttribute(node: ArkCommonMethodComponent, value: Array<UniformDataType> | null | undefined) : void {
    if (!node) {
        return
    }
    if (value === null) {
        ArkUIAniModule._Drag_Set_AllowDrop_Null(node.getPeer().getPeerPtr())
        return
    }
    let value_type : int32 = RuntimeType.UNDEFINED
    value_type = runtimeType(value)
    if ((RuntimeType.UNDEFINED) === (value_type)) {
        return
    }
    const value_value = value! as Array<UniformDataType>
    const length = value_value.length as int32
    let array = new Array<string>()
    for (let i = 0; i < length; i++) {
        const value_value_element : UniformDataType = value_value[i] as UniformDataType
        if (value_value_element !== undefined) {
            const value_string : string = value_value_element
            array.push(value_string)
        }
    }
    ArkUIAniModule._Drag_Set_AllowDrop(node.getPeer().getPeerPtr(), array, length)
}

export function hookDragPreview(node: ArkCommonMethodComponent, preview: CustomBuilder | DragItemInfo | string | undefined, config?: PreviewConfiguration) : void {
    const preview_type = runtimeType(preview)
    const config_type = runtimeType(config)

    if (RuntimeType.OBJECT === preview_type) {
        let dragInfo = new HookDragInfo()
        const preview_casted = preview as DragItemInfo
        dragInfo.pixelMap = preview_casted.pixelMap
        if (dragInfo.pixelMap) {
            if ((RuntimeType.OBJECT === config_type)) {
                const config_casted = config as PreviewConfiguration
                dragInfo.parseConfig(config_casted)
            }
            ArkUIAniModule._Drag_Set_DragPreview(node.getPeer().getPeerPtr(), dragInfo)
            return
        }
    }
    DragDropOps.registerDragPreview(node.getPeer().getPeerPtr(), preview, config)
}

export function hookOnDrop(node: ArkCommonMethodComponent, eventCallback: ((event: DragEvent,extraParams?: string) => void) | OnDragEventCallback | undefined, dropOptions?: DropOptions) {
    DragDropOps.registerOnDrop(node.getPeer().getPeerPtr(), eventCallback, dropOptions)
}

export function hookDragEventStartDataLoading(node: KPointer, options: DataSyncOptions): string {
    const options_casted = options as (DataSyncOptions)
    return ArkUIAniModule._DragEvent_Start_Data_Loading(node, options_casted)
}
