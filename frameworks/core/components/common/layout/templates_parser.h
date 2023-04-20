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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_COMMON_LAYOUT_TEMPLATES_PARSER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_COMMON_LAYOUT_TEMPLATES_PARSER_H

#include "base/utils/noncopyable.h"
#include "base/geometry/dimension.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {
class TemplatesParser final : public NonCopyable {
public:
    TemplatesParser() = default;
    ~TemplatesParser() override = default;
    explicit TemplatesParser(const WeakPtr<RenderNode>& renderNode) : renderNode_(renderNode) {}

    std::vector<double> ParseArgs(const WeakPtr<RenderNode>& node, const std::string& args, double size, double gap);

private:
    enum class RepeatType {
        NONE = 0,
        FIXED_COUNT,
        AUTO_FILL,
    };

    using Value = struct {
        std::string str;
        bool isRepeat = false;
    };

    static void RTrim(std::string& str);
    static std::string TrimTemplate(std::string& str);
    static std::string GetRepeat(const std::string& str);
    double ParseUnit(const Value& val, double size);

    static void ConvertRepeatArgs(std::string& handledArg);
    static std::vector<double> ParseArgs(const std::string& args, double size, double gap);
    static std::vector<double> ParseAutoFill(const std::vector<std::string>& strs, double size, double gap);

    double ConvertVirtualSize(const std::string& val, const DimensionUnit& unit, double size);
    static bool SplitTemplate(const std::string& str, std::vector<Value>& vec, bool isRepeat = false);
    std::vector<double> ParseArgsWithAutoFill(const std::string& args, double size, double gap);
    static bool CheckRepeatAndSplitString(
        std::vector<std::string>& vec, std::string& repeat, std::vector<Value>& resultvec);
    static bool CheckAutoFillParameter(
        const std::string& args, double size, std::vector<double>& out,  std::vector<Value>& resultvec);

    WeakPtr<RenderNode> renderNode_;
    ACE_DISALLOW_COPY_AND_MOVE(TemplatesParser);
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_COMMON_LAYOUT_TEMPLATES_PARSER_H
