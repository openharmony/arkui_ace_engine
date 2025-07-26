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

#include <iostream>

enum Kind {
    INIT,
    DEINIT,
    RESIZE,
    REDRAW,
    FOCUS,
    UNFOCUS,
    PAUSE,
    RESUME,
    TAP,
    MOVE,
    KEY
};

struct Event {
    Kind kind;
    int count;
    int args1[10];
    int args2[10];
    int arg3;
    int target;
    Event(Kind kind, int arg1, int arg2, int arg3) : kind(kind), count(1), arg3(arg3), target(0) {
        args1[0] = arg1;
        args2[0] = arg2;
    }
    Event(Kind kind, int arg1, int arg2) : kind(kind), count(1), arg3(0), target(0) {
        args1[0] = arg1;
        args2[0] = arg2;
    }
    Event(Kind kind, int count) : kind(kind), count(count), arg3(0), target(0) {
        args1[0] = 0;
        args2[0] = 0;
    }
    Event(Kind kind) : Event(kind, 1) {}
};