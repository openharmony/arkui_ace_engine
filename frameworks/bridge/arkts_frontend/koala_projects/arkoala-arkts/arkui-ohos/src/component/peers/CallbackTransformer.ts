/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import { KPointer, nullptr } from "@koalaui/interop"
import { IncrementalNode } from "@koalaui/runtime"
import { CustomBuilder } from "../common"
import { CustomNodeBuilder } from "../customBuilder"
import { UIContextUtil } from 'arkui/handwritten/UIContextUtil'
import { UIContextImpl } from 'arkui/handwritten/UIContextImpl'

export class CallbackTransformer {
    static transformFromCustomBuilder(value: CustomBuilder): CustomNodeBuilder {
        let context = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        return (parentNodeId: KPointer): KPointer => {
            const peer = context.getDetachedRootEntryManager().createUiDetachedFreeRoot(() => new IncrementalNode(), value)
            return peer ? peer.peer.ptr : nullptr;
        }
    }
    static transformToCustomBuilder(value: CustomNodeBuilder): CustomBuilder {
        throw new Error("Not implemented")
    }

    static transfromToCallbackVoid(value: (data: undefined) => void): (() => void) {
        return () => {
            return value(undefined)
        }
    }

    static transfromFromCallbackVoid(value: () => void): ((data: undefined) => void) {
        return (data: undefined) => {
            return value()
        }
    }
}