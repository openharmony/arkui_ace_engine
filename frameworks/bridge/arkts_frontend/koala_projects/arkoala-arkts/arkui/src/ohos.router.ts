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

export default class OhosRouter {
    static back(options?: RouterOptions, mode?: RouterMode): void {
        console.log(`TODO SHOPPING: @ohos.router back`)
    }

    static getParams(): Object {
        throw new Error(`TODO SHOPPING: @ohos.router getParams`)
    }

    static pushUrl(options: RouterOptions, mode?: RouterMode): Promise<void> {
        throw new Error(`TODO SHOPPING: @ohos.router pushUrl`)
    }
}
