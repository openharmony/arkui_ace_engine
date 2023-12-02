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


/*  UINodeRegisterProxy singeleton class

Acts on behave on ElementRegister to hold elmtIds of deleted UINodes
until these get unregistered from a ViewPU.

Two flows inside the framework that involve UINodeRegisterProxy:

Flow A:
1. UINode Destructor calls ElementRegister.RemoveItem(UINode's elmtId) - processing stops:

2. Some time later on next re-render of a ViewPU:
3. ViewPU.purgeDeletedElmtIds calls C+++ UINodeRegisterProxy.obtainElementIds(),
4. UINodeRegisterProxy.obtainElementIds() calls C++  ElementRegister::MoveRemovedItems to move elmtIds of deleted UINodes UINodeRegisterProxy
   (those added by RemoveItems(elmtId) in step 1).
5. UINodeRegisterProxy.unregisterElmtIdsFromViewPUs: unregister the removedElementIds from the all the viewpus:
  1) purge the update function in viewpu
  2) purge the dependent element if from statevariable

Flow B:
1. CustomNode destructor calls deleteFunction calls ViewPU.aboutToBeDeleted
   note that CustomNode destructor may get called before child UINodes' destructor.
  1) unregister its own element ids
  2) call UINodeRegisterProxy.obtainElementIds() to get the removed elementIds from cpp and unregister from all the viewpus.
     it may make the first viewpu aboutToBeDeleted execution time longer than before, but for rest viewpu may be faster.
     It's function equals with purgeDeletedElmtIdsRecursively, so it is not necessary to execute purgeDeletedElmtIds for all its child recursively.

2. some time later or when idle: PipelineContext::OnIdle will CallJSCleanUpIdleTaskFunc to do the clean up for the removed elements which have not unregisted
   from the stateMgmt side.
*/

type RemovedElementInfo = { elmtId : number, tag : string };
// defined a globle function to clean up the removeItems when idle
function uiNodeCleanUpIdleTask(): void {
    stateMgmtConsole.debug(`UINodeRegisterProxy. static uiNodeCleanUpIdleTask:`);
    UINodeRegisterProxy.obtainDeletedElmtIds();
    UINodeRegisterProxy.unregisterElmtIdsFromViewPUs();
}

class UINodeRegisterProxy {
    public static obtainDeletedElmtIds(): void {
        stateMgmtConsole.debug(`UINodeRegisterProxy. static obtainDeletedElmtIds:`);
        if ((!UINodeRegisterProxy.instance_.obtainDeletedElmtIds) || typeof UINodeRegisterProxy.instance_.obtainDeletedElmtIds != "function") {
            stateMgmtConsole.error(`UINodeRegisterProxy obtainDeletedElmtIds is not a function: ${UINodeRegisterProxy.instance_.obtainDeletedElmtIds}.` );
        } else {
            UINodeRegisterProxy.instance_.obtainDeletedElmtIds();
        }
    }

    public static unregisterElmtIdsFromViewPUs(): void {
        stateMgmtConsole.debug('UINodeRegisterProxy.unregisterElmtIdsFromViewPUs elmtIds');
        UINodeRegisterProxy.instance_.unregisterElmtIdsFromViewPUs();
    }

    /* just get the remove items from the native side
    */
    private obtainDeletedElmtIds(): void {
        stateMgmtConsole.debug('UINodeRegisterProxy.obtainDeletedElmtIds: ');
        let removedElementsInfo = new Array<RemovedElementInfo>();
        ViewStackProcessor.moveDeletedElmtIds(removedElementsInfo);
        stateMgmtConsole.debug(`   ... ${removedElementsInfo.length} elmtIds newly obtained from ElementRegister: ${JSON.stringify(removedElementsInfo)} .`);
        this.removeElementsInfo_ = removedElementsInfo;
    }

    public unregisterElmtIdsFromViewPUs(): void {
        stateMgmtConsole.debug(`${this.removeElementsInfo_.length} elmtIds newly obtained from ElementRegister: ${JSON.stringify(this.removeElementsInfo_)} .`);
        
        if (this.removeElementsInfo_.length == 0) {
            stateMgmtConsole.debug(`${this.removeElementsInfo_.length} elmtIds needs to purgeDelete. } .`);
            return;
        }
        let owningView : ViewPU | undefined;
        this.removeElementsInfo_.forEach((rmElmtInfo  : RemovedElementInfo) => {
            const owningViewPUWeak : WeakRef<ViewPU> = UINodeRegisterProxy.ElementIdToOwningViewPU_.get(rmElmtInfo.elmtId );
            if (owningViewPUWeak != undefined) {
                owningView = owningViewPUWeak.deref();
                if (owningView) {
                    owningView.purgeDeleteElmtId(rmElmtInfo.elmtId);
                } else {
                    stateMgmtConsole.debug(`elmtIds ${rmElmtInfo.elmtId} tag: ${rmElmtInfo.tag} has not been removed because of failure of updating the weakptr of viewpu. Internal error!.`);
                }
            } else {
                stateMgmtConsole.debug(`elmtIds ${rmElmtInfo.elmtId} tag: ${rmElmtInfo.tag} cannot find its owning viewpu, maybe this viewpu has already been abouttobedeleted. Internal error!`)
            }
        })

        this.removeElementsInfo_.length = 0;
    }

    public static instance_: UINodeRegisterProxy = new UINodeRegisterProxy();
    public removeElementsInfo_: Array<RemovedElementInfo> = new Array<RemovedElementInfo>();
    public static ElementIdToOwningViewPU_: Map<number, WeakRef<ViewPU>> = new Map<number, WeakRef<ViewPU>>();
}
