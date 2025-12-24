import { int32, int64, float32 } from '@koalaui/common';
import { KInt, KPointer, KBoolean, NativeBuffer, KStringPtr, wrapCallback } from '@koalaui/interop';
import { memo, memo_stable } from '@koalaui/runtime/annotations';
import { ComponentBuilder } from '@koalaui/builderLambda';
import { isDynamicObject } from './interop';
import { StateMgmtTool } from '#stateMgmtTool';

export class WrappedBuilder<T> {
    /** @memo */
    public builder: T;
    constructor(t: T) {
        this.builder = t;
    }
}

export function wrapBuilder<T>(builder: T): WrappedBuilder<T> {
    return new WrappedBuilder<T>(builder);
}

export function makeBuilderParameterProxy<T extends Object>(
    instance: T, source: Map<string, () => Any>, initializer?: (t: T) => void): T {
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
    if (initializer) {
        initializer(instance);
    }
    return instance;
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