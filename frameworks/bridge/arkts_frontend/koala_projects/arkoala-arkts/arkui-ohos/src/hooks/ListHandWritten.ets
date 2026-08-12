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

import { ArkUIAniModule } from "arkui.ani"
import { ArkListPeer, ArkListItemGroupPeer, ChildrenMainSize } from "#generated";
import { ArkArcListPeer, ArkArcListComponent, ArcListAttribute } from "../../@ohos.arkui.ArcList.ets";
import { AttributeModifier, CommonMethod } from "../component/common";
import { CommonModifier } from "../CommonModifier";
import { applyAttributeModifierNoCommonMethod, applyCommonModifier } from "./modifiers/ArkCommonModifier";

export class ListHandWritten {
    static hookListChildrenMainSizeImpl(peer: ArkListPeer, value: ChildrenMainSize | undefined): void {
        ArkUIAniModule._SetListChildrenMainSize(peer.peer.ptr, value)
    }

    static hookListItemGroupChildrenMainSizeImpl(
        peer: ArkListItemGroupPeer, value: ChildrenMainSize | undefined): void {
        ArkUIAniModule._SetListChildrenMainSize(peer.peer.ptr, value)
    }

    static hookArkListChildrenMainSizeImpl(
        peer: ArkArcListPeer, value: ChildrenMainSize | undefined): void {
        ArkUIAniModule._SetListChildrenMainSize(peer.peer.ptr, value)
    }
}

export function hookArcListAttributeModifier(
    component: ArkArcListComponent,
    modifier: AttributeModifier<ArcListAttribute> | AttributeModifier<CommonMethod> | undefined
): void {
    if (modifier === undefined) {
        return;
    }
    if (modifier instanceof CommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    const peer = component.getPeer();
    const createReceiver = (): ArkArcListComponent => {
        const receiver = new ArkArcListComponent();
        receiver.setPeer(peer);
        return receiver;
    };
    const constructParam = (receiver: ArkArcListComponent, ...params: FixedArray<Object>): void => {};
    const receiver = applyAttributeModifierNoCommonMethod(
        modifier as Object as AttributeModifier<ArcListAttribute>,
        createReceiver,
        constructParam,
        createReceiver,
        peer
    );
    receiver.applyAttributesFinish();
}
