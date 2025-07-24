/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
@Entry
@Component
struct ProgressTest {
    value: number = 33
    total: number = 999
    color: string = '#0000ff'
    backColor: string = '#808080'
    fontColor: string = '#030303'
    enableSmoothEffect: boolean = true
    enableScanEffect: boolean = true
    shadowValue: boolean = true
    status: number = 1
    strokeWidth: number = 4
    strokeRadius: number = 16
    scaleCount: number = 100
    scaleWidth: number = 2
    borderColorValue: string = '#ff0000'
    borderWidthValue: number = 6
    content: string = 'Capsule Progress Content'
    showDefaultPercentage: boolean = true
    font: Font = {size: '10fp', weight: 'Lighter', family: 'Calibri', style: FontStyle.Italic }

    ringStyle: RingStyleOptions = {strokeWidth: this.strokeWidth, shadow: this.shadowValue, status: this.status,
        enableSmoothEffect: this.enableSmoothEffect, enableScanEffect: this.enableScanEffect }
    linearStyle: LinearStyleOptions = { enableSmoothEffect: !this.enableSmoothEffect,
        enableScanEffect: !this.enableScanEffect, strokeWidth: this.strokeWidth, strokeRadius: `${this.strokeRadius}px` }
    eclipseStyle: EclipseStyleOptions = { enableSmoothEffect: this.enableSmoothEffect }
    scaleRingStyle: ScaleRingStyleOptions = { strokeWidth: this.strokeWidth, scaleWidth: this.scaleWidth,
        scaleCount: this.scaleCount, enableSmoothEffect: this.enableSmoothEffect }
    capsuleStyle: CapsuleStyleOptions = { borderColor: this.borderColorValue, borderWidth: this.borderWidthValue,
        content: this.content, font: this.font, fontColor: this.fontColor, showDefaultPercentage: this.showDefaultPercentage,
        enableSmoothEffect: this.enableSmoothEffect, enableScanEffect: this.enableScanEffect }

    build() {
        Column() {
            Progress({ value: this.value })
            Progress({ value: this.value, type: ProgressType.Ring })
            Progress({ value: this.value, type: ProgressType.Eclipse })
            Progress({ value: this.value, type: ProgressType.ScaleRing })
            Progress({ value: this.value, type: ProgressType.Capsule })
            Progress({ value: 0, total: this.total })
            .value(this.value).color(this.color).backgroundColor(this.backColor).style(this.linearStyle)
            Progress({ value: 0, type: ProgressType.Ring, total: this.total })
            .value(this.value).color(this.color).backgroundColor(this.backColor).style(this.ringStyle)
            Progress({ value: 0, type: ProgressType.Eclipse, total: this.total })
            .value(this.value).color(this.color).backgroundColor(this.backColor).style(this.eclipseStyle)
            Progress({ value: 0, type: ProgressType.ScaleRing, total: this.total })
            .value(this.value).color(this.color).backgroundColor(this.backColor).style(this.scaleRingStyle)
            Progress({ value: 0, type: ProgressType.Capsule, total: this.total })
            .value(this.value).color(this.color).backgroundColor(this.backColor).style(this.capsuleStyle)
        }
        .width('100%')
        .height('100%')
    }
}