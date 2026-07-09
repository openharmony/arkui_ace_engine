/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cstdint>
#include <js_native_api_types.h>
#include "plugin_render.h"

namespace NativeXComponentSample {

PluginRender::PluginRender(int64_t& id)
{
    this->id_ = id;
    this->eglCore_ = new EGLCore();
    hasDraw_ = 0;
    hasChangeColor_ = 0;
}
// [Start xcomponent_render_cpp]
void PluginRender::ChangeColor()
{
    eglCore_->ChangeColor(hasChangeColor_);
}

void PluginRender::DrawPattern()
{
    eglCore_->Draw(hasDraw_); // 参考Native XComponent场景Draw实现
}

void PluginRender::InitNativeWindow(OHNativeWindow *window)
{
    eglCore_->EglContextInit(window); // 参考Native XComponent场景EglContextInit的实现
}

void PluginRender::UpdateNativeWindowSize(int width, int height)
{
    eglCore_->UpdateSize(width, height); // 参考Native XComponent场景UpdateSize的实现
    if (!hasChangeColor_ && !hasDraw_) {
        eglCore_->Background(); // 参考Native XComponent场景Background的实现
    }
}

int32_t PluginRender::HasDraw()
{
    return hasDraw_;
}

int32_t PluginRender::HasChangedColor()
{
    return hasChangeColor_;
}
// [End xcomponent_render_cpp]
} // namespace NativeXComponentSample
