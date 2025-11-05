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


function __makeBuilderParameterStaticProxy_Interop_Internal(name: string, value: Object, sourceGetter: Object) : Object {
  if (InteropExtractorModule.makeBuilderParameterStaticProxy === undefined) {
      throw new Error('makeBuilderParameterStaticProxy error!');
  }
  return InteropExtractorModule.makeBuilderParameterStaticProxy(name, value, sourceGetter);
}

function startStaticHook(source: Object, addRef: () => void): Object | undefined {
  if ('__static_interop_hook' in source) {
    source['__static_interop_hook'] = addRef;
    return source;
  }
  return undefined;
}

/**
* 
* @param staticBuilder ArkTS1.2builder, return the pointer of PeerNode
* @returns  Creates a dynamic builder function that wraps a static builder
*/
function createDynamicBuilder(
  staticBuilder: (...args: any[]) => number
): (...args: any[]) => void {
  let func = function (...args: any[]): void {
      this.observeComponentCreation2((elmtId: number, isInitialRender: boolean) => {
          ObserveV2.getObserve().__interopInStaticRendering_internal_ = true;
          if (isInitialRender) {
              let pointer = staticBuilder(...args);
              ViewStackProcessor.push(pointer);
              ViewStackProcessor.pop();
          }
          ObserveV2.getObserve().__interopInStaticRendering_internal_ = false;
      }, {});
  };
  return func;
}

/**
* 
* @param staticBuilder ArkTS1.2builder, return the pointer of PeerNode
* @returns  Creates an updatable dynamic builder function that wraps a static builder
*/
function createDynamicUpdatableBuilder(
  staticBuilder: (args: any) => [number, ()=>void]
): (args: any) => void {
  let func = function (args: any): void {
      let stateMeta: [number, ()=>void]
      this.observeComponentCreation2((elmtId: number, isInitialRender: boolean) => {
        ObserveV2.getObserve().__interopInStaticRendering_internal_ = true;
          if (isInitialRender) {
              stateMeta = staticBuilder(args);
              ViewStackProcessor.push(stateMeta[0]);
              ViewStackProcessor.pop();
          } else {
              Object.values(args).forEach(arg =>arg);
              stateMeta[1]()
          }
          ObserveV2.getObserve().__interopInStaticRendering_internal_ = false;
      }, {});
  };
  return func;
}

function enableCompatibleObservedV2ForStatic(value: Object, 
  createFunc: Function, recordFunc: Function, updateFunc: Function): void {
  value['__staticCompatibleFunc__'] = [createFunc, recordFunc, updateFunc]
}

function createCompatibleStateMetaForStaticObservedV2(): [()=>void, ()=>void] {
  let stateMeta = UIUtilsImpl.instance().makeObserved({value: 1});
  let addRef = (): void => { stateMeta.value }
  let fireChange = (): void => { stateMeta.value++ }
  return [addRef, fireChange]
}

function isDynamicBuilderProxy(value: Object): boolean {
    return !!(value && value['__builder_param_get_target']);
}

function getBuilderParamProxyEntries(value: Object): any[] {
    const res: any[] = [];
    if (isDynamicBuilderProxy(value)) {
        const raw = value['__builder_param_get_target'];
        if (raw instanceof Map) {
            const entries = Array.from(raw.entries());
            entries.forEach((entry)=>{
                if(typeof entry[1] === 'function') {
                    res.push([entry[0], entry[1]()]);
                }
            })
        }
    }
    return res;
}
