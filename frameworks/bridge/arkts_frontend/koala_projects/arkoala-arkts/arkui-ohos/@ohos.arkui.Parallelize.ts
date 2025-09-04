
import { int32, KoalaCallsiteKey, observableProxy } from "@koalaui/common"
import { MutableState, rememberDisposable, mutableState, __context, StateContext, memoEntry, __id, StateManager, ComputableState, remember } from "@koalaui/runtime"
import { PeerNode } from "arkui/PeerNode";
import { ArkComponentRootPeer } from 'arkui/framework'
import { ArkUIGeneratedNativeModule } from "#components"


/** @memo:stable */
export class ParallelNode {
    private __needAttach?: MutableState<boolean> = mutableState<boolean>(false);
    private status: int32 = 0; // 0: initial 1: building 2:builded 3:attached
    private manager: StateManager | undefined = undefined;
    private rootState: ComputableState<PeerNode> | undefined = undefined
    private peerNode: ArkComponentRootPeer | undefined = undefined
    private get needAttach(): boolean {
        return this.__needAttach!.value;
    }
    private set needAttach(value: boolean) {
        this.__needAttach!.value = value;
    }

    /** @memo */
    build(
        /** @memo */
        builder: () => void) {
            throw new Error("TBD")
    }

    dispose(): void {
        throw new Error("TBD")
    }
}

export interface ParallelOption {
    enable?: boolean,
    initlize?: () => void,
    completed?: () => void,
}

export interface UIParallelAttribute extends CommonMethod {
    enable?: boolean;
    updateUseParallel?: boolean;

    setParallelizeUIOptions(options?: ParallelOption): this;
}

export class ArkParallelComponent extends ArkCommonMethodComponent implements UIParallelAttribute {
    enable?: boolean = true;
    initlize?: () => void = undefined;
    completed?: () => void = undefined;
    updateUseParallel?: boolean = undefined;

    public setParallelizeUIOptions(options?: ParallelOption): this {
        this.enable = options?.enable;
        this.initlize = options?.initlize;
        this.completed = options?.completed;
        this.updateUseParallel = options?.updateUseParallel;
        return this;
    }
}

/** @memo */
export function ParallelizeUIImpl(
    /** @memo */
    style: ((attributes: UIParallelAttribute) => void) | undefined,
    /** @memo */
    content_?: () => void,
) {
    throw new Error("TBD")
}