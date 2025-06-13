/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
import { LegacyComponent } from "@koalaui/arkoala"

declare namespace globalThis {
  function registerNamedRoute(lambda: () => any, arg1: string, arg2: any): void;
  function loadDocument(page: any): void;
}

export function arkoalaRewrite(componentRewriter: (component: LegacyComponent | undefined) => void) {
  let oldRegisterNamedRoute = globalThis.registerNamedRoute as any
  if (oldRegisterNamedRoute && !oldRegisterNamedRoute.__chained) {
    globalThis.registerNamedRoute = (lambda: () => any, ...args) => {
      let newLambda = () => {
        let page = lambda()
        let oldObserver = page.observeComponentCreation2
        page.observeComponentCreation2 = function (updater: (elemId: number, isFirst: boolean) => void, component: LegacyComponent) {
          componentRewriter(component)
          return oldObserver.call(page, (elemId: number, isFirst: boolean) => {
            console.log("updater2", elemId)
            updater(elemId, isFirst)
          }, component)
        }
        return page
      }
      let value = oldRegisterNamedRoute(newLambda, ...args)
      return value
    }
    oldRegisterNamedRoute.__chained = 1
  }
  let oldLoadDocument = globalThis.loadDocument as any
  if (oldLoadDocument && !oldLoadDocument.__chained) {
    globalThis.loadDocument = (page: any) => {
      console.log("page", page)
      if (!oldLoadDocument.__patched) {
        // To patch everything.
        componentRewriter(undefined)
        oldLoadDocument.__patched = 1
      }
      let oldObserver = page.observeComponentCreation
      page.observeComponentCreation = function (updater: (elemId: number, isFirst: boolean) => void) {
        return oldObserver.call(page, (elemId: number, isFirst: boolean) => {
          console.log("updater", elemId)
          updater(elemId, isFirst)
        })
      }
      oldLoadDocument(page)
    }
    oldLoadDocument.__chained = 1
  }
}
