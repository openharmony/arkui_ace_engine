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

#include <stdio.h>
#include <cstddef>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <stdlib.h>
#endif

#include <GLFW/glfw3.h>
#ifdef SK_BUILD_FOR_WIN
    #define GLFW_EXPOSE_NATIVE_WIN32
    #include <GLFW/glfw3native.h>
#endif
// TODO: use Metal instead.
#ifdef SK_BUILD_FOR_MAC
#ifndef SK_USE_METAL
#include <OpenGL/gl.h>
#endif
#else
#include <GL/gl.h>
#endif

#include "skoala-interop.h"

#ifdef KOALA_NAPI
#include "node-interop.h"
#endif

#ifdef SK_BUILD_FOR_LINUX
#include <X11/Xlib.h>
#endif

#include "SkoalaCursor.h"

#ifndef SK_BUILD_FOR_MAC
void globalPointer(int &x, int &y) {
#ifdef SK_BUILD_FOR_WIN
    POINT p;
    GetCursorPos(&p);
    x = p.x;
    y = p.y;
#endif
#ifdef SK_BUILD_FOR_LINUX
    Display *display = XOpenDisplay(nullptr);
    int screen = DefaultScreen(display);
    Window rootWin = RootWindow(display, screen);
    Window root;
    Window child;
    int childX;
    int childY;
    unsigned int mask;
    XQueryPointer(display, rootWin, &root, &child, &x, &y, &childX, &childY, &mask);
    XCloseDisplay(display);
#endif
}
#else
    extern void globalPointer(int &x, int &y);
#endif


#ifdef SK_BUILD_FOR_WIN
static void setWindowsDefaultIcon(GLFWwindow* window) {
    HWND hwnd = glfwGetWin32Window(window);
    HICON hIcon = (HICON) LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(1));
    LRESULT res = 0;
    if (hIcon) {
        res = SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM) hIcon);
        res = SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM) hIcon);
        // TODO error handling if needed
    }
}

static int getWindowTitlebarHeight() {
    int height = (GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CXPADDEDBORDER));
    return height;
}
#endif

struct KeyEvent {
    int key;
    unsigned int character;
    int mods;
};

enum FramePlacement {
    FramePlacement_Default = 0,
    FramePlacement_Specified = 1,
    FramePlacement_StartTop = 17,
    FramePlacement_StartCenter = 18,
    FramePlacement_StartBottom = 19,
    FramePlacement_CenterTop = 33,
    FramePlacement_Center = 34,
    FramePlacement_CenterBottom = 35,
    FramePlacement_EndTop = 49,
    FramePlacement_EndCenter = 50,
    FramePlacement_EndBottom = 51,
};

enum FrameMode {
    FrameMode_Float = 0,
    FrameMode_Maximized = 64,
    FrameMode_Minimized = 128,
    FrameMode_Fullscreen = 256,
};

enum FrameRequests {
    FrameRequests_Focus = 1,
    FrameRequests_Move = 2,
    FrameRequests_Align = 3,
    FrameRequests_Resize = 4,
    FrameRequests_Mode = 5,
    FrameRequests_Visible = 6,
};

struct WindowState {
    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;
    int mode = 0;
};

static int mini(int x, int y) {
    return x < y ? x : y;
}

static int maxi(int x, int y) {
    return x > y ? x : y;
}

GLFWmonitor* get_current_monitor(GLFWwindow *window) {
    int numMonitors, i;
    int windowX, windowY, windowWidth, windowHeight;
    int monitorX, monitorY, monitorWidth, monitorHeight;
    int overlap, bestOverlap;
    GLFWmonitor *bestMonitor;
    GLFWmonitor **monitors;
    const GLFWvidmode *mode;

    bestOverlap = 0;
    bestMonitor = NULL;

    glfwGetWindowPos(window, &windowX, &windowY);
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    monitors = glfwGetMonitors(&numMonitors);

    for (i = 0; i < numMonitors; i++) {
        mode = glfwGetVideoMode(monitors[i]);
        glfwGetMonitorPos(monitors[i], &monitorX, &monitorY);
        monitorWidth = mode->width;
        monitorHeight = mode->height;

        overlap =
            maxi(0, mini(windowX + windowWidth, monitorX + monitorWidth) - maxi(windowX, monitorX)) *
            maxi(0, mini(windowY + windowHeight, monitorY + monitorHeight) - maxi(windowY, monitorY));

        if (bestOverlap < overlap) {
            bestOverlap = overlap;
            bestMonitor = monitors[i];
        }
    }

    return bestMonitor;
}

