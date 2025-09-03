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
import { ResourceColor, QRCodeAttribute, ArkQRCodeComponent } from "../../component";
import { Resource } from "global.resource"

export class ArkQRCodeNode extends ArkBaseNode implements QRCodeAttribute {
    private component: ArkQRCodeComponent = new ArkQRCodeComponent()
    initialize(value: string): this {
        this.component.setPeer(this.getPeer())
        this.setQRCodeOptions(value)
        return this;
    }
    public setQRCodeOptions(value: string): this {
        this.component.setQRCodeOptions(value)
        this.markDirty()
        return this
    }
    public color(value: ResourceColor | undefined): this {
        this.component.color(value)
        this.markDirty()
        return this
    }
    public backgroundColor(value: ResourceColor | undefined): this {
        this.component.backgroundColor(value)
        this.markDirty()
        return this
    }
    public contentOpacity(value: number | Resource | undefined): this {
        this.component.contentOpacity(value)
        this.markDirty()
        return this
    }
    public markDirty(): void {
        // we call this function outside of class, so need to make it public
        super.markDirty()
    }
}