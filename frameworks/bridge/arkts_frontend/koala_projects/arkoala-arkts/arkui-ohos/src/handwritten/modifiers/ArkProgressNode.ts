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
import { LinearGradient, ProgressOptions, ResourceColor, ProgressAttribute, ArkProgressComponent, LinearStyleOptions, RingStyleOptions, CapsuleStyleOptions, ProgressStyleOptions } from "../../component";
import { ContentModifier } from "../../component/arkui-wrapper-builder"

export class ArkProgressNode extends ArkBaseNode implements ProgressAttribute {
    private component: ArkProgressComponent = new ArkProgressComponent()
    initialize(options: ProgressOptions): this {
        this.component.setPeer(this.getPeer())
        this.setProgressOptions(options)
        return this;
    }
    public setProgressOptions(options: ProgressOptions): this {
        this.component.setProgressOptions(options)
        this.markDirty()
        return this
    }
    public value(value: number | undefined): this {
        this.component.value(value)
        this.markDirty()
        return this
    }
    public color(value: ResourceColor | LinearGradient | undefined): this {
        this.component.color(value)
        this.markDirty()
        return this
    }
    public style(value: LinearStyleOptions | RingStyleOptions | CapsuleStyleOptions | ProgressStyleOptions | undefined): this {
        this.component.style(value)
        this.markDirty()
        return this
    }
    public privacySensitive(value: boolean | undefined): this {
        this.component.privacySensitive(value)
        this.markDirty()
        return this
    }
    public contentModifier(value: ContentModifier | undefined): this {
        this.component.contentModifier(value)
        this.markDirty()
        return this
    }
    public markDirty(): void {
        // we call this function outside of class, so need to make it public
        super.markDirty()
    }
}