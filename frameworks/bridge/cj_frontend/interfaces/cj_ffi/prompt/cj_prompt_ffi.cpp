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

#include "cj_prompt_ffi.h"


#include "cj_lambda.h"
#include "bridge/cj_frontend/frontend/cj_frontend_abstract.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace {
const int32_t SHOW_DIALOG_BUTTON_NUM_MAX = 3;
const int32_t SHOW_ACTION_MENU_BUTTON_NUM_MAX = 6;
const std::vector<DialogAlignment> DIALOG_ALIGNMENT = { DialogAlignment::TOP, DialogAlignment::CENTER,
    DialogAlignment::BOTTOM, DialogAlignment::DEFAULT, DialogAlignment::TOP_START, DialogAlignment::TOP_END,
    DialogAlignment::CENTER_START, DialogAlignment::CENTER_END, DialogAlignment::BOTTOM_START,
    DialogAlignment::BOTTOM_END };

RefPtr<OHOS::Ace::CJFrontendAbstract> CheckFrontendLegality(int32_t size, CButtonInfo* buttonsInfo)
{
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(Utils::GetCurrentFrontend());
    if (!frontend) {
        LOGE("Can not get frontend.");
        return nullptr;
    }
    if (size < 0 || buttonsInfo == nullptr) {
        LOGE("Invalid buttons info");
        return nullptr;
    }
    return frontend;
}

std::vector<ButtonInfo> CreateButtonInfoVector(CButtonInfo* buttonsInfo, int32_t size, int32_t numMax)
{
    std::vector<ButtonInfo> buttons;
    if (size > numMax) {
        size = numMax;
        LOGE("Supports 1 - %{public}d buttons", numMax);
    }
    for (int i = 0; i < size; ++i) {
        auto curInfo = buttonsInfo + i;
        ButtonInfo button { .text = curInfo->text, .textColor = Color(curInfo->textColor).ColorToString() };
        buttons.emplace_back(button);
    }
    return buttons;
}
} // namespace

extern "C" {
void* FfiPromptMallocButtons(int64_t size)
{
    if (size <= 0) {
        return nullptr;
    }

    CButtonInfo* pButton = static_cast<CButtonInfo*>(malloc(sizeof(CButtonInfo) * size));
    if (pButton == nullptr) {
        printf("Fail to malloc pButton.");
        return nullptr;
    }
    return pButton;
}

void FfiPromptShowToast(const char* message, int32_t duration, const char* bottom, int32_t mode)
{
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(Utils::GetCurrentFrontend());
    if (!frontend) {
        LOGE("Can not get frontend.");
        return;
    }
    frontend->ShowToast(message, duration, bottom, NG::ToastShowMode(mode));
}

void FfiPromptShowDialog(const char* title, const char* message, int32_t size,
    CButtonInfo* buttonsInfo, ShowDialogCallBack callbackRef)
{
    auto frontend = CheckFrontendLegality(size, buttonsInfo);
    if (!frontend) {
        return;
    }
    std::vector<ButtonInfo> buttons = CreateButtonInfoVector(buttonsInfo, size, SHOW_DIALOG_BUTTON_NUM_MAX);
    std::set<std::string> callbacks;
    callbacks.emplace("success");
    callbacks.emplace("cancel");

    auto callback = [ffiOnClick = CJLambda::Create(callbackRef)](
        int32_t callbackType, int32_t successType) { ffiOnClick(callbackType, successType); };
    frontend->ShowDialog(title, message, buttons, std::move(callback), callbacks);
}

void FfiPromptShowActionMenu(
    const char* title, int32_t size, CButtonInfo* buttonsInfo, ShowActionMenuCallBack callbackRef)
{
    auto frontend = CheckFrontendLegality(size, buttonsInfo);
    if (!frontend) {
        return;
    }
    std::vector<ButtonInfo> buttons = CreateButtonInfoVector(buttonsInfo, size, SHOW_ACTION_MENU_BUTTON_NUM_MAX);
    auto callback = [ffiOnClick = CJLambda::Create(callbackRef)](
                        int callbackType, int successType) { ffiOnClick(callbackType, successType); };
    frontend->ShowActionMenu(title, buttons, std::move(callback));
}

void FfiPromptOpenCustomDialog(void(*builder)(), NativeBaseOption options, void(*callback)(int32_t))
{
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(Utils::GetCurrentFrontend());
    if (!frontend) {
        LOGE("Can not get frontend.");
        return;
    }

    auto builderFunc = [func = CJLambda::Create(builder)]() {
        func();
    };
    auto callbackFunc = [func = CJLambda::Create(callback)](int32_t customId) {
        func(customId);
    };

    std::function<void(const int32_t& info)> onWillDismiss = nullptr;

    auto alignment = DIALOG_ALIGNMENT[options.alignment];

    // parse maskRect
    Dimension xDimen = Dimension(options.maskRect.x, static_cast<DimensionUnit>(options.maskRect.xUnit));
    Dimension yDimen = Dimension(options.maskRect.y, static_cast<DimensionUnit>(options.maskRect.yUnit));
    Dimension widthDimen =
        Dimension(options.maskRect.width, static_cast<DimensionUnit>(options.maskRect.widthUnit));
    Dimension heightDimen =
        Dimension(options.maskRect.height, static_cast<DimensionUnit>(options.maskRect.heightUnit));
    DimensionOffset offsetDimen(xDimen, yDimen);
    auto maskRect = DimensionRect(widthDimen, heightDimen, offsetDimen);

    // parse offset
    double dxVal = options.offset.dx.value;
    int32_t dxType = options.offset.dx.unitType;
    CalcDimension dx = CalcDimension(dxVal, static_cast<DimensionUnit>(dxType));
    double dyVal = options.offset.dy.value;
    int32_t dyType = options.offset.dy.unitType;
    CalcDimension dy = CalcDimension(dyVal, static_cast<DimensionUnit>(dyType));
    auto offset = DimensionOffset(dx, dy);

    PromptDialogAttr promptDialogAttr = {
        .showInSubWindow = options.showInSubWindow,
        .isModal = options.isModal,
        .customBuilder = std::move(builderFunc),
        .customOnWillDismiss = std::move(onWillDismiss),
        .alignment = alignment,
        .offset = offset,
        .maskRect = maskRect,
    };

    frontend->OpenCustomDialog(promptDialogAttr, std::move(callbackFunc));
}

void FfiPromptCloseCustomDialog(int32_t id)
{
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(Utils::GetCurrentFrontend());
    if (!frontend) {
        LOGE("Can not get frontend.");
        return;
    }

    frontend->CloseCustomDialog(id);
}
}
