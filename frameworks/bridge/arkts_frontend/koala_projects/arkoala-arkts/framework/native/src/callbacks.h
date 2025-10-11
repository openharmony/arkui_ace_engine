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

#ifndef _ARKOALA_CALLBACKS_H
#define _ARKOALA_CALLBACKS_H

#include <stdint.h>
#include <stdlib.h>
#include "koala-types.h"
#include "arkoala_api_generated.h"
#include "callback_kind.h"
#include "callback-resource.h"

Ark_NativePointer getManagedCallbackCaller(CallbackKind kind);
Ark_NativePointer getManagedCallbackCallerSync(CallbackKind kind);

void deserializeAndCallCallback(KInt kind, KByte* args, KInt argsSize);
void deserializeAndCallCallbackSync(Ark_VMContext vmContext, KInt kind, KByte* args, KInt argsSize);

#endif