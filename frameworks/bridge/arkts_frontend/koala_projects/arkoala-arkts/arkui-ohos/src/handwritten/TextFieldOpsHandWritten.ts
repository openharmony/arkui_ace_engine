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

import { KPointer } from "@koalaui/interop"
import { TextFieldOps, Bindable, ResourceStr, Length, LayoutPolicy, BorderRadiuses, LocalizedBorderRadiuses, EdgeStyles, BorderStyle, ResourceColor, EdgeColors, LocalizedEdgeColors, LocalizedEdgeWidths, EdgeWidths, BorderOptions, Padding, LocalizedPadding } from "../component"

export class TextFieldOpsHandWritten {
    static hookTextFieldInputValueImpl(node: KPointer, value: Bindable<ResourceStr>) {
        TextFieldOps.registerTextFieldValueCallback(node, value.value, (v) => {
            value.onChange(v)
        })
    }

    static hookTextFieldSetWidth(node: KPointer, value?: Length | LayoutPolicy) {
        TextFieldOps.textFieldOpsSetWidth(node, value)
    }

    static hookTextFieldSetHeight(node: KPointer, value?: Length | LayoutPolicy) {
        TextFieldOps.textFieldOpsSetHeight(node, value)
    }

    static hookTextFieldSetPadding(node: KPointer, value?: Padding | Length | LocalizedPadding) {
        TextFieldOps.textFieldOpsSetPadding(node, value)
    }

    static hookTextFieldSetMargin(node: KPointer, value?: Padding | Length | LocalizedPadding) {
        TextFieldOps.textFieldOpsSetMargin(node, value)
    }

    static hookTextFieldSetBorder(node: KPointer, value?: BorderOptions) {
        TextFieldOps.textFieldOpsSetBorder(node, value)
    }

    static hookTextFieldSetBorderWidth(node: KPointer, value?: Length | EdgeWidths | LocalizedEdgeWidths) {
        TextFieldOps.textFieldOpsSetBorderWidth(node, value)
    }

    static hookTextFieldSetBorderColor(node: KPointer, value?: ResourceColor | EdgeColors | LocalizedEdgeColors) {
        TextFieldOps.textFieldOpsSetBorderColor(node, value)
    }

    static hookTextFieldSetBorderStyle(node: KPointer, value?: BorderStyle | EdgeStyles) {
        TextFieldOps.textFieldOpsSetBorderStyle(node, value)
    }

    static hookTextFieldSetBorderRadius(node: KPointer, value?: Length | BorderRadiuses | LocalizedBorderRadiuses) {
        TextFieldOps.textFieldOpsSetBorderRadius(node, value)
    }

    static hookTextFieldSetBackgroundColor(node: KPointer, value?: ResourceColor) {
        TextFieldOps.textFieldOpsSetBackgroundColor(node, value)
    }
}