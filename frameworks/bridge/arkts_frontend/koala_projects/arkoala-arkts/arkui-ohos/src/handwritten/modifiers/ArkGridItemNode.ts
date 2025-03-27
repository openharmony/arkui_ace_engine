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

import { GridItemAttribute } from "../../generated";
import { ArkGridItemPeer } from "../../generated/peers/ArkGridItemPeer";
import { ArkBaseNode } from "./ArkBaseNode";

export class ArkGridItemNode extends ArkBaseNode /* implements GridItemAttribute */ {
    
    rowStart(value : number) : this {
        if (value) {
            this.getPeer().rowStartAttribute(value);
        }
        return this;
    }

    rowEnd(value : number) : this {
        if (value) {
            this.getPeer().rowEndAttribute(value);
        }
        return this;
    }

    columnStart(value : number) : this {
        if (value) {
            this.getPeer().columnStartAttribute(value);
        }
        return this;
    }

    columnEnd(value : number) : this {
        if (value) {
            this.getPeer().columnEndAttribute(value);
        }
        return this;
    }

    getPeer() : ArkGridItemPeer {
        return this.peer as ArkGridItemPeer
    }
}