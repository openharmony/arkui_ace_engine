/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_loading_progress.h"

#include "base/utils/utils.h"
#include "bridge/declarative_frontend/jsview/models/loading_progress_model_impl.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_model.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_model_ng.h"

namespace OHOS::Ace {
std::unique_ptr<LoadingProgressModel> LoadingProgressModel::instance_ = nullptr;
std::mutex LoadingProgressModel::mutex_;

LoadingProgressModel* LoadingProgressModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::LoadingProgressModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::LoadingProgressModelNG());
            } else {
                instance_.reset(new Framework::LoadingProgressModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {} // namespace

void JSLoadingProgress::JSBind(BindingTarget globalObj)
{
    JSClass<JSLoadingProgress>::Declare("LoadingProgress");
    MethodOptions opt = MethodOptions::NONE;

    JSClass<JSLoadingProgress>::StaticMethod("create", &JSLoadingProgress::Create, opt);
    JSClass<JSLoadingProgress>::StaticMethod("color", &JSLoadingProgress::SetColor, opt);
    JSClass<JSLoadingProgress>::StaticMethod("enableLoading", &JSLoadingProgress::SetEnableLoading, opt);
    JSClass<JSLoadingProgress>::StaticMethod("foregroundColor", &JSLoadingProgress::SetForegroundColor, opt);

    JSClass<JSLoadingProgress>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSLoadingProgress>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSLoadingProgress>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSLoadingProgress>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSLoadingProgress>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSLoadingProgress>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSLoadingProgress::Create()
{
    LoadingProgressModel::GetInstance()->Create();
}

void JSLoadingProgress::SetColor(const JSCallbackInfo& info)
{
    Color progressColor;
    RefPtr<ResourceObject> resObj;
    if (SystemProperties::ConfigChangePerform()) {
        bool state = ParseJsColor(info[0], progressColor, resObj);
        LoadingProgressModel::GetInstance()->CreateWithResourceObj(
            OHOS::Ace::LoadingProgressResourceType::COLOR, resObj);
        if (state) {
            LoadingProgressModel::GetInstance()->SetColor(progressColor);
        } else {
            if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
                RefPtr<ProgressTheme> progressTheme = GetTheme<ProgressTheme>();
                CHECK_NULL_VOID(progressTheme);
                progressColor = progressTheme->GetLoadingParseFailedColor();
            } else {
                return;
            }
            LoadingProgressModel::GetInstance()->SetColor(progressColor);
            LoadingProgressModel::GetInstance()->SetColorByUser(false);
        }
    } else {
        if (!ParseJsColor(info[0], progressColor)) {
            if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
                RefPtr<ProgressTheme> progressTheme = GetTheme<ProgressTheme>();
                CHECK_NULL_VOID(progressTheme);
                progressColor = progressTheme->GetLoadingParseFailedColor();
            } else {
                return;
            }
        }
        LoadingProgressModel::GetInstance()->SetColor(progressColor);
    }
}

void JSLoadingProgress::SetForegroundColor(const JSCallbackInfo& info)
{
    ForegroundColorStrategy strategy;
    if (ParseJsColorStrategy(info[0], strategy)) {
        ViewAbstractModel::GetInstance()->SetForegroundColorStrategy(strategy);
        return;
    }
    Color progressColor;
    RefPtr<ResourceObject> resObj;
    if (SystemProperties::ConfigChangePerform()) {
        bool state = ParseJsColor(info[0], progressColor, resObj);
        LoadingProgressModel::GetInstance()->CreateWithResourceObj(
            OHOS::Ace::LoadingProgressResourceType::FOREGROUNDCOLOR, resObj);
        if (state) {
            LoadingProgressModel::GetInstance()->SetForegroundColorParseFailed(false);
            LoadingProgressModel::GetInstance()->SetColor(progressColor);
        } else {
            if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
                LoadingProgressModel::GetInstance()->SetForegroundColorParseFailed(true);
                LoadingProgressModel::GetInstance()->ResetColor();
            }
            return;
        }
    } else {
        if (!ParseJsColor(info[0], progressColor)) {
            if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
                LoadingProgressModel::GetInstance()->SetForegroundColorParseFailed(true);
                LoadingProgressModel::GetInstance()->ResetColor();
            }
            return;
        }
        LoadingProgressModel::GetInstance()->SetForegroundColorParseFailed(false);
        LoadingProgressModel::GetInstance()->SetColor(progressColor);
    }
}

void JSLoadingProgress::SetEnableLoading(const JSCallbackInfo& info)
{
    bool enable = true;
    if (info[0]->IsBoolean()) {
        enable = info[0]->ToBoolean();
    }
    LoadingProgressModel::GetInstance()->SetEnableLoading(enable);
}
}; // namespace OHOS::Ace::Framework
