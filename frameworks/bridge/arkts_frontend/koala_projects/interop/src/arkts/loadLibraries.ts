const nativeModuleLibraries: Map<string, string> = new Map<string, string>()

export function loadNativeLibrary(library: string) {
    loadLibrary(library)
}

export function registerNativeModuleLibraryName(nativeModule: string, libraryName: string) {
    nativeModuleLibraries.set(nativeModule, libraryName)
}

export function loadNativeModuleLibrary(nativeModule: string) {
    loadLibrary(nativeModuleLibraries.get(nativeModule) ?? nativeModule)
}
