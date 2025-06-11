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

#pragma once

#include <unordered_map>
#include <map>
#include <tuple>

#include <jni.h>

class JNIBridge {
    JavaVM* jvm;
    JNIEnv* env;
    std::unordered_map<std::string, jclass> classes;
    // Using tuples as unordered maps keys in not very good in C++.
    std::map<std::tuple<jclass, std::string, std::string>, jmethodID> methods; 

  public:
    JNIBridge(JavaVM* jvm) : jvm(jvm), env(nullptr) {}
    ~JNIBridge() {
        if (env) {
            for (const auto& kv : classes) {
                env->DeleteGlobalRef(kv.second);
            }
            jvm->DetachCurrentThread();
        }
    }

    bool init() {
        if (jvm->AttachCurrentThreadAsDaemon(&env, nullptr) != 0) {
            fprintf(stderr, "Cannot attach current thread to JVM\n");
            return false;
        }
        return true;
    }

    jstring makeString(const char* str) {
        return env->NewStringUTF(str);
    }

    const char* getStringUTFChars(jstring str, jboolean *isCopy) {
        return env->GetStringUTFChars(str, isCopy);
    }

    void releaseStringUTFChars(jstring str, const char* chars) {
        env->ReleaseStringUTFChars(str, chars);
    }

    jclass getObjectClass(jobject obj) {
        return env->GetObjectClass(obj);
    }

    jclass findClass(const char* clazz) {
        auto it = classes.find(clazz);
        if (it == classes.end()) {
            auto result = env->FindClass(clazz);
            classes[clazz] = (jclass)env->NewGlobalRef(result);
            return result;
        } else {
            return it->second;
        }
    }

    jobject newObject(jclass clazz, jmethodID methodID, ...) {
        va_list args;
        jobject result;
        va_start(args, methodID);
        result = env->NewObjectV(clazz, methodID, args);
        va_end(args);
        return result;
    }

    jmethodID getMethodID(jclass clazz, const char* method, const char* sig) {
        auto key = std::make_tuple(clazz, method, sig);
        auto it = methods.find(key);
        if (it == methods.end()) {
            auto result = env->GetMethodID(clazz, method, sig);
            methods[key] = result;
            return result;
        } else {
            return it->second;
        }
    }

    jmethodID getStaticMethodID(jclass clazz, const char* method, const char* sig) {
        return env->GetStaticMethodID(clazz, method, sig);
    }

    void callStaticVoidMethod(jclass clazz, jmethodID methodID, ...) {
        va_list args;
        va_start(args, methodID);
        env->CallStaticVoidMethodV(clazz, methodID, args);
        va_end(args);
    }

    jobject callStaticObjectMethod(jclass clazz, jmethodID methodID, ...) {
        va_list args;
        jobject result;
        va_start(args, methodID);
        result = env->CallStaticObjectMethodV(clazz, methodID, args);
        va_end(args);
        return result;
    }

    jobject callObjectMethod(jobject obj, jmethodID methodID, ...) {
        va_list args;
        jobject result;
        va_start(args, methodID);
        result = env->CallObjectMethodV(obj, methodID, args);
        va_end(args);
        return result;
    }

    void callVoidMethod(jobject obj, jmethodID methodID, ...) {
        va_list args;
        va_start(args, methodID);
        env->CallVoidMethodV(obj, methodID, args);
        va_end(args);
    }

    jboolean callBooleanMethod(jobject obj, jmethodID methodID, ...) {
        va_list args;
        jboolean result;
        va_start(args, methodID);
        result = env->CallBooleanMethodV(obj, methodID, args);
        va_end(args);
        return result;
    }

    jfieldID getStaticFieldID(jclass clazz, const char *name, const char *sig) {
        return env->GetStaticFieldID(clazz, name, sig);
    }

    jint getStaticIntField(jclass clazz, jfieldID fieldID) {
        return env->GetStaticIntField(clazz, fieldID);
    }

    jobject getStaticObjectField(jclass clazz, jfieldID fieldID) {
        return env->GetStaticObjectField(clazz, fieldID);
    }

    jint callIntMethod(jobject obj, jmethodID methodID, ...) {
        va_list args;
        jint result;
        va_start(args, methodID);
        result = env->CallIntMethodV(obj, methodID, args);
        va_end(args);
        return result;
    }

    jfloat callFloatMethod(jobject obj, jmethodID methodID, ...) {
        va_list args;
        jint result;
        va_start(args, methodID);
        result = env->CallFloatMethodV(obj, methodID, args);
        va_end(args);
        return result;
    }

    bool check() {
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
            env->ExceptionClear();
            return false;
        }
        return true;
    }

    jobjectArray makeArray(jclass clazz, jsize length, jobject initialElement) {
        return env->NewObjectArray(length, clazz, initialElement);
    }

    void setArrayElement(jobjectArray array, jsize index, jobject value) {
        env->SetObjectArrayElement(array, index, value);
    }

    jobject getArrayElement(jobjectArray array, jsize index) {
        return env->GetObjectArrayElement(array, index);
    }

    jfloat* getFloatArrayElement(jfloatArray array) {
        return env->GetFloatArrayElements(array, 0);
    }
};