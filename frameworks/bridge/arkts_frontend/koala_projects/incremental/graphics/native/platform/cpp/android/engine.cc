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

#include "engine.h"
#include <android/input.h>
#include <jni.h>
#include <stdio.h>
#include <algorithm>
#include <iterator>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "logdefs.h"

Engine* applicationEngine = nullptr;

static void type_event_cb(Engine* engine, void* ctx) {
    InputTextEventState* state = (InputTextEventState*)ctx;
    engine->peer->callOnTextInput(state->type, state->cursorPosition, state->characters);
    delete state;
}

static void key_event_cb(Engine* engine, void* ctx) {
    InputKeyEventState* state = (InputKeyEventState*)ctx;
    engine->peer->callOnKey(state->key, state->modifiers, state->action);
    delete state;
}

static void permissions_event_cb(Engine* engine, void* ctx) {
    PermissionGrantedEventState* state = (PermissionGrantedEventState*)ctx;
    engine->peer->callPermissionGranted(state->requestCode, state->permissions, state->grantResults);
    delete state;
}


void Engine::callOnUIThread(engine_callback_t cb, void* state) {
    locker.lock();
    cb_queue.push_back(std::make_pair(cb, state));
    locker.unlock();
}

void Engine::processQueue() {
    locker.lock();
    while (cb_queue.size() > 0) {
        auto element = cb_queue.front();
        cb_queue.pop_front();
        locker.unlock();
        element.first(this, element.second);
        locker.lock();
    }
    locker.unlock();
}

std::string toStdString(JNIEnv *env, jstring jStr) {
    if (!jStr)
        return "";

    const jclass stringClass = env->GetObjectClass(jStr);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray bytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes, env->NewStringUTF("UTF-8"));

    size_t length = (size_t) env->GetArrayLength(bytes);
    jbyte* pBytes = env->GetByteArrayElements(bytes, NULL);

    std::string ret = std::string((char *)pBytes, length);
    env->ReleaseByteArrayElements(bytes, pBytes, JNI_ABORT);

    env->DeleteLocalRef(bytes);
    env->DeleteLocalRef(stringClass);
    return ret;
}

extern "C" JNIEXPORT void JNICALL Java_ohos_koala_InputProxy_sendType(
        JNIEnv* env, jobject obj, jint type, jint cursor_start, jstring characters) {
    auto* engine = applicationEngine;
    if (engine != nullptr) {
        engine->callOnUIThread(
            type_event_cb,
            new InputTextEventState(type, cursor_start, toStdString(env, characters))
        );
    }
}

extern "C" JNIEXPORT void JNICALL Java_ohos_koala_InputProxy_sendKey(
        JNIEnv* env, jobject obj, jint key, jint modifiers, jint action) {
    auto* engine = applicationEngine;
    if (engine != nullptr) {
        int type = (action == AKEY_EVENT_ACTION_UP) ? 0 : 1;
        engine->callOnUIThread(key_event_cb,new InputKeyEventState(key, modifiers, type));
    }
}

extern "C" JNIEXPORT void JNICALL Java_ohos_koala_RequestHandler_sendPermissionsInfo(
        JNIEnv* env, jobject obj, jint requestCode, jobjectArray permissions, jintArray grantResults) {
    auto* engine = applicationEngine;
    if (engine != nullptr) {
        jint arrayLength = env->GetArrayLength(permissions);
        auto results = env->GetIntArrayElements(grantResults, JNI_FALSE);

        std::vector<std::string> perms(arrayLength);
        std::vector<int> vgrantResults(arrayLength);

        for (auto i=0; i<arrayLength; i++) {
            jstring obj = (jstring) env->GetObjectArrayElement(permissions, i);
            perms[i] =  env->GetStringUTFChars(obj, JNI_FALSE);
            vgrantResults[i] = results[i];
            env->DeleteLocalRef(obj);
        }

        engine->callOnUIThread(permissions_event_cb,new PermissionGrantedEventState(requestCode, perms, vgrantResults));
    }
}

Engine::Engine(android_app *app) {
    this->app = app;
    androidCpuFamily = android_getCpuFamily();
    canDraw = 0;
    display = nullptr;
    surface = nullptr;
    context = nullptr;
    density = 0.0f;
    peer = nullptr;
    savedState.index = 0;
    vibrationEffectClass = nullptr;
    vibratorInstance = nullptr;
    vibrateWithDurationMethod = nullptr;
    vibrateWithEffectMethod = nullptr;
    createPredefinedEffectMethod = nullptr;
    applicationEngine = this;
}

void Engine::softKeyboard(bool show) {
    if (!checkJniBridge()) {
        return;
    }

    auto* nativeActivity = jniBridge->getObjectClass(app->activity->clazz);
    auto* viewKeyboardMethod = jniBridge->getMethodID(nativeActivity, "keyboard", "(Z)V");
    jniBridge->callVoidMethod(app->activity->clazz, viewKeyboardMethod, show);
}

