project('ArkoalaNative', 'c', 'cpp',
    version: '0.1',
    default_options: ['cpp_std=c++17', 'buildtype=release']
)

source_dir = meson.current_source_dir()
interop_src = '../../../interop/src/cpp'

oses = { 'darwin': 'macos' }  # rename meson default names to convenient ones
archs = { 'x86_64': 'x64', 'aarch64': 'arm64', 'armv7-a': 'arm32', 'wasm32': 'wasm' }

fs = import('fs')

os = target_machine.system()
os = oses.get(os, os)
arch = target_machine.cpu()
arch = archs.get(arch, arch)

libace_name = 'ace_compatible_mock'
libace_sources = [
    './src/generated/dummy_impl.cc',
    interop_src / 'interop-logging.cc'
]

arkoala_sources = [
    './src/events.cc',
    './src/vsync.cc',
    './src/generated/bridge_generated.cc',
    './src/generated/callback_deserialize_call.cc',
    './src/generated/callback_managed_caller.cc',
]

sources = [
    './src/generated/library.cc',
    './src/generated/bridge_custom.cc',
    interop_src / 'common-interop.cc',
    interop_src / 'callback-resource.cc',
    interop_src / 'interop-logging.cc'
]

include_dirs = [
    './src',
    './src/generated',
    interop_src,
    interop_src / 'types',
]

node_api_headers = run_command('node', '-p', 'require.resolve("node-api-headers/package.json").slice(0, -12)', check: true).stdout().strip()

is_node = get_option('vm_kind') == 'node'
is_hzvm = get_option('vm_kind') == 'hzvm'

is_panda = get_option('vm_kind') == 'panda'
is_ani = is_panda
is_etsapi = is_panda
is_jvm = get_option('vm_kind') == 'jvm'
is_msvc = meson.get_compiler('cpp').get_id() == 'msvc'
is_napi = is_node or is_hzvm
is_jni = is_jvm
# To control if we use dummy or libace based implementation
is_dummy_impl = is_node
is_ohos = os == 'ohos'
is_user_bridge = true

if is_ohos
    if is_user_bridge
        library_use_name = 'ArkoalaNative'
        interop_library_name = library_use_name
    else
        library_use_name = 'arkoalanative_' + os + '_' + arch + '.z'
        interop_library_name = 'arkoalanative_' + os + '_' + arch
    endif
else
    library_use_name = 'ArkoalaNative_' + os + '_' + arch
    interop_library_name = library_use_name
endif

if is_jni
    library_use_name += '_jni'
endif

cflags = []
ldflags = []
deps = []

cflags += ['-DINTEROP_LIBRARY_NAME=' + interop_library_name]

if os == 'windows'
    cflags += ['-DKOALA_WINDOWS']
    ldflags += []
    if is_napi
        # apply node.exe symbol loading hook
        sources += [
            interop_src / 'napi' / 'win-dynamic-node.cc'
        ]
        cflags += ['/Gy-']
		# Strange, but true
        platform_prefix = 'lib'
    else
        platform_prefix = ''
    endif
    platform_suffix = 'dll'
endif
if os == 'linux'
    cflags += ['-DKOALA_LINUX', '-Wno-unused']
    platform_prefix = 'lib'
    platform_suffix = 'so'
endif
if os == 'macos'
    cflags += ['-DKOALA_MACOS', '-mmacosx-version-min=13.3']
    platform_prefix = 'lib'
    platform_suffix = 'dylib'
endif
if is_ohos
    clang_flags = [
        '-Wno-non-virtual-dtor',
        '-fno-rtti',
        '-Wall',
        # '-Werror', TODO: turn back on once generated part compiles without warnings
        '-Wno-error=attributes',
        '-Wno-unused'
    ]
    include_dirs += [
        interop_src / 'ohos',
    ]
    cflags += [
        '-DKOALA_OHOS',
        '-D__MUSL__',
    ] + clang_flags
    ldflags += [
        '-lEGL',
        '-lGLESv3',
        '-lhilog_ndk.z',
        '-lace_ndk.z',
        '-lace_napi.z',
        '-luv',
        '-static-libstdc++'
    ]
    platform_prefix = 'lib'
    platform_suffix = 'so'
endif

if is_napi
    sources += [
        interop_src / 'napi/convertors-napi.cc',
    ]
    include_dirs += [
        interop_src / 'napi',
        node_api_headers / 'include'
    ]
    cflags += [
        '-DKOALA_NAPI',
    ]
endif
if is_etsapi
    sources_ets = [
        interop_src / 'ets/convertors-ets.cc',
        interop_src / 'types/signatures.cc',
    ]
    include_dirs_ets = [
        interop_src / 'ets',
        interop_src / 'types',
    ]
    cflags_ets = [
        '-DKOALA_ETS_NAPI',
    ]
endif
if is_ani
    sources_ani = [
        interop_src / 'ani/convertors-ani.cc',
        interop_src / 'types/signatures.cc',
    ]
    include_dirs_ani = [
        interop_src / 'ani',
        interop_src / 'types',
    ]
    cflags_ani = [
        '-DKOALA_ANI',
    ]
endif
if is_jni
    sources += [
        interop_src / 'jni/convertors-jni.cc',
        interop_src / 'types/signatures.cc',
    ]
    jni_os_dir = os
    if jni_os_dir == 'windows'
        jni_os_dir = 'win32'
    endif
    if jni_os_dir == 'macos'
        jni_os_dir = 'darwin'
    endif
    include_dirs += [
        interop_src / 'jni',
        interop_src / 'types',
        get_option('jdk_dir') / 'include',
        get_option('jdk_dir') / 'include' / jni_os_dir,
    ]
    cflags += [
        '-DKOALA_JNI',
    ]
