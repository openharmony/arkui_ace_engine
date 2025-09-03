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

import { ChildrenMainSize } from "../component/common"
import { ArkUIAniModule } from "arkui.ani"
import { ArkListComponent, ArkListItemGroupComponent } from "../component"
import { ArkListNode } from "./modifiers/ArkListNode"
import { ArkListItemGroupNode } from "./modifiers/ArkListItemGroupNode"

export function hookListChildrenMainSizeImpl(node: ArkListComponent, value: ChildrenMainSize | undefined): void {
    if (value !== undefined) {
        ArkUIAniModule._SetListChildrenMainSize(node.getPeer().peer.ptr, value)
    }
}

export function hookListItemGroupChildrenMainSizeImpl(
    node: ArkListItemGroupComponent, value: ChildrenMainSize | undefined): void {
    if (value !== undefined) {
        ArkUIAniModule._SetListChildrenMainSize(node.getPeer().peer.ptr, value)
    }
}

export function hookListNodeChildrenMainSizeImpl(node: ArkListNode, value: ChildrenMainSize | undefined): void {
    if (value !== undefined) {
        ArkUIAniModule._SetListChildrenMainSize(node.getPeer().peer.ptr, value)
    }
}

export function hookListItemGroupNodeChildrenMainSizeImpl(
    node: ArkListItemGroupNode, value: ChildrenMainSize | undefined): void {
    if (value !== undefined) {
        ArkUIAniModule._SetListChildrenMainSize(node.getPeer().peer.ptr, value)
    }
}