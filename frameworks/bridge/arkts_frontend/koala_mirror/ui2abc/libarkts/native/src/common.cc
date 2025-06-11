/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#include <common.h>
#include <utility>

using std::string, std::cout, std::endl, std::vector;

static es2panda_Impl *impl = nullptr;

static thread_local StageArena currentArena;

StageArena* StageArena::instance()
{
    return &currentArena;
}

void StageArena::add(void* pointer)
{
    if (pointer)
        allocated.push_back(pointer);
}

void StageArena::cleanup()
{
    if (totalSize > 0 && false)
        printf("cleanup %d objects %d bytes\n", (int)allocated.size(), (int)totalSize);
    for (auto it : allocated) {
        free(it);
    }
    totalSize = 0;
    allocated.clear();
}

StageArena::StageArena()
{
    totalSize = 0;
}

StageArena::~StageArena()
{
    cleanup();
}

char* StageArena::strdup(const char* string)
{
    auto* arena = StageArena::instance();
    auto size = strlen(string) + 1;
    char* memory = (char*)arena->alloc(size);
    memcpy(memory, string, size);
    return memory;
}

void* StageArena::alloc(size_t size)
{
    void* result = malloc(size);
    totalSize += size;
    add(result);
    return result;
}

#ifdef KOALA_WINDOWS
    #include <windows.h>
    #define PLUGIN_DIR "windows_host_tools"
    #define LIB_PREFIX ""
    #define LIB_SUFFIX ".dll"
#endif

#ifdef KOALA_LINUX
    #include <dlfcn.h>

    #ifdef __x86_64__
        #define PLUGIN_DIR "linux_host_tools"
    #else
        #define PLUGIN_DIR "linux_arm64_host_tools"
    #endif

    #define LIB_PREFIX "lib"
    #define LIB_SUFFIX ".so"
#endif

const char* DEFAULT_SDK_PATH = "../../../incremental/tools/panda/node_modules/@panda/sdk" ;
const char* NAME = LIB_PREFIX "es2panda-public" LIB_SUFFIX;

void* FindLibrary()
{
    char* envValue = getenv("PANDA_SDK_PATH");
    if (!envValue) {
        std::cout << "PANDA_SDK_PATH not specified, assuming " << DEFAULT_SDK_PATH << std::endl;
    }
    std::string prefix = envValue ? std::string(envValue) : DEFAULT_SDK_PATH;
    std::string libraryName = prefix + ("/" PLUGIN_DIR "/lib/") + NAME;
    return loadLibrary(libraryName);
}

es2panda_Impl *GetImpl()
{
    if (impl) {
        return impl;
    }
    auto library = FindLibrary();
    if (!library) {
        printf("No library (es2panda_lib.cc)");
        abort();
    }
    auto symbol = findSymbol(library, "es2panda_GetImpl");
    if (!symbol) {
        printf("no entry point");
        abort();
    }
    impl = reinterpret_cast<es2panda_Impl *(*)(int)>(symbol)(ES2PANDA_LIB_VERSION);
    return impl;
}

es2panda_ContextState intToState(KInt state)
{
    return es2panda_ContextState(state);
}

string getString(KStringPtr ptr)
{
    return ptr.data();
}

char* getStringCopy(KStringPtr& ptr)
{
    return StageArena::strdup(ptr.c_str() ? ptr.c_str() : "");
}

inline KUInt unpackUInt(const KByte* bytes)
{
    const KUInt BYTE_0 = 0;
    const KUInt BYTE_1 = 1;
    const KUInt BYTE_2 = 2;
    const KUInt BYTE_3 = 3;

    const KUInt BYTE_1_SHIFT = 8;
    const KUInt BYTE_2_SHIFT = 16;
    const KUInt BYTE_3_SHIFT = 24;
    return (
        bytes[BYTE_0]
        | (bytes[BYTE_1] << BYTE_1_SHIFT)
        | (bytes[BYTE_2] << BYTE_2_SHIFT)
        | (bytes[BYTE_3] << BYTE_3_SHIFT)
    );
}

void impl_MemInitialize()
{
    GetImpl()->MemInitialize();
}
KOALA_INTEROP_V0(MemInitialize)