endif

if is_node
    cflags += [
        '-DKOALA_USE_NODE_VM',
    ]
    module_prefix = ''
    module_suffix = 'node'
endif
if is_hzvm
    cflags += [
        '-DKOALA_USE_HZ_VM',
    ]
    module_prefix = platform_prefix
    module_suffix = platform_suffix
endif
if is_panda
    cflags += [
        '-DKOALA_USE_PANDA_VM',
        '-DKOALA_FOREIGN_NAPI'
    ]
    include_dirs += [
        interop_src / 'napi',
        node_api_headers / 'include'
    ]
    module_prefix = platform_prefix
    module_suffix = platform_suffix
endif
if is_jni
    cflags += [
        '-DKOALA_USE_JAVA_VM',
    ]
    module_prefix = platform_prefix
    module_suffix = platform_suffix
endif

if is_dummy_impl
    cflags += [
        '-DUSE_DUMMY_IMPL',
    ]
    arkoala_sources += [
        './src/generated/dummy_impl.cc',
    ]
endif

if get_option('arkoala')
    sources += arkoala_sources
endif

if is_msvc
    cflags += []
else
    cflags += ['-Wno-parentheses-equality', '-Wno-extern-c-compat']
endif

if get_option('arkoala') and not is_ohos
    cflags += ['-DLIBACE_' + os.to_upper() + '_' + arch.to_upper()]
    shared_library(libace_name,
        libace_sources,
        override_options: [
            'b_lundef=false',
        ],
        install: true,
        include_directories: include_dirs,
        install_dir: source_dir / '..' / 'build',
        cpp_args: cflags,
        link_args: ldflags,
        dependencies: []
    )
endif

if is_panda
library_use_name_ani = library_use_name + '_ani'
library_use_name_ets = library_use_name + '_ets'
shared_library(library_use_name_ani,
    sources + sources_ani,
    override_options: [
        # So that ArkJS build can refer NAPI symbols.
        'b_lundef=false',
    ],
    install: true,
    name_prefix: module_prefix,
    name_suffix: module_suffix,
    include_directories: include_dirs + include_dirs_ani,
    install_dir: source_dir / '..' / 'build',
    cpp_args: cflags + cflags_ani,
    link_args: ldflags,
    dependencies: deps
)
shared_library(library_use_name_ets,
    sources + sources_ets,
    override_options: [
        # So that ArkJS build can refer NAPI symbols.
        'b_lundef=false',
    ],
    install: true,
    name_prefix: module_prefix,
    name_suffix: module_suffix,
    include_directories: include_dirs + include_dirs_ets,
    install_dir: source_dir / '..' / 'build',
    cpp_args: cflags + cflags_ets,
    link_args: ldflags,
    dependencies: deps
)
else
shared_library(library_use_name,
    sources,
    override_options: [
        # So that ArkJS build can refer NAPI symbols.
        'b_lundef=false',
    ],
    install: true,
    name_prefix: module_prefix,
    name_suffix: module_suffix,
    include_directories: include_dirs,
    install_dir: source_dir / '..' / 'build',
    cpp_args: cflags,
    link_args: ldflags,
    dependencies: deps
)
endif

if get_option('vmloader') == true

    vmloader_cflags = ['-DKOALA_' + os.to_upper(), '-DKOALA_' + os.to_upper() + '_' + arch.to_upper()]
    vmloader_ldflags = []

    if is_ohos
        vmloader_ldflags += ['-lhilog_ndk.z']
    endif

    if get_option('vmloader_apis').contains('jni')
        jni_os_dir = os
        if jni_os_dir == 'windows'
            jni_os_dir = 'win32'
        endif
        include_dirs += [
            get_option('jdk_dir') / 'include',
            get_option('jdk_dir') / 'include' / jni_os_dir,
        ]
        vmloader_cflags += [
            '-DKOALA_JNI',
        ]
    endif

    if get_option('vmloader_apis').contains('ets')
        include_dirs += [
            interop_src / 'ets',
        ]
        vmloader_cflags += [
            '-DKOALA_ETS_NAPI',
        ]
    endif

    shared_library('vmloader',
        interop_src / 'vmloader.cc',
        override_options: [
            'b_lundef=false',
        ],
        include_directories: include_dirs,
        install: true,
        install_dir: source_dir / '..' / 'build',
        cpp_args: vmloader_cflags,
        link_args: vmloader_ldflags,
    )

    loader_sources = [
        './src/generated/library.cc',
        './src/vsync.cc',
        interop_src / 'common-interop.cc',
        interop_src / 'interop-logging.cc',
    ]

    if is_napi
    loader_sources += [
        interop_src / 'napi/convertors-napi.cc',
    ]
    endif

    cflags += ['-DLIBACE_' + os.to_upper() + '_' + arch.to_upper()]
    shared_library('ArkoalaLoader',
        loader_sources,
        override_options: [
            # So that we can refer NAPI symbols.
            'b_lundef=false',
        ],
        install: true,
        name_prefix: module_prefix,
        name_suffix: module_suffix,
        include_directories: include_dirs,
        install_dir: source_dir / '..' / 'build',
        cpp_args: cflags,
        link_args: ldflags,
        dependencies: deps
    )
endif
