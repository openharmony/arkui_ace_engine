import { Router } from "./handwritten"

export function registerArkuiEntry(
    /** @memo */
    content: () => void,
    page: string
) {
    console.log("TODO: register route: ", page)
}

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

export default class OhosRouter {
    static router: Router | undefined = undefined
    static setRouter(router: Router, ) {
        OhosRouter.router = router
    }

    static getParams(): Object {
        throw new Error(`TODO SHOPPING: @ohos.router getParams`)
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
