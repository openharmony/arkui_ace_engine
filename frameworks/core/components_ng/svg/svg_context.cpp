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

#include "core/components_ng/svg/svg_context.h"

#include "core/common/thread_checker.h"
#include "core/components_ng/svg/parse/svg_node.h"

namespace OHOS::Ace::NG {
RefPtr<SvgNode> SvgContext::GetSvgNodeById(const std::string& id) const
{
    auto item = idMapper_.find(id);
    if (item != idMapper_.end()) {
        return item->second.Upgrade();
    }
    return nullptr;
}

void SvgContext::PushStyle(const std::string& styleName, const std::pair<std::string, std::string>& attrPair)
{
    const auto& arrMapIter = styleMap_.find(styleName);
    if (arrMapIter == styleMap_.end()) {
        AttrMap attrMap;
        attrMap.emplace(attrPair);
        styleMap_.emplace(std::make_pair(styleName, attrMap));
    } else {
        if (arrMapIter->second.find(attrPair.first) != arrMapIter->second.end()) {
            arrMapIter->second.erase(attrPair.first);
        }
        arrMapIter->second.emplace(attrPair);
    }
}

const AttrMap& SvgContext::GetAttrMap(const std::string& key) const
{
    auto styleClassIter = styleMap_.find(key);
    if (styleClassIter != styleMap_.end()) {
        return styleClassIter->second;
    }
    static AttrMap emptyMap;
    return emptyMap;
}

void SvgContext::AddAnimator(int32_t key, const RefPtr<Animator>& animator)
{
    animators_[key] = animator;
}

void SvgContext::RemoveAnimator(int32_t key)
{
    animators_.erase(key);
}

void SvgContext::ControlAnimators(bool play)
{
    for (auto&& it : animators_) {
        auto animator = it.second.Upgrade();
        if (!animator) {
            LOGW("null animator in map");
            animators_.erase(it.first);
            continue;
        }
        if (play) {
            animator->Play();
        } else {
            animator->Pause();
        }
    }
}

void SvgContext::SetFuncAnimateFlush(FuncAnimateFlush&& funcAnimateFlush, const WeakPtr<CanvasImage>& imagePtr)
{
    CHECK_NULL_VOID(funcAnimateFlush);
    animateCallbacks_[imagePtr] = funcAnimateFlush;
}

size_t SvgContext::GetAnimatorCount()
{
    return animators_.size();
}

void SvgContext::AnimateFlush()
{
    CHECK_RUN_ON(UI);
    CHECK_NULL_VOID(!animateCallbacks_.empty());
    for (auto it = animateCallbacks_.begin(); it != animateCallbacks_.end();) {
        if (it->first.Upgrade()) {
            it->second();
            ++it;
        } else {
            animateCallbacks_.erase(it++);
        }
    }
}

void SvgContext::SetFuncNormalizeToPx(const FuncNormalizeToPx& funcNormalizeToPx)
{
    funcNormalizeToPx_ = funcNormalizeToPx;
}

double SvgContext::NormalizeToPx(const Dimension& value)
{
    if (funcNormalizeToPx_ == nullptr) {
        return 0.0;
    }
    return funcNormalizeToPx_(value);
}
} // namespace OHOS::Ace::NG
