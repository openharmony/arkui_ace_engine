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

import { ArkBaseNode } from "./ArkBaseNode";
import { BadgeAttribute, ArkBadgeComponent, BadgeParamWithNumber, BadgeParamWithString } from "../component/badge";
import { runtimeType } from "@koalaui/interop";

export class ArkBadgeNode extends ArkBaseNode  implements BadgeAttribute  {
    private component: ArkBadgeComponent = new ArkBadgeComponent()
    initialize(value: BadgeParamWithNumber | BadgeParamWithString): this {
        this.component.setPeer(this.getPeer())
        this.setBadgeOptions(value)
        return this;
    }
    public setBadgeOptions(value: BadgeParamWithNumber | BadgeParamWithString): this {
        this.component.setBadgeOptions(value)
        return this
    }
    public markDirty(): void {
        // we call this function outside of class, so need to make it public
        super.markDirty()
    }
}