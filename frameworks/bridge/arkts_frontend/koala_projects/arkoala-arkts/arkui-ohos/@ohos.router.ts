import { InteropNativeModule } from "@koalaui/interop/InteropNativeModule"
import { Router } from "arkui/handwritten"
import { PeerNode } from "arkui/PeerNode"
import { UserViewBuilder } from "arkui/UserView"
import { ComputableState, State } from "@koalaui/runtime"
import { UIContextImpl } from "arkui/handwritten/UIContextImpl";
import { UIContextUtil } from "arkui/handwritten/UIContextUtil"

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

    export interface EnableAlertOptions {
        message: string;
    }

    export function error(prefix: string, e: Object|null|undefined): string {
        if (e instanceof Error) {
            return `${prefix}: ${e} ${e.stack}`
        } else {
            return `${prefix}: ${e}`
        }
    }

    let pageEntries: Map<string, string>

    export function setRouter(routerImp: Router): void {
        let uiContext: UIContextImpl = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        uiContext.setRouter(routerImp)
    }

    export function getParams(): Object {
        let uiContext: UIContextImpl = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        const globalRouterImp = uiContext.getRouter().getRouter();
        return globalRouterImp!.getParams()
    }

    export function clear(): void {
        let uiContext: UIContextImpl = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        const globalRouterImp = uiContext.getRouter().getRouter();
        globalRouterImp!.clear()
    }

    export function getLength(): string {
        let uiContext: UIContextImpl = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        const globalRouterImp = uiContext.getRouter().getRouter();
        return globalRouterImp!.getLength();
    }

    export function getState(): RouterState {
        let uiContext: UIContextImpl = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        const globalRouterImp = uiContext.getRouter().getRouter();
        return globalRouterImp!.getState();
    }

    export function getStateByIndex(index: number): RouterState | undefined {
        let uiContext: UIContextImpl = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        const globalRouterImp = uiContext.getRouter().getRouter();
        return globalRouterImp!.getStateByIndex(index);
    }

    export function getStateByUrl(url: string): Array<RouterState> {
        let uiContext: UIContextImpl = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        const globalRouterImp = uiContext.getRouter().getRouter();
        return globalRouterImp!.getStateByUrl(url);
    }

    export function pushUrl(options: RouterOptions): void {
        InteropNativeModule._NativeLog("AceRouter:enter ohos pushUrl " + options.url)
        let uiContext: UIContextImpl = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        const globalRouterImp = uiContext.getRouter().getRouter();
        globalRouterImp!.push(options)
    }

    export function replaceUrl(options: RouterOptions): void {
        InteropNativeModule._NativeLog("AceRouter:enter ohos replaceUrl " + options.url)
        let uiContext: UIContextImpl = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        const globalRouterImp = uiContext.getRouter().getRouter();
        globalRouterImp!.replace(options)
    }

    export function push(options: RouterOptions): void {
        InteropNativeModule._NativeLog("AceRouter:enter ohos push " + options.url)
        let uiContext: UIContextImpl = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        const globalRouterImp = uiContext.getRouter().getRouter();
        globalRouterImp!.push(options)
    }

    export function back(options?: RouterOptions): void {
        InteropNativeModule._NativeLog("AceRouter:enter ohos back")
        let uiContext: UIContextImpl = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        const globalRouterImp = uiContext.getRouter().getRouter();
        globalRouterImp!.back(options)
    }

    export function UpdateVisiblePagePeerNode(node: PeerNode, index: number = -1): void {
        InteropNativeModule._NativeLog("AceRouter:enter ohos UpdateVisiblePagePeerNode")
        let uiContext: UIContextImpl = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        const globalRouterImp = uiContext.getRouter().getRouter();
        globalRouterImp!.UpdateVisiblePagePeerNode(node, index);
    }

    export function getStateRoot(): ComputableState<PeerNode> {
        let uiContext: UIContextImpl = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        const globalRouterImp = uiContext.getRouter().getRouter();
        return globalRouterImp!.getEntryRootValue();
    }

    export function runPage(options: RouterOptions, builder: UserViewBuilder): void {
        let uiContext: UIContextImpl = UIContextUtil.getOrCreateCurrentUIContext() as UIContextImpl;
        const globalRouterImp = uiContext.getRouter().getRouter();
        globalRouterImp!.runStartPage(options, builder)
    }
}

export default router