static void window_mode_callback(GLFWwindow* window, int value)
{
    RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(glfwGetWindowUserPointer(window));
    if (peer) {
        switch (value)
        {
            case FrameMode_Float: {
                peer->callOnFrameEvent(FrameEventType::Restore);
                return;
            }
            case FrameMode_Minimized: {
                peer->callOnFrameEvent(FrameEventType::Minimize);
                return;
            }
            case FrameMode_Maximized: {
                peer->callOnFrameEvent(FrameEventType::Maximize);
                return;
            }
            case FrameMode_Fullscreen: {
                peer->callOnFrameEvent(FrameEventType::Fullscreen);
                return;
            }
        }
    }
}

bool is_fullscreen(GLFWwindow *window) {
    return glfwGetWindowMonitor(window) != nullptr;
}

void switch_fullscreen(GLFWwindow *window, WindowState &rect) {
    bool isNotFullscreen = !is_fullscreen(window);
    GLFWmonitor* monitor = get_current_monitor(window);
    if (isNotFullscreen) {
        glfwGetWindowPos(window, &rect.x, &rect.y);
        glfwGetWindowSize(window, &rect.width, &rect.height);
        const GLFWvidmode * mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, 0);
        window_mode_callback(window, FrameMode_Fullscreen);
    } else {
        glfwSetWindowMonitor(window, NULL, rect.x, rect.y, rect.width, rect.height, 0);
        window_mode_callback(window, FrameMode_Float);
    }
}

// We may need  to scale to display coordinates on some platforms.
static void maybeScale(GLFWwindow* window, double* xpos, double* ypos) {
#ifndef SK_BUILD_FOR_MAC
    // We get events with framebuffer precision on non-Apple platforms.
    float xscale = 1.0f;
    float yscale = 1.0f;
    glfwGetWindowContentScale(window, &xscale, &yscale);
    *xpos /= xscale;
    *ypos /= yscale;
#endif
}

static void maybeScale(GLFWwindow* window, int* xpos, int* ypos) {
#ifndef SK_BUILD_FOR_MAC
    // We get events with framebuffer precision on non-Apple platforms.
    float xscale = 1.0f;
    float yscale = 1.0f;
    glfwGetWindowContentScale(window, &xscale, &yscale);
    *xpos /= xscale;
    *ypos /= yscale;
#endif
}

static int toButtonType(int button) {
    switch (button)
    {
    case GLFW_MOUSE_BUTTON_LEFT:
        return 1;
    case GLFW_MOUSE_BUTTON_RIGHT:
        return 2;
    case GLFW_MOUSE_BUTTON_MIDDLE:
        return 4;
    default:
        return 0;
    }
}

static void window_minimize_callback(GLFWwindow* window, int value)
{
    window_mode_callback(window, value ? FrameMode_Minimized : FrameMode_Float);
}

static void window_maximize_callback(GLFWwindow* window, int value)
{
    window_mode_callback(window, value ? FrameMode_Maximized : FrameMode_Float);
}

static void window_close_callback(GLFWwindow* window)
{
    RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(glfwGetWindowUserPointer(window));
    if (peer) {
        glfwSetWindowShouldClose(window, GLFW_FALSE);
        peer->callOnFrameEvent(FrameEventType::Close);
    }
}

void window_focus_callback(GLFWwindow* window, int focused)
{
    RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(glfwGetWindowUserPointer(window));
    if (peer) {
        if (focused)
        {
            peer->callOnFrameEvent(FrameEventType::Focus);
        }
        else
        {
            peer->callOnFrameEvent(FrameEventType::Unfocus);
        }
    }
}

