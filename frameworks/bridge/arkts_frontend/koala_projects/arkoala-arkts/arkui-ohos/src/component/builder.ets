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

export function makeBuilderParameterProxy<T extends Object>(instance: T, source: Map<string, () => Any>, initializer?: (t: T) => void): T {
    const proxiedInstance = proxy.Proxy.create(instance, new BuilderLiteralProxyHandler<T>(source));
    if (initializer) {
        initializer!(proxiedInstance);
    }
    return proxiedInstance;
}

class BuilderLiteralProxyHandler<T extends Object> extends proxy.DefaultProxyHandler<T> {
    source: Map<string, () => Any>;
    constructor(source: Map<string, () => Any>) {
        this.source = source;
    }
    override get(target: T, name: string): Any {
        const propertyGetter: (() => Any) | undefined = this.source.get(name);
        if (propertyGetter) {
            return (propertyGetter as () => Any)();
        }
        return super.get(target, name);
    }
}