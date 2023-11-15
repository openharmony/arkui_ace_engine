/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_XCOMPONENT_XCOMPONENT_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_XCOMPONENT_XCOMPONENT_COMPONENT_H

#include <string>

#include "base/geometry/size.h"
#include "base/utils/utils.h"
#include "core/components/declaration/xcomponent/xcomponent_declaration.h"
#include "core/components/xcomponent/native_interface_xcomponent_impl.h"
#include "core/components/xcomponent/resource/native_texture.h"
#include "core/components_ng/pattern/xcomponent/inner_xcomponent_controller.h"
#include "core/pipeline/base/element.h"

namespace OHOS::Ace {
class XComponentDelegate;
class RenderXComponent;
class XComponentComponent;

using TaskFunction = std::function<void(RenderXComponent&, const Offset&)>;
using PushTaskFunction = std::function<void(const TaskFunction&)>;

class ACE_EXPORT XComponentTaskPool : virtual public AceType {
    DECLARE_ACE_TYPE(XComponentTaskPool, AceType);

public:
    void PushTask(const TaskFunction& task)
    {
        if (pushToRenderNodeFunc_) {
            pushToRenderNodeFunc_(task);
        } else {
            tasks_.emplace_back(task);
        }
    }

    void SetPushToRenderNodeFunc(const PushTaskFunction& pushTaskFunc)
    {
        pushToRenderNodeFunc_ = pushTaskFunc;
    }

    const std::list<TaskFunction>& GetTasks() const
    {
        return tasks_;
    }

    void ClearTasks()
    {
        tasks_.clear();
    }

    void SetRenderNode(const WeakPtr<RenderXComponent>& renderNode);
    void NativeXComponentInit(
        OH_NativeXComponent* nativeXComponent, WeakPtr<NativeXComponentImpl> nativeXComponentImpl);

    WeakPtr<XComponentComponent> component_;

private:
    PushTaskFunction pushToRenderNodeFunc_;
    std::list<TaskFunction> tasks_;
    WeakPtr<RenderXComponent> renderNode_;
};

// A component can show different native view.
class ACE_EXPORT XComponentComponent : public RenderComponent {
    DECLARE_ACE_TYPE(XComponentComponent, RenderComponent);

public:
    using CreatedCallback = std::function<void()>;
    using ReleasedCallback = std::function<void(bool)>;
    using DeleteCallback = std::function<void()>;
    using ErrorCallback = std::function<void(const std::string&, const std::string&)>;
    using MethodCall = std::function<void(const std::string&)>;
    using Method = std::string;

    XComponentComponent() = default;
    explicit XComponentComponent(const std::string& type);
    ~XComponentComponent() override
    {
        if (deleteCallback_) {
            deleteCallback_();
        }
    }

    RefPtr<RenderNode> CreateRenderNode() override;
    RefPtr<Element> CreateElement() override;

    void SetType(const std::string& type)
    {
        type_ = type;
    }

    const std::string& GetType() const
    {
        return type_;
    }

    void SetName(const std::string& name)
    {
        declaration_->SetXComponentName(name);
    }

    const std::string& GetName() const
    {
        return declaration_->GetXComponentName();
    }

    void SetId(const std::string& id)
    {
        declaration_->SetXComponentId(id);
    }

    const std::string& GetId() const
    {
        return declaration_->GetXComponentId();
    }

    void SetXComponentType(const std::string& type)
    {
        declaration_->SetXComponentType(type);
    }

    const std::string& GetXComponentType() const
    {
        return declaration_->GetXComponentType();
    }

    void SetLibraryName(const std::string& libraryName)
    {
        declaration_->SetXComponentLibraryName(libraryName);
    }

    const std::string& GetLibraryName() const
    {
        return declaration_->GetXComponentLibraryName();
    }

    void SetXComponentInitEventId(const EventMarker& xComponentInitEventId)
    {
        declaration_->SetXComponentInitEventId(xComponentInitEventId);
    }

    const EventMarker& GetXComponentInitEventId() const
    {
        return declaration_->GetXComponentInitEventId();
    }

    void SetXComponentDestroyEventId(const EventMarker& xComponentDestroyEventId)
    {
        declaration_->SetXComponentDestroyEventId(xComponentDestroyEventId);
    }

    const EventMarker& GetXComponentDestroyEventId() const
    {
        return declaration_->GetXComponentDestroyEventId();
    }

    void SetDeclaration(const RefPtr<XComponentDeclaration>& declaration)
    {
        if (declaration) {
            declaration_ = declaration;
        }
    }

    const RefPtr<XComponentTaskPool>& GetTaskPool() const
    {
        return pool_;
    }

    int64_t GetTextureId() const
    {
        return textureId_;
    }

    void SetTextureId(int64_t textureId)
    {
        textureId_ = textureId;
    }

    int32_t GetNodeId() const
    {
        return nodeId_;
    }

    void SetNodeId(int32_t nodeId)
    {
        nodeId_ = nodeId;
    }

    RefPtr<NativeTexture> GetTexture() const
    {
        return texture_;
    }

    void SetTexture(RefPtr<NativeTexture> texture)
    {
        texture_ = texture;
    }

    std::shared_ptr<InnerXComponentController> GetXComponentController() const
    {
        return xcomponentController_;
    }

    void SetXComponentController(const std::shared_ptr<InnerXComponentController>& xcomponentController)
    {
        xcomponentController_ = xcomponentController;
    }

    void RegisterDeleteCallback(DeleteCallback&& callback)
    {
        deleteCallback_ = std::move(callback);
    }

    void SetDeleteCallbackToNull()
    {
        deleteCallback_ = nullptr;
    }

    const std::optional<std::string>& GetSoPath() const
    {
        return soPath_;
    }

    void SetSoPath(const std::string& soPath)
    {
        soPath_ = soPath;
    }

#ifdef OHOS_STANDARD_SYSTEM
    void SetNativeWindow(void* nativeWindow)
    {
        nativeWindow_ = nativeWindow;
    }

    void* GetNativeWindow()
    {
        return nativeWindow_;
    }
#endif

private:
    RefPtr<XComponentDeclaration> declaration_;
    CreatedCallback createdCallback_ = nullptr;
    ReleasedCallback releasedCallback_ = nullptr;
    DeleteCallback deleteCallback_ = nullptr;
    ErrorCallback errorCallback_ = nullptr;
    RefPtr<XComponentTaskPool> pool_;
    std::shared_ptr<InnerXComponentController> xcomponentController_;
    std::string type_;
    std::optional<std::string> soPath_;
    int64_t textureId_ = -1;
    int32_t nodeId_ = -1;
    RefPtr<NativeTexture> texture_;
#ifdef OHOS_STANDARD_SYSTEM
    void* nativeWindow_ = nullptr;
#endif
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_XCOMPONENT_XCOMPONENT_COMPONENT_H