static void drop_callback(GLFWwindow* window, int count, const char** paths)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(glfwGetWindowUserPointer(window));
    if (peer) {
        maybeScale(window, &xpos, &ypos);
        int xInt = (int)xpos;
        int yInt = (int)ypos;
        peer->callOnDrop(count, paths, xInt, yInt);
    }
}

static void window_size_callback(GLFWwindow* window, int width, int height)
{
    RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(glfwGetWindowUserPointer(window));
    maybeScale(window, &width, &height);
    if (peer) peer->callOnResize(width, height);
}

static void framebuffer_size_callback(GLFWwindow* window, int physicalWidth, int physicalHeight)
{
#ifdef SKOALA_USE_METAL
    int frameWidth = 0, frameHeight = 0;
    glfwGetWindowSize(window, &frameWidth, &frameHeight);
    void resizeMetalWindow(GLFWwindow* window, int frameWidth, int frameHeight, int physicalWidth, int physicalHeight);
    resizeMetalWindow(window, frameWidth, frameHeight, physicalWidth, physicalHeight);
#endif
}

static void window_pos_callback(GLFWwindow* window, int x, int y)
{
    RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(glfwGetWindowUserPointer(window));
    if (peer) peer->callOnFrameMove(x, y);
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    int tap = (action == GLFW_PRESS) ? 1 : 0;
    RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(glfwGetWindowUserPointer(window));
    if (peer) {
        maybeScale(window, &xpos, &ypos);
        int xInt = (int)xpos;
        int yInt = (int)ypos;
        peer->callOnTap(1, &xInt, &yInt, tap, 0, toButtonType(button));
    }
}

static void mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
{
    RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(glfwGetWindowUserPointer(window));
    if (peer) {
        maybeScale(window, &xpos, &ypos);
        int xInt = (int)xpos;
        int yInt = (int)ypos;
        peer->callOnMove(1, &xInt, &yInt);
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(glfwGetWindowUserPointer(window));
    if (peer) {
        int type = (action == GLFW_RELEASE) ? 0 : 1;
        peer->callOnKey(key, mods, type);
    }
}

const int CommitTextTypeFlag = 1;
const int CursorPositionIgnoredFlag = -1;
std::string UnicodeToUTF8(unsigned int codepoint)
{
    std::string out;

    if (codepoint <= 0x7f)
        out.append(1, static_cast<char>(codepoint));
    else if (codepoint <= 0x7ff)
    {
        out.append(1, static_cast<char>(0xc0 | ((codepoint >> 6) & 0x1f)));
        out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
    }
    else if (codepoint <= 0xffff)
    {
        out.append(1, static_cast<char>(0xe0 | ((codepoint >> 12) & 0x0f)));
        out.append(1, static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f)));
        out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
    }
    else
    {
        out.append(1, static_cast<char>(0xf0 | ((codepoint >> 18) & 0x07)));
        out.append(1, static_cast<char>(0x80 | ((codepoint >> 12) & 0x3f)));
        out.append(1, static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f)));
        out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
    }
    return out;
}

void character_callback(GLFWwindow* window, unsigned int codepoint)
{
    if (glfwGetWindowAttrib(window, GLFW_FOCUSED)) {
        RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(glfwGetWindowUserPointer(window));
        if (peer) {
            peer->callOnTextInput(CommitTextTypeFlag, CursorPositionIgnoredFlag, UnicodeToUTF8(codepoint));
        }
    }
}

void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(glfwGetWindowUserPointer(window));
    if (peer) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        maybeScale(window, &xpos, &ypos);
        // We need to convert scroll offset to Px (like in Web)
        double deltaX = xoffset * 100;
        double deltaY = yoffset * 100;
        peer->callOnScroll((int)xpos, (int)ypos, (int)deltaX, (int)deltaY);
    }
}

