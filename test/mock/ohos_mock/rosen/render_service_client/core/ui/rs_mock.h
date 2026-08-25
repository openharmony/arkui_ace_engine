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

#ifndef RENDER_SERVICE_CLIENT_CORE_UI_RS_MOCK_H
#define RENDER_SERVICE_CLIENT_CORE_UI_RS_MOCK_H

#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <utility>

namespace OHOS::Rosen {
using NodeId = uint64_t;

class RSTransaction {
public:
    void FlushImplicitTransaction() {}
};

class RSUIContext {
public:
    void AttachFromUI() {}
    void DetachFromUI() {}
    bool HasTaskRunner() const
    {
        return false;
    }
    std::shared_ptr<RSTransaction> GetRSTransaction() const
    {
        return transaction_;
    }

private:
    std::shared_ptr<RSTransaction> transaction_ = std::make_shared<RSTransaction>();
};

class RSNode : public std::enable_shared_from_this<RSNode> {
public:
    using SharedPtr = std::shared_ptr<RSNode>;

    virtual ~RSNode() = default;

    NodeId GetId() const
    {
        return id_;
    }

    size_t GetAnimationsCount() const
    {
        return 0;
    }

    bool GetIsOnTheTree() const
    {
        return false;
    }

    template<typename T>
    static std::shared_ptr<T> ReinterpretCast(const std::shared_ptr<RSNode>& node)
    {
        return std::static_pointer_cast<T>(node);
    }

private:
    NodeId id_ = 1;
};

class RSRootNode : public RSNode {};

class RSSurfaceNode : public RSNode {
public:
    std::shared_ptr<RSUIContext> GetRSUIContext() const
    {
        return context_;
    }

private:
    std::shared_ptr<RSUIContext> context_ = std::make_shared<RSUIContext>();
};

using TaskRunner = std::function<void(const std::function<void()>&, uint32_t)>;

class RSUIDirector final {
public:
    static std::shared_ptr<RSUIDirector> Create(std::nullptr_t, std::shared_ptr<RSUIContext> context = nullptr)
    {
        return std::make_shared<RSUIDirector>(std::move(context));
    }

    explicit RSUIDirector(std::shared_ptr<RSUIContext> context)
        : context_(context ? std::move(context) : std::make_shared<RSUIContext>())
    {}

    void GoResume() {}
    void GoForeground(bool = false) {}
    void GoBackground(bool = false) {}
    void GoStop() {}
    void Destroy(bool = false) {}
    void SetRSSurfaceNode(const std::shared_ptr<RSSurfaceNode>& node)
    {
        surfaceNode_ = node;
    }
    std::shared_ptr<RSSurfaceNode> GetRSSurfaceNode() const
    {
        return surfaceNode_;
    }
    void SetUITaskRunner(const TaskRunner&, int32_t = -1, bool = false) {}
    void SendMessages() {}
    void SendMessages(const std::function<void()>& callback)
    {
        if (callback) {
            callback();
        }
    }
    void SetTimeStamp(uint64_t, const std::string&) {}
    void SetCacheDir(const std::string&) {}
    bool FlushAnimation(uint64_t, int64_t = 0)
    {
        return false;
    }
    bool HasFirstFrameAnimation() const
    {
        return false;
    }
    void FlushModifier() {}
    bool HasUIRunningAnimation() const
    {
        return false;
    }
    void FlushAnimationStartTime(uint64_t) {}
    void SetRequestVsyncCallback(const std::function<void()>& callback)
    {
        requestVsyncCallback_ = callback;
    }
    int32_t GetCurrentRefreshRateMode() const
    {
        return 0;
    }
    int32_t GetAnimateExpectedRate() const
    {
        return 0;
    }
    std::shared_ptr<RSUIContext> GetRSUIContext() const
    {
        return context_;
    }
    void SetRSRootNode(const std::shared_ptr<RSRootNode>& node)
    {
        rootNode_ = node;
    }
    void SetDVSyncUpdate(uint64_t) {}

private:
    std::function<void()> requestVsyncCallback_;
    std::shared_ptr<RSUIContext> context_;
    std::shared_ptr<RSSurfaceNode> surfaceNode_;
    std::shared_ptr<RSRootNode> rootNode_;
};

class RSSystemProperties {
public:
    static void SetDrawTextAsBitmap(bool) {}
};
} // namespace OHOS::Rosen

#endif // RENDER_SERVICE_CLIENT_CORE_UI_RS_MOCK_H
