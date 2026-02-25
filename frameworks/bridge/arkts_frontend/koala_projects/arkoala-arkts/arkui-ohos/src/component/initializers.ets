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
import { ColorSpace, GestureEvent, GestureRecognizer, EventTarget, SourceType, SourceTool } from '#generated'
import { GestureActionPhase } from '@ohos.arkui.UIContext'

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
            export namespace InnerGestureTriggerInfoNS {
                export const event: GestureEvent = {
                    repeat: false,
                    fingerList: [],
                    offsetX: 0.0,
                    offsetY: 0.0,
                    angle: 0.0,
                    speed: 0.0,
                    scale: 0.0,
                    pinchCenterX: 0.0,
                    pinchCenterY: 0.0,
                    velocityX: 0.0,
                    velocityY: 0.0,
                    velocity: 0.0,
                    timestamp: 0,
                    tiltX: 0.0,
                    tiltY: 0.0,
                    pressure: 0.0,
                    source: SourceType.Unknown,
                    sourceTool: SourceTool.Unknown,
                    target: { area: { width: 0, height: 0, position: {}, globalPosition: {} } }
                }
                export const current: GestureRecognizer = {}
                export const currentPhase: GestureActionPhase = GestureActionPhase.fromValue(0)
            }
            export namespace InnerGestureObserverConfigsNS {
                export const actionPhases: Array<GestureActionPhase> = []
            }
            export namespace LengthMetricsCustomNS {
                export const unit = 0
                export const value = 0
            }
            export namespace ColorMetricsExtNS {
                export const red = 0
                export const green = 0
                export const blue = 0
                export const alpha = 0
                export const colorSpace = ColorSpace.SRGB
                export const resourceId = -1
            }
        }
        export namespace waterFlow {
            export namespace SectionOptionsNS {
                export const itemsCount = 0
            }
        }
    }
}