class GLFWCursorFactory {
public:
    static GLFWcursor* getCursor(SkoalaCursor cursor) {
        return _instance.getCursorPriv(cursor);
    }
private:
    static GLFWCursorFactory _instance;

    GLFWcursor* cache[static_cast<int>(SkoalaCursor::MaxValue)];

    GLFWcursor* createCursor(SkoalaCursor cursor) {
        switch (cursor) {
        case SkoalaCursor::Pointer: return glfwCreateStandardCursor(GLFW_HAND_CURSOR);
        case SkoalaCursor::Text: return glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
        case SkoalaCursor::ResizeX: return glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
        case SkoalaCursor::ResizeY: return glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
        case SkoalaCursor::ResizeXY: return glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
        default: return nullptr;
        }
    }

    GLFWcursor* getCursorPriv(SkoalaCursor cursor) {
        if (cursor == SkoalaCursor::Default) {
            return nullptr;
        }

        int idx = static_cast<int>(cursor);
        if (!cache[idx]) {
            cache[idx] = createCursor(cursor);
        }
        return cache[idx];
    }
};

GLFWCursorFactory GLFWCursorFactory::_instance = {};

struct GLFWEngine {
    WindowState recordState;

    KNativePointer getFrame(KNativePointer peerPtr, int width, int height, int flags, int placement, int x, int y) {
        RedrawerPeerBase* peer = reinterpret_cast<RedrawerPeerBase*>(peerPtr);

        GLFWwindow* window;
        if (!glfwInit()) return nullptr;
        glfwDefaultWindowHints();
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
        if ((flags & FrameFlag_NoResize) != 0) {
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        }
        if ((flags & FrameFlag_NoDecorations) != 0) {
            glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        }
        if ((flags & FrameFlag_AlwaysOnTop) != 0) {
            glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
        }
        if ((flags & FrameFlag_NoFocused) != 0) {
            glfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);
        }
        if ((flags & FrameFlag_Transparent) != 0) {
            glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
        }
        if ((flags & FrameMode_Maximized) != 0) {
            glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
        }

#ifdef SKOALA_USE_METAL
        GLFWwindow* createMetalWindow(int width, int height, const char* title);
        window = createMetalWindow(width, height, peer->title.c_str());
#else
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        window = glfwCreateWindow(width, height, peer->title.c_str(), nullptr, nullptr);
        if (!window) {
            if (glfwGetError(nullptr) == GLFW_VERSION_UNAVAILABLE) {
                // If we can not load OpenGL >= 3.2 with core profile, try to load something else
                // Core profile is useful for debugging, but it is not a hard constraint
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
                window = glfwCreateWindow(width, height, peer->title.c_str(), nullptr, nullptr);
            }
        }
#endif
        if (!window) {
            glfwTerminate();
            return nullptr;
        }

#ifdef SK_BUILD_FOR_WIN
        setWindowsDefaultIcon(window);
#endif

#ifndef SKOALA_USE_METAL
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);
#endif

        peer->userData = glfwGetWindowUserPointer(window);
        glfwSetWindowUserPointer(window, peer);

        glfwSetWindowSizeCallback(window, window_size_callback);
        glfwSetWindowPosCallback(window, window_pos_callback);
        glfwSetWindowCloseCallback(window, window_close_callback);
        glfwSetWindowFocusCallback(window, window_focus_callback);
        glfwSetWindowIconifyCallback(window, window_minimize_callback);
        glfwSetWindowMaximizeCallback(window, window_maximize_callback);

        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        glfwSetMouseButtonCallback(window, mouse_button_callback);

        glfwSetDropCallback(window, drop_callback);

        glfwSetCursorPosCallback(window, mouse_move_callback);

        glfwSetKeyCallback(window, key_callback);

        glfwSetCharCallback(window, character_callback);

        glfwSetScrollCallback(window, mouse_scroll_callback);

#if KOALA_NAPI
        if (peer) {
            RedrawerPeer* nodePeer = reinterpret_cast<RedrawerPeer*>(peer);
            nodePeer->node->startCallbacks();
        }
