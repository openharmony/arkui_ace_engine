/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import resmgr from '@ohos.resourceManager'

export default class GlobalThis
{
  static getInstance(): GlobalThis
  {
    return GlobalThis.instance
  }static instance: GlobalThis = new GlobalThis()

  getResourceManager(): resmgr.ResourceManager
  {
    return this.resourceManager!
  }resourceManager: resmgr.ResourceManager | undefined = undefined

  touch0Id: number = -1 // camera move touch id
  touch0StorePos: Position = {x: 0, y: 0}
  touch1Id: number = -1 // camera
  touch1StorePos: Position = {x: 0, y: 0}

  touches: Map<number, Position> = new Map<number, Position>()
}
