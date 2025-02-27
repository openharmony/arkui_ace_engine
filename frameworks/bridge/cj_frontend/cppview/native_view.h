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

#ifndef FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_NATIVE_VIEW_H
#define FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_NATIVE_VIEW_H

#include <list>
#include <unordered_set>

#include "ffi_remote_data.h"

#include "base/utils/macros.h"
#include "bridge/cj_frontend/cppview/view_abstract.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "core/components_ng/base/view_partial_update_model.h"

namespace OHOS::Ace::Framework {

class NativeView;

ACE_EXPORT bool LoadNativeView(const sptr<NativeView>& view);

ACE_EXPORT std::string GetProcessViewId(int64_t id);

/**
 * delegate for cj view object
 */
class RemoteView : public FFI::RemoteData {
    CJ_REMOTE_CLASS(RemoteView)

public:
    void OnShow();
    void OnHide();
    bool OnBackPress();
    void UpdateWithJson(const std::string&);
    void OnAppear();
    void OnTransition();
    void OnAboutToRender();
    void Render();
    void Rerender();
    void OnAfterRender();
    void OnDisappear();
    void OnAboutToBeDeleted();
    void Reload(bool deep);
    void OnDidBuild();
    void AboutToReuse(const std::string&);
    void AboutToRecycle();
    void RecycleSelf(const std::string&);

private:
    void VoidCallback(void (*cjFunc)(int64_t), const char* funcName);
};

/**
 * NativeView render process have 3 steps
 *  1. create ComposedComponent, set build children callback
 *  2. ComposedComponent create ComposedElement and PerformBuild
 *  3. build children component by CallRenderFunction(set by step 1)
 *
 *  why can't build children component on step 1, because `InternalRender` is not reentrant.
 *  When a NativeView contains a NativeView child, that will cause unexpected result.
 *
 *  how `InternalRender` can't reentrant, see `ViewStackProcessor::GetInstance()->Finish();`,
 *  ViewStackProcessor has a global component tree, and `Finish()` will wrap the whole tree to a Component,
 *  meanwhile clear the tree. when build a tree in the middle of another tree building process,
 *  when subtree finish building by `ViewStackProcessor::GetInstance()->Finish();`, the subtree will be wrap at
 *  wrong start, and the previous tree will lose some nodes.
 */
class ACE_EXPORT NativeView : public ViewAbstract {
    DECL_TYPE(NativeView, ViewAbstract)
    using UpdateFuncResult = std::tuple<int32_t, RefPtr<Component>, RefPtr<Component>>;

public:
    explicit NativeView(sptr<RemoteView> cjView);
    ~NativeView() override;

    void Destroy();

    RefPtr<AceType> CreateUI();
    RefPtr<AceType> InitialUIRender();

    void SyncInstanceId();
    void RestoreInstanceId();
    void MarkNeedUpdate();
    void FlushReload();
    bool NeedsUpdate() const
    {
        return needsUpdate_;
    }
    bool IsFullUpdate() const
    {
        return !useNewPipeline_;
    }

    void SetRenderDoneCallback(std::function<void()> callback)
    {
        onRenderDone_ = std::move(callback);
    }

    /**
     * Views which do not have a state can mark static.
     * The element will be reused and re-render will be skipped.
     */
    void MarkStatic()
    {
        isStatic_ = true;
    }
    bool IsStatic() const
    {
        return isStatic_;
    }

    bool IsFirstRender() const
    {
        return isFirstRender_;
    }

    bool IsUseNewPipeline() const
    {
        return useNewPipeline_;
    }

    /**
     * During render function execution, the child customview with same id will
     * be recycled if they exist already in our child map. The ones which are not
     * recycled needs to be cleaned. So After render function execution, clean the
     * abandoned child customview.
     */
    void CleanUpAbandonedChild();

    void FireOnShow();
    void FireOnHide();
    bool FireOnBackPress();
    void FireOnTransition();
    void ExecuteUpdateWithValueParams(const std::string& jsonData);

