/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { ILocalStoragePropRefDecoratedVariable, IPropRefDecoratedVariable, IStateMgmtFactory } from '../decorator';
import {
    IStateDecoratedVariable,
    ILinkDecoratedVariable,
    IPropDecoratedVariable,
    IProvideDecoratedVariable,
    IConsumeDecoratedVariable,
    IObjectLinkDecoratedVariable,
    IStorageLinkDecoratedVariable,
    IStoragePropRefDecoratedVariable,
    ILocalStorageLinkDecoratedVariable,
    LinkSourceType,
    IMonitorPathInfo,
    IMonitor,
    IMonitorDecoratedVariable,
    IComputedDecoratedVariable
} from '../decorator';
import { IMutableStateMeta } from '../decorator';
import { MutableStateMeta } from './mutableStateMeta';
import { ExtendableComponent } from '../../component/extendableComponent';
import { ISubscribedWatches, WatchFuncType } from '../decorator';
import { StateDecoratedVariable } from '../decoratorImpl/decoratorState';
import { PropDecoratedVariable } from '../decoratorImpl/decoratorProp';
import { ObjectLinkDecoratedVariable } from '../decoratorImpl/decoratorObjectLink';
import { LinkDecoratedVariable } from '../decoratorImpl/decoratorLink';
import { ProvideDecoratedVariable } from '../decoratorImpl/decoratorProvide';
import { ConsumeDecoratedVariable } from '../decoratorImpl/decoratorConsume';
import { StateMgmtTool } from '#stateMgmtTool';
import { SubscribedWatches } from '../decoratorImpl/decoratorWatch';
import { UIUtils } from '../utils';
import { AppStorage } from '../storage/appStorage';
import { PropRefDecoratedVariable } from '../decoratorImpl/decoratorPropRef';
import { StoragePropRefDecoratedVariable } from '../decoratorImpl/decoratorStoragePropRef';
import { ComputedDecoratedVariable } from '../decoratorImpl/decoratorComputed';
import { MonitorFunctionDecorator } from '../decoratorImpl/decoratorMonitor';

export class __StateMgmtFactoryImpl implements IStateMgmtFactory {
    public makeMutableStateMeta(): IMutableStateMeta {
        return new MutableStateMeta('');
    }
    public makeSubscribedWatches(): ISubscribedWatches {
        return new SubscribedWatches();
    }
    makeState<T>(
        owningView: ExtendableComponent,
        varName: string,
        initValue: T,
        watchFunc?: WatchFuncType
    ): IStateDecoratedVariable<T> {
        return new StateDecoratedVariable<T>(owningView, varName, UIUtils.makeObserved(initValue) as T, watchFunc);
    }

    makeProp<T>(
        owningView: ExtendableComponent,
        varName: string,
        initValue: T,
        watchFunc?: WatchFuncType
    ): IPropDecoratedVariable<T> {
        return new PropDecoratedVariable<T>(owningView, varName, UIUtils.makeObserved(initValue) as T, watchFunc);
    }

    makePropRef<T>(
        owningView: ExtendableComponent,
        varName: string,
        initValue: T,
        watchFunc?: WatchFuncType
    ): IPropRefDecoratedVariable<T> {
        return new PropRefDecoratedVariable<T>(owningView, varName, UIUtils.makeObserved(initValue) as T, watchFunc);
    }

