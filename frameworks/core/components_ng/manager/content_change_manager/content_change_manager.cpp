/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "content_change_manager.h"

#include "base/utils/time_util.h"
#include "base/log/ace_trace.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include <sstream>

namespace OHOS::Ace::NG {
#ifndef IS_RELEASE_VERSION
enum DumpEvent {
    REGISTER = 0,
    UNREGISTER,
    REPORT,
    SCROLL,
    UNKNOWN
};

using ReportInfo = std::tuple<OHOS::Ace::ChangeType, int32_t, std::string>;
using ScrollInfo = std::tuple<bool, int32_t, std::string, int>;

constexpr int CHANGE_TYPE_INDEX = 0;
constexpr int NODE_ID_INDEX = 1;
constexpr int NODE_TAG_INDEX = 2;
constexpr int START_FLAG_INDEX = 0;
constexpr int COUNT_INDEX = 3;
constexpr int FACTOR = 1000;

struct DumpItem {
    int64_t timestamp = 0;
    DumpEvent event = DumpEvent::UNKNOWN;
    std::variant<
        std::optional<OHOS::Ace::ContentChangeConfig>,
        ReportInfo,
        ScrollInfo
    > extralInfo;

    DumpItem() {}

    DumpItem(int64_t timestamp, DumpEvent event, std::optional<OHOS::Ace::ContentChangeConfig> config)
        : timestamp(timestamp), event(event), extralInfo(config) {}

    DumpItem(int64_t timestamp, DumpEvent event, const ReportInfo& reportInfo)
        : timestamp(timestamp), event(event), extralInfo(reportInfo) {}

    DumpItem(int64_t timestamp, DumpEvent event, const ScrollInfo& scrollInfo)
        : timestamp(timestamp), event(event), extralInfo(scrollInfo) {}
};

static constexpr int DUMP_RECORD_SIZE = 50;
class ContentChangeDumpManager final {
public:
    ContentChangeDumpManager() : records_(DUMP_RECORD_SIZE) {}
    ~ContentChangeDumpManager() = default;

    void AddRegisterRecord(DumpEvent event, std::optional<OHOS::Ace::ContentChangeConfig> config)
    {
        timestamp_ = GetCurrentTimestamp();
        config_ = config;
        records_[currIndex_] = DumpItem(timestamp_, event, config);
        currIndex_ = (currIndex_ + 1) % DUMP_RECORD_SIZE;
    }

    void AddReportRecord(const ReportInfo& reportInfo)
    {
        uint64_t timestamp = GetCurrentTimestamp();
        records_[currIndex_] = DumpItem(timestamp, DumpEvent::REPORT, reportInfo);
        currIndex_ = (currIndex_ + 1) % DUMP_RECORD_SIZE;
    }

    void AddScrollRecord(const ScrollInfo& scrollInfo)
    {
        uint64_t timestamp = GetCurrentTimestamp();
        records_[currIndex_] = DumpItem(timestamp, DumpEvent::SCROLL, scrollInfo);
        currIndex_ = (currIndex_ + 1) % DUMP_RECORD_SIZE;
    }

    std::string Dump()
    {
        std::string ret;
        ret += DumpState();
        for (int i = 0; i < DUMP_RECORD_SIZE; ++i) {
            int index = (currIndex_ + DUMP_RECORD_SIZE - 1 - i) % DUMP_RECORD_SIZE;
            if (records_[index].event == DumpEvent::UNKNOWN) {
                break;
            }
            ret += DumpRecordItem(index);
        }

        return ret;
    }
private:
    std::string DumpState()
    {
        std::stringstream ss;
        if (!config_.has_value()) {
            ss << "UNREGISTERED," << FormatTimestamp(timestamp_) << "\n\n";
            return ss.str();
        }

        ss << "REGISTERED," << FormatTimestamp(timestamp_) << ",textContentratio:" << config_->textContentRatio <<
            ",minReportTime:" << config_->minReportTime << "\n\n";

        return ss.str();
    }

    std::string FormatTimestamp(int64_t timestamp)
    {
        return OHOS::Ace::ConvertTimestampToStr(timestamp);
    }

    int64_t GetCurrentTimestamp()
    {
        return OHOS::Ace::GetCurrentTimestamp();
    }

