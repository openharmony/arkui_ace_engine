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
package org.koalaui.interop;

import java.util.Arrays;
import java.util.HashMap;

class CallbackRegistry {

    private static HashMap<Integer, CallbackRecord> callbacks = new HashMap<Integer, CallbackRecord>();
    private static Integer id = 0;

    static {
        CallbackRegistry.callbacks.put(id, new CallbackRecord(
            new CallbackType() {
                @Override
                public int apply(byte[] args, int length) {
                    System.out.printf("Callback 0 called with args = %s and length = %d\n", Arrays.toString(args), length);
                    throw new Error("Null callback called");
                }
            }, false)
        );
        CallbackRegistry.id++;
    }

    private CallbackRegistry() {
        
    }

    public static Integer wrap(CallbackType callback) {
        Integer id = CallbackRegistry.id++;
        CallbackRegistry.callbacks.put(id, new CallbackRecord(callback, true));
        return id;
    }

    public static Integer wrap(CallbackType callback, boolean autoDisposable) {
        Integer id = CallbackRegistry.id++;
        CallbackRegistry.callbacks.put(id, new CallbackRecord(callback, autoDisposable));
        return id;
    }

    public static int call(Integer id, byte[] args, int length) {
        if (!CallbackRegistry.callbacks.containsKey(id)) {
            System.out.printf("Callback %d is not known\n", id);
            throw new Error(String.format("Disposed or unwrapped callback called (id = %d)", id));
        }
        CallbackRecord record = CallbackRegistry.callbacks.get(id);
        if (record.autoDisposable) {
            CallbackRegistry.dispose(id);
        }
        return record.callback.apply(args, length);
    }
    
    public static void dispose(Integer id) {
        CallbackRegistry.callbacks.remove(id);
    }
}