    makeLink<T>(
        owningView: ExtendableComponent,
        varName: string,
        source: LinkSourceType<T>,
        watchFunc?: WatchFuncType
    ): ILinkDecoratedVariable<T> {
        if (StateMgmtTool.isIStateDecoratedVariable(source)) {
            return this.makeLinkOnState(
                owningView,
                varName,
                source as Object as IStateDecoratedVariable<T>,
                watchFunc
            ) as ILinkDecoratedVariable<T>;
        }
        if (StateMgmtTool.isIPropDecoratedVariable(source)) {
            return this.makeLinkOnProp(
                owningView,
                varName,
                source as Object as IPropDecoratedVariable<T>,
                watchFunc
            ) as ILinkDecoratedVariable<T>;
        }
        if (source instanceof IPropRefDecoratedVariable) {
            return this.makeLinkOnPropRef(
                owningView,
                varName,
                source as Object as IPropRefDecoratedVariable<T>,
                watchFunc
            ) as ILinkDecoratedVariable<T>;
        }
        if (StateMgmtTool.isILinkDecoratedVariable(source)) {
            return this.makeLinkOnLink(
                owningView,
                varName,
                source as Object as ILinkDecoratedVariable<T>,
                watchFunc
            ) as ILinkDecoratedVariable<T>;
        }
        if (StateMgmtTool.isIObjectLinkDecoratedVariable(source)) {
            return this.makeLinkOnObjectLink(
                owningView,
                varName,
                source as Object as IObjectLinkDecoratedVariable<T>,
                watchFunc
            ) as ILinkDecoratedVariable<T>;
        }
        if (StateMgmtTool.isIProvideDecoratedVariable(source)) {
            return this.makeLinkOnProvide(
                owningView,
                varName,
                source as Object as IProvideDecoratedVariable<T>,
                watchFunc
            ) as ILinkDecoratedVariable<T>;
        }
        if (StateMgmtTool.isIConsumeDecoratedVariable(source)) {
            return this.makeLinkOnConsume(
                owningView,
                varName,
                source as Object as IConsumeDecoratedVariable<T>,
                watchFunc
            ) as ILinkDecoratedVariable<T>;
        }
        if (StateMgmtTool.isIStorageLinkDecoratedVariable(source)) {
            return this.makeLinkOnStorageLink(
                owningView,
                varName,
                source as Object as IStorageLinkDecoratedVariable<T>,
                watchFunc
            ) as ILinkDecoratedVariable<T>;
        }
        if (StateMgmtTool.isILocalStorageLinkDecoratedVariable(source)) {
            return this.makeLinkOnLocalStorageLink(
                owningView,
                varName,
                source as Object as ILocalStorageLinkDecoratedVariable<T>,
                watchFunc
            ) as ILinkDecoratedVariable<T>;
        }
        if (StateMgmtTool.isIStoragePropRefDecoratedVariable(source)) {
            return this.makeLinkOnStoragePropRef(
                owningView,
                varName,
                source as Object as IStoragePropRefDecoratedVariable<T>,
                watchFunc
            ) as ILinkDecoratedVariable<T>;
        }
        if (source instanceof ILocalStoragePropRefDecoratedVariable) {
            return this.makeLinkOnLocalStoragePropRef(
                owningView,
                varName,
                source as Object as ILocalStoragePropRefDecoratedVariable<T>,
                watchFunc
            ) as ILinkDecoratedVariable<T>;
        }
        throw new Error('inValid Link source');
    }
    public makeLinkOnState<T>(
        owningView: ExtendableComponent,
        varName: string,
        source: IStateDecoratedVariable<T>,
        watchFunc?: WatchFuncType
    ): ILinkDecoratedVariable<T> {
        const link = new LinkDecoratedVariable<T>(
            owningView,
            varName,
            source,
            () => source.get(),
            (newValue: T) => source.set(newValue),
            watchFunc
        );
        source.registerWatchToSource(link);
        return link;
    }

    protected makeLinkOnProp<T>(
        owningView: ExtendableComponent,
        varName: string,
        source: IPropDecoratedVariable<T>,
        watchFunc?: WatchFuncType
    ): ILinkDecoratedVariable<T> {
        const link = new LinkDecoratedVariable<T>(
            owningView,
            varName,
            source,
            () => source.get(),
            (newValue: T) => source.set(newValue),
            watchFunc
        );
        source.registerWatchToSource(link);
        return link;
    }

    protected makeLinkOnPropRef<T>(
        owningView: ExtendableComponent,
        varName: string,
        source: IPropRefDecoratedVariable<T>,
        watchFunc?: WatchFuncType
    ): ILinkDecoratedVariable<T> {
        const link = new LinkDecoratedVariable<T>(
            owningView,
            varName,
            source,
            () => source.get(),
            (newValue: T) => source.set(newValue),
            watchFunc
        );
        source.registerWatchToSource(link);
        return link;
    }

    protected makeLinkOnLink<T>(
        owningView: ExtendableComponent,
        varName: string,
        source: ILinkDecoratedVariable<T>,
        watchFunc?: WatchFuncType
    ): ILinkDecoratedVariable<T> {
        const link = new LinkDecoratedVariable<T>(
            owningView,
            varName,
            source,
            () => source.get(),
            (newValue: T) => source.set(newValue),
            watchFunc
        );
        source.registerWatchToSource(link);
        return link;
    }

