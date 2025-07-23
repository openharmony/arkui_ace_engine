/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { KInt, KPointer, KBoolean, NativeBuffer, KStringPtr, wrapCallback, SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KSerializerBuffer, KUint8ArrayPtr, Finalizable, registerCallback } from "@koalaui/interop"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { CallbackKind } from "./peers/CallbackKind"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
import { BaseContext, BaseContextInternal } from "./application.BaseContext"
export type Context_getGroupDir_Callback = (result: string) => void;
export class common_Context_serializer {
    public static write(buffer: SerializerBase, value: common.Context): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): common.Context {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return common.ContextInternal.fromPtr(ptr)
    }
}
export namespace common {
    export class ContextInternal {
        public static fromPtr(ptr: KPointer): common.Context {
            return new common.Context(ptr)
        }
    }
    export class Context extends BaseContext implements MaterializedBase {
        get cacheDir(): string {
            return this.getCacheDir()
        }
        set cacheDir(cacheDir: string) {
            this.setCacheDir(cacheDir)
        }
        get tempDir(): string {
            return this.getTempDir()
        }
        set tempDir(tempDir: string) {
            this.setTempDir(tempDir)
        }
        get filesDir(): string {
            return this.getFilesDir()
        }
        set filesDir(filesDir: string) {
            this.setFilesDir(filesDir)
        }
        get databaseDir(): string {
            return this.getDatabaseDir()
        }
        set databaseDir(databaseDir: string) {
            this.setDatabaseDir(databaseDir)
        }
        get preferencesDir(): string {
            return this.getPreferencesDir()
        }
        set preferencesDir(preferencesDir: string) {
            this.setPreferencesDir(preferencesDir)
        }
        get bundleCodeDir(): string {
            return this.getBundleCodeDir()
        }
        set bundleCodeDir(bundleCodeDir: string) {
            this.setBundleCodeDir(bundleCodeDir)
        }
        get distributedFilesDir(): string {
            return this.getDistributedFilesDir()
        }
        set distributedFilesDir(distributedFilesDir: string) {
            this.setDistributedFilesDir(distributedFilesDir)
        }
        get resourceDir(): string {
            return this.getResourceDir()
        }
        set resourceDir(resourceDir: string) {
            this.setResourceDir(resourceDir)
        }
        get cloudFileDir(): string {
            return this.getCloudFileDir()
        }
        set cloudFileDir(cloudFileDir: string) {
            this.setCloudFileDir(cloudFileDir)
        }
        constructor(peerPtr: KPointer) {
            super(peerPtr)
        }
        constructor() {
            this(Context.construct())
        }
        static construct(): KPointer {
            const retval  = ArkUIGeneratedNativeModule._common_Context_construct()
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._common_Context_getFinalizer()
        }
        public createBundleContext(bundleName: string): Context {
            const bundleName_casted = bundleName as (string)
            return this.createBundleContext_serialize(bundleName_casted)
        }
        public createModuleContext(moduleName: string): Context {
            const moduleName_casted = moduleName as (string)
            return this.createModuleContext0_serialize(moduleName_casted)
        }
        public createModuleContext(bundleName: string, moduleName: string): Context {
            const bundleName_casted = bundleName as (string)
            const moduleName_casted = moduleName as (string)
            return this.createModuleContext1_serialize(bundleName_casted, moduleName_casted)
        }
        public getGroupDir(dataGroupID: string, callback_: Context_getGroupDir_Callback): void {
            const dataGroupID_casted = dataGroupID as (string)
            const callback__casted = callback_ as (Context_getGroupDir_Callback)
            this.getGroupDir0_serialize(dataGroupID_casted, callback__casted)
            return
        }
        public getGroupDir(dataGroupID: string): Promise<string> {
            const dataGroupID_casted = dataGroupID as (string)
            return this.getGroupDir1_serialize(dataGroupID_casted)
        }
        private getCacheDir(): string {
            return this.getCacheDir_serialize()
        }
        private setCacheDir(cacheDir: string): void {
            const cacheDir_casted = cacheDir as (string)
            this.setCacheDir_serialize(cacheDir_casted)
            return
        }
        private getTempDir(): string {
            return this.getTempDir_serialize()
        }
        private setTempDir(tempDir: string): void {
            const tempDir_casted = tempDir as (string)
            this.setTempDir_serialize(tempDir_casted)
            return
        }
        private getFilesDir(): string {
            return this.getFilesDir_serialize()
        }
        private setFilesDir(filesDir: string): void {
            const filesDir_casted = filesDir as (string)
            this.setFilesDir_serialize(filesDir_casted)
            return
        }
        private getDatabaseDir(): string {
            return this.getDatabaseDir_serialize()
        }
        private setDatabaseDir(databaseDir: string): void {
            const databaseDir_casted = databaseDir as (string)
            this.setDatabaseDir_serialize(databaseDir_casted)
            return
        }
        private getPreferencesDir(): string {
            return this.getPreferencesDir_serialize()
        }
        private setPreferencesDir(preferencesDir: string): void {
            const preferencesDir_casted = preferencesDir as (string)
            this.setPreferencesDir_serialize(preferencesDir_casted)
            return
        }
        private getBundleCodeDir(): string {
            return this.getBundleCodeDir_serialize()
        }
        private setBundleCodeDir(bundleCodeDir: string): void {
            const bundleCodeDir_casted = bundleCodeDir as (string)
            this.setBundleCodeDir_serialize(bundleCodeDir_casted)
            return
        }
        private getDistributedFilesDir(): string {
            return this.getDistributedFilesDir_serialize()
        }
        private setDistributedFilesDir(distributedFilesDir: string): void {
            const distributedFilesDir_casted = distributedFilesDir as (string)
            this.setDistributedFilesDir_serialize(distributedFilesDir_casted)
            return
        }
        private getResourceDir(): string {
            return this.getResourceDir_serialize()
        }
        private setResourceDir(resourceDir: string): void {
            const resourceDir_casted = resourceDir as (string)
            this.setResourceDir_serialize(resourceDir_casted)
            return
        }
        private getCloudFileDir(): string {
            return this.getCloudFileDir_serialize()
        }
        private setCloudFileDir(cloudFileDir: string): void {
            const cloudFileDir_casted = cloudFileDir as (string)
            this.setCloudFileDir_serialize(cloudFileDir_casted)
            return
        }
        private createBundleContext_serialize(bundleName: string): Context {
            const retval  = ArkUIGeneratedNativeModule._common_Context_createBundleContext(this.peer!.ptr, bundleName)
            const obj : Context = common.ContextInternal.fromPtr(retval)
            return obj
        }
        private createModuleContext0_serialize(moduleName: string): Context {
            const retval  = ArkUIGeneratedNativeModule._common_Context_createModuleContext0(this.peer!.ptr, moduleName)
            const obj : Context = common.ContextInternal.fromPtr(retval)
            return obj
        }
        private createModuleContext1_serialize(bundleName: string, moduleName: string): Context {
            const retval  = ArkUIGeneratedNativeModule._common_Context_createModuleContext1(this.peer!.ptr, bundleName, moduleName)
            const obj : Context = common.ContextInternal.fromPtr(retval)
            return obj
        }
        private getGroupDir0_serialize(dataGroupID: string, callback_: Context_getGroupDir_Callback): void {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            thisSerializer.holdAndWriteCallback(callback_)
            ArkUIGeneratedNativeModule._common_Context_getGroupDir0(this.peer!.ptr, dataGroupID, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
        }
        private getGroupDir1_serialize(dataGroupID: string): Promise<string> {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            const retval  = thisSerializer.holdAndWriteCallbackForPromise<string>()[0]
            ArkUIGeneratedNativeModule._common_Context_getGroupDir1(this.peer!.ptr, dataGroupID, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
            return retval
        }
        private getCacheDir_serialize(): string {
            const retval  = ArkUIGeneratedNativeModule._common_Context_getCacheDir(this.peer!.ptr)
            return retval
        }
        private setCacheDir_serialize(cacheDir: string): void {
            ArkUIGeneratedNativeModule._common_Context_setCacheDir(this.peer!.ptr, cacheDir)
        }
        private getTempDir_serialize(): string {
            const retval  = ArkUIGeneratedNativeModule._common_Context_getTempDir(this.peer!.ptr)
            return retval
        }
        private setTempDir_serialize(tempDir: string): void {
            ArkUIGeneratedNativeModule._common_Context_setTempDir(this.peer!.ptr, tempDir)
        }
        private getFilesDir_serialize(): string {
            const retval  = ArkUIGeneratedNativeModule._common_Context_getFilesDir(this.peer!.ptr)
            return retval
        }
        private setFilesDir_serialize(filesDir: string): void {
            ArkUIGeneratedNativeModule._common_Context_setFilesDir(this.peer!.ptr, filesDir)
        }
        private getDatabaseDir_serialize(): string {
            const retval  = ArkUIGeneratedNativeModule._common_Context_getDatabaseDir(this.peer!.ptr)
            return retval
        }
        private setDatabaseDir_serialize(databaseDir: string): void {
            ArkUIGeneratedNativeModule._common_Context_setDatabaseDir(this.peer!.ptr, databaseDir)
        }
        private getPreferencesDir_serialize(): string {
            const retval  = ArkUIGeneratedNativeModule._common_Context_getPreferencesDir(this.peer!.ptr)
            return retval
        }
        private setPreferencesDir_serialize(preferencesDir: string): void {
            ArkUIGeneratedNativeModule._common_Context_setPreferencesDir(this.peer!.ptr, preferencesDir)
        }
        private getBundleCodeDir_serialize(): string {
            const retval  = ArkUIGeneratedNativeModule._common_Context_getBundleCodeDir(this.peer!.ptr)
            return retval
        }
        private setBundleCodeDir_serialize(bundleCodeDir: string): void {
            ArkUIGeneratedNativeModule._common_Context_setBundleCodeDir(this.peer!.ptr, bundleCodeDir)
        }
        private getDistributedFilesDir_serialize(): string {
            const retval  = ArkUIGeneratedNativeModule._common_Context_getDistributedFilesDir(this.peer!.ptr)
            return retval
        }
        private setDistributedFilesDir_serialize(distributedFilesDir: string): void {
            ArkUIGeneratedNativeModule._common_Context_setDistributedFilesDir(this.peer!.ptr, distributedFilesDir)
        }
        private getResourceDir_serialize(): string {
            const retval  = ArkUIGeneratedNativeModule._common_Context_getResourceDir(this.peer!.ptr)
            return retval
        }
        private setResourceDir_serialize(resourceDir: string): void {
            ArkUIGeneratedNativeModule._common_Context_setResourceDir(this.peer!.ptr, resourceDir)
        }
        private getCloudFileDir_serialize(): string {
            const retval  = ArkUIGeneratedNativeModule._common_Context_getCloudFileDir(this.peer!.ptr)
            return retval
        }
        private setCloudFileDir_serialize(cloudFileDir: string): void {
            ArkUIGeneratedNativeModule._common_Context_setCloudFileDir(this.peer!.ptr, cloudFileDir)
        }
    }
}
