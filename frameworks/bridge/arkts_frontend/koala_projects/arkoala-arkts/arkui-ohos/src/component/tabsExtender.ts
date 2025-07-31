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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { KPointer } from "@koalaui/interop"

export class TabsExtender {
    public static ApplyAttributesFinish(node: KPointer): void {
        const node_casted = node as (KPointer)
        TabsExtender.ApplyAttributesFinish_serialize(node_casted)
        return
    }
    private static ApplyAttributesFinish_serialize(node: KPointer): void {
        ArkUIGeneratedNativeModule._TabsExtender_ApplyAttributesFinish(node)
    }
}