#endif

        if (placement == FramePlacement_Specified) {
            moveFrame(window, x, y);
        } else {
            requestAlign(window, placement);
        }
        if ((flags & FrameMode_Minimized) != 0) {
            requestMode(window, FrameMode_Minimized);
        }
        if ((flags & FrameMode_Fullscreen) != 0) {
            requestMode(window, FrameMode_Fullscreen);
        }
        if ((flags & FrameFlag_NoVisible) == 0 && glfwGetWindowAttrib(window, GLFW_VISIBLE) == GLFW_FALSE) {
            glfwShowWindow(window);
        }

        return reinterpret_cast<KNativePointer>(window);
    }

    KInt getFrameX(GLFWwindow* window) {
        int x = 0, y = 0;
        glfwGetWindowPos(window, &x, &y);
        maybeScale(window, &x, &y);
        return x;
    }

    KInt getFrameY(GLFWwindow* window) {
        int x = 0, y = 0;
        glfwGetWindowPos(window, &x, &y);
        maybeScale(window, &x, &y);
        return y;
    }

    KInt getFrameWidth(GLFWwindow* window) {
        int w = 0, h = 0;
        glfwGetWindowSize(window, &w, &h);
        maybeScale(window, &w, &h);
        return w;
    }

    KInt getFrameHeight(GLFWwindow* window) {
        int w = 0, h = 0;
        glfwGetWindowSize(window, &w, &h);
        maybeScale(window, &w, &h);
        return h;
    }

    KInt getPhysicalWidth(GLFWwindow* window) {
        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        return w;
    }

    KInt getPhysicalHeight(GLFWwindow* window) {
        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        return h;
    }

    KFloat getContentScale(GLFWwindow* window) {
        float xscale;
        float yscale;
        glfwGetWindowContentScale(window, &xscale, &yscale);
        return yscale;
    }

    bool makeCurrent(GLFWwindow* window) {
#ifdef SKOALA_USE_METAL
        void metalMakeCurrent(GLFWwindow*);
        metalMakeCurrent(window);
#else
        glfwMakeContextCurrent(window);
#endif
        return true;
    }

    void swapBuffers(GLFWwindow* window) {
#ifdef SKOALA_USE_METAL
        void metalSwapBuffers(GLFWwindow*);
        metalSwapBuffers(window);
#else
        glfwSwapBuffers(window);
#endif
    }

    void closeFrame(GLFWwindow* window) {
        GLFWwindow* current = glfwGetCurrentContext();
        glfwMakeContextCurrent(window);
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        glfwSetWindowUserPointer(window, nullptr);
        glfwDestroyWindow(window);
        glfwMakeContextCurrent(current);
    }

    bool checkEvents(GLFWwindow* window) {
        glfwPollEvents();
        return true;
    }

    SkString* getClipboard(GLFWwindow* window) {
        SkString* result = nullptr;
        auto str = glfwGetClipboardString(window);
        if (str) {
            result = new SkString(str);
        }
        return result;
    }

    void setClipboard(GLFWwindow* window, const SkString& str) {
        glfwSetClipboardString(window, str.c_str());
    }

    void requestHaptic(int p1, int p2) {}

    void softKeyboard(bool show) {}

    void setFrameTitle(GLFWwindow* window, const char * title) {
        glfwSetWindowTitle(window, title);
    }

    void focusFrame(GLFWwindow* window) {
        int focused = glfwGetWindowAttrib(window, GLFW_FOCUSED);
        if (focused == GLFW_FALSE) {
            glfwFocusWindow(window);
        }
    }

    void setFrameVisibility(GLFWwindow* window, bool value) {
        if (value) {
            glfwShowWindow(window);
        } else {
            glfwHideWindow(window);
        }
    }

    void commitInput() {}

    void requestMove(GLFWwindow* window, int x, int y) {
        glfwSetWindowPos(window, x, y);
    }

    void requestAlign(GLFWwindow* window, int placement) {
        int width = 0, height = 0;
        glfwGetWindowSize(window, &width, &height);
        GLFWmonitor* monitor = get_current_monitor(window);
        int screenX;
        int screenY;
        int screenW;
        int screenH;
        glfwGetMonitorWorkarea(monitor, &screenX, &screenY, &screenW, &screenH);
        int titlebarHeight = 0;
#ifdef SK_BUILD_FOR_WIN
        if (glfwGetWindowAttrib(window, GLFW_DECORATED)) {
            titlebarHeight = getWindowTitlebarHeight();
        }
#endif
        switch (placement)
        {
            case FramePlacement_StartTop: {
                moveFrame(window, screenX, screenY + titlebarHeight);
                break;
            }
            case FramePlacement_StartCenter: {
                int centerY = (screenY + screenH - height) / 2 + screenY;
                moveFrame(window, screenX, centerY);
                break;
            }
            case FramePlacement_StartBottom: {
                int bottomY = screenY + screenH - height;
                moveFrame(window, screenX, bottomY);
                break;
            }
            case FramePlacement_CenterTop: {
                int centerX = (screenW - width) / 2 + screenX;
                moveFrame(window, centerX, screenY + titlebarHeight);
                break;
            }
            case FramePlacement_Center: {
                int centerX = (screenW - width) / 2 + screenX;
                int centerY = (screenH - height) / 2 + screenY;
                moveFrame(window, centerX, centerY);
                break;
            }
            case FramePlacement_CenterBottom: {
                int centerX = (screenW - width) / 2 + screenX;
                int bottomY = screenY + screenH - height;
                moveFrame(window, centerX, bottomY);
                break;
            }
            case FramePlacement_EndTop: {
                int endX = screenX + screenW - width;
                moveFrame(window, endX, screenY + titlebarHeight);
                break;
            }
            case FramePlacement_EndCenter: {
                int endX = screenX + screenW - width;
                int centerY = (screenH - height) / 2 + screenY;
                moveFrame(window, endX, centerY);
                break;
            }
            case FramePlacement_EndBottom: {
                int endX = screenX + screenW - width;
                int bottomY = screenY + screenH - height;
                moveFrame(window, endX, bottomY);
                break;
            }
            default:
                break;
        }
    }

    void moveFrame(GLFWwindow* window, int x, int y) {
        int currentX, currentY;
        glfwGetWindowPos(window, &currentX, &currentY);
        if (x == currentX && y == currentY) return;
        glfwSetWindowPos(window, x, y);
    }

    void requestResize(GLFWwindow* window, int width, int height) {
#ifndef SK_BUILD_FOR_MAC
        float xscale = 1.0f;
        float yscale = 1.0f;
        glfwGetWindowContentScale(window, &xscale, &yscale);
        width *= xscale;
        height *= yscale;
#endif
        glfwSetWindowSize(window, width, height);
    }

    void requestMode(GLFWwindow* window, int mode) {
        int x, y, width = 0, height = 0;
        glfwGetWindowPos(window, &x, &y);
        glfwGetWindowSize(window, &width, &height);
        switch (mode)
        {
            case FrameMode_Float: {
                if (is_fullscreen(window)) {
                    switch_fullscreen(window, recordState);
                } else if (recordState.mode != FrameMode_Float) {
                    glfwRestoreWindow(window);
                }
                break;
            }
            case FrameMode_Maximized: {
                if (is_fullscreen(window)) {
                    switch_fullscreen(window, recordState);
                }
                if (recordState.mode != FrameMode_Maximized) {
                    glfwMaximizeWindow(window);
                }
                break;
            }
            case FrameMode_Minimized: {
                if (is_fullscreen(window)) {
                    switch_fullscreen(window, recordState);
                }
                if (recordState.mode != FrameMode_Minimized) {
                    glfwIconifyWindow(window);
                }
                break;
            }
            case FrameMode_Fullscreen: {
                if (!is_fullscreen(window)) {
                    switch_fullscreen(window, recordState);
                }
                break;
            }

            default:
                break;
        }
        recordState.mode = mode;
    }

    void setCursor(GLFWwindow* window, SkoalaCursor cursor) {
        glfwSetCursor(window, GLFWCursorFactory::getCursor(cursor));
    }
};

