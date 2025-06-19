/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

import { ControlSize, SizeOptions } from "@koalaui/arkts-arkui"
import { ArkButtonPeer } from "@koalaui/arkts-arkui"
import { int32, int64 } from "@koalaui/common"

function measure(name: string, repeat: int32, op: (repeat: int64) => void) {
    const start = Date.now()
    op(repeat)
    const total = Date.now() - start
    console.log(`${name}: ${total}ms, ${(total as number) / repeat * 1000000}ms per 1M`)
}

export function benchmark() {
    let peer = ArkButtonPeer.create()
    console.log(`peer ${peer}`)

    // Int+ETSNAPI: 3722ms, 372.2ms per 1M
    // Int+ETSNAPI+@ani.unsafe.Direct: 2149ms, 214.9ms per 1M
    // Int+ANI: 3904ms, 390.4ms per 1M
    // AOT+ETSNAPI: 747ms, 74.7ms per 1M
    // AOT+ANI: 1049ms, 104.9ms per 1M
    // AOT+ANI+direct: 214ms, 21.4ms per 1M
    measure("Simple number", 10000000, (repeat) => {
        for (let i = 0; i < repeat; i++) {
            peer.controlSizeAttribute(ControlSize.SMALL)
        }
    })
    // Int+ETSNAPI: 2940ms, 2940ms per 1M
    // Int+ETSNAPI+@ani.unsafe.Quick: 1144ms, 1144ms per 1M
    // Int+ANI: 2549ms, 2549ms per 1M:
    // AOT+ETSNAPI: 1791ms, 1791ms per 1M
    // AOT+ANI: 2108ms, 2108ms per 1M
    // AOT+ANI+@ani.unsafe.Quick: 1273ms, 1273ms per 1M
    measure("Union with number", 1000000, (repeat) => {
        for (let i = 0; i < repeat; i++) {
            peer.fontColorAttribute(100)
        }
    })

    // Int+ETSNAPI:5666ms, 5666ms per 1M
    // Int+ETSNAPI+@ani.unsafe.Direct:
    // Int+ANI: 5932ms, 5932ms per 1M
    // AOT+ETSNAPI: 5666ms, 5666ms per 1M
    // AOT+ANI: 5102ms, 5102ms per 1M
    // AOT+ANI+@ani.unsafe.Quick: 1916ms, 1916ms per 1M
    measure("backgroundImageSizeAttribute", 1000000, (repeat) => {
        for (let i = 0; i < repeat; i++) {
            peer.backgroundImageSizeAttribute({
                width: 100,
                height: "100px"
            } as SizeOptions)
        }
    })

}