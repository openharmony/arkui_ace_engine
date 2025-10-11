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

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.IntBuffer;
import java.util.function.Function;

import org.koalaui.arkoala.NativeModule;

public class CallbackTests {
    // Improve: where tests will be located?

    public class TestUtils {
        // Improve: where test utils will be located?
        public static <T> void assertEquals(String name, T expected, T actual) {
            if (!expected.equals(actual)) {
                System.out.printf("TEST %s FAIL:\n  EXPECTED \"%s\"\n  ACTUAL   \"%s\"\n", name, expected.toString(), actual.toString());
            } else {
                System.out.printf("TEST %s PASS\n", name);
            }
        }

        public static <T> void assertThrows(String name, Function<Void, T> fn) {
            boolean caught = false;
            try {
                fn.apply(null);
            } catch (Throwable e) {
                caught = true;
            }
            if (!caught) {
                System.out.printf("TEST %s FAIL:\n  No exception thrown\n", name);
            } else {
                System.out.printf("TEST %s PASS\n", name);
            }
        }
    }

    public static void checkCallback() {
        Integer id1 = CallbackRegistry.wrap(new CallbackType() {
            @Override
            public int apply(byte[] args, int length) {
                return 2024;
            }
        });
        Integer id2 = CallbackRegistry.wrap(new CallbackType() {
            @Override
            public int apply(byte[] args, int length) {
                return 2025;
            }
        });

        TestUtils.assertEquals("Call callback 1", 2024, CallbackRegistry.call(id1, new byte[] {}, 0));
        TestUtils.assertEquals("Call callback 2", 2025, CallbackRegistry.call(id2, new byte[] {}, 0));
        TestUtils.assertThrows("Call disposed callback 1", new Function<Void, Integer>() {
            @Override
            public Integer apply(Void v) {
                return CallbackRegistry.call(id1, new byte[] { }, 0);
            }
        });
        TestUtils.assertThrows("Call callback 0", new Function<Void, Integer>() {
            @Override
            public Integer apply(Void v) {
                return CallbackRegistry.call(0, new byte[] { 2, 4, 6, 8 }, 4);
            }
        });
    }

    public static void checkNativeCallback() {
        Integer id1 = CallbackRegistry.wrap(new CallbackType() {
            @Override
            public int apply(byte[] args, int length) {
                return 123456;
            }
        });
        TestUtils.assertEquals("NativeCallback without args", 123456, NativeModule._TestCallIntNoArgs(id1));
        TestUtils.assertThrows("NativeCallback without args called again", new Function<Void, Integer>() {
            @Override
            public Integer apply(Void v) {
                return CallbackRegistry.call(id1, new byte[] { }, 0);
            }
        });
        TestUtils.assertThrows("NativeCallback without args called again from native", new Function<Void, Integer>() {
            @Override
            public Integer apply(Void v) {
                return NativeModule._TestCallIntNoArgs(id1);
            }
        });

        Integer id2 = CallbackRegistry.wrap(new CallbackType() {
            @Override
            public int apply(byte[] args, int length) {
                ByteBuffer buffer = ByteBuffer.wrap(args);
                buffer.order(ByteOrder.LITTLE_ENDIAN);
                IntBuffer intBuffer = buffer.asIntBuffer();
                int sum = 0;
                for (int i = 0; i < length / 4; i++) {
                    sum += intBuffer.get(i);
                }
                return sum;
            }
        });
        int[] arr2 = new int[] { 100, 200, 300, -1000 };
        TestUtils.assertEquals("NativeCallback Int32Array sum", -400, NativeModule._TestCallIntIntArraySum(id2, arr2, arr2.length));

        Integer id3 = CallbackRegistry.wrap(new CallbackType() {
            @Override
            public int apply(byte[] args, int length) {
                ByteBuffer buffer = ByteBuffer.wrap(args);
                buffer.order(ByteOrder.LITTLE_ENDIAN);
                IntBuffer intBuffer = buffer.asIntBuffer();
                for (int i = 1; i < length / 4; i++) {
                    intBuffer.put(i, intBuffer.get(i) + intBuffer.get(i - 1));
                }
                return 0;
            }
        });
        int[] arr3 = new int[] { 100, 200, 300, -1000 };
        NativeModule._TestCallVoidIntArrayPrefixSum(id3, arr3, arr3.length);
        TestUtils.assertEquals("NativeCallback Int32Array PrefixSum [0]", 100, arr3[0]);
        TestUtils.assertEquals("NativeCallback Int32Array PrefixSum [1]", 300, arr3[1]);
        TestUtils.assertEquals("NativeCallback Int32Array PrefixSum [2]", 600, arr3[2]);
        TestUtils.assertEquals("NativeCallback Int32Array PrefixSum [3]", -400, arr3[3]);

        long start = System.currentTimeMillis();
        Integer id4 = CallbackRegistry.wrap(new CallbackType() {
            @Override
            public int apply(byte[] args, int length) {
                ByteBuffer buffer = ByteBuffer.wrap(args);
                buffer.order(ByteOrder.LITTLE_ENDIAN);
                IntBuffer intBuffer = buffer.asIntBuffer();
                intBuffer.put(1, intBuffer.get(1) + 1);
                if (intBuffer.get(0) + intBuffer.get(1) < intBuffer.get(2)) {
                    return NativeModule._TestCallIntRecursiveCallback(id3 + 1, args, args.length);
                }
                return 1;
            }
        }, false);
        TestUtils.assertEquals("NativeCallback prepare recursive callback test", id4, id3 + 1);
        int depth = 500;
        int count = 100;
        for (int i = 0; i < count; i++) {
            int length = 12;
            byte[] args = new byte[length];
            IntBuffer args32 = ByteBuffer.wrap(args).order(ByteOrder.LITTLE_ENDIAN).asIntBuffer();
            args32.put(2, depth);
            NativeModule._TestCallIntRecursiveCallback(id4, args, args.length);
            if (i == 0) {
                TestUtils.assertEquals("NativeCallback Recursive [0]", (depth + 1) / 2, args32.get(0));
                TestUtils.assertEquals("NativeCallback Recursive [1]", depth / 2, args32.get(1));
            }
        }
        long passed = System.currentTimeMillis() - start;
        System.out.println("recursive native callback: " + String.valueOf(passed) + "ms for " + depth * count + " callbacks, " + Math.round((double)passed / (depth * count) * 1000000) + "ms per 1M callbacks");

        Integer id5 = CallbackRegistry.wrap(new CallbackType() {
            @Override
            public int apply(byte[] args, int length) {
                int sum = 0;
                for (int i = 0; i < length; i++) {
                    sum += args[i];
                }
                return sum;
            }
        }, false);
        NativeModule._TestCallIntMemory(id5, 1000);
    }
}
