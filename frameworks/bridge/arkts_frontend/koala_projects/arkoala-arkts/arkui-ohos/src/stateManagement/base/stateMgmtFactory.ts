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

import { IStateMgmtFactory } from '../decorator';
import {
    IStateDecoratedVariable,
    ILinkDecoratedVariable,
    IPropDecoratedVariable,
    IProvideDecoratedVariable,
    IConsumeDecoratedVariable,
    IObjectLinkDecoratedVariable,
    IStorageLinkDecoratedVariable,
    IStoragePropDecoratedVariable,
    LinkSourceType
} from '../decorator';
import { IMutableStateMeta } from '../decorator';
import { MutableStateMeta } from './mutableStateMeta';
import { ExtendableComponent } from '../../component/extendableComponent';
import { ISubscribedWatches, WatchFuncType } from '../decorator';
import { StateDecoratedVariable } from '../decoratorImpl/decoratorState';
import { PropDecoratedVariable } from '../decoratorImpl/decoratorProp';
import { ObjectLinkDecoratedVariable } from '../decoratorImpl/decoratorObjectLink'
import { TypeChecker } from '#components';
import { LinkDecoratedVariable } from '../decoratorImpl/decoratorLink';
import { ProvideDecoratedVariable } from '../decoratorImpl/decoratorProvide';
import { ConsumeDecoratedVariable } from '../decoratorImpl/decoratorConsume';
import { StoragePropDecoratedVariable } from '../decoratorImpl/decoratorStorageProp';
import { StorageLinkDecoratedVariable } from '../decoratorImpl/decoratorStorageLink';
import { StateMgmtTool } from '#stateMgmtTool';
import { SubscribedWatches } from '../decoratorImpl/decoratorWatch';

export class __StateMgmtFactoryImpl implements IStateMgmtFactory {
    public makeMutableStateMeta(): IMutableStateMeta {
        return new MutableStateMeta('');
    }
    public makeSubscribedWatches(): ISubscribedWatches {
        return new SubscribedWatches();
    }
    makeState<T>(owningView: ExtendableComponent, varName: string, initValue: T, watchFunc?: WatchFuncType): IStateDecoratedVariable<T> {
        return new StateDecoratedVariable<T>(owningView, varName, initValue, watchFunc);
    }

    makeProp<T>(owningView: ExtendableComponent, varName: string, initValue: T, watchFunc?: WatchFuncType): IPropDecoratedVariable<T> {
        return new PropDecoratedVariable<T>(owningView, varName, initValue, watchFunc);
    }

    makeLink<T>(owningView: ExtendableComponent, varName: string, source: LinkSourceType<T>, watchFunc?: WatchFuncType): ILinkDecoratedVariable<T> {
        if (StateMgmtTool.isIStateDecoratedVariable(source)) {
            return this.makeLinkOnState(owningView, varName, source as Object as IStateDecoratedVariable<T>, watchFunc);
        }
        if (StateMgmtTool.isIPropDecoratedVariable(source)) {
            return this.makeLinkOnProp(owningView, varName, source as Object as IPropDecoratedVariable<T>, watchFunc);
        }
        if (StateMgmtTool.isILinkDecoratedVariable(source)) {
            return this.makeLinkOnLink(owningView, varName, source as Object as ILinkDecoratedVariable<T>, watchFunc);
        }
        if (StateMgmtTool.isIObjectLinkDecoratedVariable(source)) {
            return this.makeLinkOnObjectLink(owningView, varName, source as Object as IObjectLinkDecoratedVariable<T>, watchFunc);
        }
        if (StateMgmtTool.isIProvideDecoratedVariable(source)) {
            return this.makeLinkOnProvide(owningView, varName, source as Object as IProvideDecoratedVariable<T>, watchFunc);
        }
        if (StateMgmtTool.isIConsumeDecoratedVariable(source)) {
            return this.makeLinkOnConsume(owningView, varName, source as Object as IConsumeDecoratedVariable<T>, watchFunc);
        }
        if (StateMgmtTool.isIStorageLinkDecoratedVariable(source)) {
            return this.makeLinkOnStorageLink(owningView, varName, source as Object as IStorageLinkDecoratedVariable<T>, watchFunc);
        }
        if (StateMgmtTool.isIStoragePropDecoratedVariable(source)) {
            return this.makeLinkOnStorageProp(owningView, varName, source as Object as IStoragePropDecoratedVariable<T>, watchFunc);
        }
        throw new Error('inValid Link source');

    }
    public makeLinkOnState<T>(owningView: ExtendableComponent, varName: string,
        source: IStateDecoratedVariable<T>, watchFunc?: WatchFuncType): ILinkDecoratedVariable<T> {
        const link = new LinkDecoratedVariable<T>(owningView, varName, () => source.get(), (newValue: T) => source.set(newValue), watchFunc);
        source.registerWatchToSource(link);
        return link;
    }

