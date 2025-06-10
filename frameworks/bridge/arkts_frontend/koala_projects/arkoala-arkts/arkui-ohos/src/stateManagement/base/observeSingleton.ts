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

import { IObserve, OBSERVE } from "../decorator";
import { IObservedObject, RenderIdType } from "../decorator";
import { IBindingSource } from "./mutableStateMeta";
import { TypeChecker } from "#components";
import { StateMgmtTool } from "#stateMgmtTool";
import { NullableObject } from "./types";
import { GlobalStateManager } from "@koalaui/runtime";
import { StateMgmtConsole } from "../tools/stateMgmtDFX";

export class ObserveSingleton implements IObserve {
    public static readonly instance: ObserveSingleton = new ObserveSingleton;
    public static readonly InvalidRenderId: RenderIdType | undefined = undefined;
    public static readonly RenderingComponent: number = 0;
    public static readonly RenderingComponentV1: number = 1;
    public static readonly RenderingComponentV2: number = 2;

    public _renderingComponent: number = ObserveSingleton.RenderingComponent;

    get renderingComponent(): number {
        return this._renderingComponent;
    }
    set renderingComponent(value: number) {
        this._renderingComponent = value;
    }

    get renderingId(): RenderIdType | undefined {
        const id = GlobalStateManager.getCurrentScopeId() ?? ObserveSingleton.InvalidRenderId;
        return id;
    }
    set renderingId(value: RenderIdType | undefined) {
        this._renderingId = value;
    }
    public _renderingId: RenderIdType|undefined = ObserveSingleton.InvalidRenderId;

    private id2BindingSource = new Map<RenderIdType, Set<IBindingSource>>();

    constructor() {

    }

    public castToIObservedObject<T>(obj: T): IObservedObject | undefined {
        return (obj && typeof obj === 'object' && StateMgmtTool.isIObservedObject(obj as Object))
            ? (obj as Object as IObservedObject)
            : undefined
    }

    public setV1RenderId(value: NullableObject): void {
        if ((this.renderingComponent === ObserveSingleton.RenderingComponentV1)
            && (this.renderingId !== ObserveSingleton.InvalidRenderId)
            && value
            && (typeof (value) === 'object')) {
                if (StateMgmtTool.isIObservedObject(value as Object)) {
                    (value as Object as IObservedObject).setV1RenderId(this.renderingId!);
                } else {
                    this.trySetRenderIdOnInterface(value as object);
                }
            }
    }

    private trySetRenderIdOnInterface(obj: object): void {
        const handler = StateMgmtTool.tryGetHandler(obj);
        if (handler && StateMgmtTool.isInterfaceProxyHandler(handler)) {
            (handler as Object as IObservedObject).setV1RenderId(this.renderingId!);
        }
    }

    public isObservedInterface(value: NullableObject): boolean {
        if (value === undefined || value === null || typeof value !== "object") {
            return false;
        }
        const handler = StateMgmtTool.tryGetHandler(value as Object);
        return (handler !== undefined && StateMgmtTool.isInterfaceProxyHandler(handler));
    }

    public shouldAddRef(iObjectsRenderId: RenderIdType): boolean {
        return ((this.renderingComponent >= ObserveSingleton.RenderingComponentV2)
            || ((this.renderingComponent === ObserveSingleton.RenderingComponentV1)
            && (iObjectsRenderId === this.renderingId)));
    }

    public clearBindingById(id: RenderIdType): void {
        const bindingSources: Set<IBindingSource> | undefined = this.id2BindingSource.get(id);
        bindingSources?.forEach((binding) => {
            binding.clearBinding(id);
        });
        this.id2BindingSource.delete(id);
    }

}