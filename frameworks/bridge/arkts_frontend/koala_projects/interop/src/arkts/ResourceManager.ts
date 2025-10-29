/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

import { int32 } from "@koalaui/common"

export type ResourceId = int32

interface ResourceInfo {
    resource: object
    holdersCount: int32
}

export interface Disposable {
    dispose(): void;
}

export class ResourceHolder {
    private instanceLock = new Mutex()
    private resources = new containers.ConcurrentHashMap<ResourceId, ResourceInfo>();

    private static staticLock = new Mutex()
    private static nextResourceId: ResourceId = 100 
    private static _instance: ResourceHolder = new ResourceHolder();
    private static disposables = new Array<Disposable>();
    private static disposablesSize = 0

    static instance(): ResourceHolder {
        return ResourceHolder._instance;
    }

    public hold(resourceId: ResourceId) {
        this.instanceLock.lock()
        if (!this.resources.has(resourceId)) {
            this.instanceLock.unlock()
            throw new Error(`Resource ${resourceId} does not exists, can not hold`);
        }
        this.resources.get(resourceId)!.holdersCount++;
        this.instanceLock.unlock()
    }

    public release(resourceId: ResourceId) {
        this.instanceLock.lock()
        if (!this.resources.has(resourceId)) {
            this.instanceLock.unlock()
            throw new Error(`Resource ${resourceId} does not exists, can not release`);
        }
        const resource = this.resources.get(resourceId)!;
        resource.holdersCount--;
        if (resource.holdersCount <= 0) this.resources.delete(resourceId);
        this.instanceLock.unlock()
    }

    public registerAndHold(resource: object): ResourceId {
        this.instanceLock.lock()
        const resourceId = ResourceHolder.nextResourceId++;
        this.resources.set(resourceId, {
            resource: resource,
            holdersCount: 1,
        });
        this.instanceLock.unlock()
        return resourceId;
    }

    public get(resourceId: ResourceId): object {
        this.instanceLock.lock()
        if (!this.resources.has(resourceId)) {
            this.instanceLock.unlock()
            throw new Error(`Resource ${resourceId} does not exists`);
        }
        const resource = this.resources.get(resourceId)!.resource
        this.instanceLock.unlock()
        return resource;
    }

    public has(resourceId: ResourceId): boolean {
        return this.resources.has(resourceId)
    }

    static register(resource: Disposable) {
        ResourceHolder.staticLock.lock()
        if (ResourceHolder.disposablesSize < ResourceHolder.disposables.length) {
            ResourceHolder.disposables[ResourceHolder.disposablesSize] = resource
        } else {
            ResourceHolder.disposables.push(resource)
        }
        ResourceHolder.disposablesSize++
        ResourceHolder.staticLock.unlock()
    }

    static unregister(resource: Disposable) {
        ResourceHolder.staticLock.lock()
        const index = ResourceHolder.disposables.indexOf(resource);
        if (index !== -1 && index < ResourceHolder.disposablesSize) {
            if (index !== ResourceHolder.disposablesSize - 1) {
                ResourceHolder.disposables[index] = ResourceHolder.disposables[ResourceHolder.disposablesSize - 1];
            }
            ResourceHolder.disposablesSize--;
        }
        ResourceHolder.staticLock.unlock()
    }

    static disposeAll() {
        ResourceHolder.staticLock.lock()
        for (let i = 0; i < ResourceHolder.disposablesSize; ++i) {
            ResourceHolder.disposables[i].dispose()
        }
        ResourceHolder.disposablesSize = 0
        ResourceHolder.staticLock.unlock()
    }

    static compactDisposables() {
        ResourceHolder.staticLock.lock()
        ResourceHolder.disposables = ResourceHolder.disposables.slice(0, ResourceHolder.disposablesSize);
        ResourceHolder.staticLock.unlock()
    }
}