    protected makeLinkOnStorageLink<T>(
        owningView: ExtendableComponent,
        varName: string,
        source: IStorageLinkDecoratedVariable<T>,
        watchFunc?: WatchFuncType
    ): ILinkDecoratedVariable<T> {
        const link = new LinkDecoratedVariable<T>(
            owningView,
            varName,
            source,
            () => source.get(),
            (newValue: T) => source.set(newValue),
            watchFunc
        );
        source.registerWatchToSource(link);
        return link;
    }

    protected makeLinkOnLocalStorageLink<T>(
        owningView: ExtendableComponent,
        varName: string,
        source: ILocalStorageLinkDecoratedVariable<T>,
        watchFunc?: WatchFuncType
    ): ILinkDecoratedVariable<T> {
        const link = new LinkDecoratedVariable<T>(
            owningView,
            varName,
            source,
            () => source.get(),
            (newValue: T) => source.set(newValue),
            watchFunc
        );
        source.registerWatchToSource(link);
        return link;
    }

    protected makeLinkOnStoragePropRef<T>(
        owningView: ExtendableComponent,
        varName: string,
        source: IStoragePropRefDecoratedVariable<T>,
        watchFunc?: WatchFuncType
    ): ILinkDecoratedVariable<T> {
        const link = new LinkDecoratedVariable<T>(
            owningView,
            varName,
            source,
            () => source.get(),
            (newValue: T) => source.set(newValue),
            watchFunc
        );
        source.registerWatchToSource(link);
        return link;
    }

    protected makeLinkOnLocalStoragePropRef<T>(
        owningView: ExtendableComponent,
        varName: string,
        source: ILocalStoragePropRefDecoratedVariable<T>,
        watchFunc?: WatchFuncType
    ): ILinkDecoratedVariable<T> {
        const link = new LinkDecoratedVariable<T>(
            owningView,
            varName,
            source,
            () => source.get(),
            (newValue: T) => source.set(newValue),
            watchFunc
        );
        source.registerWatchToSource(link);
        return link;
    }

    protected makeLinkOnProvide<T>(
        owningView: ExtendableComponent,
        varName: string,
        source: IProvideDecoratedVariable<T>,
        watchFunc?: WatchFuncType
    ): ILinkDecoratedVariable<T> {
        const link = new LinkDecoratedVariable<T>(
            owningView,
            varName,
            source,
            () => source.get(),
            (newValue: T) => source.set(newValue),
            watchFunc
        );
        source.registerWatchToSource(link);
        return link;
    }

    protected makeLinkOnConsume<T>(
        owningView: ExtendableComponent,
        varName: string,
        source: IConsumeDecoratedVariable<T>,
        watchFunc?: WatchFuncType
    ): ILinkDecoratedVariable<T> {
        const link = new LinkDecoratedVariable<T>(
            owningView,
            varName,
            source,
            () => source.get(),
            (newValue: T) => source.set(newValue),
            watchFunc
        );
        source.registerWatchToSource(link);
        return link;
    }

    protected makeLinkOnObjectLink<T>(
        owningView: ExtendableComponent,
        varName: string,
        source: IObjectLinkDecoratedVariable<T>,
        watchFunc?: WatchFuncType
    ): ILinkDecoratedVariable<T> {
        const link = new LinkDecoratedVariable<T>(
            owningView,
            varName,
            source,
            () => source.get(),
            (newValue: T) => {
                /* set do nothing */
            },
            watchFunc
        );
        source.registerWatchToSource(link);
        return link;
    }

    makeObjectLink<T>(
        owningView: ExtendableComponent,
        varName: string,
        initValue: T,
        watchFunc?: WatchFuncType
    ): IObjectLinkDecoratedVariable<T> {
        return new ObjectLinkDecoratedVariable<T>(owningView, varName, UIUtils.makeObserved(initValue) as T, watchFunc);
    }