    static void Create(const sptr<NativeView>& view);
    static void CreateRecycle(
        const sptr<NativeView>& view, bool isRecycling, const std::string& nodeName, std::function<void()> callback);

    /**
     * Last step of executing an partial update function
     * get the result component from ViewStackProcessor
     * add it to the queue to [elmtId, Component] to
     * execute an local update on in the UI thread
     * parameters
     * elmtId of the Component/Element that's updated
     * removedElementId : Array<number>  ids of Elements that were removed while updating
     * caused by if condition toggle or ForEach array deleted / replaced items
     * return boolean - true means success
     */
    void FinishUpdateFunc(int32_t elmtId);

    // The process of Component to Element sync leads to Elements being
    // deleted. ElementRegister keeps track of these deletions
    // before the framework can forget about these elmtIds
    // these need to be removed from its own book keeping
    // state variables keep track of dependent elmtIds and
    // View objects keep a map elmtId -> update function,
    // both on TS side.
    // View.purgeDeletedElmtIds cleans both state variables
    // and update function map from deleted ElmtIds
    // afterwards it informs the ElementRegister that elmtIds
    // it was able to purge.
    // only then ElementRegister can forget about these elmtIds
    void GetDeletedElemtIds(std::vector<int64_t>& vec);

    // JS signature: View.deletedElmtIdsHaveBeenPurged(elmtIds : number[])
    // inform ElementRegister that given deleted eltIds
    // have been deleted from partial updates book keeping
    // at this point ElementRegister can forget about the,
    void DeletedElmtIdsHaveBeenPurged(std::vector<int64_t>& vec);

    int32_t GetInstanceId() const
    {
        return instanceId_;
    }

    RefPtr<AceType> GetViewNode() const
    {
        return node_.Upgrade();
    }

    void ResetRecycleCustomNode()
    {
        recycleCustomNode_.Reset();
    }

    void SetRecycleCustomNode(const RefPtr<NG::CustomNodeBase>& recycleNode)
    {
        recycleCustomNode_ = recycleNode;
    }

    RefPtr<NG::CustomNodeBase> GetCachedRecycleNode()
    {
        auto node = RefPtr<NG::CustomNodeBase>(recycleCustomNode_);
        recycleCustomNode_.Reset();
        return node;
    }

    const std::string& GetRecycleCustomNodeName()
    {
        return recycleCustomNodeName_;
    }

    void SetRecycleCustomNodeName(const std::string& recycleCustomNodeName)
    {
        recycleCustomNodeName_ = recycleCustomNodeName;
    }

    void SetIsRecycleRerender(bool isRecycleRerender)
    {
        isRecycleRerender_ = isRecycleRerender;
    }

    bool GetIsRecycleRerender()
    {
        return isRecycleRerender_;
    }

private:
    /**
     * cjView is the delegate for cj_custom_view object, it should be assigned once NativeView is created
     * and release after NativeView is released. It's possible to reuse a NativeView to bind several cj_custom_view
     * objects, but it should not, just keep things simple. One NativeView bind one cj_custom_view, never bind
     * a second object, keep it that way.
     */
    sptr<RemoteView> cjView_;

    // view id for custom view itself
    std::string viewId_;

    int32_t instanceId_ = -1;
    int32_t restoreInstanceId_ = -1;

    bool needsUpdate_ = false;
    bool isStatic_ = false;

    std::function<void()> onRenderDone_ = nullptr;
    bool useNewPipeline_ = false;
    bool isFirstRender_ = true;
    WeakPtr<AceType> node_ = nullptr;

    /* list of update function result is a triple (tuple with three entries)
    <0> elmtId
    <1> outmost wrapping Component
    <2> main Component
    */
    std::list<UpdateTask> pendingUpdateTasks_;

    RefPtr<NG::CustomNodeBase> recycleCustomNode_;
    std::string recycleCustomNodeName_;
    bool isRecycleRerender_ = false;
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_NATIVE_VIEW_H