void impl_MemFinalize()
{
    GetImpl()->MemFinalize();
}
KOALA_INTEROP_V0(MemFinalize)

KNativePointer impl_CreateGlobalContext(KNativePointer configPtr, KStringArray externalFileListPtr,
    KInt fileNum, KBoolean lspUsage)
{
    auto config = reinterpret_cast<es2panda_Config*>(configPtr);

    const std::size_t headerLen = 4;

    const char** externalFileList = new const char* [fileNum];
    std::size_t position = headerLen;
    std::size_t strLen;
    for (std::size_t i = 0; i < static_cast<std::size_t>(fileNum); ++i) {
        strLen = unpackUInt(externalFileListPtr + position);
        position += headerLen;
        externalFileList[i] = strdup(std::string(
            reinterpret_cast<const char*>(externalFileListPtr + position), strLen).c_str());
        position += strLen;
    }

    return GetImpl()->CreateGlobalContext(config, externalFileList, fileNum, lspUsage);
}
KOALA_INTEROP_4(CreateGlobalContext, KNativePointer, KNativePointer, KStringArray, KInt, KBoolean)

void impl_DestroyGlobalContext(KNativePointer globalContextPtr)
{
    auto context = reinterpret_cast<es2panda_GlobalContext*>(globalContextPtr);
    GetImpl()->DestroyGlobalContext(context);
}
KOALA_INTEROP_V1(DestroyGlobalContext, KNativePointer)

KNativePointer impl_CreateCacheContextFromFile(KNativePointer configPtr, KStringPtr& fileName,
    KNativePointer globalContext, KBoolean isExternal)
{
    auto config = reinterpret_cast<es2panda_Config*>(configPtr);
    auto context = reinterpret_cast<es2panda_GlobalContext*>(globalContext);
    return GetImpl()->CreateCacheContextFromFile(config, getStringCopy(fileName), context, isExternal);
}
KOALA_INTEROP_4(CreateCacheContextFromFile, KNativePointer, KNativePointer, KStringPtr, KNativePointer, KBoolean)

KNativePointer impl_CreateConfig(KInt argc, KStringArray argvPtr) {
    const std::size_t headerLen = 4;

    const char** argv = StageArena::allocArray<const char*>(argc);
    std::size_t position = headerLen;
    std::size_t strLen;
    for (std::size_t i = 0; i < static_cast<std::size_t>(argc); ++i) {
        strLen = unpackUInt(argvPtr + position);
        position += headerLen;
        argv[i] = StageArena::strdup(std::string(reinterpret_cast<const char*>(argvPtr + position), strLen).c_str());
        position += strLen;
    }
    return GetImpl()->CreateConfig(argc, argv);
}
KOALA_INTEROP_2(CreateConfig, KNativePointer, KInt, KStringArray)

KNativePointer impl_DestroyConfig(KNativePointer configPtr) {
    auto config = reinterpret_cast<es2panda_Config*>(configPtr);
    GetImpl()->DestroyConfig(config);
    return nullptr;
}
KOALA_INTEROP_1(DestroyConfig, KNativePointer, KNativePointer)

KNativePointer impl_DestroyContext(KNativePointer contextPtr) {
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    GetImpl()->DestroyContext(context);
    StageArena::instance()->cleanup();
    return nullptr;
}
KOALA_INTEROP_1(DestroyContext, KNativePointer, KNativePointer)

KNativePointer impl_UpdateCallExpression(
    KNativePointer contextPtr,
    KNativePointer nodePtr,
    KNativePointer calleePtr,
    KNativePointerArray argumentsPtr,
    KInt argumentsLen,
    KNativePointer typeParamsPtr,
    KBoolean optionalT,
    KBoolean trailingCommaT
) {
    auto node = reinterpret_cast<es2panda_AstNode*>(nodePtr);
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto callee = reinterpret_cast<es2panda_AstNode*>(calleePtr);
    auto arguments = reinterpret_cast<es2panda_AstNode**>(argumentsPtr);
    auto typeParams = reinterpret_cast<es2panda_AstNode*>(typeParamsPtr);
    auto optional = static_cast<bool>(optionalT);
    auto trailingComma = static_cast<bool>(trailingCommaT);

    auto nn = GetImpl()->CreateCallExpression(
        context, callee, arguments, argumentsLen, typeParams, optional, trailingComma
    );
    GetImpl()->AstNodeSetOriginalNode(context, nn, node);
    return nn;
}
KOALA_INTEROP_8(UpdateCallExpression, KNativePointer, KNativePointer, KNativePointer, KNativePointer, KNativePointerArray, KInt, KNativePointer, KBoolean, KBoolean)

