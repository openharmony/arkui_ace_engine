/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "test/mock/core/common/theme_mock.h"

#include "core/components/common/layout/constants.h"
#include "core/components/theme/theme_attributes.h"
#include "core/pipeline/pipeline_context.h"

namespace OHOS::Ace {
namespace {

std::unordered_map<int32_t, std::unordered_map<std::string, ResValueWrapper>> g_themes = {
    { 0,
        {
            { THEME_ATTR_BG_COLOR, { .type = ThemeConstantsType::COLOR, .value = Color(0xffffff00) } },
            { THEME_PATTERN_BUTTON, { .type = ThemeConstantsType::PATTERN, .value = 0U } },
        } },
};

std::unordered_map<uint32_t, std::unordered_map<std::string, ResValueWrapper>> g_componentStyles = {
    // buttonStyle
    { 0,
        {
            { PATTERN_BG_COLOR, { .type = ThemeConstantsType::STATE_RESOURCE, .value = 0U } },
            { PATTERN_TEXT_SIZE, { .type = ThemeConstantsType::STRING, .value = "?theme:textSizeButton1" } },
            { PATTERN_WIDTH, { .type = ThemeConstantsType::DOUBLE, .value = 36.0 } },
            { PATTERN_HEIGHT, { .type = ThemeConstantsType::DIMENSION, .value = 36.0_vp } },
        } },
};

const std::unordered_map<uint32_t, std::unordered_map<uint32_t, ResValueWrapper>> STATE_ELEMENTS = {
    // buttonBackgroundColor
    { 0,
        {
            { STATE_NORMAL, { .type = ThemeConstantsType::COLOR, .value = Color(0x0c000000) } },
            { STATE_PRESSED, { .type = ThemeConstantsType::COLOR, .value = Color(0x19000000) } },
        } },
};

const std::unordered_map<uint32_t, ResValueWrapper> RESOURCES = {
    { 117440511, { .type = ThemeConstantsType::COLOR, .value = Color(0xffffffff) } },
    { 117440512, { .type = ThemeConstantsType::COLOR, .value = Color(0xffffffff) } },
    { 117440513, { .type = ThemeConstantsType::DIMENSION, .value = 10.0_vp } },
    { 117440514, { .type = ThemeConstantsType::DOUBLE, .value = 10.0 } },
    { 117440515, { .type = ThemeConstantsType::INT, .value = -10 } },
    { 117440516, { .type = ThemeConstantsType::STRING, .value = "sans-serif" } },
    { 117441012, { .type = ThemeConstantsType::COLOR, .value = Color(0xff5434ff) } },
};

const std::unordered_map<std::string, ResValueWrapper> RESOURCES_WITH_NAME = {
    { "sys.color.test_color", { .type = ThemeConstantsType::COLOR, .value = Color(0xffffffff) } },
    { "sys.float.test_dimension", { .type = ThemeConstantsType::DIMENSION, .value = 10.0_vp } },
    { "sys.double.test_double", { .type = ThemeConstantsType::DOUBLE, .value = 10.0 } },
    { "sys.integer.test_int", { .type = ThemeConstantsType::INT, .value = -10 } },
    { "sys.string.test_string", { .type = ThemeConstantsType::STRING, .value = "sans-serif" } },
    { "sys.string.test_media_path", { .type = ThemeConstantsType::STRING, .value = "./user/a.png" } },
};

const Color ERROR_VALUE_COLOR = Color(0xff000000);
constexpr Dimension ERROR_VALUE_DIMENSION = 0.0_px;
constexpr double ERROR_VALUE_DOUBLE = 0.0;
constexpr int32_t ERROR_VALUE_INT = 0;

} // namespace

ResourceAdapterMock::ResourceAdapterMock()
{
    Initialize();
}

void ResourceAdapterMock::Initialize()
{
    // Replace state resource id with real content in g_componentStyles.
    for (auto& iter : g_componentStyles) {
        for (auto& [attr, valueWrapper] : iter.second) {
            if (valueWrapper.type != ThemeConstantsType::STATE_RESOURCE) {
                continue;
            }
            auto uintPtr = std::get_if<uint32_t>(&(valueWrapper.value));
            if (!uintPtr) {
                continue;
            }
            auto elementItr = STATE_ELEMENTS.find(*uintPtr);
            if (elementItr == STATE_ELEMENTS.end()) {
                continue;
            }
            auto states = AceType::MakeRefPtr<StateResource>();
            for (const auto& [state, value] : elementItr->second) {
                states->SetStateValue(state, value);
            }
            valueWrapper.type = ThemeConstantsType::STATE_RESOURCE;
            valueWrapper.value = states;
        }
    }
    for (auto& iter : g_themes) {
        for (auto& [attr, valueWrapper] : iter.second) {
            if (valueWrapper.type != ThemeConstantsType::PATTERN) {
                continue;
            }
            auto uintPtr = std::get_if<uint32_t>(&(valueWrapper.value));
            if (!uintPtr) {
                continue;
            }
            auto styleItr = g_componentStyles.find(*uintPtr);
            if (styleItr == g_componentStyles.end()) {
                continue;
            }
            RefPtr<ThemeStyle> componentStyle = AceType::MakeRefPtr<ThemeStyle>();
            for (const auto& [attr, value] : styleItr->second) {
                componentStyle->SetAttr(attr, value);
            }
            valueWrapper.type = ThemeConstantsType::PATTERN;
            valueWrapper.value = componentStyle;
        }
    }
}

RefPtr<ThemeStyle> ResourceAdapterMock::GetTheme(int32_t themeId)
{
    auto findIter = g_themes.find(themeId);
    if (findIter == g_themes.end()) {
        return nullptr;
    }
    RefPtr<ThemeStyle> theme = AceType::MakeRefPtr<ThemeStyle>();
    theme->SetAttributes(findIter->second);
    return theme;
}

Color ResourceAdapterMock::GetColor(uint32_t resId)
{
    auto findIter = RESOURCES.find(resId);
    if (findIter == RESOURCES.end()) {
        return ERROR_VALUE_COLOR;
    }
    return findIter->second.GetValue<Color>(ERROR_VALUE_COLOR).second;
}

Dimension ResourceAdapterMock::GetDimension(uint32_t resId)
{
    auto findIter = RESOURCES.find(resId);
    if (findIter == RESOURCES.end()) {
        return ERROR_VALUE_DIMENSION;
    }
    return findIter->second.GetValue<Dimension>(ERROR_VALUE_DIMENSION).second;
}

std::string ResourceAdapterMock::GetString(uint32_t resId)
{
    auto findIter = RESOURCES.find(resId);
    if (findIter == RESOURCES.end()) {
        return "";
    }
    return findIter->second.GetValue<std::string>("").second;
}


std::vector<std::string> ResourceAdapterMock::GetStringArray(uint32_t resId) const
{
    return {};
}

double ResourceAdapterMock::GetDouble(uint32_t resId)
{
    auto findIter = RESOURCES.find(resId);
    if (findIter == RESOURCES.end()) {
        return ERROR_VALUE_DOUBLE;
    }
    return findIter->second.GetValue<double>(ERROR_VALUE_DOUBLE).second;
}

int32_t ResourceAdapterMock::GetInt(uint32_t resId)
{
    auto findIter = RESOURCES.find(resId);
    if (findIter == RESOURCES.end()) {
        return ERROR_VALUE_INT;
    }
    return findIter->second.GetValue<int32_t>(ERROR_VALUE_INT).second;
}

Color ResourceAdapterMock::GetColorByName(const std::string& resName)
{
    auto findIter = RESOURCES_WITH_NAME.find(resName);
    if (findIter == RESOURCES_WITH_NAME.end()) {
        return ERROR_VALUE_COLOR;
    }
    return findIter->second.GetValue<Color>(ERROR_VALUE_COLOR).second;
}

Dimension ResourceAdapterMock::GetDimensionByName(const std::string& resName)
{
    auto findIter = RESOURCES_WITH_NAME.find(resName);
    if (findIter == RESOURCES_WITH_NAME.end()) {
        return ERROR_VALUE_DIMENSION;
    }
    return findIter->second.GetValue<Dimension>(ERROR_VALUE_DIMENSION).second;
}

std::string ResourceAdapterMock::GetStringByName(const std::string& resName)
{
    auto findIter = RESOURCES_WITH_NAME.find(resName);
    if (findIter == RESOURCES_WITH_NAME.end()) {
        return "";
    }
    return findIter->second.GetValue<std::string>("").second;
}

std::vector<std::string> ResourceAdapterMock::GetStringArrayByName(const std::string& resName) const
{
    return {};
}

double ResourceAdapterMock::GetDoubleByName(const std::string& resName)
{
    auto findIter = RESOURCES_WITH_NAME.find(resName);
    if (findIter == RESOURCES_WITH_NAME.end()) {
        return ERROR_VALUE_DOUBLE;
    }
    return findIter->second.GetValue<double>(ERROR_VALUE_DOUBLE).second;
}

int32_t ResourceAdapterMock::GetIntByName(const std::string& resName)
{
    auto findIter = RESOURCES_WITH_NAME.find(resName);
    if (findIter == RESOURCES_WITH_NAME.end()) {
        return ERROR_VALUE_INT;
    }
    return findIter->second.GetValue<int32_t>(ERROR_VALUE_INT).second;
}

std::string ResourceAdapterMock::GetMediaPathByName(const std::string& resName)
{
    auto findIter = RESOURCES_WITH_NAME.find(resName);
    if (findIter == RESOURCES_WITH_NAME.end()) {
        return "";
    }
    return findIter->second.GetValue<std::string>("").second;
}

std::vector<uint32_t> ResourceAdapterMock::GetIntArrayByName(const std::string& resName) const
{
    return {};
}

AnimationOption PipelineContext::GetExplicitAnimationOption() const
{
    return {};
}

uint64_t PipelineContext::GetTimeFromExternalTimer()
{
    return 0;
}

uint32_t PipelineContext::AddScheduleTask(const RefPtr<ScheduleTask>& task)
{
    return 0;
}

void PipelineContext::RemoveScheduleTask(uint32_t id) {}

bool PipelineBase::Animate(const AnimationOption& option, const RefPtr<Curve>& curve,
    const std::function<void()>& propertyCallback, const std::function<void()>& finishCallBack)
{
    return true;
}

void PipelineBase::OpenImplicitAnimation(
    const AnimationOption& option, const RefPtr<Curve>& curve, const std::function<void()>& finishCallBack)
{}

bool PipelineBase::CloseImplicitAnimation()
{
    return true;
}

void PipelineBase::PrepareOpenImplicitAnimation() {}

void PipelineBase::PrepareCloseImplicitAnimation() {}

bool PipelineContext::GetIsDeclarative() const
{
    return true;
}

void PipelineContext::AddGeometryChangedNode(const RefPtr<RenderNode>& renderNode) {}

void PipelineBase::PostAsyncEvent(
    const std::function<void()>& task, const std::string& name, TaskExecutor::TaskType type) {}

void PipelineBase::PostAsyncEvent(
    std::function<void()>&& task, const std::string& name, TaskExecutor::TaskType type) {}

} // namespace OHOS::Ace
