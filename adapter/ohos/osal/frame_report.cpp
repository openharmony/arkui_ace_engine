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

#include <cstdio>
#include <dlfcn.h>
#include <unistd.h>

#include <frame_collector.h>

#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"

namespace OHOS::Ace {
namespace {
#ifdef __aarch64__
    const std::string FRAME_AWARE_SO_PATH = "/system/lib64/libframe_ui_intf.z.so";
#else
    const std::string FRAME_AWARE_SO_PATH = "/system/lib/libframe_ui_intf.z.so";
#endif
}
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
        frameSchedSoLoaded_ = true;
    }
    LOGD("frame-ace:[LoadLibrary]dlopen libframe_ui_intf.so success");
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
    LOGD("frame-ace:[CloseLibrary]libframe_ui_intf.so close success!\n");
}

void *FrameReport::LoadSymbol(const char *symName)
{
    CHECK_NULL_RETURN(frameSchedSoLoaded_, nullptr);

    void *funcSym = dlsym(frameSchedHandle_, symName);
    CHECK_NULL_RETURN(funcSym, nullptr);
    return funcSym;
}

void FrameReport::Init()
{
    LoadLibrary();
    frameInitFunc_ = (FrameInitFunc)LoadSymbol("Init");
    CHECK_NULL_VOID(frameInitFunc_);
    frameInitFunc_();
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
    frameGetEnableFunc_ = (FrameGetEnableFunc)LoadSymbol("GetSenseSchedEnable");
    CHECK_NULL_RETURN(frameGetEnableFunc_, 0);
    return frameGetEnableFunc_();
}

void FrameReport::BeginFlushAnimation()
{
    Rosen::FrameCollector::GetInstance().MarkFrameEvent(Rosen::FrameEventType::AnimateStart);
    if (GetFrameReportEnable() == 0) {
        return;
    }
    beginFlushAnimationFunc_ = (BeginFlushAnimationFunc)LoadSymbol("BeginFlushAnimation");
    CHECK_NULL_VOID(beginFlushAnimationFunc_);
    beginFlushAnimationFunc_();
}

void FrameReport::EndFlushAnimation()
{
    Rosen::FrameCollector::GetInstance().MarkFrameEvent(Rosen::FrameEventType::AnimateEnd);
    if (GetFrameReportEnable() == 0) {
        return;
    }
    endFlushAnimationFunc_ = (EndFlushAnimationFunc)LoadSymbol("EndFlushAnimation");
    CHECK_NULL_VOID(endFlushAnimationFunc_);
    endFlushAnimationFunc_();
}

void FrameReport::BeginFlushBuild()
{
    Rosen::FrameCollector::GetInstance().MarkFrameEvent(Rosen::FrameEventType::BuildStart);
    if (GetFrameReportEnable() == 0) {
        return;
    }
    beginFlushBuildFunc_ = (BeginFlushBuildFunc)LoadSymbol("BeginFlushBuild");
    CHECK_NULL_VOID(beginFlushBuildFunc_);
    beginFlushBuildFunc_();
}

void FrameReport::EndFlushBuild()
{
    Rosen::FrameCollector::GetInstance().MarkFrameEvent(Rosen::FrameEventType::BuildEnd);
    if (GetFrameReportEnable() == 0) {
        return;
    }
    endFlushBuildFunc_ = (EndFlushBuildFunc)LoadSymbol("EndFlushBuild");
    CHECK_NULL_VOID(endFlushBuildFunc_);
    endFlushBuildFunc_();
}

void FrameReport::BeginFlushLayout()
{
    Rosen::FrameCollector::GetInstance().MarkFrameEvent(Rosen::FrameEventType::LayoutStart);
    if (GetFrameReportEnable() == 0) {
        return;
    }
    beginFlushLayoutFunc_ = (BeginFlushLayoutFunc)LoadSymbol("BeginFlushLayout");
    CHECK_NULL_VOID(beginFlushLayoutFunc_);
    beginFlushLayoutFunc_();
}