void Engine::globalPointer(int32_t &x, int32_t &y) {
    if (!checkJniBridge()) {
        return;
    }
    auto* nativeActivity = jniBridge->getObjectClass(app->activity->clazz);
    auto* method = jniBridge->getMethodID(nativeActivity, "getMousePointer", "()[F");
    jfloatArray javaArray = (jfloatArray)jniBridge->callObjectMethod(app->activity->clazz, method);
    jfloat* array = jniBridge->getFloatArrayElement(javaArray);
    x = (int)array[0];
    y = (int)array[1];
}

void Engine::commitInput() {
    if (!checkJniBridge()) {
        return;
    }

    auto* nativeActivity = jniBridge->getObjectClass(app->activity->clazz);
    auto* commitInputMethod = jniBridge->getMethodID(nativeActivity, "commitInput", "()V");
    jniBridge->callVoidMethod(app->activity->clazz, commitInputMethod);
}

jstring Engine::androidPermissionName(const char* perm_name) {
    jclass manifestPermissionClass = jniBridge->findClass(
       "android/Manifest$permission"
    );
    jfieldID actualPermission = jniBridge->getStaticFieldID(
       manifestPermissionClass, perm_name, "Ljava/lang/String;"
    );

    jstring actualPermissionString = (jstring)(jniBridge->getStaticObjectField(
        manifestPermissionClass, actualPermission
    ));
    return actualPermissionString;
}

bool Engine::androidExistPermission(const char *perm_name) {
    jclass manifestPermissionClass = jniBridge->findClass(
       "android/Manifest$permission"
    );
    jfieldID actualPermission = jniBridge->getStaticFieldID(
       manifestPermissionClass, perm_name, "Ljava/lang/String;"
    );

    if (!actualPermission) {
        jniBridge->check();
        return false;
    }

    return true;
}

bool Engine::androidHasPermission(const char* perm_name) {
    bool result = false;

    jstring actualPermissionString = androidPermissionName(perm_name);

    jint PERMISSION_GRANTED = -1;
    jclass packageManagerClass = jniBridge->findClass(
        "android/content/pm/PackageManager"
    );
    jfieldID permissionGrantedField = jniBridge->getStaticFieldID(
        packageManagerClass, "PERMISSION_GRANTED", "I"
    );
    PERMISSION_GRANTED = jniBridge->getStaticIntField(
        packageManagerClass, permissionGrantedField
    );
    jobject activity = app->activity->clazz;
    jclass contextClass = jniBridge->findClass(
        "android/content/Context"
    );
    jmethodID checkSelfPermissionMethod = jniBridge->getMethodID(
        contextClass, "checkSelfPermission", "(Ljava/lang/String;)I"
    );
    jint intResult = jniBridge->callIntMethod(
        activity, checkSelfPermissionMethod, actualPermissionString
    );
    result = (intResult == PERMISSION_GRANTED);

    return result;
}

void Engine::askPermissions(std::vector<std::string> &perms) {
    if (!checkJniBridge()) return;

    jclass stringClass = jniBridge->findClass("java/lang/String");
    jobjectArray permArray = jniBridge->makeArray(
    stringClass,
    perms.size(),
    jniBridge->makeString("")
    );

    for (int i = 0; i < perms.size(); i++) {
        jobject permString = androidPermissionName(perms[i].c_str());
        jniBridge->setArrayElement(
            permArray, i,
            permString
        );
    }

    jobject activity = app->activity->clazz;
    jclass classActivity = jniBridge->getObjectClass(app->activity->clazz);
    jmethodID requestPermissionsMethod = jniBridge->getMethodID(
        classActivity, "requestPermissions", "([Ljava/lang/String;I)V"
    );

    jniBridge->callVoidMethod(
    activity, requestPermissionsMethod, permArray, 0
    );
}

bool Engine::initNode() {
    if (androidCpuFamily != ANDROID_CPU_FAMILY_ARM64 && androidCpuFamily != ANDROID_CPU_FAMILY_X86_64) {
        LOGE("Unsupported CPU, cannot run node.js!");
        return false;
    }
    nodeRuntime = std::make_unique<NodeRuntime>();
#ifdef KOALA_USE_PROFILE
    bool inspect = true;
#else
    bool inspect = false;
#endif
    if (!nodeRuntime->init(inspect)) {
        nodeRuntime.reset();
        LOGE("Cannot initialize node.js runtime");
        return false;
    }
    nodeScopedState = std::make_unique<NodeScopedState>(nodeRuntime->setup);
    return true;
}

void Engine::deinitNode() {
    canDraw = 0;
    nodeScopedState.reset();
}

void Engine::runNode() {
    if (!canDraw || !nodeRuntime) return;
    uv_run(nodeRuntime->setup->event_loop(), UV_RUN_NOWAIT);
    nodeRuntime->platform->DrainTasks(nodeScopedState->isolate);
}

/* TODO: make native function for that!
static int64_t timestamp() {
    struct timespec res = {0};
    clock_gettime(CLOCK_REALTIME, &res);
    return static_cast<int64_t>(1000.0 * res.tv_sec + (double) res.tv_nsec / 1e6);
} */