    std::string DumpRecordItem(int index)
    {
        std::stringstream ss;
        ss << FormatTimestamp(records_[index].timestamp) << ',';

        DumpEvent event = records_[index].event;
        switch (event) {
            case DumpEvent::REGISTER: {
                if (auto optConfig = std::get_if<std::optional<OHOS::Ace::ContentChangeConfig>>(
                    &records_[index].extralInfo)) {
                    OHOS::Ace::ContentChangeConfig config = optConfig->value_or(OHOS::Ace::ContentChangeConfig());
                    ss << "REGISTER,ratio:" << config.textContentRatio << " minReportTime:" << config.minReportTime;
                } else {
                    ss << "INVALID REGISTER RECORD";
                }
                break;
            }
            case DumpEvent::UNREGISTER:
                ss << "UNREGISTER";
                break;
            case DumpEvent::REPORT: {
                if (auto reportInfo = std::get_if<ReportInfo>(&records_[index].extralInfo)) {
                    DumpReportRecord(ss, *reportInfo);
                } else {
                    ss << "INVALID REPORT RECORD";
                }
                break;
            }
            case DumpEvent::SCROLL: {
                if (auto scrollInfo = std::get_if<ScrollInfo>(&records_[index].extralInfo)) {
                    DumpScrollRecord(ss, *scrollInfo);
                } else {
                    ss << "INVALID SCROLL RECORD";
                }
                break;
            }
            default:
                ss << "INVALID RECORD";
                break;
        }
        ss << '\n';

        return ss.str();
    }

    void DumpReportRecord(std::stringstream& ss,
        const ReportInfo& reportInfo)
    {
        ss << "REPORT,";
        OHOS::Ace::ChangeType type = std::get<CHANGE_TYPE_INDEX>(reportInfo);
        int32_t nodeId = std::get<NODE_ID_INDEX>(reportInfo);
        switch (type) {
            case OHOS::Ace::ChangeType::PAGE:
            case OHOS::Ace::ChangeType::SCROLL:
                ss << typeDict_[type] << ',' << nodeId << ',' << std::get<NODE_TAG_INDEX>(reportInfo);
                break;
            case OHOS::Ace::ChangeType::SWIPER:
            case OHOS::Ace::ChangeType::TABS:
                ss << typeDict_[type] << ',' << nodeId;
                break;
            case OHOS::Ace::ChangeType::TEXT:
                ss << typeDict_[type] << ",0." << nodeId; // the nodeId is representing the text ratio here.
                break;
            case OHOS::Ace::ChangeType::DIALOG:
                ss << "DIALOG," << (nodeId > 0 ? "show" : "hide") << ',' << std::abs(nodeId) << ',' <<
                    std::get<NODE_TAG_INDEX>(reportInfo);
                break;
            default:
                ss << "INVALID REPORT RECORD";
        }
    }

    void DumpScrollRecord(std::stringstream& ss, const ScrollInfo& scrollInfo)
    {
        bool isStart = std::get<START_FLAG_INDEX>(scrollInfo);
        int32_t nodeId = std::get<NODE_ID_INDEX>(scrollInfo);
        std::string nodeTag = std::get<NODE_TAG_INDEX>(scrollInfo);
        int count = std::get<COUNT_INDEX>(scrollInfo);
        ss << "SCROLL," << (isStart ? "START" : "END") << ',' << nodeId << ',' << nodeTag << ',' << count;
    }

    std::unordered_map<OHOS::Ace::ChangeType, const char *> typeDict_ = {
        {OHOS::Ace::ChangeType::PAGE, "PAGE"},
        {OHOS::Ace::ChangeType::SCROLL, "SCROLL"},
        {OHOS::Ace::ChangeType::SWIPER, "SWIPER"},
        {OHOS::Ace::ChangeType::TABS, "TABS"},
        {OHOS::Ace::ChangeType::TEXT, "TEXT"},
        {OHOS::Ace::ChangeType::DIALOG, "DIALOG"}
    };

