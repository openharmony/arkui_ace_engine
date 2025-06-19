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

import { log } from "./util.test"

/** @memo */
export function zex(
    /** @memo */
    content: () => void,
) {
    log("I'm zex")
    content()
}

/** @memo */
export function til(
    arg: string,
    /** @memo */
    content: () => void,
) {
    log(`I'm til, I have an ${arg}`)
    content()
}

/** @memo */
export function qox(
    arg: string,
    /** @memo */
    content: () => void
) {
    log(`I'm qox, I have an ${arg}`)
    content()
}

/** @memo */
export function juv(
    arg: string,
    content: () => void
) {
    log(`I'm juv, I have a ${arg}`)
}


/** @memo */
export function accessId(
    arg: string,
    /** @memo */
    content: () => void,
) {
    log(`I'm accessId, I have an ${arg}`)
    content()
}

export class Zan {
    /** @memo */
    rek(msg: string) {
        log(`I'm rek the member. I have an ${msg}`)
    }

    /** @memo */
    cep(
        arg: string,
        /** @memo */
        content: () => void
    ) {
        log(`I'm cep the member. I have an ${arg}, ${this === undefined}`)
        content()
    }
}

/** @memo */
export function kla(
    arg: string,
    /** @memo */
    por: (n: string) => string,
    los: (n: string) => string,
) {
    log(por("funny") + " " + arg)
    log(los("happy") + " " + arg)
}

/** @memo */
export function ryq(arg: string, adv: string) {
    kla(
        arg,
        /** @memo */
        (s):string => s + " ui cow " + adv,
        (s):string => s + " non-ui goat " + adv
    )
}

/** @memo */
export function bae(arg: string, adv: string) {
    kla(
        arg,
        /** @memo */
        function(s): string { return s + " ui pig " + adv },
        function(s): string { return s + " non-ui horse " + adv }
    )
}