int Engine::initDisplay() {
    const EGLint attributes[] = {
                EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                EGL_BLUE_SIZE, 8,
                EGL_GREEN_SIZE, 8,
                EGL_RED_SIZE, 8,
                EGL_ALPHA_SIZE, 8,
                EGL_CONFORMANT, EGL_OPENGL_ES2_BIT,
                EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
                EGL_NONE
        };
    EGLint format;
    EGLint numConfigs;
    EGLConfig config = nullptr;
    EGLSurface surface;
    EGLContext context;

    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(display, nullptr, nullptr);

    /* Here, the application chooses the configuration it desires.
     * find the best match if possible, otherwise use the very first one
     */
    eglChooseConfig(display, attributes, nullptr, 0, &numConfigs);
    std::unique_ptr<EGLConfig[]> supportedConfigs(new EGLConfig[numConfigs]);
    assert(supportedConfigs);
    eglChooseConfig(display, attributes, supportedConfigs.get(), numConfigs, &numConfigs);
    assert(numConfigs);
    auto i = 0;
    for (; i < numConfigs; i++) {
        auto& cfg = supportedConfigs[i];
        EGLint r = 0, g = 0, b = 0, a = 0;
        if (eglGetConfigAttrib(display, cfg, EGL_RED_SIZE, &r)   &&
            eglGetConfigAttrib(display, cfg, EGL_GREEN_SIZE, &g) &&
            eglGetConfigAttrib(display, cfg, EGL_BLUE_SIZE, &b)  &&
            eglGetConfigAttrib(display, cfg, EGL_ALPHA_SIZE, &a)) {
            if (r == 8 && g == 8 && b == 8 && a == 8) {
                config = supportedConfigs[i];
                break;
            }
        }
    }
    if (i == numConfigs) {
        config = supportedConfigs[0];
    }

    if (config == nullptr) {
        LOGW_ANDROID("Unable to initialize EGLConfig");
        return -1;
    }

    /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
     * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
     * As soon as we picked a EGLConfig, we can safely reconfigure the
     * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

    //eglBindAPI(EGL_OPENGL_ES_API);
    surface = eglCreateWindowSurface(display, config, app->window, nullptr);
    EGLint contextAttribs[] = {
            EGL_CONTEXT_CLIENT_VERSION, 2,
            EGL_NONE
    };
    context = eglCreateContext(display, config, nullptr, contextAttribs);

    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
        LOGW_ANDROID("Unable to eglMakeCurrent");
        return -1;
    }

    physicalWidth = 0;
    physicalHeight = 0;
    eglQuerySurface(display, surface, EGL_WIDTH, &physicalWidth);
    eglQuerySurface(display, surface, EGL_HEIGHT, &physicalHeight);

    this->display = display;
    this->context = context;
    this->surface = surface;
    this->savedState.index = 0;

    // Check openGL on the system
    auto opengl_info = { GL_VENDOR, GL_RENDERER, GL_VERSION, GL_EXTENSIONS };
    for (auto name : opengl_info) {
        auto info = glGetString(name);
        LOGI_ANDROID("OpenGL Info: %s", info);
    }
    canDraw = 1;

    LOGE("Engine::initDisplay with %d x %d", physicalWidth, physicalHeight);

    return 0;
}

void Engine::deinitDisplay() {
    if (display != EGL_NO_DISPLAY) {
        eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (context != EGL_NO_CONTEXT) {
            eglDestroyContext(display, context);
        }
        if (surface != EGL_NO_SURFACE) {
            eglDestroySurface(display, surface);
        }
        eglTerminate(display);
    }
    display = EGL_NO_DISPLAY;
    context = EGL_NO_CONTEXT;
    surface = EGL_NO_SURFACE;

    canDraw = 0;
}

void Engine::resizeDisplay() {
    if (app->window) {
        physicalWidth = ANativeWindow_getWidth(app->window);
        physicalHeight = ANativeWindow_getHeight(app->window);
        int frameWidth = getFrameWidth();
        int frameHeight = getFrameHeight();
        LOGE("Engine::resizeDisplay %p %p %d x %d thiz=%p", peer, app->window, physicalWidth, physicalHeight, this);
        _pendingEvents.emplace_back(std::make_unique<Event>(Kind::RESIZE, frameWidth, frameHeight));
    }
}