void FrameReport::EndFlushLayout()
{
    Rosen::FrameCollector::GetInstance().MarkFrameEvent(Rosen::FrameEventType::LayoutEnd);
    if (GetFrameReportEnable() == 0) {
        return;
    }
    endFlushLayoutFunc_ = (EndFlushLayoutFunc)LoadSymbol("EndFlushLayout");
    CHECK_NULL_VOID(endFlushLayoutFunc_);
    endFlushLayoutFunc_();
}

void FrameReport::BeginFlushRender()
{
    Rosen::FrameCollector::GetInstance().MarkFrameEvent(Rosen::FrameEventType::DrawStart);
    if (GetFrameReportEnable() == 0) {
        return;
    }
    beginFlushRenderFunc_ = (BeginFlushRenderFunc)LoadSymbol("BeginFlushRender");
    CHECK_NULL_VOID(beginFlushRenderFunc_);
    beginFlushRenderFunc_();
}

void FrameReport::EndFlushRender()
{
    if (GetFrameReportEnable() == 0) {
        return;
    }
    endFlushRenderFunc_ = (EndFlushRenderFunc)LoadSymbol("EndFlushRender");
    CHECK_NULL_VOID(endFlushRenderFunc_);
    endFlushRenderFunc_();
}

void FrameReport::BeginFlushRenderFinish()
{
    if (GetFrameReportEnable() == 0) {
        return;
    }
    beginFlushRenderFinishFunc_ = (BeginFlushRenderFinishFunc)LoadSymbol("BeginFlushRenderFinish");
    CHECK_NULL_VOID(beginFlushRenderFinishFunc_);
    beginFlushRenderFinishFunc_();
}

void FrameReport::EndFlushRenderFinish()
{
    Rosen::FrameCollector::GetInstance().MarkFrameEvent(Rosen::FrameEventType::DrawEnd);
    if (GetFrameReportEnable() == 0) {
        return;
    }
    endFlushRenderFinishFunc_ = (EndFlushRenderFinishFunc)LoadSymbol("EndFlushRenderFinish");
    CHECK_NULL_VOID(endFlushRenderFinishFunc_);
    endFlushRenderFinishFunc_();
}

void FrameReport::BeginProcessPostFlush()
{
    if (GetFrameReportEnable() == 0) {
        return;
    }
    beginProcessPostFunc_ = (BeginProcessPostFlushFunc)LoadSymbol("BeginProcessPostFlush");
    CHECK_NULL_VOID(beginProcessPostFunc_);
    beginProcessPostFunc_();
}

void FrameReport::BeginListFling()
{
    if (GetFrameReportEnable() == 0) {
        return;
    }
    beginListFlingFunc_ = (BeginListFlingFunc)LoadSymbol("BeginListFling");
    CHECK_NULL_VOID(beginListFlingFunc_);
    beginListFlingFunc_();
}

void FrameReport::EndListFling()
{
    if (GetFrameReportEnable() == 0) {
        return;
    }
    endListFlingFunc_ = (EndListFlingFunc)LoadSymbol("EndListFling");
    CHECK_NULL_VOID(beginListFlingFunc_);
    endListFlingFunc_();
}

void FrameReport::FlushBegin()
{
    if (GetFrameReportEnable() == 0) {
        return;
    }
    flushBeginFunc_ = (FlushBeginFunc)LoadSymbol("FlushBegin");
    CHECK_NULL_VOID(flushBeginFunc_);
    flushBeginFunc_();
}

void FrameReport::FlushEnd()
{
    if (GetFrameReportEnable() == 0) {
        return;
    }
    flushEndFunc_ = (FlushEndFunc)LoadSymbol("FlushEnd");
    CHECK_NULL_VOID(flushEndFunc_);
    flushEndFunc_();
}
} // namespace OHOS::Ace