    makeProvide<T>(
        owningView: ExtendableComponent,
        varName: string,
        provideAlias: string,
        initValue: T,
        allowOverride: boolean,
        watchFunc?: WatchFuncType
    ): IProvideDecoratedVariable<T> {
        return new ProvideDecoratedVariable<T>(
            owningView,
            varName,
            provideAlias,
            UIUtils.makeObserved(initValue) as T,
            allowOverride,
            watchFunc
        );
    }

    makeConsume<T>(
        owningView: ExtendableComponent,
        varName: string,
        provideAlias: string,
        watchFunc?: WatchFuncType
    ): IConsumeDecoratedVariable<T> {
        return new ConsumeDecoratedVariable<T>(owningView, varName, provideAlias, watchFunc);
    }

    makeStorageLink<T>(
        owningView: ExtendableComponent,
        propertyNameInAppStorage: string,
        varName: string,
        defaultValue: T,
        ttype: Type,
        watchFunc?: WatchFuncType
    ): IStorageLinkDecoratedVariable<T> {
        const result: IStorageLinkDecoratedVariable<T> | undefined = AppStorage.__makeStorageLink<T>(
            owningView,
            propertyNameInAppStorage,
            varName,
            UIUtils.makeObserved(defaultValue) as T,
            ttype,
            watchFunc
        );
        if (result === undefined) {
            throw new TypeError(`@LocalStorageLink('${propertyNameInAppStorage}') ${varName}
                configured Type ${ttype.toString()} does not match property type in storage`);
            // error of unutilized variable can not be recovered, must throw.
        }
        return result;
    }

    makeLocalStorageLink<T>(
        owningView: ExtendableComponent,
        propertyNameInAppStorage: string,
        varName: string,
        defaultValue: T,
        ttype: Type,
        watchFunc?: WatchFuncType
    ): ILocalStorageLinkDecoratedVariable<T> {
        const result: ILocalStorageLinkDecoratedVariable<T> | undefined = undefined/*TODO:SAM owningView.localStorage_.__makeStorageLink<T>(
            owningView,
            propertyNameInAppStorage,
            varName,
            UIUtils.makeObserved(defaultValue) as T,
            ttype,
            watchFunc
        );*/
        if (result === undefined) {
            throw new TypeError(`@StorageLink('${propertyNameInAppStorage}') ${varName}
                configured Type ${ttype.toString()} does not match property type in storage`);
            // error of unutilized variable can not be recovered, must throw.
        }
        return result;
    }

    makeStoragePropRef<T>(
        owningView: ExtendableComponent,
        propName: string,
        varName: string,
        initValue: T,
        ttype: Type,
        watchFunc?: WatchFuncType
    ): IStoragePropRefDecoratedVariable<T> {
        const ref = AppStorage.setAndRef<T>(propName, UIUtils.makeObserved(initValue), ttype);
        if (ref === undefined) {
            throw new TypeError(
                `@StoragePropRef('${propName}') ${varName} configured Type ${ttype.toString()} does not match property type in storage`
            );
        }
        return new StoragePropRefDecoratedVariable<T>(
            owningView,
            ref,
            propName,
            varName,
            watchFunc
        ) as IStoragePropRefDecoratedVariable<T>;
    }

    makeLocalStoragePropRef<T>(
        owningView: ExtendableComponent,
        propName: string,
        varName: string,
        initValue: T,
        ttype: Type,
        watchFunc?: WatchFuncType
    ): ILocalStoragePropRefDecoratedVariable<T> {
        const ref = undefined//TODO:SAM owningView.localStorage_.setAndRef<T>(propName, UIUtils.makeObserved(initValue), ttype);
        if (ref === undefined) {
            throw new TypeError(
                `@LocalStoragePropRef('${propName}') ${varName} configured Type ${ttype.toString()} does not match property type in storage`
            );
        }
        return new StoragePropRefDecoratedVariable<T>(
            owningView,
            ref,
            propName,
            varName,
            watchFunc
        ) as ILocalStoragePropRefDecoratedVariable<T>;
    }

    makeComputed<T>(computeFunction: () => T, varName: string): IComputedDecoratedVariable<T> {
        return new ComputedDecoratedVariable<T>(computeFunction, varName);
    }

    makeMonitor(pathLambda: Array<IMonitorPathInfo>, monitorFunction: (m: IMonitor) => void): IMonitorDecoratedVariable {
        return new MonitorFunctionDecorator(pathLambda, monitorFunction);
    }
}