int Engine::handleInput(AInputEvent *event) {
    auto type = AInputEvent_getType(event);
    int result = 0;

    switch (type) {
        case AINPUT_EVENT_TYPE_KEY: {
            if (peer && canDraw) {
                int action = AKeyEvent_getAction(event);
                int key = AKeyEvent_getKeyCode(event);
                int metaState = AKeyEvent_getMetaState(event);
                int character = getUnicodeChar(event);
                LOGI_ANDROID(
                    "Key event: action=%d keyCode=%d metaState=0x%x text:%d",
                    action,
                    key,
                    metaState,
                    character
                );
                switch(action) {
                    case AKEY_EVENT_ACTION_MULTIPLE: {
                        // TODO: some how we need to get characters from multi-staged keyboards
                        break;
                    }
                    case AKEY_EVENT_ACTION_DOWN: {
                        if (key == AKEYCODE_BACK) result = 1;
                        // 1 - key down event
                        _pendingEvents.emplace_back(std::make_unique<Event>(Kind::KEY, key, metaState, 1));
                        break;
                    }
                    case AKEY_EVENT_ACTION_UP: {
                        // 0 - key up event
                        _pendingEvents.emplace_back(std::make_unique<Event>(Kind::KEY, key, metaState, 0));
                        break;
                    }
                }
            }
            break;
        }

        case AINPUT_EVENT_TYPE_MOTION: {
            /* LOGI_ANDROID("Motion event: action=%d source=%d",
                    AMotionEvent_getAction(event),
                    AMotionEvent_getFlags(event)); */
            int action  = getCurrentAction(event);
            int count   = getPointersCount(event);
            int pointer = getCurrentPointerIndex(event);

            if (peer && canDraw) {
                auto pointerEvent = std::make_unique<Event>(Kind::TAP, count);
                pointerEvent->target = pointer;

                for (int i = 0; i < count; i++) {
                    pointerEvent->args1[i] = AMotionEvent_getX(event, i);
                    pointerEvent->args2[i] = AMotionEvent_getY(event, i);
                }

                maybeScaleVector(pointerEvent.get());

                switch(action) {
                    case AMOTION_EVENT_ACTION_POINTER_DOWN:
                    case AMOTION_EVENT_ACTION_DOWN: {
                        pointerEvent->arg3 = 1;
                        _pendingEvents.push_back(std::forward<std::unique_ptr<Event>>(pointerEvent));
                        break;
                    }
                    case AMOTION_EVENT_ACTION_POINTER_UP:
                    case AMOTION_EVENT_ACTION_UP: {
                        pointerEvent->arg3 = 0;
                        _pendingEvents.push_back(std::forward<std::unique_ptr<Event>>(pointerEvent));
                        break;
                    }
                    case AMOTION_EVENT_ACTION_MOVE: {
                        // TODO: gesture detection.
                        pointerEvent->kind = Kind::MOVE;
                        _pendingEvents.push_back(std::forward<std::unique_ptr<Event>>(pointerEvent));
                        break;
                    }
                }
            }
            break;
        }

        case AINPUT_EVENT_TYPE_FOCUS:
        default:
            break;
    }

    return result;
}


int Engine::getUnicodeChar(AInputEvent *event) {
    if (!checkJniBridge()) {
        return 0;
    }
    int unicodeKey;
    auto* class_key_event = jniBridge->findClass("android/view/KeyEvent");
    auto* eventConstructor = jniBridge->getMethodID(class_key_event, "<init>", "(JJIIIIIIII)V");
    auto* method_get_unicode_char = jniBridge->getMethodID(class_key_event, "getUnicodeChar", "(I)I");
    auto* eventObj = jniBridge->newObject(
        class_key_event,
        eventConstructor,
        AKeyEvent_getDownTime(event),
        AKeyEvent_getEventTime(event),
        AKeyEvent_getAction(event),
        AKeyEvent_getKeyCode(event),
        AKeyEvent_getRepeatCount(event),
        AKeyEvent_getMetaState(event),
        AInputEvent_getDeviceId(event),
        AKeyEvent_getScanCode(event),
        AKeyEvent_getFlags(event),
        AInputEvent_getSource(event)
    );

    unicodeKey = jniBridge->callIntMethod(eventObj, method_get_unicode_char, AKeyEvent_getMetaState(event));

    return unicodeKey;
}

void Engine::handleCommand(int command)
{
    // LOGE("command %d arrived", command);
    switch (command)
    {
    case APP_CMD_INPUT_CHANGED:
        LOGE("APP_CMD_INPUT_CHANGED");
        break;
    case APP_CMD_INIT_WINDOW:
        LOGE("APP_CMD_INIT_WINDOW: %p", app->window);
        if (app->window) {
            initDisplay();
        }
        _pendingEvents.emplace_back(std::make_unique<Event>(Kind::INIT));
        break;
    case APP_CMD_TERM_WINDOW:
        LOGE("APP_CMD_TERM_WINDOW");
        deinitDisplay();
        _pendingEvents.emplace_back(std::make_unique<Event>(Kind::DEINIT));
        break;
    case APP_CMD_GAINED_FOCUS:
        LOGE("APP_CMD_GAINED_FOCUS");
        canDraw = 1;
        _pendingEvents.emplace_back(std::make_unique<Event>(Kind::FOCUS));
        break;
    case APP_CMD_LOST_FOCUS:
        LOGE("APP_CMD_LOST_FOCUS");
        canDraw = 0;
        _pendingEvents.emplace_back(std::make_unique<Event>(Kind::UNFOCUS));
        break;
    case APP_CMD_CONTENT_RECT_CHANGED:
        LOGE("APP_CMD_CONTENT_RECT_CHANGED");
        resizeDisplay();
        break;
    case APP_CMD_CONFIG_CHANGED:
        LOGE("APP_CMD_CONFIG_CHANGED");
        resizeDisplay();
        break;
    case APP_CMD_WINDOW_REDRAW_NEEDED:
        LOGE("APP_CMD_WINDOW_REDRAW_NEEDED");
        _pendingEvents.emplace_back(std::make_unique<Event>(Kind::REDRAW));
        break;
    case APP_CMD_WINDOW_RESIZED:
        LOGE("APP_CMD_WINDOW_RESIZED");
        resizeDisplay();
        break;
    case APP_CMD_START:
        LOGE("APP_CMD_START");
        break;
    case APP_CMD_RESUME:
        LOGE("APP_CMD_RESUME");
        _pendingEvents.emplace_back(std::make_unique<Event>(Kind::RESUME));
        break;
    case APP_CMD_SAVE_STATE:
        LOGE("APP_CMD_SAVE_STATE");
        break;
    case APP_CMD_PAUSE:
        LOGE("APP_CMD_PAUSE");
        _pendingEvents.emplace_back(std::make_unique<Event>(Kind::PAUSE));
        break;
    case APP_CMD_STOP:
        LOGE("APP_CMD_STOP");
        break;
    case APP_CMD_DESTROY:
        LOGE("APP_CMD_DESTROY");
        break;
    default:
        LOGE("Unknown: %d", command);
        break;
    }
}

