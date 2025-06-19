project('playground', 'cpp',
    version: '1.0',
    default_options: [
        'cpp_std=c++17',
        'buildtype=debug',
    ],
)

cflags = [
    '-DKOALA_USE_NODE_VM',
    '-DKOALA_NAPI'
]

if target_machine.system() == 'windows'
    cflags += ['-DKOALA_WINDOWS']
else
    cflags += ['-DKOALA_LINUX']
endif

executable(
    'playground.out',
    [
        './src/playground.cc',
    ],
    include_directories: [
        get_option('panda_sdk_dir') / 'ohos_arm64/include/tools/es2panda/public',
        get_option('panda_sdk_dir') / 'ohos_arm64/include/tools/es2panda',
        get_option('interop_src_dir'),
    ],
    cpp_args: cflags
)
