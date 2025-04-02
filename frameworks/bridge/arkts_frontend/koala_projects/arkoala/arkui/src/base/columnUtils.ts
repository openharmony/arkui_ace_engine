/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

enum ArkUIAPIFlexAlign {
    AUTO,

    // align to the start of the axis, can be both used in MainAxisAlign and CrossAxisAlign.
    FLEX_START,

    // align to the center of the axis, can be both used in MainAxisAlign and CrossAxisAlign.
    CENTER,

    // align to the end of the axis, can be both used in MainAxisAlign and CrossAxisAlign.
    FLEX_END,

    // stretch the cross size, only used in CrossAxisAlign.
    STRETCH,

    // adjust the cross position according to the textBaseline, only used in CrossAxisAlign.
    BASELINE,

    // align the children on both ends, only used in MainAxisAlign.
    SPACE_BETWEEN,

    // align the child with equivalent space, only used in MainAxisAlign.
    SPACE_AROUND,

    // align the child with space evenly, only used in MainAxisAlign.
    SPACE_EVENLY,

    // User-defined space, only used in MainAxisAlign.
    SPACE_CUSTOMIZATION,
}

// TODO: use consistent enum between managed and C++ sides.
export function translateAlignItemsToArk(value: HorizontalAlign):number {
    switch (value) {
        case HorizontalAlign.START:
            return ArkUIAPIFlexAlign.FLEX_START
        case HorizontalAlign.CENTER:
            return ArkUIAPIFlexAlign.CENTER
        case HorizontalAlign.END:
            return ArkUIAPIFlexAlign.FLEX_END
        default:
            return ArkUIAPIFlexAlign.CENTER
    }
}