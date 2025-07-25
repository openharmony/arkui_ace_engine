/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MOCK_CANVAS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MOCK_CANVAS_H

#include "interfaces/inner_api/ace/ai/image_analyzer.h"
#include "core/components/common/properties/paint_state.h"
#include "core/components_ng/render/drawing_forward.h"
namespace OHOS::Ace::NG {
class TestHolder {
public:
    TestHolder() = default;
    ~TestHolder() = default;

    static TestHolder* GetInstance()
    {
        static TestHolder instance;
        return &instance;
    }

    void SetUp()
    {
        config = nullptr;
        onAnalyzed = nullptr;
        x = -1;
        y = -1;
        width = -1;
        height = -1;
        counter = 0;
        isCalled = false;
        isCalled2 = false;
        isCalled3 = false;
        isCalled4 = false;
        request = true;
        rect = Rect(-1, -1, -1, -1);
        value = -1;
        segments.clear();
        text = "";
        maxWidth = std::make_optional<double>();
        scaleX = -1;
        scaleY = -1;
        skewX = -1;
        skewY = -1;
        transX = -1;
        transY = -1;
        composite = static_cast<CompositeOperation>(-1);
        enabled = false;
        color = Color::BLACK;
        fontStyle = Ace::FontStyle::NONE;
        fontWeight = Ace::FontWeight::REGULAR;
        fontSize = Dimension(-1, DimensionUnit::NONE);
        fontFamilies.clear();
        path = nullptr;
        gradient = nullptr;
        pattern = nullptr;
        imageData = nullptr;
        pixelMap = nullptr;
        param = nullptr;
        lineDash = nullptr;
        lineCap = std::nullopt;
        lineJoin = std::nullopt;
        canvasImage = std::nullopt;
        fillRule = std::nullopt;
        direction = std::nullopt;
        textAlign = std::nullopt;
        baseline = std::nullopt;
        type = std::nullopt;
        quality = std::nullopt;
    }

    void TearDown()
    {
        request = false;
        path = nullptr;
        gradient = nullptr;
        pattern = nullptr;
        imageData = nullptr;
        pixelMap = nullptr;
        param = nullptr;
        lineDash = nullptr;
        lineCap = std::nullopt;
        lineJoin = std::nullopt;
        canvasImage = std::nullopt;
        fillRule = std::nullopt;
        direction = std::nullopt;
        textAlign = std::nullopt;
        baseline = std::nullopt;
        type = std::nullopt;
        quality = std::nullopt;
    }

    void* config = nullptr;
    OnAnalyzedCallback onAnalyzed = nullptr;
    double x = -1;
    double y = -1;
    double width = -1;
    double height = -1;
    int counter = 0;
    bool isCalled = false;
    bool isCalled2 = false;
    bool isCalled3 = false;
    bool isCalled4 = false;
    bool request = false;
    Rect rect = Rect(-1, -1, -1, 1);
    double value = -1;
    std::vector<double> segments;
    std::string text = "";
    std::optional<double> maxWidth = std::make_optional<double>();
    double scaleX = -1;
    double scaleY = -1;
    double skewX = -1;
    double skewY = -1;
    double transX = -1;
    double transY = -1;
    CompositeOperation composite = static_cast<CompositeOperation>(-1);
    bool enabled = false;
    Color color = Color::BLACK;
    Ace::FontStyle fontStyle = Ace::FontStyle::NONE;
    Ace::FontWeight fontWeight = Ace::FontWeight::REGULAR;
    Dimension fontSize = Dimension(-1, DimensionUnit::NONE);
    std::vector<std::string> fontFamilies;
    OHOS::Ace::RefPtr<OHOS::Ace::CanvasPath2D> path = nullptr;
    std::shared_ptr<OHOS::Ace::Pattern> pattern = nullptr;
    std::shared_ptr<OHOS::Ace::Gradient> gradient = nullptr;
    std::shared_ptr<OHOS::Ace::ImageData> imageData = nullptr;
    OHOS::Ace::RefPtr<OHOS::Ace::PixelMap> pixelMap = nullptr;
    std::shared_ptr<OHOS::Ace::TransformParam> param = nullptr;
    std::shared_ptr<OHOS::Ace::LineDashParam> lineDash = nullptr;
    std::optional<OHOS::Ace::LineCapStyle> lineCap = std::nullopt;
    std::optional<OHOS::Ace::LineJoinStyle> lineJoin = std::nullopt;
    std::optional<Ace::CanvasImage> canvasImage = std::nullopt;
    std::optional<Ace::CanvasFillRule> fillRule = std::nullopt;
    std::optional<Ace::TextDirection> direction = std::nullopt;
    std::optional<Ace::TextAlign> textAlign = std::nullopt;
    std::optional<Ace::TextBaseline> baseline = std::nullopt;
    std::optional<std::string> type = std::nullopt;
    std::optional<double> quality = std::nullopt;
    std::function<void(RSCanvas*, double, double)> rsCallback;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MOCK_CANVAS_H
