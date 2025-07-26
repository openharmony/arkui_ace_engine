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

import { ImageAttribute, HorizontalAlign } from "../../generated";
import { ArkImagePeer } from "../../generated/peers/ArkImagePeer";
import { Length, BorderRadiuses } from "../../generated/ArkUnitsInterfaces"
import { Resource } from "../../generated/ArkResourceInterfaces"
import { ArkBaseNode } from "./ArkBaseNode";

export class ArkImageNode extends ArkBaseNode implements ImageAttribute {
    borderRadius(value: Length | BorderRadiuses): this {
        if (value) {
            this.getPeer().imageBorderRadiusAttribute(value);
        } else {
        }
        return this;
    }
    opacity(value: number | Resource): this {
        if (value) {
            this.getPeer().imageOpacityAttribute(value);
        } else {
        }
        return this;
    }
    getPeer() : ArkImagePeer {
        return this.peer as ArkImagePeer
    }
}