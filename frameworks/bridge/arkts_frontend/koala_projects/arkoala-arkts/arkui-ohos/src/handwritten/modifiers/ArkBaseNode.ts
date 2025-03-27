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

import { ComponentBase } from "../../ComponentBase";
import { CommonAttribute, CommonMethod, Length } from "../../generated";
import { ArkCommonMethodPeer } from "../../generated/peers/ArkCommonPeer";

export class ArkBaseNode extends ComponentBase implements CommonAttribute {
    getPeer() : ArkCommonMethodPeer {
        return this.peer as ArkCommonMethodPeer
    }

    width(value: Length | undefined) : this {
        if (!value) {
            // this.getPeer().resetWidthAttribute()
            return this;
        }
        this.getPeer().widthAttribute(value)
        return this;
    }
    height(value: Length | undefined): this {
        if (!value) {
            // this.getPeer().resetHeightAttribute()
            return this;
        }
        this.getPeer().heightAttribute(value)
        return this;
    }
}