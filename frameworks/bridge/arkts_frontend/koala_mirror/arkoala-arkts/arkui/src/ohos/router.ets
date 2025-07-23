/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

import { Router } from "../handwritten"

interface RouterOptions {
    url: string
    params?: Object
}

enum RouterMode {
    Standard,
    Single
}

function error(prefix: string, e: Object|null|undefined): string {
    if (e instanceof Error) {
        return `${prefix}: ${e} ${e.stack}`
    } else {
        return `${prefix}: ${e}`
    }
}

export function registerPage(page: string, className: string): void {
    OhosRouter.pageEntries.set(page, className)
}

export default class OhosRouter {
    static pageEntries: Map<string, string> = new Map<string, string>()

    static router: Router | undefined = undefined
    static setRouter(router: Router) {
        OhosRouter.router = router
        router.provideClassNameResolver((page: string) => OhosRouter.pageEntries.get(page))
    }

    static getParams(): Object | undefined {
        return OhosRouter.router!.getParam("arkuiOptions")
    }

    static clear(): void {
        OhosRouter.router!.clear()
    }

    static pushUrl(options: RouterOptions): void {
        OhosRouter.push(options)
    }

    static push(options: RouterOptions, mode?: RouterMode): void {
        OhosRouter.router!.push(options.url)
            .catch((e: Object|null|undefined) => console.log(error(`Push URL ${options.url} in router failed`, e)))
    }

    static back(options?: RouterOptions, mode?: RouterMode): void {
        OhosRouter.router!.back(options?.url)
            .catch((e: Object|null|undefined) => console.log(error(`Cannot go back in router`, e)))
    }
}
