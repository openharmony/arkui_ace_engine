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
   (those added by RemoveItems(elmtId) in step 1), see documentation of the UINodeRegisterProxy.obtainElementIds() for details.
5. continue if UINodeRegisterProxy.elmtIdsNeedUnregister:
6. forEach elmtId managed by this ViewPU call UINodeRegisterProxy.consume(elmtId)
7. if the consume(elmtId) returns true it means this elmtId has been deleted and needs to be unregistered from the ViewPU and its state vars.
   consume(elmtId) also deleted the elmtId from Set UINodeRegisterProxy.elmtIdsToUnregister_


Flow B:
1. CustomNode destructor calls deleteFunction calls ViewPU.aboutToBeDeleted
   note that CustomNode destructor may get called before child UINodes' destructor.
2. aboutToBeDeleted calls UINodeRegisterProxy.accountElmtIdsAsUnregistered(elmtIds) for all elmtIds of child UINodes of this ViewPU
   see accountElmtIdsAsUnregistered(elmtIds array) method for details.

3. some time later: child UINodes destructor call ElementRegister::removeItem(elmtId), ElementRegister memorises the elmtId until  
   next ViewPU.purgeDeletedElmtIds - processing ends

4. some time later: a ViewPU rerenders and calls ViewPU.purgeDeletedElmtIds, calls UINodeRegisterProxy.obtainElementIds()
   obtainElementIds() realizes that the elmtIds added in step 3 have already been marked as unregistered in step 2.
   see obtainElementIds() for details.
*/

type RemovedElementInfo = { elmtId : number, tag : string };

class UINodeRegisterProxy {
    public static UINodeRegisterCleanUpFunction() : void {
        UINodeRegisterProxy.instance_.obtainDeletedElmtIds();
    }

    public static obtainDeletedElmtIds(): void {
        UINodeRegisterProxy.instance_.obtainDeletedElmtIds();
    }

    public static accountElmtIdsAsUnregistered(elmtIds: number[]): void {
        UINodeRegisterProxy.instance_.accountElmtIdsAsUnregistered(elmtIds);
    }

    public static consume(elmtId: number): boolean {
        return UINodeRegisterProxy.instance_.consume(elmtId);
    }

    /*
    a function to enable an optimization, returns true if UINodeRegisterProxy
    has any elmtIds that need to be unregistered
    */
    public static hasElmtIdsPendingUnregister(): boolean {
        return UINodeRegisterProxy.instance_.elmtIdsToUnregister_.size > 0;
    }

    public static dump() {
        UINodeRegisterProxy.instance_.dump();
    }

    // private properties & functions:

    /* move elmtIds from C++ ElementRegister, elmtIds of UINodes that have been deleted 
     two processing steps for each moved elmtId:
     1. check if elmtId has been unregistered ahead of time (when a ViewPU gets deleted)
     2. if not, memorize elmtId to still need un-registration
    */
    private obtainDeletedElmtIds(): void {

        stateMgmtConsole.debug(`UINodeRegisterProxy.obtainDeletedElmtIds: `);

        let removedElementsInfo = new Array<RemovedElementInfo>();
        ViewStackProcessor.moveDeletedElmtIds(removedElementsInfo);
        stateMgmtConsole.debug(`   ... ${removedElementsInfo.length} elmtIds newly obtained from ElementRegister: ${JSON.stringify(removedElementsInfo)} .`);

        removedElementsInfo.forEach(rmElmtInfo => {
            if (this.elmtIdsUnregisteredAheadOfTime_.has(rmElmtInfo.elmtId)) {
                stateMgmtConsole.debug(`   ... elmtId ${rmElmtInfo.elmtId}[${rmElmtInfo.tag}] listed as unregistered ahead of time. Done with it. `);
                this.elmtIdsUnregisteredAheadOfTime_.delete(rmElmtInfo.elmtId);
            } else {
                stateMgmtConsole.debug(`   ... elmtId ${rmElmtInfo.elmtId}[${rmElmtInfo.tag}] need to be unregistered later.`);
                this.elmtIdsToUnregister_.add(rmElmtInfo.elmtId);
                this.tagByElmtId_.set(rmElmtInfo.elmtId, rmElmtInfo.tag);
            }
        });
        this.dump();
    }

    /* 
        called from ViewPU with all its child elmtIds
        memorize these elmtIds until obtainDeletedElmtIds finds them in ElementRegister later (see its step 1)
    */
    private accountElmtIdsAsUnregistered(elmtIds: Array<number>): void {
        stateMgmtConsole.debug(`UINodeRegisterProxy.accountElmtIdsAsUnregistered: ${elmtIds.length} elmtIds: [ ${JSON.stringify(elmtIds)} ] - start`);
        // get info about latest deleted elmtIds from C++ to UINodeRegisterProxy
        this.obtainDeletedElmtIds();
        elmtIds.filter((elmtId: number) => {
            return /* can not unregister elmtId */ !this.consume(elmtId)
        }).forEach((elmtIdUnregisteredAheadOfTime) => {
            // add to Set of elmtIds that have been unregistered already
            // when the elmtId arrives with later ObtainDeletedElementIds, we know it is unregistered already
            this.elmtIdsUnregisteredAheadOfTime_.add(elmtIdUnregisteredAheadOfTime)
        });
        this.dump();
    }


    /* called view View to query if given elmtId needs to be unregistered 
      (these are the elmtIds added in step 2 of obtainDeletedElmtIds)
      if true, forget about the elmtId because called ViewPU will unregistered it next, tell it
      to do so by returning true.
    */
    private consume(elmtId: number): boolean {
        if (this.elmtIdsToUnregister_.delete(elmtId)) {
            stateMgmtConsole.debug(`UINodeRegisterProxy.consume ${elmtId}[${this.tagByElmtId_.get(elmtId)}] has been removed from UINodeRegisterProxy.`);
            this.tagByElmtId_.delete(elmtId);
            return true;
        }
        return false;
    }

    /*
  dump the state  of UINodeRegisterProxy to log
  does nothing in release build
*/
    private dump() {
        const formatElementInfo = () : string => {
            let result = '[ ';
            let sepa = "";
            Array.from(this.elmtIdsToUnregister_).forEach((elmtId) => {
                result+= `${sepa}${elmtId}[${this.tagByElmtId_.get(elmtId)}]`;
                sepa=", ";
            });
            result += ' ]';
            return result;
        };

        stateMgmtConsole.debug(`UINodeRegisterProxy dump: `);
        stateMgmtConsole.debug(`- ${this.elmtIdsToUnregister_.size} elmtIds need unregister: ${formatElementInfo()}.`);
        stateMgmtConsole.debug(`- ${this.elmtIdsUnregisteredAheadOfTime_.size} elmtIds marked as unregistered already: ${JSON.stringify(Array.from(this.elmtIdsUnregisteredAheadOfTime_))} .`);
    }

    private static instance_: UINodeRegisterProxy = new UINodeRegisterProxy();
    private elmtIdsToUnregister_: Set<number> = new Set<number>();
    private tagByElmtId_ : Map<number, string> = new Map<number, string>();
    private elmtIdsUnregisteredAheadOfTime_: Set<number> = new Set<number>();
}

const UINodeRegisterCleanUpFunction = UINodeRegisterProxy.UINodeRegisterCleanUpFunction;
