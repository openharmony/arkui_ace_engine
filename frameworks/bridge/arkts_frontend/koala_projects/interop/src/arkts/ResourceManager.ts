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
    private static nextResourceId: ResourceId = 100 
    private resources: Map<ResourceId, ResourceInfo> = new Map<ResourceId, ResourceInfo>()
    private static _instance: ResourceHolder|undefined = undefined
    static instance(): ResourceHolder {
        if (ResourceHolder._instance == undefined) {
            ResourceHolder._instance = new ResourceHolder()
        }
        return ResourceHolder._instance!
    }

    public hold(resourceId: ResourceId) {
        if (!this.resources.has(resourceId))
            throw new Error(`Resource ${resourceId} does not exists, can not hold`)
        this.resources.get(resourceId)!.holdersCount++
    }

    public release(resourceId: ResourceId) {
        if (!this.resources.has(resourceId))
            throw new Error(`Resource ${resourceId} does not exists, can not release`)
        const resource = this.resources.get(resourceId)!
        resource.holdersCount--
        if (resource.holdersCount <= 0)
            this.resources.delete(resourceId)
    }

    public registerAndHold(resource: object): ResourceId {
        const resourceId = ResourceHolder.nextResourceId++
        this.resources.set(resourceId, {
            resource: resource,
            holdersCount: 1,
        })
        return resourceId
    }

    public get(resourceId: ResourceId): object {
        if (!this.resources.has(resourceId))
            throw new Error(`Resource ${resourceId} does not exists`)
        return this.resources.get(resourceId)!.resource
    }

    public has(resourceId: ResourceId): boolean {
        return this.resources.has(resourceId)
    }
}
