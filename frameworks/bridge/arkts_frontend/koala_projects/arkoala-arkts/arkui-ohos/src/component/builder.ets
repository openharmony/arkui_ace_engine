import { int32, int64, float32 } from "@koalaui/common"
import { KInt, KPointer, KBoolean, NativeBuffer, KStringPtr, wrapCallback } from "@koalaui/interop"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { conditionScopeImpl, conditionBranchImpl } from './conditionScope'

export class WrappedBuilder<T> {
    /** @memo */
    builder: T;
    constructor(t: T) {
        this.builder = t;
    }
}

export function wrapBuilder<T>(builder: T): WrappedBuilder<T> {
    return new WrappedBuilder<T>(builder);
}

/** @memo:intrinsic */
export function ConditionScope(
    /** @memo */
    content: () => void
): void {
    conditionScopeImpl(content);
}

/** @memo:intrinsic */
export function ConditionBranch(
    /** @memo */
    content: () => void
): void {
    conditionBranchImpl(content);
}
