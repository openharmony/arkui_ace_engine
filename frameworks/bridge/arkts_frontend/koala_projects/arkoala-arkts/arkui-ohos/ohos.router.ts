import { InteropNativeModule } from "@koalaui/interop/InteropNativeModule"
import { Router } from "./src/handwritten"
import { PeerNode } from "./src/PeerNode"

namespace router {
    interface RouterOptions {
        url: string
        params?: Object
    }
    
    enum RouterMode {
        Standard,
        Single
    }

    export function registerPage(page: string, className: string): void {
        pageEntries.set(page, className)
    }

    export function error(prefix: string, e: Object|null|undefined): string {
        if (e instanceof Error) {
            return `${prefix}: ${e} ${e.stack}`
        } else {
            return `${prefix}: ${e}`
        }
    }

    let pageEntries: Map<string, string>
    let globalRouterImp: Router | undefined

    export function setRouter(routerImp: Router): void {
        pageEntries = new Map<string, string>();
        InteropNativeModule._NativeLog("AceRouter:enter set router")
        globalRouterImp = routerImp
        routerImp.provideClassNameResolver((page:string) => pageEntries?.get(page))
    }

    export function getParams(): Object | undefined {
        return globalRouterImp!.getParam("arkuiOptions")
    }

    export function clear(): void {
        InteropNativeModule._NativeLog("AceRouter:enter ohos clear")
        globalRouterImp!.clear()
    }

    export function pushUrl(options: RouterOptions): void {
        InteropNativeModule._NativeLog("AceRouter:enter ohos pushUrl " + options.url)
        globalRouterImp!.push(options.url)
    }

    export function push(options: RouterOptions): void {
        InteropNativeModule._NativeLog("AceRouter:enter ohos push " + options.url)
        globalRouterImp!.push(options.url)
            .catch((e: Object|null|undefined) => InteropNativeModule._NativeLog(error(`AceRouter:Push URL ${options.url} in router failed`, e)))
    }

    export function back(options?: RouterOptions): void {
        InteropNativeModule._NativeLog("AceRouter:enter ohos back")
        globalRouterImp!.back(options?.url)
            .catch((e: Object|null|undefined) => InteropNativeModule._NativeLog(error(`AceRouter:Cannot go back in router`, e)))
    }

    export function UpdateVisiblePagePeerNode(node: PeerNode, index: number = -1): void {
        InteropNativeModule._NativeLog("AceRouter:enter ohos UpdateVisiblePagePeerNode")
        globalRouterImp!.UpdateVisiblePagePeerNode(node, index);
    }
}

export default router