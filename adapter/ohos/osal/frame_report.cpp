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

#include "base/log/frame_report.h"

#include <dlfcn.h>
#include <frame_collector.h>

#include "base/utils/utils.h"

namespace OHOS::Ace {
namespace {
const std::string FRAME_AWARE_SO_PATH = "libframe_ui_intf.z.so";
} // namespace
FrameReport& FrameReport::GetInstance()
{
    static FrameReport instance;
    return instance;
}

FrameReport::FrameReport() {}

FrameReport::~FrameReport()
{
    CloseLibrary();
}

bool FrameReport::LoadLibrary()
{
    if (!frameSchedSoLoaded_) {
        frameSchedHandle_ = dlopen(FRAME_AWARE_SO_PATH.c_str(), RTLD_LAZY);
        CHECK_NULL_RETURN(frameSchedHandle_, false);
        frameInitFunc_ = (FrameInitFunc)LoadSymbol("Init");
        CHECK_NULL_RETURN(frameInitFunc_, false);
        frameGetEnableFunc_ = (FrameGetEnableFunc)LoadSymbol("GetSenseSchedEnable");
        CHECK_NULL_RETURN(frameGetEnableFunc_, false);
        beginFlushAnimationFunc_ = (BeginFlushAnimationFunc)LoadSymbol("BeginFlushAnimation");
        CHECK_NULL_RETURN(beginFlushAnimationFunc_, false);
        endFlushAnimationFunc_ = (EndFlushAnimationFunc)LoadSymbol("EndFlushAnimation");
        CHECK_NULL_RETURN(endFlushAnimationFunc_, false);
        beginFlushBuildFunc_ = (BeginFlushBuildFunc)LoadSymbol("BeginFlushBuild");
        CHECK_NULL_RETURN(beginFlushBuildFunc_, false);
        endFlushBuildFunc_ = (EndFlushBuildFunc)LoadSymbol("EndFlushBuild");
        CHECK_NULL_RETURN(endFlushBuildFunc_, false);
        beginFlushLayoutFunc_ = (BeginFlushLayoutFunc)LoadSymbol("BeginFlushLayout");
        CHECK_NULL_RETURN(beginFlushLayoutFunc_, false);
        endFlushLayoutFunc_ = (EndFlushLayoutFunc)LoadSymbol("EndFlushLayout");
        CHECK_NULL_RETURN(endFlushLayoutFunc_, false);
        beginFlushRenderFunc_ = (BeginFlushRenderFunc)LoadSymbol("BeginFlushRender");
        CHECK_NULL_RETURN(beginFlushRenderFunc_, false);
        endFlushRenderFunc_ = (EndFlushRenderFunc)LoadSymbol("EndFlushRender");
        CHECK_NULL_RETURN(endFlushRenderFunc_, false);
        beginFlushRenderFinishFunc_ = (BeginFlushRenderFinishFunc)LoadSymbol("BeginFlushRenderFinish");
        CHECK_NULL_RETURN(beginFlushRenderFinishFunc_, false);
        endFlushRenderFinishFunc_ = (EndFlushRenderFinishFunc)LoadSymbol("EndFlushRenderFinish");
        CHECK_NULL_RETURN(endFlushRenderFinishFunc_, false);
        beginProcessPostFunc_ = (BeginProcessPostFlushFunc)LoadSymbol("BeginProcessPostFlush");
        CHECK_NULL_RETURN(beginProcessPostFunc_, false);
        beginListFlingFunc_ = (BeginListFlingFunc)LoadSymbol("BeginListFling");
        CHECK_NULL_RETURN(beginListFlingFunc_, false);
        endListFlingFunc_ = (EndListFlingFunc)LoadSymbol("EndListFling");
        CHECK_NULL_RETURN(endListFlingFunc_, false);
        flushBeginFunc_ = (FlushBeginFunc)LoadSymbol("FlushBegin");
        CHECK_NULL_RETURN(flushBeginFunc_, false);
        flushEndFunc_ = (FlushEndFunc)LoadSymbol("FlushEnd");
        CHECK_NULL_RETURN(flushEndFunc_, false);
        setFrameParamFunc_ = (SetFrameParamFunc)LoadSymbol("SetFrameParam");
        CHECK_NULL_RETURN(setFrameParamFunc_, false);
        enableSelfRenderFunc_ = (EnableSelfRenderFunc)LoadSymbol("EnableSelfRender");
        CHECK_NULL_RETURN(enableSelfRenderFunc_, false);
        disableSelfRenderFunc_ = (DisableSelfRenderFunc)LoadSymbol("DisableSelfRender");
        CHECK_NULL_RETURN(disableSelfRenderFunc_, false);
        frameSchedSoLoaded_ = true;
    }
    return true;
}

void FrameReport::CloseLibrary()
{
    if (dlclose(frameSchedHandle_) != 0) {
        LOGE("frame-ace:[CloseLibrary]libframe_ui_intf.so failed!\n");
        return;
    }
    frameSchedHandle_ = nullptr;
    frameSchedSoLoaded_ = false;
}

void* FrameReport::LoadSymbol(const char* symName)
{
    CHECK_NULL_RETURN(frameSchedHandle_, nullptr);
    return dlsym(frameSchedHandle_, symName);
}

void FrameReport::Init()
{
    if (LoadLibrary()) {
        frameInitFunc_();
        enable_ = frameGetEnableFunc_() != 0;
    }
}

int FrameReport::GetEnable()
{
    return true;
}

int FrameReport::GetFrameReportEnable()
{
    if (!frameSchedSoLoaded_) {
        return 0;
    }
    return frameGetEnableFunc_();
}

void FrameReport::BeginFlushAnimation()
{
    Rosen::FrameCollector::GetInstance().MarkFrameEvent(Rosen::FrameEventType::AnimateStart);
    if (!enable_) {
        return;
    }
    beginFlushAnimationFunc_();
}

void FrameReport::EndFlushAnimation()
{
    Rosen::FrameCollector::GetInstance().MarkFrameEvent(Rosen::FrameEventType::AnimateEnd);
    if (!enable_) {
        return;
    }
    endFlushAnimationFunc_();
}

void FrameReport::BeginFlushBuild()
{
    Rosen::FrameCollector::GetInstance().MarkFrameEvent(Rosen::FrameEventType::BuildStart);
    if (!enable_) {
        return;
    }
    beginFlushBuildFunc_();
}

void FrameReport::EndFlushBuild()
{
    Rosen::FrameCollector::GetInstance().MarkFrameEvent(Rosen::FrameEventType::BuildEnd);
    if (!enable_) {
        return;
    }
    endFlushBuildFunc_();
}

void FrameReport::BeginFlushLayout()
{
    Rosen::FrameCollector::GetInstance().MarkFrameEvent(Rosen::FrameEventType::LayoutStart);
    if (!enable_) {
        return;
    }
    beginFlushLayoutFunc_();
}

void FrameReport::EndFlushLayout()
{
    Rosen::FrameCollector::GetInstance().MarkFrameEvent(Rosen::FrameEventType::LayoutEnd);
    if (!enable_) {
        return;
    }
    endFlushLayoutFunc_();
}

void FrameReport::BeginFlushRender()
{
    Rosen::FrameCollector::GetInstance().MarkFrameEvent(Rosen::FrameEventType::DrawStart);
    if (!enable_) {
        return;
    }
    beginFlushRenderFunc_();
}

void FrameReport::EndFlushRender()
{
    if (!enable_) {
        return;
    }
    endFlushRenderFunc_();
}

void FrameReport::BeginFlushRenderFinish()
{
    if (!enable_) {
        return;
    }
    beginFlushRenderFinishFunc_();
}

void FrameReport::EndFlushRenderFinish()
{
    Rosen::FrameCollector::GetInstance().MarkFrameEvent(Rosen::FrameEventType::DrawEnd);
    if (!enable_) {
        return;
    }
    endFlushRenderFinishFunc_();
}

void FrameReport::BeginProcessPostFlush()
{
    if (!enable_) {
        return;
    }
    beginProcessPostFunc_();
}

void FrameReport::BeginListFling()
{
    if (!enable_) {
        return;
    }
    beginListFlingFunc_();
}

void FrameReport::EndListFling()
{
    if (!enable_) {
        return;
    }
    endListFlingFunc_();
}

void FrameReport::FlushBegin()
{
    if (!enable_) {
        return;
    }
    flushBeginFunc_();
}

void FrameReport::FlushEnd()
{
    if (!enable_) {
        return;
    }
    flushEndFunc_();
}

void FrameReport::SetFrameParam(int requestId, int load, int schedFrameNum, int value)
{
    if (!enable_) {
        return;
    }
    setFrameParamFunc_(requestId, load, schedFrameNum, value);
}

void FrameReport::EnableSelfRender()
{
    if (!enable_) {
        return;
    }
    enableSelfRenderFunc_();
}

void FrameReport::DisableSelfRender()
{
    if (!enable_) {
        return;
    }
    disableSelfRenderFunc_();
}
} // namespace OHOS::Ace