KInt impl_IdentifierIdentifierFlags(KNativePointer contextPtr, KNativePointer nodePtr) {
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto node = reinterpret_cast<es2panda_AstNode*>(nodePtr);

    return
        (GetImpl()->IdentifierIsOptionalConst(context, node) ? (1 << 0) : 0) |
        (GetImpl()->IdentifierIsReferenceConst(context, node) ? (1 << 1) : 0) |
        (GetImpl()->IdentifierIsTdzConst(context, node) ? (1 << 2) : 0);
}
KOALA_INTEROP_2(IdentifierIdentifierFlags, KInt, KNativePointer, KNativePointer)

/*
TODO: NOT FROM API (shouldn't be there)
-----------------------------------------------------------------------------------------------------------------------------
*/

KNativePointer impl_AstNodeProgram(KNativePointer contextPtr, KNativePointer instancePtr)
{
    auto _context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto _receiver = reinterpret_cast<es2panda_AstNode*>(instancePtr);

    if (GetImpl()->AstNodeIsProgramConst(_context, _receiver)) {
        return GetImpl()->ETSModuleProgram(_context, _receiver);
    }
    return impl_AstNodeProgram(_context, GetImpl()->AstNodeParent(_context, _receiver));
}
KOALA_INTEROP_2(AstNodeProgram, KNativePointer, KNativePointer, KNativePointer)

thread_local es2panda_AstNode *cachedParentNode;
thread_local es2panda_Context *cachedContext;

static void changeParent(es2panda_AstNode *child)
{
    GetImpl()->AstNodeSetParent(cachedContext, child, cachedParentNode);
}

static void SetRightParent(es2panda_AstNode *node, void *arg)
{
    es2panda_Context *ctx = static_cast<es2panda_Context *>(arg);
    cachedContext = ctx;
    cachedParentNode = node;

    GetImpl()->AstNodeIterateConst(ctx, node, changeParent);
}

KNativePointer impl_AstNodeUpdateAll(KNativePointer contextPtr, KNativePointer programPtr) {
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto program = reinterpret_cast<es2panda_AstNode*>(programPtr);

    GetImpl()->AstNodeForEach(program, SetRightParent, context);
    return program;
}
KOALA_INTEROP_2(AstNodeUpdateAll, KNativePointer, KNativePointer, KNativePointer)

KNativePointer impl_AstNodeUpdateChildren(KNativePointer contextPtr, KNativePointer nodePtr) {
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto node = reinterpret_cast<es2panda_AstNode*>(nodePtr);
    cachedParentNode = node;

    GetImpl()->AstNodeIterateConst(context, node, changeParent);
    return node;
}
KOALA_INTEROP_2(AstNodeUpdateChildren, KNativePointer, KNativePointer, KNativePointer)

thread_local std::vector<void*> cachedChildren;

static void visitChild(es2panda_AstNode *node)
{
    cachedChildren.emplace_back(node);
}

KNativePointer impl_AstNodeChildren(
    KNativePointer contextPtr,
    KNativePointer nodePtr
) {
    auto context = reinterpret_cast<es2panda_Context*>(contextPtr);
    auto node = reinterpret_cast<es2panda_AstNode*>(nodePtr);
    cachedContext = context;
    cachedChildren.clear();

    GetImpl()->AstNodeIterateConst(context, node, visitChild);
    return StageArena::clone(cachedChildren);
}
KOALA_INTEROP_2(AstNodeChildren, KNativePointer, KNativePointer, KNativePointer)

/*
-----------------------------------------------------------------------------------------------------------------------------
*/