static GLFWEngine* theEngine = nullptr;

static KNativePointer get_frame(void* enginePtr, void* peerPtr, int width, int height, int flags, int placement, int x, int y) {
    GLFWEngine* engine = reinterpret_cast<GLFWEngine*>(enginePtr);
    return engine->getFrame(peerPtr, width, height, flags, placement, x, y);
}

static int get_frame_x(void* enginePtr, void* context) {
    GLFWEngine* engine = reinterpret_cast<GLFWEngine*>(enginePtr);
    GLFWwindow* window = reinterpret_cast<GLFWwindow*>(context);
    return engine->getFrameX(window);
}

static int get_frame_y(void* enginePtr, void* context) {
    GLFWEngine* engine = reinterpret_cast<GLFWEngine*>(enginePtr);
    GLFWwindow* window = reinterpret_cast<GLFWwindow*>(context);
    return engine->getFrameY(window);
}

static int get_frame_width(void* enginePtr, void* context) {
    GLFWEngine* engine = reinterpret_cast<GLFWEngine*>(enginePtr);
    GLFWwindow* window = reinterpret_cast<GLFWwindow*>(context);
    return engine->getFrameWidth(window);
}

static int get_frame_height(void* enginePtr, void* context) {
    GLFWEngine* engine = reinterpret_cast<GLFWEngine*>(enginePtr);
    GLFWwindow* window = reinterpret_cast<GLFWwindow*>(context);
    return engine->getFrameHeight(window);
}

