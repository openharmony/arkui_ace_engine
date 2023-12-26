/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
/// <reference path="../../state_mgmt/src/lib/common/ifelse_native.d.ts" />
/// <reference path="../../state_mgmt/src/lib/partial_update/pu_viewstack_processor.d.ts" />

class BuilderNode extends BaseNode {
  private updateFuncByElmtId?: Map<number, UpdateFunc | UpdateFuncRecord>;
  private params_: Object;
  private uiContext_: UIContext;
  private frameNode_: FrameNode;

  constructor(uiContext: UIContext, options?: RenderOptions) {
    super(uiContext, options);
    this.uiContext_ = uiContext;
    this.updateFuncByElmtId = new Map();
  }

  public getCardId(): number {
    return -1;
  }

  public addChild(child: ViewPU): boolean {
    return false;
  }
  public updateStateVarsOfChildByElmtId(elmtId, params: Object): void { }

  public build(builder: WrappedBuilder<Object[]>, params: Object) {
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    this.params_ = params;
    this.updateFuncByElmtId.clear();
    this.nodePtr_ = super.create(builder.builder, this.params_);
    if (this.frameNode_ === undefined || this.frameNode_ === null) {
      this.frameNode_ = new FrameNode(this.uiContext_, "BuilderNode");
    }
    this.frameNode_.setNodePtr(this.nodePtr_);
    __JSScopeUtil__.restoreInstanceId();
  }
  public update(param: Object) {
    __JSScopeUtil__.syncInstanceId(this.instanceId_);
    this.purgeDeletedElmtIds();
    this.params_ = param;
    Array.from(this.updateFuncByElmtId.keys()).sort((a: number, b: number): number => {
      return (a < b) ? -1 : (a > b) ? 1 : 0;
    }).forEach(elmtId => this.UpdateElement(elmtId));
    __JSScopeUtil__.restoreInstanceId();
  }
  private UpdateElement(elmtId: number): void {
    // do not process an Element that has been marked to be deleted
    const obj: UpdateFunc | UpdateFuncRecord | undefined = this.updateFuncByElmtId.get(elmtId);
    const updateFunc = (typeof obj === "object") ? obj.updateFunc : null;
    if (typeof updateFunc === "function") {
      updateFunc(elmtId, /* isFirstRender */ false);
      this.finishUpdateFunc();
    }
  }

  protected purgeDeletedElmtIds(): void {
    UINodeRegisterProxy.obtainDeletedElmtIds();
    UINodeRegisterProxy.unregisterElmtIdsFromViewPUs();
  }
  public purgeDeleteElmtId(rmElmtId: number): boolean {
    const result = this.updateFuncByElmtId.delete(rmElmtId);
    if (result) {
      UINodeRegisterProxy.ElementIdToOwningViewPU_.delete(rmElmtId);
    }
    return result;
  }

  public getFrameNode(): FrameNode | null {
    if (
      this.frameNode_ !== undefined &&
      this.frameNode_ !== null &&
      this.frameNode_.getNodePtr() !== null
    ) {
      return this.frameNode_;
    }
    return null;
  }

  public observeComponentCreation(func: (arg0: number, arg1: boolean) => void) {
    var elmId: number = ViewStackProcessor.AllocateNewElmetIdForNextComponent();
    UINodeRegisterProxy.ElementIdToOwningViewPU_.set(elmId, new WeakRef(this));
    try {
      func(elmId, true);
    } catch (error) {
      // avoid the incompatible change that move set function before updateFunc.
      UINodeRegisterProxy.ElementIdToOwningViewPU_.delete(elmId);
      throw error;
    }
  }

