/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

class ViewInterop extends PUV2ViewBase implements IView {
    constructor(
        findProvidePU__: (providedPropName: string) => ObservedPropertyAbstractPU<any> | undefined,
        findProvideV2: () => any,
        findLocalStorageInterop: () => Object
    ) {
        super(undefined);
        this.findProvidePU__ = findProvidePU__;
        this.findProvideV2 = findProvideV2;
        this.findLocalStorageInterop = findLocalStorageInterop;
    }
    purgeDeleteElmtId(rmElmtId: number): boolean {
        throw new Error('Method not implemented.');
    }
    initialRenderView(): void {
        throw new Error('Method not implemented.');
    }
    uiNodeNeedUpdateV2(elmtId: number): void {
        throw new Error('Method not implemented.');
    }
    debugInfoDirtDescendantElementIdsInternal(
        depth: number,
        recursive: boolean,
        counter: ProfileRecursionCounter
    ): string {
        throw new Error('Method not implemented.');
    }
    aboutToBeDeleted(): void {
        throw new Error('Method not implemented.');
    }
    protected debugInfoStateVars(): string {
        throw new Error('Method not implemented.');
    }
    protected purgeVariableDependenciesOnElmtId(removedElmtId: number): void {
        throw new Error('Method not implemented.');
    }
    protected initialRender(): void {
        throw new Error('Method not implemented.');
    }
    protected rerender(): void {
        throw new Error('Method not implemented.');
    }
    protected get isViewV2(): boolean {
        throw new Error('Method not implemented.');
    }
    public updateRecycleElmtId(oldElmtId: number, newElmtId: number): void {
        throw new Error('Method not implemented.');
    }
    public updateStateVars(params: Object): void {
        throw new Error('Method not implemented.');
    }
    public UpdateElement(elmtId: number): void {
        throw new Error('Method not implemented.');
    }
    public __mkRepeatAPI: <I>(arr: Array<I>) => RepeatAPI<I> = <I>(arr: Array<I>): RepeatAPI<I> => {
        throw new Error('Method not implemented.');
    };
    public get localStorage_(): LocalStorage {
        return (
            (this.findLocalStorageInterop() as LocalStorage) ??
            new LocalStorage({
                /* empty */
            })
        );
    }
    public __getPathValueFromJson__Internal(propertyName: string, jsonPath: string): string | undefined {
        throw new Error('Method not implemented.');
    }
    public findProvidePU__: (providedPropName: string) => ObservedPropertyAbstractPU<Object> | undefined;
    public findProvideV2: (providedPropName: string) => [ViewV2, string] | undefined;
    public findLocalStorageInterop: () => Object;
}

function makeInteropAliasKey(name: string): string {
    return `__interop_proxy_${name}`;
}

function findProviderForInterop(checkView: IView, aliasName: string): [ViewV2, string] | undefined {
    const searchingPrefixedAliasName = `${ProviderConsumerUtilV2.ALIAS_PREFIX}_@Provider_${aliasName}`; // ProviderConsumerUtilV2.metaAliasKey(aliasName, '@Provider')
    stateMgmtConsole.debug(
        `findProviderInterop: Try to connect ${checkView.debugInfo__()} '@Consumer ${aliasName}' to @Provider counterpart....`
    );
    while (checkView) {
        const meta = checkView.constructor?.prototype[ObserveV2.V2_DECO_META];
        if (checkView instanceof ViewV2 && meta && meta[searchingPrefixedAliasName]) {
            const aliasMeta = meta[searchingPrefixedAliasName];
            const providedVarName: string | undefined =
                aliasMeta && aliasMeta.deco === '@Provider' ? aliasMeta.varName : undefined;

            if (providedVarName) {
                stateMgmtConsole.debug(
                    `findProvider: success: ${checkView.debugInfo__()} has matching @Provider('${aliasName}') ${providedVarName}`
                );
                return [checkView, providedVarName];
            }
        }
        if (checkView instanceof ViewInterop) {
            return checkView.findProvideV2(aliasName);
        }
        checkView = checkView.getParent();
    } // while
    stateMgmtConsole.warn(
        `findProvider: ${checkView.debugInfo__()} @Consumer('${aliasName}'), no matching @Provider found amongst ancestor @ComponentV2's!`
    );
    return undefined;
}

function findDynamicProvider(
    dynamicComponent: ViewV2,
    providerName: string,
    createStaticProvider: <T>(value: T, viewV2: Object) => Object
): Object | undefined {
    const providerInfo = findProviderForInterop(dynamicComponent, providerName);
    if (providerInfo === undefined) {
        return undefined;
    }
    const viewV2 = providerInfo[0]; // assume varName is the same?
    const interopAliasKey = makeInteropAliasKey(providerName);
    if (viewV2[interopAliasKey] === undefined) {
        Object.getPrototypeOf(viewV2)[interopAliasKey] = createStaticProvider(viewV2[providerName], viewV2); // need register
    }
    return viewV2[interopAliasKey];
}

class DummyViewV2 {}

function createDummyViewV2<T>(staticProvider: Object, propertyKey: string, value: T): Object {
    const result = new DummyViewV2();
    result[propertyKey] = value;
    result[makeInteropAliasKey(propertyKey)] = staticProvider;
    trackInternalInterop(result, propertyKey);
    return result;
}

const trackInternalInterop = (
    target: any, // ViewV2
    propertyKey: string // ProviderName
): void => {
    if (typeof target === 'function' && !Reflect.has(target, propertyKey)) {
        // dynamic track，and it not a static attribute
        target = target.prototype;
    }
    const storeProp = ObserveV2.OB_PREFIX + propertyKey;
    target[storeProp] = target[propertyKey];
    const interopProp = makeInteropAliasKey(propertyKey);
    Reflect.defineProperty(target, propertyKey, {
        get() {
            ObserveV2.getObserve().addRef(this, propertyKey);
            return ObserveV2.autoProxyObject(this, ObserveV2.OB_PREFIX + propertyKey);
        },
        set(val) {
            // If the object has not been observed, you can directly assign a value to it. This improves performance.
            if (val !== this[storeProp]) {
                this[storeProp] = val;
                if (interopProp in target) {
                    const interopKey = target[interopProp];
                    (interopKey as any).set(val);
                }
                // the bindings <*, target, propertyKey> might not have been recorded yet (!)
                // fireChange will run idleTasks to record pending bindings, if any
                ObserveV2.getObserve().fireChange(this, propertyKey);
            }
        },
        enumerable: true,
    });
    // this marks the proto as having at least one @Trace property inside
    // used by IsObservedObjectV2
    target[ObserveV2.V2_DECO_META] ??= {};
}; // trackInternalInterop

function createViewInterop(
    findProvidePU: (providedPropName: string) => ObservedPropertyAbstractPU<Object> | undefined,
    findProvideV2: () => [ViewV2, string] | undefined,
    findLocalStorageInterop: () => Object
): ViewInterop {
    return new ViewInterop(findProvidePU, findProvideV2, findLocalStorageInterop);
}

function createLocalStorage(staticLocalStorage: Object): LocalStorage {
    const result = new LocalStorage();
    result.setProxy(staticLocalStorage);
    return result;
}
