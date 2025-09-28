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
 
package koalaui.interop

public typealias ResourceId = Int

class ResourceInfo(var resource: Any, var holdersCount: Int ) {}

public class ResourceHolder {
    private var resources: HashMap<ResourceId, ResourceInfo> = HashMap<ResourceId, ResourceInfo>()

    companion object {
        private var nextResourceId: ResourceId = 100
        private var _instance: ResourceHolder? = null
        public fun instance(): ResourceHolder {
            if (ResourceHolder._instance == null) {
                ResourceHolder._instance = ResourceHolder()
            }
            return ResourceHolder._instance!!
        }
        public fun hold(resourceId: ResourceId) {
            val resource = instance().resources.get(resourceId) 
            if (resource != null) {
                resource.holdersCount++
            } else {
                throw Exception("Resource ${resourceId} does not exists, can not hold")
            }
        }
        
        public fun release(resourceId: ResourceId) {
            val resource = instance().resources.get(resourceId) 
            if (resource != null) {
                resource.holdersCount--
                if (resource.holdersCount <= 0) {
                    instance().resources.remove(resourceId)
                }
            } else {
                throw Exception("Resource ${resourceId} does not exists, can not hold")
            }
        }
        
        public fun registerAndHold(resource: Any): ResourceId {
            val resourceId = ResourceHolder.nextResourceId++
            instance().resources.put(resourceId, ResourceInfo(resource, 1))
            return resourceId
        }
        
        public fun get(resourceId: ResourceId): Any {
            val resource = instance().resources.get(resourceId)
            if (resource != null) {
                return resource.resource
            } else {
                throw Exception("Resource ${resourceId} does not exists")
            }
        }
    }        
}