static int get_physical_width(void* enginePtr, void* context) {
    GLFWEngine* engine = reinterpret_cast<GLFWEngine*>(enginePtr);
    GLFWwindow* window = reinterpret_cast<GLFWwindow*>(context);
    return engine->getPhysicalWidth(window);
}

static int get_physical_height(void* enginePtr, void* context) {
    GLFWEngine* engine = reinterpret_cast<GLFWEngine*>(enginePtr);
    GLFWwindow* window = reinterpret_cast<GLFWwindow*>(context);
    return engine->getPhysicalHeight(window);
}

static float get_content_scale(void* enginePtr, void* context) {
    GLFWEngine* engine = reinterpret_cast<GLFWEngine*>(enginePtr);
    GLFWwindow* window = reinterpret_cast<GLFWwindow*>(context);
    return engine->getContentScale(window);
}

static bool make_current(void* enginePtr, void* context) {
    GLFWEngine* engine = reinterpret_cast<GLFWEngine*>(enginePtr);
    GLFWwindow* window = reinterpret_cast<GLFWwindow*>(context);
    return engine->makeCurrent(window);
}

static void swap_buffers(void* enginePtr, void* context) {
    GLFWEngine* engine = reinterpret_cast<GLFWEngine*>(enginePtr);
    GLFWwindow* window = reinterpret_cast<GLFWwindow*>(context);
    engine->swapBuffers(window);
}

static bool check_events(void* enginePtr, void* context) {
    GLFWEngine* engine = reinterpret_cast<GLFWEngine*>(enginePtr);
    GLFWwindow* window = reinterpret_cast<GLFWwindow*>(context);
    return engine->checkEvents(window);
}

static void request_haptic(void* enginePtr, int p1, int p2) {
    GLFWEngine* engine = reinterpret_cast<GLFWEngine*>(enginePtr);
    return engine->requestHaptic(p1, p2);
}

static void soft_keyboard(void* enginePtr, bool show) {
    GLFWEngine* engine = reinterpret_cast<GLFWEngine*>(enginePtr);
    return engine->softKeyboard(show);
}

static void set_frame_title(void* enginePtr, void* context, const char *title) {
    GLFWEngine* engine = reinterpret_cast<GLFWEngine*>(enginePtr);
    GLFWwindow* window = reinterpret_cast<GLFWwindow*>(context);
    return engine->setFrameTitle(window, title);
}