bool Engine::makeCurrent(bool attach) {
    if (attach) {
        if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
            LOGW_ANDROID("Unable to eglMakeCurrent");
            return false;
        }
    } else {
        eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    }
    return true;
}

void Engine::swapBuffers() {
    if (display && surface != EGL_NO_SURFACE)
        eglSwapBuffers(display, surface);
}

bool Engine::checkEvents() {
    processQueue();
    if (peer) {
        while (!_pendingEvents.empty()) {
            auto e = std::move(_pendingEvents.front());
            _pendingEvents.pop_front();
            switch (e->kind) {
                case Kind::RESIZE:
                    peer->callOnResize(e->args1[0], e->args2[0]);
                    break;
                case Kind::INIT:
                    peer->callOnInit();
                    break;
                case Kind::DEINIT:
                    peer->callOnDeinit();
                    break;
                case Kind::FOCUS:
                    peer->callOnFrameEvent(FrameEventType::Focus);
                    break;
                case Kind::UNFOCUS:
                    peer->callOnFrameEvent(FrameEventType::Unfocus);
                    break;
                case Kind::REDRAW:
                    peer->callRequestRedraw();
                    break;
                case Kind::TAP:
                    peer->callOnTap(e->count, e->args1, e->args2, e->arg3, e->target, 0);
                    break;
                case Kind::MOVE:
                    peer->callOnMove(e->count, e->args1, e->args2);
                    break;
                case Kind::KEY:
                    peer->callOnKey(e->args1[0], e->args2[0], e->arg3);
                    break;
                default:
                    // TODO: add lifecycle events.
                    break;
            }
        }
    }

    return app->destroyRequested == 0;
}

float Engine::getContentScale() {
    if (density == 0.0f) {
        density = AConfiguration_getDensity(app->config) * (1.0f / (float)ACONFIGURATION_DENSITY_MEDIUM);
        if (!density) {
            density = 1.0f / (float)ACONFIGURATION_DENSITY_MEDIUM;
        }
    }
    return density;
}

KNativePointer Engine::getFrame(KNativePointer peerPtr, int width, int height) {
    return peerPtr;
}

int32_t Engine::getFrameWidth() {
    return ANativeWindow_getWidth(app->window) / getContentScale();
}

int32_t Engine::getFrameHeight() {
    return ANativeWindow_getHeight(app->window) / getContentScale();
}

int32_t Engine::getPhysicalWidth() {
    return physicalWidth;
}

int32_t Engine::getPhysicalHeight() {
    return physicalHeight;
}

class JNIBridgeWrapper {
public:
    JNIBridgeWrapper(std::shared_ptr<JNIBridge> bridge): jniBridge(bridge) {}

    jobject getSystemService(jobject context, const char* service) {
        auto contextClass = jniBridge->findClass("android/content/Context");
        auto getSystemServiceMethod = jniBridge->getMethodID(
                contextClass, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
        return jniBridge->callObjectMethod(context, getSystemServiceMethod, jniBridge->makeString(service));
    }

protected:
    const std::shared_ptr<JNIBridge> jniBridge;
};

class JNIBridgeClipboardPaste : public JNIBridgeWrapper {
public:
    using JNIBridgeWrapper::JNIBridgeWrapper;

    bool hasPrimaryClip(jobject clipboard) {
        if (!clipboardManagerClass) {
            clipboardManagerClass = jniBridge->findClass("android/content/ClipboardManager");
        }
        auto clipboardManager_hasPrimaryClip = jniBridge->getMethodID(
                clipboardManagerClass, "hasPrimaryClip", "()Z");
        return jniBridge->callBooleanMethod(clipboard, clipboardManager_hasPrimaryClip) != JNI_FALSE;
    }

