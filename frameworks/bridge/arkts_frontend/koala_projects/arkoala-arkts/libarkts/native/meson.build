project(
    'es2panda_interop',
    'cpp',
    version: '1.0',
    default_options: [
        'cpp_std=c++17',
        'buildtype=debug',
    ],
)

sources = [
    './src/common.cc',
    './src/bridges.cc',
    './src/generated/bridges.cc',
    get_option('interop_src_dir') / 'common-interop.cc',
    get_option('interop_src_dir') / 'callback-resource.cc',
    get_option('interop_src_dir') / 'interop-logging.cc',
    get_option('interop_src_dir') / 'napi/convertors-napi.cc',
]

cflags = [
    '-DKOALA_INTEROP_MODULE=NativeModule',
    '-DINTEROP_LIBRARY_NAME=' + get_option('lib_name'),
    '-DKOALA_USE_NODE_VM',
    '-DKOALA_NAPI',
]

if (target_machine.system() == 'windows')
    cflags += ['-DKOALA_WINDOWS']
    if (meson.get_compiler('cpp').get_id() == 'msvc')
        # apply node.exe symbol loading hook
        sources += [
            get_option('interop_src_dir') / 'napi/win-dynamic-node.cc'
        ]
    endif
else
    cflags += ['-DKOALA_LINUX']
endif

shared_library(
    get_option('lib_name'),
    sources,
    override_options: [
        'b_lundef=false',
    ],
    install: true,
    name_prefix: '',
    name_suffix: 'node',
    include_directories: [
        './src/',
        get_option('panda_sdk_dir') / 'ohos_arm64/include/tools/es2panda/public',
        get_option('panda_sdk_dir') / 'ohos_arm64/include/tools/es2panda',
        get_option('interop_src_dir'),
        get_option('interop_src_dir') / 'types',
        get_option('interop_src_dir') / 'napi',
        get_option('node_modules_dir') / 'node-api-headers/include',
        get_option('node_modules_dir') / 'node-addon-api',
    ],
    cpp_args: cflags,
    link_args: [],
    dependencies: []
)