  public observeComponentCreation2(compilerAssignedUpdateFunc: UpdateFunc, classObject: { prototype: Object; pop?: () => void }): void {
    const _componentName: string = classObject && "name" in classObject ? (Reflect.get(classObject, "name") as string) : "unspecified UINode";
    const _popFunc: () => void =
      classObject && "pop" in classObject ? classObject.pop! : () => { };
    const updateFunc = (elmtId: number, isFirstRender: boolean) => {
      __JSScopeUtil__.syncInstanceId(this.instanceId_);
      ViewStackProcessor.StartGetAccessRecordingFor(elmtId);
      compilerAssignedUpdateFunc(elmtId, isFirstRender, this.params_);
      if (!isFirstRender) {
        _popFunc();
      }
      ViewStackProcessor.StopGetAccessRecording();
      __JSScopeUtil__.restoreInstanceId();
    };

    const elmtId = ViewStackProcessor.AllocateNewElmetIdForNextComponent();
    // needs to move set before updateFunc.
    // make sure the key and object value exist since it will add node in attributeModifier during updateFunc.
    this.updateFuncByElmtId.set(elmtId, {
      updateFunc: updateFunc,
      componentName: _componentName,
    });
    UINodeRegisterProxy.ElementIdToOwningViewPU_.set(elmtId, new WeakRef(this));
    try {
      updateFunc(elmtId, /* is first render */ true);
    } catch (error) {
      // avoid the incompatible change that move set function before updateFunc.
      this.updateFuncByElmtId.delete(elmtId);
      UINodeRegisterProxy.ElementIdToOwningViewPU_.delete(elmtId);
      throw error;
    }
  }

  /**
   Partial updates for ForEach.
   * @param elmtId ID of element.
   * @param itemArray Array of items for use of itemGenFunc.
   * @param itemGenFunc Item generation function to generate new elements. If index parameter is
   *                    given set itemGenFuncUsesIndex to true.
   * @param idGenFunc   ID generation function to generate unique ID for each element. If index parameter is
   *                    given set idGenFuncUsesIndex to true.
   * @param itemGenFuncUsesIndex itemGenFunc optional index parameter is given or not.
   * @param idGenFuncUsesIndex idGenFunc optional index parameter is given or not.
   */
  public forEachUpdateFunction(
    elmtId: number,
    itemArray: Array<any>,
    itemGenFunc: (item: any, index?: number) => void,
    idGenFunc?: (item: any, index?: number) => string,
    itemGenFuncUsesIndex: boolean = false,
    idGenFuncUsesIndex: boolean = false
  ): void {
    if (itemArray === null || itemArray === undefined) {
      return;
    }

    if (itemGenFunc === null || itemGenFunc === undefined) {
      return;
    }

    if (idGenFunc === undefined) {
      idGenFuncUsesIndex = true;
      // catch possible error caused by Stringify and re-throw an Error with a meaningful (!) error message
      idGenFunc = (item: any, index: number) => {
        try {
          return `${index}__${JSON.stringify(item)}`;
        } catch (e) {
          throw new Error(
            ` ForEach id ${elmtId}: use of default id generator function not possible on provided data structure. Need to specify id generator function (ForEach 3rd parameter). Application Error!`
          );
        }
      };
    }

    let diffIndexArray = []; // New indexes compared to old one.
    let newIdArray = [];
    let idDuplicates = [];
    const arr = itemArray; // just to trigger a 'get' onto the array

    // ID gen is with index.
    if (idGenFuncUsesIndex) {
      // Create array of new ids.
      arr.forEach((item, indx) => {
        newIdArray.push(idGenFunc(item, indx));
      });
    } else {
      // Create array of new ids.
      arr.forEach((item, index) => {
        newIdArray.push(
          `${itemGenFuncUsesIndex ? index + "_" : ""}` + idGenFunc(item)
        );
      });
    }

    // Set new array on C++ side.
    // C++ returns array of indexes of newly added array items.
    // these are indexes in new child list.
    ForEach.setIdArray(elmtId, newIdArray, diffIndexArray, idDuplicates);
    // Item gen is with index.
    diffIndexArray.forEach((indx) => {
      ForEach.createNewChildStart(newIdArray[indx], this);
      if (itemGenFuncUsesIndex) {
        itemGenFunc(arr[indx], indx);
      } else {
        itemGenFunc(arr[indx]);
      }
      ForEach.createNewChildFinish(newIdArray[indx], this);
    });
  }

  public ifElseBranchUpdateFunction(branchId: number, branchfunc: () => void) {
    const oldBranchid = If.getBranchId();
    if (branchId == oldBranchid) {
      return;
    }
    // branchid identifies uniquely the if .. <1> .. else if .<2>. else .<3>.branch
    // ifElseNode stores the most recent branch, so we can compare
    // removedChildElmtIds will be filled with the elmtIds of all childten and their children will be deleted in response to if .. else chnage
    var removedChildElmtIds = new Array();
    If.branchId(branchId, removedChildElmtIds);
    this.purgeDeletedElmtIds();

    branchfunc();
  }
}