    jobject getPrimaryClipDescription(jobject clipboard) {
        if (!clipboardManagerClass) {
            clipboardManagerClass = jniBridge->findClass("android/content/ClipboardManager");
        }
        auto clipboardManager_getPrimaryClipDescription = jniBridge->getMethodID(
                clipboardManagerClass, "getPrimaryClipDescription", "()Landroid/content/ClipDescription;");
        return jniBridge->callObjectMethod(clipboard, clipboardManager_getPrimaryClipDescription);
    }

    bool hasMimeType(jobject clipDescription, const char* mimeType) {
        auto clipDescriptionClass = jniBridge->findClass("android/content/ClipDescription");
        auto clipDescription_hasMimeType = jniBridge->getMethodID(
                clipDescriptionClass, "hasMimeType", "(Ljava/lang/String;)Z");
        return jniBridge->callBooleanMethod(
                clipDescription, clipDescription_hasMimeType, jniBridge->makeString(mimeType)) != JNI_FALSE;
    }

    jobject getPrimaryClip(jobject clipboard) {
        if (!clipboardManagerClass) {
            clipboardManagerClass = jniBridge->findClass("android/content/ClipboardManager");
        }
        auto clipboardManager_getPrimaryClip = jniBridge->getMethodID(
                clipboardManagerClass, "getPrimaryClip", "()Landroid/content/ClipData;");
        return jniBridge->callObjectMethod(clipboard, clipboardManager_getPrimaryClip);
    }

    jobject getClipDataItemAt(jobject clipData, int index) {
        auto clipDataClass = jniBridge->findClass("android/content/ClipData");
        auto clipData_getItemAt = jniBridge->getMethodID(
                clipDataClass, "getItemAt", "(I)Landroid/content/ClipData$Item;");
        jvalue jIndex;
        jIndex.i = index;
        return jniBridge->callObjectMethod(clipData, clipData_getItemAt, jIndex);
    }

    jstring getClipDataItemText(jobject item) {
        auto clipDataItemClass = jniBridge->findClass("android/content/ClipData$Item");
        auto item_getText = jniBridge->getMethodID(
                clipDataItemClass, "getText", "()Ljava/lang/CharSequence;");
        auto charSequence = jniBridge->callObjectMethod(item, item_getText);
        auto charSequenceClass = jniBridge->findClass("java/lang/CharSequence");
        auto charSequence_toString = jniBridge->getMethodID(
                charSequenceClass, "toString", "()Ljava/lang/String;");
        return reinterpret_cast<jstring>(jniBridge->callObjectMethod(charSequence, charSequence_toString));
    }

private:
    jclass clipboardManagerClass = nullptr;
};

SkString* Engine::getClipboard() {
    if (!checkJniBridge()) {
        return nullptr;
    }
    SkString* result = nullptr;
    auto bridge = JNIBridgeClipboardPaste(jniBridge);
    auto clipboard = bridge.getSystemService(app->activity->clazz, "clipboard");
    if (bridge.hasPrimaryClip(clipboard) && (
            bridge.hasMimeType(bridge.getPrimaryClipDescription(clipboard), "text/plain") ||
            bridge.hasMimeType(bridge.getPrimaryClipDescription(clipboard), "text/html"))) {
        auto clipData = bridge.getPrimaryClip(clipboard);
        auto item = bridge.getClipDataItemAt(clipData, 0);
        auto jStr = bridge.getClipDataItemText(item);
        auto cStr = jniBridge->getStringUTFChars(jStr, nullptr);
        if (cStr) {
            result = new SkString(cStr);
            jniBridge->releaseStringUTFChars(jStr, cStr);
        }
    }
    return result;
}

class JNIBridgeClipboardCopy : public JNIBridgeWrapper {
public:
    using JNIBridgeWrapper::JNIBridgeWrapper;

    jobject newPlainText(const char* text) {
        auto clipDataClass = jniBridge->findClass("android/content/ClipData");
        auto clipData_newPlainText = jniBridge->getStaticMethodID(
                clipDataClass, "newPlainText",
                "(Ljava/lang/CharSequence;Ljava/lang/CharSequence;)Landroid/content/ClipData;");
        return jniBridge->callStaticObjectMethod(
                clipDataClass, clipData_newPlainText, jniBridge->makeString(""), jniBridge->makeString(text));
    }

