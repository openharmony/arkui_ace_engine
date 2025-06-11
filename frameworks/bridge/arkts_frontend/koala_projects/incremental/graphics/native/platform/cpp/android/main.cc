/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include <android_native_app_glue.h>
#include <cpu-features.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <cerrno>
#include <unistd.h>
#include <dlfcn.h>

#include <GLES/gl.h>
#include <EGL/egl.h>

#include <uv.h>
#include <node.h>

#include "skoala-interop.h"
#include "node-interop.h"
#include "assets-loader.h"
#include "logdefs.h"
#include "engine.h"

static int engine_handle_input(android_app *app, AInputEvent *event) {
    auto engine = (Engine *) app->userData;
    return engine->handleInput(event);
}

static void engine_handle_cmd(android_app *app, int32_t cmd) {
    auto engine = (Engine *) app->userData;
    engine->handleCommand(cmd);
}

void android_main(struct android_app *state) {
    // Logger redirecting stdout to logcat.
    start_logger("koala");
    struct timeval tv;
    gettimeofday(&tv, NULL);

    LOGI_ANDROID("Koala activity started: %ld%ld", tv.tv_sec, tv.tv_usec/1000);

    Engine engine(state);

    state->userData = &engine;
    state->onAppCmd = engine_handle_cmd;
    state->onInputEvent = engine_handle_input;

    auto nativeActivity = state->activity;
    AssetsLoader al(nativeActivity->assetManager, nativeActivity->internalDataPath);

    bool resourcesReady = al.syncFiles();
    if (resourcesReady && engine.initNode()) {
        auto startScript = std::string (nativeActivity->internalDataPath) + "/js/index.js";
        std::vector<std::string> errors;
        engine.prepareNode(errors, startScript);
        // TODO: log `errors`.
    } else {
        LOGE_ANDROID("Cannot start Koala app: %s", resourcesReady ? "cannot init JS VM" : "cannot sync resources");
        return;
    }

    // loop waiting for stuff to do.
    while (true) {
        // Read all pending events.
        int events;
        struct android_poll_source *source;

        engine.runNode();

        // If not animating, we will block forever waiting for events.
        // If animating, we loop until all events are read, then continue
        // to draw the next frame of animation.
        while (ALooper_pollAll(0, nullptr, &events, (void**)&source) >= 0) {
            // Process this event.
            if (source) {
                source->process(state, source);
            }
            // Check if we are exiting.
            if (state->destroyRequested != 0) {
                LOGE_ANDROID("Engine thread destroy requested!");
                engine.deinit();
                exit(0);
            }
        }
    }
}