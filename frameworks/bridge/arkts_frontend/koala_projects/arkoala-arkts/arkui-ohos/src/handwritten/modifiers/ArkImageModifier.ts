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

import { AttributeModifier, ImageAttribute } from "../..";
import { ArkCommonAttributeSet } from "./ArkCommonModifier";

export class ArkImageAttributeSet extends ArkCommonAttributeSet { }

export class ImageModifier implements AttributeModifier<ImageAttribute> {

    private attributeSet: ArkImageAttributeSet = new ArkImageAttributeSet()

    get attribute(): ArkImageAttributeSet {
        return this.attributeSet;
    }

    applyNormalAttribute(instance: ImageAttribute): void { }

    applyPressedAttribute(instance: ImageAttribute): void { }

    applyFocusedAttribute(instance: ImageAttribute): void { }

    applyDisabledAttribute(instance: ImageAttribute): void { }

    applySelectedAttribute(instance: ImageAttribute): void { }
}