import { registerNativeModuleLibraryName, loadInteropNativeModule, InteropNativeModule, callCallback } from "@koalaui/interop"

declare const NATIVE_LIBRARY_NAME: string
export function loadNative() {
    registerNativeModuleLibraryName("InteropNativeModule", NATIVE_LIBRARY_NAME)
    registerNativeModuleLibraryName("ArkUINativeModule", NATIVE_LIBRARY_NAME)
    registerNativeModuleLibraryName("ArkUIGeneratedNativeModule", NATIVE_LIBRARY_NAME)
    registerNativeModuleLibraryName("TestNativeModule", NATIVE_LIBRARY_NAME)
    loadInteropNativeModule()
    InteropNativeModule._SetCallbackDispatcher(callCallback)
}