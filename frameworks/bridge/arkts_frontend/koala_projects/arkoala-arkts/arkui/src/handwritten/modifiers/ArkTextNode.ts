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

import { TextAttribute, TextAlign } from "../../generated";
import { ArkTextPeer } from "../../generated/peers/ArkTextPeer";
import { ArkBaseNode } from "./ArkBaseNode";

export class ArkTextNode extends ArkBaseNode implements TextAttribute {
    textAlign(value : TextAlign | undefined) : this {
        if (value) {
            this.getPeer().textAlignAttribute(value);
        } else {
            // this.getPeer().resetAlignItemsAttribute(value);
        }
        return this;
    }
    getPeer() : ArkTextPeer {
        return this.peer as ArkTextPeer
    }
}