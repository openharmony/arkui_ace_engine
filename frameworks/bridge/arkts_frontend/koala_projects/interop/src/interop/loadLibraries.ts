const nativeModuleLibraries: Map<string, string> = new Map()

export function loadNativeLibrary(name: string): Record<string, object> {
    if ((globalThis as any).requireNapi)
        return (globalThis as any).requireNapi(name, true)
    else {
        const suffixedName = name.endsWith(".node") ? name : `${name}.node`
        return eval(`let exports = {}; process.dlopen({ exports }, require.resolve("${suffixedName}"), 2); exports`)
    }
}

export function registerNativeModuleLibraryName(nativeModule: string, libraryName: string) {
    nativeModuleLibraries.set(nativeModule, libraryName)
}

export function loadNativeModuleLibrary(moduleName: string, module?: object) {
    if (!module)
        throw new Error("<module> argument is required and optional only for compatibility with ArkTS")
    const library = loadNativeLibrary(nativeModuleLibraries.get(moduleName) ?? moduleName)
    if (!library || !library[moduleName]) {
        console.error(`Failed to load library for module ${moduleName}`)
        return
    }
    Object.assign(module, library[moduleName])
}
