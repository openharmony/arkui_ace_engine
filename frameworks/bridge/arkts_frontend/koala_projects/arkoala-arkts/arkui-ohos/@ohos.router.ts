import { InteropNativeModule } from "@koalaui/interop/InteropNativeModule"
import { Router } from "arkui/handwritten"
import { PeerNode } from "arkui/PeerNode"
import { UserViewBuilder } from "arkui/UserView"
import { ComputableState } from "@koalaui/runtime"

namespace router {
    export interface RouterOptions {
        url: string
        params?: Object
    }
    
    export enum RouterMode {
        Standard,
        Single
    }

    export interface RouterState {
        index: number;
        name: string;
        path: string;
        params: Object;
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
        globalRouterImp = routerImp
    }

    export function getParams(): Object {
        return globalRouterImp!.getParams()
    }

    export function clear(): void {
        globalRouterImp!.clear()
    }

    export function getLength(): string {
        return globalRouterImp!.getLength();
    }

    export function getState(): RouterState {
        return globalRouterImp!.getState();
    }

    export function getStateByIndex(index: number): RouterState | undefined {
        return globalRouterImp!.getStateByIndex(index);
    }

    export function getStateByUrl(url: string): Array<RouterState> {
        return globalRouterImp!.getStateByUrl(url);
    }

    export function pushUrl(options: RouterOptions): void {
        InteropNativeModule._NativeLog("AceRouter:enter ohos pushUrl " + options.url)
        globalRouterImp!.push(options)
    }

    export function replaceUrl(options: RouterOptions): void {
        InteropNativeModule._NativeLog("AceRouter:enter ohos replaceUrl " + options.url)
        globalRouterImp!.replace(options)
    }

    export function push(options: RouterOptions): void {
        InteropNativeModule._NativeLog("AceRouter:enter ohos push " + options.url)
        globalRouterImp!.push(options)
    }

    export function back(options?: RouterOptions): void {
        InteropNativeModule._NativeLog("AceRouter:enter ohos back")
        globalRouterImp!.back(options)
    }

    export function UpdateVisiblePagePeerNode(node: PeerNode, index: number = -1): void {
        InteropNativeModule._NativeLog("AceRouter:enter ohos UpdateVisiblePagePeerNode")
        globalRouterImp!.UpdateVisiblePagePeerNode(node, index);
    }

    export function getStateRoot(): Array<ComputableState<PeerNode>> {
        return globalRouterImp!.getEntryRootValue();
    }

    export function runPage(options: RouterOptions, builder: UserViewBuilder): void {
        globalRouterImp!.runPage(options, builder)
    }
}

export default router