    protected makeLinkOnProp<T>(owningView: ExtendableComponent, varName: string,
        source: IPropDecoratedVariable<T>, watchFunc?: WatchFuncType): ILinkDecoratedVariable<T> {
        const link = new LinkDecoratedVariable<T>(owningView, varName, () => source.get(), (newValue: T) => source.set(newValue), watchFunc);
        source.registerWatchToSource(link);
        return link;
    }

    protected makeLinkOnLink<T>(owningView: ExtendableComponent, varName: string,
        source: ILinkDecoratedVariable<T>, watchFunc?: WatchFuncType): ILinkDecoratedVariable<T> {
        const link = new LinkDecoratedVariable<T>(owningView, varName, () => source.get(), (newValue: T) => source.set(newValue), watchFunc);
        source.registerWatchToSource(link);
        return link;
    }

    protected makeLinkOnStorageLink<T>(owningView: ExtendableComponent, varName: string,
        source: IStorageLinkDecoratedVariable<T>, watchFunc?: WatchFuncType): ILinkDecoratedVariable<T> {
        const link = new LinkDecoratedVariable<T>(owningView, varName, () => source.get(), (newValue: T) => source.set(newValue), watchFunc);
        source.registerWatchToSource(link);
        return link;
    }

    protected makeLinkOnStorageProp<T>(owningView: ExtendableComponent, varName: string,
        source: IStoragePropDecoratedVariable<T>, watchFunc?: WatchFuncType): ILinkDecoratedVariable<T> {
        const link = new LinkDecoratedVariable<T>(owningView, varName, () => source.get(), (newValue: T) => source.set(newValue), watchFunc);
        source.registerWatchToSource(link);
        return link;
    }

    protected makeLinkOnProvide<T>(owningView: ExtendableComponent, varName: string,
        source: IProvideDecoratedVariable<T>, watchFunc?: WatchFuncType): ILinkDecoratedVariable<T> {
        const link = new LinkDecoratedVariable<T>(owningView, varName, () => source.get(), (newValue: T) => source.set(newValue), watchFunc);
        source.registerWatchToSource(link);
        return link;
    }

    protected makeLinkOnConsume<T>(owningView: ExtendableComponent, varName: string,
        source: IConsumeDecoratedVariable<T>, watchFunc?: WatchFuncType): ILinkDecoratedVariable<T> {
        const link = new LinkDecoratedVariable<T>(owningView, varName, () => source.get(), (newValue: T) => source.set(newValue), watchFunc);
        source.registerWatchToSource(link);
        return link;
    }

    protected makeLinkOnObjectLink<T>(owningView: ExtendableComponent, varName: string,
        source: IObjectLinkDecoratedVariable<T>, watchFunc?: WatchFuncType): ILinkDecoratedVariable<T> {
        const link = new LinkDecoratedVariable<T>(owningView, varName, () => source.get(), (newValue: T) => {/* set do nothing */}, watchFunc);
        source.registerWatchToSource(link);
        return link;
    }

    makeObjectLink<T>(owningView: ExtendableComponent, varName: string, initValue: T, watchFunc?: WatchFuncType): IObjectLinkDecoratedVariable<T> {
        return new ObjectLinkDecoratedVariable<T>(owningView, varName, initValue, watchFunc);
    }

    makeProvide<T>(owningView: ExtendableComponent, varName: string, provideAlias: string,
        initValue: T, allowOverride: boolean, watchFunc?: WatchFuncType): IProvideDecoratedVariable<T> {
        return new ProvideDecoratedVariable<T>(owningView, varName, provideAlias, initValue, allowOverride, watchFunc);
    }

    makeConsume<T>(owningView: ExtendableComponent, varName: string, provideAlias: string,
        watchFunc?: WatchFuncType): IConsumeDecoratedVariable<T> {
        return new ConsumeDecoratedVariable<T>(owningView, varName, provideAlias, watchFunc);
    }

    makeStorageProp<T>(owningView: ExtendableComponent, propName: string, varName: string,
        initValue: T, watchFunc?: WatchFuncType): IStoragePropDecoratedVariable<T> {
        return new StoragePropDecoratedVariable<T>(owningView, propName, varName, initValue, watchFunc);
    }

    makeStorageLink<T>(owningView: ExtendableComponent, propName: string, varName: string,
        initValue: T, watchFunc?: WatchFuncType): IStorageLinkDecoratedVariable<T> {
        return new StorageLinkDecoratedVariable<T>(owningView, propName, varName, initValue, watchFunc);
    }

}