    int64_t timestamp_ = 0;
    std::optional<OHOS::Ace::ContentChangeConfig> config_;
    int currIndex_ = 0;
    std::vector<DumpItem> records_;
};
#endif

ContentChangeManager::ContentChangeManager()
{
#ifndef IS_RELEASE_VERSION
    dumpMgr_ = std::make_shared<ContentChangeDumpManager>();
#endif
}

void ContentChangeManager::StartContentChangeReport(const ContentChangeConfig& config)
{
    currentContentChangeConfig_ = config;
    if (LessNotEqual(config.textContentRatio, 0.0) || GreatNotEqual(config.textContentRatio, 1.0)) {
        currentContentChangeConfig_->textContentRatio = DEFAULT_TEXT_CONTENT_RATIO;
    }
    if (config.minReportTime < 0) {
        currentContentChangeConfig_->minReportTime = DEFAULT_TEXT_MIN_REPORT_TIME;
    }
    ACE_SCOPED_TRACE("[ContentChangeManager] StartContentChangeReport: ratio:%f, minReportTime:%d",
        currentContentChangeConfig_->textContentRatio, currentContentChangeConfig_->minReportTime);
    LOGI("[ContentChangeManager] StartContentChangeReport: ratio:%{public}f, minReportTime:%{public}d",
        currentContentChangeConfig_->textContentRatio, currentContentChangeConfig_->minReportTime);
    textContentRatio_ = currentContentChangeConfig_->textContentRatio;
    textContentInterval_ = currentContentChangeConfig_->minReportTime * NS_PER_MS;
    for (auto& weak : onContentChangeNodes_) {
        auto node = weak.Upgrade();
        if (!node) {
            continue;
        }
        node->OnContentChangeRegister(config);
    }
#ifndef IS_RELEASE_VERSION
    dumpMgr_->AddRegisterRecord(DumpEvent::REGISTER, currentContentChangeConfig_);
#endif
}

void ContentChangeManager::StopContentChangeReport()
{
    ACE_SCOPED_TRACE("[ContentChangeManager] StopContentChangeReport");
    LOGI("[ContentChangeManager] StopContentChangeReport");
    currentContentChangeConfig_.reset();
    for (auto& weak : onContentChangeNodes_) {
        auto node = weak.Upgrade();
        if (!node) {
            continue;
        }
        node->OnContentChangeUnregister();
    }
#ifndef IS_RELEASE_VERSION
    dumpMgr_->AddRegisterRecord(DumpEvent::UNREGISTER, currentContentChangeConfig_);
#endif
}

#ifndef IS_RELEASE_VERSION
std::string ContentChangeManager::DumpInfo() const
{
    return dumpMgr_->Dump();
}
#endif

void ContentChangeManager::AddOnContentChangeNode(WeakPtr<FrameNode> node)
{
    onContentChangeNodes_.emplace(node);
    if (IsContentChangeDetectEnable()) {
        auto nodePtr = node.Upgrade();
        CHECK_NULL_VOID(nodePtr);
        nodePtr->OnContentChangeRegister(currentContentChangeConfig_.value());
    }
}

void ContentChangeManager::RemoveOnContentChangeNode(WeakPtr<FrameNode> node)
{
    onContentChangeNodes_.erase(node);
}

void ContentChangeManager::OnPageTransitionEnd(const RefPtr<FrameNode>& keyNode)
{
    if (!IsContentChangeDetectEnable() || !keyNode || IsScrolling()) {
        return;
    }
    ACE_SCOPED_TRACE("[ContentChangeManager] OnPageTransitionEnd");
    auto simpleTree = JsonUtil::CreateSharedPtrJson(true);
    keyNode->DumpSimplifyTreeWithParamConfig(0, simpleTree, false, {false, false, false});
    UiSessionManager::GetInstance()->ReportContentChangeEvent(ChangeType::PAGE, simpleTree->ToString());
#ifndef IS_RELEASE_VERSION
    dumpMgr_->AddReportRecord(std::make_tuple(ChangeType::PAGE, keyNode->GetId(), keyNode->GetTag()));
#endif
}

void ContentChangeManager::OnScrollChangeEnd(const RefPtr<FrameNode>& keyNode)
{
    if (!IsContentChangeDetectEnable() || !keyNode) {
        return;
    }
    ACE_SCOPED_TRACE("[ContentChangeManager] OnScrollChangeEnd");
    scrollingNodes_.erase(keyNode->GetId());
#ifndef IS_RELEASE_VERSION
    dumpMgr_->AddScrollRecord(std::make_tuple(false, keyNode->GetId(), keyNode->GetTag(), scrollingNodes_.size()));
#endif
    if (!scrollingNodes_.empty()) {
        return;
    }
    UiSessionManager::GetInstance()->ReportContentChangeEvent(ChangeType::SCROLL, "");
#ifndef IS_RELEASE_VERSION
    dumpMgr_->AddReportRecord(std::make_tuple(ChangeType::SCROLL, keyNode->GetId(), keyNode->GetTag()));
#endif
}

void ContentChangeManager::OnSwiperChangeEnd(const RefPtr<FrameNode>& keyNode, bool hasTabsAncestor)
{
    if (!IsContentChangeDetectEnable() || !keyNode || IsScrolling()) {
        return;
    }

    ACE_SCOPED_TRACE("[ContentChangeManager] OnSwiperChangeEnd");
    changedSwiperNodes_.emplace(std::make_pair(WeakPtr(keyNode), hasTabsAncestor));
}

void ContentChangeManager::OnDialogChangeEnd(const RefPtr<FrameNode>& keyNode, bool isShow)
{
    if (!IsContentChangeDetectEnable() || !keyNode || IsScrolling()) {
        return;
    }
    ACE_SCOPED_TRACE("[ContentChangeManager] OnDialogChangeEnd");
    auto simpleTree = JsonUtil::CreateSharedPtrJson(true);
    if (isShow) {
        keyNode->DumpSimplifyTreeWithParamConfig(0, simpleTree, false, {false, false, false});
    } else {
        simpleTree->Put("$type", keyNode->GetTag().c_str());
    }
    simpleTree->Put("show", isShow);
    UiSessionManager::GetInstance()->ReportContentChangeEvent(ChangeType::DIALOG, simpleTree->ToString());
#ifndef IS_RELEASE_VERSION
    int32_t nodeId = keyNode->GetId() * (isShow ? 1 : -1);
    dumpMgr_->AddReportRecord(std::make_tuple(ChangeType::DIALOG, nodeId, keyNode->GetTag()));
#endif
}

void ContentChangeManager::OnTextChangeEnd(const RectF& rect)
{
    if (!IsContentChangeDetectEnable() || !textCollecting_ || rect.IsEmpty() || IsScrolling()) {
        return;
    }
    ACE_SCOPED_TRACE("[ContentChangeManager] OntextChange {%s}", rect.ToString().c_str());
    if (textAABB_.IsEmpty()) {
        textAABB_ = rect;
    } else {
        textAABB_.CombineRectTInner(rect);
    }
}

void ContentChangeManager::OnVsyncStart()
{
    if (!IsContentChangeDetectEnable()) {
        return;
    }

    StartTextAABBCollecting();
}

void ContentChangeManager::OnVsyncEnd(const RectF& rootRect)
{
    if (!IsContentChangeDetectEnable()) {
        return;
    }

    ProcessSwiperNodes();
    StopTextAABBCollecting(rootRect);
}

void ContentChangeManager::ProcessSwiperNodes()
{
    std::set<std::pair<WeakPtr<FrameNode>, bool>> changedSwiperNodes;
    changedSwiperNodes_.swap(changedSwiperNodes);
    for (auto [weak, hasTabsAncestor] : changedSwiperNodes) {
        auto node = weak.Upgrade();
        CHECK_NULL_CONTINUE(node);

        ReportSwiperEvent(node, hasTabsAncestor);
    }
}

void ContentChangeManager::ReportSwiperEvent(const RefPtr<FrameNode> &node, bool hasTabsAncestor)
{
    auto pattern = node->GetPattern();
    CHECK_NULL_VOID(pattern);

    auto keyChildren = pattern->GetKeyFrameNodeWhenContentChanged();

    std::unordered_set<int32_t> visibleNode;
    std::unordered_set<int32_t> subTreeNode;
    visibleNode.emplace(node->GetId());

    for (auto& keyChild : keyChildren) {
        subTreeNode.emplace(keyChild->GetId());
        visibleNode.emplace(keyChild->GetId());
        auto parent = keyChild->GetParent();
            while (parent && !visibleNode.count(parent->GetId())) {
                visibleNode.emplace(parent->GetId());
                parent = parent->GetParent();
            }
    }

    std::function<std::pair<bool, bool>(const RefPtr<UINode>&)> dumpChecker = [&visibleNode, &subTreeNode]
        (const RefPtr<UINode>& node) -> std::pair<bool, bool> {
            CHECK_NULL_RETURN(node, std::make_pair(false, false));
            bool needDump = visibleNode.count(node->GetId());
            CHECK_EQUAL_RETURN(needDump, false, std::make_pair(false, false));
            bool isSubTreeRoot = subTreeNode.count(node->GetId());
            return std::make_pair(needDump, isSubTreeRoot);
    };

    auto rootNode = JsonUtil::CreateSharedPtrJson(true);
    node->DumpSimplifyTreeWithParamConfig(0, rootNode, true, {false, false, false}, dumpChecker);

    if (hasTabsAncestor) {
        auto parent = node->GetParent();
        while (parent) {
            auto jsonNode = JsonUtil::CreateSharedPtrJson(true);
            parent->DumpSimplifyTreeNode(jsonNode, {false, false, false});
            auto array = JsonUtil::CreateArray(true);
            array->PutRef(std::move(rootNode));
            jsonNode->PutRef("$children", std::move(array));
            rootNode = jsonNode;
            if (parent->GetTag() == V2::TABS_ETS_TAG) {
                break;
            }
            parent = parent->GetParent();
        }
    }

    ACE_SCOPED_TRACE("[ContentChangeManager] On%sChanged Reporting", hasTabsAncestor ? "Tabs" : "Swiper");
    UiSessionManager::GetInstance()->ReportContentChangeEvent(
        hasTabsAncestor ? ChangeType::TABS : ChangeType::SWIPER, rootNode->ToString());
#ifndef IS_RELEASE_VERSION
    dumpMgr_->AddReportRecord(std::make_tuple(hasTabsAncestor ? ChangeType::TABS : ChangeType::SWIPER,
        node->GetId(), node->GetTag()));
#endif
}

bool ContentChangeManager::IsTextAABBCollecting() const
{
    return IsContentChangeDetectEnable() && textCollecting_;
}

void ContentChangeManager::StartTextAABBCollecting()
{
    if (!IsContentChangeDetectEnable() || textCollecting_ || IsScrolling()) {
        return;
    }

    uint64_t curr = GetSysTimestamp();
    if (curr - lastTextReportTime_ < textContentInterval_) {
        return;
    }
    textCollecting_ = true;
}

void ContentChangeManager::StopTextAABBCollecting(const RectF& rootRect)
{
    if (!IsContentChangeDetectEnable() || textAABB_.IsEmpty() || IsScrolling()) {
        return;
    }
    if (rootRect.IsIntersectWith(textAABB_)) {
        float rootSize = rootRect.Height() * rootRect.Width();
        RectF intersectRect = rootRect.IntersectRectT(textAABB_);
        float textAABBSize = intersectRect.Height() * intersectRect.Width();
        ACE_SCOPED_TRACE("[ContentChangeManager] StopTextAABBCollecting {%s} / {%s} = %f",
            intersectRect.ToString().c_str(), rootRect.ToString().c_str(), textAABBSize / rootSize);
        if (textAABBSize >= rootSize * textContentRatio_) {
            UiSessionManager::GetInstance()->ReportContentChangeEvent(ChangeType::TEXT, "");
            lastTextReportTime_ = GetSysTimestamp();
#ifndef IS_RELEASE_VERSION
            float currRatio = static_cast<float>(textAABBSize) / rootSize;
            dumpMgr_->AddReportRecord(std::make_tuple(ChangeType::TEXT, static_cast<int32_t>(currRatio * FACTOR), ""));
#endif
        }
    }

    textAABB_.Reset();
    textCollecting_ = false;
}

void ContentChangeManager::OnScrollChangeStart(const RefPtr<FrameNode>& keyNode)
{
    if (!IsContentChangeDetectEnable() || !keyNode) {
        return;
    }
    scrollingNodes_.emplace(keyNode->GetId());
#ifndef IS_RELEASE_VERSION
    dumpMgr_->AddScrollRecord(std::make_tuple(true, keyNode->GetId(), keyNode->GetTag(), scrollingNodes_.size()));
#endif
}

void ContentChangeManager::OnScrollRemoved(int32_t nodeId)
{
    if (scrollingNodes_.count(nodeId)) {
        scrollingNodes_.erase(nodeId);
    }
}

bool ContentChangeManager::IsScrolling() const
{
    return !scrollingNodes_.empty();
}
} // namespace OHOS::Ace::NG
