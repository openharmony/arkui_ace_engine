/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * IView is an interface implemented by both ViewPU and ViewV2
 * 
 */

interface IView {
    id__() : number;
    debugInfo__() : string;

    getCardId(): number; // implemented in NativeViewPartialUpdate
    getParent(): IView | undefined;
    setParent(p: IView) : void;
    addChild(c: IView): boolean;
    getChildById(elmtId: number) : IView | undefined;
    removeChild(child: IView): boolean;
    findViewPUInHierarchy(id: number): ViewPU | undefined;

    purgeDeleteElmtId(rmElmtId: number): boolean;
    initialRenderView(): void;
    forceCompleteRerender(deep: boolean): void;
    forceRerenderNode(elmtId: number): void;
    
    uiNodeNeedUpdateV2(elmtId: number) : void;
    
    // FIXME replace updateStateVarsOfChildByElmtId by new solution
    updateStateVarsOfChildByElmtId(elmtId, params: Object): void;

    aboutToBeDeleted(): void;
    isDeleting(): boolean;
    setDeleting(): void;
    setDeleteStatusRecursively(): void;

    isCompFreezeAllowed(): boolean;
    setActiveInternal(newState: boolean): void;

    findProvidePU(providedPropName: string): ObservedPropertyAbstractPU<any> | undefined;

    localStorage_ : LocalStorage;

    debugInfoViewHierarchyInternal(depth: number, recursive: boolean): string;
    debugInfoUpdateFuncByElmtIdInternal(counter: ProfileRecursionCounter, depth: number, recursive: boolean): string;
    debugInfoDirtDescendantElementIdsInternal(depth: number, recursive: boolean, counter: ProfileRecursionCounter): string;

    onGlobalThemeChanged(): void;
}