    void setPrimaryClip(jobject clipboard, jobject clipData) {
        auto clipboardManagerClass = jniBridge->findClass("android/content/ClipboardManager");
        auto clipboardManager_setPrimaryClip = jniBridge->getMethodID(
                clipboardManagerClass, "setPrimaryClip", "(Landroid/content/ClipData;)V");
        jniBridge->callVoidMethod(clipboard, clipboardManager_setPrimaryClip, clipData);
    }
};

void Engine::setClipboard(const SkString& str) {
    if (!checkJniBridge()) {
        return;
    }
    auto bridge = JNIBridgeClipboardCopy(jniBridge);
    auto clipData = bridge.newPlainText(str.c_str());
    auto clipboard = bridge.getSystemService(app->activity->clazz, "clipboard");
    bridge.setPrimaryClip(clipboard, clipData);
}

void Engine::requestHaptic(int32_t p1, int32_t p2) {
    if (!checkJniBridge()) {
        return;
    }

    if (!vibratorInstance) {
        auto* contextClass = jniBridge->findClass("android/content/Context");
        auto* getSystemServiceMethod = jniBridge->getMethodID(
                contextClass, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
        auto androidContext = this->app->activity->clazz;
        jstring vibratorString = jniBridge->makeString("vibrator");
        jvalue arg;
        arg.l = vibratorString;
        vibratorInstance = jniBridge->callObjectMethod(androidContext, getSystemServiceMethod, arg);
        if (!jniBridge->check()) {
            return;
        }
        auto* vibratorClass = jniBridge->findClass("android/os/Vibrator");
        if (!vibratorClass) {
            LOGE("No android/os/Vibrator");
            return;
        }
        vibrateWithDurationMethod = jniBridge->getMethodID(vibratorClass, "vibrate", "(J)V");
        vibrateWithEffectMethod = jniBridge->getMethodID(vibratorClass, "vibrate", "(Landroid/os/VibrationEffect;)V");
        if (!vibrateWithEffectMethod) {
            LOGE("No vibrate(VibrationEffect) method");
            return;
        }
        vibrationEffectClass = jniBridge->findClass("android/os/VibrationEffect");
        if (!vibrationEffectClass) {
            LOGE("No android/os/VibrationEffect class");
            return;
        }
        createPredefinedEffectMethod = jniBridge->getStaticMethodID(vibrationEffectClass, "createPredefined", "(I)Landroid/os/VibrationEffect;");
        if (!createPredefinedEffectMethod) {
            LOGE("No createPredefined(int) method");
            jniBridge->check();
            return;
        }
    }
    if (vibratorInstance != nullptr && vibrateWithDurationMethod != nullptr && p1 != 0) {
        jvalue arg;
        arg.j = p1;
        jniBridge->callVoidMethod(vibratorInstance, vibrateWithDurationMethod, arg);
    } else {
        if (vibratorInstance != nullptr && vibrateWithEffectMethod != nullptr && createPredefinedEffectMethod != nullptr) {
            jvalue arg;
            arg.i = p2;
            arg.l = jniBridge->callStaticObjectMethod(vibrationEffectClass, createPredefinedEffectMethod, arg);
            if (!jniBridge->check()) return;
            jniBridge->callVoidMethod(vibratorInstance, vibrateWithEffectMethod, arg);
        }
    }
}

int32_t Engine::getOrientation() {
    if (!checkJniBridge()) {
        return -1;
    }
    jclass displayClass = jniBridge->findClass("android/view/Display");
    auto activity = this->app->activity->clazz;
    jclass activityClass = jniBridge->getObjectClass(activity);
    jmethodID getWindowManager = jniBridge->getMethodID(activityClass, "getWindowManager", "()Landroid/view/WindowManager;");
    if (!jniBridge->check()) return -1;
    jclass windowManagerClass = jniBridge->findClass("android/view/WindowManager");
    if (!jniBridge->check()) return -1;
    jmethodID getDefaultDisplay = jniBridge->getMethodID(windowManagerClass,"getDefaultDisplay","()Landroid/view/Display;");
    if (!jniBridge->check()) return -1;
    jmethodID getRotation = jniBridge->getMethodID(displayClass, "getRotation", "()I");
    if (!jniBridge->check()) return -1;
    jobject windowManager = jniBridge->callObjectMethod(activity, getWindowManager);
    if (!jniBridge->check() || !windowManager) return -1;
    jobject display = jniBridge->callObjectMethod(windowManager, getDefaultDisplay);
    if (!jniBridge->check() || !display) return -1;
    return jniBridge->callIntMethod(display, getRotation);
}

static bool make_current(void* enginePtr, void* context) {
    Engine* engine = (Engine *)enginePtr;
    return engine->makeCurrent(context != nullptr);
}

static void swap_buffers(void* enginePtr, void* context) {
    Engine* engine = (Engine *)enginePtr;
    engine->swapBuffers();
}

static bool check_events(void* enginePtr, void* context) {
    Engine* engine = (Engine *)enginePtr;
    return engine->checkEvents();
}

static float get_content_scale(void* enginePtr, void* context) {
    Engine* engine = (Engine *)enginePtr;
    return engine->getContentScale();
}

static KNativePointer get_frame(void* enginePtr, void* peerPtr, int width, int height, int flags, int placement, int x, int y) {
    Engine* engine = reinterpret_cast<Engine*>(enginePtr);
    return engine->getFrame(peerPtr, width, height);
}

static int32_t get_frame_width(void* enginePtr, void* window) {
    Engine* engine = (Engine *)enginePtr;
    return engine->getFrameWidth();
}

static int32_t get_frame_height(void* enginePtr, void* window) {
    Engine* engine = (Engine*)enginePtr;
    return engine->getFrameHeight();
}

static int32_t get_physical_width(void* enginePtr, void* window) {
    Engine* engine = (Engine *)enginePtr;
    return engine->getPhysicalWidth();
}

static int32_t get_physical_height(void* enginePtr, void* window) {
    Engine* engine = (Engine*)enginePtr;
    return engine->getPhysicalHeight();
}

static void request_haptic(void* enginePtr, int p1, int p2) {
    Engine* engine = (Engine*)enginePtr;
    return engine->requestHaptic(p1, p2);
}

static int32_t get_orientation(void* enginePtr) {
    Engine* engine = (Engine*)enginePtr;
    return engine->getOrientation();
}

static void soft_keyboard(void* enginePtr, bool show) {
    Engine* engine = (Engine*)enginePtr;
    return engine->softKeyboard(show);
}

static void commit_input(void* enginePtr) {
    Engine* engine = (Engine*)enginePtr;
    return engine->commitInput();
}

static std::vector<std::string> stringPermissions(KStringArray strArray) {
    if (strArray == nullptr) {
        return std::vector<std::string>(0);
    }

    KUInt arraySize = skoala::unpackUInt(strArray);
    std::vector<std::string> res(arraySize);
    size_t offset = sizeof(KUInt);
    for (KUInt i = 0; i < arraySize; ++i) {
        auto s = strArray + offset;
        auto* str = reinterpret_cast<const char *>(&s[sizeof(KUInt)]);
        res[i] = std::string(str, skoala::unpackUInt(s));
        offset += res[i].size() + sizeof(KUInt);
    }

    return res;
}

static void askPermissions(void* enginePtr, KStringArray perms) {
    Engine* engine = (Engine*)enginePtr;
    auto vector_perms = stringPermissions(perms);
    std::vector<std::string> missed_perms;
    std::copy_if(
        vector_perms.begin(),
        vector_perms.end(),
        std::back_inserter(missed_perms),
        [engine](std::string s) {
            return engine->androidExistPermission(s.c_str());
    });

    if (!missed_perms.empty()) {
        engine->askPermissions(missed_perms);
    }
}

static SkString* get_clipboard(void* enginePtr, void* context) {
    Engine* engine = reinterpret_cast<Engine*>(enginePtr);
    return engine->getClipboard();
}

static void set_clipboard(void* enginePtr, void* context, const SkString& str) {
    Engine* engine = reinterpret_cast<Engine*>(enginePtr);
    return engine->setClipboard(str);
}

static void get_global_pointer(void* enginePtr, KInt* pointer) {
    Engine* engine = reinterpret_cast<Engine*>(enginePtr);
    engine->globalPointer(pointer[0], pointer[1]);
}

RedrawerPeer* Engine::peer_factory(void* ctx, v8::Local<v8::Object> redrawer) {
    Engine* engine = (Engine*)ctx;

    RedrawerPeer* peer = new RedrawerPeer(engine->nodeScopedState.get(), redrawer);
    engine->peer = peer;
    peer->engine = engine;

    peer->getFrame = ::get_frame;
    peer->makeCurrent = ::make_current;
    peer->swapBuffers = ::swap_buffers;
    peer->checkEvents = ::check_events;
    peer->getContentScale = ::get_content_scale;
    peer->getFrameWidth = ::get_frame_width;
    peer->getFrameHeight = ::get_frame_height;
    peer->getPhysicalWidth = ::get_physical_width;
    peer->getPhysicalHeight = ::get_physical_height;
    peer->requestHaptic = ::request_haptic;
    peer->getOrientation = ::get_orientation;
    peer->softKeyboard = ::soft_keyboard;
    peer->commitInput = ::commit_input;
    peer->askPermissions = ::askPermissions;
    peer->readFromClipboard = ::get_clipboard;
    peer->writeToClipboard = ::set_clipboard;
    peer->getGlobalPointer = get_global_pointer;

    return peer;
}

using namespace v8;

int Engine::prepareNode(std::vector<std::string> &errors, const std::string& startScript) {
    node::CommonEnvironmentSetup* setup = nodeRuntime->setup;
    Isolate* isolate = setup->isolate();
    node::Environment* env = setup->env();
    v8::HandleScope handle_scope(isolate);
    std::string mainScript =
            "const publicRequire = require('module').createRequire(process.cwd());"
            "globalThis.require = publicRequire;"
            "return require('vm').runInThisContext('try { require(\"" + startScript + "\"); global.platformAPI(); } catch (e) { console.log(e) }');"
            ;
    MaybeLocal<v8::Value> maybeResult = node::LoadEnvironment(env, mainScript.c_str());
    if (maybeResult.IsEmpty()) {
        LOGE("Cannot load environment");
        return 1; // There has been a JS exception.
    }
    Local<v8::Value> result;
    if (!maybeResult.ToLocal(&result)) {
        LOGE("Cannot convert to local");
        return -1;
    }
    if (result->IsObject()) {
        nodeScopedState->startCallbacks();
        nodeScopedState->initPlatform(result.As<v8::Object>());
        nodeScopedState->providePlatformData(peer_factory, this);
    }
    return 0;
}