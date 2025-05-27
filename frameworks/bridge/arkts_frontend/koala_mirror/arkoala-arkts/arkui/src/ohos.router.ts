import { Router } from "./handwritten"

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
