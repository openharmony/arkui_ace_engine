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

import { RectResult, TouchTestStrategy } from "./common"

export namespace initializers {
    export namespace arkui.component {
        export namespace common {
            export namespace TouchTestInfoNS {
                export const windowX = 0.0
                export const windowY = 0.0
                export const parentX = 0.0
                export const parentY = 0.0
                export const x = 0.0
                export const y = 0.0
                export const rect: RectResult = { x: 0, y: 0, width: 0, height: 0 }
                export const id = ""
            }
            export namespace TouchResultNS {
                export const strategy = TouchTestStrategy.DEFAULT
            }
        }
        export namespace idlize {
            export namespace LengthMetricsCustomNS {
                export const unit = 0
                export const value = 0
            }
        }
        export namespace waterFlow {
            export namespace SectionOptionsNS {
                export const itemsCount = 0
            }
        }
    }
}