static void commit_input(void* enginePtr) {
    GLFWEngine* engine = reinterpret_cast<GLFWEngine*>(enginePtr);
    return engine->commitInput();
}

static void send_request(void* enginePtr, void* context, KInt type, KInt data1, KInt data2) {
    GLFWEngine* engine = reinterpret_cast<GLFWEngine*>(enginePtr);
    GLFWwindow* window = reinterpret_cast<GLFWwindow*>(context);
    switch (type)
    {
        case FrameRequests_Align: {
            engine->requestAlign(window, data1);
            break;
        }
        case FrameRequests_Move: {
            engine->requestMove(window, data1, data2);
            break;
        }
        case FrameRequests_Resize: {
            engine->requestResize(window, data1, data2);
            break;
        }
        case FrameRequests_Mode: {
            engine->requestMode(window, data1);
            break;
        }
        case FrameRequests_Focus: {
            engine->focusFrame(window);
            break;
        }
        case FrameRequests_Visible: {
            engine->setFrameVisibility(window, data1);
            break;
        }
        default:
            break;
        }
}

static void set_cursor(void* enginePtr, void* context, SkoalaCursor cursor) {
    GLFWEngine* engine = reinterpret_cast<GLFWEngine*>(enginePtr);
    GLFWwindow* window = reinterpret_cast<GLFWwindow*>(context);
    return engine->setCursor(window, cursor);
}

static SkString* get_clipboard(void* enginePtr, void* context) {
    GLFWEngine* engine = reinterpret_cast<GLFWEngine*>(enginePtr);
    GLFWwindow* window = reinterpret_cast<GLFWwindow*>(context);
    return engine->getClipboard(window);
}

static void set_clipboard(void* enginePtr, void* context, const SkString& str) {
    GLFWEngine* engine = reinterpret_cast<GLFWEngine*>(enginePtr);
    GLFWwindow* window = reinterpret_cast<GLFWwindow*>(context);
    return engine->setClipboard(window, str);
}

static void close_frame(void* enginePtr, void* context) {
    GLFWEngine* engine = reinterpret_cast<GLFWEngine*>(enginePtr);
    GLFWwindow* window = reinterpret_cast<GLFWwindow*>(context);
    return engine->closeFrame(window);
}

static void get_global_pointer(void* enginePtr, KInt* pointer) {
    globalPointer(pointer[0], pointer[1]);
}

#ifdef KOALA_NAPI
static NodeScopedState* theNodeState = nullptr;

RedrawerPeer* glfwPeerFactory(void* arg, v8::Local<v8::Object> redrawer) {
    RedrawerPeer* peer = new RedrawerPeer(theNodeState, redrawer);
    if (theEngine == nullptr) {
        theEngine = new GLFWEngine();
    }
    peer->engine = theEngine;
    peer->getFrame = get_frame;
    peer->getFrameX = get_frame_x;
    peer->getFrameY = get_frame_y;
    peer->getFrameWidth = get_frame_width;
    peer->getFrameHeight = get_frame_height;
    peer->getPhysicalWidth = get_physical_width;
    peer->getPhysicalHeight = get_physical_height;
    peer->getContentScale = get_content_scale;
    peer->makeCurrent = make_current;
    peer->swapBuffers = swap_buffers;
    peer->checkEvents = check_events;
    peer->requestHaptic = request_haptic;
    peer->softKeyboard = soft_keyboard;
    peer->setFrameTitle = set_frame_title;
    peer->commitInput = commit_input;
    peer->sendRequest = send_request;
    peer->setCursor = set_cursor;
    peer->closeFrame = close_frame;
    peer->getGlobalPointer = get_global_pointer;
    peer->readFromClipboard = get_clipboard;
    peer->writeToClipboard = set_clipboard;

    return peer;
}

peerFactory_t getSystemPeerFactory(NodeScopedState* nodeState) {
    theNodeState = nodeState;
    return glfwPeerFactory;
}
#endif

void* getSystemPeerFactoryArg() {
    if (theEngine == nullptr) {
        theEngine = new GLFWEngine();
    }
    return theEngine;
}

