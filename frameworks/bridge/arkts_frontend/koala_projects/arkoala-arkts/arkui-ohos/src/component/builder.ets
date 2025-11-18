import { int32, int64, float32 } from "@koalaui/common"
import { KInt, KPointer, KBoolean, NativeBuffer, KStringPtr, wrapCallback } from "@koalaui/interop"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { conditionScopeImpl, conditionBranchImpl } from './conditionScope'
import { isDynamicObject } from "./interop"
import { StateMgmtTool } from '#stateMgmtTool';

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
    if (isDynamicObject(instance)) {
        const makeBuilderParameterProxy = ESValue.getGlobal().getProperty('makeBuilderParameterProxy');
        const proxy = makeBuilderParameterProxy.invoke(ESValue.wrap('interopBuilderProxy'), ESValue.wrap(source)).unwrap() as T;
        return proxy;
    }
    if (StateMgmtTool.isObjectLiteral(instance)) {
        const ifaces: FixedArray<Class> = Class.of(instance).getInterfaces();
        const linker = Class.current().getLinker();
        return reflect.Proxy.create(linker, ifaces, new BuilderLiteralInterfaceProxyHandler(instance, source)) as T;
    }
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

class BuilderLiteralInterfaceProxyHandler implements reflect.InvocationHandler {
    private _target: Object;
    private source: Map<string, () => Any>;
    constructor(target: Object, source: Map<string, () => Any>) {
        this._target = target;
        this.source = source;
    }
    get(target: Object, method: reflect.InstanceMethod): Any {
        const name = method.getName().substring(5);
        const propertyGetter: (() => Any) | undefined = this.source.get(name);
        if (propertyGetter) {
            return (propertyGetter as () => Any)();
        }
        return method.invoke(this._target);
    }
    set(target: Object, method: reflect.InstanceMethod, newValue: Any): void {
        method.invoke(this._target, [newValue]);
    }
    invoke(target: Object, method: reflect.InstanceMethod, args: FixedArray<Any>): Any {
        return method.invoke(this._target, args);
    }
}