/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

/**
 * 
 * This file includes only framework internal classes and functions 
 * non are part of SDK. Do not access from app.
 * 
 * Helper classes used by ViewPU and ViewV2
 * 
 */

/**
 * WeakRef
 * ref to an Object that does not prevent the Object from getting GC'ed
 * current version of tsc does not know about WeakRef
 * but Ark runtime supports it
 *
 */
declare class WeakRef<T extends Object> {
    constructor(o: T);
    deref(): T;
  }
  
  declare class DumpLog {
    static print(depth: number, content: string): void;
  }
  
  // function type of partial update function
  type UpdateFunc = (elmtId: number, isFirstRender: boolean) => void;
  type UIClassObject = { prototype: Object, pop?: () => void };
  
  // UpdateFuncRecord: misc framework-internal info related to updating of a UINode C++ object 
  // that TS side needs to know. 
  // updateFunc_  lambda function to update the UINode
  // JS interface class reference (it only has static functions)
  class UpdateFuncRecord {
    private updateFunc_: UpdateFunc;
    private classObject_: UIClassObject;
    private node_?: ArkComponent;
    private isPending_: boolean = false;
    private isChanged_: boolean = false;
  
    constructor(params: { updateFunc: UpdateFunc, classObject?: UIClassObject, node?: ArkComponent }) {
      this.updateFunc_ = params.updateFunc;
      this.classObject_ = params.classObject;
      this.node_ = params.node;
    }
  
    public getUpdateFunc(): UpdateFunc | undefined {
      return this.updateFunc_;
    }
  
    public getComponentClass(): UIClassObject | undefined {
      return this.classObject_;
    }
  
    public getComponentName(): string {
      return (this.classObject_ && ('name' in this.classObject_)) ? Reflect.get(this.classObject_, 'name') as string : 'unspecified UINode';
    }
  
    public getPopFunc(): () => void {
      return (this.classObject_ && 'pop' in this.classObject_) ? this.classObject_.pop! : (): void => { };
    }
  
    public getNode(): ArkComponent | undefined {
      return this.node_;
    }
  
    public setNode(node: ArkComponent | undefined): void {
      this.node_ = node;
    }

    public isPending(): boolean {
      return this.isPending_;
    }

    public setPending(isPending: boolean): void {
      this.isPending_ = isPending;
    }

    public isChanged(): boolean {
      return this.isChanged_;
    }

    public setIsChanged(isChanged: boolean): void {
      this.isChanged_ = isChanged;
    }
  } // UpdateFuncRecord
  
  
class UpdateFuncsByElmtId {

    private map_ = new Map<number, UpdateFuncRecord>();
  
    public delete(elmtId: number): boolean {
      return this.map_.delete(elmtId);
    }
  
    public set(elmtId: number, params: UpdateFunc | { updateFunc: UpdateFunc, classObject?: UIClassObject, node?: ArkComponent }): void {
      (typeof params === 'object') ?
        this.map_.set(elmtId, new UpdateFuncRecord(params)) :
        this.map_.set(elmtId, new UpdateFuncRecord({ updateFunc: params as UpdateFunc }));
    }
  
    public get(elmtId: number): UpdateFuncRecord | undefined {
      return this.map_.get(elmtId);
    }
  
    public has(elmtId: number): boolean {
      return this.map_.has(elmtId);
    }
  
    public keys(): IterableIterator<number> {
      return this.map_.keys();
    }
  
    public clear(): void {
      return this.map_.clear();
    }
  
    public get size(): number {
      return this.map_.size;
    }
  
    public forEach(callbackfn: (value: UpdateFuncRecord, key: number, map: Map<number, UpdateFuncRecord>) => void): void {
      this.map_.forEach(callbackfn);
    }
  
    // dump info about known elmtIds to a string
    // use function only for debug output and DFX.
    public debugInfoRegisteredElmtIds(): string {
      let result: string = '';
      let sepa: string = '';
      this.map_.forEach((value: UpdateFuncRecord, elmtId: number) => {
        result += `${sepa}${value.getComponentName()}[${elmtId}]`;
        sepa = ', ';
      });
      return result;
    }
  
    public debugInfoElmtId(elmtId: number): string {
      const updateFuncEntry = this.map_.get(elmtId);
      return updateFuncEntry ? `${updateFuncEntry!.getComponentName()}[${elmtId}]` : `unknown component type[${elmtId}]`;
    }
  } // class UpdateFuncByElmtId
  